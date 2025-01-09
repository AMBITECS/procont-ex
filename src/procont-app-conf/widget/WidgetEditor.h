#ifndef WIDGETEDITOR_H
#define WIDGETEDITOR_H

#include <QSplitter>
#include <QDomNode>

// ----------------------------------------------------------------------------
// *** WidgetEditor ***

/*!
 * \brief The WidgetEditor class
 */

QT_FORWARD_DECLARE_CLASS(QAbstractItemModel)
QT_FORWARD_DECLARE_CLASS(QUndoStack)

QT_FORWARD_DECLARE_CLASS(DomItem)
QT_FORWARD_DECLARE_CLASS(CodeEditorWidget)
QT_FORWARD_DECLARE_CLASS(TableView)

#include <QAbstractProxyModel>

class WidgetEditor : public QSplitter
{
    Q_OBJECT
public:
    WidgetEditor(const QModelIndex &index_, QAbstractProxyModel *proxy_, QWidget *parent_ = {});

    QUndoStack * undoStack() const;

protected slots:
    void slot_varTxtViewToggled(bool);
    void slot_varTblViewToggled(bool);
    void slot_varAddVariable();
    void slot_varDelVariable();
    virtual void slot_varTxtVarChanged();
    virtual void slot_varTblVarChanged();

    void slot_codeTxtChanged();

    void slot_activateUndoStack(QWidget *);

    void slot_selectRow_tree(const QModelIndex &index_, bool);

protected:
    void updateTblView();
    virtual QWidget * createVarsEditor();
    virtual QWidget * createCodeEditor();

protected:
    QModelIndex _m_index{};
    DomItem * _m_item{nullptr};
    QAbstractProxyModel * _m_proxy{nullptr};

protected:
    TableView * _vars_table{nullptr};
    CodeEditorWidget * _vars_text{nullptr};
    CodeEditorWidget * _body_text{nullptr};
    QWidget * _m_table_container{nullptr};

    QUndoStack * _m_undo_stack{nullptr};
};
// ----------------------------------------------------------------------------

#endif // WIDGETEDITOR_H
