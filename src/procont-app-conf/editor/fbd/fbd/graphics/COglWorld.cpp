//
// Created by artem on 29.10.24.
//

#include <QTimer>
#include "COglWorld.h"
#include <QApplication>
#include <QDrag>
#include <QMimeData>
#include <QTextStream>


#include "../redo-undo/CAddNewLadder.h"
#include "../redo-undo/CInsertNewLadder.h"
#include "../redo-undo/CInsertNewObject.h"
#include "../redo-undo/CMoveObject.h"
#include "../redo-undo/CInsertLadder.h"
#include "../redo-undo/CRenameInst.h"

#include "coglwidget.h"
#include "editor/fbd/common/general/QtDialogs.h"
#include "../editors/CEditors.h"
#include "editor/fbd/fbd/redo-undo/CPinConnecting.h"
#include "editor/fbd/fbd/redo-undo/CRemoveObject.h"


uint16_t    max_local_id;
extern CProject *project;


COglWorld::COglWorld(COglWidget * openGLwidget, CPou *pou, QPoint * hatch_pos)
{
    max_local_id = 0;

    m_pou = pou;
    m_ladders         = new std::vector<CFbdLadder*> ();
    m_visible_ladders = new std::vector<CFbdLadder*> ();
    m_undo_stack      = new QUndoStack();
    m_hatch_topLeft   = hatch_pos;


    m_diagram_type = EBodyType::BT_COUNT;

    m_editors   = new CEditors(openGLwidget, this);

    connect(m_editors, &CEditors::interface_new_var, this, &COglWorld::iface_new_var);


    connect(m_editors, &CEditors::interface_rename, this, &COglWorld::iface_rename);


    connect(m_editors, &CEditors::pin_variable_renamed,
            this, &COglWorld::pin_variable_rename);

    connect(this, &COglWorld::undo_enabled, this, &COglWorld::convert_to_XML);

    init_projects_instances();

    QTimer::singleShot(20, this, SLOT(load_later()));
}

COglWorld::~COglWorld()
{
    delete m_editors;
    clear_ladders();
    delete m_ladders;
    delete m_visible_ladders;
    delete m_undo_stack;
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

    auto body = new CBody(m_pou);
    m_pou->bodies()->push_back(body);
    m_fbd_content = body->add_fbd_diagram();
    m_diagram_type = BT_FBD;
}

CFbdLadder *COglWorld::add_new_ladder()
{
    auto cmd_new_ladder = new CAddNewLadder(this);
    m_undo_stack->push(cmd_new_ladder);

    emit undo_enabled();

    return cmd_new_ladder->new_ladder();
}

