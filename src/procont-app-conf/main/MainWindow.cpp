#include "MainWindow.h"

#include "item/DomItem.h"
#include "model/DomModel.h"
#include "model/ProxyModel.h"
#include "widget/TabWidgetEditor.h"
#include "widget/TabWidgetProtocol.h"
#include "log/Logger.h"
#include "iec/StandardLibrary.h"
#include "view/TreeView.h"
#include "dialog/InputDialog.h"
#include "dialog/AddPOUDialog.h"
#include "dialog/AddDUTDialog.h"
#include "generate/Translator.h"
#include "generate/Compiler.h"
#include "editor/fbd/general/ctreeobject.h"

#include <QDockWidget>
#include <QTreeView>
#include <QTableView>
#include <QPlainTextEdit>
#include <QMenuBar>
#include <QFileDialog>
#include <QToolBar>
#include <QToolButton>
#include <QApplication>
#include <QMessageBox>

#include <QDebug>

MainWindow * MainWindow::_m_instance = nullptr;
QString MainWindow::_m_config_filepath = QString();
QString MainWindow::_m_base_directory = QString();

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    proxy_pou(new ProxyModelTree_pou),
    proxy_dev(new ProxyModelTree_dev)
{
    setMinimumSize(QSize(1440, 900));

    setWindowIcon(QIcon(":/icon/images/pro.svg"));

    createWidgets();

    createMenu();

    createDynamicActions();

    StandardLibrary::instance()->load(/*m_baseDir*/);
    // StandardLibrary::instance()->test();

    open(/*QString("%1/plc-e.xml").arg(m_projDir)*/);

    if(!QFileInfo::exists(_m_base_directory))
        _m_base_directory = QFileInfo(QDir::currentPath()).absolutePath();
    m_projDir = QString("%1/proj").arg(_m_base_directory);

    if(!QFileInfo::exists(_m_config_filepath))
        _m_config_filepath = QString("%1/etc/procont.ini").arg(_m_base_directory);

    _m_settings = new QSettings(_m_config_filepath, QSettings::IniFormat);
}

void MainWindow::setConfig(const QString &filepath_)
{
    _m_config_filepath = filepath_;
}

void MainWindow::setDirectory(const QString &dirpath_)
{
    _m_base_directory = dirpath_;
}

MainWindow * MainWindow::instance()
{
    if(_m_instance == nullptr)
        _m_instance = new MainWindow;

    return _m_instance;
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

    viewPou = new TreeView();
    viewPou->setExpandsOnDoubleClick(false);
    viewPou->setMinimumSize(250, 400);
    viewPou->setHeaderHidden(true);
    viewPou->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(viewPou, &QTreeView::customContextMenuRequested, this, &MainWindow::slot_pouCustomContextMenu);
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
    _m_toolWidget = new CTreeObject(this);
    _m_toolWidget->setMinimumSize(200, 500);
    pDock = new QDockWidget(tr("ToolBar"), this);
    pDock->setTitleBarWidget(new QWidget());
    pDock->setAllowedAreas(Qt::RightDockWidgetArea);
    pDock->setWidget(_m_toolWidget);
    addDockWidget(Qt::RightDockWidgetArea, pDock);

    // bottom area
    pDock = new QDockWidget(tr("Protocol"), this);
    pDock->setTitleBarWidget(new QWidget());
    pDock->setAllowedAreas(Qt::BottomDockWidgetArea);
    pDock->setWidget(CWidgetProtocol::instance());
    addDockWidget(Qt::BottomDockWidgetArea, pDock);
}

CTreeObject * MainWindow::toolWidget() const
{
    return _m_toolWidget;
}

