#include "TabWidgetProtocol.h"

#include "TabWidgetTree.h"

#include "log/Logger.h"

#include <QTreeWidget>
#include <QHeaderView>
#include <QUndoView>

#include <QDebug>

CWidgetMessage *CWidgetMessage::m_pInstance = nullptr;

CWidgetMessage::CWidgetMessage(QWidget *parent) :
    QTabWidget{parent},
    m_pWidgetTreeMessage(nullptr)
{
    m_pWidgetTreeMessage = new QTreeWidget(this);
    m_pWidgetTreeMessage->setColumnCount(6);
    m_pWidgetTreeMessage->header()->resizeSection(1, 150);
    m_pWidgetTreeMessage->header()->resizeSection(2, 160);
    m_pWidgetTreeMessage->header()->resizeSection(3, 220);
    m_pWidgetTreeMessage->header()->resizeSection(4, 150);
    m_pWidgetTreeMessage->setHeaderLabels(QStringList() << tr("Number") << tr("Type") << tr("Time") << tr("Source") << tr("Object") << tr("Message"));
    addTab(m_pWidgetTreeMessage, tr("Messages"));

    m_pActionUndoView = new QUndoView(this);
    // m_pActionUndoView->setStack(CWidgetProject::instance()->undoStack());
    addTab(m_pActionUndoView, tr("Actions"));

    setMinimumHeight(200);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    setTabPosition(QTabWidget::South);

    connect(CMessanger::instance(), SIGNAL(signal_send(CMessage)), this, SLOT(slot_add(CMessage)));
}

CWidgetMessage::~CWidgetMessage()
{
}

CWidgetMessage * CWidgetMessage::instance()
{
    if(!m_pInstance)
        m_pInstance = new CWidgetMessage;

    return  m_pInstance;
}

void CWidgetMessage::set_type(QTreeWidgetItem *item_, CMessage::eMsgType type_) const
{
    switch(type_)
    {
    case CMessage::eMT_Info:
        item_->setIcon(1, style()->standardIcon(QStyle::SP_MessageBoxInformation));
        item_->setText(1, tr("Info"));
        break;
    case CMessage::eMT_Warning:
        item_->setIcon(1, style()->standardIcon(QStyle::SP_MessageBoxWarning));
        item_->setText(1, tr("Warning"));
        break;
    case CMessage::eMT_Critical:
        item_->setIcon(1, style()->standardIcon(QStyle::SP_MessageBoxCritical));
        item_->setText(1, tr("Critical"));
        break;
    default:
        item_->setIcon(1, style()->standardIcon(QStyle::SP_MessageBoxInformation));
        item_->setText(1, tr("Info"));
        break;
    }
}

void CWidgetMessage::slot_add(const CMessage &message_)
{
    bool first = true;
    QTreeWidgetItem *root;
    for(const auto& i : message_.text())
    {
        if(first)
        {
            first = false;
            root = new QTreeWidgetItem(m_pWidgetTreeMessage);
            set_type(root, message_.type());
            root->setText(0, QString().asprintf("%08lld", message_.number()));
            root->setText(2, message_.time().toString("dd.MM.yyyy hh:mm:ss.zzz"));
            root->setText(3, message_.function());
            root->setText(4, QString("0x%1").arg(*(quint64*)message_.object(), 16, 16, QChar('0')));
            root->setText(5, i);
        }
        else
        {
            QTreeWidgetItem *item = new QTreeWidgetItem(root);
            item->setText(2, i);
        }
    }
    m_pWidgetTreeMessage->sortByColumn(0, Qt::DescendingOrder);
}
