#ifndef WIDGETCODEEDITOR_H
#define WIDGETCODEEDITOR_H

#include <QSplitter>
#include <QDomNode>

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

    void slot_codeChanged();
    void slot_txtVarChanged();
    void updateTblView();
    void slot_tblVarChanged();

private:
    QModelIndex _index;
    QDomNode _node;
    QAbstractProxyModel * _proxy;

    CodeEditorWidget * _vars_text;
    CodeEditorWidget * _body_text;
    TableView * _vars_table;
};

#endif // WIDGETCODEEDITOR_H
