#include "cgraphicshelper.h"

#include <QMimeData>
#include <QPixmap>
#include <QTimer>
#include <QMenu>


#include "coglwidget.h"
#include "editor/fbd/common/general/QtDialogs.h"
#include "editor/fbd/fbd/redo-undo/CPinInvers.h"
#include "editor/fbd/fbd/redo-undo/CPinRising.h"
#include "editor/fbd/fbd/redo-undo/CPinFalling.h"
#include "editor/fbd/fbd/redo-undo/CResetConnections.h"

extern CProject *project;

CGraphicsHelper::CGraphicsHelper(COglWidget *ogl_widget, QDomNode *node) : QWidget()
{
    get_project(node);
    m_pou_node = node;
    m_opengl_widget = ogl_widget;

    m_graphics_world = new COglWorld(ogl_widget, m_pou, &m_hatch_tl);

    connect(m_graphics_world, &COglWorld::object_selected,
            [this](){emit object_selected();});

    connect(m_graphics_world, &COglWorld::set_current_pou,
            [=](CPou *pou){emit set_current_pou(pou);});

    connect(m_graphics_world, &COglWorld::instance_removed,
            [=](const QString &type, const QString &name){ emit instance_removed(type, name); });

    connect(m_graphics_world, &COglWorld::diagram_changed,
            [=](const QDomNode &node){emit diagram_changed(node);});

    connect(m_graphics_world, &COglWorld::drag_complete,
            this, &CGraphicsHelper::drag_process_complete);

    connect(m_graphics_world, &COglWorld::iface_var_new,
            this, &CGraphicsHelper::iface_new_var);

    connect(m_graphics_world, &COglWorld::iface_var_rename,
            this, &CGraphicsHelper::iface_ren_var);

    connect(m_graphics_world, &COglWorld::undo_enabled,
            [this](){emit this->undo_enabled();});

    connect(this, &CGraphicsHelper::canvas_resized,
            m_graphics_world, &COglWorld::win_resized);

    connect(this, &CGraphicsHelper::scroll_bars_moving,
            m_graphics_world, &COglWorld::view_hatch_moved);

    /*connect(this, &CGraphicsHelper::mouse_clicked,
            m_graphics_world, &COglWorld::mouse_clicked);*/

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

    connect(this, &CGraphicsHelper::mouse_dblClicked,
            this, &CGraphicsHelper::double_clicked);

    m_ladders = m_graphics_world->visible_ladders();
}

CGraphicsHelper::~CGraphicsHelper()
{
    project->Delete();
    delete m_graphics_world;
}

std::vector<CFbdLadder*>  * CGraphicsHelper::ladders()
{
    return m_ladders;
}

void CGraphicsHelper::on_right_mouse_click(QMouseEvent *)
{
    /// ещё не придумал
}

void CGraphicsHelper::on_left_mouse_click(QMouseEvent *event)
{
    emit mouse_left_pressed(event->pos());
}

void CGraphicsHelper::on_mouse_released(const QPoint &)
{

}

void CGraphicsHelper::on_key_press_evt(QKeyEvent *)
{
    ///activate shortcuts or may be graphics world moving by WSAD
}

void CGraphicsHelper::on_key_released_event(QKeyEvent *)
{
    /// see above
}