void MainWindow::createMenu()
{
    auto fileMenu = menuBar()->addMenu(tr("File"));
    auto file_open_act = fileMenu->addAction(QIcon(":/icon/images/open.svg"), tr("Open..."), QKeySequence::Open, this, &MainWindow::slot_open);
    auto file_save_act = fileMenu->addAction(QIcon(":/icon/images/save.svg"), tr("Save..."), QKeySequence::Save, this, &MainWindow::slot_save);
    fileMenu->addAction(tr("Exit"), QKeySequence::Quit, this, &QWidget::close);

    auto editMenu = menuBar()->addMenu(tr("Edit"));
    auto edit_undo_act = editMenu->addAction(QIcon(":/icon/images/undo1.svg"), tr("Undo"), QKeySequence::Undo, this, &MainWindow::slot_undo);
    edit_undo_act->setEnabled(false);
    auto edit_redo_act = editMenu->addAction(QIcon(":/icon/images/redo1.svg"), tr("Redo"), QKeySequence::Redo, this, &MainWindow::slot_redo);
    edit_redo_act->setEnabled(false);
    editMenu->addSeparator();
    auto edit_cut_act = editMenu->addAction(QIcon(":/icon/images/cut.svg"), tr("Cut"), QKeySequence::Cut, this, &MainWindow::slot_cut);
    edit_cut_act->setEnabled(false);
    auto edit_copy_act = editMenu->addAction(QIcon(":/icon/images/copy.svg"), tr("Copy"), QKeySequence::Copy, this, &MainWindow::slot_copy);
    edit_copy_act->setEnabled(false);
    auto edit_paste_act = editMenu->addAction(QIcon(":/icon/images/paste.svg"), tr("Paste"), QKeySequence::Paste, this, &MainWindow::slot_paste);
    edit_paste_act->setEnabled(false);
    auto edit_delete_act = editMenu->addAction(QIcon(":/icon/images/delete2.svg"), tr("Delete"), QKeySequence::Delete, this, &MainWindow::slot_delete);
    editMenu->addSeparator();
    auto edit_input_assistant_act = editMenu->addAction(QIcon(":/icon/images/hierarchy.svg"), tr("Input assistant..."), QKeySequence(tr("F2")), this, &MainWindow::slot_input_assistant);

    auto viewMenu = menuBar()->addMenu(tr("View"));

    auto projectMenu = menuBar()->addMenu(tr("Project"));
    _m_addObjectMenu = new QMenu(tr("Add object"));
    projectMenu->addMenu(_m_addObjectMenu);

    auto compileMenu = menuBar()->addMenu(tr("Compile"));
    auto compile_compile_act = compileMenu->addAction(tr("Compile"), this, &MainWindow::slot_compile);
    auto compile_build_act = compileMenu->addAction(QIcon(":/icon/images/hammer2.svg"), tr("Build"), QKeySequence(tr("Ctrl+Shift+B")), this, &MainWindow::slot_build);

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
    _m_button = new QToolButton();
    toolbar->addWidget(_m_button);
    _m_button->setIcon(QIcon(":/icon/images/plus-large.svg"));
    _m_button->setPopupMode(QToolButton::InstantPopup);
    toolbar->addSeparator();
    toolbar->addAction(compile_build_act);
    toolbar->setIconSize(QSize(24, 24));
}

void MainWindow::createDynamicActions()
{
    // Type
    auto act = new QAction(QIcon(":/icon/images/hierarchy-3.svg"), tr("DUT"));
    connect(act, &QAction::triggered, this, &MainWindow::slot_addDUT);
    _m_dynamicActions.insert("project", act);
    _m_dynamicActions.insert("dataTypes", act);

    // POU
    act = new QAction(QIcon(":/icon/images/document.svg"), tr("POU"));
    connect(act, &QAction::triggered, this, &MainWindow::slot_addPOU);
    _m_dynamicActions.insert("project", act);
    _m_dynamicActions.insert("pous", act);
}

