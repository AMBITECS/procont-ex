//
// Created by artem on 29.10.24.
//

#include <QTimer>
#include "COglWorld.h"
#include <QApplication>
#include <QDrag>
#include <QMimeData>



#include "../redo-undo/CAddNewLadder.h"
#include "../redo-undo/CInsertNewLadder.h"
#include "../redo-undo/CInsertNewObject.h"
#include "../redo-undo/CMoveObject.h"
#include "../redo-undo/CInsertLadder.h"
#include "../redo-undo/CRenameInst.h"

#include "coglwidget.h"
#include "CGrapchicsLogic.h"
#include "editor/fbd/general/QtDialogs.h"
#include "../editors/CEditors.h"


uint16_t    max_local_id;



COglWorld::COglWorld(COglWidget * openGLwidget, CPou *pou, QPoint * hatch_pos)
{
    max_local_id = 0;

    m_ladders         = new std::vector<CLadder*> ();
    m_visible_ladders = new std::vector<CLadder*> ();
    m_undo_stack      = new QUndoStack();
    m_hatch_topLeft   = hatch_pos;
    m_pou = pou;
    m_diagram_type = EBodyType::BT_COUNT;

    m_editors   = new CEditors(openGLwidget, this, pou->sourceDomNode());
    connect(m_editors, &CEditors::interface_new_var,
            [this](const QString &t, const QString &n){ iface_new_var(t, n); });

    connect(m_editors, &CEditors::interface_rename,
            [this](const QString &o, const QString &n){ iface_rename(o, n); });

    connect(m_editors, &CEditors::pin_variable_renamed,
            this, &COglWorld::pin_variable_rename);

    init_projects_instances();

    QTimer::singleShot(20, this, SLOT(load_later()));
}

COglWorld::~COglWorld()
{
    clear_ladders();
    delete m_ladders;
    delete m_visible_ladders;
    delete m_undo_stack;
    delete m_editors;
}

void COglWorld::init_projects_instances()
{
    if (!m_pou->bodies()->isEmpty())
    {
        m_diagram_type = m_pou->bodies()->front()->diagram_lang();
        if (m_diagram_type == BT_FBD)
        {
            m_fbd_content = m_pou->bodies()->front()->fbd_content();
        }
        else
        {
            m_fbd_content = m_pou->bodies()->front()->add_fbd_diagram();
        }
        return;
    }

    auto body = new CBody();
    m_pou->bodies()->push_back(body);
    m_fbd_content = body->add_fbd_diagram();
    m_diagram_type = BT_FBD;
}

CLadder *COglWorld::add_new_ladder()
{
    auto cmd_new_ladder = new CAddNewLadder(this);
    m_undo_stack->push(cmd_new_ladder);

    emit undo_enabled();

    return cmd_new_ladder->new_ladder();
}

bool COglWorld::move_object(CLadder *source, CLadder *destination, CDiagramObject *object, const QPoint &pos)
{
    source = object->parent();
    auto cmd_move = new CMoveObject(this, source, destination, object, pos);
    m_undo_stack->push(cmd_move);

    if (!cmd_move->is_error())
    {
        emit undo_enabled();
    }

    return !cmd_move->is_error();
}

void COglWorld::clear_ladders()
{
    for (auto &item : *m_ladders)
    {
        delete item;
    }
    m_ladders->clear();
}

std::vector<CLadder*>  *COglWorld::ladders()
{
    return m_visible_ladders;
}

void COglWorld::win_resized(const int &w, const int &h)
{
    m_hatch_width = w;
    m_hatch_height = h;
    m_hatch_size = QSize(w, h);

    update_visible_ladders();
}

void COglWorld::view_hatch_moved(const QPoint &)
{
    /// define visible ladders
    update_visible_ladders();
}

