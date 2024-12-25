#include "TranslatorLD.h"
#include "../iec/StandardLibrary.h"

TranslatorLD::TranslatorLD() {}

// *** POU
//
//-----------------------------------------------------------------------------------
void TranslatorLD::Code_STgenerator(T_POU pou_, QString &text_)
{
    _m_add_var_string = "";
    QString _code_string = "";

    _m_item.clear();
    _m_execution_order_item.clear();
    _m_generator_item.clear();

    for(int _i = 0; _i < (int)pou_._body._LD._item.size(); _i++)
        _m_item.insert(pou_._body._LD._item[_i]._localId, pou_._body._LD._item[_i]);

    checkIsChainUsed();

    parseItem(&pou_);
    prepareConnectContinuation();
    prepareModificators();
    prepareFuncTempVar();
    prepareVarType();
    prepareVar();
    prepareFunc();
    AllVar_STgenerator(&pou_, text_);

    if(!_m_func_item.empty())
    {
        text_ += "  VAR\n";
        foreach(T_POU_LD_ITEM _it, _m_func_item)
            text_ += QString("    %1 : %2;\n").arg(_m_func_item[_it._localId]._expression, _m_func_item[_it._localId]._return_type);
        text_ += "  END_VAR\n\n";
    }

    prepareBlock();

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
        case IT_LD_BLOCK:{         Block_STcode(_it, _code_string); }break;
        case IT_LD_FUNCTION:{      Func_STcode(_it, _code_string);  }break;
        case IT_LD_OUTPUT:{        Var_STcode(_it, _code_string);   }break;
        case IT_LD_INPUT_OUTPUT:{  Var_STcode(_it, _code_string);   }break;
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

    foreach(T_POU_LD_ITEM _it, _m_block_item)        Block_STcode(_it, _code_string);
    foreach(T_POU_LD_ITEM _it, _m_func_item)         Func_STcode(_it, _code_string);
    foreach(T_POU_LD_ITEM _it, _m_in_out_var_item)   Var_STcode(_it, _code_string);
    foreach(T_POU_LD_ITEM _it, _m_out_var_item)      Var_STcode(_it, _code_string);

    foreach(T_MODIFICATOR _it, _m_contact_modificator_item)
        if(_m_item[_it._localId]._is_chain_used)
            if(!_it._is_used)
            {
                if(_it._type != "") _m_add_var_string += QString("    %1 : %2;\n").arg(_it._name, _it._type);
                if(_it._code != "") _code_string += QString("  %1%2;\n").arg(_it._name, _it._code);
            }
    foreach(T_MODIFICATOR _it, _m_coil_modificator_item)
        if(_m_item[_it._localId]._is_chain_used)
            if(!_it._is_used)
            {
                switch(_it._mod_type)
                {
                case MT_COIL_RISING:
                case MT_COIL_FALLING:{
                    _m_add_var_string += _it._var_declaration;
                    _m_add_var_string += QString("    %1 : %2;\n").arg(_it._name, _it._type);
                    _code_string += _it._code_declaration;
                    _code_string += QString("  %1%2%3;\n").arg(_it._name, _it._code, _it._out);
                }break;
                case MT_COIL_SET:
                case MT_COIL_RESET:{
                    _m_add_var_string += _it._var_declaration;
                    _code_string += _it._code_declaration;
                    _code_string += QString("  %1;\n").arg(_it._code);
                }break;
                case MT_COIL_NOT:{
                    _code_string += QString("  %1;\n").arg(_it._code);
                }break;

                case MT_NONE:
                case MT_CONTACT_NOT:
                case MT_CONTACT_RISING:
                case MT_CONTACT_FALLING:{}break;
                }
            }

    if(_m_add_var_string != ""){    text_ += "  VAR\n";    text_ += _m_add_var_string;    text_ += "  END_VAR\n\n"; }
    text_ += _code_string;

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
    QString _code_string = "";

    _m_item.clear();
    _m_execution_order_item.clear();
    _m_generator_item.clear();

    for(int _i = 0; _i < (int)_ld._item.size(); _i++)
        _m_item.insert(_ld._item[_i]._localId, _ld._item[_i]);

    checkIsChainUsed();

    parseItem(&_ld);
    prepareConnectContinuation();
    prepareModificators();
    prepareFuncTempVar();
    prepareVarType();
    prepareVar();
    prepareFunc();
//    AllVar_STgenerator(&_ld, text_);

    if(!_m_func_item.empty())
    {
        text_ += "  VAR\n";
        foreach(T_POU_LD_ITEM _it, _m_func_item)
            text_ += QString("    %1 : %2;\n").arg(_m_func_item[_it._localId]._expression, _m_func_item[_it._localId]._return_type);
        text_ += "  END_VAR\n\n";
    }

    prepareBlock();

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
        case IT_LD_BLOCK:{         Block_STcode(_it, _code_string); }break;
        case IT_LD_FUNCTION:{      Func_STcode(_it, _code_string);  }break;
        case IT_LD_OUTPUT:{        Var_STcode(_it, _code_string);   }break;
        case IT_LD_INPUT_OUTPUT:{  Var_STcode(_it, _code_string);   }break;
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

    foreach(T_POU_LD_ITEM _it, _m_block_item)        Block_STcode(_it, _code_string);
    foreach(T_POU_LD_ITEM _it, _m_func_item)         Func_STcode(_it, _code_string);
    foreach(T_POU_LD_ITEM _it, _m_in_out_var_item)   Var_STcode(_it, _code_string);
    foreach(T_POU_LD_ITEM _it, _m_out_var_item)      Var_STcode(_it, _code_string);

    foreach(T_MODIFICATOR _it, _m_contact_modificator_item)
        if(_m_item[_it._localId]._is_chain_used)
            if(!_it._is_used)
        {
            if(_it._type != "") _m_add_var_string += QString("    %1 : %2;\n").arg(_it._name, _it._type);
            if(_it._code != "") _code_string += QString("  %1%2;\n").arg(_it._name, _it._code);
        }
    foreach(T_MODIFICATOR _it, _m_coil_modificator_item)
        if(_m_item[_it._localId]._is_chain_used)
            if(!_it._is_used)
        {
            switch(_it._mod_type)
            {
            case MT_COIL_RISING:
            case MT_COIL_FALLING:{
                _m_add_var_string += _it._var_declaration;
                _m_add_var_string += QString("    %1 : %2;\n").arg(_it._name, _it._type);
                _code_string += _it._code_declaration;
                _code_string += QString("  %1%2%3;\n").arg(_it._name, _it._code, _it._out);
            }break;
            case MT_COIL_SET:
            case MT_COIL_RESET:{
                _code_string += _it._code_declaration;
                _code_string += QString("  %1%2%3;\n").arg(_it._name, _it._code, _it._out);
            }break;

            case MT_COIL_NOT:
            case MT_NONE:
            case MT_CONTACT_NOT:
            case MT_CONTACT_RISING:
            case MT_CONTACT_FALLING:{}break;
            }
        }

    if(_m_add_var_string != ""){    text_ += "  VAR\n";    text_ += _m_add_var_string;    text_ += "  END_VAR\n\n"; }
    text_ += _code_string;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void TranslatorLD::Block_STcode(T_POU_LD_ITEM _block, QString &text_)
{
    if(!_block._is_chain_used)return;

    text_ += _block._comment_content;

    text_ += _block._expression;
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
            if(!_it._point_in.empty())
                for(int _i = 0; _i < _it._point_in[0]._connection.size(); _i++)
                    if(_it._point_in[0]._connection[_i]._refLocalId == _block._localId)
                        Var_STcode(_m_out_var_item[_it._localId], text_);

    foreach(T_POU_LD_ITEM _it, _m_in_out_var_item)
        if(!_it._is_used)
            if(!_it._point_in.empty())
                for(int _i = 0; _i < _it._point_in[0]._connection.size(); _i++)
                    if(_it._point_in[0]._connection[_i]._refLocalId == _block._localId)
                        Var_STcode(_m_in_out_var_item[_it._localId], text_);
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void TranslatorLD::Func_STcode(T_POU_LD_ITEM _func, QString &text_)
{
    if(!_func._is_chain_used)return;

    text_ += _func._comment_content;

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
            if(!_it._point_in.empty())
                for(int _i = 0; _i < _it._point_in[0]._connection.size(); _i++)
                    if(_it._point_in[0]._connection[_i]._refLocalId == _func._localId)
                        Var_STcode(_m_out_var_item[_it._localId], text_);

    foreach(T_POU_LD_ITEM _it, _m_in_out_var_item)
        if(!_it._is_used)
            if(!_it._point_in.empty())
                for(int _i = 0; _i < _it._point_in[0]._connection.size(); _i++)
                    if(_it._point_in[0]._connection[_i]._refLocalId == _func._localId)
                        Var_STcode(_m_in_out_var_item[_it._localId], text_);
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void TranslatorLD::Var_STcode(T_POU_LD_ITEM _var, QString &text_)
{
    QString _code = "";
    if(_var._is_used) return;
    if(_var._inputVar.isEmpty()) return;

    for(int _j = 0; _j < _var._inputVar.size(); _j++)
        if(_var._inputVar[_j]._is_modificator && (_var._inputVar[_j]._code != ""))
            _code += QString("  %1;\n").arg(_var._inputVar[_j]._code);

    _code += QString("  %1 := ").arg(_var._expression);

    for(int _j = 0; _j < _var._inputVar.size(); _j++)
        if(_var._inputVar[_j]._name != "")
        {
            _code += _var._inputVar[_j]._name;
            if(_j < (_var._inputVar.size() - 1)) _code += " OR ";
//            if(_j < (_var._inputVar.size() - 1)) _code += " AND ";
        }
    _code += ";\n";
    text_ += _code;

    if(itemIsOutVar(_var._localId)) _m_out_var_item[_var._localId]._is_used = true;
    if(itemIsInOutVar(_var._localId)) _m_in_out_var_item[_var._localId]._is_used = true;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void TranslatorLD::prepareBlock()
{
    foreach(T_POU_LD_ITEM _it, _m_block_item)
    {
        quint32 _block_id = _it._localId;
        _m_block_item[_block_id]._comment_content = "";

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
                    _id = checkBlockConnectionChain(_m_block_item[_block_id]._instanceName, _id, &_temp_var);
                    if(_temp_var._name != "")
                    {
                        if(_temp_var._code != "")
                            _m_block_item[_block_id]._comment_content += QString("  %1;\n").arg(_temp_var._code);
                        _var._name += _temp_var._name;
                    }
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
qint32 TranslatorLD::checkBlockConnectionChain(QString _target_name, qint32 _var_id, T_CONNECTION_VAR *_var)
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
        _var->_type = _m_contact_item[_var_id]._return_type;
        _var->_is_modificator = itemIsModifContact(_var_id);
        if(_var->_is_modificator)
        {
            if(_m_contact_modificator_item[_var_id]._type == "")
            {
                _var->_name = _m_contact_modificator_item[_var_id]._name;
                _var->_type = _m_contact_modificator_item[_var_id]._type;
                _var->_code = _m_contact_modificator_item[_var_id]._code;
            }else{
                QString _full_name = _var->_name + QString("_%1").arg(_target_name);
                _var->_name = _full_name + _m_contact_modificator_item[_var_id]._out;
                _var->_type = _m_contact_modificator_item[_var_id]._type;
                if(_m_contact_modificator_item[_var_id]._type != "")
                    _m_add_var_string += QString("    %1 : %2;\n").arg(_full_name, _m_contact_modificator_item[_var_id]._type);
                _var->_code = QString("%1%2").arg(_full_name, _m_contact_modificator_item[_var_id]._code);
            }
            _m_contact_modificator_item[_var_id]._is_used = true;
        }
        _result = _m_contact_item[_var_id]._point_in[0]._connection[0]._refLocalId;
        if(itemIsLeftPowerRail(_result))_result = 0;
        if(itemIsRightPowerRail(_result))_result = 0;
    }else
    if(itemIsCoil(_var_id))
    {
        _var->_name += ""; //_m_coil_item[_var_id]._expression;
        _var->_id = _var_id;
        _var->_type = _m_contact_item[_var_id]._return_type;
        _var->_is_modificator = itemIsModifCoil(_var_id);
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
                    _id = checkFuncConnectionChain(_m_func_item[_func_id]._instanceName, _id, &_temp_var);
                    if(_temp_var._name != "")
                    {
                        if(_temp_var._code != "")
                            _m_func_item[_func_id]._comment_content += QString("  %2;\n").arg(_temp_var._code);
                        _var._name += _temp_var._name;
                    }
                    if((_id != 0) && (_temp_var._name != "")) _var._name += " AND ";
                    _var._id = _temp_var._id;
                    _var._type = _temp_var._type;
                    //---------------------------------------------------
                    if(_m_func_item[_func_id]._return_type == "")
                        _m_func_item[_func_id]._return_type = _var._type;
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
qint32 TranslatorLD::checkFuncConnectionChain(QString _target_name, qint32 _var_id, T_CONNECTION_VAR *_var)
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
        _var->_type = _m_contact_item[_var_id]._return_type;
        _var->_is_modificator = itemIsModifContact(_var_id);
        if(_var->_is_modificator)
        {
            if(_m_contact_modificator_item[_var_id]._type == "")
            {
                _var->_name = _m_contact_modificator_item[_var_id]._name;
                _var->_type = _m_contact_modificator_item[_var_id]._type;
                _var->_code = _m_contact_modificator_item[_var_id]._code;
            }else{
                QString _full_name = _var->_name + QString("_%1").arg(_target_name);
                _var->_name = _full_name + _m_contact_modificator_item[_var_id]._out;
                _var->_type = _m_contact_modificator_item[_var_id]._type;
                _m_add_var_string += QString("    %1 : %2;\n").arg(_full_name, _m_contact_modificator_item[_var_id]._type);
                _var->_code = QString("%1%2").arg(_full_name, _m_contact_modificator_item[_var_id]._code);
            }
            _m_contact_modificator_item[_var_id]._is_used = true;
        }
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
                for(int _i = 0; _i < _it._point_in[0]._connection.size(); _i++)
                {
                    qint32 _id = _m_out_var_item[_out_var_id]._point_in[0]._connection[_i]._refLocalId;
                    do{
                        T_CONNECTION_VAR _var;
                        _id = checkVarConnectionChain(_m_out_var_item[_out_var_id]._expression, _id, &_var);
                        _m_out_var_item[_out_var_id]._inputVar.push_back(_var);
                    }while(_id != 0);
                }
            }
    }

    foreach(T_POU_LD_ITEM _it, _m_in_out_var_item)
    {
        qint32 _out_var_id = _it._localId;

        if(!_it._point_in.empty())
            if(!_it._point_in[0]._connection.empty())
            {
                for(int _i = 0; _i < _it._point_in[0]._connection.size(); _i++)
                {
                    qint32 _id = _m_in_out_var_item[_out_var_id]._point_in[0]._connection[_i]._refLocalId;
                    do{
                        T_CONNECTION_VAR _var;
                        _id = checkVarConnectionChain(_m_in_out_var_item[_out_var_id]._expression, _id, &_var);
                        _m_in_out_var_item[_out_var_id]._inputVar.push_back(_var);
                    }while(_id != 0);
                }
            }
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
qint32 TranslatorLD::checkVarConnectionChain(QString _target_name, qint32 _var_id, T_CONNECTION_VAR *_var)
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
        _var->_type = _m_contact_item[_var_id]._return_type;
        _var->_is_modificator = itemIsModifContact(_var_id);
        if(_var->_is_modificator)
        {
            if(_m_contact_modificator_item[_var_id]._type == "")
            {
                _var->_name = _m_contact_modificator_item[_var_id]._name;
                _var->_type = _m_contact_modificator_item[_var_id]._type;
                _var->_code = _m_contact_modificator_item[_var_id]._code;
            }else{
                QString _full_name = _var->_name + QString("_%1").arg(_target_name);
                _var->_name = _full_name + _m_contact_modificator_item[_var_id]._out;
                _var->_type = _m_contact_modificator_item[_var_id]._type;
                if(_m_contact_modificator_item[_var_id]._type != "")
                    _m_add_var_string += QString("    %1 : %2;\n").arg(_full_name, _m_contact_modificator_item[_var_id]._type);
                _var->_code = QString("%1%2").arg(_full_name, _m_contact_modificator_item[_var_id]._code);
            }
            _m_contact_modificator_item[_var_id]._is_used = true;
        }
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
    {
        pou_->_body._LD._item[_i]._is_chain_used = _m_item[pou_->_body._LD._item[_i]._localId]._is_chain_used;
        switch(pou_->_body._LD._item[_i]._type)
        {
        case IT_LD_BLOCK:{      _m_block_item.insert(pou_->_body._LD._item[_i]._localId, pou_->_body._LD._item[_i]);    }break;
        case IT_LD_FUNCTION:{
            pou_->_body._LD._item[_i]._return_type = get_return_type(pou_->_body._LD._item[_i]._typeName);
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

    foreach(T_POU_LD_ITEM _it, _m_contact_item)
    {
        foreach(T_POU_LD_ITEM _in_it, _m_in_var_item)
        {
            if(_in_it._expression == _it._expression)
                _m_in_var_item[_in_it._localId]._modificator_id = _it._localId;
        }
        foreach(T_POU_LD_ITEM _out_it, _m_out_var_item)
        {
            if(_out_it._expression == _it._expression)
                _m_in_var_item[_out_it._localId]._modificator_id = _it._localId;
        }
        foreach(T_POU_LD_ITEM _in_out_it, _m_in_out_var_item)
        {
            if(_in_out_it._expression == _it._expression)
                _m_in_var_item[_in_out_it._localId]._modificator_id = _it._localId;
        }
    }
    foreach(T_POU_LD_ITEM _it, _m_coil_item)
    {
        foreach(T_POU_LD_ITEM _in_it, _m_in_var_item)
        {
            if(_in_it._expression == _it._expression)
                _m_in_var_item[_in_it._localId]._modificator_id = _it._localId;
        }
        foreach(T_POU_LD_ITEM _out_it, _m_out_var_item)
        {
            if(_out_it._expression == _it._expression)
                _m_in_var_item[_out_it._localId]._modificator_id = _it._localId;
        }
        foreach(T_POU_LD_ITEM _in_out_it, _m_in_out_var_item)
        {
            if(_in_out_it._expression == _it._expression)
                _m_in_var_item[_in_out_it._localId]._modificator_id = _it._localId;
        }
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
    {
        _ld->_item[_i]._is_chain_used = _m_item[_ld->_item[_i]._localId]._is_chain_used;
        switch(_ld->_item[_i]._type)
        {
        case IT_LD_BLOCK:{      _m_block_item.insert(_ld->_item[_i]._localId, _ld->_item[_i]);    }break;
        case IT_LD_FUNCTION:{
            _ld->_item[_i]._return_type = get_return_type(_ld->_item[_i]._typeName);
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

    foreach(T_POU_LD_ITEM _it, _m_contact_item)
    {
        foreach(T_POU_LD_ITEM _in_it, _m_in_var_item)
        {
            if(_in_it._expression == _it._expression)
                _m_in_var_item[_in_it._localId]._modificator_id = _it._localId;
        }
        foreach(T_POU_LD_ITEM _out_it, _m_out_var_item)
        {
            if(_out_it._expression == _it._expression)
                _m_in_var_item[_out_it._localId]._modificator_id = _it._localId;
        }
        foreach(T_POU_LD_ITEM _in_out_it, _m_in_out_var_item)
        {
            if(_in_out_it._expression == _it._expression)
                _m_in_var_item[_in_out_it._localId]._modificator_id = _it._localId;
        }
    }
    foreach(T_POU_LD_ITEM _it, _m_coil_item)
    {
        foreach(T_POU_LD_ITEM _in_it, _m_in_var_item)
        {
            if(_in_it._expression == _it._expression)
                _m_in_var_item[_in_it._localId]._modificator_id = _it._localId;
        }
        foreach(T_POU_LD_ITEM _out_it, _m_out_var_item)
        {
            if(_out_it._expression == _it._expression)
                _m_in_var_item[_out_it._localId]._modificator_id = _it._localId;
        }
        foreach(T_POU_LD_ITEM _in_out_it, _m_in_out_var_item)
        {
            if(_in_out_it._expression == _it._expression)
                _m_in_var_item[_in_out_it._localId]._modificator_id = _it._localId;
        }
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void TranslatorLD::prepareModificators()
{
    foreach(T_POU_LD_ITEM _it, _m_contact_item)
    {
        T_MODIFICATOR _mod;
        _mod._localId = _it._localId;
        if(_it._negated)
        {
            _mod._name = QString("NOT(%1)").arg(_m_contact_item[_it._localId]._expression);
            _mod._type = "";
            _mod._code = "";
            _mod._out = "";
            _mod._mod_type = MT_CONTACT_NOT;
            _m_contact_modificator_item.insert(_it._localId, _mod);
        }else{
            if(_it._edge == "")
            {
                _mod._name = QString("%1").arg(_m_contact_item[_it._localId]._expression);
                _mod._type = "";
                _mod._code = "";
                _mod._out = "";
                _mod._mod_type = MT_NONE;
                _m_contact_modificator_item.insert(_it._localId, _mod);
            }else{
                if(_it._edge == "rising")
                {
                    _mod._name = QString("R_TRIG_%1_TMP_VAR").arg(_it._localId);
                    _mod._type = QString("R_TRIG");
                    _mod._code = QString("(CLK := %1)").arg(_m_contact_item[_it._localId]._expression);
                    _mod._out = QString(".Q");
                    _mod._mod_type = MT_CONTACT_RISING;
                    _m_contact_item[_it._localId]._expression = QString("%1").arg(_mod._name);
                    _m_contact_item[_it._localId]._return_type = QString("R_TRIG");
                    _m_contact_modificator_item.insert(_it._localId, _mod);
                }else
                if(_it._edge == "falling")
                {
                    _mod._name = QString("F_TRIG_%1_TMP_VAR").arg(_it._localId);
                    _mod._type = QString("F_TRIG");
                    _mod._code = QString("(CLK := %1)").arg(_m_contact_item[_it._localId]._expression);
                    _mod._out = QString(".Q");
                    _mod._mod_type = MT_CONTACT_FALLING;
                    _m_contact_item[_it._localId]._expression = QString("%1").arg(_mod._name);
                    _m_contact_item[_it._localId]._return_type = QString("F_TRIG");
                    _m_contact_modificator_item.insert(_it._localId, _mod);
                }
            }
        }
    }

    foreach(T_POU_LD_ITEM _it, _m_coil_item)
    {
        T_MODIFICATOR _mod;
        _mod._localId = _it._localId;
        if(_it._negated)
        {
            _m_coil_item[_it._localId]._expression = QString("%1").arg(_m_coil_item[_it._localId]._expression);
            qint32 _id = _it._point_in[0]._connection[0]._refLocalId;
            QString _var = "";
            do{
                T_MODIFICATOR _next_mod;
                _id = checkCoilConnectionChain(_mod._name, _id, MT_COIL_NOT, _next_mod);
                _var += _next_mod._name + _next_mod._out;
                if((_id != 0) && (_next_mod._name != ""))_var += " AND ";
                if(_next_mod._type != "")
                    _mod._var_declaration += QString("    %1 : %2;\n").arg(_next_mod._name, _next_mod._type);
                if(_next_mod._code != "")
                    _mod._code_declaration += QString("  %1%2;\n").arg(_next_mod._name, _next_mod._code);
            }while(_id != 0);
            _mod._code = QString("%1 := NOT(%2)").arg(_m_coil_item[_it._localId]._expression, _var);
            _mod._out = "";
            _mod._type = "";
            _mod._mod_type = MT_COIL_NOT;
        }else{
            if(_it._edge == "rising")
            {
                _mod._name = QString("R_TRIG_%1_TMP_VAR").arg(_it._localId);
                _mod._type = QString("R_TRIG");
                qint32 _id = _it._point_in[0]._connection[0]._refLocalId;
                QString _var = "";
                do{
                    T_MODIFICATOR _next_mod;
                    _id = checkCoilConnectionChain(_mod._name, _id, MT_COIL_RISING, _next_mod);
                    _var += _next_mod._name + _next_mod._out;
                    if((_id != 0) && (_next_mod._name != ""))_var += " AND ";
                    if(_next_mod._type != "")
                        _mod._var_declaration += QString("    %1 : %2;\n").arg(_next_mod._name, _next_mod._type);
                    if(_next_mod._code != "")
                        _mod._code_declaration += QString("  %1%2;\n").arg(_next_mod._name, _next_mod._code);
                }while(_id != 0);
                _mod._code = QString("(CLK := %1);\n").arg(_var);
                _mod._code += QString("  %1 := %2").arg(_m_coil_item[_it._localId]._expression, _mod._name);
                _mod._out = ".Q";
                _mod._mod_type = MT_COIL_RISING;
            }else
            if(_it._edge == "falling")
            {
                _mod._name = QString("F_TRIG_%1_TMP_VAR").arg(_it._localId);
                _mod._type = QString("F_TRIG");
                qint32 _id = _it._point_in[0]._connection[0]._refLocalId;
                QString _var = "";
                do{
                    T_MODIFICATOR _next_mod;
                    _id = checkCoilConnectionChain(_mod._name, _id, MT_COIL_FALLING, _next_mod);
                    _var += _next_mod._name + _next_mod._out;
                    if((_id != 0) && (_next_mod._name != ""))_var += " AND ";
                    if(_next_mod._type != "")
                        _mod._var_declaration += QString("    %1 : %2;\n").arg(_next_mod._name, _next_mod._type);
                    if(_next_mod._code != "")
                        _mod._code_declaration += QString("  %1%2;\n").arg(_next_mod._name, _next_mod._code);
                }while(_id != 0);
                _mod._code = QString("(CLK := %1);\n").arg(_var);
                _mod._code += QString("  %1 := %2").arg(_m_coil_item[_it._localId]._expression, _mod._name);
                _mod._out = ".Q";
                _mod._mod_type = MT_COIL_FALLING;
            }else
            if(_it._storage == "set")
            {
                _mod._name = QString("SET_%1_TMP_VAR").arg(_it._localId);
                qint32 _id = _it._point_in[0]._connection[0]._refLocalId;
                QString _var = "";
                do{
                    T_MODIFICATOR _next_mod;
                    _id = checkCoilConnectionChain(_mod._name, _id, MT_COIL_SET, _next_mod);
                    _var += _next_mod._name + _next_mod._out;
                    if((_id != 0) && (_next_mod._name != ""))_var += " AND ";
                    if(_next_mod._type != "")
                        _mod._var_declaration += QString("    %1 : %2;\n").arg(_next_mod._name, _next_mod._type);
                    if(_next_mod._code != "")
                        _mod._code_declaration += QString("  %1%2;\n").arg(_next_mod._name, _next_mod._code);
                }while(_id != 0);
                _mod._code = QString("IF %1 THEN\n    %2 := TRUE;\n    END_IF").arg(_var, _m_coil_item[_it._localId]._expression);
                _mod._out = "";
                _mod._type = "";
                _mod._mod_type = MT_COIL_SET;
            }else
            if(_it._storage == "reset")
            {
                _mod._name = QString("RESET_%1_TMP_VAR").arg(_it._localId);
                qint32 _id = _it._point_in[0]._connection[0]._refLocalId;
                QString _var = "";
                do{
                    T_MODIFICATOR _next_mod;
                    _id = checkCoilConnectionChain(_mod._name, _id, MT_COIL_RESET, _next_mod);
                    _var += _next_mod._name + _next_mod._out;
                    if((_id != 0) && (_next_mod._name != ""))_var += " AND ";
                    if(_next_mod._type != "")
                        _mod._var_declaration += QString("    %1 : %2;\n").arg(_next_mod._name, _next_mod._type);
                    if(_next_mod._code != "")
                        _mod._code_declaration += QString("  %1%2;\n").arg(_next_mod._name, _next_mod._code);
                }while(_id != 0);
                _mod._code = QString("IF %1 THEN\n    %2 := FALSE;\n    END_IF").arg(_var, _m_coil_item[_it._localId]._expression);
                _mod._out = "";
                _mod._type = "";
                _mod._mod_type = MT_COIL_RESET;
            }else{
                _mod._name = QString("NONE_%1_TMP_VAR").arg(_it._localId);
                qint32 _id = _it._point_in[0]._connection[0]._refLocalId;
                QString _var;
                do{
                    T_MODIFICATOR _next_mod;
                    _id = checkCoilConnectionChain(_mod._name, _id, MT_NONE, _next_mod);
                    _var += _next_mod._name + _next_mod._out;
                    if((_id != 0) && (_next_mod._name != ""))_var += " AND ";
                    if(_next_mod._type != "")
                        _mod._var_declaration += QString("    %1 : %2;\n").arg(_next_mod._name, _next_mod._type);
                    if(_next_mod._code != "")
                        _mod._code_declaration += QString("  %1%2;\n").arg(_next_mod._name, _next_mod._code);
                }while(_id != 0);
                _mod._code = QString("%1 := %2").arg(_m_coil_item[_it._localId]._expression, _var);
                _mod._out = "";
                _mod._type = "";
                _mod._mod_type = MT_NONE;
            }
        }
        _m_coil_modificator_item.insert(_it._localId, _mod);
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
qint32 TranslatorLD::checkCoilConnectionChain(QString _target_name, qint32 _var_id, T_MODIFICATOR_TYPE _modificator_type, T_MODIFICATOR &_mod)
{
    qint32 _result = 0;

    if(itemIsBlock(_var_id))
    {
        _mod._name = QString("%1.%1").arg(_m_block_item[_var_id]._instanceName, _m_item[_var_id]._outputVariables[0]._formalParameter);
        _result = 0;
    }else
    if(itemIsFunc(_var_id))
    {
        _mod._name = QString("%1").arg(_m_func_item[_var_id]._expression);
        _result = 0;
    }else
    if(itemIsInVar(_var_id))
    {
        _mod._name = QString("%1").arg(_m_in_var_item[_var_id]._expression);
        _result = 0;
    }else
    if(itemIsInOutVar(_var_id))
    {
        _mod._name = QString("%1").arg(_m_in_out_var_item[_var_id]._expression);
        _result = 0;
    }else
    if(itemIsContinuation(_var_id))
    {
    }else
    if(itemIsContact(_var_id))
    {
        switch(_modificator_type)
        {
        case MT_COIL_SET:
        case MT_COIL_RESET:
        case MT_COIL_NOT:
        case MT_COIL_RISING:
        case MT_COIL_FALLING:{
            if(_m_contact_modificator_item[_var_id]._type == "")
            {
                _mod._name = _m_contact_modificator_item[_var_id]._name;
                _mod._type = "";
                _mod._code = "";
                _mod._out = "";
            }else{
                _mod._name = QString("%1_%2").arg(_target_name, _m_contact_modificator_item[_var_id]._name);
                _mod._code = _m_contact_modificator_item[_var_id]._code;
                _mod._out = _m_contact_modificator_item[_var_id]._out;
                _mod._type = _m_contact_modificator_item[_var_id]._type;
            }
            _m_contact_modificator_item[_var_id]._is_used = true;
        }break;
        case MT_NONE:
        case MT_CONTACT_NOT:
        case MT_CONTACT_RISING:
        case MT_CONTACT_FALLING:{
            _mod._name = "";
        }break;
        }
        _result = _m_contact_item[_var_id]._point_in[0]._connection[0]._refLocalId;
    }else
    if(itemIsCoil(_var_id))
    {
        _mod._name = "";
        _result = _m_coil_item[_var_id]._point_in[0]._connection[0]._refLocalId;
    }else
    if(itemIsLeftPowerRail(_var_id))
    {
        _mod._name = "TRUE";
        _result = 0;
    }else
    if(itemIsRightPowerRail(_var_id))
    {
        _mod._name = "FALSE";
        _result = 0;
    }
    return _result;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
QString TranslatorLD::get_return_type(QString _function_name)
{
    QDomNode _iface = StandardLibrary::instance()->find_pou(_function_name).firstChild();
    QDomNode _param = _iface.firstChild();

    while(!_param.isNull())
    {
        if(_param.toElement().tagName() == "returnType")
        {
            QString _type = _param.firstChild().toElement().tagName();
            if(_type == "ANY_NUM")  _type = "INT";
            if(_type == "ANY_INT")  _type = "INT";
            if(_type == "ANY_REAL") _type = "LREAL";
            if(_type == "ANY_BIT")  _type = "BOOL";
            if(_type == "ANY_NBIT") _type = "BYTE";

            return _type;
        }
        _param = _param.nextSibling();
    }
    return {};
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void TranslatorLD::checkIsChainUsed()
{
    foreach(T_POU_LD_ITEM _it, _m_item)
    {
        switch(_it._type)
        {
        case IT_LD_BLOCK:
        case IT_LD_FUNCTION:
        case IT_LD_INPUT:
        case IT_LD_OUTPUT:
        case IT_LD_INPUT_OUTPUT:
        case IT_LD_LEFT_POWER_RAIL:
        case IT_LD_RIGHT_POWER_RAIL:
        case IT_LD_CONTACT:
        case IT_LD_COIL:
        case IT_LD_CONNECTOR:
        case IT_LD_CONTINUATION:{
            foreach(T_POU_LD_ITEM _it_next, _m_item)
            {
                switch(_it_next._type)
                {

                case IT_LD_BLOCK:
                case IT_LD_FUNCTION:{
                    for(int _i = 0; _i < _it_next._inputVariables.size(); _i++)
                        if(_it._localId == _it_next._inputVariables[_i]._connection._refLocalId)
                            _m_item[_it._localId]._is_chain_used = true;
                }break;
                case IT_LD_INPUT:
                case IT_LD_OUTPUT:
                case IT_LD_INPUT_OUTPUT:
                case IT_LD_LEFT_POWER_RAIL:
                case IT_LD_RIGHT_POWER_RAIL:
                case IT_LD_CONTACT:
                case IT_LD_COIL:
                case IT_LD_CONNECTOR:
                case IT_LD_CONTINUATION:{
                    for(int _i = 0; _i < _it_next._point_in.size(); _i++)
                        for(int _j = 0; _j < _it_next._point_in[_i]._connection.size(); _j++)
                            if(_it._localId == _it_next._point_in[_i]._connection[_j]._refLocalId)
                                _m_item[_it._localId]._is_chain_used = true;
                }break;

                case IT_LD_NOT_DEFINED:
                case IT_LD_COMMENT:
                case IT_LD_MAX:{
                }break;
                }
            }
        }break;

        case IT_LD_NOT_DEFINED:
        case IT_LD_COMMENT:
        case IT_LD_MAX:{
        }break;
        }
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

/*
--------------------------------
  R_TRIG1(CLK := ov1);
  F_TRIG1(CLK := iv9);
  R_TRIG2(CLK := iv8);
  SR0(S1 := TRUE, R := R_TRIG1.Q AND F_TRIG1.Q AND R_TRIG2.Q AND iov2);
  ov3 := SR0.Q1;
  F_TRIG2(CLK := iov1);
  iov2 := NOT(iov0) AND iov3 AND F_TRIG2.Q AND iv12;
  F_TRIG3(CLK := iov1);
  R_TRIG3(CLK := NOT(iov0) AND iov3 AND F_TRIG3.Q AND iv12);
  iv6 := R_TRIG3.Q;
  F_TRIG4(CLK := iov1);
  F_TRIG5(CLK := NOT(iov0) AND iov3 AND F_TRIG4.Q AND iv12);
  iv7 := F_TRIG5.Q;
  R_TRIG4(CLK := ov1);
  F_TRIG6(CLK := iv9);
  R_TRIG5(CLK := iv8);
  IF R_TRIG4.Q AND F_TRIG6.Q AND R_TRIG5.Q AND iov2 THEN
    ov0 := TRUE; (*set*)
  END_IF;
  F_TRIG7(CLK := iv9);
  R_TRIG6(CLK := iv8);
  F_TRIG8(CLK := F_TRIG7.Q AND R_TRIG6.Q AND iov2);
  ov2 := F_TRIG8.Q;
  F_TRIG9(CLK := iov1);
  IF iov3 AND F_TRIG9.Q AND iv12 THEN
    iv0 := FALSE; (*reset*)
  END_IF;
  F_TRIG10(CLK := iov1);
  R_TRIG7(CLK := iov8 AND F_TRIG10.Q AND iv12);
  iov9 := R_TRIG7.Q;
  F_TRIG11(CLK := iov1);
  R_TRIG8(CLK := iv1);
  SEMA0(CLAIM := iov8 AND F_TRIG11.Q AND iv12, RELEASE := R_TRIG8.Q AND iv2);
  iov0 := SEMA0.BUSY;
--------------------------------
--------------------------------
  R_TRIG_59_TMP_VAR_SR0(CLK := ov1);
  F_TRIG_57_TMP_VAR_SR0(CLK := iv9);
  R_TRIG_56_TMP_VAR_SR0(CLK := iv8);
  SR0(S1 := TRUE, R := R_TRIG_59_TMP_VAR_SR0.Q AND F_TRIG_57_TMP_VAR_SR0.Q AND R_TRIG_56_TMP_VAR_SR0.Q AND iov2);
  ov3 := SR0.Q1;
  F_TRIG_63_TMP_VAR_SEMA0(CLK := iov1);
  R_TRIG_71_TMP_VAR_SEMA0(CLK := iv1);
  SEMA0(CLAIM := iov8 AND F_TRIG_63_TMP_VAR_SEMA0.Q AND iv12, RELEASE := R_TRIG_71_TMP_VAR_SEMA0.Q AND iv2);
  iov0 := SEMA0.BUSY;
  F_TRIG_63_TMP_VAR_iov2(CLK := iov1);
  iov2 := NOT(iov0) OR iov3 OR F_TRIG_63_TMP_VAR_iov2.Q OR iv12;
  R_TRIG_50_TMP_VAR_F_TRIG_63_TMP_VAR(CLK := iov1);
  R_TRIG_50_TMP_VAR(CLK := NOT(iov0) AND iov3 AND R_TRIG_50_TMP_VAR_F_TRIG_63_TMP_VAR.Q AND iv12);
  iv6 := R_TRIG_50_TMP_VAR.Q;
  F_TRIG_51_TMP_VAR_F_TRIG_63_TMP_VAR(CLK := iov1);
  F_TRIG_51_TMP_VAR(CLK := NOT(iov0) AND iov3 AND F_TRIG_51_TMP_VAR_F_TRIG_63_TMP_VAR.Q AND iv12);
  iv7 := F_TRIG_51_TMP_VAR.Q;
  SET_58_TMP_VAR_R_TRIG_59_TMP_VAR(CLK := ov1);
  SET_58_TMP_VAR_F_TRIG_57_TMP_VAR(CLK := iv9);
  SET_58_TMP_VAR_R_TRIG_56_TMP_VAR(CLK := iv8);
  IF SET_58_TMP_VAR_R_TRIG_59_TMP_VAR.Q AND SET_58_TMP_VAR_F_TRIG_57_TMP_VAR.Q AND SET_58_TMP_VAR_R_TRIG_56_TMP_VAR.Q AND iov2 THEN
    ov0 := TRUE;
    END_IF;
  F_TRIG_60_TMP_VAR_F_TRIG_57_TMP_VAR(CLK := iv9);
  F_TRIG_60_TMP_VAR_R_TRIG_56_TMP_VAR(CLK := iv8);
  F_TRIG_60_TMP_VAR(CLK := F_TRIG_60_TMP_VAR_F_TRIG_57_TMP_VAR.Q AND F_TRIG_60_TMP_VAR_R_TRIG_56_TMP_VAR.Q AND iov2);
  ov2 := F_TRIG_60_TMP_VAR.Q;
  RESET_61_TMP_VAR_F_TRIG_63_TMP_VAR(CLK := iov1);
  IF iov3 AND RESET_61_TMP_VAR_F_TRIG_63_TMP_VAR.Q AND iv12 THEN
    iv0 := FALSE;
    END_IF;
  R_TRIG_69_TMP_VAR_F_TRIG_63_TMP_VAR(CLK := iov1);
  R_TRIG_69_TMP_VAR(CLK := iov8 AND R_TRIG_69_TMP_VAR_F_TRIG_63_TMP_VAR.Q AND iv12);
  iov9 := R_TRIG_69_TMP_VAR.Q;
--------------------------------
*/
