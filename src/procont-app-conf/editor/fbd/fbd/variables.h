//
// Created by nechi on 05.11.2024.
//

#ifndef EDITORSD_VARIABLES_H
#define EDITORSD_VARIABLES_H

#include <QString>

namespace txt_vars
{
    static const char * drag_source_prop   = "source";      //!< наименование свойства, характеризующего источник drag (откуда несём)
    static const QString  drag_src_palette = "palette";   //!< десант из палитры компонентов
    static const QString  drag_src_canvas  = "canvas";     //!< десант из диаграммы
    static const char *   drag_obj_prop_name = "object";  //!< наименование свойства, характеризующего что мы несём
    static const QString  dragging_ladder = "ladder";     //!< мы несём ступень (из диаграммы
    static const QString  dragging_object = "object";     //!< мы несём компонент (из диаграммы)
    static const char *   drag_element    = "element";    //!< несём элемент из палитры
    static const QString  drag_pin        = "pin";
}

namespace xmln
{
    static const char * pou_type  = "pouType";
    static const char * interface = "interface";
    static const char * return_type = "returnType";
    static const char * datatypes = "dataTypes";
    static const char * datatype  = "dataType";
    static const char * name      = "name";
    static const char * base_type = "baseType";
    static const char * values    = "values";
    static const char * value     = "value";
    static const char * struct_node = "struct";
    static const char * array_node  = "array";
    static const char * array_lower = "lower";
    static const char * array_upper = "upper";
    static const char * array_dim   = "dimension";
    static const char * range_node = "range";
    static const char * initial_value_node = "initialValue";
    static const char * init_val_attrib    = "value";
    static const char * subrange_node = "subrangeSigned";
    static const char * simple_value  = "simpleValue";
    static const char * types_node    = "types";
    static const char * function_pou_type = "function";
    static const char * project_types = "types";
}

#endif //EDITORSD_VARIABLES_H