s_selection COglWorld::get_selection(const QPoint &pos)
{
    m_selection.reset();

    if (m_ladders->empty())
    {
        return m_selection;
    }

    bool p_selected = false;

    for (auto vis : *m_visible_ladders)
    {
        if (!vis->is_clicked_here(pos))
        {
            continue;
        }

        m_selection.ladder = vis;

        for (auto &obj : *vis->draw_components())
        {
            if (obj->rect()->contains(pos))
            {
                m_selection.object = obj;
                break;
            }

            for (auto &pin : *obj->pins())
            {
                if (!pin->pin_here(pos))
                {
                    continue;
                }
                m_selection.pin = pin;
                p_selected = true;
                break;
            }
            if (p_selected)
                break;
        }

        CConnectLine *sel_line = nullptr;
        for (auto &line : *vis->connections())
        {
            line->set_selected(false);
            if (line->is_clicked_on(pos))
            {
                sel_line = line;
            }
        }

        if (sel_line)
        {
            sel_line->set_selected(true);
            m_selection.connection_line = sel_line;
            p_selected = true;
        }

        if (p_selected)
            break;
    }
    return m_selection;
}

QPoint COglWorld::get_visible_range(const QPoint &)
{
    /// исходим из того, что лестниц более 100
    /// TODO: обязательно отрефакторить этот мусор
    uint16_t index = 0;
    uint16_t count = m_ladders->size();

    /// определив один видимый, мы определим начальный диаппазон +limit -limit от этого видимого и уже из этого
    /// начального диаппазона определим диаппазон реально видимых ступеней
    int limit = 20;
    int ladder_top, ladder_bottom;
    int left = 0;
    int right = count - 1;
    int mid;

    CLadder * curr_ladder = m_ladders->at(index);

    /// define one of visible by binary search method
    while ((right > left))
    {
        mid = (left + right) / 2;
        curr_ladder = m_ladders->at(mid);

        ladder_top = curr_ladder->base_relative_rect()->top();
        ladder_bottom = curr_ladder->base_relative_rect()->bottom();

        if (curr_ladder->is_visible())
        {
            break;
        }

        /// if lower
        if (ladder_top >= m_hatch_height)
        {
            right = mid - 1;
        }

        /// if higher
        if (ladder_bottom <= 0)
        {
            left = mid + 1;
        }

    }

    if (!curr_ladder->is_visible())
    {
        return {0,0};
    }

    /// it could be situation with single visible ladder
    if (right <= left)
    {
        return {left, right};
    }

    /// Definition of the visible ladders range starts from the range -(minus) "limit" items from defined
    /// visible item till + "limit" items from defined visible item

    int first_number = curr_ladder->number() - limit;
    int last_number = curr_ladder->number() + limit;

    /// strange checkins. Has to be refactoring
    {
        if (first_number < 0)
            first_number = 0;
        if (first_number >= count)
            return {0, 0};

        if (last_number < 0)
            return {0, 0};
        if (last_number >= count)
            last_number = count - 1;
    }

    int last = -1;
    int first = -1;

    for (int i = first_number; i <= last_number; ++i)
    {
        auto ladder = m_ladders->at(i);

        if ( ladder->is_visible() and first < 0 )
        {
            first = i;
        }

        if ( !ladder->is_visible() && first >= 0 )
        {
            last = i; // a little reserve
            break;
        }
    }

    if ( (first >= 0 && first < count) && last < 0)
        last = count - 1;

    if (first < 0 || last < 0)
        return {0, 0};

    return {first, last};
}

