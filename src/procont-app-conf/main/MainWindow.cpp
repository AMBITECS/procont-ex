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
#include "dialog/RenameDialog.h"

#include "generate/Translator.h"
#include "generate/Compiler.h"

#include "editor/fbd/general/ctreeobject.h"

#include "undo/cundocommand_remove.h"
#include "undo/cundocommand_insert.h"

#include "tr/translation.h"

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
#include <QUndoStack>

#include <QDebug>

MainWindow * MainWindow::_m_instance = nullptr;
QString MainWindow::_m_config_filepath = QString();
QString MainWindow::_m_base_directory = QString();

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _m_proxy_pou(new ProxyModelTree_pou),
    _m_proxy_dev(new ProxyModelTree_dev),
    _m_undo_stack(new QUndoStack)
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
    _m_proj_dir = QString("%1/proj").arg(_m_base_directory);

    if(!QFileInfo::exists(_m_config_filepath))
        _m_config_filepath = QString("%1/etc/procont.ini").arg(_m_base_directory);

    _m_settings = new QSettings(_m_config_filepath, QSettings::IniFormat);

    if(!QFileInfo::exists(_m_config_filepath))
    {
        QString etc_dir_ = QString("%1/etc").arg(_m_base_directory);
        if(!QFileInfo::exists(etc_dir_))
            QDir(_m_base_directory).mkdir(etc_dir_);
        _m_settings->setValue("Compiler/matiec_path", QString("%1/matiec").arg(_m_base_directory));
    }
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

QUndoStack * MainWindow::undoStack() const
{
    return _m_undo_stack;
}

