#include "TranslatorFbd.h"

TranslatorFBD::TranslatorFBD() {}

// *** POU
//
//-----------------------------------------------------------------------------------
void TranslatorFBD::Code_STgenerator(T_POU pou_, QString &text_)
{
    _m_item.clear();
    _m_execution_order_item.clear();
    _m_generator_item.clear();

    for(int _i = 0; _i < (int)pou_._body._FBD._item.size(); _i++)
        _m_item.insert(pou_._body._FBD._item[_i]._localId, pou_._body._FBD._item[_i]);

    parseItem(&pou_);
    prepareFuncTempVar();
    prepareVarType();
    prepareConnectContinuation();
    prepareVar();
    prepareFunc();
    AllVar_STgenerator(&pou_, text_);

    if(!_m_func_item.empty())
    {
        text_ += "  VAR\n";

        foreach(T_POU_FBD_ITEM_SHORT _it, _m_func_item)
            text_ += QString("    %1 : %2;\n").arg(_m_func_item[_it._localId]._expression, _m_func_item[_it._localId]._return_type);
        text_ += "  END_VAR\n\n";
    }

    prepareBlock();

    _m_execution_order_item.clear();
    foreach(T_POU_FBD_ITEM_SHORT _it, _m_block_item)
        if(_it._executionOrderId != 0)
        {
            _m_execution_order_item.insert(_it._executionOrderId, _it);
            _m_block_item.remove(_it._localId);
        }

    foreach(T_POU_FBD_ITEM_SHORT _it, _m_func_item)
        if(_it._executionOrderId != 0)
        {
            _m_execution_order_item.insert(_it._executionOrderId, _it);
            _m_func_item.remove(_it._localId);
        }

    foreach(T_POU_FBD_ITEM_SHORT _it, _m_execution_order_item)
    {
        switch(_it._type)
        {
        case IT_FBD_BLOCK:{         Block_STcode(_it, text_); }break;
        case IT_FBD_FUNCTION:{      Func_STcode(_it, text_);  }break;
        case IT_FBD_OUTPUT:{        Var_STcode(_it, text_);   }break;
        case IT_FBD_INPUT_OUTPUT:{  Var_STcode(_it, text_);   }break;
        case IT_FBD_MAX:
        case IT_FBD_COMMENT:
        case IT_FBD_INPUT:
        case IT_FBD_CONNECTOR:
        case IT_FBD_NOT_DEFINED:
        case IT_FBD_CONTINUATION:{}break;
        }
    }

    foreach(T_POU_FBD_ITEM_SHORT _it, _m_block_item)        Block_STcode(_it, text_);
    foreach(T_POU_FBD_ITEM_SHORT _it, _m_func_item)         Func_STcode(_it, text_);
    foreach(T_POU_FBD_ITEM_SHORT _it, _m_in_out_var_item)   Var_STcode(_it, text_);
    foreach(T_POU_FBD_ITEM_SHORT _it, _m_out_var_item)      Var_STcode(_it, text_);

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
void TranslatorFBD::Code_STgenerator(T_POU_BODY_FBD _fbd, QString &text_)
{
    _m_item.clear();
    _m_execution_order_item.clear();
    _m_generator_item.clear();

    for(int _i = 0; _i < (int)_fbd._item.size(); _i++)
        _m_item.insert(_fbd._item[_i]._localId, _fbd._item[_i]);

    parseItem(&_fbd);
    prepareFuncTempVar();
    prepareVarType();
    prepareConnectContinuation();
    prepareVar();
    prepareFunc();

    if(!_m_func_item.empty())
    {
        text_ += "  VAR\n";

        foreach(T_POU_FBD_ITEM_SHORT _it, _m_func_item)
            text_ += QString("    %1 : %2;\n").arg(_m_func_item[_it._localId]._expression, _m_func_item[_it._localId]._return_type);
        text_ += "  END_VAR\n\n";
    }

    prepareBlock();

    _m_execution_order_item.clear();
    foreach(T_POU_FBD_ITEM_SHORT _it, _m_block_item)
        if(_it._executionOrderId != 0)
        {
            _m_execution_order_item.insert(_it._executionOrderId, _it);
            _m_block_item.remove(_it._localId);
        }

    foreach(T_POU_FBD_ITEM_SHORT _it, _m_func_item)
        if(_it._executionOrderId != 0)
        {
            _m_execution_order_item.insert(_it._executionOrderId, _it);
            _m_func_item.remove(_it._localId);
        }

    foreach(T_POU_FBD_ITEM_SHORT _it, _m_execution_order_item)
    {
        switch(_it._type)
        {
        case IT_FBD_BLOCK:{         Block_STcode(_it, text_); }break;
        case IT_FBD_FUNCTION:{      Func_STcode(_it, text_);  }break;
        case IT_FBD_OUTPUT:{        Var_STcode(_it, text_);   }break;
        case IT_FBD_INPUT_OUTPUT:{  Var_STcode(_it, text_);   }break;
        case IT_FBD_MAX:
        case IT_FBD_COMMENT:
        case IT_FBD_INPUT:
        case IT_FBD_CONNECTOR:
        case IT_FBD_NOT_DEFINED:
        case IT_FBD_CONTINUATION:{}break;
        }
    }

    foreach(T_POU_FBD_ITEM_SHORT _it, _m_block_item)        Block_STcode(_it, text_);
    foreach(T_POU_FBD_ITEM_SHORT _it, _m_func_item)         Func_STcode(_it, text_);
    foreach(T_POU_FBD_ITEM_SHORT _it, _m_in_out_var_item)   Var_STcode(_it, text_);
    foreach(T_POU_FBD_ITEM_SHORT _it, _m_out_var_item)      Var_STcode(_it, text_);
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void TranslatorFBD::Block_STcode(T_POU_FBD_ITEM_SHORT _block, QString &text_)
{
    //    if(_block._inputVariables.isEmpty()) return;

    text_ += "  ";
    text_ += _block._instanceName + "(";
    for(int _j = 0; _j < _block._inputVariables.size(); _j++)
    {
        text_ += _block._inputVariables[_j]._name;
        if((_j + 1) < _block._inputVariables.size()) text_ += ", ";
    }
    text_ += ");\n";

    if(!_block._outputVariables.isEmpty())
    {
        foreach(T_CONNECTION_VAR _var, _block._outputVariables)
            text_ += QString("  %1;\n").arg(_var._name);
    }

    if(!_block._inOutVariables.isEmpty())
    {
        foreach(T_CONNECTION_VAR _var, _block._inOutVariables)
            text_ += QString("  %1;\n").arg(_var._name);
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void TranslatorFBD::Func_STcode(T_POU_FBD_ITEM_SHORT _func, QString &text_)
{
    //    if(_func._inputVariables.isEmpty()) return;

    text_ += "  ";
    text_ += _func._expression + " := ";
    text_ += _func._typeName + "(";

    for(int _j = 0; _j < _func._inputVariables.size(); _j++)
    {
        text_ += _func._inputVariables[_j]._name;
        if((_j + 1) < _func._inputVariables.size()) text_ += ", ";
    }
    text_ += ");\n";

    if(!_func._outputVariables.isEmpty())
    {
        foreach(T_CONNECTION_VAR _var, _func._outputVariables)
            text_ += QString("  %1;\n").arg(_var._name);
    }

    if(!_func._inOutVariables.isEmpty())
    {
        foreach(T_CONNECTION_VAR _var, _func._inOutVariables)
            text_ += QString("  %1;\n").arg(_var._name);
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void TranslatorFBD::Var_STcode(T_POU_FBD_ITEM_SHORT _var, QString &text_)
{
    if(_var._is_used) return;
    if(_var._inputVariables.isEmpty()) return;

    text_ += "  ";
    text_ += _var._inputVariables[0]._name + ";\n";
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void TranslatorFBD::prepareBlock()
{
    foreach(T_POU_FBD_ITEM_SHORT _it, _m_block_item)
    {
        quint32 _block_id = _it._localId;

        for(int _v = 0; _v < (int)_m_item[_block_id]._inputVariables.size(); _v++)
        {
            if(_m_item[_block_id]._inputVariables[_v]._connection._refLocalId != -1)
            {
                T_CONNECTION_VAR _var;
                quint32 _var_id = _m_item[_block_id]._inputVariables[_v]._connection._refLocalId;
                _var._name = _m_item[_block_id]._inputVariables[_v]._formalParameter + " := ";

                if(itemIsBlock(_var_id))
                {
                    _var._name += _m_block_item[_var_id]._instanceName;
                    _var._name += ".";
                    _var._name += _m_item[_block_id]._inputVariables[_v]._connection._formalParameter;
                    _var._type = "BOOL";
                }else
                    if(itemIsFunc(_var_id))
                    {
                        _var._name += _m_func_item[_var_id]._expression;
                        _var._type = _m_func_item[_var_id]._return_type;
                    }else
                        if(itemIsInVar(_var_id))
                        {
                            _var._name += _m_in_var_item[_var_id]._expression;
                            _var._type = _m_in_var_item[_var_id]._return_type;
                        }else
                            if(itemIsInOutVar(_var_id))
                            {
                                _var._name += _m_in_out_var_item[_var_id]._expression;
                                _var._type = _m_in_out_var_item[_var_id]._return_type;
                            }else
                                if(itemIsContinuation(_var_id))
                                {
                                    if(!_m_continuation_item[_var_id]._inputVariables.isEmpty())
                                    {
                                        _var._name += _m_continuation_item[_var_id]._inputVariables[0]._name;
                                        _var._type = _m_continuation_item[_var_id]._inputVariables[0]._type;
                                    }
                                }
                _m_block_item[_block_id]._inputVariables.push_back(_var);
            }
        }
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void TranslatorFBD::prepareFuncTempVar()
{
    foreach(T_POU_FBD_ITEM_SHORT _it, _m_func_item)
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
void TranslatorFBD::prepareFunc()
{
    // QString _temp_var;
    // QString _var_type;

    foreach(T_POU_FBD_ITEM_SHORT _it, _m_func_item)
    {
        quint32 _func_id = _it._localId;

        for(int _v = 0; _v < (int)_m_item[_func_id]._inputVariables.size(); _v++)
        {
            if(_m_item[_func_id]._inputVariables[_v]._connection._refLocalId != -1)
            {
                quint32 _var_id = _m_item[_func_id]._inputVariables[_v]._connection._refLocalId;
                T_CONNECTION_VAR _var;

                if(itemIsBlock(_var_id))
                {
                    _var._name += _m_block_item[_var_id]._instanceName;
                    _var._name += ".";
                    _var._name += _m_item[_func_id]._inputVariables[_v]._connection._formalParameter;
                    _var._type = "BOOL";
                }else
                if(itemIsFunc(_var_id))
                {
                    _var._name += _m_func_item[_var_id]._expression;
                    _var._type = _m_func_item[_func_id]._return_type;
                    _m_func_item[_var_id]._return_type = _m_func_item[_func_id]._return_type;
                }else
                if(itemIsInVar(_var_id))
                {
                    _var._name += _m_in_var_item[_var_id]._expression;
                    _var._type = _m_in_var_item[_var_id]._return_type;
                }else
                if(itemIsOutVar(_var_id))
                {
                    _var._name += _m_out_var_item[_var_id]._expression;
                    _var._type = _m_out_var_item[_var_id]._return_type;
                }else
                if(itemIsInOutVar(_var_id))
                {
                    _var._name += _m_in_out_var_item[_var_id]._expression;
                    _var._type = _m_in_out_var_item[_var_id]._return_type;
                }else
                if(itemIsContinuation(_var_id))
                {
                    if(!_m_continuation_item[_var_id]._inputVariables.isEmpty())
                    {
                        _var._name += _m_continuation_item[_var_id]._inputVariables[0]._name;
                        _var._type = _m_continuation_item[_var_id]._inputVariables[0]._type;
                    }
                }
                _m_func_item[_func_id]._inputVariables.push_back(_var);
            }
        }
    }

    //    foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_func_item)
    //    {
    //        quint32 _func_id = _it._localId;

    //        for(int _v = 0; _v < (int)_m_pou_item[_func_id]._inputVariables.size(); _v++)
    //        {
    //            if(_m_pou_item[_func_id]._inputVariables[_v]._connection._refLocalId != -1)
    //            {
    //                quint32 _var_id = _m_pou_item[_func_id]._inputVariables[_v]._connection._refLocalId;
    //                if(itemIsFunc(_var_id))
    //                    _m_pou_func_item[_var_id]._return_type = _m_pou_func_item[_func_id]._return_type;
    //            }
    //        }
    //    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void TranslatorFBD::prepareVarType()
{
//    QString _var_type;

    foreach(T_POU_FBD_ITEM_SHORT _it, _m_out_var_item)
    {
        quint32 _var_id = _it._localId;
        quint32 _connect_id = _m_item[_var_id]._connection._refLocalId;

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
                        }
    }
    foreach(T_POU_FBD_ITEM_SHORT _it, _m_in_out_var_item)
    {
        quint32 _var_id = _it._localId;
        quint32 _connect_id = _m_item[_var_id]._connection._refLocalId;

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
                        }
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void TranslatorFBD::prepareVar()
{
    bool _is_connected;

    foreach(T_POU_FBD_ITEM_SHORT _it, _m_out_var_item)
    {
        T_CONNECTION_VAR _var;

        _is_connected = false;
        quint32 _out_var_id = _it._localId;
        quint32 _connect_id = _m_item[_out_var_id]._connection._refLocalId;
        _var._name = _m_item[_out_var_id]._expression + " := ";
        _var._type = _m_item[_out_var_id]._return_type;

        if(itemIsBlock(_connect_id))
        {
            _is_connected = true;
            _var._name += _m_block_item[_connect_id]._instanceName;
            _var._name += ".";
            _var._name += _m_item[_out_var_id]._connection._formalParameter;
            _m_block_item[_connect_id]._outputVariables.push_back(_var);
            _m_out_var_item[_out_var_id]._is_used = true;
        }else
        if(itemIsFunc(_connect_id))
        {
            _is_connected = true;
            _var._name += _m_func_item[_connect_id]._expression;
            _m_func_item[_connect_id]._outputVariables.push_back(_var);
            _m_out_var_item[_out_var_id]._is_used = true;
        }else
        if(itemIsInVar(_connect_id))
        {
            _is_connected = true;
            _var._name += _m_in_var_item[_connect_id]._expression;
        }else
        if(itemIsInOutVar(_connect_id))
        {
            _is_connected = true;
            _var._name += _m_in_out_var_item[_connect_id]._expression;
        }else
        if(itemIsContinuation(_connect_id))
        {
            if(!_m_continuation_item[_connect_id]._inputVariables.isEmpty())
            {
                _is_connected = true;
                _var._name += _m_continuation_item[_connect_id]._inputVariables[0]._name;
                quint32 _connect_dev_id = _m_item[_connect_id]._connection._refLocalId;
                if(itemIsBlock(_connect_dev_id))
                {
                    _m_block_item[_connect_dev_id]._outputVariables.push_back(_var);
                    _m_out_var_item[_out_var_id]._is_used = true;
                }else
                if(itemIsFunc(_connect_dev_id))
                {
                    _m_func_item[_connect_dev_id]._outputVariables.push_back(_var);
                    _m_out_var_item[_out_var_id]._is_used = true;
                }
            }
        }
        if(_is_connected)
            _m_out_var_item[_out_var_id]._inputVariables.push_back(_var);
    }

    foreach(T_POU_FBD_ITEM_SHORT _it, _m_in_out_var_item)
    {
        T_CONNECTION_VAR _var;

        _is_connected = false;
        quint32 _out_var_id = _it._localId;
        quint32 _connect_id = _m_item[_out_var_id]._connection._refLocalId;
        _var._name = _m_item[_out_var_id]._expression + " := ";
        _var._type = _m_item[_out_var_id]._return_type;

        if(itemIsBlock(_connect_id))
        {
            _is_connected = true;
            _var._name += _m_block_item[_connect_id]._instanceName;
            _var._name += ".";
            _var._name += _m_item[_out_var_id]._connection._formalParameter;
            _m_block_item[_connect_id]._inOutVariables.push_back(_var);
            _m_in_out_var_item[_out_var_id]._is_used = true;
        }else
        if(itemIsFunc(_connect_id))
        {
            _is_connected = true;
            _var._name += _m_func_item[_connect_id]._expression;
            _m_func_item[_connect_id]._inOutVariables.push_back(_var);
            _m_in_out_var_item[_out_var_id]._is_used = true;
        }else
        if(itemIsInVar(_connect_id))
        {
            _is_connected = true;
            _var._name += _m_in_var_item[_connect_id]._expression;
        }else
        if(itemIsInOutVar(_connect_id))
        {
            _is_connected = true;
            _var._name += _m_in_out_var_item[_connect_id]._expression;
        }else
        if(itemIsContinuation(_connect_id))
        {
            if(!_m_continuation_item[_connect_id]._inputVariables.isEmpty())
            {
                _is_connected = true;
                _var._name += _m_continuation_item[_connect_id]._inputVariables[0]._name;
            }
        }
        if(_is_connected)
            _m_in_out_var_item[_out_var_id]._inputVariables.push_back(_var);
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
quint32 TranslatorFBD::linkConnect(quint32 _connect_id)
{
    quint32 _id = 0;
    foreach(T_POU_FBD_ITEM_SHORT _it, _m_continuation_item)
        if(_it._name == _m_connect_item[_connect_id]._name)
        {
            _id = _it._localId;
            break;
        }
    return _id;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void TranslatorFBD::prepareConnectContinuation()
{
    foreach(T_POU_FBD_ITEM_SHORT _it, _m_connect_item)
    {
        T_CONNECTION_VAR _var;

        qint32 _connect_id = _it._localId;
        switch(_m_item[_m_item[_connect_id]._connection._refLocalId]._type)
        {
        case IT_FBD_BLOCK:{
            _var._name = QString("%1.%2")
            .arg(_m_item[_m_item[_connect_id]._connection._refLocalId]._instanceName)
                .arg(_m_item[_connect_id]._connection._formalParameter);
            _m_connect_item[_connect_id]._return_type = _m_block_item[_m_item[_connect_id]._connection._refLocalId]._return_type;
            _var._type = _m_connect_item[_connect_id]._return_type;
        }break;
        case IT_FBD_FUNCTION:{
            _var._name = QString("%1")
            .arg(_m_item[_m_item[_connect_id]._connection._refLocalId]._expression);
            _m_connect_item[_connect_id]._return_type = _m_func_item[_m_item[_connect_id]._connection._refLocalId]._return_type;
            _var._type = _m_connect_item[_connect_id]._return_type;
        }break;
        case IT_FBD_INPUT:{
            _var._name = QString("%1")
            .arg(_m_item[_m_item[_connect_id]._connection._refLocalId]._expression);
            _m_connect_item[_connect_id]._return_type = _m_in_var_item[_m_item[_connect_id]._connection._refLocalId]._return_type;
            _var._type = _m_connect_item[_connect_id]._return_type;
        }break;
        case IT_FBD_OUTPUT:{
            _var._name = QString("%1")
            .arg(_m_item[_m_item[_connect_id]._connection._refLocalId]._expression);
            _m_connect_item[_connect_id]._return_type = _m_out_var_item[_m_item[_connect_id]._connection._refLocalId]._return_type;
            _var._type = _m_connect_item[_connect_id]._return_type;
        }break;
        case IT_FBD_INPUT_OUTPUT:{
            _var._name = QString("%1")
            .arg(_m_item[_m_item[_connect_id]._connection._refLocalId]._expression);
            _m_connect_item[_connect_id]._return_type = _m_in_out_var_item[_m_item[_connect_id]._connection._refLocalId]._return_type;
            _var._type = _m_connect_item[_connect_id]._return_type;
        }break;
        case IT_FBD_MAX:
        case IT_FBD_NOT_DEFINED:
        case IT_FBD_COMMENT:
        case IT_FBD_CONNECTOR:
        case IT_FBD_CONTINUATION:{}break;
        }
        _m_connect_item[_connect_id]._outputVariables.push_back(_var);
        quint32 _continuation_id = linkConnect(_connect_id);
        if(_continuation_id != 0)
        {
            _m_continuation_item[_continuation_id]._inputVariables.push_back(_var);
            _m_connect_item[_connect_id]._return_type = _m_continuation_item[_continuation_id]._return_type;
            _m_item[_continuation_id]._connection._refLocalId = _m_item[_connect_id]._connection._refLocalId;
        }
    }

    foreach(T_POU_FBD_ITEM_SHORT _it, _m_continuation_item)
    {
        qint32 _connect_id = _it._localId;
        switch(_m_item[_m_item[_connect_id]._connection._refLocalId]._type)
        {
        case IT_FBD_BLOCK:{
        }break;
        case IT_FBD_FUNCTION:{
            _m_func_item[_m_item[_connect_id]._connection._refLocalId]._return_type = _it._return_type;
        }break;
        case IT_FBD_INPUT:{
        }break;
        case IT_FBD_OUTPUT:{
        }break;
        case IT_FBD_INPUT_OUTPUT:{
        }break;
        case IT_FBD_MAX:
        case IT_FBD_NOT_DEFINED:
        case IT_FBD_COMMENT:
        case IT_FBD_CONNECTOR:
        case IT_FBD_CONTINUATION:{}break;
        }
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool TranslatorFBD::itemIsBlock(quint32 _id)
{
    if(_m_block_item.find(_id) != _m_block_item.end())
        return true;
    return false;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool TranslatorFBD::itemIsFunc(quint32 _id)
{
    if(_m_func_item.find(_id) != _m_func_item.end())
        return true;
    return false;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool TranslatorFBD::itemIsInVar(quint32 _id)
{
    if(_m_in_var_item.find(_id) != _m_in_var_item.end())
        return true;
    return false;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool TranslatorFBD::itemIsOutVar(quint32 _id)
{
    if(_m_out_var_item.find(_id) != _m_out_var_item.end())
        return true;
    return false;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool TranslatorFBD::itemIsInOutVar(quint32 _id)
{
    if(_m_in_out_var_item.find(_id) != _m_in_out_var_item.end())
        return true;
    return false;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool TranslatorFBD::itemIsConnect(quint32 _id)
{
    if(_m_connect_item.find(_id) != _m_connect_item.end())
        return true;
    return false;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool TranslatorFBD::itemIsContinuation(quint32 _id)
{
    if(_m_continuation_item.find(_id) != _m_continuation_item.end())
        return true;
    return false;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void TranslatorFBD::parseItem(T_POU *pou_)
{
    T_POU_FBD_ITEM_SHORT _item;

    _m_in_var_item.clear();
    _m_out_var_item.clear();
    _m_in_out_var_item.clear();

    _m_block_item.clear();
    _m_func_item.clear();
    _m_connect_item.clear();
    _m_continuation_item.clear();

    for(int _i = 0; _i < (int)pou_->_body._FBD._item.size(); _i++)
        if(pou_->_body._FBD._item[_i]._type == IT_FBD_BLOCK)
        {
            _item._type                 = pou_->_body._FBD._item[_i]._type;
            _item._localId              = pou_->_body._FBD._item[_i]._localId;
            _item._executionOrderId     = pou_->_body._FBD._item[_i]._executionOrderId;
            _item._negated              = pou_->_body._FBD._item[_i]._negated;
            _item._expression           = pou_->_body._FBD._item[_i]._expression;
            _item._name                 = pou_->_body._FBD._item[_i]._name;
            _item._typeName             = pou_->_body._FBD._item[_i]._typeName;
            _item._instanceName         = pou_->_body._FBD._item[_i]._instanceName;
            _item._return_type          = "";
            _item._inOutVariables.clear();
            _item._inputVariables.clear();
            _item._outputVariables.clear();
            _m_block_item.insert(_item._localId, _item);
        }

    for(int _i = 0; _i < (int)pou_->_body._FBD._item.size(); _i++)
        if(pou_->_body._FBD._item[_i]._type == IT_FBD_FUNCTION)
        {
            _item._type                 = pou_->_body._FBD._item[_i]._type;
            _item._localId              = pou_->_body._FBD._item[_i]._localId;
            _item._executionOrderId     = pou_->_body._FBD._item[_i]._executionOrderId;
            _item._negated              = pou_->_body._FBD._item[_i]._negated;
            _item._expression           = pou_->_body._FBD._item[_i]._expression;
            _item._name                 = pou_->_body._FBD._item[_i]._name;
            _item._typeName             = pou_->_body._FBD._item[_i]._typeName;
            _item._instanceName         = pou_->_body._FBD._item[_i]._instanceName;
            //            _item._return_type          = pou_->_return_type;
            //            _item._return_type          = getRetTypeStandartFunction(_item._typeName);
            _item._return_type          = "";
            _item._inOutVariables.clear();
            _item._inputVariables.clear();
            _item._outputVariables.clear();
            _m_func_item.insert(_item._localId, _item);
        }

    for(int _i = 0; _i < (int)pou_->_body._FBD._item.size(); _i++)
        if(pou_->_body._FBD._item[_i]._type == IT_FBD_INPUT)
        {
            _item._type                 = pou_->_body._FBD._item[_i]._type;
            _item._localId              = pou_->_body._FBD._item[_i]._localId;
            _item._executionOrderId     = pou_->_body._FBD._item[_i]._executionOrderId;
            _item._negated              = pou_->_body._FBD._item[_i]._negated;
            _item._expression           = pou_->_body._FBD._item[_i]._expression;
            _item._name                 = pou_->_body._FBD._item[_i]._name;
            _item._typeName             = pou_->_body._FBD._item[_i]._typeName;
            _item._instanceName         = pou_->_body._FBD._item[_i]._instanceName;
            _item._return_type          = getTypeByVar(pou_, _item._expression);
            _item._inOutVariables.clear();
            _item._inputVariables.clear();
            _item._outputVariables.clear();
            _m_in_var_item.insert(_item._localId, _item);
        }

    for(int _i = 0; _i < (int)pou_->_body._FBD._item.size(); _i++)
        if(pou_->_body._FBD._item[_i]._type == IT_FBD_OUTPUT)
        {
            _item._type                 = pou_->_body._FBD._item[_i]._type;
            _item._localId              = pou_->_body._FBD._item[_i]._localId;
            _item._executionOrderId     = pou_->_body._FBD._item[_i]._executionOrderId;
            _item._negated              = pou_->_body._FBD._item[_i]._negated;
            _item._expression           = pou_->_body._FBD._item[_i]._expression;
            _item._name                 = pou_->_body._FBD._item[_i]._name;
            _item._typeName             = pou_->_body._FBD._item[_i]._typeName;
            _item._instanceName         = pou_->_body._FBD._item[_i]._instanceName;
            _item._return_type          = getTypeByVar(pou_, _item._expression);
            _item._inOutVariables.clear();
            _item._inputVariables.clear();
            _item._outputVariables.clear();
            _m_out_var_item.insert(_item._localId, _item);
        }

    for(int _i = 0; _i < (int)pou_->_body._FBD._item.size(); _i++)
        if(pou_->_body._FBD._item[_i]._type == IT_FBD_INPUT_OUTPUT)
        {
            _item._type                 = pou_->_body._FBD._item[_i]._type;
            _item._localId              = pou_->_body._FBD._item[_i]._localId;
            _item._executionOrderId     = pou_->_body._FBD._item[_i]._executionOrderId;
            _item._negated              = pou_->_body._FBD._item[_i]._negated;
            _item._expression           = pou_->_body._FBD._item[_i]._expression;
            _item._name                 = pou_->_body._FBD._item[_i]._name;
            _item._typeName             = pou_->_body._FBD._item[_i]._typeName;
            _item._instanceName         = pou_->_body._FBD._item[_i]._instanceName;
            _item._return_type          = getTypeByVar(pou_, _item._expression);
            _item._inOutVariables.clear();
            _item._inputVariables.clear();
            _item._outputVariables.clear();
            _m_in_out_var_item.insert(_item._localId, _item);
        }

    for(int _i = 0; _i < (int)pou_->_body._FBD._item.size(); _i++)
        if(pou_->_body._FBD._item[_i]._type == IT_FBD_CONNECTOR)
        {
            _item._type                 = pou_->_body._FBD._item[_i]._type;
            _item._localId              = pou_->_body._FBD._item[_i]._localId;
            _item._executionOrderId     = pou_->_body._FBD._item[_i]._executionOrderId;
            _item._negated              = pou_->_body._FBD._item[_i]._negated;
            _item._expression           = pou_->_body._FBD._item[_i]._expression;
            _item._name                 = pou_->_body._FBD._item[_i]._name;
            _item._typeName             = pou_->_body._FBD._item[_i]._typeName;
            _item._instanceName         = pou_->_body._FBD._item[_i]._instanceName;
            _item._inOutVariables.clear();
            _item._inputVariables.clear();
            _item._outputVariables.clear();
            _m_connect_item.insert(_item._localId, _item);
        }

    for(int _i = 0; _i < (int)pou_->_body._FBD._item.size(); _i++)
        if(pou_->_body._FBD._item[_i]._type == IT_FBD_CONTINUATION)
        {
            _item._type                 = pou_->_body._FBD._item[_i]._type;
            _item._localId              = pou_->_body._FBD._item[_i]._localId;
            _item._executionOrderId     = pou_->_body._FBD._item[_i]._executionOrderId;
            _item._negated              = pou_->_body._FBD._item[_i]._negated;
            _item._expression           = pou_->_body._FBD._item[_i]._expression;
            _item._name                 = pou_->_body._FBD._item[_i]._name;
            _item._typeName             = pou_->_body._FBD._item[_i]._typeName;
            _item._instanceName         = pou_->_body._FBD._item[_i]._instanceName;
            _item._inOutVariables.clear();
            _item._inputVariables.clear();
            _item._outputVariables.clear();
            _m_continuation_item.insert(_item._localId, _item);
        }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void TranslatorFBD::parseItem(T_POU_BODY_FBD *_fbd)
{
    T_POU_FBD_ITEM_SHORT _item;

    _m_in_var_item.clear();
    _m_out_var_item.clear();
    _m_in_out_var_item.clear();

    _m_block_item.clear();
    _m_func_item.clear();
    _m_connect_item.clear();
    _m_continuation_item.clear();

    for(int _i = 0; _i < (int)_fbd->_item.size(); _i++)
        if(_fbd->_item[_i]._type == IT_FBD_BLOCK)
        {
            _item._type                 = _fbd->_item[_i]._type;
            _item._localId              = _fbd->_item[_i]._localId;
            _item._executionOrderId     = _fbd->_item[_i]._executionOrderId;
            _item._negated              = _fbd->_item[_i]._negated;
            _item._expression           = _fbd->_item[_i]._expression;
            _item._name                 = _fbd->_item[_i]._name;
            _item._typeName             = _fbd->_item[_i]._typeName;
            _item._instanceName         = _fbd->_item[_i]._instanceName;
            _item._return_type          = "";
            _item._inOutVariables.clear();
            _item._inputVariables.clear();
            _item._outputVariables.clear();
            _m_block_item.insert(_item._localId, _item);
        }

    for(int _i = 0; _i < (int)_fbd->_item.size(); _i++)
        if(_fbd->_item[_i]._type == IT_FBD_FUNCTION)
        {
            _item._type                 = _fbd->_item[_i]._type;
            _item._localId              = _fbd->_item[_i]._localId;
            _item._executionOrderId     = _fbd->_item[_i]._executionOrderId;
            _item._negated              = _fbd->_item[_i]._negated;
            _item._expression           = _fbd->_item[_i]._expression;
            _item._name                 = _fbd->_item[_i]._name;
            _item._typeName             = _fbd->_item[_i]._typeName;
            _item._instanceName         = _fbd->_item[_i]._instanceName;
            //            _item._return_type          = pou_->_return_type;
            //            _item._return_type          = getRetTypeStandartFunction(_item._typeName);
            _item._return_type          = "";
            _item._inOutVariables.clear();
            _item._inputVariables.clear();
            _item._outputVariables.clear();
            _m_func_item.insert(_item._localId, _item);
        }

    for(int _i = 0; _i < (int)_fbd->_item.size(); _i++)
        if(_fbd->_item[_i]._type == IT_FBD_INPUT)
        {
            _item._type                 = _fbd->_item[_i]._type;
            _item._localId              = _fbd->_item[_i]._localId;
            _item._executionOrderId     = _fbd->_item[_i]._executionOrderId;
            _item._negated              = _fbd->_item[_i]._negated;
            _item._expression           = _fbd->_item[_i]._expression;
            _item._name                 = _fbd->_item[_i]._name;
            _item._typeName             = _fbd->_item[_i]._typeName;
            _item._instanceName         = _fbd->_item[_i]._instanceName;
//            _item._return_type          = getTypeByVar(pou_, _item._expression);
            _item._inOutVariables.clear();
            _item._inputVariables.clear();
            _item._outputVariables.clear();
            _m_in_var_item.insert(_item._localId, _item);
        }

    for(int _i = 0; _i < (int)_fbd->_item.size(); _i++)
        if(_fbd->_item[_i]._type == IT_FBD_OUTPUT)
        {
            _item._type                 = _fbd->_item[_i]._type;
            _item._localId              = _fbd->_item[_i]._localId;
            _item._executionOrderId     = _fbd->_item[_i]._executionOrderId;
            _item._negated              = _fbd->_item[_i]._negated;
            _item._expression           = _fbd->_item[_i]._expression;
            _item._name                 = _fbd->_item[_i]._name;
            _item._typeName             = _fbd->_item[_i]._typeName;
            _item._instanceName         = _fbd->_item[_i]._instanceName;
//            _item._return_type          = getTypeByVar(pou_, _item._expression);
            _item._inOutVariables.clear();
            _item._inputVariables.clear();
            _item._outputVariables.clear();
            _m_out_var_item.insert(_item._localId, _item);
        }

    for(int _i = 0; _i < (int)_fbd->_item.size(); _i++)
        if(_fbd->_item[_i]._type == IT_FBD_INPUT_OUTPUT)
        {
            _item._type                 = _fbd->_item[_i]._type;
            _item._localId              = _fbd->_item[_i]._localId;
            _item._executionOrderId     = _fbd->_item[_i]._executionOrderId;
            _item._negated              = _fbd->_item[_i]._negated;
            _item._expression           = _fbd->_item[_i]._expression;
            _item._name                 = _fbd->_item[_i]._name;
            _item._typeName             = _fbd->_item[_i]._typeName;
            _item._instanceName         = _fbd->_item[_i]._instanceName;
//            _item._return_type          = getTypeByVar(pou_, _item._expression);
            _item._inOutVariables.clear();
            _item._inputVariables.clear();
            _item._outputVariables.clear();
            _m_in_out_var_item.insert(_item._localId, _item);
        }

    for(int _i = 0; _i < (int)_fbd->_item.size(); _i++)
        if(_fbd->_item[_i]._type == IT_FBD_CONNECTOR)
        {
            _item._type                 = _fbd->_item[_i]._type;
            _item._localId              = _fbd->_item[_i]._localId;
            _item._executionOrderId     = _fbd->_item[_i]._executionOrderId;
            _item._negated              = _fbd->_item[_i]._negated;
            _item._expression           = _fbd->_item[_i]._expression;
            _item._name                 = _fbd->_item[_i]._name;
            _item._typeName             = _fbd->_item[_i]._typeName;
            _item._instanceName         = _fbd->_item[_i]._instanceName;
            _item._inOutVariables.clear();
            _item._inputVariables.clear();
            _item._outputVariables.clear();
            _m_connect_item.insert(_item._localId, _item);
        }

    for(int _i = 0; _i < (int)_fbd->_item.size(); _i++)
        if(_fbd->_item[_i]._type == IT_FBD_CONTINUATION)
        {
            _item._type                 = _fbd->_item[_i]._type;
            _item._localId              = _fbd->_item[_i]._localId;
            _item._executionOrderId     = _fbd->_item[_i]._executionOrderId;
            _item._negated              = _fbd->_item[_i]._negated;
            _item._expression           = _fbd->_item[_i]._expression;
            _item._name                 = _fbd->_item[_i]._name;
            _item._typeName             = _fbd->_item[_i]._typeName;
            _item._instanceName         = _fbd->_item[_i]._instanceName;
            _item._inOutVariables.clear();
            _item._inputVariables.clear();
            _item._outputVariables.clear();
            _m_continuation_item.insert(_item._localId, _item);
        }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

