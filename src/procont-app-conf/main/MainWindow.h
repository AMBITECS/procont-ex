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
    ~MainWindow() = default;

public:
    static MainWindow * instance();

    CTreeObject * toolWidget() const;

    static QString config_file() { return _m_config_filepath; }
    static void setConfig(const QString &);
    static void setDirectory(const QString &);

    QDomDocument & document();

    QUndoStack * undoStack() const;

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

private:
    void createContextMenu(const QPoint &pos_, const QTreeView *tree_);

private:
    static QModelIndex s_index(const QModelIndex &index, QAbstractItemModel * proxy = nullptr);
    static QModelIndex p_index(const QModelIndex &index, QAbstractItemModel * proxy);
    static QAbstractProxyModel * proxy(QAbstractItemModel *);
    static DomItem * item(const QModelIndex &index, QAbstractItemModel * proxy = nullptr);

private:
    QDockWidget * dockPou{nullptr};
    QDockWidget * dockDev{nullptr};

    // QTreeView * view{nullptr};
    QTreeView * _m_tree_dev{nullptr};
    TreeView * _m_tree_pou{nullptr};

    DomModel * _m_model_project{nullptr};
    ProxyModelTree_pou * _m_proxy_pou{nullptr};
    ProxyModelTree_dev * _m_proxy_dev{nullptr};

    QString _m_proj_dir{};

    Compiler * _m_compiler{nullptr};

    QMultiHash<QString, DynamicAction> _m_dynamic_actions;
    QMenu * _m_addobject_menu{nullptr};

    QToolButton * _m_button{nullptr};

    CTreeObject * _m_toolWidget{nullptr};

    QSettings * _m_settings{nullptr};

    static QString _m_config_filepath;
    static QString _m_base_directory;

    QDomDocument _m_project_document;

    CWidgetProtocol * _m_widget_protocol{nullptr};
    QUndoStack * _m_undo_stack{nullptr};

private:
    static MainWindow * _m_instance;
};

#endif // MAINWINDOW_H