void MainWindow::createWidgets()
{
    // central
    setCentralWidget(TabWidgetEditor::instance());
    connect(TabWidgetEditor::instance(), &TabWidgetEditor::signal_currentTabChanged, this, &MainWindow::slot_currentViewChanged);

    // left area
    _m_tree_dev = new QTreeView();
    _m_tree_dev->setExpandsOnDoubleClick(false);
    _m_tree_dev->setMinimumSize(250, 400);
    _m_tree_dev->setHeaderHidden(true);
    _m_tree_dev->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(_m_tree_dev, &QTreeView::customContextMenuRequested, this, &MainWindow::slot_devCustomContextMenu);
    dockDev = new QDockWidget(tr("Device"), this);
    dockDev->setTitleBarWidget(new QWidget());
    dockDev->setAllowedAreas(Qt::LeftDockWidgetArea);
    dockDev->setWidget(_m_tree_dev);
    addDockWidget(Qt::LeftDockWidgetArea, dockDev);

    _m_tree_pou = new TreeView();
    _m_tree_pou->setExpandsOnDoubleClick(false);
    _m_tree_pou->setMinimumSize(250, 400);
    _m_tree_pou->setHeaderHidden(true);
    _m_tree_pou->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(_m_tree_pou, &QTreeView::customContextMenuRequested, this, &MainWindow::slot_pouCustomContextMenu);
    dockPou = new QDockWidget(tr("POU"), this);
    dockPou->setTitleBarWidget(new QWidget());
    dockPou->setAllowedAreas(Qt::LeftDockWidgetArea);
    dockPou->setWidget(_m_tree_pou);
    addDockWidget(Qt::LeftDockWidgetArea, dockPou);

    // view = new QTreeView();
    // view->setMinimumSize(250, 400);
    // view->setHeaderHidden(true);
    // auto pDock = new QDockWidget(tr("Model"), this);
    // pDock->setTitleBarWidget(new QWidget());
    // pDock->setAllowedAreas(Qt::LeftDockWidgetArea);
    // pDock->setWidget(view);
    // addDockWidget(Qt::LeftDockWidgetArea, pDock);

    // tabifyDockWidget(pDock, dockDev);
    tabifyDockWidget(dockDev, dockPou);

    // right area
    _m_toolWidget = new CTreeObject;
    _m_toolWidget->setMinimumSize(200, 500);
    QStringList treeHeaderLabels; treeHeaderLabels << tr("Components");
    _m_toolWidget->setHeaderLabels(treeHeaderLabels);
    auto pDock = new QDockWidget(tr("ToolBar"), this);
    pDock->setTitleBarWidget(new QWidget());
    pDock->setAllowedAreas(Qt::RightDockWidgetArea);
    pDock->setWidget(_m_toolWidget);
    addDockWidget(Qt::RightDockWidgetArea, pDock);

    // bottom area
    _m_widget_protocol = new CWidgetProtocol(undoStack());
    _m_widget_protocol->setMinimumHeight(300);
    pDock = new QDockWidget(tr("Protocol"), this);
    pDock->setTitleBarWidget(new QWidget());
    pDock->setAllowedAreas(Qt::BottomDockWidgetArea);
    pDock->setWidget(_m_widget_protocol);
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
    auto edit_undo_act = undoStack()->createUndoAction(this);
    edit_undo_act->setText(tr("Undo"));
    edit_undo_act->setIcon(QIcon(":/icon/images/undo1.svg"));
    edit_undo_act->setShortcuts(QKeySequence::Undo);
    edit_undo_act->setStatusTip(tr("Undo action"));

    auto edit_redo_act = undoStack()->createRedoAction(this);
    edit_redo_act->setText(tr("Redo"));
    edit_redo_act->setIcon(QIcon(":/icon/images/redo1.svg"));
    edit_redo_act->setShortcuts(QKeySequence::Redo);
    edit_redo_act->setStatusTip(tr("Redo action"));

    //     editMenu->addAction(QIcon(":/icon/images/undo1.svg"), tr("Undo"), QKeySequence::Undo, this, &MainWindow::slot_undo);
    // edit_undo_act->setEnabled(false);

    //     auto edit_redo_act = editMenu->addAction(QIcon(":/icon/images/redo1.svg"), tr("Redo"), QKeySequence::Redo, this, &MainWindow::slot_redo);
    // edit_redo_act->setEnabled(false);

    editMenu->addSeparator();
    auto edit_cut_act = editMenu->addAction(QIcon(":/icon/images/cut.svg"), tr("Cut"), QKeySequence::Cut, this, &MainWindow::slot_cut);
    _m_dynamic_actions.insert("dataType", DynamicAction(edit_cut_act, {_m_tree_pou}));
    _m_dynamic_actions.insert("pou", DynamicAction(edit_cut_act, {_m_tree_pou}));
    _m_dynamic_actions.insert("configuration", DynamicAction(edit_cut_act, {_m_tree_dev}));
    _m_dynamic_actions.insert("resource", DynamicAction(edit_cut_act, {_m_tree_dev}));
    _m_dynamic_actions.insert("task", DynamicAction(edit_cut_act, {_m_tree_dev}));
    _m_dynamic_actions.insert("pouInstance", DynamicAction(edit_cut_act, {_m_tree_dev}));
    edit_cut_act->setEnabled(false);
    auto edit_copy_act = editMenu->addAction(QIcon(":/icon/images/copy.svg"), tr("Copy"), QKeySequence::Copy, this, &MainWindow::slot_copy);
    _m_dynamic_actions.insert("dataType", DynamicAction(edit_copy_act, {_m_tree_pou}));
    _m_dynamic_actions.insert("pou", DynamicAction(edit_copy_act, {_m_tree_pou}));
    _m_dynamic_actions.insert("configuration", DynamicAction(edit_copy_act, {_m_tree_dev}));
    _m_dynamic_actions.insert("resource", DynamicAction(edit_copy_act, {_m_tree_dev}));
    _m_dynamic_actions.insert("task", DynamicAction(edit_copy_act, {_m_tree_dev}));
    _m_dynamic_actions.insert("pouInstance", DynamicAction(edit_copy_act, {_m_tree_dev}));
    edit_copy_act->setEnabled(false);
    auto edit_paste_act = editMenu->addAction(QIcon(":/icon/images/paste.svg"), tr("Paste"), QKeySequence::Paste, this, &MainWindow::slot_paste);
    _m_dynamic_actions.insert("dataType", DynamicAction(edit_paste_act, {_m_tree_pou}));
    _m_dynamic_actions.insert("pou", DynamicAction(edit_paste_act, {_m_tree_pou}));
    _m_dynamic_actions.insert("configuration", DynamicAction(edit_paste_act, {_m_tree_dev}));
    _m_dynamic_actions.insert("resource", DynamicAction(edit_paste_act, {_m_tree_dev}));
    _m_dynamic_actions.insert("task", DynamicAction(edit_paste_act, {_m_tree_dev}));
    _m_dynamic_actions.insert("pouInstance", DynamicAction(edit_paste_act, {_m_tree_dev}));
    edit_paste_act->setEnabled(false);
    auto edit_delete_act = editMenu->addAction(QIcon(":/icon/images/delete2.svg"), tr("Delete"), QKeySequence::Delete, this, &MainWindow::slot_delete);
    _m_dynamic_actions.insert("dataType", DynamicAction(edit_delete_act, {_m_tree_pou}, true));
    _m_dynamic_actions.insert("pou", DynamicAction(edit_delete_act, {_m_tree_pou}, true));
    _m_dynamic_actions.insert("configuration", DynamicAction(edit_delete_act, {_m_tree_dev}, true));
    _m_dynamic_actions.insert("resource", DynamicAction(edit_delete_act, {_m_tree_dev}, true));
    _m_dynamic_actions.insert("task", DynamicAction(edit_delete_act, {_m_tree_dev}, true));
    _m_dynamic_actions.insert("pouInstance", DynamicAction(edit_delete_act, {_m_tree_dev}, true));
    editMenu->addSeparator();
    auto edit_input_assistant_act = editMenu->addAction(QIcon(":/icon/images/hierarchy.svg"), tr("Input assistant..."), QKeySequence(tr("F2")), this, &MainWindow::slot_input_assistant);

    auto viewMenu = menuBar()->addMenu(tr("View"));

    auto projectMenu = menuBar()->addMenu(tr("Project"));
    _m_addobject_menu = new QMenu(tr("Add object"));
    projectMenu->addMenu(_m_addobject_menu);

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
    toolbar->setIconSize(QSize(32, 32));
}

