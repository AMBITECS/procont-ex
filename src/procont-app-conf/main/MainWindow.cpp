#include "MainWindow.h"

#include "item/DomItem.h"
#include "model/DomModel.h"
#include "model/ProxyModel.h"
#include "widget/TabWidgetEditor.h"
#include "widget/TabWidgetProtocol.h"
#include "log/Logger.h"

#include <QDockWidget>
#include <QTreeView>
#include <QTableView>
#include <QPlainTextEdit>
#include <QMenuBar>
#include <QFileDialog>
#include <QSplitter>
#include <QToolBar>

#include <QDebug>

#define this_pointer this

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    proxy_pou(new ProxyModelTree_pou),
    proxy_dev(new ProxyModelTree_dev)
{
    setMinimumSize(QSize(1440, 900));

    createWidgets();

    createMenu();

    open("plc-0.xml");
}

void MainWindow::createWidgets()
{
    // central
    setCentralWidget(TabWidgetEditor::instance());
    connect(TabWidgetEditor::instance(), &TabWidgetEditor::signal_currentTabChanged, this, &MainWindow::slot_currentViewChanged);

    // left area
    viewDev = new QTreeView();
    viewDev->setExpandsOnDoubleClick(false);
    viewDev->setHeaderHidden(true);
    viewDev->setMinimumSize(250, 400);
    dockDev = new QDockWidget(tr("Device"), this);
    dockDev->setTitleBarWidget(new QWidget());
    dockDev->setAllowedAreas(Qt::LeftDockWidgetArea);
    dockDev->setWidget(viewDev);
    addDockWidget(Qt::LeftDockWidgetArea, dockDev);

    viewPou = new QTreeView();
    viewPou->setExpandsOnDoubleClick(false);
    viewPou->setMinimumSize(250, 400);
    viewPou->setHeaderHidden(true);
    dockPou = new QDockWidget(tr("POUs"), this);
    dockPou->setTitleBarWidget(new QWidget());
    dockPou->setAllowedAreas(Qt::LeftDockWidgetArea);
    dockPou->setWidget(viewPou);
    addDockWidget(Qt::LeftDockWidgetArea, dockPou);

    view = new QTreeView();
    view->setMinimumSize(250, 400);
    view->setHeaderHidden(true);
    auto pDock = new QDockWidget(tr("Model"), this);
    pDock->setTitleBarWidget(new QWidget());
    pDock->setAllowedAreas(Qt::LeftDockWidgetArea);
    pDock->setWidget(view);
    addDockWidget(Qt::LeftDockWidgetArea, pDock);

    tabifyDockWidget(pDock, dockDev);
    tabifyDockWidget(dockDev, dockPou);

    // right area
    // auto prpWgt = new QTreeWidget();
    // prpWgt->setMinimumSize(200, 500);
    // auto prpWgt_dw = new ads::CDockWidget("Properties");
    // prpWgt_dw->setWidget(prpWgt);
    // prpWgt_dw->setMinimumSizeHintMode(ads::CDockWidget::MinimumSizeHintFromContentMinimumSize);
    // manager->addDockWidgetTab(ads::RightDockWidgetArea, prpWgt_dw);

    // bottom area
    pDock = new QDockWidget(tr("Protocol"), this);
    pDock->setTitleBarWidget(new QWidget());
    pDock->setAllowedAreas(Qt::BottomDockWidgetArea);
    pDock->setWidget(CWidgetMessage::instance());
    addDockWidget(Qt::BottomDockWidgetArea, pDock);
}

void MainWindow::createMenu()
{
    auto fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(tr("&Open..."), QKeySequence::Open, this, &MainWindow::slot_open);
    fileMenu->addAction(tr("&Save..."), QKeySequence::Save, this, &MainWindow::slot_save);
    fileMenu->addAction(tr("&Exit"), QKeySequence::Quit, this, &QWidget::close);
}

void MainWindow::slot_open()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"), QString{}, tr("XML files (*.xml)"));
    if(filePath.isEmpty())
        return;

    open(filePath);
}

void MainWindow::open(const QString & filePath)
{
    TabWidgetEditor::instance()->closeTabs();

    info(QString(tr("open file %1")).arg(filePath));

    if (!filePath.isEmpty())
    {
        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly))
        {
            QDomDocument document;
            if (document.setContent(&file))
            {
                auto newModel = new DomModel(document, this);

                view->setModel(newModel);

                proxy_pou->setSourceModel(newModel);
                viewPou->setModel(proxy_pou);
                connect(viewPou, &QTreeView::doubleClicked, TabWidgetEditor::instance(), &TabWidgetEditor::slot_addTabWidget);

                proxy_dev->setSourceModel(newModel);
                viewDev->setModel(proxy_dev);
                connect(viewDev, &QTreeView::doubleClicked, TabWidgetEditor::instance(), &TabWidgetEditor::slot_addTabWidget);

                TabWidgetEditor::setModel(newModel);

                delete model; model = newModel;
                viewPou->expandAll();
                viewDev->expandAll();
                for (int i = 0; i < proxy_pou->columnCount(); ++i)
                    viewPou->resizeColumnToContents(i);
                for (int i = 0; i < proxy_dev->columnCount(); ++i)
                    viewDev->resizeColumnToContents(i);
            }
            file.close();
        }
    }
}

void MainWindow::slot_save()
{
    QString filePath = QFileDialog::getSaveFileName(this, tr("Save File"), QString{}, tr("XML files (*.xml)"));

    save(filePath);
}

void MainWindow::save(const QString & filePath)
{
    if (!filePath.isEmpty())
    {
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly))
        {
            file.write(model->document().toByteArray());
            file.close();
        }
    }
}

void MainWindow::slot_currentViewChanged(const QModelIndex &index)
{
    if(!index.isValid())
        return;

    if(index.model() == proxy_pou)
    {
        viewPou->setCurrentIndex(index);
        dockPou->raise();
        return;
    }

    if(index.model() == proxy_dev)
    {
        viewDev->setCurrentIndex(index);
        dockDev->raise();
        return;
    }
}

#undef this_pointer

