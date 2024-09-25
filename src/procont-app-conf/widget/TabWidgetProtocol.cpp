#include "TabWidgetProtocol.h"

#include "TabWidgetTree.h"

#include "log/Logger.h"

#include <QTreeWidget>
#include <QHeaderView>
#include <QUndoView>
#include <QPlainTextEdit>

#include <QDebug>

CWidgetMessage * CWidgetMessage::m_pInstance = nullptr;
QPlainTextEdit * CWidgetMessage::m_pWidgetBuild = nullptr;

CWidgetMessage::CWidgetMessage(QWidget *parent) :
    QTabWidget{parent},
    m_pWidgetMessage(nullptr)
{
    m_pWidgetMessage = new QTreeWidget(this);
    m_pWidgetMessage->setColumnCount(6);
    m_pWidgetMessage->header()->resizeSection(1, 150);
    m_pWidgetMessage->header()->resizeSection(2, 160);
    m_pWidgetMessage->header()->resizeSection(3, 220);
    m_pWidgetMessage->header()->resizeSection(4, 150);
    m_pWidgetMessage->setHeaderLabels(QStringList() << tr("Number") << tr("Type") << tr("Time") << tr("Source") << tr("Object") << tr("Message"));
    addTab(m_pWidgetMessage, tr("Messages"));

    m_pWidgetAction = new QUndoView(this);
    // m_pActionUndoView->setStack(CWidgetProject::instance()->undoStack());
    addTab(m_pWidgetAction, tr("Actions"));

    if(m_pWidgetBuild == nullptr)
        m_pWidgetBuild = new QPlainTextEdit(this);
    m_pWidgetBuild->setReadOnly(true);
    addTab(m_pWidgetBuild, tr("Build"));

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

QPlainTextEdit * CWidgetMessage::buildWidget()
{
    return m_pWidgetBuild;
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
            root = new QTreeWidgetItem(m_pWidgetMessage);
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
    m_pWidgetMessage->sortByColumn(0, Qt::DescendingOrder);
}
