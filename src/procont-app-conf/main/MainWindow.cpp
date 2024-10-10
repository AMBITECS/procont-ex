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
#include <QToolBar>

#include <QDebug>

#define this_pointer this

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    proxy_pou(new ProxyModelTree_pou),
    proxy_dev(new ProxyModelTree_dev)
{
    setMinimumSize(QSize(1440, 900));

    setWindowIcon(QIcon(":/icon/images/pro.svg"));

    createWidgets();

    createMenu();

    open("plc-e.xml");
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
    pDock->setWidget(CWidgetProtocol::instance());
    addDockWidget(Qt::BottomDockWidgetArea, pDock);

    m_projectDir = QDir::currentPath();
}

void MainWindow::createMenu()
{
    auto fileMenu = menuBar()->addMenu(tr("&File"));
    auto file_open_act = fileMenu->addAction(QIcon(":/icon/images/open.svg"), tr("&Open..."), QKeySequence::Open, this, &MainWindow::slot_open);
    auto file_save_act = fileMenu->addAction(QIcon(":/icon/images/save.svg"), tr("&Save..."), QKeySequence::Save, this, &MainWindow::slot_save);
    fileMenu->addAction(tr("&Exit"), QKeySequence::Quit, this, &QWidget::close);

    auto editMenu = menuBar()->addMenu(tr("&Edit"));
    auto edit_undo_act = editMenu->addAction(QIcon(":/icon/images/undo1.svg"), tr("Undo"), QKeySequence::Undo, this, &MainWindow::slot_undo);
    auto edit_redo_act = editMenu->addAction(QIcon(":/icon/images/redo1.svg"), tr("Redo"), QKeySequence::Redo, this, &MainWindow::slot_redo);
    editMenu->addSeparator();
    auto edit_cut_act = editMenu->addAction(QIcon(":/icon/images/cut.svg"), tr("Cut"), QKeySequence::Cut, this, &MainWindow::slot_cut);
    auto edit_copy_act = editMenu->addAction(QIcon(":/icon/images/copy.svg"), tr("Copy"), QKeySequence::Copy, this, &MainWindow::slot_copy);
    auto edit_paste_act = editMenu->addAction(QIcon(":/icon/images/paste.svg"), tr("Paste"), QKeySequence::Paste, this, &MainWindow::slot_paste);
    auto edit_delete_act = editMenu->addAction(QIcon(":/icon/images/delete2.svg"), tr("Delete"), QKeySequence::Delete, this, &MainWindow::slot_delete);

    auto viewMenu = menuBar()->addMenu(tr("&View"));

    auto projectMenu = menuBar()->addMenu(tr("&Project"));

    auto compileMenu = menuBar()->addMenu(tr("&Compile"));
    auto compile_compile_act = compileMenu->addAction(tr("Compile"), QKeySequence(tr("Ctrl+B")), this, &MainWindow::slot_compile);
    auto compile_build_act = compileMenu->addAction(QIcon(":/icon/images/hammer2.svg"), tr("Build"), QKeySequence(tr("F11")), this, &MainWindow::slot_build);

    auto toolbar = addToolBar("main");
    toolbar->addAction(file_open_act);
    toolbar->addAction(file_save_act);
    toolbar->addSeparator();
    toolbar->addAction(edit_undo_act);
    toolbar->addAction(edit_redo_act);
    toolbar->addSeparator();
    toolbar->addAction(edit_cut_act);
    toolbar->addAction(edit_copy_act);
    toolbar->addAction(edit_paste_act);
    toolbar->addAction(edit_delete_act);
    toolbar->addSeparator();
    toolbar->addAction(compile_build_act);
    toolbar->setIconSize(QSize(24, 24));
}

void MainWindow::slot_open()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"), QString{}, tr("XML files (*.xml)"));
    if(filePath.isEmpty())
        return;

   m_projectDir = QFileInfo(filePath).absoluteDir().absolutePath();

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

void MainWindow::slot_undo()
{
}

void MainWindow::slot_redo()
{
}

void MainWindow::slot_cut()
{
}

void MainWindow::slot_copy()
{
}

void MainWindow::slot_paste()
{
}

void MainWindow::slot_delete()
{
}

void MainWindow::slot_compile()
{
}

#include "generate/Translator.h"
#include "generate/Compiler.h"

void MainWindow::slot_build()
{
    b_command(CCmd::eCT_Show);

    // *** подготовка ST-файла
    // создание папки для сборки
    auto _buildDir = QString("%1/build").arg(m_projectDir);
    QDir(_buildDir).removeRecursively();
    QDir(m_projectDir).mkdir(_buildDir);

    // формирование ST-файла
    QString st_text = Translator::translate(model->document());

    // запись файла
    QFile file(QString("%1/generated.st").arg(_buildDir));
    file.open(QIODevice::WriteOnly);
    file.write(st_text.toLocal8Bit());
    file.close();
    // ***

    // *** трансляция ST->C
    if(_m_compiler == nullptr)
        _m_compiler = new Compiler_matiec
            (
                "generated.st",
                _buildDir,
                "/home/ambitecs/proj/procont/matiec"
            );
    _m_compiler->compile();
    // ***
}

#undef this_pointer

