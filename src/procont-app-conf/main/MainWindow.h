#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>

QT_FORWARD_DECLARE_CLASS(QTreeView)
QT_FORWARD_DECLARE_CLASS(QDockWidget)
QT_FORWARD_DECLARE_CLASS(QAbstractItemModel)
QT_FORWARD_DECLARE_CLASS(QAbstractProxyModel)
QT_FORWARD_DECLARE_CLASS(QToolButton)

QT_FORWARD_DECLARE_CLASS(DomModel)
QT_FORWARD_DECLARE_CLASS(DomItem)
QT_FORWARD_DECLARE_CLASS(TreeView)
QT_FORWARD_DECLARE_CLASS(ProxyModelTree_pou)
QT_FORWARD_DECLARE_CLASS(ProxyModelTree_dev)
QT_FORWARD_DECLARE_CLASS(Compiler)
QT_FORWARD_DECLARE_CLASS(CTreeObject)

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow() = default;

public:
    static MainWindow * instance();

    CTreeObject * toolWidget() const;

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
    void slot_undo();
    void slot_redo();
    void slot_cut();
    void slot_copy();
    void slot_paste();
    void slot_delete();
    void slot_input_assistant();

    void slot_compile();
    void slot_build();

    void slot_addDUT();
    void slot_addPOU();

    void slot_pouCurrentChanged(const QModelIndex &current, const QModelIndex &previous);

    void slot_currentViewChanged(const QModelIndex &index);

    void slot_pouCustomContextMenu(const QPoint &);

private:
    static QModelIndex s_index(const QModelIndex &index, QAbstractItemModel * proxy = nullptr);
    static QModelIndex p_index(const QModelIndex &index, QAbstractItemModel * proxy);
    static QAbstractProxyModel * proxy(QAbstractItemModel *);
    static DomItem * item(const QModelIndex &index, QAbstractItemModel * proxy = nullptr);

private:
    QDockWidget * dockPou = nullptr;
    QDockWidget * dockDev = nullptr;

    QTreeView * view = nullptr;
    QTreeView * viewDev = nullptr;
    TreeView * viewPou = nullptr;

    DomModel * model = nullptr;
    ProxyModelTree_pou * proxy_pou = nullptr;
    ProxyModelTree_dev * proxy_dev = nullptr;

    QString m_projDir = {};
    QString m_baseDir = {};

    Compiler * _m_compiler = nullptr;

    QMultiHash<QString, QAction *> _m_dynamicActions;
    QMenu * _m_addObjectMenu = nullptr;

    QToolButton * _m_button;

    CTreeObject * _m_toolWidget;

private:
    static MainWindow * _m_instance;
};

#endif // MAINWINDOW_H
