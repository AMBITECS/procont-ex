#ifndef GLOBALTYPE_H
#define GLOBALTYPE_H
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
#include <QWidget>
#include <QVector>

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
typedef enum
{
    IT_NOT_DEFINED = 0,
    IT_BLOCK,
    IT_FUNCTION,
    IT_INPUT,
    IT_OUTPUT,
    IT_INPUT_OUTPUT,
    IT_CONNECTOR,
    IT_CONTINUATION,
    IT_COMMENT,

    IT_MAX
}T_FCB_ITEM_TYPE;
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
typedef enum
{
    VT_BASE = 0,
    VT_DERIVED,

    VT_MAX
}T_VARIABLE_TYPE;
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
typedef struct
{
    QString _simpleValue;
}T_INITIAL_VALUE;
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
typedef struct
{
    QString _name;
    T_VARIABLE_TYPE _type;
    T_INITIAL_VALUE _initialValue;
    QString _type_name;
}T_VARIABLE;
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
typedef struct
{
    QVector<T_VARIABLE> _localVars;
}T_POU_INTERFACE;

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
typedef struct
{
    quint32 _x;
    quint32 _y;
}T_CONNECT_POSITION;
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
typedef struct
{
    QString _formalParameter;
    QString _edge;
    struct {
        quint32 _x;
        quint32 _y;
    }_relPosition;
    struct {
        qint32 _refLocalId;
        QString _formalParameter;
        QVector<T_CONNECT_POSITION> _position;
    }_connection;
}T_POU_FBD_ITEM_VARIABLE;
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
typedef struct
{
    // for painting
    bool    _show;
    bool    _select;
    bool    _select_move;
    QRect   _rect;
    // ------------

    T_FCB_ITEM_TYPE _type;
    quint64 _localId;
    QString _name;
    QString _typeName;
    QString _instanceName;
    quint64 _executionOrderId;
    quint32 _pos_x;
    quint32 _pos_y;
    quint64 _width;
    quint64 _height;

    bool    _negated;
    bool    _negatedOut;
    bool    _negatedIn;
    QString _expression;

    struct {
        quint32 _x;
        quint32 _y;
    }_relPositionIn;

    struct {
        quint32 _x;
        quint32 _y;
    }_relPositionOut;

    struct {
        quint32 _refLocalId;
        QString _formalParameter;
        QVector<T_CONNECT_POSITION> _position;
    }_connection;

    QString _comment_content;

    QVector<T_POU_FBD_ITEM_VARIABLE> _inputVariables;
    QVector<T_POU_FBD_ITEM_VARIABLE> _inOutVariables;
    QVector<T_POU_FBD_ITEM_VARIABLE> _outputVariables;
}T_POU_FBD_ITEM;

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
typedef struct
{
    T_FCB_ITEM_TYPE     _type               = IT_NOT_DEFINED;
    bool                _is_used            = false;
    quint64             _localId            = 0;
    quint64             _executionOrderId   = 0;

    bool                _negated            = false;
    bool                _negatedIn          = false;
    bool                _negatedOut         = false;
    QString             _expression         = "";
    QString             _out_var_type       = "";

    QString             _name               = "";
    QString             _typeName           = "";
    QString             _instanceName       = "";

    QVector<QString> _inputVariables;
    QVector<QString> _inOutVariables;
    QVector<QString> _outputVariables;

    QVector<quint32> _out_item_tree;

}T_POU_FBD_ITEM_SHORT;
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
typedef struct
{
    QVector<T_POU_FBD_ITEM> _item;
}T_POU_BODY_FBD;

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
typedef struct
{
    QString _ST_string;
    QString _code_string;
}T_POU_BODY_ST;

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
typedef struct
{
}T_POU_BODY_IL;

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
typedef struct
{
    T_POU_BODY_FBD _FBD;
    T_POU_BODY_ST _ST;
    T_POU_BODY_IL _IL;
    QString _documentation;
}T_POU_BODY;

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
typedef struct
{
    bool _active;
    QString _name;
    QString _pouType;

    T_POU_INTERFACE _interface;
    T_POU_BODY      _body;
}T_POU;

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
typedef enum
{
    DT_REDEFINE = 0,
    DT_ARRAY,
    DT_STRUCT,
    DT_ENUM,
    DT_SUBRANGE_SIGNED,
    DT_SUBRANGE_UNSIGNED,

    DT_MAX
}TE_USER_DATA_TYPE;
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
typedef struct
{
    QString _name;
    QString _type;
}T_UDT_VARIABLE;
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
typedef struct
{
    quint64 _begin;
    quint64 _end;
}T_UDT_RANGE_ARRAY;
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
typedef struct
{
    TE_USER_DATA_TYPE _type;
    QString _name;

    //------------------------------
    bool _initial_value_present;
    QVector<QString> _initial_value;
    //------------------------------
    QString _redefined_name;
    //------------------------------
    QVector<T_UDT_VARIABLE> _struct;
    //------------------------------
    struct{
        std::vector<T_UDT_RANGE_ARRAY> _range;
        QString _type;
    }_array;
    //------------------------------
    struct{
        QVector<QString> _value;
    }_enum;
    //------------------------------
    struct{
        qint64 _begin;
        qint64 _end;
        QString _type;
    }_sign_unsign_range;
    //------------------------------
}T_UDT;
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
typedef struct
{
    QString _name;
    QString _typeName;
}T_POU_INSTANCE;
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
typedef struct
{
    QString _name;
    QString _priority;
    QString _interval;
    QVector<T_POU_INSTANCE> _pouInstance;
}T_TASK;
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
typedef struct
{
    QString _name;
    QVector<T_TASK> _task;
}T_RESUORCE;
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
typedef struct
{
    QString _name;
    T_RESUORCE _resource;
}T_CONFIGURATION;
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
typedef struct
{
    QVector<T_CONFIGURATION> _configuration;
}T_INSTANCES;
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

#endif // GLOBALTYPE_H
