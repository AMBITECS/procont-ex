#include "FbdTranslator.h"

// *** dataType
//
//-----------------------------------------------------------------------------------
QString FbdTranslator::getSTCode_types(const QDomNode &node_)
{
    // node is dataTypes
    if(node_.nodeName() != "dataTypes")
        return {};

    QString _text = {};

    QDomNodeList types = node_.toElement().elementsByTagName("dataType");

    if(types.size())
        _text += QString("TYPE\n");

    for(auto i=0;i<types.size();i++)
        _text += getSTCode_type(types.at(i));

    if(types.size())
        _text += QString("END_TYPE\n\n");

    return _text;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
QString FbdTranslator::getSTCode_type(const QDomNode &node_)
{
    QString _text = {};

    T_UDT _UDT;
    if(PLCopenXmlParser::parseUDT(node_, &_UDT))
        _text = UDT_STgenerator(_UDT);

    return _text;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
QString FbdTranslator::UDT_STgenerator(const T_UDT &udt_)
{
    QString _data = {};

    switch(udt_._type)
    {
    case DT_MAX:{}break;
    case DT_ARRAY:{
        int _range_counter = 0;
        int _ini_val_counter = 0;
        //            datatype0 : ARRAY [10..20,50..60] OF WORD := [1, 1];
        _data += QString("  %1 : ARRAY [").arg(udt_._name);
        int _size = (int)udt_._array._range.size();
        for(int _j = 0; _j < _size; _j++)
        {
            QString _range = QString("%1..%2").arg(udt_._array._range[_j]._begin).arg(udt_._array._range[_j]._end);
            _data += _range;
            _range_counter++;
            if(_range_counter < _size)_data += ",";
        }
        _data += QString("] OF %1").arg(udt_._array._type);
        if(udt_._initial_value_present)
        {
            _data += " := [";
            int _init_size = (int)udt_._initial_value.size();
            for(int _j = 0; _j < _init_size; _j++)
            {
                QString _val = QString("%1").arg(udt_._initial_value[_j]);
                _data += _val;
                _ini_val_counter++;
                if(_ini_val_counter < _init_size)_data += ", ";
            }
            _data += "];\n";
        }else _data += QString(";\n");
    }break;
    case DT_STRUCT:{
        //            datatype5 : STRUCT
        //              p0 : datatype3;
        //              p1 : DINT;
        //              p2 : DINT;
        //              p3 : DINT;
        //            END_STRUCT;
        _data += QString("  %1 : STRUCT\n").arg(udt_._name);
        for(int _j = 0; _j < (int)udt_._struct.size(); _j++)
        {
            QString _part = QString("    %1 : %2;\n").arg(udt_._struct[_j]._name).arg(udt_._struct[_j]._type);
            _data += _part;
        }
        _data += "  END_STRUCT;\n";
    }break;
    case DT_ENUM:{
        //            datatype3 : (firstType, secondType) := firstType;
        _data += QString("  %1 : (%2").arg(udt_._name).arg(udt_._enum._value[0]);
        for(int _j = 1; _j < (int)udt_._enum._value.size(); _j++)
            _data += QString(", %1").arg(udt_._name);

        if(udt_._initial_value_present)   _data += QString(") := %1;\n").arg(udt_._initial_value[0]);
        else                                    _data += QString(");\n");
    }break;
    case DT_REDEFINE:{
        _data += QString("  %1 : %2;\n").arg(udt_._name).arg(udt_._redefined_name);
    }break;
    case DT_SUBRANGE_SIGNED:{
        //            datatype1 : INT (0..0) := 0;
        _data += QString("  %1 : %2 (%3..%4)").arg(udt_._name)
                     .arg(udt_._sign_unsign_range._type)
                     .arg(udt_._sign_unsign_range._begin)
                     .arg(udt_._sign_unsign_range._end);
        if(udt_._initial_value_present)   _data += QString(" := %1;\n").arg(udt_._initial_value[0]);
        else                                    _data += QString(";\n");
    }break;
    case DT_SUBRANGE_UNSIGNED:{
        //            datatype1 : UINT (0..0) := 0;
        _data += QString("  %1 : %2 (%3..%4)").arg(udt_._name)
                     .arg(udt_._sign_unsign_range._type)
                     .arg(udt_._sign_unsign_range._begin)
                     .arg(udt_._sign_unsign_range._end);
        if(udt_._initial_value_present)   _data += QString(" := %1;\n").arg(udt_._initial_value[0]);
        else                                    _data += QString(";\n");
    }break;
    }

    return _data;
}
//-----------------------------------------------------------------------------------
// ***

// *** instances
//
//-----------------------------------------------------------------------------------
QString FbdTranslator::getSTCode_instances(const QDomNode &node_)
{
    QString _text = {};

    T_INSTANCES _INST;
    if(PLCopenXmlParser::parseINSTANCES(node_, &_INST))
        _text = INSTANCES_STgenerator(_INST);

    return _text;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
QString FbdTranslator::INSTANCES_STgenerator(const T_INSTANCES &inst_)
{
    if(!inst_._configuration.size())
        return {};

    QString _data = {};
    _data = QString("CONFIGURATION %1\n").arg(inst_._configuration[0]._name);
    _data += QString(" RESOURCE %1 ON PLC\n").arg(inst_._configuration[0]._resource._name);
    for(auto _i = 0; _i < inst_._configuration[0]._resource._task.size(); _i++)
    {
        _data += QString("   TASK %1(INTERVAL := %2,PRIORITY := %3);\n")
        .arg(inst_._configuration[0]._resource._task[_i]._name)
            .arg(inst_._configuration[0]._resource._task[_i]._interval)
            .arg(inst_._configuration[0]._resource._task[_i]._priority);
    }
    for(auto _i = 0; _i < inst_._configuration[0]._resource._task.size(); _i++)
    {
        for(auto _j = 0; _j < inst_._configuration[0]._resource._task[_i]._pouInstance.size(); _j++)
        {
            _data += QString("   PROGRAM %1 WITH %2 : %3;\n")
            .arg(inst_._configuration[0]._resource._task[_i]._pouInstance[_j]._name)
                .arg(inst_._configuration[0]._resource._task[_i]._name)
                .arg(inst_._configuration[0]._resource._task[_i]._pouInstance[_j]._typeName);
        }
    }
    _data += "  END_RESOURCE\n";
    _data += "END_CONFIGURATION\n";

    return _data;
}
//-----------------------------------------------------------------------------------
// ***

// *** POU
//
//-----------------------------------------------------------------------------------
QString FbdTranslator::getSTCode_pou(const QDomNode &node_)
{


    QString _text = {};

    T_POU _POU;
    if(PLCopenXmlParser::parsePOU(node_, &_POU))
        _text = POU_STgenerator(_POU);

    return _text;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
QString FbdTranslator::POU_STgenerator(const T_POU &pou_)
{
    QString _data = {};

    _m_pou_item.clear();
    _m_pou_execution_order_item.clear();
    _m_pou_generator_item.clear();

    for(auto _i = 0; _i < pou_._body._FBD._item.size(); _i++)
        _m_pou_item.insert(pou_._body._FBD._item[_i]._localId, pou_._body._FBD._item[_i]);

    parseItem(pou_);
    prepareFuncTempVar();
    prepareVarType();
    prepareConnectContinuation();
    prepareVar();
    prepareFunc();
    _data += prepareLocalVar(pou_);
    prepareBlock();

    _m_pou_execution_order_item.clear();
    for(const auto & _it : std::as_const(_m_pou_block_item))
        if(_it._executionOrderId != 0)
        {
            _m_pou_execution_order_item.insert(_it._executionOrderId, _it);
            _m_pou_block_item.remove(_it._localId);
        }

    foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_func_item)
        if(_it._executionOrderId != 0)
        {
            _m_pou_execution_order_item.insert(_it._executionOrderId, _it);
            _m_pou_func_item.remove(_it._localId);
        }

    foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_execution_order_item)
    {
        switch(_it._type)
        {
        case IT_BLOCK:{         Block_STgenerator(_it, _data); }break;
        case IT_FUNCTION:{      Func_STgenerator(_it, _data);  }break;
        case IT_OUTPUT:{        Var_STgenerator(_it, _data);   }break;
        case IT_INPUT_OUTPUT:{  Var_STgenerator(_it, _data);   }break;
        case IT_MAX:
        case IT_COMMENT:
        case IT_INPUT:
        case IT_CONNECTOR:
        case IT_NOT_DEFINED:
        case IT_CONTINUATION:{}break;
        }
    }

    foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_block_item)        Block_STgenerator(_it, _data);
    foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_func_item)         Func_STgenerator(_it, _data);
    foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_in_out_var_item)   Var_STgenerator(_it, _data);
    foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_out_var_item)      Var_STgenerator(_it, _data);

    _data += "\nEND_PROGRAM\n\n";

    return _data;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
