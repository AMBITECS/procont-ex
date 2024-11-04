#include "TranslatorLD.h"

TranslatorLD::TranslatorLD() {}

// *** POU
//
//-----------------------------------------------------------------------------------
void TranslatorLD::Code_STgenerator(T_POU pou_, QString &text_)
{
    _m_item.clear();
    _m_execution_order_item.clear();
    _m_generator_item.clear();

    for(int _i = 0; _i < (int)pou_._body._LD._item.size(); _i++)
        _m_item.insert(pou_._body._LD._item[_i]._localId, pou_._body._LD._item[_i]);

    parseItem(&pou_);
    prepareConnectContinuation();
    prepareModificators();
    prepareFuncTempVar();
    prepareVarType();
    prepareVar();
    prepareFunc();
    AllVar_STgenerator(&pou_, text_);

    if(!_m_func_item.empty() || !_m_contact_modificator_item.isEmpty() || !_m_coil_modificator_item.isEmpty())
    {
        text_ += "  VAR\n";

        foreach(T_POU_LD_ITEM _it, _m_func_item)
            text_ += QString("    %1 : %2;\n").arg(_m_func_item[_it._localId]._expression, _m_func_item[_it._localId]._return_type);

        foreach(T_MODIFICATOR _it, _m_contact_modificator_item)
            if(_it._name != "")
                text_ += QString("    %1 : %2;\n").arg(_it._name, _it._type);

        foreach(T_MODIFICATOR _it, _m_coil_modificator_item)
            if(_it._name != "")
                text_ += QString("    %1 : %2;\n").arg(_it._name, _it._type);

        text_ += "  END_VAR\n\n";
    }

    prepareBlock();

    foreach(T_MODIFICATOR _it, _m_contact_modificator_item)
        text_ += QString("  %1;\n").arg(_it._code);
    foreach(T_MODIFICATOR _it, _m_coil_modificator_item)
        text_ += QString("  %1;\n").arg(_it._code);

    _m_execution_order_item.clear();
    foreach(T_POU_LD_ITEM _it, _m_block_item)
        if(_it._executionOrderId != 0)
        {
            _m_execution_order_item.insert(_it._executionOrderId, _it);
            _m_block_item.remove(_it._localId);
        }

    foreach(T_POU_LD_ITEM _it, _m_func_item)
        if(_it._executionOrderId != 0)
        {
            _m_execution_order_item.insert(_it._executionOrderId, _it);
            _m_func_item.remove(_it._localId);
        }

    foreach(T_POU_LD_ITEM _it, _m_execution_order_item)
    {
        switch(_it._type)
        {
        case IT_LD_BLOCK:{         Block_STcode(_it, text_); }break;
        case IT_LD_FUNCTION:{      Func_STcode(_it, text_);  }break;
        case IT_LD_OUTPUT:{        Var_STcode(_it, text_);   }break;
        case IT_LD_INPUT_OUTPUT:{  Var_STcode(_it, text_);   }break;
        case IT_LD_MAX:
        case IT_LD_COMMENT:
        case IT_LD_INPUT:
        case IT_LD_CONNECTOR:
        case IT_LD_NOT_DEFINED:
        case IT_LD_CONTINUATION:
        case IT_LD_CONTACT:
        case IT_LD_COIL:
        case IT_LD_LEFT_POWER_RAIL:
        case IT_LD_RIGHT_POWER_RAIL:{}break;
        }
    }

    foreach(T_POU_LD_ITEM _it, _m_block_item)        Block_STcode(_it, text_);
    foreach(T_POU_LD_ITEM _it, _m_func_item)         Func_STcode(_it, text_);
    foreach(T_POU_LD_ITEM _it, _m_in_out_var_item)   Var_STcode(_it, text_);
    foreach(T_POU_LD_ITEM _it, _m_out_var_item)      Var_STcode(_it, text_);

    switch(pou_._pouType)
    {
    case PT_FUNCTION:{          text_ += "END_FUNCTION\n\n";        }break;
    case PT_FUNCTION_BLOCK:{    text_ += "END_FUNCTION_BLOCK\n\n";  }break;
    case PT_PROGRAMM:{          text_ += "END_PROGRAM\n\n";         }break;
    case PT_MAX:{}break;
    case PT_NOT_DEFINED:{}break;
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void TranslatorLD::Code_STgenerator(T_POU_BODY_LD _ld, QString &text_)
{
    _m_item.clear();
    _m_execution_order_item.clear();
    _m_generator_item.clear();

    for(int _i = 0; _i < (int)_ld._item.size(); _i++)
        _m_item.insert(_ld._item[_i]._localId, _ld._item[_i]);

    parseItem(&_ld);
    prepareConnectContinuation();
    prepareModificators();
    prepareFuncTempVar();
    prepareVarType();
    prepareVar();
    prepareFunc();
//    AllVar_STgenerator(&_ld, text_);

    if(!_m_func_item.empty() || !_m_contact_modificator_item.isEmpty() || !_m_coil_modificator_item.isEmpty())
    {
        text_ += "  VAR\n";

        foreach(T_POU_LD_ITEM _it, _m_func_item)
            text_ += QString("    %1 : %2;\n").arg(_m_func_item[_it._localId]._expression, _m_func_item[_it._localId]._return_type);

        foreach(T_MODIFICATOR _it, _m_contact_modificator_item)
            text_ += QString("    %1 : %2;\n").arg(_it._name, _it._type);

        foreach(T_MODIFICATOR _it, _m_coil_modificator_item)
            text_ += QString("    %1 : %2;\n").arg(_it._name, _it._type);

        text_ += "  END_VAR\n\n";
    }

    prepareBlock();

    foreach(T_MODIFICATOR _it, _m_contact_modificator_item)
        text_ += QString("  %1;\n").arg(_it._code);
    foreach(T_MODIFICATOR _it, _m_coil_modificator_item)
        text_ += QString("  %1;\n").arg(_it._code);

    _m_execution_order_item.clear();
    foreach(T_POU_LD_ITEM _it, _m_block_item)
        if(_it._executionOrderId != 0)
        {
            _m_execution_order_item.insert(_it._executionOrderId, _it);
            _m_block_item.remove(_it._localId);
        }

    foreach(T_POU_LD_ITEM _it, _m_func_item)
        if(_it._executionOrderId != 0)
        {
            _m_execution_order_item.insert(_it._executionOrderId, _it);
            _m_func_item.remove(_it._localId);
        }

    foreach(T_POU_LD_ITEM _it, _m_execution_order_item)
    {
        switch(_it._type)
        {
        case IT_LD_BLOCK:{         Block_STcode(_it, text_); }break;
        case IT_LD_FUNCTION:{      Func_STcode(_it, text_);  }break;
        case IT_LD_OUTPUT:{        Var_STcode(_it, text_);   }break;
        case IT_LD_INPUT_OUTPUT:{  Var_STcode(_it, text_);   }break;
        case IT_LD_MAX:
        case IT_LD_COMMENT:
        case IT_LD_INPUT:
        case IT_LD_CONNECTOR:
        case IT_LD_NOT_DEFINED:
        case IT_LD_CONTINUATION:
        case IT_LD_CONTACT:
        case IT_LD_COIL:
        case IT_LD_LEFT_POWER_RAIL:
        case IT_LD_RIGHT_POWER_RAIL:{}break;
        }
    }

    foreach(T_POU_LD_ITEM _it, _m_block_item)        Block_STcode(_it, text_);
    foreach(T_POU_LD_ITEM _it, _m_func_item)         Func_STcode(_it, text_);
    foreach(T_POU_LD_ITEM _it, _m_in_out_var_item)   Var_STcode(_it, text_);
    foreach(T_POU_LD_ITEM _it, _m_out_var_item)      Var_STcode(_it, text_);
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void TranslatorLD::Block_STcode(T_POU_LD_ITEM _block, QString &text_)
{
    text_ += "  ";
    text_ += _block._instanceName + "(";
    for(int _j = 0; _j < _block._inputVar.size(); _j++)
    {
        text_ += _block._inputVar[_j]._name;
        if((_j + 1) < _block._inputVar.size()) text_ += ", ";
    }
    text_ += ");\n";

    foreach(T_POU_LD_ITEM _it, _m_out_var_item)
        if(!_it._is_used)
        {
            if(!_it._point_in.empty())
                for(int _i = 0; _i < _it._point_in[0]._connection.size(); _i++)
                    if(_it._point_in[0]._connection[_i]._refLocalId == _block._localId)
                    {
                        text_ += QString("  %1;\n").arg(_it._inputVar[0]._name);
                        _m_out_var_item[_it._localId]._is_used = true;
                    }
        }

    foreach(T_POU_LD_ITEM _it, _m_in_out_var_item)
        if(!_it._is_used)
        {
            if(!_it._point_in.empty())
                for(int _i = 0; _i < _it._point_in[0]._connection.size(); _i++)
                    if(_it._point_in[0]._connection[_i]._refLocalId == _block._localId)
                    {
                        text_ += QString("  %1;\n").arg(_it._inputVar[0]._name);
                        _m_in_out_var_item[_it._localId]._is_used = true;
                    }
        }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void TranslatorLD::Func_STcode(T_POU_LD_ITEM _func, QString &text_)
{
    text_ += "  ";
    text_ += _func._expression + " := ";
    text_ += _func._typeName + "(";

    for(int _j = 0; _j < _func._inputVar.size(); _j++)
    {
        text_ += _func._inputVar[_j]._name;
        if((_j + 1) < _func._inputVar.size()) text_ += ", ";
    }
    text_ += ");\n";

    foreach(T_POU_LD_ITEM _it, _m_out_var_item)
        if(!_it._is_used)
        {
            if(!_it._point_in.empty())
                for(int _i = 0; _i < _it._point_in[0]._connection.size(); _i++)
                    if(_it._point_in[0]._connection[_i]._refLocalId == _func._localId)
                    {
                        text_ += QString("  %1;\n").arg(_it._inputVar[0]._name);
                        _m_out_var_item[_it._localId]._is_used = true;
                    }
        }

    foreach(T_POU_LD_ITEM _it, _m_in_out_var_item)
        if(!_it._is_used)
        {
            if(!_it._point_in.empty())
                for(int _i = 0; _i < _it._point_in[0]._connection.size(); _i++)
                    if(_it._point_in[0]._connection[_i]._refLocalId == _func._localId)
                    {
                        text_ += QString("  %1;\n").arg(_it._inputVar[0]._name);
                        _m_in_out_var_item[_it._localId]._is_used = true;
                    }
        }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void TranslatorLD::Var_STcode(T_POU_LD_ITEM _var, QString &text_)
{
    QString _code = "";
    if(_var._is_used) return;
    if(_var._inputVar.isEmpty()) return;

    _code += QString("  %1;\n").arg(_var._inputVar[0]._name);

    text_ += _code;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void TranslatorLD::prepareBlock()
{
    foreach(T_POU_LD_ITEM _it, _m_block_item)
    {
        quint32 _block_id = _it._localId;

        for(int _v = 0; _v < (int)_m_block_item[_block_id]._inputVariables.size(); _v++)
        {
            if(_m_block_item[_block_id]._inputVariables[_v]._connection._refLocalId != -1)
            {
                T_CONNECTION_VAR _var;
                quint32 _var_id = _m_block_item[_block_id]._inputVariables[_v]._connection._refLocalId;
                _var._name = _m_block_item[_block_id]._inputVariables[_v]._formalParameter + " := ";

                quint64 _id = _var_id;
                do{
                    T_CONNECTION_VAR _temp_var;
                    _id = checkBlockConnectionChain(_id, &_temp_var);
                    if(_temp_var._name != "") _var._name += _temp_var._name;
                    if((_id != 0) && (_temp_var._name != "")) _var._name += " AND ";
                    _var._id = _temp_var._id;
                    _var._type = _temp_var._type;
                }while(_id != 0);
                _m_block_item[_block_id]._inputVar.push_back(_var);
            }
        }
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
qint32 TranslatorLD::checkBlockConnectionChain(qint32 _var_id, T_CONNECTION_VAR *_var)
{
    quint64 _result = 0;

    if(itemIsBlock(_var_id))
    {
        _var->_name += _m_block_item[_var_id]._instanceName;
        _var->_name += ".";
        _var->_name += _m_item[_var_id]._outputVariables[0]._formalParameter;
        _var->_id = _var_id;
        _var->_type = "BOOL";
    }else
    if(itemIsFunc(_var_id))
    {
        _var->_name += _m_func_item[_var_id]._expression;
        _var->_id = _var_id;
        _var->_type = _m_func_item[_var_id]._return_type;
    }else
    if(itemIsInVar(_var_id))
    {
        _var->_name += _m_in_var_item[_var_id]._expression;
        _var->_id = _var_id;
        _var->_type = _m_in_var_item[_var_id]._return_type;
    }else
    if(itemIsInOutVar(_var_id))
    {
        _var->_name += _m_in_out_var_item[_var_id]._expression;
        _var->_id = _var_id;
        _var->_type = _m_in_out_var_item[_var_id]._return_type;
    }else
    if(itemIsContinuation(_var_id))
    {
        if(!_m_continuation_item[_var_id]._inputVar.isEmpty())
        {
            _var->_name += _m_continuation_item[_var_id]._inputVar[0]._name;
            _var->_id = _var_id;
            _var->_type = _m_continuation_item[_var_id]._inputVar[0]._type;
            _result = _m_continuation_item[_var_id]._inputVar[0]._id;
            if(itemIsLeftPowerRail(_result))_result = 0;
            if(itemIsRightPowerRail(_result))_result = 0;
        }
    }else
    if(itemIsContact(_var_id))
    {
        _var->_name += _m_contact_item[_var_id]._expression;
        _var->_id = _var_id;
        _var->_is_modificator = itemIsModifContact(_var_id);
//                    _var._type = _m_in_out_var_item[_var_id]._return_type;
        _result = _m_contact_item[_var_id]._point_in[0]._connection[0]._refLocalId;
        if(itemIsLeftPowerRail(_result))_result = 0;
        if(itemIsRightPowerRail(_result))_result = 0;
    }else
    if(itemIsCoil(_var_id))
    {
        _var->_name += ""; //_m_coil_item[_var_id]._expression;
        _var->_id = _var_id;
        _var->_is_modificator = itemIsModifCoil(_var_id);
        //                    _var._type = _m_in_out_var_item[_var_id]._return_type;
        _result = _m_coil_item[_var_id]._point_in[0]._connection[0]._refLocalId;
    }else
    if(itemIsLeftPowerRail(_var_id))
    {
        _var->_name += "TRUE";
    }else
    if(itemIsRightPowerRail(_var_id))
    {
        _var->_name += "FALSE";
    }
    return _result;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void TranslatorLD::prepareFuncTempVar()
{
    foreach(T_POU_LD_ITEM _it, _m_func_item)
    {
        QString _var = QString("%1%2_TMP_VAR")
                           .arg(_m_func_item[_it._localId]._typeName)
                           .arg(_it._localId);
        _m_func_item[_it._localId]._expression = _var;
        _m_item[_it._localId]._expression = _var;
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void TranslatorLD::prepareFunc()
{
    //------------------------------------------------------
    //------------------------------------------------------
    //------------------------------------------------------
    foreach(T_POU_LD_ITEM _func, _m_func_item)
    {
        foreach(T_POU_LD_ITEM _it, _m_out_var_item)
            if(!_it._point_in.empty())
                for(int _i = 0; _i < _it._point_in[0]._connection.size(); _i++)
                    if(_it._point_in[0]._connection[_i]._refLocalId == _func._localId)
                    {
                        _m_func_item[_func._localId]._return_type = _it._return_type;
                        break;
                    }

        foreach(T_POU_LD_ITEM _it, _m_in_out_var_item)
            if(!_it._point_in.empty())
                for(int _i = 0; _i < _it._point_in[0]._connection.size(); _i++)
                    if(_it._point_in[0]._connection[_i]._refLocalId == _func._localId)
                    {
                        _m_func_item[_func._localId]._return_type = _it._return_type;
                        break;
                    }
    }
    //------------------------------------------------------
    //------------------------------------------------------
    //------------------------------------------------------

    foreach(T_POU_LD_ITEM _it, _m_func_item)
    {
        quint32 _func_id = _it._localId;

        for(int _v = 0; _v < (int)_m_func_item[_func_id]._inputVariables.size(); _v++)
        {
            if(_m_func_item[_func_id]._inputVariables[_v]._connection._refLocalId != -1)
            {
                quint32 _var_id = _m_func_item[_func_id]._inputVariables[_v]._connection._refLocalId;
                T_CONNECTION_VAR _var;

                quint64 _id = _var_id;
                do{
                    T_CONNECTION_VAR _temp_var;
                    _id = checkFuncConnectionChain(_id, &_temp_var);
                    if(_temp_var._name != "") _var._name += _temp_var._name;
                    if((_id != 0) && (_temp_var._name != "")) _var._name += " AND ";
                    _var._id = _temp_var._id;
                    _var._type = _temp_var._type;
                    //---------------------------------------------------
                    if(_m_func_item[_it._localId]._return_type == "")
                        _m_func_item[_it._localId]._return_type = _var._type;
                    //---------------------------------------------------
                }while(_id != 0);
                _m_func_item[_func_id]._inputVar.push_back(_var);
            }
        }
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
qint32 TranslatorLD::checkFuncConnectionChain(qint32 _var_id, T_CONNECTION_VAR *_var)
{
    quint64 _result = 0;

    if(itemIsBlock(_var_id))
    {
        _var->_name += _m_block_item[_var_id]._instanceName;
        _var->_name += ".";
        _var->_name += _m_item[_var_id]._outputVariables[0]._formalParameter;
        _var->_id = _var_id;
        _var->_type = "BOOL";
    }else
    if(itemIsFunc(_var_id))
    {
        _var->_name += _m_func_item[_var_id]._expression;
        _var->_id = _var_id;
        _var->_type = _m_func_item[_var_id]._return_type;
    }else
    if(itemIsInVar(_var_id))
    {
        _var->_name += _m_in_var_item[_var_id]._expression;
        _var->_id = _var_id;
        _var->_type = _m_in_var_item[_var_id]._return_type;
    }else
    if(itemIsInOutVar(_var_id))
    {
        _var->_name += _m_in_out_var_item[_var_id]._expression;
        _var->_id = _var_id;
        _var->_type = _m_in_out_var_item[_var_id]._return_type;
    }else
    if(itemIsContinuation(_var_id))
    {
        if(!_m_continuation_item[_var_id]._inputVar.isEmpty())
        {
            _var->_name += _m_continuation_item[_var_id]._inputVar[0]._name;
            _var->_id = _var_id;
            _var->_type = _m_continuation_item[_var_id]._inputVar[0]._type;
            _result = _m_continuation_item[_var_id]._inputVar[0]._id;
            if(itemIsLeftPowerRail(_result))_result = 0;
            if(itemIsRightPowerRail(_result))_result = 0;
        }
    }else
    if(itemIsContact(_var_id))
    {
        _var->_name += _m_contact_item[_var_id]._expression;
        _var->_id = _var_id;
        _var->_is_modificator = itemIsModifContact(_var_id);
        //                    _var._type = _m_in_out_var_item[_var_id]._return_type;
        _result = _m_contact_item[_var_id]._point_in[0]._connection[0]._refLocalId;
        if(itemIsLeftPowerRail(_result))_result = 0;
        if(itemIsRightPowerRail(_result))_result = 0;
    }else
    if(itemIsCoil(_var_id))
    {
        _var->_name += ""; //_m_coil_item[_var_id]._expression;
        _var->_id = _var_id;
        _var->_is_modificator = itemIsModifCoil(_var_id);
        //                    _var._type = _m_in_out_var_item[_var_id]._return_type;
        _result = _m_coil_item[_var_id]._point_in[0]._connection[0]._refLocalId;
    }else
    if(itemIsLeftPowerRail(_var_id))
    {
        _var->_name += "TRUE";
    }else
    if(itemIsRightPowerRail(_var_id))
    {
        _var->_name += "FALSE";
    }
    return _result;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void TranslatorLD::prepareVarType()
{
    foreach(T_POU_LD_ITEM _it, _m_out_var_item)
    {
        quint32 _var_id = _it._localId;
        quint32 _connect_id = _m_out_var_item[_var_id]._connection._refLocalId;

        if(itemIsBlock(_connect_id))
        {
        }else
        if(itemIsFunc(_connect_id))
        {
            _m_func_item[_connect_id]._return_type = _m_out_var_item[_var_id]._return_type;
        }else
        if(itemIsInVar(_connect_id))
        {
        }else
        if(itemIsInOutVar(_connect_id))
        {
        }else
        if(itemIsContinuation(_connect_id))
        {
            _m_continuation_item[_connect_id]._return_type = _m_out_var_item[_var_id]._return_type;
        }else
        if(itemIsContact(_connect_id))
        {
        }else
        if(itemIsLeftPowerRail(_connect_id))
        {
        }else
        if(itemIsRightPowerRail(_connect_id))
        {
        }else
        if(itemIsCoil(_connect_id))
        {
        }
    }
    foreach(T_POU_LD_ITEM _it, _m_in_out_var_item)
    {
        quint32 _var_id = _it._localId;
        quint32 _connect_id = _m_in_out_var_item[_var_id]._connection._refLocalId;

        if(itemIsBlock(_connect_id))
        {
        }else
        if(itemIsFunc(_connect_id))
        {
            _m_func_item[_connect_id]._return_type = _m_in_out_var_item[_var_id]._return_type;
        }else
        if(itemIsInVar(_connect_id))
        {
        }else
        if(itemIsInOutVar(_connect_id))
        {
        }else
        if(itemIsContinuation(_connect_id))
        {
            _m_continuation_item[_connect_id]._return_type = _m_in_out_var_item[_var_id]._return_type;
        }else
        if(itemIsContact(_connect_id))
        {
        }else
        if(itemIsLeftPowerRail(_connect_id))
        {
        }else
        if(itemIsRightPowerRail(_connect_id))
        {
        }else
        if(itemIsCoil(_connect_id))
        {
        }
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void TranslatorLD::prepareVar()
{
    foreach(T_POU_LD_ITEM _it, _m_out_var_item)
    {
        qint32 _out_var_id = _it._localId;

        if(!_it._point_in.empty())
            if(!_it._point_in[0]._connection.empty())
            {
                T_CONNECTION_VAR _var;

                _var._name = _m_out_var_item[_out_var_id]._expression + " := ";
                _var._type = _m_out_var_item[_out_var_id]._return_type;

                for(int _i = 0; _i < _it._point_in[0]._connection.size(); _i++)
                {
                    qint32 _id = _m_out_var_item[_out_var_id]._point_in[0]._connection[_i]._refLocalId;
                    do{
                        T_CONNECTION_VAR _temp_var;
                        _id = checkVarConnectionChain(_id, &_temp_var);
                        if(_temp_var._name != "") _var._name += _temp_var._name;
                        if((_id != 0) && (_temp_var._name != "")) _var._name += " OR ";
                        _var._id = _temp_var._id;
                        _var._type = _temp_var._type;
                    }while(_id != 0);
                    if(_i < (_it._point_in[0]._connection.size() - 1)) _var._name += " OR ";
                }
                _m_out_var_item[_out_var_id]._inputVar.push_back(_var);
            }
    }

    foreach(T_POU_LD_ITEM _it, _m_in_out_var_item)
    {
        qint32 _out_var_id = _it._localId;

        if(!_it._point_in.empty())
            if(!_it._point_in[0]._connection.empty())
            {
                T_CONNECTION_VAR _var;

                _var._name = _m_in_out_var_item[_out_var_id]._expression + " := ";
                _var._type = _m_in_out_var_item[_out_var_id]._return_type;

                for(int _i = 0; _i < _it._point_in[0]._connection.size(); _i++)
                {
                    qint32 _id = _m_in_out_var_item[_out_var_id]._point_in[0]._connection[_i]._refLocalId;
                    do{
                        T_CONNECTION_VAR _temp_var;
                        _id = checkVarConnectionChain(_id, &_temp_var);
                        if(_temp_var._name != "") _var._name += _temp_var._name;
                        if((_id != 0) && (_temp_var._name != "")) _var._name += " OR ";
                        _var._id = _temp_var._id;
                        _var._type = _temp_var._type;
                    }while(_id != 0);
                    if(_i < (_it._point_in[0]._connection.size() - 1)) _var._name += " OR ";
                }
                _m_in_out_var_item[_out_var_id]._inputVar.push_back(_var);
            }
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
qint32 TranslatorLD::checkVarConnectionChain(qint32 _var_id, T_CONNECTION_VAR *_var)
{
    quint64 _result = 0;

    if(itemIsBlock(_var_id))
    {
        _var->_name += _m_block_item[_var_id]._instanceName;
        _var->_name += ".";
        _var->_name += _m_item[_var_id]._outputVariables[0]._formalParameter;
        _var->_id = _var_id;
        _var->_type = "BOOL";
    }else
    if(itemIsFunc(_var_id))
    {
        _var->_name += _m_func_item[_var_id]._expression;
        _var->_id = _var_id;
        _var->_type = _m_func_item[_var_id]._return_type;
    }else
    if(itemIsInVar(_var_id))
    {
        _var->_name += _m_in_var_item[_var_id]._expression;
        _var->_id = _var_id;
        _var->_type = _m_in_var_item[_var_id]._return_type;
    }else
    if(itemIsInOutVar(_var_id))
    {
        _var->_name += _m_in_out_var_item[_var_id]._expression;
        _var->_id = _var_id;
        _var->_type = _m_in_out_var_item[_var_id]._return_type;
    }else
    if(itemIsContinuation(_var_id))
    {
        if(!_m_continuation_item[_var_id]._inputVar.isEmpty())
        {
            _var->_name += _m_continuation_item[_var_id]._inputVar[0]._name;
            _var->_id = _var_id;
            _var->_type = _m_continuation_item[_var_id]._inputVar[0]._type;
            _result = _m_continuation_item[_var_id]._inputVar[0]._id;
            if(itemIsLeftPowerRail(_result))_result = 0;
            if(itemIsRightPowerRail(_result))_result = 0;
        }
    }else
    if(itemIsContact(_var_id))
    {
        _var->_name += _m_contact_item[_var_id]._expression;
        _var->_id = _var_id;
        _var->_is_modificator = itemIsModifContact(_var_id);
        _result = _m_contact_item[_var_id]._point_in[0]._connection[0]._refLocalId;
        if(itemIsLeftPowerRail(_result))_result = 0;
        if(itemIsRightPowerRail(_result))_result = 0;
    }else
    if(itemIsCoil(_var_id))
    {
        _var->_name += ""; //_m_coil_item[_var_id]._expression;
        _var->_id = _var_id;
        _var->_is_modificator = itemIsModifCoil(_var_id);
        _result = _m_coil_item[_var_id]._point_in[0]._connection[0]._refLocalId;
        if(itemIsLeftPowerRail(_result))_result = 0;
        if(itemIsRightPowerRail(_result))_result = 0;
    }else
    if(itemIsLeftPowerRail(_var_id))
    {
        _var->_name += "TRUE";
    }else
    if(itemIsRightPowerRail(_var_id))
    {
        _var->_name += "FALSE";
    }
    return _result;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
quint32 TranslatorLD::linkConnect(qint32 _connect_id)
{
    quint32 _id = 0;
    foreach(T_POU_LD_ITEM _it, _m_continuation_item)
        if(_it._name == _m_connector_item[_connect_id]._name)
        {
            _id = _it._localId;
            break;
        }
    return _id;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
quint32 TranslatorLD::linkContinuation(qint32 _connect_id, qint32 _new_connect_id)
{
    quint32 _id = 0;
    foreach(T_POU_LD_ITEM _it, _m_item)
    {
        switch(_it._type)
        {
        case IT_LD_BLOCK:{
            if(!_it._inputVariables.empty())
                for(int _i = 0; _i < _it._inputVariables.size(); _i++)
                    if(_it._inputVariables[_i]._connection._refLocalId == _connect_id)
                    {
                        _m_block_item[_it._localId]._inputVariables[_i]._connection._refLocalId = _new_connect_id;
                        break;
                    }
        }break;
        case IT_LD_FUNCTION:{
            if(!_it._inputVariables.empty())
                for(int _i = 0; _i < _it._inputVariables.size(); _i++)
                    if(_it._inputVariables[_i]._connection._refLocalId == _connect_id)
                    {
                        _m_func_item[_it._localId]._inputVariables[_i]._connection._refLocalId = _new_connect_id;
                        break;
                    }
        }break;
        case IT_LD_INPUT:{
            if(!_it._point_in.empty())
                if(!_it._point_in[0]._connection.empty())
                    for(int _i = 0; _i < _it._point_in[0]._connection.size(); _i++)
                        if(_it._point_in[0]._connection[_i]._refLocalId == _connect_id)
                        {
                            _m_in_var_item[_it._localId]._point_in[0]._connection[_i]._refLocalId = _new_connect_id;
                            break;
                        }
        }break;
        case IT_LD_OUTPUT:{
        }break;
        case IT_LD_INPUT_OUTPUT:{
            if(!_it._point_in.empty())
                if(!_it._point_in[0]._connection.empty())
                    for(int _i = 0; _i < _it._point_in[0]._connection.size(); _i++)
                        if(_it._point_in[0]._connection[_i]._refLocalId == _connect_id)
                        {
                            _m_in_out_var_item[_it._localId]._point_in[0]._connection[_i]._refLocalId = _new_connect_id;
                            break;
                        }
        }break;
        case IT_LD_CONTACT:{
            if(!_it._point_in.empty())
                if(!_it._point_in[0]._connection.empty())
                    for(int _i = 0; _i < _it._point_in[0]._connection.size(); _i++)
                        if(_it._point_in[0]._connection[_i]._refLocalId == _connect_id)
                        {
                            _m_contact_item[_it._localId]._point_in[0]._connection[_i]._refLocalId = _new_connect_id;
                            break;
                        }
        }break;
        case IT_LD_COIL:{
            if(!_it._point_in.empty())
                if(!_it._point_in[0]._connection.empty())
                    for(int _i = 0; _i < _it._point_in[0]._connection.size(); _i++)
                        if(_it._point_in[0]._connection[_i]._refLocalId == _connect_id)
                        {
                            _m_coil_item[_it._localId]._point_in[0]._connection[_i]._refLocalId = _new_connect_id;
                            break;
                        }
        }break;
        case IT_LD_LEFT_POWER_RAIL:{
            if(!_it._point_out.empty())
                for(int _i = 0; _i < _it._point_out.size(); _i++)
                    if(_it._point_out[_i]._refLocalId == _connect_id)
                    {
                        _m_left_power_rail_item[_it._localId]._point_out[_i]._refLocalId = _new_connect_id;
                        break;
                    }
        }break;
        case IT_LD_RIGHT_POWER_RAIL:{
            if(!_it._point_in.empty())
                for(int _i = 0; _i < _it._point_in.size(); _i++)
                    if(!_it._point_in[_i]._connection.empty())
                        for(int _j = 0; _j < _it._point_in[_i]._connection.size(); _j++)
                            if(_it._point_in[_i]._connection[_j]._refLocalId == _connect_id)
                            {
                                _m_right_power_rail_item[_it._localId]._point_in[_i]._connection[_j]._refLocalId = _new_connect_id;
                                break;
                            }
        }break;
        case IT_LD_CONNECTOR:
        case IT_LD_CONTINUATION:
        case IT_LD_MAX:
        case IT_LD_NOT_DEFINED:
        case IT_LD_COMMENT:{}break;
        }
    }
    return _id;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void TranslatorLD::prepareConnectContinuation()
{
    foreach(T_POU_LD_ITEM _it, _m_connector_item)
    {
        qint32 _connect_id      = _it._localId;
        quint32 _item_in        = _m_connector_item[_connect_id]._point_in[0]._connection[0]._refLocalId;
        quint32 _item_out       = linkConnect(_connect_id);
        linkContinuation(_item_out, _item_in);
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool TranslatorLD::itemIsBlock(quint32 _id)
{
    if(_m_block_item.find(_id) != _m_block_item.end())
        return true;
    return false;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool TranslatorLD::itemIsFunc(quint32 _id)
{
    if(_m_func_item.find(_id) != _m_func_item.end())
        return true;
    return false;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool TranslatorLD::itemIsInVar(quint32 _id)
{
    if(_m_in_var_item.find(_id) != _m_in_var_item.end())
        return true;
    return false;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool TranslatorLD::itemIsOutVar(quint32 _id)
{
    if(_m_out_var_item.find(_id) != _m_out_var_item.end())
        return true;
    return false;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool TranslatorLD::itemIsInOutVar(quint32 _id)
{
    if(_m_in_out_var_item.find(_id) != _m_in_out_var_item.end())
        return true;
    return false;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool TranslatorLD::itemIsConnect(quint32 _id)
{
    if(_m_connector_item.find(_id) != _m_connector_item.end())
        return true;
    return false;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool TranslatorLD::itemIsContinuation(quint32 _id)
{
    if(_m_continuation_item.find(_id) != _m_continuation_item.end())
        return true;
    return false;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool TranslatorLD::itemIsContact(quint32 _id)
{
    if(_m_contact_item.find(_id) != _m_contact_item.end())
        return true;
    return false;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool TranslatorLD::itemIsLeftPowerRail(quint32 _id)
{
    if(_m_left_power_rail_item.find(_id) != _m_left_power_rail_item.end())
        return true;
    return false;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool TranslatorLD::itemIsRightPowerRail(quint32 _id)
{
    if(_m_right_power_rail_item.find(_id) != _m_right_power_rail_item.end())
        return true;
    return false;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool TranslatorLD::itemIsCoil(quint32 _id)
{
    if(_m_coil_item.find(_id) != _m_coil_item.end())
        return true;
    return false;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool TranslatorLD::itemIsModifContact(quint32 _id)
{
    if(_m_contact_modificator_item.find(_id) != _m_contact_modificator_item.end())
        return true;
    return false;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool TranslatorLD::itemIsModifCoil(quint32 _id)
{
    if(_m_coil_modificator_item.find(_id) != _m_coil_modificator_item.end())
        return true;
    return false;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void TranslatorLD::parseItem(T_POU *pou_)
{
    _m_in_var_item.clear();
    _m_out_var_item.clear();
    _m_in_out_var_item.clear();

    _m_block_item.clear();
    _m_func_item.clear();
    _m_connector_item.clear();
    _m_continuation_item.clear();
    _m_contact_item.clear();
    _m_left_power_rail_item.clear();
    _m_right_power_rail_item.clear();
    _m_contact_item.clear();
    _m_coil_item.clear();
    _m_contact_modificator_item.clear();
    _m_coil_modificator_item.clear();

    quint32 _counter = 0;
    for(int _i = 0; _i < (int)pou_->_body._LD._item.size(); _i++)
        if(pou_->_body._LD._item[_i]._type == IT_LD_LEFT_POWER_RAIL)
        {
            for(int _j = 0; _j < (int)pou_->_body._LD._item.size(); _j++)
                if(!pou_->_body._LD._item[_j]._point_in.isEmpty())
                    for(int _p = 0; _p < pou_->_body._LD._item[_j]._point_in.size(); _p++)
                        if(pou_->_body._LD._item[_j]._point_in[_p]._connection[0]._refLocalId == pou_->_body._LD._item[_i]._localId)
                        {
                            pou_->_body._LD._item[_i]._point_out[_counter]._refLocalId = pou_->_body._LD._item[_j]._localId;
                            _counter++;
                            break;
                        }
        }

    for(int _i = 0; _i < (int)pou_->_body._LD._item.size(); _i++)
        switch(pou_->_body._LD._item[_i]._type)
        {
        case IT_LD_BLOCK:{      _m_block_item.insert(pou_->_body._LD._item[_i]._localId, pou_->_body._LD._item[_i]);    }break;
        case IT_LD_FUNCTION:{
//            pou_->_body._LD._item[_i]._return_type          = pou_->_return_type;
//            pou_->_body._LD._item[_i]._return_type          = getRetTypeStandartFunction(_item._typeName);
            _m_func_item.insert(pou_->_body._LD._item[_i]._localId, pou_->_body._LD._item[_i]);
        }break;
        case IT_LD_INPUT:{
            pou_->_body._LD._item[_i]._return_type = getTypeByVar(pou_, pou_->_body._LD._item[_i]._expression);
            _m_in_var_item.insert(pou_->_body._LD._item[_i]._localId, pou_->_body._LD._item[_i]);
        }break;
        case IT_LD_OUTPUT:{
            pou_->_body._LD._item[_i]._return_type = getTypeByVar(pou_, pou_->_body._LD._item[_i]._expression);
            _m_out_var_item.insert(pou_->_body._LD._item[_i]._localId, pou_->_body._LD._item[_i]);
        }break;
        case IT_LD_INPUT_OUTPUT:{
            pou_->_body._LD._item[_i]._return_type = getTypeByVar(pou_, pou_->_body._LD._item[_i]._expression);
            _m_in_out_var_item.insert(pou_->_body._LD._item[_i]._localId, pou_->_body._LD._item[_i]);
        }break;
        case IT_LD_CONNECTOR:{          _m_connector_item.insert(pou_->_body._LD._item[_i]._localId, pou_->_body._LD._item[_i]);        }break;
        case IT_LD_CONTINUATION:{       _m_continuation_item.insert(pou_->_body._LD._item[_i]._localId, pou_->_body._LD._item[_i]);     }break;
        case IT_LD_CONTACT:{            _m_contact_item.insert(pou_->_body._LD._item[_i]._localId, pou_->_body._LD._item[_i]);          }break;
        case IT_LD_COIL:{               _m_coil_item.insert(pou_->_body._LD._item[_i]._localId, pou_->_body._LD._item[_i]);             }break;
        case IT_LD_LEFT_POWER_RAIL:{    _m_left_power_rail_item.insert(pou_->_body._LD._item[_i]._localId, pou_->_body._LD._item[_i]);  }break;
        case IT_LD_RIGHT_POWER_RAIL:{   _m_right_power_rail_item.insert(pou_->_body._LD._item[_i]._localId, pou_->_body._LD._item[_i]); }break;

        case IT_LD_COMMENT:
        case IT_LD_NOT_DEFINED:
        case IT_LD_MAX:{}break;
        }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void TranslatorLD::parseItem(T_POU_BODY_LD *_ld)
{
    _m_in_var_item.clear();
    _m_out_var_item.clear();
    _m_in_out_var_item.clear();

    _m_block_item.clear();
    _m_func_item.clear();
    _m_connector_item.clear();
    _m_continuation_item.clear();
    _m_contact_item.clear();
    _m_left_power_rail_item.clear();
    _m_right_power_rail_item.clear();
    _m_contact_item.clear();
    _m_coil_item.clear();
    _m_contact_modificator_item.clear();
    _m_coil_modificator_item.clear();

    quint32 _counter = 0;
    for(int _i = 0; _i < (int)_ld->_item.size(); _i++)
        if(_ld->_item[_i]._type == IT_LD_LEFT_POWER_RAIL)
        {
            for(int _j = 0; _j < (int)_ld->_item.size(); _j++)
                if(!_ld->_item[_j]._point_in.isEmpty())
                    for(int _p = 0; _p < _ld->_item[_j]._point_in.size(); _p++)
                        if(_ld->_item[_j]._point_in[_p]._connection[0]._refLocalId == _ld->_item[_i]._localId)
                        {
                            _ld->_item[_i]._point_out[_counter]._refLocalId = _ld->_item[_j]._localId;
                            _counter++;
                            break;
                        }
        }

    for(int _i = 0; _i < (int)_ld->_item.size(); _i++)
        switch(_ld->_item[_i]._type)
        {
        case IT_LD_BLOCK:{      _m_block_item.insert(_ld->_item[_i]._localId, _ld->_item[_i]);    }break;
        case IT_LD_FUNCTION:{
            //            _ld->_item[_i]._return_type          = pou_->_return_type;
            //            _ld->_item[_i]._return_type          = getRetTypeStandartFunction(_item._typeName);
            _m_func_item.insert(_ld->_item[_i]._localId, _ld->_item[_i]);
        }break;
        case IT_LD_INPUT:{
//            _ld->_item[_i]._return_type = getTypeByVar(pou_, _ld->_item[_i]._expression);
            _m_in_var_item.insert(_ld->_item[_i]._localId, _ld->_item[_i]);
        }break;
        case IT_LD_OUTPUT:{
//            _ld->_item[_i]._return_type = getTypeByVar(pou_, _ld->_item[_i]._expression);
            _m_out_var_item.insert(_ld->_item[_i]._localId, _ld->_item[_i]);
        }break;
        case IT_LD_INPUT_OUTPUT:{
//            _ld->_item[_i]._return_type = getTypeByVar(pou_, _ld->_item[_i]._expression);
            _m_in_out_var_item.insert(_ld->_item[_i]._localId, _ld->_item[_i]);
        }break;
        case IT_LD_CONNECTOR:{          _m_connector_item.insert(_ld->_item[_i]._localId, _ld->_item[_i]);        }break;
        case IT_LD_CONTINUATION:{       _m_continuation_item.insert(_ld->_item[_i]._localId, _ld->_item[_i]);     }break;
        case IT_LD_CONTACT:{            _m_contact_item.insert(_ld->_item[_i]._localId, _ld->_item[_i]);          }break;
        case IT_LD_COIL:{               _m_coil_item.insert(_ld->_item[_i]._localId, _ld->_item[_i]);             }break;
        case IT_LD_LEFT_POWER_RAIL:{    _m_left_power_rail_item.insert(_ld->_item[_i]._localId, _ld->_item[_i]);  }break;
        case IT_LD_RIGHT_POWER_RAIL:{   _m_right_power_rail_item.insert(_ld->_item[_i]._localId, _ld->_item[_i]); }break;

        case IT_LD_COMMENT:
        case IT_LD_NOT_DEFINED:
        case IT_LD_MAX:{}break;
        }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void TranslatorLD::prepareModificators()
{
    foreach(T_POU_LD_ITEM _it, _m_contact_item)
    {
        if(_it._negated)
        {
            _m_contact_item[_it._localId]._expression = QString("NOT(%1)").arg(_m_contact_item[_it._localId]._expression);
        }else{
            if(_it._edge == "")
            {
                _m_contact_item[_it._localId]._expression = QString("%1").arg(_m_contact_item[_it._localId]._expression);
            }else{
                T_MODIFICATOR _mod;
                if(_it._edge == "rising")
                {
                    _mod._name = QString("R_TRIG_%1_TMP_VAR").arg(_it._localId);
                    _mod._type = QString("R_TRIG");
                    _mod._code = QString("%1(CLK := %2)").arg(_mod._name, _m_contact_item[_it._localId]._expression);
                    _mod._out = QString("%1.Q").arg(_mod._name);
                    _m_contact_item[_it._localId]._expression = QString("%1").arg(_mod._out);
                    _m_contact_modificator_item.insert(_it._localId, _mod);
                }else
                if(_it._edge == "falling")
                {
                    _mod._name = QString("F_TRIG_%1_TMP_VAR").arg(_it._localId);
                    _mod._type = QString("F_TRIG");
                    _mod._code = QString("%1(CLK := %2)").arg(_mod._name, _m_contact_item[_it._localId]._expression);
                    _mod._out = QString("%1.Q").arg(_mod._name);
                    _m_contact_item[_it._localId]._expression = QString("%1").arg(_mod._out);
                    _m_contact_modificator_item.insert(_it._localId, _mod);
                }
            }
        }
    }
    foreach(T_POU_LD_ITEM _it, _m_coil_item)
    {
        T_MODIFICATOR _mod;
        if(_it._negated)
        {
            _m_coil_item[_it._localId]._expression = QString("%1").arg(_m_coil_item[_it._localId]._expression);
            qint32 _id = _it._point_in[0]._connection[0]._refLocalId;
            QString _var;
            do{ _var = checkCoilConnectionChain(_id, _id, "NOT");  }while(_var == "");
            _mod._code = QString("%1 := NOT(%2)").arg(_m_coil_item[_it._localId]._expression, _var);
            _m_coil_modificator_item.insert(_it._localId, _mod);
        }else{
            if(_it._edge == "rising")
            {
                _mod._name = QString("R_TRIG_%1_TMP_VAR").arg(_it._localId);
                _mod._type = QString("R_TRIG");

                qint32 _id = _it._point_in[0]._connection[0]._refLocalId;
                QString _var;
                do{ _var = checkCoilConnectionChain(_id, _id, "RISING");  }while(_var == "");

                _mod._code = QString("%1(CLK := %2);\n").arg(_mod._name, _var);
                _mod._code += QString("  %1 := %2.Q").arg(_m_coil_item[_it._localId]._expression, _mod._name);
                _m_coil_modificator_item.insert(_it._localId, _mod);
            }else
            if(_it._edge == "falling")
            {
                _mod._name = QString("F_TRIG_%1_TMP_VAR").arg(_it._localId);
                _mod._type = QString("F_TRIG");

                qint32 _id = _it._point_in[0]._connection[0]._refLocalId;
                QString _var;
                QString _all_var = "";
                do{
                    _var = checkCoilConnectionChain(_id, _id, "FALLING");
                    _all_var += _var;
                    if((_id != 0) && (_var != ""))_all_var += " AND ";
                }while(_id != 0);

                _mod._code = QString("%1(CLK := %2);\n").arg(_mod._name, _all_var);
                _mod._code += QString("  %1 := %2.Q").arg(_m_coil_item[_it._localId]._expression, _mod._name);
                _m_coil_modificator_item.insert(_it._localId, _mod);
            }else
            if(_it._storage == "set")
            {
                qint32 _id = _it._point_in[0]._connection[0]._refLocalId;
                QString _var;
                QString _all_var = "";
                do{
                    _var = checkCoilConnectionChain(_id, _id, "SET");
                    _all_var += _var;
                    if((_id != 0) && (_var != ""))_all_var += " AND ";
                }while(_id != 0);
                _mod._code = QString("IF %1 THEN\n    %2 := TRUE;\n    END_IF").arg(_all_var, _m_coil_item[_it._localId]._expression);
                _m_coil_modificator_item.insert(_it._localId, _mod);
            }else
            if(_it._storage == "reset")
            {
                qint32 _id = _it._point_in[0]._connection[0]._refLocalId;
                QString _var;
                QString _all_var = "";
                do{
                    _var = checkCoilConnectionChain(_id, _id, "SET");
                    _all_var += _var;
                    if((_id != 0) && (_var != ""))_all_var += " AND ";
                }while(_id != 0);
                _mod._code = QString("IF %1 THEN\n    %2 := FALSE;\n    END_IF").arg(_all_var, _m_coil_item[_it._localId]._expression);
                _m_coil_modificator_item.insert(_it._localId, _mod);
            }else{
                _m_coil_item[_it._localId]._expression = QString("%1").arg(_m_coil_item[_it._localId]._expression);
                qint32 _id = _it._point_in[0]._connection[0]._refLocalId;
                QString _var;
                do{ _var = checkCoilConnectionChain(_id, _id, "");  }while(_var == "");
                _mod._code = QString("%1 := %2").arg(_m_coil_item[_it._localId]._expression, _var);
                _m_coil_modificator_item.insert(_it._localId, _mod);
            }
        }
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
QString TranslatorLD::checkCoilConnectionChain(qint32 _var_id, qint32 &_next_id, QString _coil_type)
{
    QString _result = "";

    if(itemIsBlock(_var_id))
    {
        _result = QString("%1.%1").arg(_m_block_item[_var_id]._instanceName, _m_item[_var_id]._outputVariables[0]._formalParameter);
        _next_id = 0;
    }else
    if(itemIsFunc(_var_id))
    {
        _result = QString("%1").arg(_m_func_item[_var_id]._expression);
        _next_id = 0;
    }else
    if(itemIsInVar(_var_id))
    {
        _result = QString("%1").arg(_m_in_var_item[_var_id]._expression);
        _next_id = 0;
    }else
    if(itemIsInOutVar(_var_id))
    {
        _result = QString("%1").arg(_m_in_out_var_item[_var_id]._expression);
        _next_id = 0;
    }else
    if(itemIsContinuation(_var_id))
    {
        // if(!_m_continuation_item[_var_id]._inputVar.isEmpty())
        // {
        //     _var->_name += _m_continuation_item[_var_id]._inputVar[0]._name;
        //     _var->_id = _var_id;
        //     _var->_type = _m_continuation_item[_var_id]._inputVar[0]._type;
        //     _result = _m_continuation_item[_var_id]._inputVar[0]._id;
        //     if(itemIsLeftPowerRail(_result))_result = 0;
        //     if(itemIsRightPowerRail(_result))_result = 0;
        // }
    }else
    if(itemIsContact(_var_id))
    {
        if(_coil_type == "SET")     _result = QString("%1").arg(_m_contact_item[_var_id]._expression);
        else
        if(_coil_type == "RESET")   _result = QString("%1").arg(_m_contact_item[_var_id]._expression);
        else
        if(_coil_type == "FALLING") _result = QString("%1").arg(_m_contact_item[_var_id]._expression);
        else
            _result = "";
        _next_id = _m_contact_item[_var_id]._point_in[0]._connection[0]._refLocalId;
    }else
    if(itemIsCoil(_var_id))
    {
        _result = "";
        _next_id = _m_coil_item[_var_id]._point_in[0]._connection[0]._refLocalId;
    }else
    if(itemIsLeftPowerRail(_var_id))
    {
        _result = "TRUE";
        _next_id = 0;
    }else
    if(itemIsRightPowerRail(_var_id))
    {
        _result = "FALSE";
        _next_id = 0;
    }
    return _result;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
/*
--------------------------------
  SEMA0(CLAIM := TRUE, RELEASE := iv10);
  iov0 := SEMA0.BUSY OR iv12 OR iv3 OR iv4;
  _TMP_SEL23_OUT := SEL(TRUE, iv15, iv11);
  ov10 := _TMP_SEL23_OUT;
  R_TRIG1(CLK := ov1);
  F_TRIG1(CLK := iv9);
  R_TRIG2(CLK := iv8);
  SR0(S1 := iov0, R := R_TRIG1.Q AND F_TRIG1.Q AND R_TRIG2.Q AND iov2);
  ov1 := SR0.Q1;
  iov2 := iv12;
  iv4 := TRUE;
  iv0 := NOT(TRUE);
  iv1 := TRUE;
  IF iv4 THEN
    iv2 := TRUE; (*set*)
  END_IF;
  IF iv4 THEN
    iv5 := TRUE; (*set*)
  END_IF;
  R_TRIG3(CLK := iv12);
  iv6 := R_TRIG3.Q;
  F_TRIG2(CLK := iv12);
  iv7 := F_TRIG2.Q;
  IF iv4 THEN
    iv7 := FALSE; (*reset*)
  END_IF;
  iov1 := iv4;
  R_TRIG4(CLK := ov1);
  IF R_TRIG4.Q AND F_TRIG1.Q AND R_TRIG2.Q AND iov2 THEN
    ov0 := TRUE; (*set*)
  END_IF;
  F_TRIG3(CLK := F_TRIG1.Q AND R_TRIG2.Q AND iov2);
  ov2 := F_TRIG3.Q;
  iov1 := iov0;
  iov9 := NOT(iov0);
--------------------------------
--------------------------------
  SEMA0(CLAIM := TRUE, RELEASE := iv10);
  iov0 := iv3 OR SEMA0.BUSY OR iv4 OR iv12;
  SEL23_TMP_VAR := SEL(TRUE, iv15, iv11);
  ov10 := SEL23_TMP_VAR;
  R_TRIG_59_TMP_VAR(CLK := ov1);
  F_TRIG_57_TMP_VAR(CLK := iv9);
  R_TRIG_56_TMP_VAR(CLK := iv8);
  SR0(S1 := iov0, R := R_TRIG_59_TMP_VAR.Q AND F_TRIG_57_TMP_VAR.Q AND R_TRIG_56_TMP_VAR.Q AND iov2);
  ov1 := SR0.Q1;
  iov2 := iv12;
  iv4 := TRUE;
  iv0 := NOT(TRUE);
  iv1 := TRUE;
  IF iv4 THEN
    iv2 := TRUE;
    END_IF;
  IF iv4 THEN
    iv5 := TRUE;
    END_IF;
  R_TRIG_50_TMP_VAR(CLK := iv12)
  iv6 = R_TRIG_50_TMP_VAR.Q;
  F_TRIG_51_TMP_VAR(CLK := iv12)
  iv7 = F_TRIG_51_TMP_VAR.Q;
  IF iv4 THEN
    iv7 := FALSE;
    END_IF;
  iov1 := iv4;
  IF R_TRIG_59_TMP_VAR.Q AND F_TRIG_57_TMP_VAR.Q AND R_TRIG_56_TMP_VAR.Q AND iov2 THEN
    ov0 := TRUE;
    END_IF;
  F_TRIG_60_TMP_VAR(CLK := F_TRIG_57_TMP_VAR.Q AND R_TRIG_56_TMP_VAR.Q AND iov2)
  ov2 = F_TRIG_60_TMP_VAR.Q;
  iov1 := iov0;
  iov9 := NOT(iov0);
--------------------------------
*/
