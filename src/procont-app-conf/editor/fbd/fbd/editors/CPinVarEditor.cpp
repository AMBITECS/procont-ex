//
// Created by artem on 11/17/24.
//

#include "CPinVarEditor.h"
#include "qvarselectmodel.h"
#include <QHeaderView>
#include <QEvent>
#include <QKeyEvent>
#include <QTimer>
#include <QLineEdit>


CPinVarEditor::CPinVarEditor(QWidget *parent) : QComboBox(parent)
{
    this->setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    this->installEventFilter(this);

    m_view = new QTreeView(parent);

    connect(m_view, &QTreeView::clicked, this, &CPinVarEditor::tree_clicked);

    m_view->setFrameShape(QFrame::NoFrame);

    m_view->setEditTriggers(QTreeView::NoEditTriggers);
    m_view->setAlternatingRowColors(true);
    m_view->setSelectionBehavior(QTreeView::SelectRows);
    m_view->setRootIsDecorated(false);
    //m_view->setWordWrap(true);
    m_view->setAllColumnsShowFocus(true);
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

    this->setFixedWidth(size + 5);

    setRootModelIndex(QModelIndex());
    QComboBox::showPopup();
}

void CPinVarEditor::hidePopup()
{
    setRootModelIndex(m_view->currentIndex().parent());
    setCurrentIndex(  m_view->currentIndex().row());

    auto item = static_cast<TreeItem*>(m_view->currentIndex().internalPointer());
    if (item)
    {
        tree_clicked(m_view->currentIndex());
        //m_new_variable = item->name;
        /// Этот финт ушами, что бы обойти непонятную очистку QComboBox'а. Иначе поле ввода остаётся пустым
        QTimer::singleShot(20, this, SLOT(show_variable()));
    }

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
            emit edit_cancel();
            return false;
        }

        if (key == Qt::Key_Return || key == Qt::Key_Enter)
        {
            prepare_new_variable();
            return false;
        }
        reset_selection();
    }

    if (event->type() == QEvent::FocusOut && this->lineEdit()->text() != "")
    {
        reset_selection();
        emit edit_cancel();
        return false;
    }
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

    m_new_variable = "";

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

        this->setEditText(m_new_variable);
    }
}

void CPinVarEditor::show_variable()
{
    this->setEditText(m_new_variable);
}

void CPinVarEditor::prepare_new_variable()
{
    emit new_pin_connection(m_selected_item, m_new_variable);
    reset_selection();
}

void CPinVarEditor::reset_selection()
{
    //m_new_variable = {};
    m_selected_item = nullptr;
    m_parent_item = nullptr;
}
