#include "cgraphicshelper.h"

#include <QMimeData>
#include <QPixmap>
#include "../palette/palette.h"
#include "../../../st/CodeEditorWidget.h"
#include <QDrag>
#include <QTimer>
#include "../../general/QtDialogs.h"

CGraphicsHelper::CGraphicsHelper(QDomNode *node, CodeEditorWidget * st_widget) : QWidget()
{
    m_pou_node = node;
    m_pou = new CPou(*m_pou_node);

    m_st_widget = st_widget;

    fill_interface();

    m_graphics_world = new COglWorld(m_pou, &m_hatch_tl);

    connect(this, &CGraphicsHelper::canvas_resized,
            m_graphics_world, &COglWorld::win_resized);
    connect(this, &CGraphicsHelper::scroll_bars_moving,
            m_graphics_world, &COglWorld::view_hatch_moved);
    connect(this, &CGraphicsHelper::mouse_clicked,
            m_graphics_world, &COglWorld::mouse_clicked);
    connect(this, &CGraphicsHelper::mouse_drag_over,
            m_graphics_world, &COglWorld::mouse_drag_over);
    connect(this, &CGraphicsHelper::shutdown_highlights,
            m_graphics_world, &COglWorld::shutdown_highlights);
    connect(this, &CGraphicsHelper::mouse_left_pressed,
            m_graphics_world, &COglWorld::mouse_left_pressed);
    connect(this, &CGraphicsHelper::mouse_moving,
            m_graphics_world, &COglWorld::mouse_move);
    connect(m_graphics_world, &COglWorld::canvas_changed,
            this, &CGraphicsHelper::diagram_sized);
    connect(m_graphics_world, &COglWorld::update_hatch,
            this, &CGraphicsHelper::project_complete);

    m_ladders = m_graphics_world->ladders();
}

CGraphicsHelper::~CGraphicsHelper()
{
    delete m_graphics_world;
    delete m_pou;
}

std::vector<CLadder*>  * CGraphicsHelper::ladders()
{
    return m_ladders;
}

void CGraphicsHelper::on_right_mouse_click(QMouseEvent *event)
{
    // TODO: if under mouse is ladder or nothing - build context menu
}

void CGraphicsHelper::on_left_mouse_click(QMouseEvent *event)
{
    emit mouse_left_pressed(event->pos());
}

void CGraphicsHelper::on_mouse_released(const QPoint &pos)
{

}

void CGraphicsHelper::on_key_press_evt(QKeyEvent *event)
{
    // TODO: activate shortcuts or may be graphics world moving by WSAD
}

void CGraphicsHelper::on_key_released_event(QKeyEvent *event)
{
    // TODO: see above
}

void CGraphicsHelper::on_drop_event(QDropEvent *event)
{
    auto mime = event->mimeData();
    CLadder * receiver = nullptr;

    /// define which ladder is receiver
    s_selection selected = m_graphics_world->get_selection(event->position().toPoint());

    /// define what is dropped: component or ladder, from palette or inner drag
    if (mime->property("palette").toInt() == 1)
    {
        EPaletteElements type = (EPaletteElements)event->mimeData()->property("element").toInt();
        /// new component
        if (type != EPaletteElements::EG_CIRCUIT)
        {
            if (selected.ladder)
            {
                m_graphics_world->insert_new_component(selected.ladder, type);
            }
            else
            {
                event->ignore();
                return;
            }
        }
        /// new ladder from palette
        else
        {
            if (!selected.ladder)
                m_graphics_world->add_new_ladder();
            else
                m_graphics_world->insert_new_ladder(selected.ladder);
        }

    }

    /// well it's existing CLadder or component
    if (m_dragged_ladder)
    {
        m_graphics_world->insert_ladder(m_dragged_ladder, selected.ladder);
    }

    if (m_dragged_obj && selected.ladder)
    {
        /// if dropped on the source ladder
        if (selected.ladder == m_object_source)
        {
            selected.reset();
            m_dragged_obj = nullptr;
            m_object_source = nullptr;
            return;
        }

        if (!m_object_source->remove_object(m_dragged_obj))
        {
            QtDialogs::warn_user("Can't remove object from source");
            return;
        }

        selected.ladder->put_dragged_object(m_dragged_obj, event->position().toPoint());
    }

    /// there were different landing highlights. Now we have to switch them off
    m_graphics_world->shutdown_highlights();
    m_dragged_obj = nullptr;
    m_object_source = nullptr;
    m_dragged_ladder = nullptr;
    selected.reset();
    /// accept and out
    event->acceptProposedAction();

    m_graphics_world->check_diagram_size();
}

void
CGraphicsHelper::on_drag_enter_event(QDragEnterEvent *event)
{
    /*auto sel = m_graphics_world->get_selection();

    if (sel->ladder && !sel->object)
    {
        m_dragged_ladder = sel->ladder;
    }

    if (sel->object)
    {
        m_dragged_obj = sel->object;
    }

    if (sel->pin)
    {

    }*/
}

void CGraphicsHelper::on_drag_move_event(QDragMoveEvent *event)
{
    emit mouse_drag_over(event);
}

void CGraphicsHelper::resized(const int &w, const int &h)
{
    m_w = w;
    m_h = h;
    emit canvas_resized(w, h);
}

void CGraphicsHelper::on_drag_exit(QDragLeaveEvent *event)
{
    emit shutdown_highlights();
}

void CGraphicsHelper::scroll_bar_moved(const QPoint &pos)
{
    m_hatch_tl.setX(pos.x());
    m_hatch_tl.setY(pos.y());
    emit scroll_bars_moving(pos);
}

void CGraphicsHelper::fill_interface()
{
    if (m_pou->interface()->is_empty())
    {
        return;
    }

    QString name = "PROGRAM " + m_pou->name() + "\n";
    QString vars = name;
    QString comment;
    auto iface = m_pou->interface();

    vars += "VAR\n";
    for (auto &var : *iface->local_variables()->variables())
    {
        // TODO: realize arrays, addresses pointers and so on
        comment = var->comment().isEmpty() ? "" : "//" + var->comment();
        vars += "\t"+  var->name() + "\t:\t"+var->type() + ";\t" +  comment + "\n";
    }
    vars += "END_VAR";

    // m_st_widget->setPlainText(vars);
}

void CGraphicsHelper::on_drag_ladder_enter(QDragEnterEvent *event)
{
    auto sel = m_graphics_world->get_selection();
    if (!sel->ladder)
    {
        return;
    }

    m_dragged_ladder = sel->ladder;

    //emit drag_ladder_enter(event);
}

void CGraphicsHelper::on_drag_object_enter(QDragEnterEvent *event)
{
    auto sel = m_graphics_world->get_selection();
    if (!sel->object)
    {
        return;
    }

    m_dragged_obj = sel->object;
    m_object_source = sel->ladder;
    //emit  drag_object_enter(event);
}

void CGraphicsHelper::on_move_object(QDragMoveEvent *event)
{

}

void CGraphicsHelper::on_move_ladder(QDragMoveEvent *event)
{

}

void CGraphicsHelper::diagram_sized(const int &w, const int &h)
{
    emit diagram_resized(w, h);
}

void CGraphicsHelper::project_complete()
{
    emit on_project_loaded();
}


