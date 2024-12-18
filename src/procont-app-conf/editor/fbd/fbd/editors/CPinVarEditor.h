//
// Created by artem on 11/17/24.
//

#ifndef EDITORSD_CPINVAREDITOR_H
#define EDITORSD_CPINVAREDITOR_H

#include <QComboBox>
#include <QWidget>
#include <QTreeView>
#include "../graphics/CPin.h"
#include "editor/fbd/plc-xml/common/CVariablesAnalytics.h"


class CPinVarEditor : public QComboBox
{
    Q_OBJECT
public:
    explicit CPinVarEditor(QWidget *parent = nullptr);
    ~CPinVarEditor() override;

    void hideColumn(int n);
    void expandAll();
    void selectIndex(const QModelIndex &index);
    void set_pin(CPin *pin);

signals:
    void edit_cancel();
    void new_variable_name(const QString &variable_name);
    void new_pin_connection(s_tree_item *selected_item, const QString & manual_str);

protected slots:
    void tree_clicked(const QPersistentModelIndex &index);
    void show_variable();
    void text_changed(const QString &text);

protected:
    void showPopup() override;
    void hidePopup() override;
    bool eventFilter(QObject* object, QEvent* event) override;



private:
    QTreeView   * m_view = nullptr;
    CPin        * m_pin{nullptr};
    QString       m_new_variable;
    s_tree_item * m_parent_item{nullptr};
    s_tree_item * m_selected_item {nullptr};
    bool skipNextHide;
    CVariablesAnalytics * m_analytics{nullptr};

    QColor  m_foreground_error;
    QColor  m_background_error;
    QColor  m_foreground_norm;
    QColor  m_background_norm;

    void prepare_new_variable();
    void reset_selection();
    void    set_error(const bool &is_error);

    bool check_compatibility(CVariable *iface_var, const EDefinedDataTypes &type);
};


#endif //EDITORSD_CPINVAREDITOR_H
