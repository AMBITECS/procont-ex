#include "cgraphicshelper.h"

#include <QMimeData>
#include <QPixmap>
#include <QTimer>
#include <QMenu>

#include "../../general/QtDialogs.h"
#include "../variables.h"
#include "coglwidget.h"

CGraphicsHelper::CGraphicsHelper(QDomNode *node) : QWidget()
{
    m_pou_node = node;
    if (node->isNull())
        m_pou = new CPou();
    else
        m_pou = new CPou(*m_pou_node);


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
    /// ещё не придумал
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
    //CLadder * receiver;

    /// reset all highlights
    for (auto &ladder : *m_ladders)
    {
        ladder->highlights_off();
    }

    /// define which ladder is receiver
    s_selection selected = m_graphics_world->get_selection(event->position().toPoint());

    QString drag_source = mime->property(txt_vars::drag_source_prop).toString();

    /// define what is dropped: component or ladder, from palette or inner drag
    if (drag_source == txt_vars::drag_src_palette)
    {
        EPaletteElements type = (EPaletteElements)event->mimeData()->property(txt_vars::drag_element).toInt();

        /// new component
        if (type >= 9)
        {
            if (selected.ladder)
            {
                m_graphics_world->insert_new_component(selected.ladder, type,
                                                       event->position().toPoint());
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

        if (!m_object_source->remove_object(m_dragged_obj))
        {
            QtDialogs::warn_user("Can't remove object from source");
            return;
        }

        selected.ladder->put_dragged_object(m_dragged_obj, event->position().toPoint());

        if (m_object_source != selected.ladder)
        {
            m_object_source->resort();
        }
        selected.ladder->resort();
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

void CGraphicsHelper::object_remove(CLadder *ladder, CDiagramObject *object)
{

}


bool CGraphicsHelper::make_menu(COglWidget *p_widget, QMenu *p_menu, const QPoint &point)
{
    s_selection selection = m_graphics_world->get_selection(point);

    if (selection.empty())
    {
        return false;
    }

    auto p_object = selection.object;
    auto p_ladder = selection.ladder;
    auto p_pin = selection.pin;

    if (p_object && p_ladder)
    {
        make_object_menu(p_menu, p_object, p_ladder);
    }

    if (p_pin)
    {
        make_pin_menu(p_menu, p_pin);
    }

    if (p_ladder && !p_pin && !p_object)
    {
        make_ladder_menu(p_menu, p_ladder);
    }

    return true;
}

void CGraphicsHelper::make_object_menu(QMenu *p_menu, CDiagramObject *p_object, CLadder *p_ladder)
{
    auto act_remove = new QAction(p_menu);
    auto act_cat = new QAction(p_menu);

    QAction * act_paste = nullptr;
    if (m_clip_object)
    {
        act_paste = new QAction(p_menu);
        act_paste->setEnabled(m_clip_object);
    }



    QString text = "Удалить " + p_object->type_name() + " " + p_object->instance_name();
    act_remove->setText(text);

    text = "Вырезать " + p_object->type_name() + " " + p_object->instance_name();
    act_cat->setText(text);

    if (m_clip_object)
    {
        text = "Вставить " + m_clip_object->type_name() + " " + m_clip_object->instance_name();
        act_paste->setIcon(QIcon(":/24/images/24x24/Paste.png"));
        //connect()
    }


    act_remove->setIcon(QIcon(":/24/images/24x24/Close.png"));
    connect(act_remove, &QAction::toggled, [=](){
        object_remove(p_ladder, p_object);});

    act_cat->setIcon(QIcon(":/16/images/16x16/cut_red.png"));
    connect(act_cat, &QAction::toggled, [=](){object_cat(p_ladder, p_object);});

    p_menu->addAction(act_remove);
    p_menu->addAction(act_cat);
    if(act_paste)
        p_menu->addAction(act_paste);
}

void CGraphicsHelper::make_pin_menu(QMenu *p_menu, CConnectorPin * p_pin)
{
    auto act_find_helper = new QAction(QIcon(":/24/images/24x24/Search.png"),
                                       "Найти переменную с помощью ассистента...",
                                       p_menu);
    auto act_edit_connect = new QAction(QIcon(":/24/images/24x24/Modify.png"),
                                        "Редактировать соединение",
                                        p_menu);
    auto act_reset_connect = new QAction(QIcon(":/16/images/16x16/chart_organisation_delete.png"),
                                        "Очистить соединение",
                                        p_menu);

    QAction * act_inversion = nullptr;
    QAction * act_edge_rising = nullptr;
    QAction * act_edge_falling = nullptr;
    //QAction * act_storage = nullptr;

    if (p_pin->type() == EDefinedDataTypes::DDT_BOOL)
    {
        act_inversion = new QAction(QIcon(""), "Инвертировать", p_menu);
        connect(act_inversion, &QAction::toggled, this, [p_pin]{p_pin->set_negated(!p_pin->is_negated());});

        act_edge_rising = new QAction(QIcon(""), "Нарастающий фронт");
    }




    p_menu->addAction(act_find_helper);
    p_menu->addAction(act_edit_connect);
    p_menu->addAction(act_reset_connect);
    p_menu->addSeparator();

}

void CGraphicsHelper::make_ladder_menu(QMenu *p_menu, CLadder *p_ladder)
{

}

void CGraphicsHelper::object_cat(CLadder *p_ladder, CDiagramObject *p_object)
{

}


