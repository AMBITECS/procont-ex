#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QDomDocument>

QT_FORWARD_DECLARE_CLASS(QTreeView)
QT_FORWARD_DECLARE_CLASS(QDockWidget)
QT_FORWARD_DECLARE_CLASS(QAbstractItemModel)
QT_FORWARD_DECLARE_CLASS(QAbstractProxyModel)
QT_FORWARD_DECLARE_CLASS(QToolButton)
QT_FORWARD_DECLARE_CLASS(QSettings)
QT_FORWARD_DECLARE_CLASS(QUndoStack)
QT_FORWARD_DECLARE_CLASS(QUndoGroup)

QT_FORWARD_DECLARE_CLASS(DomModel)
QT_FORWARD_DECLARE_CLASS(DomItem)
QT_FORWARD_DECLARE_CLASS(TreeView)
QT_FORWARD_DECLARE_CLASS(ProxyModelTree_pou)
QT_FORWARD_DECLARE_CLASS(ProxyModelTree_dev)
QT_FORWARD_DECLARE_CLASS(Compiler)
QT_FORWARD_DECLARE_CLASS(CTreeObject)
QT_FORWARD_DECLARE_CLASS(CWidgetProtocol)

class MainWindow : public QMainWindow
{
    Q_OBJECT

    struct DynamicAction
    {
        DynamicAction(QAction *act_, const QList<QTreeView *> &views_) :
            _m_act(act_), _m_views(views_)
        {;}
        DynamicAction(QAction *act_, const QList<QTreeView *> &views_, const QString &menu_) :
            _m_act(act_), _m_views(views_), _m_menu(menu_)
        {;}
        DynamicAction(QAction *act_, const QList<QTreeView *> &views_, bool separator_) :
            _m_act(act_), _m_views(views_), _m_separator(separator_)
        {;}
        DynamicAction(QAction *act_, const QList<QTreeView *> &views_, const QString &menu_, bool separator_) :
            _m_act(act_), _m_views(views_), _m_menu(menu_), _m_separator(separator_)
        {;}

        DynamicAction(const DynamicAction &other_) = default;
        DynamicAction & operator = (const DynamicAction &other_) = default;

        QAction * _m_act = nullptr;
        QList<QTreeView *> _m_views;
        QString _m_menu = QString();
        bool _m_separator = false;
    };


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow() override;

public:
    static MainWindow * instance();

    CTreeObject * toolWidget() const;
    TreeView * pouWidget() const { return _m_tree_pou; }
    ProxyModelTree_pou * pouProxy() const { return _m_proxy_pou; }

    static QString config_file() { return _m_config_filepath; }
    static void setConfig(const QString &);
    static void setDirectory(const QString &);

    QDomDocument & document();

    static void addStack(QUndoStack *_stack);
    QUndoStack * emptyStack() const;
    void setModified(bool modified_);

protected:
    void closeEvent(QCloseEvent *event) override;
    [[nodiscard]] bool isModified() const;

private:
    static QUndoGroup * undoGroup();

private:
    void open(const QString & filePath = {});
    void save(const QString & filePath);

private:
    void createWidgets();
    void createMenu();
    void createDynamicActions();

private slots:
    void slot_open();
    void slot_save();
    // void slot_undo();
    // void slot_redo();
    void slot_cut();
    void slot_copy();
    void slot_paste();
    void slot_delete();
    void slot_rename();
    void slot_properties();
    void slot_input_assistant();

    void slot_compile();
    void slot_build();

    void slot_add_DUT();
    void slot_add_POU();
    void slot_add_device();
    void slot_add_resource();
    void slot_add_task();
    void slot_add_instance();

    void slot_pouCurrentChanged(const QModelIndex &current, const QModelIndex &previous);
    void slot_devCurrentChanged(const QModelIndex &current, const QModelIndex &previous);

    void slot_currentViewChanged(const QModelIndex &index);

    void slot_pouCustomContextMenu(const QPoint &);
    void slot_devCustomContextMenu(const QPoint &);

    void slot_focusChanged(QWidget *, QWidget *);

    void slot_treeitem_insert(const QModelIndex &index_);

private:
    void createContextMenu(const QPoint &pos_, const QTreeView *tree_);

private:
    QDockWidget * dockPou{nullptr};
    QDockWidget * dockDev{nullptr};

    // QTreeView * view{nullptr};
    TreeView * _m_tree_dev{nullptr};
    TreeView * _m_tree_pou{nullptr};

    DomModel * _m_model_project{nullptr};
    ProxyModelTree_pou * _m_proxy_pou{nullptr};
    ProxyModelTree_dev * _m_proxy_dev{nullptr};

    QString _m_proj_dir{};

    Compiler * _m_compiler{nullptr};

    QMenu * _m_view_menu{nullptr};
    QMultiHash<QString, DynamicAction> _m_dynamic_actions;
    QMenu * _m_addobject_menu{nullptr};

    QToolButton * _m_button{nullptr};

    CTreeObject * _m_toolWidget{nullptr};

    QSettings * _m_settings{nullptr};

    QDomDocument _m_project_document;

    static QUndoGroup * _m_undo_group;
    std::list<QObject *> _m_nostack_widgets;
    QUndoStack * _m_empty_stack{nullptr};
    bool _m_modified{false};

private:
    static MainWindow * _m_instance;
    static QString _m_config_filepath;
    static QString _m_base_directory;
    static const QString _m_defaultProjectFilename;
};

#endif // MAINWINDOW_H
