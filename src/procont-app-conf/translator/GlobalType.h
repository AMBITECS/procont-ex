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
    PT_NOT_DEFINED = 0,
    PT_PROGRAMM,
    PT_FUNCTION_BLOCK,
    PT_FUNCTION,

    PT_MAX
}T_POU_TYPE;
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
typedef enum
{
    PBT_NOT_DEFINED = 0,
    PBT_FBD,
    PBT_ST,
    PBT_SFC,
    PBT_IL,
    PBT_LD,

    PBT_MAX
}T_POU_BODY_TYPE;
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
typedef enum
{
    IT_FBD_NOT_DEFINED = 0,
    IT_FBD_BLOCK,
    IT_FBD_FUNCTION,
    IT_FBD_INPUT,
    IT_FBD_OUTPUT,
    IT_FBD_INPUT_OUTPUT,
    IT_FBD_CONNECTOR,
    IT_FBD_CONTINUATION,
    IT_FBD_COMMENT,

    IT_FBD_MAX
}T_FBD_ITEM_TYPE;
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
typedef enum
{
    IT_SFC_NOT_DEFINED = 0,
    IT_SFC_STEP,
    IT_SFC_ACTION_BLOCK,
    IT_SFC_TRANSITION,
    IT_SFC_JUMP_STEP,
    IT_SFC_SELECTION_DIVERGENCE,
    IT_SFC_SELECTION_CONVERGENCE,
//    IT_SFC_CONTINUATION,
//    IT_SFC_COMMENT,

    IT_SFC_MAX
}T_SFC_ITEM_TYPE;
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
typedef enum
{
    VQ_NOQUALIFIER = 0,
    VQ_CONSTANT,
    VQ_RETAIN,
    VQ_NONRETAIN
}T_VARIABLE_QUALIFIER;

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
    bool _is_used                       = false;
    T_VARIABLE_QUALIFIER _qualifier     = VQ_NOQUALIFIER;
    QString _name                       = "";
    QString _address                    = "";
    QString _documentation              = "";
    T_VARIABLE_TYPE _type               = VT_BASE;
    T_INITIAL_VALUE _initialValue;
    QString _type_name                  = "";
}T_VARIABLE;
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
typedef struct
{
    QVector<T_VARIABLE> _globalVars;
    QVector<T_VARIABLE> _localVars;
    QVector<T_VARIABLE> _inputVars;
    QVector<T_VARIABLE> _outputVars;
    QVector<T_VARIABLE> _inoutVars;
    QVector<T_VARIABLE> _tempVars;
    QVector<T_VARIABLE> _externalVars;
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
    QString _formalParameter_type;
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

    T_FBD_ITEM_TYPE _type;
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
    QString _return_type;

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
    QString _name;
    QString _ST_code;
}T_SFC_CONDITION;

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
typedef struct
{
    quint32 _localId        = 0;
    QString _qualifier      = "N";
    QString _indicator      = "";
    quint32 _pel_position_x = 0;
    quint32 _pel_position_y = 0;
    QString _ST_code;
}T_SFC_ACTION;

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
typedef struct
{
    QString _formalParameter;
    quint32 _rel_position_x;
    quint32 _rel_position_y;
}T_SFC_CONNECTION_POINT_OUT;

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
typedef struct
{
    quint32 _refLocalId         = 0;
    QVector<T_CONNECT_POSITION> _position;
}T_SFC_CONNECTION;

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
typedef struct
{
    quint32 _rel_position_x;
    quint32 _rel_position_y;
    T_SFC_CONNECTION _connection;
}T_SFC_CONNECTION_POINT_IN;

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
typedef struct
{
    T_SFC_ITEM_TYPE _type   = IT_SFC_NOT_DEFINED;

    bool _is_used               = false;

    quint64 _localId            = 0;
    QString _name               = "";
    quint64 _executionOrderId   = 0;
    QString _initialStep        = "";
    QString _targetName         = "";
    quint64 _width              = 0;
    quint64 _height             = 0;

    quint32 _position_x;
    quint32 _position_y;

    QVector<T_SFC_CONNECTION_POINT_OUT> _point_out;
    QVector<T_SFC_CONNECTION_POINT_OUT> _point_out_action;
    QVector<T_SFC_CONNECTION_POINT_IN>  _point_in;

    QVector<T_SFC_CONDITION>    _condition;
    QVector<T_SFC_ACTION>       _action;
}T_POU_SFC_ITEM;

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
typedef struct {
    QString _name;
    QString _type;
}T_CONNECTION_VAR;
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
typedef struct
{
    T_FBD_ITEM_TYPE     _type               = IT_FBD_NOT_DEFINED;
    bool                _is_used            = false;
    quint64             _localId            = 0;
    quint64             _executionOrderId   = 0;

    bool                _negated            = false;
    bool                _negatedIn          = false;
    bool                _negatedOut         = false;
    QString             _expression         = "";
    QString             _return_type        = "";

    QString             _name               = "";
    QString             _typeName           = "";
    QString             _instanceName       = "";

    bool _connection_complit                = false;
    QVector<T_CONNECTION_VAR> _inputVariables;
    QVector<T_CONNECTION_VAR> _inOutVariables;
    QVector<T_CONNECTION_VAR> _outputVariables;
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
    QVector<T_POU_SFC_ITEM> _item;
}T_POU_BODY_SFC;

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
typedef struct
{
    QStringList _ST_code;
}T_POU_BODY_ST;

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
typedef struct
{
    QStringList _IL_code;
}T_POU_BODY_IL;

//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
typedef struct
{
    T_POU_BODY_TYPE _type;
    T_POU_BODY_FBD _FBD;
    T_POU_BODY_SFC _SFC;
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
    T_POU_TYPE _pouType;

    T_POU_INTERFACE _interface;
    T_POU_BODY      _body;
    QString         _return_type;
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
    QVector<T_VARIABLE> _globalVars;
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