void MainWindow::slot_pouCustomContextMenu(const QPoint &pos_)
{
    QModelIndex index = viewPou->indexAt(pos_);
    if(index.isValid())
    {
        QDomNode node = item(index)->node();
        QList<QAction *> acts = _m_dynamicActions.values(node.nodeName());
        if(acts.size())
        {
            auto menu = new QMenu;
            for(auto i : std::as_const(acts))
                menu->addAction(i);
            menu->exec(viewPou->viewport()->mapToGlobal(pos_));
        }
    }
}

void MainWindow::slot_pouCurrentChanged(const QModelIndex &current, const QModelIndex &)
{
    _m_addObjectMenu->clear();
    if(current.isValid())
    {
        QDomNode node = item(current)->node();
        QList<QAction *> acts = _m_dynamicActions.values(node.nodeName());
        if(acts.size())
        {
            for(auto i : std::as_const(acts))
                _m_addObjectMenu->addAction(i);
        }
    }
    _m_button->setMenu(_m_addObjectMenu);
}

QModelIndex MainWindow::s_index(const QModelIndex &index, QAbstractItemModel * proxy)
{
    if(proxy == nullptr)
        return reinterpret_cast<const QAbstractProxyModel*>(index.model())->mapToSource(index);

    return reinterpret_cast<const QAbstractProxyModel*>(proxy)->mapToSource(index);
}

QModelIndex MainWindow::p_index(const QModelIndex &index, QAbstractItemModel * proxy)
{
    return reinterpret_cast<const QAbstractProxyModel*>(proxy)->mapFromSource(index);
}

QAbstractProxyModel * MainWindow::proxy(QAbstractItemModel *model)
{
    return reinterpret_cast<QAbstractProxyModel*>(model);
}

DomItem * MainWindow::item(const QModelIndex &index, QAbstractItemModel * proxy)
{
    return reinterpret_cast<DomItem *>(s_index(index, proxy).internalPointer());
}

void MainWindow::slot_addDUT()
{
    AddDUTDialog dlg;
    if(dlg.exec() == QDialog::Accepted)
    {
        auto model = reinterpret_cast<QAbstractProxyModel*>(viewPou->model());
        auto indexes = model->sourceModel()->match(model->sourceModel()->index(0, 0), Qt::DecorationRole, "dataTypes", -1, Qt::MatchRecursive);
        auto parentIndex = indexes.at(0);
        auto parentItem = reinterpret_cast<DomItem *>(parentIndex.internalPointer());

        parentItem->addNode(dlg.getNode().toDocument().documentElement());
        model->sourceModel()->insertRow(parentItem->rowCount(), parentIndex);
    }
}

void MainWindow::slot_addPOU()
{
    AddPOUDialog dlg;
    if(dlg.exec() == QDialog::Accepted)
    {
        auto model = reinterpret_cast<QAbstractProxyModel*>(viewPou->model());
        auto indexes = model->sourceModel()->match(model->sourceModel()->index(0, 0), Qt::DecorationRole, "pous", -1, Qt::MatchRecursive);
        auto parentIndex = indexes.at(0);
        auto parentItem = reinterpret_cast<DomItem *>(parentIndex.internalPointer());

        parentItem->addNode(dlg.getNode().toDocument().documentElement());
        model->sourceModel()->insertRow(parentItem->rowCount(), parentIndex);
    }
}

void MainWindow::slot_open()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"), QString{}, tr("XML files (*.xml)"));
    if(filePath.isEmpty())
        return;

    m_projDir = QFileInfo(filePath).absoluteDir().absolutePath();

    open(filePath);
}