void COglWorld::load_project()
{
    CVariablesAnalytics analytics(this);

    CLadder *cur_ladder;

    /// loading diagram objects and locate them to the corresponding ladder (without connecting lines)
    for (auto &block : *m_fbd_content->blocks())
    {
        check_local_id(block->local_id());
        cur_ladder = get_ladder(block->global_id().toLong());

        analytics.setup_block(block);
        auto object = cur_ladder->add_object(block);


        analytics.bind_pins(object);

        object->update_bound_rect();
        object->update_position();
    }

    /// need to shake projects graphics
    if (!m_ladders->empty())
    {
        CLadder *prev = nullptr;
        CLadder *next = nullptr;
        for (auto &ladder : *m_ladders)
        {
            ladder->set_previous(prev);
            if (prev)
            {
                prev->set_next(ladder);
            }

            ladder->resort();

            prev = ladder;
        }

        m_ladders->front()->update_real_position();
    }

    /// draw connecting lines
    CGraphicsLogic connect_logic;
    for (auto &ladder : *m_ladders)
    {
        for (auto &obj : *ladder->draw_components())
        {
            for (auto &pin : *obj->pins())
            {
                if (pin->graphic_connection_base()->block_local_id == 0)
                {
                    continue;
                }

                /// this pin has to be connected to the other pin. Find him.
                CConnectorPin * opposite_pin = find_opposite_pin(pin);

                if (opposite_pin->parent()->parent() != pin->parent()->parent())
                {
                    // FIXME: возможно на этот пин нужно что-нить повесить
                    break;
                }

                CConnectLine * line = connect_logic.add_new_line(pin, opposite_pin);

                if (line)
                {
                    pin->parent()->parent()->add_line(line);
                }
            }
        }
    }
}

void COglWorld::load_later()
{
    if (m_diagram_type == BT_COUNT)
    {
        return;
    }

    switch (m_diagram_type) {
        case BT_FBD:
            load_project();
            break;
        case BT_LD:
        default:
            break;
    }

    if (m_ladders->empty())
    {
        CLadder *prev = m_ladders->empty() ? nullptr : m_ladders->back();
        auto last = new CLadder(m_hatch_topLeft, &m_hatch_size, prev);

        m_ladders->push_back(last);
        if (prev)
        {
            prev->set_next(last);
        }
    }

    check_diagram_size();
    update_visible_ladders();

    emit update_hatch();
}

void COglWorld::check_diagram_size()
{
    QPoint br = m_ladders->back()->real_bottom_right();

    if (m_diagram_size.width() != br.x() ||
        m_diagram_size.height() != br.y()
            )
    {
        m_diagram_size = QSize(br.x(), br.y());

        emit canvas_changed(br.x(), br.y());
    }
}

void COglWorld::shutdown_highlights()
{
    for (auto lad : *m_visible_ladders)
    {
        lad->highlights_off();
    }
}

CLadder *COglWorld::insert_new_ladder(CLadder *next)
{
    auto cmd_insert_ladder = new CInsertNewLadder(this, next);
    m_undo_stack->push(cmd_insert_ladder);

    emit undo_enabled();

    return cmd_insert_ladder->new_ladder();
}

CDiagramObject * COglWorld::insert_new_component(CLadder *p_ladder, const EPaletteElements &element, const QPoint &pos)
{
    if (!m_fbd_content)
    {
        QtDialogs::warn_user("There is no FBD POUs");
        return nullptr;
    }

    if (element < EL_AND || element >= EP_FBD)
    {
        QtDialogs::warn_user("Пока компонент не поддерживается.");
        return nullptr;
    }

    auto cmd_insert_obj = new CInsertNewObject(this, m_fbd_content, p_ladder, element, pos);
    m_undo_stack->push(cmd_insert_obj);

    emit undo_enabled();

    return cmd_insert_obj->inserted_object();
}

void COglWorld::update_visible_ladders()
{
    if (m_ladders->empty())
    {
        return;
    }

    auto range = get_visible_range(*m_hatch_topLeft);
    if (range == QPoint())
    {
        if (!m_ladders->empty())
            range = QPoint(0, (int)m_ladders->size());
    }

    if ((range.y() + 1) <= m_ladders->size())
    {
        range.setY(range.y()+1);
    }

    m_visible_ladders->clear();
    m_visible_ladders->insert(m_visible_ladders->end(),
                              m_ladders->begin() + range.x(),
                              m_ladders->begin() + range.y());

    /*for (int i = range.x(); i < range.y(); i++)
    {
        m_ladders->at(i)->update_relative_position();
    }*/
    for (auto &item : *m_visible_ladders)
    {
        item->update_relative_position();
    }

    emit update_hatch();
}

