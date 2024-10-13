#include "TranslatorSfc.h"

TranslatorSFC::TranslatorSFC() {}

// *** POU
//
//-----------------------------------------------------------------------------------
void TranslatorSFC::ProgramCode_Program_STgenerator(T_POU &pou_, QString &text_)
{
    switch(pou_._body._type)
    {
    case PBT_SFC:{
        parseSFCitem(pou_);
        AllVarSFC_STgenerator(pou_, text_);
        _m_SFC_inline_counter = 1;
        InitialStepSFC_STcode(_m_pou_SFC_all_item[_m_SFC_localId_start], text_);
        _m_pou_SFC_all_item[_m_SFC_localId_start]._is_used = true;
        foreach(T_POU_SFC_ITEM _it, _m_pou_SFC_transition_item)
            TransactionSFC_STcode(_it, text_);
    }break;
    case PBT_MAX:{}break;
    case PBT_NOT_DEFINED:{}break;
    }
    text_ += "END_PROGRAM\n\n";
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void TranslatorSFC::ProgramCode_Function_STgenerator(T_POU &pou_, QString &text_)
{
    switch(pou_._body._type)
    {
    case PBT_SFC:{
        parseSFCitem(pou_);
        AllVarSFC_STgenerator(pou_, text_);
        _m_SFC_inline_counter = 1;
        InitialStepSFC_STcode(_m_pou_SFC_all_item[_m_SFC_localId_start], text_);
        _m_pou_SFC_all_item[_m_SFC_localId_start]._is_used = true;
        foreach(T_POU_SFC_ITEM _it, _m_pou_SFC_transition_item)
            TransactionSFC_STcode(_it, text_);
    }break;
    case PBT_MAX:{}break;
    case PBT_NOT_DEFINED:{}break;
    }
    text_ += "END_FUNCTION\n\n";
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void TranslatorSFC::ProgramCode_FunctionBlock_STgenerator(T_POU &pou_, QString &text_)
{
    switch(pou_._body._type)
    {
    case PBT_SFC:{
        parseSFCitem(pou_);
        AllVarSFC_STgenerator(pou_, text_);
        _m_SFC_inline_counter = 1;
        InitialStepSFC_STcode(_m_pou_SFC_all_item[_m_SFC_localId_start], text_);
        _m_pou_SFC_all_item[_m_SFC_localId_start]._is_used = true;
        foreach(T_POU_SFC_ITEM _it, _m_pou_SFC_transition_item)
            TransactionSFC_STcode(_it, text_);
    }break;
    case PBT_MAX:{}break;
    case PBT_NOT_DEFINED:{}break;
    }
    text_ += "END_FUNCTION_BLOCK\n\n";
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void TranslatorSFC::parseSFCitem(const T_POU &pou_)
{
    _m_pou_SFC_all_item.clear();
    _m_pou_SFC_transition_item.clear();

    for(int _i = 0; _i < (int)pou_._body._SFC._item.size(); _i++)
        if(pou_._body._SFC._item[_i]._initialStep == "true")
        {
            _m_SFC_localId_start = pou_._body._SFC._item[_i]._localId;
            break;
        }

    for(int _i = 0; _i < (int)pou_._body._SFC._item.size(); _i++)
        if(pou_._body._SFC._item[_i]._type == IT_SFC_TRANSITION)
            _m_pou_SFC_transition_item.push_back(pou_._body._SFC._item[_i]);
        else
            _m_pou_SFC_all_item.insert(pou_._body._SFC._item[_i]._localId, pou_._body._SFC._item[_i]);
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void TranslatorSFC::TransactionSFC_STcode(T_POU_SFC_ITEM _transaction, QString &text_)
{
    QString _data;
    bool    _complit;
    quint32 _in_localId;
    quint32 _out_localId;

    _in_localId = _transaction._point_in[0]._connection._refLocalId;

    foreach(T_POU_SFC_ITEM _it, _m_pou_SFC_all_item)
    {
        _complit = false;
        for(int _i = 0; _i < _it._point_in.size(); _i++)
            if(_it._point_in[_i]._connection._refLocalId == _transaction._localId)
            {
                _out_localId = _it._localId;
                _complit = true;
                break;
            }
        if(_complit) break;
    }

    while(_m_pou_SFC_all_item[_in_localId]._type != IT_SFC_STEP)
        _in_localId = _m_pou_SFC_all_item[_in_localId]._point_in[0]._connection._refLocalId;

    while(_m_pou_SFC_all_item[_out_localId]._type != IT_SFC_STEP)
    {
        foreach(T_POU_SFC_ITEM _it, _m_pou_SFC_all_item)
        {
            _complit = false;
            for(int _i = 0; _i < _it._point_in.size(); _i++)
                if(_it._point_in[_i]._connection._refLocalId == _out_localId)
                {
                    _out_localId = _it._localId;
                    _complit = true;
                    break;
                }
            if(_complit)
            {
                if(_m_pou_SFC_all_item[_out_localId]._type == IT_SFC_JUMP_STEP)
                {
                    foreach(T_POU_SFC_ITEM _it, _m_pou_SFC_all_item)
                    if(_it._name == _m_pou_SFC_all_item[_out_localId]._targetName)
                    {
                        _out_localId = _it._localId;
                        break;
                    }
                }
                break;
            }
        }
    }

    _data = QString("  TRANSITION FROM %1 TO %2\n    := %3;\n  END_TRANSITION\n\n")
                .arg(_m_pou_SFC_all_item[_in_localId]._name)
                .arg(_m_pou_SFC_all_item[_out_localId]._name)
                .arg(_transaction._condition[0]._ST_code);

    if(_m_pou_SFC_all_item[_out_localId]._type == IT_SFC_STEP)
        if(!_m_pou_SFC_all_item[_out_localId]._is_used)
        {
            StepSFC_STcode(_m_pou_SFC_all_item[_out_localId], _data);
            _m_pou_SFC_all_item[_out_localId]._is_used = true;
        }

    text_ += _data;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void TranslatorSFC::InitialStepSFC_STcode(T_POU_SFC_ITEM _step, QString &text_)
{
    QString _data;

    _data = QString("  INITIAL_STEP %1:\n").arg(_step._name);
    _data += "  END_STEP\n\n";

    text_ += _data;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void TranslatorSFC::StepSFC_STcode(T_POU_SFC_ITEM _step, QString &text_)
{
    QString _data;
    quint32 _action_localId;

    _data = QString("  STEP %1:\n").arg(_step._name);
    foreach(T_POU_SFC_ITEM _it, _m_pou_SFC_all_item)
        if((_it._type == IT_SFC_ACTION_BLOCK) && (_it._point_in[0]._connection._refLocalId == _step._localId))
        {
            _action_localId = _it._localId;
            break;
        }

    for(int _i = 0; _i < (int)_m_pou_SFC_all_item[_action_localId]._action.size(); _i++)
        if(_m_pou_SFC_all_item[_action_localId]._action[_i]._indicator == "")
            _data += QString("    %1_INLINE%2(%3);\n")
                         .arg(_step._name.toUpper())
                         .arg(_m_SFC_inline_counter + _i)
                         .arg(_m_pou_SFC_all_item[_action_localId]._action[_i]._qualifier);
        else
            _data += QString("    %1_INLINE%2(%3, %4);\n")
                         .arg(_step._name.toUpper())
                         .arg(_m_SFC_inline_counter + _i)
                         .arg(_m_pou_SFC_all_item[_action_localId]._action[_i]._qualifier)
                         .arg(_m_pou_SFC_all_item[_action_localId]._action[_i]._indicator);
    _data += "  END_STEP\n\n";

    for(int _i = 0; _i < (int)_m_pou_SFC_all_item[_action_localId]._action.size(); _i++)
        _data += QString("  ACTION %1_INLINE%2:\n    %3\n  END_ACTION\n\n")
                     .arg(_step._name.toUpper())
                     .arg(_m_SFC_inline_counter + _i)
                     .arg(_m_pou_SFC_all_item[_action_localId]._action[_i]._ST_code);

    _m_SFC_inline_counter += _m_pou_SFC_all_item[_action_localId]._action.size();
    text_ += _data;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void TranslatorSFC::AllVarSFC_STgenerator(T_POU &pou_, QString &text_)
{
    bool _result;
    QString _data;
    QString _type_name;

    switch(pou_._pouType)
    {
    case PT_PROGRAMM:{          _data = QString("PROGRAM %1\n").arg(pou_._name);        }break;
    case PT_FUNCTION:{          _data = QString("FUNCTION %1 : %2\n").arg(pou_._name).arg(pou_._return_type);       }break;
    case PT_FUNCTION_BLOCK:{    _data = QString("FUNCTION_BLOCK %1\n").arg(pou_._name); }break;
    case PT_NOT_DEFINED:{}break;
    case PT_MAX:{}break;
    }

    prepareAllRetainVar(pou_, _data);
    prepareAllNonRetainVar(pou_, _data);
    prepareAllConstantVar(pou_, _data);

    _result = false;
    if(!pou_._interface._outputVars.isEmpty())
    {
        for(int _j = 0; _j < (int)pou_._interface._outputVars.size(); _j++)
            if(!pou_._interface._outputVars[_j]._is_used)
            {
                _result = true;
                break;
            }

        if(_result)
        {
            _data += "  VAR_OUTPUT\n";

            for(int _j = 0; _j < (int)pou_._interface._outputVars.size(); _j++)
            {
                if(pou_._interface._outputVars[_j]._is_used) continue;

                if(pou_._interface._outputVars[_j]._type_name == "string")  _type_name = pou_._interface._outputVars[_j]._type_name.toUpper();
                else                                                                        _type_name = pou_._interface._outputVars[_j]._type_name;

                QString _var = QString("    %1").arg(pou_._interface._outputVars[_j]._name);

                if(pou_._interface._outputVars[_j]._address != "")
                    _var = _var + QString(" AT %1").arg(pou_._interface._outputVars[_j]._address);

                _var = _var + QString(" : %1").arg(_type_name);

                if(pou_._interface._outputVars[_j]._initialValue._simpleValue != "")
                    _var = _var + QString(" := %1").arg(pou_._interface._outputVars[_j]._initialValue._simpleValue);

                _var = _var + ";\n";

                _data += _var;
            }
            _data += "  END_VAR\n";
        }
    }

    _result = false;
    if(!pou_._interface._inputVars.isEmpty())
    {
        for(int _j = 0; _j < (int)pou_._interface._inputVars.size(); _j++)
            if(!pou_._interface._inputVars[_j]._is_used)
            {
                _result = true;
                break;
            }

        if(_result)
        {
            _data += "  VAR_INPUT\n";

            for(int _j = 0; _j < (int)pou_._interface._inputVars.size(); _j++)
            {
                if(pou_._interface._inputVars[_j]._is_used) continue;

                if(pou_._interface._inputVars[_j]._type_name == "string")  _type_name = pou_._interface._inputVars[_j]._type_name.toUpper();
                else                                                                        _type_name = pou_._interface._inputVars[_j]._type_name;

                QString _var = QString("    %1").arg(pou_._interface._inputVars[_j]._name);

                if(pou_._interface._inputVars[_j]._address != "")
                    _var = _var + QString(" AT %1").arg(pou_._interface._inputVars[_j]._address);

                _var = _var + QString(" : %1").arg(_type_name);

                if(pou_._interface._inputVars[_j]._initialValue._simpleValue != "")
                    _var = _var + QString(" := %1").arg(pou_._interface._inputVars[_j]._initialValue._simpleValue);

                _var = _var + ";\n";

                _data += _var;
            }
            _data += "  END_VAR\n";
        }
    }

    _result = false;
    if(!pou_._interface._inoutVars.isEmpty())
    {
        for(int _j = 0; _j < (int)pou_._interface._inoutVars.size(); _j++)
            if(!pou_._interface._inoutVars[_j]._is_used)
            {
                _result = true;
                break;
            }

        if(_result)
        {
            _data += "  VAR_IN_OUT\n";

            for(int _j = 0; _j < (int)pou_._interface._inoutVars.size(); _j++)
            {
                if(pou_._interface._inoutVars[_j]._is_used) continue;

                if(pou_._interface._inoutVars[_j]._type_name == "string")  _type_name = pou_._interface._inoutVars[_j]._type_name.toUpper();
                else                                                                        _type_name = pou_._interface._inoutVars[_j]._type_name;

                QString _var = QString("    %1").arg(pou_._interface._inoutVars[_j]._name);

                if(pou_._interface._inoutVars[_j]._address != "")
                    _var = _var + QString(" AT %1").arg(pou_._interface._inoutVars[_j]._address);

                _var = _var + QString(" : %1").arg(_type_name);

                if(pou_._interface._inoutVars[_j]._initialValue._simpleValue != "")
                    _var = _var + QString(" := %1").arg(pou_._interface._inoutVars[_j]._initialValue._simpleValue);

                _var = _var + ";\n";

                _data += _var;
            }
            _data += "  END_VAR\n";
        }
    }

    _result = false;
    if(!pou_._interface._tempVars.isEmpty())
    {
        for(int _j = 0; _j < (int)pou_._interface._tempVars.size(); _j++)
            if(!pou_._interface._tempVars[_j]._is_used)
            {
                _result = true;
                break;
            }

        if(_result)
        {
            _data += "  VAR_TEMP\n";

            for(int _j = 0; _j < (int)pou_._interface._tempVars.size(); _j++)
            {
                if(pou_._interface._tempVars[_j]._is_used) continue;

                if(pou_._interface._tempVars[_j]._type_name == "string")  _type_name = pou_._interface._tempVars[_j]._type_name.toUpper();
                else                                                                        _type_name = pou_._interface._tempVars[_j]._type_name;

                QString _var = QString("    %1").arg(pou_._interface._tempVars[_j]._name);

                if(pou_._interface._tempVars[_j]._address != "")
                    _var = _var + QString(" AT %1").arg(pou_._interface._tempVars[_j]._address);

                _var = _var + QString(" : %1").arg(_type_name);

                if(pou_._interface._tempVars[_j]._initialValue._simpleValue != "")
                    _var = _var + QString(" := %1").arg(pou_._interface._tempVars[_j]._initialValue._simpleValue);

                _var = _var + ";\n";

                _data += _var;
            }
            _data += "  END_VAR\n";
        }
    }

    _result = false;
    if(!pou_._interface._externalVars.isEmpty())
    {
        for(int _j = 0; _j < (int)pou_._interface._externalVars.size(); _j++)
            if(!pou_._interface._externalVars[_j]._is_used)
            {
                _result = true;
                break;
            }

        if(_result)
        {
            _data += "  VAR_EXTERNAL\n";

            for(int _j = 0; _j < (int)pou_._interface._externalVars.size(); _j++)
            {
                if(pou_._interface._externalVars[_j]._is_used) continue;

                if(pou_._interface._externalVars[_j]._type_name == "string")  _type_name = pou_._interface._externalVars[_j]._type_name.toUpper();
                else                                                                        _type_name = pou_._interface._externalVars[_j]._type_name;

                QString _var = QString("    %1").arg(pou_._interface._externalVars[_j]._name);

                if(pou_._interface._externalVars[_j]._address != "")
                    _var = _var + QString(" AT %1").arg(pou_._interface._externalVars[_j]._address);

                _var = _var + QString(" : %1").arg(_type_name);

                if(pou_._interface._externalVars[_j]._initialValue._simpleValue != "")
                    _var = _var + QString(" := %1").arg(pou_._interface._externalVars[_j]._initialValue._simpleValue);

                _var = _var + ";\n";

                _data += _var;
            }
            _data += "  END_VAR\n";
        }
    }

    _result = false;
    if(!pou_._interface._localVars.isEmpty())
    {
        for(int _j = 0; _j < (int)pou_._interface._localVars.size(); _j++)
            if(!pou_._interface._localVars[_j]._is_used)
            {
                _result = true;
                break;
            }

        if(_result)
        {
            _data += "  VAR\n";

            for(int _j = 0; _j < (int)pou_._interface._localVars.size(); _j++)
            {
                if(pou_._interface._localVars[_j]._is_used) continue;

                if(pou_._interface._localVars[_j]._type_name == "string")  _type_name = pou_._interface._localVars[_j]._type_name.toUpper();
                else                                                                        _type_name = pou_._interface._localVars[_j]._type_name;

                QString _var = QString("    %1").arg(pou_._interface._localVars[_j]._name);

                if(pou_._interface._localVars[_j]._address != "")
                    _var = _var + QString(" AT %1").arg(pou_._interface._localVars[_j]._address);

                _var = _var + QString(" : %1").arg(_type_name);

                if(pou_._interface._localVars[_j]._initialValue._simpleValue != "")
                    _var = _var + QString(" := %1").arg(pou_._interface._localVars[_j]._initialValue._simpleValue);

                _var = _var + ";\n";

                _data += _var;
            }
        }
    }

    if(_result) _data += "  END_VAR\n\n";
    text_ += _data;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
