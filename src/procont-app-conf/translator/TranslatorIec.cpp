#include "TranslatorIec.h"
#include "XmlParser.h"

TranslatorIEC::TranslatorIEC() {}

// *** dataType
//
//-----------------------------------------------------------------------------------
QString TranslatorIEC::getSTCode_types(const QDomNode &node_)
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
QString TranslatorIEC::getSTCode_type(const QDomNode &node_)
{
    QString _text = {};

    T_UDT _UDT;
    if(PLCopenXmlParser::parseUDT(node_, &_UDT))
        _text = UDT_STgenerator(&_UDT);

    return _text;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
QString TranslatorIEC::UDT_STgenerator(T_UDT *udt_)
{
    QString _data = {};

    switch(udt_->_type)
    {
    case DT_MAX:{}break;
    case DT_ARRAY:{
        int _range_counter = 0;
        int _ini_val_counter = 0;
        //            datatype0 : ARRAY [10..20,50..60] OF WORD := [1, 1];
        _data += QString("  %1 : ARRAY [").arg(udt_->_name);
        int _size = (int)udt_->_array._range.size();
        for(int _j = 0; _j < _size; _j++)
        {
            QString _range = QString("%1..%2").arg(udt_->_array._range[_j]._begin).arg(udt_->_array._range[_j]._end);
            _data += _range;
            _range_counter++;
            if(_range_counter < _size)_data += ",";
        }
        _data += QString("] OF %1").arg(udt_->_array._type);
        if(udt_->_initial_value_present)
        {
            _data += " := [";
            int _init_size = (int)udt_->_initial_value.size();
            for(int _j = 0; _j < _init_size; _j++)
            {
                QString _val = QString("%1").arg(udt_->_initial_value[_j]);
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
        _data += QString("  %1 : STRUCT\n").arg(udt_->_name);
        for(int _j = 0; _j < (int)udt_->_struct.size(); _j++)
        {
            QString _part = QString("    %1 : %2;\n").arg(udt_->_struct[_j]._name).arg(udt_->_struct[_j]._type);
            _data += _part;
        }
        _data += "  END_STRUCT;\n";
    }break;
    case DT_ENUM:{
        //            datatype3 : (firstType, secondType) := firstType;
        _data += QString("  %1 : (%2").arg(udt_->_name).arg(udt_->_enum._value[0]);
        for(int _j = 1; _j < (int)udt_->_enum._value.size(); _j++)
            _data += QString(", %1").arg(udt_->_enum._value[_j]);

        if(udt_->_initial_value_present)   _data += QString(") := %1;\n").arg(udt_->_initial_value[0]);
        else                               _data += QString(");\n");
    }break;
    case DT_REDEFINE:{
        _data += QString("  %1 : %2;\n").arg(udt_->_name).arg(udt_->_redefined_name);
    }break;
    case DT_SUBRANGE_SIGNED:{
        //            datatype1 : INT (0..0) := 0;
        _data += QString("  %1 : %2 (%3..%4)").arg(udt_->_name, udt_->_sign_unsign_range._type)
                                            .arg(udt_->_sign_unsign_range._begin).arg(udt_->_sign_unsign_range._end);
        if(udt_->_initial_value_present)   _data += QString(" := %1;\n").arg(udt_->_initial_value[0]);
        else                               _data += QString(";\n");
    }break;
    case DT_SUBRANGE_UNSIGNED:{
        //            datatype1 : UINT (0..0) := 0;
        _data += QString("  %1 : %2 (%3..%4)").arg(udt_->_name).arg(udt_->_sign_unsign_range._type)
                                                .arg(udt_->_sign_unsign_range._begin).arg(udt_->_sign_unsign_range._end);
        if(udt_->_initial_value_present)   _data += QString(" := %1;\n").arg(udt_->_initial_value[0]);
        else                               _data += QString(";\n");
    }break;
    }

    return _data;
}
//-----------------------------------------------------------------------------------
// ***

// *** instances
//
//-----------------------------------------------------------------------------------
QString TranslatorIEC::getSTCode_instances(const QDomNode &node_)
{
    QString _text = {};

    T_INSTANCES _INST;
    if(PLCopenXmlParser::parseINSTANCES(node_, &_INST))
        _text = INSTANCES_STgenerator(&_INST);

    return _text;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
QString TranslatorIEC::INSTANCES_STgenerator(T_INSTANCES *inst_)
{
    if(!inst_->_configuration.size())
        return {};

    bool _result;
    QString _data = {};
    _data = QString("CONFIGURATION %1\n").arg(inst_->_configuration[0]._name);

    if(!inst_->_configuration[0]._globalVars.isEmpty())
    {
        _result = false;
        for(int _i = 0; _i < inst_->_configuration[0]._globalVars.size(); _i++)
            if(inst_->_configuration[0]._globalVars[_i]._qualifier == VQ_CONSTANT)
            {
                _result = true;
                break;
            }
        if(_result)
        {
            _data += "  VAR_GLOBAL CONSTANT\n";
            for(int _i = 0; _i < inst_->_configuration[0]._globalVars.size(); _i++)
                if(inst_->_configuration[0]._globalVars[_i]._qualifier == VQ_CONSTANT)
                {
                    _data += QString("    %1 : %2")
                                .arg(inst_->_configuration[0]._globalVars[_i]._name, inst_->_configuration[0]._globalVars[_i]._type_name);
                    if(inst_->_configuration[0]._globalVars[_i]._initialValue._simpleValue != "")
                        _data += QString(" := %1;\n").arg(inst_->_configuration[0]._globalVars[_i]._initialValue._simpleValue);
                    else
                        _data += ";\n";
                }
            _data += "  END_VAR\n";
        }

        _result = false;
        for(int _i = 0; _i < inst_->_configuration[0]._globalVars.size(); _i++)
            if(inst_->_configuration[0]._globalVars[_i]._qualifier == VQ_RETAIN)
            {
                _result = true;
                break;
            }
        if(_result)
        {
            _data += "  VAR_GLOBAL RETAIN\n";
            for(int _i = 0; _i < inst_->_configuration[0]._globalVars.size(); _i++)
                if(inst_->_configuration[0]._globalVars[_i]._qualifier == VQ_RETAIN)
                {
                    _data += QString("    %1 : %2")
                                .arg(inst_->_configuration[0]._globalVars[_i]._name, inst_->_configuration[0]._globalVars[_i]._type_name);
                    if(inst_->_configuration[0]._globalVars[_i]._initialValue._simpleValue != "")
                        _data += QString(" := %1;\n").arg(inst_->_configuration[0]._globalVars[_i]._initialValue._simpleValue);
                    else
                        _data += ";\n";
                }
            _data += "  END_VAR\n";
        }

        _result = false;
        for(int _i = 0; _i < inst_->_configuration[0]._globalVars.size(); _i++)
            if(inst_->_configuration[0]._globalVars[_i]._qualifier == VQ_NONRETAIN)
            {
                _result = true;
                break;
            }
        if(_result)
        {
            _data += "  VAR_GLOBAL NONRETAIN\n";
            for(int _i = 0; _i < inst_->_configuration[0]._globalVars.size(); _i++)
                if(inst_->_configuration[0]._globalVars[_i]._qualifier == VQ_NONRETAIN)
                {
                    _data += QString("    %1 : %2")
                                .arg(inst_->_configuration[0]._globalVars[_i]._name, inst_->_configuration[0]._globalVars[_i]._type_name);
                    if(inst_->_configuration[0]._globalVars[_i]._initialValue._simpleValue != "")
                        _data += QString(" := %1;\n").arg(inst_->_configuration[0]._globalVars[_i]._initialValue._simpleValue);
                    else
                        _data += ";\n";
                }
            _data += "  END_VAR\n";
        }

        _result = false;
        for(int _i = 0; _i < inst_->_configuration[0]._globalVars.size(); _i++)
            if(inst_->_configuration[0]._globalVars[_i]._qualifier == VQ_NOQUALIFIER)
            {
                _result = true;
                break;
            }
        if(_result)
        {
            _data += "  VAR_GLOBAL\n";
            for(int _i = 0; _i < inst_->_configuration[0]._globalVars.size(); _i++)
                if(inst_->_configuration[0]._globalVars[_i]._qualifier == VQ_NOQUALIFIER)
                {
                    _data += QString("    %1 : %2")
                                .arg(inst_->_configuration[0]._globalVars[_i]._name, inst_->_configuration[0]._globalVars[_i]._type_name);
                    if(inst_->_configuration[0]._globalVars[_i]._initialValue._simpleValue != "")
                        _data += QString(" := %1;\n").arg(inst_->_configuration[0]._globalVars[_i]._initialValue._simpleValue);
                    else
                        _data += ";\n";
                }
            _data += "  END_VAR\n";
        }
    }

    _data += QString("\n  RESOURCE %1 ON PLC\n").arg(inst_->_configuration[0]._resource._name);
    for(int _i = 0; _i < inst_->_configuration[0]._resource._task.size(); _i++)
    {
        _data += QString("    TASK %1(INTERVAL := %2,PRIORITY := %3);\n")
                    .arg(inst_->_configuration[0]._resource._task[_i]._name, inst_->_configuration[0]._resource._task[_i]._interval, inst_->_configuration[0]._resource._task[_i]._priority);
    }
    for(int _i = 0; _i < inst_->_configuration[0]._resource._task.size(); _i++)
    {
        for(int _j = 0; _j < inst_->_configuration[0]._resource._task[_i]._pouInstance.size(); _j++)
        {
            _data += QString("    PROGRAM %1 WITH %2 : %3;\n")
                        .arg(inst_->_configuration[0]._resource._task[_i]._pouInstance[_j]._name, inst_->_configuration[0]._resource._task[_i]._name, inst_->_configuration[0]._resource._task[_i]._pouInstance[_j]._typeName);
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
QString TranslatorIEC::getSTCode_pou(const QDomNode &node_)
{
    QString _text = {};

    T_POU _POU;
    if(PLCopenXmlParser::parsePOU(node_, &_POU))
        Code_STgenerator(_POU, _text);

    return _text;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void TranslatorIEC::AllVar_STgenerator(T_POU *pou_, QString &text_)
{
    bool _result;
    QString _data;
    QString _type_name;

    switch(pou_->_pouType)
    {
    case PT_PROGRAMM:{          _data = QString("PROGRAM %1\n").arg(pou_->_name);                                }break;
    case PT_FUNCTION:{          _data = QString("FUNCTION %1 : %2\n").arg(pou_->_name, pou_->_return_type);       }break;
    case PT_FUNCTION_BLOCK:{    _data = QString("FUNCTION_BLOCK %1\n").arg(pou_->_name);                         }break;
    case PT_NOT_DEFINED:{}break;
    case PT_MAX:{}break;
    }

    prepareAllRetainVar(pou_, _data);
    prepareAllNonRetainVar(pou_, _data);
    prepareAllConstantVar(pou_, _data);

    _result = false;
    if(!pou_->_interface._outputVars.isEmpty())
    {
        for(int _j = 0; _j < (int)pou_->_interface._outputVars.size(); _j++)
            if(!pou_->_interface._outputVars[_j]._is_used)
            {
                _result = true;
                break;
            }

        if(_result)
        {
            _data += "  VAR_OUTPUT\n";

            for(int _j = 0; _j < (int)pou_->_interface._outputVars.size(); _j++)
            {
                if(pou_->_interface._outputVars[_j]._is_used) continue;

                if(pou_->_interface._outputVars[_j]._type_name == "string")  _type_name = pou_->_interface._outputVars[_j]._type_name.toUpper();
                else                                                         _type_name = pou_->_interface._outputVars[_j]._type_name;

                QString _var = QString("    %1").arg(pou_->_interface._outputVars[_j]._name);

                if(pou_->_interface._outputVars[_j]._address != "")
                    _var = _var + QString(" AT %1").arg(pou_->_interface._outputVars[_j]._address);

                _var = _var + QString(" : %1").arg(_type_name);

                if(pou_->_interface._outputVars[_j]._initialValue._simpleValue != "")
                {
                    if(pou_->_interface._outputVars[_j]._type_name == "string")  _var = _var + QString(" := '%1'").arg(pou_->_interface._outputVars[_j]._initialValue._simpleValue);
                    else                                                         _var = _var + QString(" := %1").arg(pou_->_interface._outputVars[_j]._initialValue._simpleValue);
                }

                _var = _var + ";\n";

                _data += _var;
            }
            _data += "  END_VAR\n";
        }
    }

    _result = false;
    if(!pou_->_interface._inputVars.isEmpty())
    {
        for(int _j = 0; _j < (int)pou_->_interface._inputVars.size(); _j++)
            if(!pou_->_interface._inputVars[_j]._is_used)
            {
                _result = true;
                break;
            }

        if(_result)
        {
            _data += "  VAR_INPUT\n";

            for(int _j = 0; _j < (int)pou_->_interface._inputVars.size(); _j++)
            {
                if(pou_->_interface._inputVars[_j]._is_used) continue;

                if(pou_->_interface._inputVars[_j]._type_name == "string")  _type_name = pou_->_interface._inputVars[_j]._type_name.toUpper();
                else                                                        _type_name = pou_->_interface._inputVars[_j]._type_name;

                QString _var = QString("    %1").arg(pou_->_interface._inputVars[_j]._name);

                if(pou_->_interface._inputVars[_j]._address != "")
                    _var = _var + QString(" AT %1").arg(pou_->_interface._inputVars[_j]._address);

                _var = _var + QString(" : %1").arg(_type_name);

                if(pou_->_interface._inputVars[_j]._initialValue._simpleValue != "")
                {
                    if(pou_->_interface._inputVars[_j]._type_name == "string")  _var = _var + QString(" := '%1'").arg(pou_->_interface._inputVars[_j]._initialValue._simpleValue);
                    else                                                        _var = _var + QString(" := %1").arg(pou_->_interface._inputVars[_j]._initialValue._simpleValue);
                }

                _var = _var + ";\n";

                _data += _var;
            }
            _data += "  END_VAR\n";
        }
    }

    _result = false;
    if(!pou_->_interface._inoutVars.isEmpty())
    {
        for(int _j = 0; _j < (int)pou_->_interface._inoutVars.size(); _j++)
            if(!pou_->_interface._inoutVars[_j]._is_used)
            {
                _result = true;
                break;
            }

        if(_result)
        {
            _data += "  VAR_IN_OUT\n";

            for(int _j = 0; _j < (int)pou_->_interface._inoutVars.size(); _j++)
            {
                if(pou_->_interface._inoutVars[_j]._is_used) continue;

                if(pou_->_interface._inoutVars[_j]._type_name == "string")  _type_name = pou_->_interface._inoutVars[_j]._type_name.toUpper();
                else                                                        _type_name = pou_->_interface._inoutVars[_j]._type_name;

                QString _var = QString("    %1").arg(pou_->_interface._inoutVars[_j]._name);

                if(pou_->_interface._inoutVars[_j]._address != "")
                    _var = _var + QString(" AT %1").arg(pou_->_interface._inoutVars[_j]._address);

                _var = _var + QString(" : %1").arg(_type_name);

                if(pou_->_interface._inoutVars[_j]._initialValue._simpleValue != "")
                {
                    if(pou_->_interface._inoutVars[_j]._type_name == "string")  _var = _var + QString(" := '%1'").arg(pou_->_interface._inoutVars[_j]._initialValue._simpleValue);
                    else                                                        _var = _var + QString(" := %1").arg(pou_->_interface._inoutVars[_j]._initialValue._simpleValue);
                }

                _var = _var + ";\n";

                _data += _var;
            }
            _data += "  END_VAR\n";
        }
    }

    _result = false;
    if(!pou_->_interface._tempVars.isEmpty())
    {
        for(int _j = 0; _j < (int)pou_->_interface._tempVars.size(); _j++)
            if(!pou_->_interface._tempVars[_j]._is_used)
            {
                _result = true;
                break;
            }

        if(_result)
        {
            _data += "  VAR_TEMP\n";

            for(int _j = 0; _j < (int)pou_->_interface._tempVars.size(); _j++)
            {
                if(pou_->_interface._tempVars[_j]._is_used) continue;

                if(pou_->_interface._tempVars[_j]._type_name == "string")  _type_name = pou_->_interface._tempVars[_j]._type_name.toUpper();
                else                                                       _type_name = pou_->_interface._tempVars[_j]._type_name;

                QString _var = QString("    %1").arg(pou_->_interface._tempVars[_j]._name);

                if(pou_->_interface._tempVars[_j]._address != "")
                    _var = _var + QString(" AT %1").arg(pou_->_interface._tempVars[_j]._address);

                _var = _var + QString(" : %1").arg(_type_name);

                if(pou_->_interface._tempVars[_j]._initialValue._simpleValue != "")
                {
                    if(pou_->_interface._tempVars[_j]._type_name == "string")  _var = _var + QString(" := '%1'").arg(pou_->_interface._tempVars[_j]._initialValue._simpleValue);
                    else                                                       _var = _var + QString(" := %1").arg(pou_->_interface._tempVars[_j]._initialValue._simpleValue);
                }

                _var = _var + ";\n";

                _data += _var;
            }
            _data += "  END_VAR\n";
        }
    }

    _result = false;
    if(!pou_->_interface._externalVars.isEmpty())
    {
        for(int _j = 0; _j < (int)pou_->_interface._externalVars.size(); _j++)
            if(!pou_->_interface._externalVars[_j]._is_used)
            {
                _result = true;
                break;
            }

        if(_result)
        {
            _data += "  VAR_EXTERNAL\n";

            for(int _j = 0; _j < (int)pou_->_interface._externalVars.size(); _j++)
            {
                if(pou_->_interface._externalVars[_j]._is_used) continue;

                if(pou_->_interface._externalVars[_j]._type_name == "string")  _type_name = pou_->_interface._externalVars[_j]._type_name.toUpper();
                else                                                           _type_name = pou_->_interface._externalVars[_j]._type_name;

                QString _var = QString("    %1").arg(pou_->_interface._externalVars[_j]._name);

                if(pou_->_interface._externalVars[_j]._address != "")
                    _var = _var + QString(" AT %1").arg(pou_->_interface._externalVars[_j]._address);

                _var = _var + QString(" : %1").arg(_type_name);

                if(pou_->_interface._externalVars[_j]._initialValue._simpleValue != "")
                {
                    if(pou_->_interface._externalVars[_j]._type_name == "string")   _var = _var + QString(" := '%1'").arg(pou_->_interface._externalVars[_j]._initialValue._simpleValue);
                    else                                                            _var = _var + QString(" := %1").arg(pou_->_interface._externalVars[_j]._initialValue._simpleValue);
                }

                _var = _var + ";\n";

                _data += _var;
            }
            _data += "  END_VAR\n";
        }
    }

    _result = false;
    if(!pou_->_interface._localVars.isEmpty())
    {
        for(int _j = 0; _j < (int)pou_->_interface._localVars.size(); _j++)
            if(!pou_->_interface._localVars[_j]._is_used)
            {
                _result = true;
                break;
            }

        if(_result)
        {
            _data += "  VAR\n";

            for(int _j = 0; _j < (int)pou_->_interface._localVars.size(); _j++)
            {
                if(pou_->_interface._localVars[_j]._is_used) continue;

                if(pou_->_interface._localVars[_j]._type_name == "string")  _type_name = pou_->_interface._localVars[_j]._type_name.toUpper();
                else                                                        _type_name = pou_->_interface._localVars[_j]._type_name;

                QString _var = QString("    %1").arg(pou_->_interface._localVars[_j]._name);

                if(pou_->_interface._localVars[_j]._address != "")
                    _var = _var + QString(" AT %1").arg(pou_->_interface._localVars[_j]._address);

                _var = _var + QString(" : %1").arg(_type_name);

                if(pou_->_interface._localVars[_j]._initialValue._simpleValue != "")
                {
                    if(pou_->_interface._localVars[_j]._type_name == "string")   _var = _var + QString(" := '%1'").arg(pou_->_interface._localVars[_j]._initialValue._simpleValue);
                    else                                                         _var = _var + QString(" := %1").arg(pou_->_interface._localVars[_j]._initialValue._simpleValue);
                }

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
void TranslatorIEC::prepareAllRetainVar(T_POU *pou_, QString &text_)
{
    bool _result;
    QString _data;
    QString _type_name;

    _result = false;
    if(!pou_->_interface._outputVars.isEmpty())
    {
        for(int _j = 0; _j < (int)pou_->_interface._outputVars.size(); _j++)
            if(pou_->_interface._outputVars[_j]._qualifier == VQ_RETAIN)
            {
                _result = true;
                break;
            }

        if(_result)
        {
            _data += "  VAR_OUTPUT RETAIN\n";

            for(int _j = 0; _j < (int)pou_->_interface._outputVars.size(); _j++)
            {
                if(pou_->_interface._outputVars[_j]._qualifier == VQ_RETAIN)
                {
                    pou_->_interface._outputVars[_j]._is_used = true;

                    if(pou_->_interface._outputVars[_j]._type_name == "string")  _type_name = pou_->_interface._outputVars[_j]._type_name.toUpper();
                    else                                                         _type_name = pou_->_interface._outputVars[_j]._type_name;

                    QString _var = QString("    %1").arg(pou_->_interface._outputVars[_j]._name);

                    if(pou_->_interface._outputVars[_j]._address != "")
                        _var = _var + QString(" AT %1").arg(pou_->_interface._outputVars[_j]._address);

                    _var = _var + QString(" : %1").arg(_type_name);

                    if(pou_->_interface._outputVars[_j]._initialValue._simpleValue != "")
                    {
                        if(pou_->_interface._outputVars[_j]._type_name == "string")   _var = _var + QString(" := '%1'").arg(pou_->_interface._outputVars[_j]._initialValue._simpleValue);
                        else                                                          _var = _var + QString(" := %1").arg(pou_->_interface._outputVars[_j]._initialValue._simpleValue);
                    }

                    _var = _var + ";\n";

                    _data += _var;
                }
            }
            _data += "  END_VAR\n";
        }
    }

    _result = false;
    if(!pou_->_interface._inputVars.isEmpty())
    {
        for(int _j = 0; _j < (int)pou_->_interface._inputVars.size(); _j++)
            if(pou_->_interface._inputVars[_j]._qualifier == VQ_RETAIN)
            {
                _result = true;
                break;
            }

        if(_result)
        {
            _data += "  VAR_INPUT RETAIN\n";

            for(int _j = 0; _j < (int)pou_->_interface._inputVars.size(); _j++)
            {
                if(pou_->_interface._inputVars[_j]._qualifier == VQ_RETAIN)
                {
                    pou_->_interface._inputVars[_j]._is_used = true;

                    if(pou_->_interface._inputVars[_j]._type_name == "string")  _type_name = pou_->_interface._inputVars[_j]._type_name.toUpper();
                    else                                                        _type_name = pou_->_interface._inputVars[_j]._type_name;

                    QString _var = QString("    %1").arg(pou_->_interface._inputVars[_j]._name);

                    if(pou_->_interface._inputVars[_j]._address != "")
                        _var = _var + QString(" AT %1").arg(pou_->_interface._inputVars[_j]._address);

                    _var = _var + QString(" : %1").arg(_type_name);

                    if(pou_->_interface._inputVars[_j]._initialValue._simpleValue != "")
                    {
                        if(pou_->_interface._inputVars[_j]._type_name == "string")   _var = _var + QString(" := '%1'").arg(pou_->_interface._inputVars[_j]._initialValue._simpleValue);
                        else                                                         _var = _var + QString(" := %1").arg(pou_->_interface._inputVars[_j]._initialValue._simpleValue);
                    }

                    _var = _var + ";\n";

                    _data += _var;
                }
            }
            _data += "  END_VAR\n";
        }
    }

    _result = false;
    if(!pou_->_interface._inoutVars.isEmpty())
    {
        for(int _j = 0; _j < (int)pou_->_interface._inoutVars.size(); _j++)
            if(pou_->_interface._inoutVars[_j]._qualifier == VQ_RETAIN)
            {
                _result = true;
                break;
            }

        if(_result)
        {
            _data += "  VAR_IN_OUT RETAIN\n";

            for(int _j = 0; _j < (int)pou_->_interface._inoutVars.size(); _j++)
            {
                if(pou_->_interface._inoutVars[_j]._qualifier == VQ_RETAIN)
                {
                    pou_->_interface._inoutVars[_j]._is_used = true;

                    if(pou_->_interface._inoutVars[_j]._type_name == "string")  _type_name = pou_->_interface._inoutVars[_j]._type_name.toUpper();
                    else                                                        _type_name = pou_->_interface._inoutVars[_j]._type_name;

                    QString _var = QString("    %1").arg(pou_->_interface._inoutVars[_j]._name);

                    if(pou_->_interface._inoutVars[_j]._address != "")
                        _var = _var + QString(" AT %1").arg(pou_->_interface._inoutVars[_j]._address);

                    _var = _var + QString(" : %1").arg(_type_name);

                    if(pou_->_interface._inoutVars[_j]._initialValue._simpleValue != "")
                    {
                        if(pou_->_interface._inoutVars[_j]._type_name == "string")   _var = _var + QString(" := '%1'").arg(pou_->_interface._inoutVars[_j]._initialValue._simpleValue);
                        else                                                         _var = _var + QString(" := %1").arg(pou_->_interface._inoutVars[_j]._initialValue._simpleValue);
                    }

                    _var = _var + ";\n";

                    _data += _var;
                }
            }
            _data += "  END_VAR\n";
        }
    }

    _result = false;
    if(!pou_->_interface._tempVars.isEmpty())
    {
        for(int _j = 0; _j < (int)pou_->_interface._tempVars.size(); _j++)
            if(pou_->_interface._tempVars[_j]._qualifier == VQ_RETAIN)
            {
                _result = true;
                break;
            }

        if(_result)
        {
            _data += "  VAR_TEMP RETAIN\n";

            for(int _j = 0; _j < (int)pou_->_interface._tempVars.size(); _j++)
            {
                if(pou_->_interface._tempVars[_j]._qualifier == VQ_RETAIN)
                {
                    pou_->_interface._tempVars[_j]._is_used = true;

                    if(pou_->_interface._tempVars[_j]._type_name == "string")  _type_name = pou_->_interface._tempVars[_j]._type_name.toUpper();
                    else                                                       _type_name = pou_->_interface._tempVars[_j]._type_name;

                    QString _var = QString("    %1").arg(pou_->_interface._tempVars[_j]._name);

                    if(pou_->_interface._tempVars[_j]._address != "")
                        _var = _var + QString(" AT %1").arg(pou_->_interface._tempVars[_j]._address);

                    _var = _var + QString(" : %1").arg(_type_name);

                    if(pou_->_interface._tempVars[_j]._initialValue._simpleValue != "")
                    {
                        if(pou_->_interface._tempVars[_j]._type_name == "string")   _var = _var + QString(" := '%1'").arg(pou_->_interface._tempVars[_j]._initialValue._simpleValue);
                        else                                                        _var = _var + QString(" := %1").arg(pou_->_interface._tempVars[_j]._initialValue._simpleValue);
                    }

                    _var = _var + ";\n";

                    _data += _var;
                }
            }
            _data += "  END_VAR\n";
        }
    }

    _result = false;
    if(!pou_->_interface._localVars.isEmpty())
    {
        for(int _j = 0; _j < (int)pou_->_interface._localVars.size(); _j++)
            if(pou_->_interface._localVars[_j]._qualifier == VQ_RETAIN)
            {
                _result = true;
                break;
            }

        if(_result)
        {
            _data += "  VAR RETAIN\n";

            for(int _j = 0; _j < (int)pou_->_interface._localVars.size(); _j++)
            {
                if(pou_->_interface._localVars[_j]._qualifier == VQ_RETAIN)
                {
                    pou_->_interface._localVars[_j]._is_used = true;

                    if(pou_->_interface._localVars[_j]._type_name == "string")  _type_name = pou_->_interface._localVars[_j]._type_name.toUpper();
                    else                                                        _type_name = pou_->_interface._localVars[_j]._type_name;

                    QString _var = QString("    %1").arg(pou_->_interface._localVars[_j]._name);

                    if(pou_->_interface._localVars[_j]._address != "")
                        _var = _var + QString(" AT %1").arg(pou_->_interface._localVars[_j]._address);

                    _var = _var + QString(" : %1").arg(_type_name);

                    if(pou_->_interface._localVars[_j]._initialValue._simpleValue != "")
                    {
                        if(pou_->_interface._localVars[_j]._type_name == "string")   _var = _var + QString(" := '%1'").arg(pou_->_interface._localVars[_j]._initialValue._simpleValue);
                        else                                                         _var = _var + QString(" := %1").arg(pou_->_interface._localVars[_j]._initialValue._simpleValue);
                    }

                    _var = _var + ";\n";

                    _data += _var;
                }
            }
            _data += "  END_VAR\n";
        }
    }

    _result = false;
    if(!pou_->_interface._externalVars.isEmpty())
    {
        for(int _j = 0; _j < (int)pou_->_interface._externalVars.size(); _j++)
            if(pou_->_interface._externalVars[_j]._qualifier == VQ_RETAIN)
            {
                _result = true;
                break;
            }

        if(_result)
        {
            _data += "  VAR_EXTERNAL RETAIN\n";

            for(int _j = 0; _j < (int)pou_->_interface._externalVars.size(); _j++)
            {
                if(pou_->_interface._externalVars[_j]._qualifier == VQ_RETAIN)
                {
                    pou_->_interface._externalVars[_j]._is_used = true;

                    if(pou_->_interface._externalVars[_j]._type_name == "string")  _type_name = pou_->_interface._externalVars[_j]._type_name.toUpper();
                    else                                                           _type_name = pou_->_interface._externalVars[_j]._type_name;

                    QString _var = QString("    %1").arg(pou_->_interface._externalVars[_j]._name);

                    if(pou_->_interface._externalVars[_j]._address != "")
                        _var = _var + QString(" AT %1").arg(pou_->_interface._externalVars[_j]._address);

                    _var = _var + QString(" : %1").arg(_type_name);

                    if(pou_->_interface._externalVars[_j]._initialValue._simpleValue != "")
                    {
                        if(pou_->_interface._externalVars[_j]._type_name == "string")   _var = _var + QString(" := '%1'").arg(pou_->_interface._externalVars[_j]._initialValue._simpleValue);
                        else                                                            _var = _var + QString(" := %1").arg(pou_->_interface._externalVars[_j]._initialValue._simpleValue);
                    }

                    _var = _var + ";\n";

                    _data += _var;
                }
            }
            _data += "  END_VAR\n";
        }
    }

    text_ += _data;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void TranslatorIEC::prepareAllNonRetainVar(T_POU *pou_, QString &text_)
{
    bool _result;
    QString _data;
    QString _type_name;

    _result = false;
    if(!pou_->_interface._outputVars.isEmpty())
    {
        for(int _j = 0; _j < (int)pou_->_interface._outputVars.size(); _j++)
            if(pou_->_interface._outputVars[_j]._qualifier == VQ_NONRETAIN)
            {
                _result = true;
                break;
            }

        if(_result)
        {
            _data += "  VAR_OUTPUT NON_RETAIN\n";

            for(int _j = 0; _j < (int)pou_->_interface._outputVars.size(); _j++)
            {
                if(pou_->_interface._outputVars[_j]._qualifier == VQ_NONRETAIN)
                {
                    pou_->_interface._outputVars[_j]._is_used = true;

                    if(pou_->_interface._outputVars[_j]._type_name == "string")  _type_name = pou_->_interface._outputVars[_j]._type_name.toUpper();
                    else                                                         _type_name = pou_->_interface._outputVars[_j]._type_name;

                    QString _var = QString("    %1").arg(pou_->_interface._outputVars[_j]._name);

                    if(pou_->_interface._outputVars[_j]._address != "")
                        _var = _var + QString(" AT %1").arg(pou_->_interface._outputVars[_j]._address);

                    _var = _var + QString(" : %1").arg(_type_name);

                    if(pou_->_interface._outputVars[_j]._initialValue._simpleValue != "")
                    {
                        if(pou_->_interface._outputVars[_j]._type_name == "string")   _var = _var + QString(" := '%1'").arg(pou_->_interface._outputVars[_j]._initialValue._simpleValue);
                        else                                                          _var = _var + QString(" := %1").arg(pou_->_interface._outputVars[_j]._initialValue._simpleValue);
                    }

                    _var = _var + ";\n";

                    _data += _var;
                }
            }
            _data += "  END_VAR\n";
        }
    }

    _result = false;
    if(!pou_->_interface._inputVars.isEmpty())
    {
        for(int _j = 0; _j < (int)pou_->_interface._inputVars.size(); _j++)
            if(pou_->_interface._inputVars[_j]._qualifier == VQ_NONRETAIN)
            {
                _result = true;
                break;
            }

        if(_result)
        {
            _data += "  VAR_INPUT NON_RETAIN\n";

            for(int _j = 0; _j < (int)pou_->_interface._inputVars.size(); _j++)
            {
                if(pou_->_interface._inputVars[_j]._qualifier == VQ_NONRETAIN)
                {
                    pou_->_interface._inputVars[_j]._is_used = true;

                    if(pou_->_interface._inputVars[_j]._type_name == "string")  _type_name = pou_->_interface._inputVars[_j]._type_name.toUpper();
                    else                                                        _type_name = pou_->_interface._inputVars[_j]._type_name;

                    QString _var = QString("    %1").arg(pou_->_interface._inputVars[_j]._name);

                    if(pou_->_interface._inputVars[_j]._address != "")
                        _var = _var + QString(" AT %1").arg(pou_->_interface._inputVars[_j]._address);

                    _var = _var + QString(" : %1").arg(_type_name);

                    if(pou_->_interface._inputVars[_j]._initialValue._simpleValue != "")
                    {
                        if(pou_->_interface._inputVars[_j]._type_name == "string")   _var = _var + QString(" := '%1'").arg(pou_->_interface._inputVars[_j]._initialValue._simpleValue);
                        else                                                         _var = _var + QString(" := %1").arg(pou_->_interface._inputVars[_j]._initialValue._simpleValue);
                    }

                    _var = _var + ";\n";

                    _data += _var;
                }
            }
            _data += "  END_VAR\n";
        }
    }

    _result = false;
    if(!pou_->_interface._inoutVars.isEmpty())
    {
        for(int _j = 0; _j < (int)pou_->_interface._inoutVars.size(); _j++)
            if(pou_->_interface._inoutVars[_j]._qualifier == VQ_NONRETAIN)
            {
                _result = true;
                break;
            }

        if(_result)
        {
            _data += "  VAR_IN_OUT NON_RETAIN\n";

            for(int _j = 0; _j < (int)pou_->_interface._inoutVars.size(); _j++)
            {
                if(pou_->_interface._inoutVars[_j]._qualifier == VQ_NONRETAIN)
                {
                    pou_->_interface._inoutVars[_j]._is_used = true;

                    if(pou_->_interface._inoutVars[_j]._type_name == "string")  _type_name = pou_->_interface._inoutVars[_j]._type_name.toUpper();
                    else                                                        _type_name = pou_->_interface._inoutVars[_j]._type_name;

                    QString _var = QString("    %1").arg(pou_->_interface._inoutVars[_j]._name);

                    if(pou_->_interface._inoutVars[_j]._address != "")
                        _var = _var + QString(" AT %1").arg(pou_->_interface._inoutVars[_j]._address);

                    _var = _var + QString(" : %1").arg(_type_name);

                    if(pou_->_interface._inoutVars[_j]._initialValue._simpleValue != "")
                    {
                        if(pou_->_interface._inoutVars[_j]._type_name == "string")   _var = _var + QString(" := '%1'").arg(pou_->_interface._inoutVars[_j]._initialValue._simpleValue);
                        else                                                         _var = _var + QString(" := %1").arg(pou_->_interface._inoutVars[_j]._initialValue._simpleValue);
                    }

                    _var = _var + ";\n";

                    _data += _var;
                }
            }
            _data += "  END_VAR\n";
        }
    }

    _result = false;
    if(!pou_->_interface._tempVars.isEmpty())
    {
        for(int _j = 0; _j < (int)pou_->_interface._tempVars.size(); _j++)
            if(pou_->_interface._tempVars[_j]._qualifier == VQ_NONRETAIN)
            {
                _result = true;
                break;
            }

        if(_result)
        {
            _data += "  VAR_TEMP NON_RETAIN\n";

            for(int _j = 0; _j < (int)pou_->_interface._tempVars.size(); _j++)
            {
                if(pou_->_interface._tempVars[_j]._qualifier == VQ_NONRETAIN)
                {
                    pou_->_interface._tempVars[_j]._is_used = true;

                    if(pou_->_interface._tempVars[_j]._type_name == "string")  _type_name = pou_->_interface._tempVars[_j]._type_name.toUpper();
                    else                                                       _type_name = pou_->_interface._tempVars[_j]._type_name;

                    QString _var = QString("    %1").arg(pou_->_interface._tempVars[_j]._name);

                    if(pou_->_interface._tempVars[_j]._address != "")
                        _var = _var + QString(" AT %1").arg(pou_->_interface._tempVars[_j]._address);

                    _var = _var + QString(" : %1").arg(_type_name);

                    if(pou_->_interface._tempVars[_j]._initialValue._simpleValue != "")
                    {
                        if(pou_->_interface._tempVars[_j]._type_name == "string")   _var = _var + QString(" := '%1'").arg(pou_->_interface._tempVars[_j]._initialValue._simpleValue);
                        else                                                        _var = _var + QString(" := %1").arg(pou_->_interface._tempVars[_j]._initialValue._simpleValue);
                    }

                    _var = _var + ";\n";

                    _data += _var;
                }
            }
            _data += "  END_VAR\n";
        }
    }

    _result = false;
    if(!pou_->_interface._localVars.isEmpty())
    {
        for(int _j = 0; _j < (int)pou_->_interface._localVars.size(); _j++)
            if(pou_->_interface._localVars[_j]._qualifier == VQ_NONRETAIN)
            {
                _result = true;
                break;
            }

        if(_result)
        {
            _data += "  VAR NON_RETAIN\n";

            for(int _j = 0; _j < (int)pou_->_interface._localVars.size(); _j++)
            {
                if(pou_->_interface._localVars[_j]._qualifier == VQ_NONRETAIN)
                {
                    pou_->_interface._localVars[_j]._is_used = true;

                    if(pou_->_interface._localVars[_j]._type_name == "string")  _type_name = pou_->_interface._localVars[_j]._type_name.toUpper();
                    else                                                        _type_name = pou_->_interface._localVars[_j]._type_name;

                    QString _var = QString("    %1").arg(pou_->_interface._localVars[_j]._name);

                    if(pou_->_interface._localVars[_j]._address != "")
                        _var = _var + QString(" AT %1").arg(pou_->_interface._localVars[_j]._address);

                    _var = _var + QString(" : %1").arg(_type_name);

                    if(pou_->_interface._localVars[_j]._initialValue._simpleValue != "")
                    {
                        if(pou_->_interface._localVars[_j]._type_name == "string")   _var = _var + QString(" := '%1'").arg(pou_->_interface._localVars[_j]._initialValue._simpleValue);
                        else                                                         _var = _var + QString(" := %1").arg(pou_->_interface._localVars[_j]._initialValue._simpleValue);
                    }

                    _var = _var + ";\n";

                    _data += _var;
                }
            }
            _data += "  END_VAR\n";
        }
    }

    _result = false;
    if(!pou_->_interface._externalVars.isEmpty())
    {
        for(int _j = 0; _j < (int)pou_->_interface._externalVars.size(); _j++)
            if(pou_->_interface._externalVars[_j]._qualifier == VQ_NONRETAIN)
            {
                _result = true;
                break;
            }

        if(_result)
        {
            _data += "  VAR_EXTERNAL NON_RETAIN\n";

            for(int _j = 0; _j < (int)pou_->_interface._externalVars.size(); _j++)
            {
                if(pou_->_interface._externalVars[_j]._qualifier == VQ_NONRETAIN)
                {
                    pou_->_interface._externalVars[_j]._is_used = true;

                    if(pou_->_interface._externalVars[_j]._type_name == "string")  _type_name = pou_->_interface._externalVars[_j]._type_name.toUpper();
                    else                                                           _type_name = pou_->_interface._externalVars[_j]._type_name;

                    QString _var = QString("    %1").arg(pou_->_interface._externalVars[_j]._name);

                    if(pou_->_interface._externalVars[_j]._address != "")
                        _var = _var + QString(" AT %1").arg(pou_->_interface._externalVars[_j]._address);

                    _var = _var + QString(" : %1").arg(_type_name);

                    if(pou_->_interface._externalVars[_j]._initialValue._simpleValue != "")
                    {
                        if(pou_->_interface._externalVars[_j]._type_name == "string")   _var = _var + QString(" := '%1'").arg(pou_->_interface._externalVars[_j]._initialValue._simpleValue);
                        else                                                            _var = _var + QString(" := %1").arg(pou_->_interface._externalVars[_j]._initialValue._simpleValue);
                    }

                    _var = _var + ";\n";

                    _data += _var;
                }
            }
            _data += "  END_VAR\n";
        }
    }

    text_ += _data;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void TranslatorIEC::prepareAllConstantVar(T_POU *pou_, QString &text_)
{
    bool _result;
    QString _data;
    QString _type_name;

    _result = false;
    if(!pou_->_interface._outputVars.isEmpty())
    {
        for(int _j = 0; _j < (int)pou_->_interface._outputVars.size(); _j++)
            if(pou_->_interface._outputVars[_j]._qualifier == VQ_CONSTANT)
            {
                _result = true;
                break;
            }

        if(_result)
        {
            _data += "  VAR_OUTPUT CONSTANT\n";

            for(int _j = 0; _j < (int)pou_->_interface._outputVars.size(); _j++)
            {
                if(pou_->_interface._outputVars[_j]._qualifier == VQ_CONSTANT)
                {
                    pou_->_interface._outputVars[_j]._is_used = true;

                    if(pou_->_interface._outputVars[_j]._type_name == "string")  _type_name = pou_->_interface._outputVars[_j]._type_name.toUpper();
                    else                                                         _type_name = pou_->_interface._outputVars[_j]._type_name;

                    QString _var = QString("    %1").arg(pou_->_interface._outputVars[_j]._name);

                    if(pou_->_interface._outputVars[_j]._address != "")
                        _var = _var + QString(" AT %1").arg(pou_->_interface._outputVars[_j]._address);

                    _var = _var + QString(" : %1").arg(_type_name);

                    if(pou_->_interface._outputVars[_j]._initialValue._simpleValue != "")
                    {
                        if(pou_->_interface._outputVars[_j]._type_name == "string")   _var = _var + QString(" := '%1'").arg(pou_->_interface._outputVars[_j]._initialValue._simpleValue);
                        else                                                          _var = _var + QString(" := %1").arg(pou_->_interface._outputVars[_j]._initialValue._simpleValue);
                    }

                    _var = _var + ";\n";

                    _data += _var;
                }
            }
            _data += "  END_VAR\n";
        }
    }

    _result = false;
    if(!pou_->_interface._inputVars.isEmpty())
    {
        for(int _j = 0; _j < (int)pou_->_interface._inputVars.size(); _j++)
            if(pou_->_interface._inputVars[_j]._qualifier == VQ_CONSTANT)
            {
                _result = true;
                break;
            }

        if(_result)
        {
            _data += "  VAR_INPUT CONSTANT\n";

            for(int _j = 0; _j < (int)pou_->_interface._inputVars.size(); _j++)
            {
                if(pou_->_interface._inputVars[_j]._qualifier == VQ_CONSTANT)
                {
                    pou_->_interface._inputVars[_j]._is_used = true;

                    if(pou_->_interface._inputVars[_j]._type_name == "string")  _type_name = pou_->_interface._inputVars[_j]._type_name.toUpper();
                    else                                                        _type_name = pou_->_interface._inputVars[_j]._type_name;

                    QString _var = QString("    %1").arg(pou_->_interface._inputVars[_j]._name);

                    if(pou_->_interface._inputVars[_j]._address != "")
                        _var = _var + QString(" AT %1").arg(pou_->_interface._inputVars[_j]._address);

                    _var = _var + QString(" : %1").arg(_type_name);

                    if(pou_->_interface._inputVars[_j]._initialValue._simpleValue != "")
                    {
                        if(pou_->_interface._inputVars[_j]._type_name == "string")   _var = _var + QString(" := '%1'").arg(pou_->_interface._inputVars[_j]._initialValue._simpleValue);
                        else                                                         _var = _var + QString(" := %1").arg(pou_->_interface._inputVars[_j]._initialValue._simpleValue);
                    }

                    _var = _var + ";\n";

                    _data += _var;
                }
            }
            _data += "  END_VAR\n";
        }
    }

    _result = false;
    if(!pou_->_interface._inoutVars.isEmpty())
    {
        for(int _j = 0; _j < (int)pou_->_interface._inoutVars.size(); _j++)
            if(pou_->_interface._inoutVars[_j]._qualifier == VQ_CONSTANT)
            {
                _result = true;
                break;
            }

        if(_result)
        {
            _data += "  VAR_IN_OUT CONSTANT\n";

            for(int _j = 0; _j < (int)pou_->_interface._inoutVars.size(); _j++)
            {
                if(pou_->_interface._inoutVars[_j]._qualifier == VQ_CONSTANT)
                {
                    pou_->_interface._inoutVars[_j]._is_used = true;

                    if(pou_->_interface._inoutVars[_j]._type_name == "string")  _type_name = pou_->_interface._inoutVars[_j]._type_name.toUpper();
                    else                                                        _type_name = pou_->_interface._inoutVars[_j]._type_name;

                    QString _var = QString("    %1").arg(pou_->_interface._inoutVars[_j]._name);

                    if(pou_->_interface._inoutVars[_j]._address != "")
                        _var = _var + QString(" AT %1").arg(pou_->_interface._inoutVars[_j]._address);

                    _var = _var + QString(" : %1").arg(_type_name);

                    if(pou_->_interface._inoutVars[_j]._initialValue._simpleValue != "")
                    {
                        if(pou_->_interface._inputVars[_j]._type_name == "string")   _var = _var + QString(" := '%1'").arg(pou_->_interface._inoutVars[_j]._initialValue._simpleValue);
                        else                                                         _var = _var + QString(" := %1").arg(pou_->_interface._inoutVars[_j]._initialValue._simpleValue);
                    }

                    _var = _var + ";\n";

                    _data += _var;
                }
            }
            _data += "  END_VAR\n";
        }
    }

    _result = false;
    if(!pou_->_interface._tempVars.isEmpty())
    {
        for(int _j = 0; _j < (int)pou_->_interface._tempVars.size(); _j++)
            if(pou_->_interface._tempVars[_j]._qualifier == VQ_CONSTANT)
            {
                _result = true;
                break;
            }

        if(_result)
        {
            _data += "  VAR_TEMP CONSTANT\n";

            for(int _j = 0; _j < (int)pou_->_interface._tempVars.size(); _j++)
            {
                if(pou_->_interface._tempVars[_j]._qualifier == VQ_CONSTANT)
                {
                    pou_->_interface._tempVars[_j]._is_used = true;

                    if(pou_->_interface._tempVars[_j]._type_name == "string")  _type_name = pou_->_interface._tempVars[_j]._type_name.toUpper();
                    else                                                       _type_name = pou_->_interface._tempVars[_j]._type_name;

                    QString _var = QString("    %1").arg(pou_->_interface._tempVars[_j]._name);

                    if(pou_->_interface._tempVars[_j]._address != "")
                        _var = _var + QString(" AT %1").arg(pou_->_interface._tempVars[_j]._address);

                    _var = _var + QString(" : %1").arg(_type_name);

                    if(pou_->_interface._tempVars[_j]._initialValue._simpleValue != "")
                    {
                        if(pou_->_interface._tempVars[_j]._type_name == "string")   _var = _var + QString(" := '%1'").arg(pou_->_interface._tempVars[_j]._initialValue._simpleValue);
                        else                                                        _var = _var + QString(" := %1").arg(pou_->_interface._tempVars[_j]._initialValue._simpleValue);
                    }

                    _var = _var + ";\n";

                    _data += _var;
                }
            }
            _data += "  END_VAR\n";
        }
    }

    _result = false;
    if(!pou_->_interface._localVars.isEmpty())
    {
        for(int _j = 0; _j < (int)pou_->_interface._localVars.size(); _j++)
            if(pou_->_interface._localVars[_j]._qualifier == VQ_CONSTANT)
            {
                _result = true;
                break;
            }

        if(_result)
        {
            _data += "  VAR CONSTANT\n";

            for(int _j = 0; _j < (int)pou_->_interface._localVars.size(); _j++)
            {
                if(pou_->_interface._localVars[_j]._qualifier == VQ_CONSTANT)
                {
                    pou_->_interface._localVars[_j]._is_used = true;

                    if(pou_->_interface._localVars[_j]._type_name == "string")  _type_name = pou_->_interface._localVars[_j]._type_name.toUpper();
                    else                                                        _type_name = pou_->_interface._localVars[_j]._type_name;

                    QString _var = QString("    %1").arg(pou_->_interface._localVars[_j]._name);

                    if(pou_->_interface._localVars[_j]._address != "")
                        _var = _var + QString(" AT %1").arg(pou_->_interface._localVars[_j]._address);

                    _var = _var + QString(" : %1").arg(_type_name);

                    if(pou_->_interface._localVars[_j]._initialValue._simpleValue != "")
                    {
                        if(pou_->_interface._localVars[_j]._type_name == "string")   _var = _var + QString(" := '%1'").arg(pou_->_interface._localVars[_j]._initialValue._simpleValue);
                        else                                                         _var = _var + QString(" := %1").arg(pou_->_interface._localVars[_j]._initialValue._simpleValue);
                    }

                    _var = _var + ";\n";

                    _data += _var;
                }
            }
            _data += "  END_VAR\n";
        }
    }

    _result = false;
    if(!pou_->_interface._externalVars.isEmpty())
    {
        for(int _j = 0; _j < (int)pou_->_interface._externalVars.size(); _j++)
            if(pou_->_interface._externalVars[_j]._qualifier == VQ_CONSTANT)
            {
                _result = true;
                break;
            }

        if(_result)
        {
            _data += "  VAR_EXTERNAL CONSTANT\n";

            for(int _j = 0; _j < (int)pou_->_interface._externalVars.size(); _j++)
            {
                if(pou_->_interface._externalVars[_j]._qualifier == VQ_CONSTANT)
                {
                    pou_->_interface._externalVars[_j]._is_used = true;

                    if(pou_->_interface._externalVars[_j]._type_name == "string")  _type_name = pou_->_interface._externalVars[_j]._type_name.toUpper();
                    else                                                           _type_name = pou_->_interface._externalVars[_j]._type_name;

                    QString _var = QString("    %1").arg(pou_->_interface._externalVars[_j]._name);

                    if(pou_->_interface._externalVars[_j]._address != "")
                        _var = _var + QString(" AT %1").arg(pou_->_interface._externalVars[_j]._address);

                    _var = _var + QString(" : %1").arg(_type_name);

                    if(pou_->_interface._externalVars[_j]._initialValue._simpleValue != "")
                    {
                        if(pou_->_interface._externalVars[_j]._type_name == "string")   _var = _var + QString(" := '%1'").arg(pou_->_interface._externalVars[_j]._initialValue._simpleValue);
                        else                                                            _var = _var + QString(" := %1").arg(pou_->_interface._externalVars[_j]._initialValue._simpleValue);
                    }

                    _var = _var + ";\n";

                    _data += _var;
                }
            }
            _data += "  END_VAR\n";
        }
    }

    text_ += _data;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
QString TranslatorIEC::getTypeByVar(const T_POU *pou_, QString _var_name)
{
    bool _result = false;
    QString _type_name;

    if(_var_name == pou_->_name)
        _type_name = pou_->_return_type;
    else{
        if(!_result)
            for(int _j = 0; _j < (int)pou_->_interface._localVars.size(); _j++)
                if(pou_->_interface._localVars[_j]._name == _var_name)
                {
                    if(pou_->_interface._localVars[_j]._type_name == "string")  _type_name = pou_->_interface._localVars[_j]._type_name.toUpper();
                    else                                                        _type_name = pou_->_interface._localVars[_j]._type_name;
                    _result = true;
                }
        if(!_result)
            for(int _j = 0; _j < (int)pou_->_interface._inputVars.size(); _j++)
                if(pou_->_interface._inputVars[_j]._name == _var_name)
                {
                    if(pou_->_interface._inputVars[_j]._type_name == "string")  _type_name = pou_->_interface._inputVars[_j]._type_name.toUpper();
                    else                                                        _type_name = pou_->_interface._inputVars[_j]._type_name;
                    _result = true;
                }
        if(!_result)
            for(int _j = 0; _j < (int)pou_->_interface._outputVars.size(); _j++)
                if(pou_->_interface._outputVars[_j]._name == _var_name)
                {
                    if(pou_->_interface._outputVars[_j]._type_name == "string")  _type_name = pou_->_interface._outputVars[_j]._type_name.toUpper();
                    else                                                         _type_name = pou_->_interface._outputVars[_j]._type_name;
                    _result = true;
                }
        if(!_result)
            for(int _j = 0; _j < (int)pou_->_interface._inoutVars.size(); _j++)
                if(pou_->_interface._inoutVars[_j]._name == _var_name)
                {
                    if(pou_->_interface._inoutVars[_j]._type_name == "string")  _type_name = pou_->_interface._inoutVars[_j]._type_name.toUpper();
                    else                                                        _type_name = pou_->_interface._inoutVars[_j]._type_name;
                    _result = true;
                }
        if(!_result)
            for(int _j = 0; _j < (int)pou_->_interface._globalVars.size(); _j++)
                if(pou_->_interface._globalVars[_j]._name == _var_name)
                {
                    if(pou_->_interface._globalVars[_j]._type_name == "string")  _type_name = pou_->_interface._globalVars[_j]._type_name.toUpper();
                    else                                                         _type_name = pou_->_interface._globalVars[_j]._type_name;
                    _result = true;
                }
        if(!_result)
            for(int _j = 0; _j < (int)pou_->_interface._externalVars.size(); _j++)
                if(pou_->_interface._externalVars[_j]._name == _var_name)
                {
                    if(pou_->_interface._externalVars[_j]._type_name == "string")  _type_name = pou_->_interface._externalVars[_j]._type_name.toUpper();
                    else                                                           _type_name = pou_->_interface._externalVars[_j]._type_name;
                    _result = true;
                }
        if(!_result)
            for(int _j = 0; _j < (int)pou_->_interface._tempVars.size(); _j++)
                if(pou_->_interface._tempVars[_j]._name == _var_name)
                {
                    if(pou_->_interface._tempVars[_j]._type_name == "string")  _type_name = pou_->_interface._tempVars[_j]._type_name.toUpper();
                    else                                                       _type_name = pou_->_interface._tempVars[_j]._type_name;
                    _result = true;
                }
    }
    return _type_name;
}
//-----------------------------------------------------------------------------------
// ***