void MainWindow::createDynamicActions()
{
    // rename
    auto act = new QAction(QIcon(":/icon/images/rename.svg"), tr("Rename"));
    connect(act, &QAction::triggered, this, &MainWindow::slot_rename);
    _m_dynamic_actions.insert("dataType", DynamicAction(act, {_m_tree_pou}, true));
    _m_dynamic_actions.insert("pou", DynamicAction(act, {_m_tree_pou}, true));
    _m_dynamic_actions.insert("configuration", DynamicAction(act, {_m_tree_dev}, true));
    _m_dynamic_actions.insert("resource", DynamicAction(act, {_m_tree_dev}, true));
    _m_dynamic_actions.insert("task", DynamicAction(act, {_m_tree_dev}, true));
    _m_dynamic_actions.insert("pouInstance", DynamicAction(act, {_m_tree_dev}, true));

    // properties
    act = new QAction(QIcon(":/icon/images/config.svg"), tr("Properties"));
    connect(act, &QAction::triggered, this, &MainWindow::slot_properties);
    _m_dynamic_actions.insert("dataType", DynamicAction(act, {_m_tree_pou}, true));
    _m_dynamic_actions.insert("pou", DynamicAction(act, {_m_tree_pou}, true));
    _m_dynamic_actions.insert("configuration", DynamicAction(act, {_m_tree_dev}, true));
    _m_dynamic_actions.insert("resource", DynamicAction(act, {_m_tree_dev}, true));
    _m_dynamic_actions.insert("task", DynamicAction(act, {_m_tree_dev}, true));
    _m_dynamic_actions.insert("pouInstance", DynamicAction(act, {_m_tree_dev}, true));

    // add DUT
    act = new QAction(QIcon(":/icon/images/hierarchy-3.svg"), tr("DUT"));
    connect(act, &QAction::triggered, this, &MainWindow::slot_add_DUT);
    _m_dynamic_actions.insert("project", DynamicAction(act, {_m_tree_pou}, tr("Add object")));
    _m_dynamic_actions.insert("dataTypes", DynamicAction(act, {_m_tree_pou}, tr("Add object")));

    // add POU
    act = new QAction(QIcon(":/icon/images/document.svg"), tr("POU"));
    connect(act, &QAction::triggered, this, &MainWindow::slot_add_POU);
    _m_dynamic_actions.insert("project", DynamicAction(act, {_m_tree_pou}, tr("Add object")));
    _m_dynamic_actions.insert("pous", DynamicAction(act, {_m_tree_pou}, tr("Add object")));

    // add resource
    act = new QAction(tr("Resource"));
    connect(act, &QAction::triggered, this, &MainWindow::slot_add_resource);
    _m_dynamic_actions.insert("configuration", DynamicAction(act, {_m_tree_dev}, tr("Add object")));

    // add task
    act = new QAction(tr("Task"));
    connect(act, &QAction::triggered, this, &MainWindow::slot_add_task);
    _m_dynamic_actions.insert("resource", DynamicAction(act, {_m_tree_dev}, tr("Add object")));

    // add pouInstance
    act = new QAction(tr("POU instance"));
    connect(act, &QAction::triggered, this, &MainWindow::slot_add_instance);
    _m_dynamic_actions.insert("task", DynamicAction(act, {_m_tree_dev}, tr("Add object")));

    // add device
    act = new QAction(tr("Add device..."));
    connect(act, &QAction::triggered, this, &MainWindow::slot_add_device);
    _m_dynamic_actions.insert("project", DynamicAction(act, {_m_tree_dev}));
    _m_dynamic_actions.insert("configuration", DynamicAction(act, {_m_tree_dev}));
}