void MainWindow::open(const QString & filePath)
{
    TabWidgetEditor::instance()->closeTabs();
    TabWidgetEditor::instance()->addIntro();

    auto default_file = false;
    QString _filePath = filePath;
    QString _fileName = QFileInfo(_filePath.right(_filePath.size()-1)).fileName();

    if(_filePath.isEmpty())
        default_file = true;
    else
        info(
            QStringList()
            << QString(tr("open project %1")).arg(_fileName)
            << QString(tr("project file: %1")).arg(_filePath)
            );

    if(!default_file && !QFileInfo::exists(_filePath))
    {
        warn(
            QStringList()
            << QString(tr("can't open project %1")).arg(_fileName)
            << QString(tr("file not found: %1").arg(_filePath))
            );

        default_file = true;
    }

    if(default_file)
    {
        _filePath = ":/proj/proj/plc-e.xml";
        _fileName = QFileInfo(_filePath.right(_filePath.size()-1)).fileName();
        info(
            QStringList()
            << QString(tr("open project %1")).arg(_fileName)
            << QString(tr("project file: %1")).arg(_filePath)
            );
    }


    QFile file(_filePath);
    if(!file.open(QIODevice::ReadOnly))
    {
        crit(
            QStringList()
            << QString(tr("can't open project %1")).arg(_fileName)
            << QString(tr("can't open file for read: %1").arg(_filePath))
            );

        return;
    }
    QDomDocument document;
    auto result = _m_project_document.setContent(&file);
    file.close();

    if(!result)
    {
        warn(
            QStringList()
            << QString(tr("can't open project %1")).arg(_fileName)
            << QString(tr("file parse error: %1").arg(_filePath))
            );

        return;
    }

    if(result)
    {
        auto newModel = new DomModel(_m_project_document, this);

        StandardLibrary::instance()->add("User objects", &_m_project_document, tr("User objects"));

        view->setModel(newModel);

        proxy_pou->setSourceModel(newModel);
        viewPou->setModel(proxy_pou);
        connect(viewPou, &QTreeView::doubleClicked, TabWidgetEditor::instance(), &TabWidgetEditor::slot_addTabWidget);
        connect(viewPou->selectionModel(), &QItemSelectionModel::currentChanged, this, &MainWindow::slot_pouCurrentChanged);

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

    info(
        QStringList()
        << QString(tr("project opened %1")).arg(_fileName)
        << QString(tr("project file: %1")).arg(_filePath)
        );
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
    while(toolWidget()->topLevelItemCount())
        delete toolWidget()->topLevelItem(0);

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
    static QStringList listViewExclude; listViewExclude << "project" << "dataTypes" << "pous";
    // pou tree
    if(QApplication::focusWidget() == viewPou)
    {
        for(auto index : viewPou->selectionModel()->selectedRows())
        {
            if(listViewExclude.contains(item(index)->node().nodeName()))
                continue;

            QString _type = {};
            if(item(index)->parentItem()->node().nodeName() == "pous")
                _type = "POU";
            if(item(index)->parentItem()->node().nodeName() == "dataTypes")
                _type = "DUT";

            auto _name = item(index)->node().toElement().attribute("name");
            if
                (
                    QMessageBox::Yes ==
                    QMessageBox::question
                    (
                        this,
                        tr("Attention"),
                        QString(tr("Do you really want to delete %1 '%2'")).arg(_type, _name)
                        )
                    )
            {
                TabWidgetEditor::instance()->closeTab(index);
                item(index)->parentItem()->removeChild(s_index(index).row(), 0, item(index)->node());
                proxy(viewPou->model())->sourceModel()->
                    removeRow(s_index(index).row(), s_index(index.parent()));
            }
        }
    }
}

void MainWindow::slot_input_assistant()
{
    InputDialog dlg;
    dlg.exec();
}

void MainWindow::slot_compile()
{
}

void MainWindow::slot_build()
{    
    b_command(CCmd::eCT_Show);

    // *** подготовка ST-файла
    // создание папки для сборки
    auto _buildDir = QString("%1/build").arg(_m_base_directory);
    QDir(_buildDir).removeRecursively();
    QDir(_m_base_directory).mkdir(_buildDir);

    // формирование ST-файла
    QString st_text = Translator::translate(model->document());
    // отображение ST-файла
    b_text(st_text);

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
                _m_settings->value("Compiler/matiec_path").toString()
            );
    _m_compiler->compile();
    // ***
}