QString FbdTranslator::prepareLocalVar(const T_POU &pou_)
{
    QString _data;
    QString _type_name;

    _data = QString("PROGRAM %1\n").arg(pou_._name);
    _data += "  VAR\n";
    for(int _j = 0; _j < (int)pou_._interface._localVars.size(); _j++)
    {
        if(pou_._interface._localVars[_j]._type_name == "string")
            _type_name = pou_._interface._localVars[_j]._type_name.toUpper();
        else
            _type_name = pou_._interface._localVars[_j]._type_name;

        QString _var;
        if(pou_._interface._localVars[_j]._initialValue._simpleValue == "")
        {
            _var = QString("    %1 : %2;\n").arg(pou_._interface._localVars[_j]._name)
            .arg(_type_name);
        }else{
            if(pou_._interface._localVars[_j]._type_name == "string")
            {
                _var = QString("    %1 : %2 := '%3';\n").arg(pou_._interface._localVars[_j]._name)
                           .arg(_type_name)
                           .arg(pou_._interface._localVars[_j]._initialValue._simpleValue);
            }else{
                _var = QString("    %1 : %2 := %3;\n").arg(pou_._interface._localVars[_j]._name)
                           .arg(_type_name)
                           .arg(pou_._interface._localVars[_j]._initialValue._simpleValue);
            }
        }
        _data += _var;
    }
    foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_func_item)
    {
        QString _var_code = QString("    _%1 : %2;\n")
        .arg(_m_pou_func_item[_it._localId]._expression)
            .arg(_m_pou_func_item[_it._localId]._out_var_type);

        _data += _var_code;
    }

    _data += "  END_VAR\n\n";

    return _data;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
