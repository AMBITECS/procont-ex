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
    virtual ~WidgetEditor() override;

    virtual void set_active();

protected slots:
    void slot_varTxtViewToggled(bool);
    void slot_varTblViewToggled(bool);

    virtual void slot_varAddVariable();
    virtual void slot_varDelVariable();
    virtual void slot_varTxtVarChanged();
    virtual void slot_varTblVarChanged();

    void slot_codeTxtChanged();

    virtual void slot_variable_insert(const QModelIndex &index_, bool first_);
    virtual void slot_variable_delete(const QDomNode &node_);
    virtual void slot_variable_change(const QDomNode& old_, const QDomNode& new_);

protected:
    virtual QWidget * createVarsEditor();
    virtual QWidget * createCodeEditor();
    void init_focus() const;
    void update_table_view();

protected:
    QModelIndex _m_index{};
    DomItem * _m_item{nullptr};
    QAbstractProxyModel * _m_proxy{nullptr};

protected:
    TableView * _m_vars_table{nullptr};
    CodeEditorWidget * _m_vars_text{nullptr};
    CodeEditorWidget * _m_body_text{nullptr};
    QWidget * _m_table_container{nullptr};
};
// ----------------------------------------------------------------------------

#endif // WIDGETEDITOR_H
