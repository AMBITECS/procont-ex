//
// Created by artem on 11/17/24.
//

#include "CPinVarEditor.h"
#include "CTreeItem.h"
#include "editor/fbd/resources/colors.h"
#include <QHeaderView>
#include <QEvent>
#include <QKeyEvent>
#include <QTimer>
#include <QLineEdit>
#include "../graphics/CDiagramObject.h"
#include "../graphics/CLadder.h"
#include "../graphics/COglWorld.h"


extern CProject *project;

CPinVarEditor::CPinVarEditor(QWidget *parent) : QComboBox(parent), skipNextHide(false)
{
    this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    this->installEventFilter(this);


    CDiagramColors colors;
    m_foreground_error = colors.base_colors().diag_text_alternate;
    m_background_error = colors.base_colors().err_color;
    m_foreground_norm = this->palette().color(QPalette::ColorRole::Text);
    m_background_norm = this->palette().color(QPalette::ColorRole::Base);

    m_view = new QTreeView(parent);
    m_view->viewport()->installEventFilter(this);

    connect(m_view, &QTreeView::clicked, this, &CPinVarEditor::tree_clicked);
    connect(this, &QComboBox::editTextChanged, this, &CPinVarEditor::text_changed);

    m_view->setFrameShape(QFrame::NoFrame);

    m_view->setEditTriggers(QTreeView::NoEditTriggers);
    m_view->setAlternatingRowColors(true);
    m_view->setSelectionBehavior(QTreeView::SelectRows);
    m_view->setRootIsDecorated(false);
    m_view->setWordWrap(false);
    m_view->setAllColumnsShowFocus(true);
    m_view->expandAll();
    m_view->setItemsExpandable(false);

    setView(m_view);

    m_view->header()->setVisible(true);

    QFont font("Helvetica", 8);
    m_view->setFont(font);

    this->setEditable(true);
}

CPinVarEditor::~CPinVarEditor()
{
    delete m_view;
    delete m_analytics;
}

void CPinVarEditor::showPopup()
{
    for (int i = 0; i < m_view->header()->count(); i++)
    {
        m_view->header()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
    }

    int size = 0;
    for (int i = 0; i < m_view->header()->count(); i++)
        size += m_view->header()->sectionSize(i);

    this->setFixedWidth(size + 15);

    //setRootModelIndex(QModelIndex());
    QComboBox::showPopup();
}

void CPinVarEditor::hidePopup()
{
    if (skipNextHide)
        skipNextHide = false;
    else
        QComboBox::hidePopup();
}

void CPinVarEditor::hideColumn(int n)
{
    m_view->hideColumn(n);
}

void CPinVarEditor::expandAll()
{
    m_view->expandAll();
}

void CPinVarEditor::selectIndex(const QModelIndex &index)
{
    setRootModelIndex(index.parent());
    setCurrentIndex(index.row());
    m_view->setCurrentIndex( index );
}

bool CPinVarEditor::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::KeyPress)
    {
        auto *evt = dynamic_cast<QKeyEvent*>(event);
        auto key = evt->key();

        if (key == Qt::Key_Escape)
        {
            reset_selection();
            QComboBox::hidePopup();
            emit edit_cancel();
            return false;
        }

        if (key == Qt::Key_Return || key == Qt::Key_Enter)
        {
            prepare_new_variable();
            QComboBox::hidePopup();
            return false;
        }
        reset_selection();
    }

    if (event->type() == QEvent::MouseButtonPress)// && object == view()->viewport())
    {
        auto* mouseEvent = dynamic_cast<QMouseEvent*>(event);
        QModelIndex index = view()->indexAt(mouseEvent->pos());

        if (index.isValid())
        {
            QPersistentModelIndex idx = index;
            tree_clicked(idx);
            return false;
        }

        if (!view()->visualRect(index).contains(mouseEvent->pos()))
        {
            skipNextHide = true;
            return false;
        }

    }

//    if (event->type() == QEvent::FocusOut && this->lineEdit()->text() != "")
//    {
//        reset_selection();
//        emit edit_cancel();
//        return true;
//    }
    return QObject::eventFilter(object, event);
}