void MainWindow::createContextMenu(const QPoint &pos_, const QTreeView *tree_)
{
    QModelIndex index = tree_->indexAt(pos_);
    if(index.isValid())
    {
        QDomNode node = item(index)->node();
        QList<DynamicAction> acts = _m_dynamic_actions.values(node.nodeName());
        if(acts.size())
        {
            auto menu = new QMenu;
            QList<QMenu *> subs_;
            std::reverse(acts.begin(), acts.end());
            auto c = 0;
            for(const auto & i : std::as_const(acts))
            {
                if(!i._m_views.contains(tree_))
                    continue;

                if(i._m_menu.length())
                {
                    auto it =
                        std::find_if(subs_.begin(), subs_.end(), [&i](QMenu *menu){ return menu->title() == i._m_menu; });
                    if(it == subs_.end())
                    {
                        auto m = menu->addMenu(i._m_menu);
                        subs_.append(m);
                        m->addAction(i._m_act);
                    }
                    else
                        (*it)->addAction(i._m_act);
                }
                else
                    menu->addAction(i._m_act);

                if(i._m_separator && ++c < acts.size())
                    menu->addSeparator();
            }
            menu->exec(tree_->viewport()->mapToGlobal(pos_));
        }
    }
}

QDomDocument & MainWindow::document()
{
    return _m_project_document;
}

void MainWindow::slot_pouCustomContextMenu(const QPoint &pos_)
{
    createContextMenu(pos_, _m_tree_pou);
}

void MainWindow::slot_devCustomContextMenu(const QPoint &pos_)
{
    createContextMenu(pos_, _m_tree_dev);
}

void MainWindow::slot_pouCurrentChanged(const QModelIndex &current, const QModelIndex &)
{
    _m_addobject_menu->clear();
    if(current.isValid())
    {
        QDomNode node = item(current)->node();
        QList<DynamicAction> acts = _m_dynamic_actions.values(node.nodeName());
        if(acts.size())
        {
            for(auto i : std::as_const(acts))
            {
                if(i._m_views.contains(_m_tree_pou) && i._m_menu == tr("Add object"))
                    _m_addobject_menu->addAction(i._m_act);
            }
        }
    }
    _m_button->setMenu(_m_addobject_menu);
}