void CGraphicsHelper::on_drop_event(QDropEvent *event)
{
    const QMimeData* mime = event->mimeData();

    /// reset all highlights
    m_graphics_world->shutdown_highlights();

    /// define which ladder is receiver
    s_selection selected = m_graphics_world->get_selection(event->position().toPoint());

    QString drag_source = mime->property(txt_vars::drag_source_prop).toString();

    /// define what is dropped: component or ladder, from palette or inner drag
    if (drag_source == txt_vars::drag_src_palette)
    {
        EPaletteElements type = (EPaletteElements)event->mimeData()->property(txt_vars::drag_element).toInt();

        /// new component
        if (type >= EPaletteElements::EL_AND && selected.ladder)
        {
            QString pou_name = mime->property("name").toString();
            m_graphics_world->insert_new_component(selected.ladder, type, pou_name,
                                                   event->position().toPoint());
        }
        /// new ladder from palette
        else if (type == 0)
        {
            selected.ladder ? m_graphics_world->insert_new_ladder(selected.ladder) :
                              m_graphics_world->add_new_ladder();
        }
    }

    /// well it's existing CLadder or component
    bool move_ok = true;

    if(drag_source == txt_vars::drag_src_canvas)
    {

        /// moving ladder
        if (m_dragged_ladder && !m_dragged_obj && !m_dragged_pin)
        {
            m_graphics_world->insert_ladder(m_dragged_ladder, selected.ladder);
        }

        /// moving object
        if (m_dragged_obj && selected.ladder)
        {
            /// define errors
            if (m_dragged_obj->bound_graph_rect().contains(event->position().toPoint()))
            {
                return;
            }


            move_ok = m_graphics_world->move_object(m_object_source,
                                                    selected.ladder,
                                                    m_dragged_obj,
                                                    event->position().toPoint());
        }

        /// connecting pins
        if (m_dragged_pin && selected.pin)
        {
            m_graphics_world->connect_pins(m_dragged_pin, selected.pin);
        }
    }

    reset_dragged_objects();
    m_graphics_world->selected()->reset();
    /// accept and out
    if (!move_ok)
    {
        QtDialogs::warn_user("Не могу изъять объект из исходной ступени.");
        event->ignore();
    }
    else
    {
        event->acceptProposedAction();
    }

    m_graphics_world->check_diagram_size();
}

void
CGraphicsHelper::on_drag_enter_event(QDragEnterEvent *event)
{
    QString source_s = event->mimeData()->property("source").toString();

    if (source_s != txt_vars::drag_src_canvas)
    {
        return;
    }

    /*m_dragged_obj = nullptr;
    m_dragged_pin = nullptr;
    m_dragged_ladder = nullptr;*/

    s_selection *sel = m_graphics_world->selected();//get_selection(event->position().toPoint());

    if (sel->pin)
    {
        m_dragged_pin = sel->pin;
        return;
    }

    if (sel->ladder && !sel->object)
    {
        m_dragged_ladder = sel->ladder;
    }

    if (sel->object && !sel->pin)
    {
        m_dragged_obj = sel->object;
    }
}

void CGraphicsHelper::on_drag_move_event(QDragMoveEvent *event)
{
    /// check all visible visible_ladders

    if (event->mimeData()->property(txt_vars::drag_obj_prop_name) == txt_vars::drag_pin)
    {
        on_drag_pin(event);
        return;
    }


    for (auto &ladder : *m_ladders)
    {
        ladder->drag_object(event);
    }
}

void CGraphicsHelper::resized(const int &w, const int &h)
{
    emit canvas_resized(w, h);
}

void CGraphicsHelper::on_drag_exit(QDragLeaveEvent *)
{
    emit shutdown_highlights();
}

void CGraphicsHelper::scroll_bar_moved(const QPoint &pos)
{
    m_hatch_tl.setX(pos.x());
    m_hatch_tl.setY(pos.y());
    emit scroll_bars_moving(pos);
}

void CGraphicsHelper::on_drag_ladder_enter(QDragEnterEvent *)
{
    auto sel = m_graphics_world->selected();
    if (!sel->ladder)
    {
        return;
    }

    m_dragged_ladder = sel->ladder;

    //emit drag_ladder_enter(event);
}

void CGraphicsHelper::on_drag_object_enter(QDragEnterEvent *)
{
    auto sel = m_graphics_world->selected();
    if (!sel->object)
    {
        return;
    }

    m_dragged_obj = sel->object;
    m_object_source = sel->ladder;
    //emit  drag_object_enter(event);
}


