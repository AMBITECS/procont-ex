//
// Created by nechi on 05.11.2024.
//

#ifndef EDITORSD_VARIABLES_H
#define EDITORSD_VARIABLES_H
#include <QString>

namespace txt_vars
{
    static const char * drag_source_prop = "source";      //!< наименование свойства, характеризующего источник drag (откуда несём)
    static const QString  drag_src_palette = "palette";   //!< десант из палитры компонентов
    static const QString  drag_src_canvas = "canvas";     //!< десант из диаграммы
    static const char *   drag_obj_prop_name = "object";  //!< наименование свойства, характеризующего что мы несём
    static const QString  dragging_ladder = "ladder";     //!< мы несём ступень (из диаграммы
    static const QString  dragging_object = "object";     //!< мы несём компонент (из диаграммы)
    static const char *   drag_element    = "element";     //!< несём элемент из палитры
}

namespace xml_nodes
{

}

#endif //EDITORSD_VARIABLES_H