bool COglWorld::move_object(CFbdLadder *source, CFbdLadder *destination, CFbdObject *object, const QPoint &pos)
{
    source = object->parent();

    /// if last moving to the end


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

std::vector<CFbdLadder*>  *COglWorld::visible_ladders()
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
    /// define visible visible_ladders
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
                if (!pin->is_pin_at_pos(pos))
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

        CFbdConnectLine *sel_line = nullptr;
        for (auto &line : *vis->connecting_lines())
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

    CFbdLadder * curr_ladder = m_ladders->at(index);

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

    /// Definition of the visible visible_ladders range starts from the range -(minus) "limit" items from defined
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
    CFbdLadder *cur_ladder;
    CVariablesAnalytics analytics(this, m_pou->name());

    /// loading diagram objects and locate them to the corresponding ladder (without connecting lines)
    for (auto &block : *m_fbd_content->blocks())
    {
        check_local_id(block->local_id());
        if (block->global_id().toLongLong() == 0)
        {
            block->set_global_id(QString::number(1));
        }
        uint64_t ladder_index = block->global_id().toLong();
        cur_ladder = get_ladder(ladder_index);


        analytics.setup_block(block);
        auto object = cur_ladder->add_object(block);

        object->update_position();
    }

    analytics.load_connections();

    /// need to shake projects graphics
    if (!m_ladders->empty())
    {
        CFbdLadder *prev = nullptr;

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
        CFbdLadder *prev = m_ladders->empty() ? nullptr : m_ladders->back();
        auto last = new CFbdLadder(this,m_hatch_topLeft, &m_hatch_size, prev);

        m_ladders->push_back(last);
        if (prev)
        {
            prev->set_next(last);
        }
    }

    check_diagram_size();
    update_visible_ladders();

    emit set_current_pou(m_pou);

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

CFbdLadder *COglWorld::insert_new_ladder(CFbdLadder *next)
{
    auto cmd_insert_ladder = new CInsertNewLadder(this, next);
    m_undo_stack->push(cmd_insert_ladder);

    emit undo_enabled();

    return cmd_insert_ladder->new_ladder();
}

CFbdObject * COglWorld::insert_new_component(CFbdLadder *p_ladder, const EPaletteElements &element,
                                                 const QString &pou_name,
                                                 const QPoint &pos)
{
    if (!m_fbd_content)
    {
        QtDialogs::warn_user("There is no FBD POUs");
        return nullptr;
    }

    if (element < EL_AND || element >= E_COUNT)
    {
        QtDialogs::warn_user("Пока компонент не поддерживается.");
        return nullptr;
    }

    //Не доходит наименование POU;
    auto cmd_insert_obj = new CInsertNewObject(this, m_fbd_content, p_ladder, element, pou_name, pos);
    m_undo_stack->push(cmd_insert_obj);
    auto object = cmd_insert_obj->inserted_object();

    convert_to_XML();
    emit undo_enabled();


    return object;
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

    for (auto &item : *m_visible_ladders)
    {
        item->update_relative_position();
    }

    emit update_hatch();
}

CFbdLadder *COglWorld::get_ladder(const unsigned long &ied_ladder)
{
    CFbdLadder *ladder;

    uint64_t ladder_index = ied_ladder - 1;

    if (ladder_index >= m_ladders->size())
    {
        size_t ind = m_ladders->size();
        CFbdLadder *prev = m_ladders->empty() ? nullptr : m_ladders->back();

        for (auto i = ind; i <= (ladder_index); i++)
        {
            ladder = new CFbdLadder(this, m_hatch_topLeft, &m_hatch_size, prev);

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
        ladder = m_ladders->at(ladder_index);
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
    }

    if ( (event->pos() - m_mouse_pressed).manhattanLength()
         < QApplication::startDragDistance()
       )
    {
        return;
    }

    if(m_selection.pin && m_selection.pin->direction() == PD_INPUT && m_selection.pin->is_connected())
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
        if (m_selection.pin->parent()->instance_name() == "???")
        {
            QtDialogs::warn_user("Задайте объекту корректное имя");
            return;
        }
        QPixmap pix = QPixmap::fromImage(*m_selection.pin->image());
        drag->setPixmap(pix);
        mime->setProperty("source", "canvas");
        mime->setProperty("object", "pin");
        drag->setHotSpot(pix.rect().center());
        m_drag_pin = m_selection.pin;
    }

    drag->exec(Qt::CopyAction | Qt::MoveAction);

    emit drag_complete();
}

s_selection *COglWorld::selected()
{
    return &m_selection;
}

void COglWorld::insert_ladder(CFbdLadder *dragged_ladder, CFbdLadder *before)
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
    if (m_selection.empty() || !m_selection.ladder)
    {
        return;
    }

    /// define pin's variable or object's instance name
    if (m_selection.pin)
    {
        /// pin variable
        if (m_selection.pin->direction() == PD_INPUT && m_selection.pin->is_connected())
        {
            QtDialogs::warn_user("Пин уже имеет соединение");
            return;
        }

        if (m_selection.pin->parent()->instance_name() == "???")
        {
            QtDialogs::warn_user("Задайте объекту имя");
            return;
        }

        text_based_connecting_pin(m_selection.pin);
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

bool COglWorld::check_pins_to_connection(CPin *target_pin, s_compare_types &comparable_types)
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
    QString dragged_pin_type_name = m_drag_pin->type() == DDT_DERIVED ? m_drag_pin->type_name() :
                                                base_types_names[m_drag_pin->type()];
    EDefinedDataTypes dragged_pin_type = m_drag_pin->type();

    /// info about target pin type
    QString target_pin_type_name = target_pin->type() == DDT_DERIVED ? target_pin->type_name() :
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
    CVariablesAnalytics analytics(this, m_pou->name());
    bool res = CVariablesAnalytics::check_pin_compatibility(dragged_pin_type_name, dragged_pin_type,
                                                target_pin_type_name, target_pin_type,
                                                comparable_types);

    return res;
}

void COglWorld::connect_pins(CPin *dragged_pin, CPin *target_pin)
{
    if (dragged_pin->direction() == target_pin->direction())
    {
        QtDialogs::warn_user("Не могу соединить пины одной направленности");
    }
    auto cmd = new CPinConnecting(this, dragged_pin, target_pin);
    m_undo_stack->push(cmd);

    emit undo_enabled();
}

std::vector<CFbdLadder *> *COglWorld::all_ladders()
{
    return m_ladders;
}

void COglWorld::text_based_connecting_pin(CPin *selected_pin)
{
    /// connecting itself is in CEditors::new_pin_connection and here we just show comboBox
    m_editors->show_combo(m_selection.pin);
}

void COglWorld::convert_to_XML()
{
    QDomNode pou_node = m_pou->dom_node();
    emit diagram_changed(pou_node);

    QUndoStack loc_stack;

    /// когда из диаграммы


    /*QDomDocument doc;
    QDomElement root = doc.documentElement();
    if (root.isNull())
    {
        root = doc.createElement("project_pou");
        doc.appendChild(root);
    }


    QDomNode node = m_pou->dom_node();

    if (node.isNull())
    {
        QtDialogs::warn_user("pou's node is null");
        return;
    }
    root.appendChild(node);

    QString sFilePath = qApp->applicationDirPath() + "/" + "XML_project.xml";
    QFile file(sFilePath);
    if (!file.open(QFile::WriteOnly|QFile::Truncate | QFile::Text))
    {
        QtDialogs::warn_user("Can't save pou");
        return;
    }
    QTextStream stream( &file );
    //stream << doc.toString();
    doc.save(stream, 4);
    file.close();*/
}

CPou *COglWorld::current_pou()
{
    return m_pou;
}

void COglWorld::erase_object(CFbdObject *object)
{
    if (!object)
    {
        return;
    }

    auto cmd = new CRemoveObject(object);
    m_undo_stack->push(cmd);

    if (!object->instance_name().isEmpty())
        emit instance_removed(object->type_name(), object->instance_name());
}