QString FbdTranslator::getTypeByVar(const T_POU &pou_, QString _var_name)
{
    QString _type_name;
    for(auto _j = 0; _j < pou_._interface._localVars.size(); _j++)
        if(pou_._interface._localVars[_j]._name == _var_name)
        {
            if(pou_._interface._localVars[_j]._type_name == "string")
                _type_name = pou_._interface._localVars[_j]._type_name.toUpper();
            else
                _type_name = pou_._interface._localVars[_j]._type_name;
        }
    return _type_name;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void FbdTranslator::Block_STgenerator(T_POU_FBD_ITEM_SHORT _block, QString &text_)
{
    QString _data;

    if(_block._inputVariables.isEmpty()) return;

    _data = "  ";
    _data += _block._instanceName + "(";
    for(int _j = 0; _j < _block._inputVariables.size(); _j++)
    {
        _data += _block._inputVariables[_j];
        if((_j + 1) < _block._inputVariables.size()) _data += ", ";
    }
    _data += ");\n";
    text_ += _data;
    if(!_block._outputVariables.isEmpty())
    {
        _data = "  ";
        _data += _block._outputVariables[0] + ";\n";
        text_ += _data;
    }
    if(!_block._inOutVariables.isEmpty())
    {
        _data = "  ";
        _data += _block._inOutVariables[0] + ";\n";
        text_ += _data;
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void FbdTranslator::Func_STgenerator(T_POU_FBD_ITEM_SHORT _func, QString &text_)
{
    QString _data;

    if(_func._inputVariables.isEmpty()) return;

    _data = "  ";
    _data += _func._expression + " := ";
    _data += _func._typeName + "(";

    for(int _j = 0; _j < _func._inputVariables.size(); _j++)
    {
        _data += _func._inputVariables[_j];
        if((_j + 1) < _func._inputVariables.size()) _data += ", ";
    }
    _data += ");\n";
    text_ += _data;

    if(!_func._outputVariables.isEmpty())
    {
        _data = "  ";
        _data += _func._outputVariables[0] + ";\n";
        text_ += _data;
    }
    if(!_func._inOutVariables.isEmpty())
    {
        _data = "  ";
        _data += _func._inOutVariables[0] + ";\n";
        text_ += _data;
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void FbdTranslator::Var_STgenerator(T_POU_FBD_ITEM_SHORT _var, QString &text_)
{
    QString _data;

    if(_var._is_used) return;
    if(_var._inputVariables.isEmpty()) return;

    _data = "  ";
    _data += _var._inputVariables[0] + ";\n";
    text_ += _data;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void FbdTranslator::prepareBlock()
{
    QString _var;
    foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_block_item)
    {
        quint32 _block_id = _it._localId;

        for(int _v = 0; _v < (int)_m_pou_item[_block_id]._inputVariables.size(); _v++)
        {
            if(_m_pou_item[_block_id]._inputVariables[_v]._connection._refLocalId != -1)
            {
                quint32 _var_id = _m_pou_item[_block_id]._inputVariables[_v]._connection._refLocalId;
                _var = _m_pou_item[_block_id]._inputVariables[_v]._formalParameter + " := ";

                if(itemIsBlock(_var_id))
                {
                    _var += _m_pou_block_item[_var_id]._instanceName;
                    _var += ".";
                    _var += _m_pou_item[_block_id]._inputVariables[_v]._connection._formalParameter;
                }else
                    if(itemIsFunc(_var_id))
                    {
                        _var += _m_pou_func_item[_var_id]._expression;
                    }else
                        if(itemIsInVar(_var_id))
                        {
                            _var += _m_pou_in_var_item[_var_id]._expression;
                        }else
                            if(itemIsInOutVar(_var_id))
                            {
                                _var += _m_pou_in_out_var_item[_var_id]._expression;
                            }else
                                if(itemIsContinuation(_var_id))
                                {
                                    if(!_m_pou_continuation_item[_var_id]._inputVariables.isEmpty())
                                        _var += _m_pou_continuation_item[_var_id]._inputVariables[0];
                                }
                _m_pou_block_item[_block_id]._inputVariables.push_back(_var);
            }
        }
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void FbdTranslator::prepareFuncTempVar()
{
    foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_func_item)
    {
        quint32 _func_id = _it._localId;

        QString _var = QString("%1%2_TMP_VAR")
                           .arg(_m_pou_item[_func_id]._typeName)
                           .arg(_func_id);
        _m_pou_func_item[_func_id]._expression = _var;
        _m_pou_item[_func_id]._expression = _var;
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void FbdTranslator::prepareFunc()
{
    QString _var;
    QString _temp_var;
    QString _var_type;

    foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_func_item)
    {
        quint32 _func_id = _it._localId;

        for(int _v = 0; _v < (int)_m_pou_item[_func_id]._inputVariables.size(); _v++)
        {
            if(_m_pou_item[_func_id]._inputVariables[_v]._connection._refLocalId != -1)
            {
                quint32 _var_id = _m_pou_item[_func_id]._inputVariables[_v]._connection._refLocalId;
                _var = "";

                if(itemIsBlock(_var_id))
                {
                    _var += _m_pou_block_item[_var_id]._instanceName;
                    _var += ".";
                    _var += _m_pou_item[_func_id]._inputVariables[_v]._connection._formalParameter;
                }else
                    if(itemIsFunc(_var_id))
                    {
                        _var += _m_pou_func_item[_var_id]._expression;
                    }else
                        if(itemIsInVar(_var_id))
                        {
                            _var += _m_pou_in_var_item[_var_id]._expression;
                        }else
                            if(itemIsOutVar(_var_id))
                            {
                                _var += _m_pou_in_var_item[_var_id]._expression;
                            }else
                                if(itemIsInOutVar(_var_id))
                                {
                                    _var += _m_pou_in_out_var_item[_var_id]._expression;
                                }else
                                    if(itemIsContinuation(_var_id))
                                    {
                                        if(!_m_pou_continuation_item[_var_id]._inputVariables.isEmpty())
                                            _var += _m_pou_continuation_item[_var_id]._inputVariables[0];
                                    }
                _m_pou_func_item[_func_id]._inputVariables.push_back(_var);
            }
        }
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void FbdTranslator::prepareVarType()
{
    QString _var_type;

    foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_out_var_item)
    {
        quint32 _out_var_id = _it._localId;
        quint32 _connect_id = _m_pou_item[_out_var_id]._connection._refLocalId;

        if(itemIsBlock(_connect_id))
        {
        }else
            if(itemIsFunc(_connect_id))
            {
                _m_pou_func_item[_connect_id]._out_var_type = _m_pou_out_var_item[_out_var_id]._out_var_type;
            }else
                if(itemIsInVar(_connect_id))
                {
                }else
                    if(itemIsInOutVar(_connect_id))
                    {
                    }else
                        if(itemIsContinuation(_connect_id))
                        {
                            _m_pou_continuation_item[_connect_id]._out_var_type = _m_pou_out_var_item[_out_var_id]._out_var_type;
                        }
    }
    foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_in_out_var_item)
    {
        quint32 _out_var_id = _it._localId;
        quint32 _connect_id = _m_pou_item[_out_var_id]._connection._refLocalId;

        if(itemIsBlock(_connect_id))
        {
        }else
            if(itemIsFunc(_connect_id))
            {
                _m_pou_func_item[_connect_id]._out_var_type = _m_pou_out_var_item[_out_var_id]._out_var_type;
            }else
                if(itemIsInVar(_connect_id))
                {
                }else
                    if(itemIsInOutVar(_connect_id))
                    {
                    }else
                        if(itemIsContinuation(_connect_id))
                        {
                            _m_pou_continuation_item[_connect_id]._out_var_type = _m_pou_out_var_item[_out_var_id]._out_var_type;
                        }
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void FbdTranslator::prepareVar()
{
    bool _is_connected;
    QString _var;

    foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_out_var_item)
    {
        _is_connected = false;
        quint32 _out_var_id = _it._localId;
        quint32 _connect_id = _m_pou_item[_out_var_id]._connection._refLocalId;
        _var = _m_pou_item[_out_var_id]._expression + " := ";

        if(itemIsBlock(_connect_id))
        {
            _is_connected = true;
            _var += _m_pou_block_item[_connect_id]._instanceName;
            _var += ".";
            _var += _m_pou_item[_out_var_id]._connection._formalParameter;
            _m_pou_block_item[_connect_id]._outputVariables.push_back(_var);
            _m_pou_out_var_item[_out_var_id]._is_used = true;
        }else
            if(itemIsFunc(_connect_id))
            {
                _is_connected = true;
                _var += _m_pou_func_item[_connect_id]._expression;
                _m_pou_func_item[_connect_id]._outputVariables.push_back(_var);
                _m_pou_out_var_item[_out_var_id]._is_used = true;
            }else
                if(itemIsInVar(_connect_id))
                {
                    _is_connected = true;
                    _var += _m_pou_in_var_item[_connect_id]._expression;
                }else
                    if(itemIsInOutVar(_connect_id))
                    {
                        _is_connected = true;
                        _var += _m_pou_in_out_var_item[_connect_id]._expression;
                    }else
                        if(itemIsContinuation(_connect_id))
                        {
                            if(!_m_pou_continuation_item[_connect_id]._inputVariables.isEmpty())
                            {
                                _is_connected = true;
                                _var += _m_pou_continuation_item[_connect_id]._inputVariables[0];
                                quint32 _connect_dev_id = _m_pou_item[_connect_id]._connection._refLocalId;
                                if(itemIsBlock(_connect_dev_id))
                                {
                                    _m_pou_block_item[_connect_dev_id]._outputVariables.push_back(_var);
                                    _m_pou_out_var_item[_out_var_id]._is_used = true;
                                }else
                                    if(itemIsFunc(_connect_dev_id))
                                    {
                                        _m_pou_func_item[_connect_dev_id]._outputVariables.push_back(_var);
                                        _m_pou_out_var_item[_out_var_id]._is_used = true;
                                    }
                            }
                        }
        if(_is_connected)
            _m_pou_out_var_item[_out_var_id]._inputVariables.push_back(_var);
    }

    foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_in_out_var_item)
    {
        _is_connected = false;
        quint32 _out_var_id = _it._localId;
        quint32 _connect_id = _m_pou_item[_out_var_id]._connection._refLocalId;
        _var = _m_pou_item[_out_var_id]._expression + " := ";

        if(itemIsBlock(_connect_id))
        {
            _is_connected = true;
            _var += _m_pou_block_item[_connect_id]._instanceName;
            _var += ".";
            _var += _m_pou_item[_out_var_id]._connection._formalParameter;
            _m_pou_block_item[_connect_id]._inOutVariables.push_back(_var);
            _m_pou_in_out_var_item[_out_var_id]._is_used = true;
        }else
            if(itemIsFunc(_connect_id))
            {
                _is_connected = true;
                _var += _m_pou_func_item[_connect_id]._expression;
                _m_pou_func_item[_connect_id]._inOutVariables.push_back(_var);
                _m_pou_in_out_var_item[_out_var_id]._is_used = true;
            }else
                if(itemIsInVar(_connect_id))
                {
                    _is_connected = true;
                    _var += _m_pou_in_var_item[_connect_id]._expression;
                }else
                    if(itemIsInOutVar(_connect_id))
                    {
                        _is_connected = true;
                        _var += _m_pou_in_out_var_item[_connect_id]._expression;
                    }else
                        if(itemIsContinuation(_connect_id))
                        {
                            if(!_m_pou_continuation_item[_connect_id]._inputVariables.isEmpty())
                            {
                                _is_connected = true;
                                _var += _m_pou_continuation_item[_connect_id]._inputVariables[0];
                            }
                        }
        if(_is_connected)
            _m_pou_in_out_var_item[_out_var_id]._inputVariables.push_back(_var);
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
quint32 FbdTranslator::linkConnect(quint32 _connect_id)
{
    quint32 _id = 0;
    foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_continuation_item)
        if(_it._name == _m_pou_connect_item[_connect_id]._name)
        {
            _id = _it._localId;
            break;
        }
    return _id;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void FbdTranslator::prepareConnectContinuation()
{
    QString _var;
    foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_connect_item)
    {
        qint32 _connect_id = _it._localId;
        switch(_m_pou_item[_m_pou_item[_connect_id]._connection._refLocalId]._type)
        {
        case IT_BLOCK:{
            _var = QString("%1.%2")
            .arg(_m_pou_item[_m_pou_item[_connect_id]._connection._refLocalId]._instanceName)
                .arg(_m_pou_item[_connect_id]._connection._formalParameter);
            _m_pou_connect_item[_connect_id]._out_var_type = _m_pou_block_item[_m_pou_item[_connect_id]._connection._refLocalId]._out_var_type;
        }break;
        case IT_FUNCTION:{
            _var = QString("%1")
            .arg(_m_pou_item[_m_pou_item[_connect_id]._connection._refLocalId]._expression);
            _m_pou_connect_item[_connect_id]._out_var_type = _m_pou_func_item[_m_pou_item[_connect_id]._connection._refLocalId]._out_var_type;
        }break;
        case IT_INPUT:{
            _var = QString("%1")
            .arg(_m_pou_item[_m_pou_item[_connect_id]._connection._refLocalId]._expression);
            _m_pou_connect_item[_connect_id]._out_var_type = _m_pou_in_var_item[_m_pou_item[_connect_id]._connection._refLocalId]._out_var_type;
        }break;
        case IT_OUTPUT:{
            _var = QString("%1")
            .arg(_m_pou_item[_m_pou_item[_connect_id]._connection._refLocalId]._expression);
            _m_pou_connect_item[_connect_id]._out_var_type = _m_pou_out_var_item[_m_pou_item[_connect_id]._connection._refLocalId]._out_var_type;
        }break;
        case IT_INPUT_OUTPUT:{
            _var = QString("%1")
            .arg(_m_pou_item[_m_pou_item[_connect_id]._connection._refLocalId]._expression);
            _m_pou_connect_item[_connect_id]._out_var_type = _m_pou_in_out_var_item[_m_pou_item[_connect_id]._connection._refLocalId]._out_var_type;
        }break;
        case IT_MAX:
        case IT_NOT_DEFINED:
        case IT_COMMENT:
        case IT_CONNECTOR:
        case IT_CONTINUATION:{}break;
        }
        _m_pou_connect_item[_connect_id]._outputVariables.push_back(_var);
        quint32 _continuation_id = linkConnect(_connect_id);
        if(_continuation_id != 0)
        {
            _m_pou_continuation_item[_continuation_id]._inputVariables.push_back(_var);
            _m_pou_connect_item[_connect_id]._out_var_type = _m_pou_continuation_item[_continuation_id]._out_var_type;
            _m_pou_item[_continuation_id]._connection._refLocalId = _m_pou_item[_connect_id]._connection._refLocalId;
            //            _m_pou_connect_item[_connect_id]._link = _continuation_id;
            //            _m_pou_continuation_item[_continuation_id]._link = _connect_id;
        }
    }

    foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_continuation_item)
    {
        qint32 _connect_id = _it._localId;
        switch(_m_pou_item[_m_pou_item[_connect_id]._connection._refLocalId]._type)
        {
        case IT_BLOCK:{
        }break;
        case IT_FUNCTION:{
            _m_pou_func_item[_m_pou_item[_connect_id]._connection._refLocalId]._out_var_type = _it._out_var_type;
        }break;
        case IT_INPUT:{
        }break;
        case IT_OUTPUT:{
        }break;
        case IT_INPUT_OUTPUT:{
        }break;
        case IT_MAX:
        case IT_NOT_DEFINED:
        case IT_COMMENT:
        case IT_CONNECTOR:
        case IT_CONTINUATION:{}break;
        }
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void FbdTranslator::parseItem(const T_POU &pou_)
{
    T_POU_FBD_ITEM_SHORT _item;

    _m_pou_block_item.clear();
    _m_pou_func_item.clear();
    _m_pou_in_var_item.clear();
    _m_pou_out_var_item.clear();
    _m_pou_in_out_var_item.clear();
    _m_pou_connect_item.clear();
    _m_pou_continuation_item.clear();

    for(int _i = 0; _i < (int)pou_._body._FBD._item.size(); _i++)
        if(pou_._body._FBD._item[_i]._type == IT_BLOCK)
        {
            _item._type                 = pou_._body._FBD._item[_i]._type;
            _item._localId              = pou_._body._FBD._item[_i]._localId;
            _item._executionOrderId     = pou_._body._FBD._item[_i]._executionOrderId;
            _item._negated              = pou_._body._FBD._item[_i]._negated;
            _item._expression           = pou_._body._FBD._item[_i]._expression;
            _item._name                 = pou_._body._FBD._item[_i]._name;
            _item._typeName             = pou_._body._FBD._item[_i]._typeName;
            _item._instanceName         = pou_._body._FBD._item[_i]._instanceName;
            _item._out_var_type         = "BOOL";
            _item._inOutVariables.clear();
            _item._inputVariables.clear();
            _item._outputVariables.clear();
            _m_pou_block_item.insert(_item._localId, _item);
        }

    for(int _i = 0; _i < (int)pou_._body._FBD._item.size(); _i++)
        if(pou_._body._FBD._item[_i]._type == IT_FUNCTION)
        {
            _item._type                 = pou_._body._FBD._item[_i]._type;
            _item._localId              = pou_._body._FBD._item[_i]._localId;
            _item._executionOrderId     = pou_._body._FBD._item[_i]._executionOrderId;
            _item._negated              = pou_._body._FBD._item[_i]._negated;
            _item._expression           = pou_._body._FBD._item[_i]._expression;
            _item._name                 = pou_._body._FBD._item[_i]._name;
            _item._typeName             = pou_._body._FBD._item[_i]._typeName;
            _item._instanceName         = pou_._body._FBD._item[_i]._instanceName;
            _item._out_var_type         = "";
            _item._inOutVariables.clear();
            _item._inputVariables.clear();
            _item._outputVariables.clear();
            _m_pou_func_item.insert(_item._localId, _item);
        }

    for(int _i = 0; _i < (int)pou_._body._FBD._item.size(); _i++)
        if(pou_._body._FBD._item[_i]._type == IT_INPUT)
        {
            _item._type                 = pou_._body._FBD._item[_i]._type;
            _item._localId              = pou_._body._FBD._item[_i]._localId;
            _item._executionOrderId     = pou_._body._FBD._item[_i]._executionOrderId;
            _item._negated              = pou_._body._FBD._item[_i]._negated;
            _item._expression           = pou_._body._FBD._item[_i]._expression;
            _item._name                 = pou_._body._FBD._item[_i]._name;
            _item._typeName             = pou_._body._FBD._item[_i]._typeName;
            _item._instanceName         = pou_._body._FBD._item[_i]._instanceName;
            _item._out_var_type         = getTypeByVar(pou_, _item._expression);
            _item._inOutVariables.clear();
            _item._inputVariables.clear();
            _item._outputVariables.clear();
            _m_pou_in_var_item.insert(_item._localId, _item);
        }

    for(int _i = 0; _i < (int)pou_._body._FBD._item.size(); _i++)
        if(pou_._body._FBD._item[_i]._type == IT_OUTPUT)
        {
            _item._type                 = pou_._body._FBD._item[_i]._type;
            _item._localId              = pou_._body._FBD._item[_i]._localId;
            _item._executionOrderId     = pou_._body._FBD._item[_i]._executionOrderId;
            _item._negated              = pou_._body._FBD._item[_i]._negated;
            _item._expression           = pou_._body._FBD._item[_i]._expression;
            _item._name                 = pou_._body._FBD._item[_i]._name;
            _item._typeName             = pou_._body._FBD._item[_i]._typeName;
            _item._instanceName         = pou_._body._FBD._item[_i]._instanceName;
            _item._out_var_type         = getTypeByVar(pou_, _item._expression);
            _item._inOutVariables.clear();
            _item._inputVariables.clear();
            _item._outputVariables.clear();
            _m_pou_out_var_item.insert(_item._localId, _item);
        }

    for(int _i = 0; _i < (int)pou_._body._FBD._item.size(); _i++)
        if(pou_._body._FBD._item[_i]._type == IT_INPUT_OUTPUT)
        {
            _item._type                 = pou_._body._FBD._item[_i]._type;
            _item._localId              = pou_._body._FBD._item[_i]._localId;
            _item._executionOrderId     = pou_._body._FBD._item[_i]._executionOrderId;
            _item._negated              = pou_._body._FBD._item[_i]._negated;
            _item._expression           = pou_._body._FBD._item[_i]._expression;
            _item._name                 = pou_._body._FBD._item[_i]._name;
            _item._typeName             = pou_._body._FBD._item[_i]._typeName;
            _item._instanceName         = pou_._body._FBD._item[_i]._instanceName;
            _item._out_var_type         = getTypeByVar(pou_, _item._expression);
            _item._inOutVariables.clear();
            _item._inputVariables.clear();
            _item._outputVariables.clear();
            _m_pou_in_out_var_item.insert(_item._localId, _item);
        }

    for(int _i = 0; _i < (int)pou_._body._FBD._item.size(); _i++)
        if(pou_._body._FBD._item[_i]._type == IT_CONNECTOR)
        {
            _item._type                 = pou_._body._FBD._item[_i]._type;
            _item._localId              = pou_._body._FBD._item[_i]._localId;
            _item._executionOrderId     = pou_._body._FBD._item[_i]._executionOrderId;
            _item._negated              = pou_._body._FBD._item[_i]._negated;
            _item._expression           = pou_._body._FBD._item[_i]._expression;
            _item._name                 = pou_._body._FBD._item[_i]._name;
            _item._typeName             = pou_._body._FBD._item[_i]._typeName;
            _item._instanceName         = pou_._body._FBD._item[_i]._instanceName;
            _item._inOutVariables.clear();
            _item._inputVariables.clear();
            _item._outputVariables.clear();
            _m_pou_connect_item.insert(_item._localId, _item);
        }

    for(int _i = 0; _i < (int)pou_._body._FBD._item.size(); _i++)
        if(pou_._body._FBD._item[_i]._type == IT_CONTINUATION)
        {
            _item._type                 = pou_._body._FBD._item[_i]._type;
            _item._localId              = pou_._body._FBD._item[_i]._localId;
            _item._executionOrderId     = pou_._body._FBD._item[_i]._executionOrderId;
            _item._negated              = pou_._body._FBD._item[_i]._negated;
            _item._expression           = pou_._body._FBD._item[_i]._expression;
            _item._name                 = pou_._body._FBD._item[_i]._name;
            _item._typeName             = pou_._body._FBD._item[_i]._typeName;
            _item._instanceName         = pou_._body._FBD._item[_i]._instanceName;
            _item._inOutVariables.clear();
            _item._inputVariables.clear();
            _item._outputVariables.clear();
            _m_pou_continuation_item.insert(_item._localId, _item);
        }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool FbdTranslator::itemIsBlock(quint32 _id)
{
    if(_m_pou_block_item.find(_id) != _m_pou_block_item.end())
        return true;
    return false;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool FbdTranslator::itemIsFunc(quint32 _id)
{
    if(_m_pou_func_item.find(_id) != _m_pou_func_item.end())
        return true;
    return false;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool FbdTranslator::itemIsInVar(quint32 _id)
{
    if(_m_pou_in_var_item.find(_id) != _m_pou_in_var_item.end())
        return true;
    return false;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool FbdTranslator::itemIsOutVar(quint32 _id)
{
    if(_m_pou_out_var_item.find(_id) != _m_pou_out_var_item.end())
        return true;
    return false;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool FbdTranslator::itemIsInOutVar(quint32 _id)
{
    if(_m_pou_in_out_var_item.find(_id) != _m_pou_in_out_var_item.end())
        return true;
    return false;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool FbdTranslator::itemIsConnect(quint32 _id)
{
    if(_m_pou_connect_item.find(_id) != _m_pou_connect_item.end())
        return true;
    return false;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool FbdTranslator::itemIsContinuation(quint32 _id)
{
    if(_m_pou_continuation_item.find(_id) != _m_pou_continuation_item.end())
        return true;
    return false;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
