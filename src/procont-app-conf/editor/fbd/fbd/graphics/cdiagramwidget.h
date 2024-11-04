//
// Created by artem on 10/10/24.
//

#ifndef EDITORSD_CDIAGRAMWIDGET_H
#define EDITORSD_CDIAGRAMWIDGET_H

#include <QWidget>
#include <QScrollBar>
#include <QTreeWidget>
#include <QDomNode>
#include "../../..//st/CodeEditorWidget.h"
#include "../../general/types.h"
#include "coglwidget.h"

typedef struct s_fbd_start_data
{
    bool    is_final;
    bool    is_abstract{false};
    QString name{"newPOU"};
    QString pou_to_derive_name;
    QString pou_to_implement_name;
    QDomNode *xml_data{nullptr};
    CTreeObject *tree;
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
    explicit CDiagramWidget(const QDomNode &pou_node, CTreeObject * tree_object, const bool &is_editable = true, QWidget *parent = nullptr);
    ~CDiagramWidget() override;

    void  set_active();


signals:
    void    diagram_changed(const QDomNode & node);

public slots:
    void    diagram_updated();

protected:



protected slots:
    void build_tree();


private:
    Ui::Form   *ui;
    CodeEditorWidget    * m_st_widget;
    COglWidget          * m_ogl_widget;
    QTreeWidget         * m_tree_widget;
    //QTabWidget          * m_parent;
    //int                   m_this_index{-1};
    //bool                  m_active{false};
    bool                  m_is_editable{true};
    QDomNode            * m_dom_node;

};


#endif //EDITORSD_CDIAGRAMWIDGET_H
