#include "TranslatorFbd.h"

TranslatorFBD::TranslatorFBD() {}

// *** POU
//
//-----------------------------------------------------------------------------------
void TranslatorFBD::ProgramCode_Program_STgenerator(T_POU &pou_, QString &text_)
{
    switch(pou_._body._type)
    {
    case PBT_FBD:{
        _m_pou_FBD_item.clear();
        _m_pou_FBD_execution_order_item.clear();
        _m_pou_FBD_generator_item.clear();

        for(int _i = 0; _i < (int)pou_._body._FBD._item.size(); _i++)
            _m_pou_FBD_item.insert(pou_._body._FBD._item[_i]._localId, pou_._body._FBD._item[_i]);

        parseFBDitem(pou_);
        prepareFuncTempVar();
        prepareVarType();
        prepareConnectContinuation();
        prepareVar();
        prepareFunc();
        AllVarFBD_STgenerator(pou_, text_);
        prepareBlock();

        _m_pou_FBD_execution_order_item.clear();
        foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_FBD_block_item)
            if(_it._executionOrderId != 0)
            {
                _m_pou_FBD_execution_order_item.insert(_it._executionOrderId, _it);
                _m_pou_FBD_block_item.remove(_it._localId);
            }

        foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_FBD_func_item)
            if(_it._executionOrderId != 0)
            {
                _m_pou_FBD_execution_order_item.insert(_it._executionOrderId, _it);
                _m_pou_FBD_func_item.remove(_it._localId);
            }

        foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_FBD_execution_order_item)
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

        foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_FBD_block_item)        Block_STcode(_it, text_);
        foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_FBD_func_item)         Func_STcode(_it, text_);
        foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_FBD_in_out_var_item)   Var_STcode(_it, text_);
        foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_FBD_out_var_item)      Var_STcode(_it, text_);
    }break;
    case PBT_MAX:{}break;
    case PBT_NOT_DEFINED:{}break;
    }
    text_ += "END_PROGRAM\n\n";
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void TranslatorFBD::ProgramCode_Function_STgenerator(T_POU &pou_, QString &text_)
{
    switch(pou_._body._type)
    {
    case PBT_FBD:{
        _m_pou_FBD_item.clear();
        _m_pou_FBD_execution_order_item.clear();
        _m_pou_FBD_generator_item.clear();

        for(int _i = 0; _i < (int)pou_._body._FBD._item.size(); _i++)
            _m_pou_FBD_item.insert(pou_._body._FBD._item[_i]._localId, pou_._body._FBD._item[_i]);

        parseFBDitem(pou_);
        prepareFuncTempVar();
        prepareVarType();
        prepareConnectContinuation();
        prepareVar();
        prepareFunc();
        AllVarFBD_STgenerator(pou_, text_);
        prepareBlock();

        _m_pou_FBD_execution_order_item.clear();
        foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_FBD_block_item)
            if(_it._executionOrderId != 0)
            {
                _m_pou_FBD_execution_order_item.insert(_it._executionOrderId, _it);
                _m_pou_FBD_block_item.remove(_it._localId);
            }

        foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_FBD_func_item)
            if(_it._executionOrderId != 0)
            {
                _m_pou_FBD_execution_order_item.insert(_it._executionOrderId, _it);
                _m_pou_FBD_func_item.remove(_it._localId);
            }

        foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_FBD_execution_order_item)
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

        foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_FBD_block_item)        Block_STcode(_it, text_);
        foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_FBD_func_item)         Func_STcode(_it, text_);
        foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_FBD_in_out_var_item)   Var_STcode(_it, text_);
        foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_FBD_out_var_item)      Var_STcode(_it, text_);
    }break;
    case PBT_MAX:{}break;
    case PBT_NOT_DEFINED:{}break;
    }
    text_ += "END_FUNCTION\n\n";
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void TranslatorFBD::ProgramCode_FunctionBlock_STgenerator(T_POU &pou_, QString &text_)
{
    switch(pou_._body._type)
    {
    case PBT_FBD:{
        _m_pou_FBD_item.clear();
        _m_pou_FBD_execution_order_item.clear();
        _m_pou_FBD_generator_item.clear();

        for(int _i = 0; _i < (int)pou_._body._FBD._item.size(); _i++)
            _m_pou_FBD_item.insert(pou_._body._FBD._item[_i]._localId, pou_._body._FBD._item[_i]);

        parseFBDitem(pou_);
        prepareFuncTempVar();
        prepareVarType();
        prepareConnectContinuation();
        prepareVar();
        prepareFunc();
        AllVarFBD_STgenerator(pou_, text_);
        prepareBlock();

        _m_pou_FBD_execution_order_item.clear();
        foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_FBD_block_item)
            if(_it._executionOrderId != 0)
            {
                _m_pou_FBD_execution_order_item.insert(_it._executionOrderId, _it);
                _m_pou_FBD_block_item.remove(_it._localId);
            }

        foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_FBD_func_item)
            if(_it._executionOrderId != 0)
            {
                _m_pou_FBD_execution_order_item.insert(_it._executionOrderId, _it);
                _m_pou_FBD_func_item.remove(_it._localId);
            }

        foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_FBD_execution_order_item)
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

        foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_FBD_block_item)        Block_STcode(_it, text_);
        foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_FBD_func_item)         Func_STcode(_it, text_);
        foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_FBD_in_out_var_item)   Var_STcode(_it, text_);
        foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_FBD_out_var_item)      Var_STcode(_it, text_);
    }break;

    case PBT_MAX:{}break;
    case PBT_NOT_DEFINED:{}break;
    }
    text_ += "END_FUNCTION_BLOCK\n\n";
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void TranslatorFBD::Block_STcode(T_POU_FBD_ITEM_SHORT _block, QString &text_)
{
    QString _data;

    //    if(_block._inputVariables.isEmpty()) return;

    _data = "  ";
    _data += _block._instanceName + "(";
    for(int _j = 0; _j < _block._inputVariables.size(); _j++)
    {
        _data += _block._inputVariables[_j]._name;
        if((_j + 1) < _block._inputVariables.size()) _data += ", ";
    }
    _data += ");\n";
    text_ += _data;

    if(!_block._outputVariables.isEmpty())
        foreach(T_CONNECTION_VAR _var, _block._outputVariables)
            text_ += QString("  %1;\n").arg(_var._name);

    if(!_block._inOutVariables.isEmpty())
        foreach(T_CONNECTION_VAR _var, _block._inOutVariables)
            text_ += QString("  %1;\n").arg(_var._name);
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void TranslatorFBD::Func_STcode(T_POU_FBD_ITEM_SHORT _func, QString &text_)
{
    QString _data;

    //    if(_func._inputVariables.isEmpty()) return;

    _data = "  ";
    _data += _func._expression + " := ";
    _data += _func._typeName + "(";

    for(int _j = 0; _j < _func._inputVariables.size(); _j++)
    {
        _data += _func._inputVariables[_j]._name;
        if((_j + 1) < _func._inputVariables.size()) _data += ", ";
    }
    _data += ");\n";
    text_ += _data;

    if(!_func._outputVariables.isEmpty())
        foreach(T_CONNECTION_VAR _var, _func._outputVariables)
            text_ += QString("  %1;\n").arg(_var._name);

    if(!_func._inOutVariables.isEmpty())
        foreach(T_CONNECTION_VAR _var, _func._inOutVariables)
            text_ += QString("  %1;\n").arg(_var._name);
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void TranslatorFBD::Var_STcode(T_POU_FBD_ITEM_SHORT _var, QString &text_)
{
    QString _data;

    if(_var._is_used) return;
    if(_var._inputVariables.isEmpty()) return;

    _data = "  ";
    _data += _var._inputVariables[0]._name + ";\n";
    text_ += _data;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void TranslatorFBD::prepareBlock()
{
    foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_FBD_block_item)
    {
        quint32 _block_id = _it._localId;

        for(int _v = 0; _v < (int)_m_pou_FBD_item[_block_id]._inputVariables.size(); _v++)
        {
            if(_m_pou_FBD_item[_block_id]._inputVariables[_v]._connection._refLocalId != -1)
            {
                T_CONNECTION_VAR _var;
                quint32 _var_id = _m_pou_FBD_item[_block_id]._inputVariables[_v]._connection._refLocalId;
                _var._name = _m_pou_FBD_item[_block_id]._inputVariables[_v]._formalParameter + " := ";

                if(itemIsBlock(_var_id))
                {
                    _var._name += _m_pou_FBD_block_item[_var_id]._instanceName;
                    _var._name += ".";
                    _var._name += _m_pou_FBD_item[_block_id]._inputVariables[_v]._connection._formalParameter;
                    _var._type = "BOOL";
                }else
                    if(itemIsFunc(_var_id))
                    {
                        _var._name += _m_pou_FBD_func_item[_var_id]._expression;
                        _var._type = _m_pou_FBD_func_item[_var_id]._return_type;
                    }else
                        if(itemIsInVar(_var_id))
                        {
                            _var._name += _m_pou_FBD_in_var_item[_var_id]._expression;
                            _var._type = _m_pou_FBD_in_var_item[_var_id]._return_type;
                        }else
                            if(itemIsInOutVar(_var_id))
                            {
                                _var._name += _m_pou_FBD_in_out_var_item[_var_id]._expression;
                                _var._type = _m_pou_FBD_in_out_var_item[_var_id]._return_type;
                            }else
                                if(itemIsContinuation(_var_id))
                                {
                                    if(!_m_pou_FBD_continuation_item[_var_id]._inputVariables.isEmpty())
                                    {
                                        _var._name += _m_pou_FBD_continuation_item[_var_id]._inputVariables[0]._name;
                                        _var._type = _m_pou_FBD_continuation_item[_var_id]._inputVariables[0]._type;
                                    }
                                }
                _m_pou_FBD_block_item[_block_id]._inputVariables.push_back(_var);
            }
        }
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void TranslatorFBD::prepareFuncTempVar()
{
    foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_FBD_func_item)
    {
        quint32 _func_id = _it._localId;

        QString _var = QString("%1%2_TMP_VAR")
                           .arg(_m_pou_FBD_item[_func_id]._typeName)
                           .arg(_func_id);
        _m_pou_FBD_func_item[_func_id]._expression = _var;
        _m_pou_FBD_item[_func_id]._expression = _var;
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void TranslatorFBD::prepareFunc()
{
    QString _temp_var;
    QString _var_type;

    foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_FBD_func_item)
    {
        quint32 _func_id = _it._localId;

        for(int _v = 0; _v < (int)_m_pou_FBD_item[_func_id]._inputVariables.size(); _v++)
        {
            if(_m_pou_FBD_item[_func_id]._inputVariables[_v]._connection._refLocalId != -1)
            {
                quint32 _var_id = _m_pou_FBD_item[_func_id]._inputVariables[_v]._connection._refLocalId;
                T_CONNECTION_VAR _var;

                if(itemIsBlock(_var_id))
                {
                    _var._name += _m_pou_FBD_block_item[_var_id]._instanceName;
                    _var._name += ".";
                    _var._name += _m_pou_FBD_item[_func_id]._inputVariables[_v]._connection._formalParameter;
                    _var._type = "BOOL";
                }else
                    if(itemIsFunc(_var_id))
                    {
                        _var._name += _m_pou_FBD_func_item[_var_id]._expression;
                        _var._type = _m_pou_FBD_func_item[_func_id]._return_type;
                        _m_pou_FBD_func_item[_var_id]._return_type = _m_pou_FBD_func_item[_func_id]._return_type;
                    }else
                        if(itemIsInVar(_var_id))
                        {
                            _var._name += _m_pou_FBD_in_var_item[_var_id]._expression;
                            _var._type = _m_pou_FBD_in_var_item[_var_id]._return_type;
                        }else
                            if(itemIsOutVar(_var_id))
                            {
                                _var._name += _m_pou_FBD_out_var_item[_var_id]._expression;
                                _var._type = _m_pou_FBD_out_var_item[_var_id]._return_type;
                            }else
                                if(itemIsInOutVar(_var_id))
                                {
                                    _var._name += _m_pou_FBD_in_out_var_item[_var_id]._expression;
                                    _var._type = _m_pou_FBD_in_out_var_item[_var_id]._return_type;
                                }else
                                    if(itemIsContinuation(_var_id))
                                    {
                                        if(!_m_pou_FBD_continuation_item[_var_id]._inputVariables.isEmpty())
                                        {
                                            _var._name += _m_pou_FBD_continuation_item[_var_id]._inputVariables[0]._name;
                                            _var._type = _m_pou_FBD_continuation_item[_var_id]._inputVariables[0]._type;
                                        }
                                    }
                _m_pou_FBD_func_item[_func_id]._inputVariables.push_back(_var);
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
    QString _var_type;

    foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_FBD_out_var_item)
    {
        quint32 _var_id = _it._localId;
        quint32 _connect_id = _m_pou_FBD_item[_var_id]._connection._refLocalId;

        if(itemIsBlock(_connect_id))
        {
        }else
            if(itemIsFunc(_connect_id))
            {
                _m_pou_FBD_func_item[_connect_id]._return_type = _m_pou_FBD_out_var_item[_var_id]._return_type;
            }else
                if(itemIsInVar(_connect_id))
                {
                }else
                    if(itemIsInOutVar(_connect_id))
                    {
                    }else
                        if(itemIsContinuation(_connect_id))
                        {
                            _m_pou_FBD_continuation_item[_connect_id]._return_type = _m_pou_FBD_out_var_item[_var_id]._return_type;
                        }
    }
    foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_FBD_in_out_var_item)
    {
        quint32 _var_id = _it._localId;
        quint32 _connect_id = _m_pou_FBD_item[_var_id]._connection._refLocalId;

        if(itemIsBlock(_connect_id))
        {
        }else
            if(itemIsFunc(_connect_id))
            {
                _m_pou_FBD_func_item[_connect_id]._return_type = _m_pou_FBD_in_out_var_item[_var_id]._return_type;
            }else
                if(itemIsInVar(_connect_id))
                {
                }else
                    if(itemIsInOutVar(_connect_id))
                    {
                    }else
                        if(itemIsContinuation(_connect_id))
                        {
                            _m_pou_FBD_continuation_item[_connect_id]._return_type = _m_pou_FBD_in_out_var_item[_var_id]._return_type;
                        }
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void TranslatorFBD::prepareVar()
{
    bool _is_connected;

    foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_FBD_out_var_item)
    {
        T_CONNECTION_VAR _var;

        _is_connected = false;
        quint32 _out_var_id = _it._localId;
        quint32 _connect_id = _m_pou_FBD_item[_out_var_id]._connection._refLocalId;
        _var._name = _m_pou_FBD_item[_out_var_id]._expression + " := ";
        _var._type = _m_pou_FBD_item[_out_var_id]._return_type;

        if(itemIsBlock(_connect_id))
        {
            _is_connected = true;
            _var._name += _m_pou_FBD_block_item[_connect_id]._instanceName;
            _var._name += ".";
            _var._name += _m_pou_FBD_item[_out_var_id]._connection._formalParameter;
            _m_pou_FBD_block_item[_connect_id]._outputVariables.push_back(_var);
            _m_pou_FBD_out_var_item[_out_var_id]._is_used = true;
        }else
            if(itemIsFunc(_connect_id))
            {
                _is_connected = true;
                _var._name += _m_pou_FBD_func_item[_connect_id]._expression;
                _m_pou_FBD_func_item[_connect_id]._outputVariables.push_back(_var);
                _m_pou_FBD_out_var_item[_out_var_id]._is_used = true;
            }else
                if(itemIsInVar(_connect_id))
                {
                    _is_connected = true;
                    _var._name += _m_pou_FBD_in_var_item[_connect_id]._expression;
                }else
                    if(itemIsInOutVar(_connect_id))
                    {
                        _is_connected = true;
                        _var._name += _m_pou_FBD_in_out_var_item[_connect_id]._expression;
                    }else
                        if(itemIsContinuation(_connect_id))
                        {
                            if(!_m_pou_FBD_continuation_item[_connect_id]._inputVariables.isEmpty())
                            {
                                _is_connected = true;
                                _var._name += _m_pou_FBD_continuation_item[_connect_id]._inputVariables[0]._name;
                                quint32 _connect_dev_id = _m_pou_FBD_item[_connect_id]._connection._refLocalId;
                                if(itemIsBlock(_connect_dev_id))
                                {
                                    _m_pou_FBD_block_item[_connect_dev_id]._outputVariables.push_back(_var);
                                    _m_pou_FBD_out_var_item[_out_var_id]._is_used = true;
                                }else
                                    if(itemIsFunc(_connect_dev_id))
                                    {
                                        _m_pou_FBD_func_item[_connect_dev_id]._outputVariables.push_back(_var);
                                        _m_pou_FBD_out_var_item[_out_var_id]._is_used = true;
                                    }
                            }
                        }
        if(_is_connected)
            _m_pou_FBD_out_var_item[_out_var_id]._inputVariables.push_back(_var);
    }

    foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_FBD_in_out_var_item)
    {
        T_CONNECTION_VAR _var;

        _is_connected = false;
        quint32 _out_var_id = _it._localId;
        quint32 _connect_id = _m_pou_FBD_item[_out_var_id]._connection._refLocalId;
        _var._name = _m_pou_FBD_item[_out_var_id]._expression + " := ";
        _var._type = _m_pou_FBD_item[_out_var_id]._return_type;

        if(itemIsBlock(_connect_id))
        {
            _is_connected = true;
            _var._name += _m_pou_FBD_block_item[_connect_id]._instanceName;
            _var._name += ".";
            _var._name += _m_pou_FBD_item[_out_var_id]._connection._formalParameter;
            _m_pou_FBD_block_item[_connect_id]._inOutVariables.push_back(_var);
            _m_pou_FBD_in_out_var_item[_out_var_id]._is_used = true;
        }else
            if(itemIsFunc(_connect_id))
            {
                _is_connected = true;
                _var._name += _m_pou_FBD_func_item[_connect_id]._expression;
                _m_pou_FBD_func_item[_connect_id]._inOutVariables.push_back(_var);
                _m_pou_FBD_in_out_var_item[_out_var_id]._is_used = true;
            }else
                if(itemIsInVar(_connect_id))
                {
                    _is_connected = true;
                    _var._name += _m_pou_FBD_in_var_item[_connect_id]._expression;
                }else
                    if(itemIsInOutVar(_connect_id))
                    {
                        _is_connected = true;
                        _var._name += _m_pou_FBD_in_out_var_item[_connect_id]._expression;
                    }else
                        if(itemIsContinuation(_connect_id))
                        {
                            if(!_m_pou_FBD_continuation_item[_connect_id]._inputVariables.isEmpty())
                            {
                                _is_connected = true;
                                _var._name += _m_pou_FBD_continuation_item[_connect_id]._inputVariables[0]._name;
                            }
                        }
        if(_is_connected)
            _m_pou_FBD_in_out_var_item[_out_var_id]._inputVariables.push_back(_var);
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
quint32 TranslatorFBD::linkConnect(quint32 _connect_id)
{
    quint32 _id = 0;
    foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_FBD_continuation_item)
        if(_it._name == _m_pou_FBD_connect_item[_connect_id]._name)
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
    foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_FBD_connect_item)
    {
        T_CONNECTION_VAR _var;

        qint32 _connect_id = _it._localId;
        switch(_m_pou_FBD_item[_m_pou_FBD_item[_connect_id]._connection._refLocalId]._type)
        {
        case IT_FBD_BLOCK:{
            _var._name = QString("%1.%2")
            .arg(_m_pou_FBD_item[_m_pou_FBD_item[_connect_id]._connection._refLocalId]._instanceName)
                .arg(_m_pou_FBD_item[_connect_id]._connection._formalParameter);
            _m_pou_FBD_connect_item[_connect_id]._return_type = _m_pou_FBD_block_item[_m_pou_FBD_item[_connect_id]._connection._refLocalId]._return_type;
            _var._type = _m_pou_FBD_connect_item[_connect_id]._return_type;
        }break;
        case IT_FBD_FUNCTION:{
            _var._name = QString("%1")
            .arg(_m_pou_FBD_item[_m_pou_FBD_item[_connect_id]._connection._refLocalId]._expression);
            _m_pou_FBD_connect_item[_connect_id]._return_type = _m_pou_FBD_func_item[_m_pou_FBD_item[_connect_id]._connection._refLocalId]._return_type;
            _var._type = _m_pou_FBD_connect_item[_connect_id]._return_type;
        }break;
        case IT_FBD_INPUT:{
            _var._name = QString("%1")
            .arg(_m_pou_FBD_item[_m_pou_FBD_item[_connect_id]._connection._refLocalId]._expression);
            _m_pou_FBD_connect_item[_connect_id]._return_type = _m_pou_FBD_in_var_item[_m_pou_FBD_item[_connect_id]._connection._refLocalId]._return_type;
            _var._type = _m_pou_FBD_connect_item[_connect_id]._return_type;
        }break;
        case IT_FBD_OUTPUT:{
            _var._name = QString("%1")
            .arg(_m_pou_FBD_item[_m_pou_FBD_item[_connect_id]._connection._refLocalId]._expression);
            _m_pou_FBD_connect_item[_connect_id]._return_type = _m_pou_FBD_out_var_item[_m_pou_FBD_item[_connect_id]._connection._refLocalId]._return_type;
            _var._type = _m_pou_FBD_connect_item[_connect_id]._return_type;
        }break;
        case IT_FBD_INPUT_OUTPUT:{
            _var._name = QString("%1")
            .arg(_m_pou_FBD_item[_m_pou_FBD_item[_connect_id]._connection._refLocalId]._expression);
            _m_pou_FBD_connect_item[_connect_id]._return_type = _m_pou_FBD_in_out_var_item[_m_pou_FBD_item[_connect_id]._connection._refLocalId]._return_type;
            _var._type = _m_pou_FBD_connect_item[_connect_id]._return_type;
        }break;
        case IT_FBD_MAX:
        case IT_FBD_NOT_DEFINED:
        case IT_FBD_COMMENT:
        case IT_FBD_CONNECTOR:
        case IT_FBD_CONTINUATION:{}break;
        }
        _m_pou_FBD_connect_item[_connect_id]._outputVariables.push_back(_var);
        quint32 _continuation_id = linkConnect(_connect_id);
        if(_continuation_id != 0)
        {
            _m_pou_FBD_continuation_item[_continuation_id]._inputVariables.push_back(_var);
            _m_pou_FBD_connect_item[_connect_id]._return_type = _m_pou_FBD_continuation_item[_continuation_id]._return_type;
            _m_pou_FBD_item[_continuation_id]._connection._refLocalId = _m_pou_FBD_item[_connect_id]._connection._refLocalId;
        }
    }

    foreach(T_POU_FBD_ITEM_SHORT _it, _m_pou_FBD_continuation_item)
    {
        qint32 _connect_id = _it._localId;
        switch(_m_pou_FBD_item[_m_pou_FBD_item[_connect_id]._connection._refLocalId]._type)
        {
        case IT_FBD_BLOCK:{
        }break;
        case IT_FBD_FUNCTION:{
            _m_pou_FBD_func_item[_m_pou_FBD_item[_connect_id]._connection._refLocalId]._return_type = _it._return_type;
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
    if(_m_pou_FBD_block_item.find(_id) != _m_pou_FBD_block_item.end())
        return true;
    return false;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool TranslatorFBD::itemIsFunc(quint32 _id)
{
    if(_m_pou_FBD_func_item.find(_id) != _m_pou_FBD_func_item.end())
        return true;
    return false;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool TranslatorFBD::itemIsInVar(quint32 _id)
{
    if(_m_pou_FBD_in_var_item.find(_id) != _m_pou_FBD_in_var_item.end())
        return true;
    return false;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool TranslatorFBD::itemIsOutVar(quint32 _id)
{
    if(_m_pou_FBD_out_var_item.find(_id) != _m_pou_FBD_out_var_item.end())
        return true;
    return false;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool TranslatorFBD::itemIsInOutVar(quint32 _id)
{
    if(_m_pou_FBD_in_out_var_item.find(_id) != _m_pou_FBD_in_out_var_item.end())
        return true;
    return false;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool TranslatorFBD::itemIsConnect(quint32 _id)
{
    if(_m_pou_FBD_connect_item.find(_id) != _m_pou_FBD_connect_item.end())
        return true;
    return false;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool TranslatorFBD::itemIsContinuation(quint32 _id)
{
    if(_m_pou_FBD_continuation_item.find(_id) != _m_pou_FBD_continuation_item.end())
        return true;
    return false;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------

