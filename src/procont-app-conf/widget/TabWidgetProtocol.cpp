#include "TabWidgetProtocol.h"

#include "TabWidgetTree.h"

#include "log/Logger.h"

#include <QTreeWidget>
#include <QHeaderView>
#include <QUndoView>
#include <QPlainTextEdit>
#include <QApplication>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QToolBar>
#include <QActionGroup>
#include <QFileInfo>

#include <QDebug>

// ----------------------------------------------------------------------------
// *** IWidgetProtocolTab ***
//
IWidgetProtocolTab::IWidgetProtocolTab(QWidget *parent_) : QWidget(parent_)
{
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** CWidgetProtocolTab_message ***
//
CWidgetProtocolTab_message::CWidgetProtocolTab_message(QWidget *parent_) : IWidgetProtocolTab(parent_)
{
    m_pWidget = new QTreeWidget(this);
    m_pWidget->setColumnCount(6);
    m_pWidget->header()->resizeSection(1, 150);
    m_pWidget->header()->resizeSection(2, 160);
    m_pWidget->header()->resizeSection(3, 220);
    m_pWidget->header()->resizeSection(4, 150);
    m_pWidget->setHeaderLabels(QStringList() << tr("Number") << tr("Type") << tr("Time") << tr("Source") << tr("Object") << tr("Message"));

    auto *layout = new QVBoxLayout(this);
    layout->addWidget(m_pWidget);

    setLayout(layout);
}

void CWidgetProtocolTab_message::add(const CMessage &message_)
{
    bool first = true;
    QTreeWidgetItem *root;
    for(const auto& i : message_.text())
    {
        if(first)
        {
            first = false;
            root = new QTreeWidgetItem(m_pWidget);
            set_type(root, message_.level());
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
    m_pWidget->sortByColumn(0, Qt::DescendingOrder);
}

void CWidgetProtocolTab_message::exec(const CCmd &)
{
}

void CWidgetProtocolTab_message::set_type(QTreeWidgetItem *item_, CMessage::eMsgLevel type_)
{
    switch(type_)
    {
    case CMessage::eML_Info:
        item_->setIcon(1, qApp->style()->standardIcon(QStyle::SP_MessageBoxInformation));
        item_->setText(1, tr("Info"));
        break;
    case CMessage::eML_Warning:
        item_->setIcon(1, qApp->style()->standardIcon(QStyle::SP_MessageBoxWarning));
        item_->setText(1, tr("Warning"));
        break;
    case CMessage::eML_Critical:
        item_->setIcon(1, qApp->style()->standardIcon(QStyle::SP_MessageBoxCritical));
        item_->setText(1, tr("Critical"));
        break;
    default:
        item_->setIcon(1, qApp->style()->standardIcon(QStyle::SP_MessageBoxInformation));
        item_->setText(1, tr("Info"));
        break;
    }
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** CWidgetProtocolTab_build ***
//
CWidgetProtocolTab_build::CWidgetProtocolTab_build(QWidget *parent_) : IWidgetProtocolTab(parent_)
{
    auto container = new QWidget(this);
    m_pPlainTextWidget = new QPlainTextEdit(this);
    m_pPlainTextWidget->setReadOnly(true);
    m_pTreeWidget = new QTreeWidget(this);
    m_pTreeWidget->setColumnCount(4);
    m_pTreeWidget->header()->resizeSection(0, 900);
    m_pTreeWidget->header()->resizeSection(1, 100);
    m_pTreeWidget->header()->resizeSection(2, 100);
    m_pTreeWidget->header()->resizeSection(3, 200);
    m_pTreeWidget->setHeaderLabels(QStringList() << tr("Message") << tr("Project") << tr("Object") << tr("Position"));
    m_pTreeWidget->setWordWrap(true);
    m_pTreeWidget->hide();
    auto hb = new QHBoxLayout;
    hb->addWidget(m_pPlainTextWidget);
    hb->addWidget(m_pTreeWidget);
    container->setLayout(hb);

    auto toolbar = new QToolBar;
    toolbar->setOrientation(Qt::Vertical);
    auto group = new QActionGroup(toolbar);
    auto action = toolbar->addAction(QIcon(":/icon/images/text_3.svg"), tr("Text"));
    connect(action, &QAction::triggered, this, &CWidgetProtocolTab_build::slot_textViewToggled);
    action->setCheckable(true); group->addAction(action);
    action->setChecked(true);
    action = toolbar->addAction(QIcon(":/icon/images/diagram.svg"), tr("Tree"));
    connect(action, &QAction::triggered, this, &CWidgetProtocolTab_build::slot_treeViewToggled);
    action->setCheckable(true); group->addAction(action);
    toolbar->setIconSize(QSize(16, 16));

    auto * layout = new QHBoxLayout(this);
    layout->addWidget(container);
    layout->addWidget(toolbar);

    setLayout(layout);
}

void CWidgetProtocolTab_build::slot_textViewToggled(bool)
{
    m_pTreeWidget->hide();
    m_pPlainTextWidget->show();
}

void CWidgetProtocolTab_build::slot_treeViewToggled(bool)
{
    m_pPlainTextWidget->hide();
    m_pTreeWidget->show();
}

void CWidgetProtocolTab_build::add(const CMessage &message_)
{
    for(const auto & i : message_.text())
    {
        m_pPlainTextWidget->appendPlainText(i);

        QString err = "error: ";
        if(i.indexOf(err) != -1)
        {
            auto k = i.indexOf(':');
            QString pos = i.mid(k+1, i.indexOf(':', k+1)-(k+1));
            auto tmp1 = pos.split("..");
            auto tmp2 = tmp1.at(0).split("-");
            auto tmp3 = tmp1.at(1).split("-");
            QString row = tmp2.at(0);
            if(tmp2.at(0) != tmp3.at(0))
                row += QString("-%1").arg(tmp3.at(0));
            QString column = tmp2.at(1);
            if(tmp2.at(1) != tmp3.at(1))
                column += QString("-%1").arg(tmp3.at(1));
            pos = QString(tr("Row %1, Column %2")).arg(row, column);
            QString message = i.right(i.size() - i.indexOf(err) - err.size());
            QString type = "error";
            auto file = QFileInfo(i.left(k));

            auto item = new QTreeWidgetItem(m_pTreeWidget);
            set_type(item, type);
            item->setText(0, message);
            item->setText(2, file.fileName());
            item->setText(3, pos);
            auto child = new QTreeWidgetItem(item, QStringList(i));
            child->setToolTip(0, i);
        }
    }
}

void CWidgetProtocolTab_build::set_type(QTreeWidgetItem *item_, const QString &type_)
{
    if(type_ == "error")
    {
        item_->setIcon(0, qApp->style()->standardIcon(QStyle::SP_MessageBoxCritical));
    }
}

void CWidgetProtocolTab_build::exec(const CCmd &cmd_)
{
    if(cmd_.cmd() == CCmd::eCT_Clear)
    {
        m_pPlainTextWidget->clear();
        m_pTreeWidget->clear();
    }
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** CWidgetProtocol ***
//

CWidgetProtocol * CWidgetProtocol::m_pInstance = nullptr;

CWidgetProtocol::CWidgetProtocol(QWidget *parent) :
    QTabWidget{parent}
{
    m_pWidgetMessage = new CWidgetProtocolTab_message(this);
    addTab(m_pWidgetMessage, tr("Messages"));

    m_pWidgetBuild = new CWidgetProtocolTab_build(this);
    addTab(m_pWidgetBuild, tr("Build"));

    m_pWidgetAction = new QUndoView(this);
    // m_pActionUndoView->setStack(CWidgetProject::instance()->undoStack());
    addTab(m_pWidgetAction, tr("Actions"));

    setMinimumHeight(200);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    setTabPosition(QTabWidget::South);

    connect(CMessanger::instance(), SIGNAL(signal_send_msg(CMessage)), this, SLOT(slot_add_msg(CMessage)));
    connect(CMessanger::instance(), SIGNAL(signal_send_cmd(CCmd)), this, SLOT(slot_exec_cmd(CCmd)));
}

CWidgetProtocol::~CWidgetProtocol()
{
}

CWidgetProtocol * CWidgetProtocol::instance()
{
    if(!m_pInstance)
        m_pInstance = new CWidgetProtocol;

    return  m_pInstance;
}

void CWidgetProtocol::slot_add_msg(const CMessage &message_)
{
    switch(message_.type())
    {
    case CMessage::eMT_Message:
        m_pWidgetMessage->add(message_);
        break;
    case CMessage::eMT_Build:
        m_pWidgetBuild->add(message_);
        break;
    default:
        m_pWidgetMessage->add(message_);
        break;
    }
}

void CWidgetProtocol::slot_exec_cmd(const CCmd &cmd_)
{
    if(cmd_.cmd() == CCmd::eCT_Show)
    {
        exec(cmd_);
        return;
    }

    switch(cmd_.type())
    {
    case CMessage::eMT_Message:
        m_pWidgetMessage->exec(cmd_);
        break;
    case CMessage::eMT_Build:
        m_pWidgetBuild->exec(cmd_);
        break;
    default:
        m_pWidgetBuild->exec(cmd_);
        break;
    }
}

void CWidgetProtocol::exec(const CCmd &cmd_)
{
    switch(cmd_.type())
    {
    case CMessage::eMT_Message:
        setCurrentWidget(m_pWidgetMessage);
        break;
    case CMessage::eMT_Action:
        setCurrentWidget(m_pWidgetAction);
        break;
    case CMessage::eMT_Build:
        setCurrentWidget(m_pWidgetBuild);
        break;
    default:
        setCurrentWidget(m_pWidgetMessage);
        break;
    }
}

// ----------------------------------------------------------------------------
