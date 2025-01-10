//
// Created by artem on 10/10/24.
//

#ifndef EDITORSD_CDIAGRAMWIDGET_H
#define EDITORSD_CDIAGRAMWIDGET_H

#include <QWidget>
#include <QScrollBar>
#include <QTreeWidget>
#include <QDomNode>

#include "editor/fbd/common/general/types.h"
#include "coglwidget.h"
#include "editor/fbd/common/general/ctreeobject.h"

typedef struct s_fbd_start_data
{
    bool    is_final;
    bool    is_abstract{false};
    QString name{"newPOU"};
    QString pou_to_derive_name;
    QString pou_to_implement_name;
    QDomNode *xml_data{nullptr};
    CTreeObject *tree{nullptr};
} SFbdStartupData;



namespace Ui {
    class Form;
}

/**
 * @brief визуальный видгет, содержащий в себе посадочные места для составляющих FBD-редактора:<br>
 @param
 * QScrollBar*  oglVerticalScrolling()   вертикальная полоса прокрутки для OpenGL видгета<br>
 @param
 * QScrollBar*  oglHorizontalScrolling() горизонтальная полоса прокрутки для OpenGL видгета<br>
 @param
 * CodeEditorWidget *  stEditorWidget()  видгет ST-редактора. Он должен быть во всех типах диаграмм<br>
 @param
 * QWidget*     oglPlaceWidget()         видгет для посадки OpenGLWidget (возможно позже он займет это место сразу) <br>
 *
 * @attention  не забудьте создать/удалить QGridLayout для посадки openGL и st-editor видгетов
 */
class CDiagramWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CDiagramWidget(const QDomNode &pou_node, CTreeObject * tree_object,
                            const bool &is_editable = true, QWidget *parent = nullptr);
    ~CDiagramWidget() override;
    void  set_active();

    QUndoStack *    undo_stack();

signals:
    void    changed_diagram(const QDomNode & node);
    void    undo_enabled();
    void    interface_variable_new(const QString &type, const QString &name);
    void    interface_variable_rename(const QString &old_name, const QString &new_name);
    void    instance_removed(const QString &type, const QString &name);
    void    object_selected();
    void    user_clicked();
public slots:
    /** @brief пользователь ввёл новую переменную. Необходимо обновить данные о локальном интерфейсе */
    void    update_interface(const QDomNode &node);
    void    delete_selected_object();

protected:


protected slots:
    void build_tree();
    void diagram_object_is_selected();
    void diagram_has_changed(const QDomNode &node);


private:
    Ui::Form   *ui;
    COglWidget          * m_ogl_widget;
    CTreeObject         * m_tree_widget;
    bool                  m_is_editable{true};
    QDomNode            * m_dom_node;
    CPou                * m_current_pou{nullptr};

};


#endif //EDITORSD_CDIAGRAMWIDGET_H