CLadder *COglWorld::get_ladder(const unsigned long &id_ladder)
{
    CLadder *ladder;

    if (id_ladder >= m_ladders->size())
    {
        size_t ind = m_ladders->empty() ? 0 : m_ladders->size() - 1;
        CLadder *prev = m_ladders->empty() ? nullptr : m_ladders->back();

        for (auto i = ind; i < (id_ladder + 1); i++)
        {
            ladder = new CLadder(m_hatch_topLeft, &m_hatch_size, prev);

            if (prev)
            {
                prev->set_next(ladder);
            }

            m_ladders->push_back(ladder);
            prev = ladder;
        }
    }
    else
    {
        ladder = m_ladders->at(id_ladder);
    }
    return ladder;
}

void COglWorld::mouse_left_pressed(const QPoint &pos)
{

    m_selection = get_selection(pos);

    for (auto &ladder : *m_ladders)
    {
        ladder->set_selected(false);

        if (ladder == m_selection.ladder)
        {
            ladder->get_selected(pos, &m_selection);
            ladder->set_selected(true);
        }
    }

    m_mouse_pressed = pos;
}

void COglWorld::mouse_move(QMouseEvent *event)
{
    if (!(event->buttons() & Qt::LeftButton) || m_selection.empty())
    {
        return;
        m_mouse_pressed = {};
    }

    if ( (event->pos() - m_mouse_pressed).manhattanLength()
         < QApplication::startDragDistance()
       )
    {
        return;
    }

    auto *drag = new QDrag(this);
    auto   * mime = new QMimeData();
    drag->setMimeData(mime);

    mime->setProperty("element", -1);

    if (m_selection.ladder && !m_selection.object && !m_selection.pin)
    {
        mime->setProperty("source", "canvas");
        mime->setProperty("object", "ladder");

        drag->setPixmap(QPixmap::fromImage(m_selection.ladder->drag_image()));
    }

    if (m_selection.object)
    {
        drag->setPixmap(QPixmap::fromImage(m_selection.object->drag_image()));
        m_selection.object->update_position();

        mime->setProperty("source", "canvas");
        mime->setProperty("object", "object");
        mime->setProperty("object_id", (int)m_selection.object->local_id());
        mime->setImageData(QImage(":/16/images/16x16/brick_link.png"));
        //m_dra = m_selection.pin;
    }

    if (m_selection.pin)
    {
        QPixmap pix = QPixmap::fromImage(*m_selection.pin->image());
        drag->setPixmap(pix);
        mime->setProperty("source", "canvas");
        mime->setProperty("object", "pin");
        drag->setHotSpot(pix.rect().center());
        m_drag_pin = m_selection.pin;
    }

    Qt::DropAction dropAction = drag->exec(Qt::CopyAction | Qt::MoveAction);

    if (dropAction == Qt::CopyAction || dropAction == Qt::MoveAction)
    {

    }

    else
    {

    }

    emit drag_complete();
}

s_selection *COglWorld::selected()
{
    return &m_selection;
}

void COglWorld::insert_ladder(CLadder *dragged_ladder, CLadder *before)
{
    if (m_ladders->size() == 1 || before == dragged_ladder)
    {
        return;
    }

    auto cmd_insert = new CInsertLadder(this, dragged_ladder, before);
    emit undo_enabled();
    m_undo_stack->push(cmd_insert);
}

void COglWorld::check_local_id(const uint16_t &local_id)
{
    if (local_id > max_local_id)
    {
        max_local_id = local_id;
    }
}

QUndoStack *COglWorld::undo_stack()
{
    return m_undo_stack;
}

void COglWorld::mouse_dblClicked(QMouseEvent *evt)
{
    /// define pin's variable or object's instance name
    if (m_selection.pin)
    {
        /// pin variable
        if (m_selection.pin->direction() == PD_INPUT && m_selection.pin->is_connected())
        {
            return;
        }

        m_editors->show_combo(m_selection.pin);
        return;
    }

    QRect rect;
    for (auto &obj : *m_selection.ladder->draw_components())
    {
        auto text_obj = obj->inst_text();
        rect.setRect(text_obj->pos().x(), text_obj->pos().y() - text_obj->text_rect().height(),
                     obj->inst_text()->text_rect().width(), obj->inst_text()->text_rect().height());

        if (rect.contains(evt->pos()))
        {
            m_selection.object = obj;
            m_editors->show_line_edit(obj);
            break;
        }
    }
}