void MainWindow::slot_devCurrentChanged(const QModelIndex &current, const QModelIndex &)
{
    _m_addobject_menu->clear();
    if(current.isValid())
    {
        QDomNode node = item(current)->node();
        QList<DynamicAction> acts = _m_dynamic_actions.values(node.nodeName());
        if(acts.size())
        {
            for(auto i : std::as_const(acts))
            {
                if(i._m_views.contains(_m_tree_dev) && i._m_menu == tr("Add object"))
                    _m_addobject_menu->addAction(i._m_act);
            }
        }
    }
    _m_button->setMenu(_m_addobject_menu);
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

void MainWindow::slot_add_DUT()
{
    AddDUTDialog dlg;
    if(dlg.exec() == QDialog::Accepted)
    {
        auto model = reinterpret_cast<QAbstractProxyModel*>(_m_tree_pou->model())->sourceModel();
        auto parentIndex = s_index(_m_tree_pou->currentIndex());
        undoStack()->push(new CUndoCommand_insert(dlg.getNode().toDocument().documentElement(), parentIndex, model));
    }
}

void MainWindow::slot_add_POU()
{
    AddPOUDialog dlg;
    if(dlg.exec() == QDialog::Accepted)
    {
        auto model = reinterpret_cast<QAbstractProxyModel*>(_m_tree_pou->model())->sourceModel();
        auto parentIndex = s_index(_m_tree_pou->currentIndex());
        undoStack()->push(new CUndoCommand_insert(dlg.getNode().toDocument().documentElement(), parentIndex, model));
    }
}

void MainWindow::slot_add_device()
{
    qDebug() << __PRETTY_FUNCTION__;
}

void MainWindow::slot_add_resource()
{
    qDebug() << __PRETTY_FUNCTION__;
}

void MainWindow::slot_add_task()
{
    qDebug() << __PRETTY_FUNCTION__;
}

void MainWindow::slot_add_instance()
{
    qDebug() << __PRETTY_FUNCTION__;
}

void MainWindow::slot_open()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"), QString{}, tr("XML files (*.xml)"));
    if(filePath.isEmpty())
        return;

    _m_proj_dir = QFileInfo(filePath).absoluteDir().absolutePath();

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
        m_info(
            QStringList()
            << QString(tr("open project %1")).arg(_fileName)
            << QString(tr("project file: %1")).arg(_filePath)
            );

    if(!default_file && !QFileInfo::exists(_filePath))
    {
        m_warn(
            QStringList()
            << QString(tr("can't open project %1")).arg(_fileName)
            << QString(tr("file not found: %1").arg(_filePath))
            );

        default_file = true;
    }

    if(default_file)
    {
        _filePath = ":/proj/proj/plc-1.xml";
        _fileName = QFileInfo(_filePath.right(_filePath.size()-1)).fileName();
        m_info(
            QStringList()
            << QString(tr("open project %1")).arg(_fileName)
            << QString(tr("project file: %1")).arg(_filePath)
            );
    }


    QFile file(_filePath);
    if(!file.open(QIODevice::ReadOnly))
    {
        m_crit(
            QStringList()
            << QString(tr("can't open project %1")).arg(_fileName)
            << QString(tr("can't open file for read: %1").arg(_filePath))
            );

        return;
    }
    auto result = _m_project_document.setContent(&file);
    file.close();

    if(!result)
    {
        m_warn(
            QStringList()
            << QString(tr("can't open project %1")).arg(_fileName)
            << QString(tr("file parse error: %1").arg(_filePath))
            );

        return;
    }

    if(result)
    {
        auto newModel = new DomModel(_m_project_document, this);

        StandardLibrary::instance()->add("User types", &_m_project_document, tr("User types"));

        // view->setModel(newModel);

        _m_proxy_pou->setSourceModel(newModel);
        _m_tree_pou->setModel(_m_proxy_pou);
        connect(_m_tree_pou, &QTreeView::doubleClicked, TabWidgetEditor::instance(), &TabWidgetEditor::slot_addTabWidget);
        connect(_m_tree_pou->selectionModel(), &QItemSelectionModel::currentChanged, this, &MainWindow::slot_pouCurrentChanged);

        _m_proxy_dev->setSourceModel(newModel);
        _m_tree_dev->setModel(_m_proxy_dev);
        connect(_m_tree_dev, &QTreeView::doubleClicked, TabWidgetEditor::instance(), &TabWidgetEditor::slot_addTabWidget);
        connect(_m_tree_dev->selectionModel(), &QItemSelectionModel::currentChanged, this, &MainWindow::slot_devCurrentChanged);

        TabWidgetEditor::setModel(newModel);

        delete _m_model_project; _m_model_project = newModel;
        _m_tree_pou->expandAll();
        _m_tree_dev->expandAll();
        for (int i = 0; i < _m_proxy_pou->columnCount(); ++i)
            _m_tree_pou->resizeColumnToContents(i);
        for (int i = 0; i < _m_proxy_dev->columnCount(); ++i)
            _m_tree_dev->resizeColumnToContents(i);
    }

    m_info(
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
        undoStack()->clear();

        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly))
        {
            file.write(_m_model_project->document().toByteArray());
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

    if(index.model() == _m_proxy_pou)
    {
        _m_tree_pou->setCurrentIndex(index);
        dockPou->raise();
        return;
    }

    if(index.model() == _m_proxy_dev)
    {
        _m_tree_dev->setCurrentIndex(index);
        dockDev->raise();
        return;
    }
}