void CPinVarEditor::tree_clicked(const QPersistentModelIndex &index)
{
    reset_selection();

    if (!index.isValid())
    {
        return;
    }

    if (!m_view->selectionModel()->hasSelection())
    {
        return;
    }

    auto * item = static_cast<TreeItem*>(m_view->currentIndex().internalPointer());
    if (item)
    {
        QPersistentModelIndex parent_index = index.parent();
        m_selected_item = item->item();

        if (!m_selected_item)
        {
            fprintf(stderr, "Algorithm is broken in 'CPinVarEditor::tree_clicked'");
            return;
        }

        if (parent_index.isValid())
        {
            auto parent_item = static_cast<TreeItem*>(parent_index.internalPointer());

            if (parent_item)
            {
                m_parent_item = parent_item->item();
                m_new_variable = parent_item->item()->name.c_str() + (QString)".";
            }
        }

        m_new_variable += item->item()->name.c_str();

        /// Этот финт ушами, что бы обойти непонятную очистку QComboBox'а. Иначе поле ввода остаётся пустым
        QTimer::singleShot(150, this, SLOT(show_variable()));
    }
}

void CPinVarEditor::show_variable()
{
    this->setEditText(m_new_variable);
}

void CPinVarEditor::prepare_new_variable()
{
    if (m_new_variable.isEmpty())
    {
        m_new_variable = this->currentText();
    }

    emit new_pin_connection(m_selected_item, m_new_variable);

    reset_selection();
}

void CPinVarEditor::reset_selection()
{
    m_new_variable = {};
    m_selected_item = nullptr;
    m_parent_item = nullptr;
}

void CPinVarEditor::text_changed(const QString &text)
{
    m_selected_item = nullptr;


    if (text.length() < 3)
    {
        set_error(false);
        return;
    }

    bool bad_type = false;
    CVariable *i_var = nullptr;
    bool compatibility{false};

    /// suppose text is constant, lets define type
    auto type = CFilter::get_type_from_const(text.toStdString());

    if (type == DDT_UNDEF || type == DDT_STRING || type == DDT_DERIVED)
    {
        /// ups... may be iface variable? Lets find it
        bad_type = true;
        i_var = project->types()->find_iface_variable(text);

        if (!i_var)
        {
            auto pin = m_analytics->
        }
    }

    if (i_var || !bad_type)
    {
        compatibility = check_compatibility(i_var, type);
    }

    set_error(!compatibility);
}

void CPinVarEditor::set_error(const bool &is_error)
{
    QPalette palette;

    if (!is_error)
    {
        palette.setColor(QPalette::ColorRole::Base, m_background_norm);
        palette.setColor(QPalette::ColorRole::Text, m_foreground_norm);
    }
    else
    {
        palette.setColor(QPalette::ColorRole::Base, m_background_error);
        palette.setColor(QPalette::ColorRole::Text, m_foreground_error);
    }


    this->setPalette(palette);
}

bool CPinVarEditor::check_compatibility(CVariable *iface_var, const EDefinedDataTypes &type)
{
    QString dr_type_name;
    EDefinedDataTypes dr_type;

    if (iface_var)
    {
        dr_type_name = iface_var->type();
        dr_type = get_type_from_string(dr_type_name.toStdString());
    }
    else
    {
        if (m_pin->direction() == PD_OUTPUT)
        {
            return false;
        }

        dr_type = type;
        dr_type_name = base_types_names[type];
    }

    s_compare_types compare_types;
    return CVariablesAnalytics::check_pin_compatibility(dr_type_name,
                                             dr_type,
                                             m_pin->type_name(),
                                             m_pin->type(),
                                             compare_types);
}

void CPinVarEditor::set_pin(CPin *pin)
{
    m_pin = pin;
    if (!m_analytics)
    {
        auto world = pin->parent()->parent()->parent();
        m_analytics = new CVariablesAnalytics(world, world->current_pou()->name());
    }

}
