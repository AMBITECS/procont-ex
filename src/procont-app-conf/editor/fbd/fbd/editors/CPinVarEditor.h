//
// Created by artem on 11/17/24.
//

#ifndef EDITORSD_CPINVAREDITOR_H
#define EDITORSD_CPINVAREDITOR_H

#include <QComboBox>
#include <QWidget>
#include <QTreeView>

class CPinVarEditor : public QComboBox
{
    Q_OBJECT
public:
    explicit CPinVarEditor(QWidget *parent = nullptr);
    ~CPinVarEditor() override;

    void hideColumn(int n);
    void expandAll();
    void selectIndex(const QModelIndex &index);

signals:
    void edit_cancel();
    void new_variable_name(const QString &variable_name);

protected slots:
    void tree_clicked(const QPersistentModelIndex &index);
    void show_variable();

protected:
    void showPopup() override;
    void hidePopup() override;
    bool eventFilter(QObject* object, QEvent* event) override;



private:
    QTreeView *m_view = nullptr;
    QString    m_new_variable;
};


#endif //EDITORSD_CPINVAREDITOR_H
