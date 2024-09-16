#ifndef WIDGETCODEEDITOR_H
#define WIDGETCODEEDITOR_H

#include <QSplitter>

QT_FORWARD_DECLARE_CLASS(DomItem)
QT_FORWARD_DECLARE_CLASS(QAbstractItemModel)

QT_FORWARD_DECLARE_CLASS(CodeEditorWidget)
QT_FORWARD_DECLARE_CLASS(TableView)

#include <QAbstractProxyModel>

class WidgetCodeEditor : public QSplitter
{
    Q_OBJECT
public:
    WidgetCodeEditor(const QModelIndex &index_, QAbstractProxyModel *proxy_, QWidget *parent_ = {});

private:
    static QModelIndex s_index(const QModelIndex &index, QAbstractItemModel * proxy = nullptr);
    static QModelIndex p_index(const QModelIndex &index, QAbstractItemModel * proxy);
    static QAbstractProxyModel * proxy(QAbstractItemModel *);
    static DomItem * item(const QModelIndex &index, QAbstractItemModel * proxy = nullptr);

private slots:
    void slot_addVariable();
    void slot_delVariable();
    void slot_txtViewToggled(bool);
    void slot_tblViewToggled(bool);

    void slot_textChanged();

private:
    QModelIndex _index;
    QAbstractProxyModel * _proxy;

    CodeEditorWidget * _var_text;
    CodeEditorWidget * _text;
    TableView * _var_table;
};

#endif // WIDGETCODEEDITOR_H
