#ifndef WIDGETEDITOR_H
#define WIDGETEDITOR_H

#include <QSplitter>
#include <QDomNode>

// ----------------------------------------------------------------------------
// *** WidgetCodeEditor ***

/*!
 * \brief The WidgetCodeEditor class
 */

QT_FORWARD_DECLARE_CLASS(DomItem)
QT_FORWARD_DECLARE_CLASS(QAbstractItemModel)

QT_FORWARD_DECLARE_CLASS(CodeEditorWidget)
QT_FORWARD_DECLARE_CLASS(TableView)

#include <QAbstractProxyModel>

class WidgetEditor : public QSplitter
{
    Q_OBJECT
public:
    WidgetEditor(const QModelIndex &index_, QAbstractProxyModel *proxy_, QWidget *parent_ = {});

protected:
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
    void slot_tblVarChanged();

protected:
    void updateTblView();
    virtual QWidget * createVarsEditor();
    virtual QWidget * createCodeEditor();

protected:
    QModelIndex _index = {};
    QDomNode _node = {};
    QAbstractProxyModel * _proxy = nullptr;

protected:
    TableView * _vars_table = nullptr;
    CodeEditorWidget * _vars_text = nullptr;
    CodeEditorWidget * _body_text = nullptr;
    QWidget * _m_table_container = nullptr;
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** WidgetEditor_vars ***

/*!
 * \brief The WidgetEditor_vars class
 */
class WidgetEditor_vars : public WidgetEditor
{
    Q_OBJECT
public:
    WidgetEditor_vars(const QModelIndex &index_, QAbstractProxyModel *proxy_, QWidget *parent_ = {});
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** WidgetEditor_st ***

/*!
 * \brief The WidgetEditor_st class
 */
class WidgetEditor_st : public WidgetEditor
{
    Q_OBJECT
public:
    WidgetEditor_st(const QModelIndex &index_, QAbstractProxyModel *proxy_, QWidget *parent_ = {});
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** WidgetEditor_fbd ***

/*!
 * \brief The WidgetEditor_fbd class
 */

// QT_FORWARD_DECLARE_CLASS(FBDviewer)
QT_FORWARD_DECLARE_CLASS(CDiagramWidget)

class WidgetEditor_fbd : public WidgetEditor
{
    Q_OBJECT
public:
    WidgetEditor_fbd(const QModelIndex &index_, QAbstractProxyModel *proxy_, QWidget *parent_ = {});

protected:
    virtual QWidget * createCodeEditor();

private slots:
    void slot_shmViewToggled(bool);
    void slot_txtViewToggled(bool);

private:
    QWidget * _txt_view = nullptr;
    // FBDviewer * _fbd_view = nullptr;
    CDiagramWidget * _m_fbd_view = nullptr;
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** WidgetEditor_type ***

/*!
 * \brief The WidgetEditor_type class
 */
class WidgetEditor_type : public WidgetEditor
{
    Q_OBJECT
public:
    WidgetEditor_type(const QModelIndex &index_, QAbstractProxyModel *proxy_, QWidget *parent_ = {});

private slots:
    void slot_codeChanged();

protected:
    virtual QWidget * createCodeEditor();
};
// ----------------------------------------------------------------------------

#endif // WIDGETEDITOR_H