// void MainWindow::slot_undo()
// {
// }

// void MainWindow::slot_redo()
// {
// }

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
    if(QApplication::focusWidget() == _m_tree_pou)
    {
        for(auto index : _m_tree_pou->selectionModel()->selectedRows())
        {
            if(listViewExclude.contains(item(index)->node().nodeName()))
                continue;

            QString _type = {};
            if(item(index)->parentItem()->node().nodeName() == "pous")
                _type = "POU";
            if(item(index)->parentItem()->node().nodeName() == "dataTypes")
                _type = "DUT";

            auto _name = item(index)->node().toElement().attribute("name");
            auto _result = QMessageBox::question
                    (
                        this,
                        tr("Attention"),
                        QString(tr("Do you really want to delete %1 '%2'")).arg(_type, _name)
                );
            if(QMessageBox::Yes == _result)
                undoStack()->push(new CUndoCommand_remove(s_index(index), proxy(_m_tree_pou->model())->sourceModel()));
        }
    }
    // dev tree
    if(QApplication::focusWidget() == _m_tree_dev)
    {
        for(auto index : _m_tree_dev->selectionModel()->selectedRows())
        {
            if(listViewExclude.contains(item(index)->node().nodeName()))
                continue;

            QString _type = {};
            if(item(index)->parentItem()->node().nodeName() == "project")
                _type = "configuration";
            if(item(index)->parentItem()->node().nodeName() == "configuration")
                _type = "resource";
            if(item(index)->parentItem()->node().nodeName() == "resource")
                _type = "task";
            if(item(index)->parentItem()->node().nodeName() == "task")
                _type = "POU instance";

            auto _name = item(index)->node().toElement().attribute("name");
            auto _result = QMessageBox::question
                (
                    this,
                    tr("Attention"),
                    QString(tr("Do you really want to delete %1 '%2'")).arg(_type, _name)
                );
            if(QMessageBox::Yes == _result)
                undoStack()->push(new CUndoCommand_remove(s_index(index), proxy(_m_tree_pou->model())->sourceModel()));
        }
    }
}

void MainWindow::slot_rename()
{
    QTreeView * _tree = nullptr;

    if(QApplication::focusWidget() == _m_tree_pou)
        _tree = _m_tree_pou;
    if(QApplication::focusWidget() == _m_tree_dev)
        _tree = _m_tree_dev;

    if(_tree == nullptr)
        return;

    for(auto index : _tree->selectionModel()->selectedRows())
    {
        // rename dialog
        RenameDialog dlg(item(index)->node().toElement().attribute("name"));
        auto _result = dlg.exec();
        if(_result == QDialog::Accepted)
        {
            // question
            QDomElement _node = item(index)->node().toElement();
            auto _result = QMessageBox::question
                (
                    this,
                    tr("Attention"),
                    QString(tr("Do you really want rename %1 from '%2' to '%3'"))
                        .arg(_node.nodeName(), _node.attribute("name"), dlg.new_name())
                );
            if(QMessageBox::Yes == _result)
            {
                // переименовать node
                item(index)->node().toElement().setAttribute("name", dlg.new_name());
                // переименовать tab
                TabWidgetEditor::instance()->renameTab(index);
            }
        }
    }
}

void MainWindow::slot_properties()
{
    qDebug() << __PRETTY_FUNCTION__;
}

void MainWindow::slot_input_assistant()
{
    InputDialog dlg(InputDialog::eCT_POU);
    dlg.exec();
    qDebug() << dlg.selectedType().toElement().attribute("name");
}

void MainWindow::slot_compile()
{
}

void MainWindow::slot_build()
{
    // *** подготовка ST-файла
    // создание папки для сборки
    auto _buildDir = QString("%1/build").arg(_m_base_directory);
    QDir(_buildDir).removeRecursively();
    QDir(_m_base_directory).mkdir(_buildDir);

    // формирование ST-файла
    QString st_text = Translator::translate(_m_model_project->document());
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
    if( 0 == _m_compiler->compile())
        b_command(CCmd::eCT_Show);
    // ***
}

