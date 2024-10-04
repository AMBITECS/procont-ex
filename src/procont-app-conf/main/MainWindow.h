#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>

QT_FORWARD_DECLARE_CLASS(QTreeView)
QT_FORWARD_DECLARE_CLASS(QDockWidget)

QT_FORWARD_DECLARE_CLASS(DomModel)
QT_FORWARD_DECLARE_CLASS(ProxyModelTree_pou)
QT_FORWARD_DECLARE_CLASS(ProxyModelTree_dev)
QT_FORWARD_DECLARE_CLASS(Compiler)

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow() = default;

private:
    void open(const QString & filePath);
    void save(const QString & filePath);

private:
    void createWidgets();
    void createMenu();

private slots:
    void slot_open();
    void slot_save();
    void slot_undo();
    void slot_redo();
    void slot_cut();
    void slot_copy();
    void slot_paste();
    void slot_delete();
    void slot_compile();
    void slot_build();

    void slot_addBuildMsg();

    void slot_currentViewChanged(const QModelIndex &index);

private:
    QDockWidget * dockPou = nullptr;
    QDockWidget * dockDev = nullptr;

    QTreeView * view = nullptr;
    QTreeView * viewDev = nullptr;
    QTreeView * viewPou = nullptr;

    DomModel * model = nullptr;
    ProxyModelTree_pou * proxy_pou = nullptr;
    ProxyModelTree_dev * proxy_dev = nullptr;

    QString m_projectDir = {};

    QProcess proc;

    Compiler * _m_compiler = nullptr;

};

#endif // MAINWINDOW_H