void CGraphicsHelper::diagram_sized(const int &w, const int &h)
{
    emit diagram_resized(w, h);
}

void CGraphicsHelper::project_complete()
{
    emit on_project_loaded();
}

void CGraphicsHelper::object_remove(CFbdLadder *ladder, CFbdObject *object)
{
    m_graphics_world->erase_object(object);
}

bool CGraphicsHelper::make_menu(COglWidget *, QMenu *p_menu, const QPoint &point)
{
    s_selection selection = m_graphics_world->get_selection(point);

    if (selection.empty())
    {
        return false;
    }

    auto p_object = selection.object;
    auto p_ladder = selection.ladder;
    auto p_pin = selection.pin;

    /// UNDO / REDO
    auto *act_undo = new QAction(QIcon(":/24/images/24x24/Undo.png"), "");
    auto *act_redo = new QAction(QIcon(":/24/images/24x24/Redo.png"), "");

    if (m_graphics_world->undo_stack()->canUndo())
    {
        QString text = "Отменить " + m_graphics_world->undo_stack()->undoText();
        act_undo->setText(text);
        connect(act_undo, &QAction::triggered, [=](){m_graphics_world->undo_stack()->undo();});
    }
    else
    {
        act_undo->setText("Отмена");
        act_undo->setEnabled(false);
    }

    if (m_graphics_world->undo_stack()->canRedo())
    {
        QString text = "Повторить " + m_graphics_world->undo_stack()->redoText() ;
        act_redo->setText(text);
        connect(act_redo, &QAction::triggered, [=](){m_graphics_world->undo_stack()->redo();});
    }
    else
    {
        act_redo->setText(tr("Вернуть"));
        act_redo->setEnabled(false);
    }

    p_menu->addAction(act_undo);
    p_menu->addAction(act_redo);
    p_menu->addSeparator();


    /// Special actions
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

void CGraphicsHelper::make_object_menu(QMenu *p_menu, CFbdObject *p_object, CFbdLadder *p_ladder)
{
    auto act_remove = new QAction(p_menu);


    QString text = "Удалить " + p_object->type_name() + " " + p_object->instance_name();
    act_remove->setText(text);

    act_remove->setIcon(QIcon(":/24/images/24x24/Close.png"));
    connect(act_remove, &QAction::triggered, [=](){
        object_remove(p_ladder, p_object);});


    p_menu->addAction(act_remove);
}

void CGraphicsHelper::make_pin_menu(QMenu *p_menu, CPin * p_pin)
{
    auto act_reset_connect = new QAction(QIcon(":/16/images/16x16/chart_organisation_delete.png"),
                                        "Очистить соединения",
                                        p_menu);

    act_reset_connect->setEnabled(p_pin->is_connected());

    if (p_pin->is_connected())
    {
        connect(act_reset_connect, &QAction::triggered, [=](){
            auto act = new CResetConnections(p_pin);
            m_graphics_world->undo_stack()->push(act);
        });
    }

    act_reset_connect->setEnabled(p_pin->is_connected());

    QAction * act_inversion = nullptr;
    QAction * act_edge_rising;
    QAction * act_edge_falling;

    if (p_pin->type() == EDefinedDataTypes::DDT_BOOL && p_pin->direction() == PD_INPUT)
    {
        /// negated input
        QString negated_text = p_pin->input()->is_negated() ? "Сбросить \"инвертирование\"" : "Инвертировать вход";
        act_inversion = new QAction(QIcon(":/16/images/16x16/contrast.png"), negated_text);
        bool enabled = !p_pin->input()->is_negated();
        connect(act_inversion, &QAction::triggered,
                [=](){
                    auto cmd = new CPinInverse(p_pin->input(), enabled);
                    m_graphics_world->undo_stack()->push(cmd);
                    });

        /// rising edge
        QString rising_text = p_pin->input()->is_rising_edge() ? "Сбросить восходящий фронт" : "Установить восходящий фронт";
        act_edge_rising = new QAction(QIcon(":/24/images/24x24/Raise.png"), rising_text);
        connect(act_edge_rising, &QAction::triggered, [=](){
                auto cmd = new CPinRising(p_pin->input(), !p_pin->input()->is_rising_edge());
                m_graphics_world->undo_stack()->push(cmd);
                });

        /// falling edge
        QString falling_text = p_pin->input()->is_falling_edge() ? "Сбросить нисходящий фронт" : "Установить нисходящий фронт";
        act_edge_falling = new QAction(QIcon(":/24/images/24x24/Fall.png"), falling_text);
        connect(act_edge_falling, &QAction::triggered, [=](){
            auto cmd = new CPinFalling(p_pin->input(), !p_pin->input()->is_falling_edge());
            m_graphics_world->undo_stack()->push(cmd);
            });

    }

    //p_menu->addAction(act_edit_connect);
    p_menu->addAction(act_reset_connect);
    p_menu->addSeparator();

    if (act_inversion)
    {
        p_menu->addAction(act_inversion);
        p_menu->addAction(act_edge_rising);
        p_menu->addAction(act_edge_falling);
        p_menu->addSeparator();
    }

}

void CGraphicsHelper::make_ladder_menu(QMenu *p_menu, CFbdLadder *p_ladder)
{

}

void CGraphicsHelper::object_cat(CFbdLadder *p_ladder, CFbdObject *p_object)
{

}

void CGraphicsHelper::reset_dragged_objects()
{
    m_dragged_obj = nullptr;
    m_object_source = nullptr;
    m_dragged_ladder = nullptr;
    m_dragged_pin = nullptr;
}

QUndoStack *CGraphicsHelper::undo_stack()
{
    return m_graphics_world->undo_stack();
}

void CGraphicsHelper::double_clicked(QMouseEvent *evt)
{
    m_graphics_world->mouse_dblClicked(evt);
}

void CGraphicsHelper::iface_new_var(const QString &type, const QString &name)
{
    emit iface_var_new(type, name);
}

void CGraphicsHelper::iface_ren_var(const QString &old_name, const QString &new_name)
{
    emit iface_var_rename(old_name, new_name);
}

void CGraphicsHelper::on_drag_pin(QDragMoveEvent *event)
{
    s_selection sel = m_graphics_world->get_selection(event->position().toPoint());
    if (!sel.pin)
    {
        //emit types_wrong("", "", {}, false);
        event->ignore();
        return;
    }

    if (sel.pin == m_dragged_pin)
    {
        event->ignore();
        return;
    }

    if (sel.pin->direction() == m_dragged_pin->direction())
    {
        QString dir = sel.pin->direction() == PD_INPUT ? "вход" : "выход";
        emit types_wrong(dir, dir, event->position().toPoint(), false);
        return;
    }

    auto target_pin = sel.pin;
    s_compare_types comparable_types;
    QPoint pos = event->position().toPoint();

    auto res = m_graphics_world->check_pins_to_connection(target_pin, comparable_types);

    emit types_wrong(comparable_types.dragged_type, comparable_types.target_type, pos, res);

    res ? event->acceptProposedAction() : event->ignore();
}

void CGraphicsHelper::drag_process_complete()
{
    emit drag_complete();
}

void CGraphicsHelper::get_project(QDomNode *pou_node)
{

    QDomNode node = *pou_node;
    QDomNode prj_node = pou_node->parentNode().parentNode().parentNode();

    CProject::get_instance(prj_node);

    m_pou =  new CPou(node, project->types());
    auto exist_pou = project->types()->find_pou_by_name(m_pou->name());

    if (!exist_pou)
    {
        project->types()->add_pou(m_pou);
    }
    else
    {
        delete m_pou;
        m_pou = exist_pou;
    }
}

void CGraphicsHelper::remove_selected_object()
{
    m_graphics_world->delete_selected();
}