void COglWorld::iface_new_var(const QString &type, const QString &name)
{
    auto cmd_rename = new CRenameInst(this, m_selection.object,
                                      m_selection.object->type_name(), name);
    m_undo_stack->push(cmd_rename);
    m_selection.reset();

    emit undo_enabled();
    emit iface_var_new(type, name);
}

void COglWorld::iface_rename(const QString &old_name, const QString &new_name)
{
    auto cmd_rename = new CRenameInst(this, m_selection.object,
                                      old_name, new_name);
    m_undo_stack->push(cmd_rename);
    m_selection.reset();

    emit undo_enabled();
    emit iface_var_rename(old_name, new_name);
}

void COglWorld::pin_variable_rename()
{
    emit undo_enabled();
}

bool COglWorld::check_pins_to_connection(CConnectorPin *target_pin, s_compare_types &comparable_types)
{
    if (!m_drag_pin || (target_pin == m_drag_pin))
    {
        return false;
    }

    /// check target pin is busy
    if (target_pin->direction() == PD_INPUT && target_pin->is_connected())
    {
        comparable_types.target_type = "ко многим";
        comparable_types.dragged_type = "один";
        return false;
    }

    /// info about dragged pin type
    QString dragged_pin_type_name = m_drag_pin->type() == DDT_DERIVED ? m_drag_pin->derived_type() :
                                                base_types_names[m_drag_pin->type()];
    EDefinedDataTypes dragged_pin_type = m_drag_pin->type();

    /// info about target pin type
    QString target_pin_type_name = target_pin->type() == DDT_DERIVED ? target_pin->derived_type() :
                                        base_types_names[target_pin->type()];
    EDefinedDataTypes target_pin_type = target_pin->type();

    comparable_types.dragged_type = dragged_pin_type_name;
    comparable_types.target_type = target_pin_type_name;

    /// check if out connecting to out (wrong)
    if (m_drag_pin->direction() == target_pin->direction())
    {
        return false;
    }

    if (target_pin_type_name.isEmpty() || dragged_pin_type_name.isEmpty())
    {
        throw std::runtime_error("Logic is broken in 'COglWorld::check_pins_to_connection(...)'");
    }

    /// compatibility check
    CVariablesAnalytics analytic(this);

    bool res = analytic.check_pin_compatibility(dragged_pin_type_name, dragged_pin_type,
                                                target_pin_type_name, target_pin_type,
                                                comparable_types);

    return res;
}

void COglWorld::connect_pins(CConnectorPin *dragged_pin, CConnectorPin *target_pin)
{
    /// if pin ladders are the same - graphic connection
    if (dragged_pin->parent()->parent() == target_pin->parent()->parent())
    {
        CGraphicsLogic connect_logic;
        CConnectLine * line = connect_logic.add_new_line(dragged_pin, target_pin);
        target_pin->parent()->parent()->add_line(line);
    }

    emit undo_enabled();
}

CConnectorPin *COglWorld::find_opposite_pin(CConnectorPin *f_pin)
{
    // auto ladder = f_pin->parent()->parent();
    auto base = f_pin->graphic_connection_base();

    for (auto &ladder : *m_ladders)
    {
        for (auto &obj : *ladder->draw_components())
        {
            if (base->block_local_id != obj->block()->local_id())
            {
                continue;
            }

            for (auto &pin : *obj->pins())
            {
                if (base->block_var == pin->block_var())
                {
                    return pin;
                }
            }
        }
    }

    throw std::runtime_error("can't find opposite pin in 'COglWorld::find_opposite_pin'");

    return nullptr;
}

/*QPoint COglWorld::start_drag_point() const
{
    return m_mouse_pressed;
}*/

