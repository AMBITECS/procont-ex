//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
#include <QFile>
#include "XmlParser.h"
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
QString _base_type_name[] = {
    "BOOL",
    "SINT",
    "INT",
    "DINT",
    "LINT",
    "USINT",
    "UINT",
    "UDINT",
    "ULINT",
    "REAL",
    "LREAL",
    "TIME",
    "DATE",
    "TOD",
    "DT",
    "STRING",
    "BYTE",
    "WORD",
    "DWORD",
    "LWORD"
};
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
PLCopenXmlParser::PLCopenXmlParser(QObject *parent) : QObject(parent),
                                                        _m_xml_file("")
{
    PROJECT_SECTION_NAME[0]._name ="fileHeader";
    PROJECT_SECTION_NAME[1]._name ="contentHeader";
    PROJECT_SECTION_NAME[2]._name ="types";
    PROJECT_SECTION_NAME[3]._name ="instances";
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool PLCopenXmlParser::setXmlFile(QString _xml_file)
{
    bool        _result = true;
    QString     _errorStr;
    int         _errorLine;
    int         _errorColumn;

    _m_xml_file = _xml_file;
    _m_file.setFileName(_m_xml_file);

    if(_m_doc.setContent(&_m_file, true, &_errorStr, &_errorLine, &_errorColumn))
    {
        QDomElement _root = _m_doc.documentElement();
        if(_root.tagName() == "project")
        {
            QDomNode _node = _root.firstChild();
            while(!_node.isNull())
            {
                for(int _i = 0; _i < ARRAY_SIZE(PROJECT_SECTION_NAME); _i++)
                    if(_node.toElement().tagName() == PROJECT_SECTION_NAME[_i]._name)
                    {
                        switch(_i)
                        {
                        case 0:{    _result &= fileHeaderParser(_node);    }break;
                        case 1:{    _result &= contentHeaderParser(_node); }break;
                        case 2:{    _result &= typesParser(_node);         }break;
                        case 3:{    _result &= instancesParser(_node);     }break;
                        default:{}break;
                        }
                        break;
                    }
                _node = _node.nextSibling();
            }
        }
    }

    return _result;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool PLCopenXmlParser::fileHeaderParser(QDomNode _node)
{
    Q_UNUSED(_node)
    return true;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool PLCopenXmlParser::contentHeaderParser(QDomNode _node)
{
    Q_UNUSED(_node)
    return true;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool PLCopenXmlParser::typesParser(QDomNode _node)
{
    QDomNode _type_node = _node.firstChild();

    while(!_type_node.isNull())
    {
        if(_type_node.toElement().tagName() == "dataTypes")
        {
            _m_user_data_type_node = _type_node;
        }else
        if(_type_node.toElement().tagName() == "pous")
        {
            _m_pou_node = _type_node.firstChild();
        }
        _type_node = _type_node.nextSibling();
    }
    return true;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool PLCopenXmlParser::POU(quint32 _index, T_POU *_pou)
{
    bool _result = false;
    quint32 _pou_counter = 0;
    QDomNode _pou_node = _m_pou_node;

    while(!_pou_node.isNull())
    {
        if(_pou_counter == _index)
        {
            _result = true;
            checkPOUattr(_pou_node, _pou);

            QDomNode _node = _pou_node.firstChild();
            while(!_node.isNull())
            {
                if(_node.toElement().tagName() == "interface")      checkPOUinterface(_node, _pou);
                if(_node.toElement().tagName() == "body")           checkPOUbody(_node, _pou);
                if(_node.toElement().tagName() == "actions")        checkPOUactions(_node, _pou);
                if(_node.toElement().tagName() == "documentation")  checkPOUdocumentation(_node, _pou);
                _node = _node.nextSibling();
            }
            _result = true;
            break;
        }
        _pou_node = _pou_node.nextSibling();
        _pou_counter++;
    }

    return _result;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool PLCopenXmlParser::parsePOU(const QDomNode &node_, T_POU * data_)
{
    // node is pou
    if(node_.nodeName() != "pou")
        return false;

    // attr
    checkPOUattr(node_, data_);
    // interface
    auto _child = node_.toElement().namedItem("interface");
    if(!_child.isNull())
        checkPOUinterface(_child, data_);
    // body
    _child = node_.toElement().namedItem("body");
    if(_child.isNull())
        return false;
    else
        checkPOUbody(_child, data_);
    // actions
    _child = node_.toElement().namedItem("actions");
    if(!_child.isNull())
        checkPOUactions(_child, data_);
    // documentation
    _child = node_.toElement().namedItem("documentation");
    if(!_child.isNull())
        checkPOUdocumentation(_child, data_);

    return true;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool PLCopenXmlParser::UDT(quint32 _index, T_UDT *_udt)
{
    bool _result = false;
    quint32 _udt_counter = 0;
    QDomNode _udt_node = _m_user_data_type_node.firstChild();

    while(!_udt_node.isNull())
    {
        if(_udt_counter == _index)
        {       
            _result = parseUDT(_udt_node, _udt);
            break;
        }
        _udt_node = _udt_node.nextSibling();
        _udt_counter++;
    }
    return _result;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool PLCopenXmlParser::parseUDT(const QDomNode &_node, T_UDT * _udt)
{
    // node is dataType
    if(_node.nodeName() != "dataType")
        return false;

    for(int _i = 0;  _i < _node.toElement().attributes().length();  _i++)
        if(!_node.toElement().attributes().item(_i).toAttr().isNull())
        {
            if(_node.toElement().attributes().item(_i).toAttr().name() == "name")
            {
                _udt->_name = _node.toElement().attributes().item(_i).toAttr().value();
            }
        }
    QDomNode _baseType_node = _node.firstChild(); // baseType
    QDomNode _type_node = _baseType_node.firstChild();

    //------------------------------------------------------------
    if(!checkRedifinitionBaseType(_type_node, _udt))
    {
        //------------------------------------------------------------
        if(_type_node.toElement().tagName() == "struct")
        {
            T_UDT_VARIABLE _var = {};
            _udt->_type = DT_STRUCT;

            QDomNode _var_node = _type_node.firstChild(); // variable
            while(!_var_node.isNull())
            {
                for(int _i = 0;  _i < _var_node.toElement().attributes().length();  _i++)
                    if(!_var_node.toElement().attributes().item(_i).toAttr().isNull())
                    {
                        if(_var_node.toElement().attributes().item(_i).toAttr().name() == "name")
                            _var._name = _var_node.toElement().attributes().item(_i).toAttr().value();
                    }
                QDomNode _type_var_node = _var_node.firstChild().firstChild(); // type
                if(_type_var_node.toElement().tagName() == "derived")
                {
                    for(int _i = 0;  _i < _type_var_node.toElement().attributes().length();  _i++)
                        if(!_type_var_node.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_type_var_node.toElement().attributes().item(_i).toAttr().name() == "name")
                                _var._type = _type_var_node.toElement().attributes().item(_i).toAttr().value();
                        }
                }else{
                    _var._type = _type_var_node.toElement().tagName();
                }
                _udt->_struct.push_back(_var);
                _var_node = _var_node.nextSibling();
            }
        }else
            //------------------------------------------------------------
            if(_type_node.toElement().tagName() == "array")
            {
                _udt->_type = DT_ARRAY;
                QDomNode _dimension_node = _type_node.firstChild(); // dimension

                _udt->_array._range.clear();
                while(!_dimension_node.isNull())
                {
                    if(_dimension_node.toElement().tagName() == "dimension")
                    {
                        T_UDT_RANGE_ARRAY _range;
                        for(int _i = 0;  _i < _dimension_node.toElement().attributes().length();  _i++)
                            if(!_dimension_node.toElement().attributes().item(_i).toAttr().isNull())
                            {
                                if(_dimension_node.toElement().attributes().item(_i).toAttr().name() == "lower")
                                    _range._begin = _dimension_node.toElement().attributes().item(_i).toAttr().value().toInt();
                                if(_dimension_node.toElement().attributes().item(_i).toAttr().name() == "upper")
                                    _range._end = _dimension_node.toElement().attributes().item(_i).toAttr().value().toInt();
                            }
                        _udt->_array._range.push_back(_range);
                    }else
                        if(_dimension_node.toElement().tagName() == "baseType")
                        {
                            _udt->_array._type = _dimension_node.firstChild().toElement().tagName();
                        }
                    _dimension_node = _dimension_node.nextSibling();
                }

                _udt->_initial_value_present = false;
                _udt->_initial_value.clear();
                QDomNode initialValue_node = _baseType_node.nextSibling(); // initialValue
                QDomNode arrayValue_node = initialValue_node.firstChild(); // arrayValue
                QDomNode value_node = arrayValue_node.firstChild(); // value
                while(!value_node.isNull())
                {
                    QDomNode simpleValue_node = value_node.firstChild(); // simpleValue
                    QString _init_val;
                    for(int _i = 0;  _i < simpleValue_node.toElement().attributes().length();  _i++)
                        if(!simpleValue_node.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(simpleValue_node.toElement().attributes().item(_i).toAttr().name() == "value")
                                _init_val = simpleValue_node.toElement().attributes().item(_i).toAttr().value();
                        }
                    _udt->_initial_value_present = true;
                    _udt->_initial_value.push_back(_init_val);
                    value_node = value_node.nextSibling();
                }
            }else
                //------------------------------------------------------------
                if(_type_node.toElement().tagName() == "enum")
                {
                    QString _name;
                    _udt->_type = DT_ENUM;
                    QDomNode _values_node = _type_node.firstChild(); // values
                    QDomNode _value_node = _values_node.firstChild(); // value

                    _udt->_enum._value.clear();
                    while(!_value_node.isNull())
                    {
                        for(int _i = 0;  _i < _value_node.toElement().attributes().length();  _i++)
                            if(!_value_node.toElement().attributes().item(_i).toAttr().isNull())
                            {
                                if(_value_node.toElement().attributes().item(_i).toAttr().name() == "name")
                                    _name = _value_node.toElement().attributes().item(_i).toAttr().value();
                            }
                        _udt->_enum._value.push_back(_name);
                        _value_node = _value_node.nextSibling();
                    }

                    _udt->_initial_value_present = false;
                    _udt->_initial_value.clear();
                    QDomNode initialValue_node = _baseType_node.nextSibling(); // initialValue
                    QDomNode simpleValue_node = initialValue_node.firstChild(); // simpleValue
                    while(!simpleValue_node.isNull())
                    {
                        QString _init_val;
                        for(int _i = 0;  _i < simpleValue_node.toElement().attributes().length();  _i++)
                            if(!simpleValue_node.toElement().attributes().item(_i).toAttr().isNull())
                            {
                                if(simpleValue_node.toElement().attributes().item(_i).toAttr().name() == "value")
                                    _init_val = simpleValue_node.toElement().attributes().item(_i).toAttr().value();
                            }
                        _udt->_initial_value_present = true;
                        _udt->_initial_value.push_back(_init_val);
                        simpleValue_node = simpleValue_node.nextSibling();
                    }
                }else
                    //------------------------------------------------------------
                    if(_type_node.toElement().tagName() == "subrangeUnsigned")
                    {
                        _udt->_type = DT_SUBRANGE_UNSIGNED;
                        QDomNode _range_node = _type_node.firstChild(); // range
                        for(int _i = 0;  _i < _range_node.toElement().attributes().length();  _i++)
                            if(!_range_node.toElement().attributes().item(_i).toAttr().isNull())
                            {
                                if(_range_node.toElement().attributes().item(_i).toAttr().name() == "lower")
                                    _udt->_sign_unsign_range._begin = _range_node.toElement().attributes().item(_i).toAttr().value().toInt();
                                if(_range_node.toElement().attributes().item(_i).toAttr().name() == "upper")
                                    _udt->_sign_unsign_range._end = _range_node.toElement().attributes().item(_i).toAttr().value().toInt();
                            }
                        QDomNode _Type_node = _range_node.nextSibling(); // baseType
                        _udt->_sign_unsign_range._type = _Type_node.firstChild().toElement().tagName();

                        _udt->_initial_value_present = false;
                        _udt->_initial_value.clear();
                        QDomNode initialValue_node = _baseType_node.nextSibling(); // initialValue
                        QDomNode simpleValue_node = initialValue_node.firstChild(); // simpleValue
                        while(!simpleValue_node.isNull())
                        {
                            QString _init_val;
                            for(int _i = 0;  _i < simpleValue_node.toElement().attributes().length();  _i++)
                                if(!simpleValue_node.toElement().attributes().item(_i).toAttr().isNull())
                                {
                                    if(simpleValue_node.toElement().attributes().item(_i).toAttr().name() == "value")
                                        _init_val = simpleValue_node.toElement().attributes().item(_i).toAttr().value();
                                }
                            _udt->_initial_value_present = true;
                            _udt->_initial_value.push_back(_init_val);
                            simpleValue_node = simpleValue_node.nextSibling();
                        }
                    }else
                        //------------------------------------------------------------
                        if(_type_node.toElement().tagName() == "subrangeSigned")
                        {
                            _udt->_type = DT_SUBRANGE_SIGNED;
                            QDomNode _range_node = _type_node.firstChild(); // range
                            for(int _i = 0;  _i < _range_node.toElement().attributes().length();  _i++)
                                if(!_range_node.toElement().attributes().item(_i).toAttr().isNull())
                                {
                                    if(_range_node.toElement().attributes().item(_i).toAttr().name() == "lower")
                                        _udt->_sign_unsign_range._begin = _range_node.toElement().attributes().item(_i).toAttr().value().toInt();
                                    if(_range_node.toElement().attributes().item(_i).toAttr().name() == "upper")
                                        _udt->_sign_unsign_range._end = _range_node.toElement().attributes().item(_i).toAttr().value().toInt();
                                }
                            QDomNode _Type_node = _range_node.nextSibling(); // baseType
                            _udt->_sign_unsign_range._type = _Type_node.firstChild().toElement().tagName();

                            _udt->_initial_value_present = false;
                            _udt->_initial_value.clear();
                            QDomNode initialValue_node = _baseType_node.nextSibling(); // initialValue
                            QDomNode simpleValue_node = initialValue_node.firstChild(); // simpleValue
                            while(!simpleValue_node.isNull())
                            {
                                QString _init_val;
                                for(int _i = 0;  _i < simpleValue_node.toElement().attributes().length();  _i++)
                                    if(!simpleValue_node.toElement().attributes().item(_i).toAttr().isNull())
                                    {
                                        if(simpleValue_node.toElement().attributes().item(_i).toAttr().name() == "value")
                                            _init_val = simpleValue_node.toElement().attributes().item(_i).toAttr().value();
                                    }
                                _udt->_initial_value_present = true;
                                _udt->_initial_value.push_back(_init_val);
                                simpleValue_node = simpleValue_node.nextSibling();
                            }
                        }
        //------------------------------------------------------------
    }

    return true;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool PLCopenXmlParser::INSTANCES(T_INSTANCES *_inst)
{
    return parseINSTANCES(_m_instances_node, _inst);
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool PLCopenXmlParser::parseINSTANCES(const QDomNode &node_, T_INSTANCES * data_)
{
    // node is instances
    if(node_.nodeName() != "instances")
        return false;

    T_CONFIGURATION _conf;

    QDomNode _configurations_node =  node_.firstChild(); // configurations
    while(!_configurations_node.isNull())
    {
        QDomNode _configuration_node = _configurations_node.firstChild(); // configuration
        for(int _i = 0;  _i < _configuration_node.toElement().attributes().length();  _i++)
            if(!_configuration_node.toElement().attributes().item(_i).toAttr().isNull())
            {
                if(_configuration_node.toElement().attributes().item(_i).toAttr().name() == "name")
                    _conf._name = _configuration_node.toElement().attributes().item(_i).toAttr().value();
            }
        QDomNode _resource_node = _configuration_node.firstChild(); // resource
        while(!_resource_node.isNull())
        {
            for(int _i = 0;  _i < _resource_node.toElement().attributes().length();  _i++)
                if(!_resource_node.toElement().attributes().item(_i).toAttr().isNull())
                {
                    if(_resource_node.toElement().attributes().item(_i).toAttr().name() == "name")
                        _conf._resource._name = _resource_node.toElement().attributes().item(_i).toAttr().value();
                }
            QDomNode _task_node = _resource_node.firstChild(); // task
            while(!_task_node.isNull())
            {
                T_TASK _task;
                for(int _i = 0;  _i < _task_node.toElement().attributes().length();  _i++)
                    if(!_task_node.toElement().attributes().item(_i).toAttr().isNull())
                    {
                        if(_task_node.toElement().attributes().item(_i).toAttr().name() == "name")
                            _task._name = _task_node.toElement().attributes().item(_i).toAttr().value();
                        if(_task_node.toElement().attributes().item(_i).toAttr().name() == "interval")
                            _task._interval = _task_node.toElement().attributes().item(_i).toAttr().value();
                        if(_task_node.toElement().attributes().item(_i).toAttr().name() == "priority")
                            _task._priority = _task_node.toElement().attributes().item(_i).toAttr().value();
                    }
                QDomNode _pou_inst_node = _task_node.firstChild(); // pouInstance
                while(!_pou_inst_node.isNull())
                {
                    T_POU_INSTANCE  _pou_inst;
                    for(int _i = 0;  _i < _pou_inst_node.toElement().attributes().length();  _i++)
                        if(!_pou_inst_node.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_pou_inst_node.toElement().attributes().item(_i).toAttr().name() == "name")
                                _pou_inst._name = _pou_inst_node.toElement().attributes().item(_i).toAttr().value();
                            if(_pou_inst_node.toElement().attributes().item(_i).toAttr().name() == "typeName")
                                _pou_inst._typeName = _pou_inst_node.toElement().attributes().item(_i).toAttr().value();
                        }
                    _task._pouInstance.push_back(_pou_inst);
                    _pou_inst_node = _pou_inst_node.nextSibling();
                }
                _conf._resource._task.push_back(_task);
                _task_node = _task_node.nextSibling();
            }
            _resource_node = _resource_node.nextSibling();
        }
        data_->_configuration.push_back(_conf);
        _configurations_node = _configurations_node.nextSibling();
    }

    return true;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void PLCopenXmlParser::checkPOUattr(QDomNode _node, T_POU *_pou)
{
    for(int _i = 0;  _i < _node.toElement().attributes().length();  _i++)
        if(!_node.toElement().attributes().item(_i).toAttr().isNull())
        {
            if(_node.toElement().attributes().item(_i).toAttr().name() == "name")
            {
                _pou->_name = _node.toElement().attributes().item(_i).toAttr().value();
            }else
            if(_node.toElement().attributes().item(_i).toAttr().name() == "pouType")
            {
                if(_node.toElement().attributes().item(_i).toAttr().value() == "program")
                    _pou->_pouType = PT_PROGRAMM;
                if(_node.toElement().attributes().item(_i).toAttr().value() == "function")
                    _pou->_pouType = PT_FUNCTION;
                if(_node.toElement().attributes().item(_i).toAttr().value() == "functionBlock")
                    _pou->_pouType = PT_FUNCTION_BLOCK;
            }
        }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void PLCopenXmlParser::checkPOUinterface(QDomNode _node, T_POU *_pou)
{
    QDomNode _if_node = _node.firstChild();

    _pou->_interface._inputVars.clear();
    _pou->_interface._outputVars.clear();
    _pou->_interface._inoutVars.clear();
    _pou->_interface._localVars.clear();
    _pou->_interface._globalVars.clear();
    _pou->_interface._externalVars.clear();
    _pou->_interface._tempVars.clear();

    while(!_if_node.isNull())
    {
        if(_if_node.toElement().tagName() == "returnType")
        {
            _pou->_return_type = _if_node.firstChild().toElement().tagName();
        }else
        if(_if_node.toElement().tagName() == "inputVars")
        {
            checkPOUinterfaceInputVar(_if_node, _pou);
        }else
        if(_if_node.toElement().tagName() == "outputVars")
        {
            checkPOUinterfaceOutputVar(_if_node, _pou);
        }else
        if(_if_node.toElement().tagName() == "inOutVars")
        {
            checkPOUinterfaceInOutVar(_if_node, _pou);
        }else
        if(_if_node.toElement().tagName() == "localVars")
        {
            checkPOUinterfaceLocalVar(_if_node, _pou);
        }else
        if(_if_node.toElement().tagName() == "globalVars")
        {
            checkPOUinterfaceGlobalVar(_if_node, _pou);
        }else
        if(_if_node.toElement().tagName() == "externalVars")
        {
            checkPOUinterfaceExternalVar(_if_node, _pou);
        }else
        if(_if_node.toElement().tagName() == "tempVars")
        {
            checkPOUinterfaceTempVar(_if_node, _pou);
        }
        _if_node = _if_node.nextSibling();
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void PLCopenXmlParser::checkPOUinterfaceLocalVar(QDomNode _node, T_POU *_pou)
{
    T_VARIABLE _var;

    _var._address = "";
    _var._qualifier = VQ_NOQUALIFIER;

    for(int _i = 0;  _i < _node.toElement().attributes().length();  _i++)
        if(!_node.toElement().attributes().item(_i).toAttr().isNull())
        {
            if(_node.toElement().attributes().item(_i).toAttr().name() == "constant")
                _var._qualifier = VQ_CONSTANT;
            if(_node.toElement().attributes().item(_i).toAttr().name() == "retain")
                _var._qualifier = VQ_RETAIN;
            if(_node.toElement().attributes().item(_i).toAttr().name() == "nonretain")
                _var._qualifier = VQ_NONRETAIN;
        }

    QDomNode _var_node = _node.firstChild(); // variable
    while(!_var_node.isNull())
    {
        for(int _i = 0;  _i < _var_node.toElement().attributes().length();  _i++)
            if(!_var_node.toElement().attributes().item(_i).toAttr().isNull())
            {
                if(_var_node.toElement().attributes().item(_i).toAttr().name() == "name")
                    _var._name = _var_node.toElement().attributes().item(_i).toAttr().value();
                if(_var_node.toElement().attributes().item(_i).toAttr().name() == "address")
                    _var._address = _var_node.toElement().attributes().item(_i).toAttr().value();
            }

        QDomNode _type_node = _var_node.firstChild(); // type
        while(!_type_node.isNull())
        {
            if(_type_node.toElement().tagName() == "type")
            {
                QDomNode _type_node_val = _type_node.firstChild(); // derived
                if(_type_node_val.toElement().tagName() == "derived")
                {
                    _var._type = VT_DERIVED;
                    for(int _i = 0;  _i < _type_node_val.toElement().attributes().length();  _i++)
                        if (!_type_node_val.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_type_node_val.toElement().attributes().item(_i).toAttr().name() == "name")
                                _var._type_name = _type_node_val.toElement().attributes().item(_i).toAttr().value();
                        }
                }else{
                    _var._type = VT_BASE;
                    _var._type_name = _type_node_val.toElement().tagName();
                }
            }
            if(_type_node.toElement().tagName() == "initialValue")
            {
                QDomNode _simpl_val_node = _type_node.firstChild(); // simpleValue
                if(_simpl_val_node.toElement().tagName() == "simpleValue")
                {
                    for(int _i = 0;  _i < _simpl_val_node.toElement().attributes().length();  _i++)
                        if (!_simpl_val_node.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_simpl_val_node.toElement().attributes().item(_i).toAttr().name() == "value")
                                _var._initialValue._simpleValue = _simpl_val_node.toElement().attributes().item(_i).toAttr().value();
                        }
                }
            }
            if(_type_node.toElement().tagName() == "documentation")
            {
                QDomNode _doc_node = _type_node.firstChild();
                if(_doc_node.toElement().tagName() == "p")
                {
                    QDomNode _text_node = _doc_node.firstChild();
                    _var._documentation = _text_node.nodeValue();
                }
            }
            _type_node = _type_node.nextSibling();
        }
        _pou->_interface._localVars.push_back(_var);
        _var._initialValue._simpleValue = "";
        _var_node = _var_node.nextSibling();
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void PLCopenXmlParser::checkPOUinterfaceInOutVar(QDomNode _node, T_POU *_pou)
{
    T_VARIABLE _var;

    _var._address = "";
    _var._qualifier = VQ_NOQUALIFIER;

    for(int _i = 0;  _i < _node.toElement().attributes().length();  _i++)
        if(!_node.toElement().attributes().item(_i).toAttr().isNull())
        {
            if(_node.toElement().attributes().item(_i).toAttr().name() == "constant")
                _var._qualifier = VQ_CONSTANT;
            if(_node.toElement().attributes().item(_i).toAttr().name() == "retain")
                _var._qualifier = VQ_RETAIN;
            if(_node.toElement().attributes().item(_i).toAttr().name() == "nonretain")
                _var._qualifier = VQ_NONRETAIN;
        }

    QDomNode _var_node = _node.firstChild(); // variable
    while(!_var_node.isNull())
    {
        for(int _i = 0;  _i < _var_node.toElement().attributes().length();  _i++)
            if(!_var_node.toElement().attributes().item(_i).toAttr().isNull())
            {
                if(_var_node.toElement().attributes().item(_i).toAttr().name() == "name")
                    _var._name = _var_node.toElement().attributes().item(_i).toAttr().value();
                if(_var_node.toElement().attributes().item(_i).toAttr().name() == "address")
                    _var._address = _var_node.toElement().attributes().item(_i).toAttr().value();
            }

        QDomNode _type_node = _var_node.firstChild(); // type
        while(!_type_node.isNull())
        {
            if(_type_node.toElement().tagName() == "type")
            {
                QDomNode _type_node_val = _type_node.firstChild(); // derived
                if(_type_node_val.toElement().tagName() == "derived")
                {
                    _var._type = VT_DERIVED;
                    for(int _i = 0;  _i < _type_node_val.toElement().attributes().length();  _i++)
                        if (!_type_node_val.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_type_node_val.toElement().attributes().item(_i).toAttr().name() == "name")
                                _var._type_name = _type_node_val.toElement().attributes().item(_i).toAttr().value();
                        }
                }else{
                    _var._type = VT_BASE;
                    _var._type_name = _type_node_val.toElement().tagName();
                }
            }
            if(_type_node.toElement().tagName() == "initialValue")
            {
                QDomNode _simpl_val_node = _type_node.firstChild(); // simpleValue
                if(_simpl_val_node.toElement().tagName() == "simpleValue")
                {
                    for(int _i = 0;  _i < _simpl_val_node.toElement().attributes().length();  _i++)
                        if (!_simpl_val_node.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_simpl_val_node.toElement().attributes().item(_i).toAttr().name() == "value")
                                _var._initialValue._simpleValue = _simpl_val_node.toElement().attributes().item(_i).toAttr().value();
                        }
                }
            }
            if(_type_node.toElement().tagName() == "documentation")
            {
                QDomNode _doc_node = _type_node.firstChild();
                if(_doc_node.toElement().tagName() == "p")
                {
                    QDomNode _text_node = _doc_node.firstChild();
                    _var._documentation = _text_node.nodeValue();
                }
            }
            _type_node = _type_node.nextSibling();
        }
        _pou->_interface._inoutVars.push_back(_var);
        _var._initialValue._simpleValue = "";
        _var_node = _var_node.nextSibling();
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void PLCopenXmlParser::checkPOUinterfaceTempVar(QDomNode _node, T_POU *_pou)
{
    T_VARIABLE _var;

    _var._address = "";
    _var._qualifier = VQ_NOQUALIFIER;

    for(int _i = 0;  _i < _node.toElement().attributes().length();  _i++)
        if(!_node.toElement().attributes().item(_i).toAttr().isNull())
        {
            if(_node.toElement().attributes().item(_i).toAttr().name() == "constant")
                _var._qualifier = VQ_CONSTANT;
            if(_node.toElement().attributes().item(_i).toAttr().name() == "retain")
                _var._qualifier = VQ_RETAIN;
            if(_node.toElement().attributes().item(_i).toAttr().name() == "nonretain")
                _var._qualifier = VQ_NONRETAIN;
        }

    QDomNode _var_node = _node.firstChild(); // variable
    while(!_var_node.isNull())
    {
        for(int _i = 0;  _i < _var_node.toElement().attributes().length();  _i++)
            if(!_var_node.toElement().attributes().item(_i).toAttr().isNull())
            {
                if(_var_node.toElement().attributes().item(_i).toAttr().name() == "name")
                    _var._name = _var_node.toElement().attributes().item(_i).toAttr().value();
                if(_var_node.toElement().attributes().item(_i).toAttr().name() == "address")
                    _var._address = _var_node.toElement().attributes().item(_i).toAttr().value();
            }

        QDomNode _type_node = _var_node.firstChild(); // type
        while(!_type_node.isNull())
        {
            if(_type_node.toElement().tagName() == "type")
            {
                QDomNode _type_node_val = _type_node.firstChild(); // derived
                if(_type_node_val.toElement().tagName() == "derived")
                {
                    _var._type = VT_DERIVED;
                    for(int _i = 0;  _i < _type_node_val.toElement().attributes().length();  _i++)
                        if (!_type_node_val.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_type_node_val.toElement().attributes().item(_i).toAttr().name() == "name")
                                _var._type_name = _type_node_val.toElement().attributes().item(_i).toAttr().value();
                        }
                }else{
                    _var._type = VT_BASE;
                    _var._type_name = _type_node_val.toElement().tagName();
                }
            }
            if(_type_node.toElement().tagName() == "initialValue")
            {
                QDomNode _simpl_val_node = _type_node.firstChild(); // simpleValue
                if(_simpl_val_node.toElement().tagName() == "simpleValue")
                {
                    for(int _i = 0;  _i < _simpl_val_node.toElement().attributes().length();  _i++)
                        if (!_simpl_val_node.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_simpl_val_node.toElement().attributes().item(_i).toAttr().name() == "value")
                                _var._initialValue._simpleValue = _simpl_val_node.toElement().attributes().item(_i).toAttr().value();
                        }
                }
            }
            if(_type_node.toElement().tagName() == "documentation")
            {
                QDomNode _doc_node = _type_node.firstChild();
                if(_doc_node.toElement().tagName() == "p")
                {
                    QDomNode _text_node = _doc_node.firstChild();
                    _var._documentation = _text_node.nodeValue();
                }
            }
            _type_node = _type_node.nextSibling();
        }
        _pou->_interface._tempVars.push_back(_var);
        _var._initialValue._simpleValue = "";
        _var_node = _var_node.nextSibling();
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void PLCopenXmlParser::checkPOUinterfaceExternalVar(QDomNode _node, T_POU *_pou)
{
    T_VARIABLE _var;

    _var._address = "";
    _var._qualifier = VQ_NOQUALIFIER;

    for(int _i = 0;  _i < _node.toElement().attributes().length();  _i++)
        if(!_node.toElement().attributes().item(_i).toAttr().isNull())
        {
            if(_node.toElement().attributes().item(_i).toAttr().name() == "constant")
                _var._qualifier = VQ_CONSTANT;
            if(_node.toElement().attributes().item(_i).toAttr().name() == "retain")
                _var._qualifier = VQ_RETAIN;
            if(_node.toElement().attributes().item(_i).toAttr().name() == "nonretain")
                _var._qualifier = VQ_NONRETAIN;
        }

    QDomNode _var_node = _node.firstChild(); // variable
    while(!_var_node.isNull())
    {
        for(int _i = 0;  _i < _var_node.toElement().attributes().length();  _i++)
            if(!_var_node.toElement().attributes().item(_i).toAttr().isNull())
            {
                if(_var_node.toElement().attributes().item(_i).toAttr().name() == "name")
                    _var._name = _var_node.toElement().attributes().item(_i).toAttr().value();
                if(_var_node.toElement().attributes().item(_i).toAttr().name() == "address")
                    _var._address = _var_node.toElement().attributes().item(_i).toAttr().value();
            }

        QDomNode _type_node = _var_node.firstChild(); // type
        while(!_type_node.isNull())
        {
            if(_type_node.toElement().tagName() == "type")
            {
                QDomNode _type_node_val = _type_node.firstChild(); // derived
                if(_type_node_val.toElement().tagName() == "derived")
                {
                    _var._type = VT_DERIVED;
                    for(int _i = 0;  _i < _type_node_val.toElement().attributes().length();  _i++)
                        if (!_type_node_val.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_type_node_val.toElement().attributes().item(_i).toAttr().name() == "name")
                                _var._type_name = _type_node_val.toElement().attributes().item(_i).toAttr().value();
                        }
                }else{
                    _var._type = VT_BASE;
                    _var._type_name = _type_node_val.toElement().tagName();
                }
            }
            if(_type_node.toElement().tagName() == "initialValue")
            {
                QDomNode _simpl_val_node = _type_node.firstChild(); // simpleValue
                if(_simpl_val_node.toElement().tagName() == "simpleValue")
                {
                    for(int _i = 0;  _i < _simpl_val_node.toElement().attributes().length();  _i++)
                        if (!_simpl_val_node.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_simpl_val_node.toElement().attributes().item(_i).toAttr().name() == "value")
                                _var._initialValue._simpleValue = _simpl_val_node.toElement().attributes().item(_i).toAttr().value();
                        }
                }
            }
            if(_type_node.toElement().tagName() == "documentation")
            {
                QDomNode _doc_node = _type_node.firstChild();
                if(_doc_node.toElement().tagName() == "p")
                {
                    QDomNode _text_node = _doc_node.firstChild();
                    _var._documentation = _text_node.nodeValue();
                }
            }
            _type_node = _type_node.nextSibling();
        }
        _pou->_interface._externalVars.push_back(_var);
        _var._initialValue._simpleValue = "";
        _var_node = _var_node.nextSibling();
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void PLCopenXmlParser::checkPOUinterfaceGlobalVar(QDomNode _node, T_POU *_pou)
{
    T_VARIABLE _var;

    _var._address = "";
    _var._qualifier = VQ_NOQUALIFIER;

    for(int _i = 0;  _i < _node.toElement().attributes().length();  _i++)
        if(!_node.toElement().attributes().item(_i).toAttr().isNull())
        {
            if(_node.toElement().attributes().item(_i).toAttr().name() == "constant")
                _var._qualifier = VQ_CONSTANT;
            if(_node.toElement().attributes().item(_i).toAttr().name() == "retain")
                _var._qualifier = VQ_RETAIN;
            if(_node.toElement().attributes().item(_i).toAttr().name() == "nonretain")
                _var._qualifier = VQ_NONRETAIN;
        }

    QDomNode _var_node = _node.firstChild(); // variable
    while(!_var_node.isNull())
    {
        for(int _i = 0;  _i < _var_node.toElement().attributes().length();  _i++)
            if(!_var_node.toElement().attributes().item(_i).toAttr().isNull())
            {
                if(_var_node.toElement().attributes().item(_i).toAttr().name() == "name")
                    _var._name = _var_node.toElement().attributes().item(_i).toAttr().value();
                if(_var_node.toElement().attributes().item(_i).toAttr().name() == "address")
                    _var._address = _var_node.toElement().attributes().item(_i).toAttr().value();
            }

        QDomNode _type_node = _var_node.firstChild(); // type
        while(!_type_node.isNull())
        {
            if(_type_node.toElement().tagName() == "type")
            {
                QDomNode _type_node_val = _type_node.firstChild(); // derived
                if(_type_node_val.toElement().tagName() == "derived")
                {
                    _var._type = VT_DERIVED;
                    for(int _i = 0;  _i < _type_node_val.toElement().attributes().length();  _i++)
                        if (!_type_node_val.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_type_node_val.toElement().attributes().item(_i).toAttr().name() == "name")
                                _var._type_name = _type_node_val.toElement().attributes().item(_i).toAttr().value();
                        }
                }else{
                    _var._type = VT_BASE;
                    _var._type_name = _type_node_val.toElement().tagName();
                }
            }
            if(_type_node.toElement().tagName() == "initialValue")
            {
                QDomNode _simpl_val_node = _type_node.firstChild(); // simpleValue
                if(_simpl_val_node.toElement().tagName() == "simpleValue")
                {
                    for(int _i = 0;  _i < _simpl_val_node.toElement().attributes().length();  _i++)
                        if (!_simpl_val_node.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_simpl_val_node.toElement().attributes().item(_i).toAttr().name() == "value")
                                _var._initialValue._simpleValue = _simpl_val_node.toElement().attributes().item(_i).toAttr().value();
                        }
                }
            }
            if(_type_node.toElement().tagName() == "documentation")
            {
                QDomNode _doc_node = _type_node.firstChild();
                if(_doc_node.toElement().tagName() == "p")
                {
                    QDomNode _text_node = _doc_node.firstChild();
                    _var._documentation = _text_node.nodeValue();
                }
            }
            _type_node = _type_node.nextSibling();
        }
        _pou->_interface._globalVars.push_back(_var);
        _var._initialValue._simpleValue = "";
        _var_node = _var_node.nextSibling();
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void PLCopenXmlParser::checkPOUinterfaceInputVar(QDomNode _node, T_POU *_pou)
{
    T_VARIABLE _var;

    _var._address = "";
    _var._qualifier = VQ_NOQUALIFIER;

    for(int _i = 0;  _i < _node.toElement().attributes().length();  _i++)
        if(!_node.toElement().attributes().item(_i).toAttr().isNull())
        {
            if(_node.toElement().attributes().item(_i).toAttr().name() == "constant")
                _var._qualifier = VQ_CONSTANT;
            if(_node.toElement().attributes().item(_i).toAttr().name() == "retain")
                _var._qualifier = VQ_RETAIN;
            if(_node.toElement().attributes().item(_i).toAttr().name() == "nonretain")
                _var._qualifier = VQ_NONRETAIN;
        }

    QDomNode _var_node = _node.firstChild(); // variable
    while(!_var_node.isNull())
    {
        for(int _i = 0;  _i < _var_node.toElement().attributes().length();  _i++)
            if(!_var_node.toElement().attributes().item(_i).toAttr().isNull())
            {
                if(_var_node.toElement().attributes().item(_i).toAttr().name() == "name")
                    _var._name = _var_node.toElement().attributes().item(_i).toAttr().value();
                if(_var_node.toElement().attributes().item(_i).toAttr().name() == "address")
                    _var._address = _var_node.toElement().attributes().item(_i).toAttr().value();
            }

        QDomNode _type_node = _var_node.firstChild(); // type
        while(!_type_node.isNull())
        {
            if(_type_node.toElement().tagName() == "type")
            {
                QDomNode _type_node_val = _type_node.firstChild(); // derived
                if(_type_node_val.toElement().tagName() == "derived")
                {
                    _var._type = VT_DERIVED;
                    for(int _i = 0;  _i < _type_node_val.toElement().attributes().length();  _i++)
                        if (!_type_node_val.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_type_node_val.toElement().attributes().item(_i).toAttr().name() == "name")
                                _var._type_name = _type_node_val.toElement().attributes().item(_i).toAttr().value();
                        }
                }else{
                    _var._type = VT_BASE;
                    _var._type_name = _type_node_val.toElement().tagName();
                }
            }
            if(_type_node.toElement().tagName() == "initialValue")
            {
                QDomNode _simpl_val_node = _type_node.firstChild(); // simpleValue
                if(_simpl_val_node.toElement().tagName() == "simpleValue")
                {
                    for(int _i = 0;  _i < _simpl_val_node.toElement().attributes().length();  _i++)
                        if (!_simpl_val_node.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_simpl_val_node.toElement().attributes().item(_i).toAttr().name() == "value")
                                _var._initialValue._simpleValue = _simpl_val_node.toElement().attributes().item(_i).toAttr().value();
                        }
                }
            }
            if(_type_node.toElement().tagName() == "documentation")
            {
                QDomNode _doc_node = _type_node.firstChild();
                if(_doc_node.toElement().tagName() == "p")
                {
                    QDomNode _text_node = _doc_node.firstChild();
                    _var._documentation = _text_node.nodeValue();
                }
            }
            _type_node = _type_node.nextSibling();
        }
        _pou->_interface._inputVars.push_back(_var);
        _var._initialValue._simpleValue = "";
        _var_node = _var_node.nextSibling();
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void PLCopenXmlParser::checkPOUinterfaceOutputVar(QDomNode _node, T_POU *_pou)
{
    T_VARIABLE _var;

    _var._address = "";
    _var._qualifier = VQ_NOQUALIFIER;

    for(int _i = 0;  _i < _node.toElement().attributes().length();  _i++)
        if(!_node.toElement().attributes().item(_i).toAttr().isNull())
        {
            if(_node.toElement().attributes().item(_i).toAttr().name() == "constant")
                _var._qualifier = VQ_CONSTANT;
            if(_node.toElement().attributes().item(_i).toAttr().name() == "retain")
                _var._qualifier = VQ_RETAIN;
            if(_node.toElement().attributes().item(_i).toAttr().name() == "nonretain")
                _var._qualifier = VQ_NONRETAIN;
        }

    QDomNode _var_node = _node.firstChild(); // variable
    while(!_var_node.isNull())
    {
        for(int _i = 0;  _i < _var_node.toElement().attributes().length();  _i++)
            if(!_var_node.toElement().attributes().item(_i).toAttr().isNull())
            {
                if(_var_node.toElement().attributes().item(_i).toAttr().name() == "name")
                    _var._name = _var_node.toElement().attributes().item(_i).toAttr().value();
                if(_var_node.toElement().attributes().item(_i).toAttr().name() == "address")
                    _var._address = _var_node.toElement().attributes().item(_i).toAttr().value();
            }

        QDomNode _type_node = _var_node.firstChild(); // type
        while(!_type_node.isNull())
        {
            if(_type_node.toElement().tagName() == "type")
            {
                QDomNode _type_node_val = _type_node.firstChild(); // derived
                if(_type_node_val.toElement().tagName() == "derived")
                {
                    _var._type = VT_DERIVED;
                    for(int _i = 0;  _i < _type_node_val.toElement().attributes().length();  _i++)
                        if (!_type_node_val.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_type_node_val.toElement().attributes().item(_i).toAttr().name() == "name")
                                _var._type_name = _type_node_val.toElement().attributes().item(_i).toAttr().value();
                        }
                }else{
                    _var._type = VT_BASE;
                    _var._type_name = _type_node_val.toElement().tagName();
                }
            }
            if(_type_node.toElement().tagName() == "initialValue")
            {
                QDomNode _simpl_val_node = _type_node.firstChild(); // simpleValue
                if(_simpl_val_node.toElement().tagName() == "simpleValue")
                {
                    for(int _i = 0;  _i < _simpl_val_node.toElement().attributes().length();  _i++)
                        if (!_simpl_val_node.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_simpl_val_node.toElement().attributes().item(_i).toAttr().name() == "value")
                                _var._initialValue._simpleValue = _simpl_val_node.toElement().attributes().item(_i).toAttr().value();
                        }
                }
            }
            if(_type_node.toElement().tagName() == "documentation")
            {
                QDomNode _doc_node = _type_node.firstChild();
                if(_doc_node.toElement().tagName() == "p")
                {
                    QDomNode _text_node = _doc_node.firstChild();
                    _var._documentation = _text_node.nodeValue();
                }
            }
            _type_node = _type_node.nextSibling();
        }
        _pou->_interface._outputVars.push_back(_var);
        _var._initialValue._simpleValue = "";
        _var_node = _var_node.nextSibling();
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void PLCopenXmlParser::checkPOUbody(QDomNode _node, T_POU *_pou)
{
    QDomNode _body_node = _node.firstChild();

    while(!_body_node.isNull())
    {
        if(_body_node.toElement().tagName() == "FBD")   checkPOUbodyFBD(_body_node, _pou);
        if(_body_node.toElement().tagName() == "ST")    checkPOUbodyST(_body_node, _pou);
        if(_body_node.toElement().tagName() == "SFC")   checkPOUbodySFC(_body_node, _pou);
        if(_body_node.toElement().tagName() == "IL")    checkPOUbodyIL(_body_node, _pou);
        if(_body_node.toElement().tagName() == "LD")    checkPOUbodyLD(_body_node, _pou);
        _body_node = _body_node.nextSibling();
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void PLCopenXmlParser::checkPOUactions(QDomNode _node, T_POU *_pou)
{
    Q_UNUSED(_node)
    Q_UNUSED(_pou)
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void PLCopenXmlParser::checkPOUbodyFBD(QDomNode _node, T_POU *_pou)
{
    QDomNode _item_node = _node.firstChild();
    _pou->_body._type = PBT_FBD;

    while(!_item_node.isNull())
    {
        T_POU_FBD_ITEM _item;
        QString _name = _item_node.toElement().tagName();
        if(_name == "block")
        {
            checkPOUbodyFBD_block(_item_node, &_item);
            if(_item._instanceName != "")   _item._type = IT_FBD_BLOCK;
            else                            _item._type = IT_FBD_FUNCTION;
            _pou->_body._FBD._item.push_back(_item);
        }else
        if(_name == "inVariable")
        {
            checkPOUbodyFBD_in_var(_item_node, &_item);
            _item._type = IT_FBD_INPUT;
            _pou->_body._FBD._item.push_back(_item);
        }else
        if(_name == "outVariable")
        {
            checkPOUbodyFBD_out_var(_item_node, &_item);
            _item._type = IT_FBD_OUTPUT;
            _pou->_body._FBD._item.push_back(_item);
        }else
        if(_name == "inOutVariable")
        {
            checkPOUbodyFBD_in_out_var(_item_node, &_item);
            _item._type = IT_FBD_INPUT_OUTPUT;
            _pou->_body._FBD._item.push_back(_item);
        }else
        if(_name == "connector")
        {
            checkPOUbodyFBD_connector(_item_node, &_item);
            _item._type = IT_FBD_CONNECTOR;
            _pou->_body._FBD._item.push_back(_item);
        }else
        if(_name == "continuation")
        {
            checkPOUbodyFBD_continuation(_item_node, &_item);
            _item._type = IT_FBD_CONTINUATION;
            _pou->_body._FBD._item.push_back(_item);
        }else
        if(_name == "comment")
        {
            checkPOUbodyFBD_comment(_item_node, &_item);
            _item._type = IT_FBD_COMMENT;
            _pou->_body._FBD._item.push_back(_item);
        }
        _item_node = _item_node.nextSibling();
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void PLCopenXmlParser::checkPOUbodySFC(QDomNode _node, T_POU *_pou)
{
    QDomNode _item_node = _node.firstChild();
    _pou->_body._type = PBT_SFC;

    while(!_item_node.isNull())
    {
        T_POU_SFC_ITEM _item;
        QString _name = _item_node.toElement().tagName();
        if(_name == "step")
        {
            checkPOUbodySFC_step(_item_node, &_item);
            _item._type = IT_SFC_STEP;
            _pou->_body._SFC._item.push_back(_item);
        }else
        if(_name == "selectionDivergence")
        {
            checkPOUbodySFC_selection_divergence(_item_node, &_item);
            _item._type = IT_SFC_SELECTION_DIVERGENCE;
            _pou->_body._SFC._item.push_back(_item);
        }else
        if(_name == "selectionConvergence")
        {
            checkPOUbodySFC_selection_convergence(_item_node, &_item);
            _item._type = IT_SFC_SELECTION_CONVERGENCE;
            _pou->_body._SFC._item.push_back(_item);
        }else
        if(_name == "transition")
        {
            checkPOUbodySFC_transition(_item_node, &_item);
            _item._type = IT_SFC_TRANSITION;
            _pou->_body._SFC._item.push_back(_item);
        }else
        if(_name == "actionBlock")
        {
            checkPOUbodySFC_action_block(_item_node, &_item);
            _item._type = IT_SFC_ACTION_BLOCK;
            _pou->_body._SFC._item.push_back(_item);
        }else
        if(_name == "jumpStep")
        {
            checkPOUbodySFC_jump_step(_item_node, &_item);
            _item._type = IT_SFC_JUMP_STEP;
            _pou->_body._SFC._item.push_back(_item);
        }
        _item_node = _item_node.nextSibling();
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void PLCopenXmlParser::checkPOUbodySFC_step(QDomNode _node, T_POU_SFC_ITEM *_item)
{
    QDomNode _main_node = _node;

    for(int _i = 0;  _i < _main_node.toElement().attributes().length(); _i++)
        if(!_main_node.toElement().attributes().item(_i).toAttr().isNull())
        {
            if(_main_node.toElement().attributes().item(_i).toAttr().name() == "localId")
                _item->_localId = _main_node.toElement().attributes().item(_i).toAttr().value().toUInt();
            if(_main_node.toElement().attributes().item(_i).toAttr().name() == "name")
                _item->_name = _main_node.toElement().attributes().item(_i).toAttr().value();
            if(_main_node.toElement().attributes().item(_i).toAttr().name() == "initialStep")
                _item->_initialStep = _main_node.toElement().attributes().item(_i).toAttr().value();
            if(_main_node.toElement().attributes().item(_i).toAttr().name() == "width")
                _item->_width = _main_node.toElement().attributes().item(_i).toAttr().value().toUInt();
            if(_main_node.toElement().attributes().item(_i).toAttr().name() == "height")
                _item->_height = _main_node.toElement().attributes().item(_i).toAttr().value().toUInt();
            if(_main_node.toElement().attributes().item(_i).toAttr().name() == "executionOrderId")
                _item->_executionOrderId = _main_node.toElement().attributes().item(_i).toAttr().value().toUInt();
        }
    QDomNode _ch_node = _main_node.firstChild();
    while(!_ch_node.isNull())
    {
        QString _tag_name = _ch_node.toElement().tagName();
        if(_tag_name == "position")
        {
            for(int _i = 0;  _i < _ch_node.toElement().attributes().length();  _i++)
                if(!_ch_node.toElement().attributes().item(_i).toAttr().isNull())
                {
                    if(_ch_node.toElement().attributes().item(_i).toAttr().name() == "x")
                        _item->_position_x = _ch_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                    if(_ch_node.toElement().attributes().item(_i).toAttr().name() == "y")
                        _item->_position_y = _ch_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                }
        }
        if(_tag_name == "connectionPointIn")
        {
            T_SFC_CONNECTION_POINT_IN _in;

            QDomNode _in_node = _ch_node.firstChild();
            while(!_in_node.isNull())
            {
                QString _in_name = _in_node.toElement().tagName();
                if(_in_name == "relPosition")
                {
                    for(int _i = 0;  _i < _in_node.toElement().attributes().length(); _i++)
                        if(!_in_node.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_in_node.toElement().attributes().item(_i).toAttr().name() == "x")
                                _in._rel_position_x = _in_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                            if(_in_node.toElement().attributes().item(_i).toAttr().name() == "y")
                                _in._rel_position_y = _in_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                        }
                }
                if(_in_name == "connection")
                {
                    T_CONNECT_POSITION _pos;
                    for(int _i = 0;  _i < _in_node.toElement().attributes().length(); _i++)
                        if(!_in_node.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_in_node.toElement().attributes().item(_i).toAttr().name() == "refLocalId")
                                _in._connection._refLocalId = _in_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                        }

                    QDomNode _pos_node = _in_node.firstChild();
                    while(!_pos_node.isNull())
                    {
                        if(_pos_node.toElement().tagName() == "position")
                        {
                            for(int _i = 0;  _i < _pos_node.toElement().attributes().length(); _i++)
                                if(!_pos_node.toElement().attributes().item(_i).toAttr().isNull())
                                {
                                    if(_pos_node.toElement().attributes().item(_i).toAttr().name() == "x")
                                        _pos._x = _pos_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                                    if(_pos_node.toElement().attributes().item(_i).toAttr().name() == "y")
                                        _pos._y = _pos_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                                }
                            _in._connection._position.push_back(_pos);
                        }
                        _pos_node = _pos_node.nextSibling();
                    }
                }
                _in_node = _in_node.nextSibling();
            }
            _item->_point_in.push_back(_in);
        }
        if(_tag_name == "connectionPointOut")
        {
            T_SFC_CONNECTION_POINT_OUT _out;
            for(int _i = 0;  _i < _ch_node.toElement().attributes().length(); _i++)
                if(!_ch_node.toElement().attributes().item(_i).toAttr().isNull())
                {
                    if(_ch_node.toElement().attributes().item(_i).toAttr().name() == "formalParameter")
                        _out._formalParameter = _ch_node.toElement().attributes().item(_i).toAttr().value();
                }
            QDomNode _out_node = _ch_node.firstChild();
            while(!_out_node.isNull())
            {
                QString _out_name = _out_node.toElement().tagName();
                if(_out_name == "relPosition")
                {
                    for(int _i = 0;  _i < _out_node.toElement().attributes().length(); _i++)
                        if(!_out_node.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_out_node.toElement().attributes().item(_i).toAttr().name() == "x")
                                _out._rel_position_x = _out_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                            if(_out_node.toElement().attributes().item(_i).toAttr().name() == "y")
                                _out._rel_position_y = _out_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                        }
                }
                _out_node = _out_node.nextSibling();
            }
            _item->_point_out.push_back(_out);
        }
        if(_tag_name == "connectionPointOutAction")
        {
            T_SFC_CONNECTION_POINT_OUT _out;
            for(int _i = 0;  _i < _ch_node.toElement().attributes().length(); _i++)
                if(!_ch_node.toElement().attributes().item(_i).toAttr().isNull())
                {
                    if(_ch_node.toElement().attributes().item(_i).toAttr().name() == "formalParameter")
                        _out._formalParameter = _ch_node.toElement().attributes().item(_i).toAttr().value();
                }
            QDomNode _out_node = _ch_node.firstChild();
            while(!_out_node.isNull())
            {
                QString _out_name = _out_node.toElement().tagName();
                if(_out_name == "relPosition")
                {
                    for(int _i = 0;  _i < _out_node.toElement().attributes().length(); _i++)
                        if(!_out_node.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_out_node.toElement().attributes().item(_i).toAttr().name() == "x")
                                _out._rel_position_x = _out_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                            if(_out_node.toElement().attributes().item(_i).toAttr().name() == "y")
                                _out._rel_position_y = _out_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                        }
                }
                _out_node = _out_node.nextSibling();
            }
            _item->_point_out_action.push_back(_out);
        }
        _ch_node = _ch_node.nextSibling();
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void PLCopenXmlParser::checkPOUbodySFC_selection_divergence(QDomNode _node, T_POU_SFC_ITEM *_item)
{
    QDomNode _main_node = _node;

    for(int _i = 0;  _i < _main_node.toElement().attributes().length(); _i++)
        if(!_main_node.toElement().attributes().item(_i).toAttr().isNull())
        {
            if(_main_node.toElement().attributes().item(_i).toAttr().name() == "localId")
                _item->_localId = _main_node.toElement().attributes().item(_i).toAttr().value().toUInt();
            if(_main_node.toElement().attributes().item(_i).toAttr().name() == "width")
                _item->_width = _main_node.toElement().attributes().item(_i).toAttr().value().toUInt();
            if(_main_node.toElement().attributes().item(_i).toAttr().name() == "height")
                _item->_height = _main_node.toElement().attributes().item(_i).toAttr().value().toUInt();
        }
    QDomNode _ch_node = _main_node.firstChild();
    while(!_ch_node.isNull())
    {
        QString _tag_name = _ch_node.toElement().tagName();
        if(_tag_name == "position")
        {
            for(int _i = 0;  _i < _ch_node.toElement().attributes().length();  _i++)
                if(!_ch_node.toElement().attributes().item(_i).toAttr().isNull())
                {
                    if(_ch_node.toElement().attributes().item(_i).toAttr().name() == "x")
                        _item->_position_x = _ch_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                    if(_ch_node.toElement().attributes().item(_i).toAttr().name() == "y")
                        _item->_position_y = _ch_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                }
        }
        if(_tag_name == "connectionPointIn")
        {
            T_SFC_CONNECTION_POINT_IN _in;

            QDomNode _in_node = _ch_node.firstChild();
            while(!_in_node.isNull())
            {
                QString _in_name = _in_node.toElement().tagName();
                if(_in_name == "relPosition")
                {
                    for(int _i = 0;  _i < _in_node.toElement().attributes().length(); _i++)
                        if(!_in_node.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_in_node.toElement().attributes().item(_i).toAttr().name() == "x")
                                _in._rel_position_x = _in_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                            if(_in_node.toElement().attributes().item(_i).toAttr().name() == "y")
                                _in._rel_position_y = _in_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                        }
                }
                if(_in_name == "connection")
                {
                    T_CONNECT_POSITION _pos;
                    for(int _i = 0;  _i < _in_node.toElement().attributes().length(); _i++)
                        if(!_in_node.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_in_node.toElement().attributes().item(_i).toAttr().name() == "refLocalId")
                                _in._connection._refLocalId = _in_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                        }

                    QDomNode _pos_node = _in_node.firstChild();
                    while(!_pos_node.isNull())
                    {
                        if(_pos_node.toElement().tagName() == "position")
                        {
                            for(int _i = 0;  _i < _pos_node.toElement().attributes().length(); _i++)
                                if(!_pos_node.toElement().attributes().item(_i).toAttr().isNull())
                                {
                                    if(_pos_node.toElement().attributes().item(_i).toAttr().name() == "x")
                                        _pos._x = _pos_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                                    if(_pos_node.toElement().attributes().item(_i).toAttr().name() == "y")
                                        _pos._y = _pos_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                                }
                            _in._connection._position.push_back(_pos);
                        }
                        _pos_node = _pos_node.nextSibling();
                    }
                }
                _in_node = _in_node.nextSibling();
            }
            _item->_point_in.push_back(_in);
        }
        if(_tag_name == "connectionPointOut")
        {
            T_SFC_CONNECTION_POINT_OUT _out;
            for(int _i = 0;  _i < _ch_node.toElement().attributes().length(); _i++)
                if(!_ch_node.toElement().attributes().item(_i).toAttr().isNull())
                {
                    if(_ch_node.toElement().attributes().item(_i).toAttr().name() == "formalParameter")
                        _out._formalParameter = _ch_node.toElement().attributes().item(_i).toAttr().value();
                }
            QDomNode _out_node = _ch_node.firstChild();
            while(!_out_node.isNull())
            {
                QString _out_name = _out_node.toElement().tagName();
                if(_out_name == "relPosition")
                {
                    for(int _i = 0;  _i < _out_node.toElement().attributes().length(); _i++)
                        if(!_out_node.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_out_node.toElement().attributes().item(_i).toAttr().name() == "x")
                                _out._rel_position_x = _out_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                            if(_out_node.toElement().attributes().item(_i).toAttr().name() == "y")
                                _out._rel_position_y = _out_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                        }
                }
                _out_node = _out_node.nextSibling();
            }
            _item->_point_out.push_back(_out);
        }
        if(_tag_name == "connectionPointOutAction")
        {
            T_SFC_CONNECTION_POINT_OUT _out;
            for(int _i = 0;  _i < _ch_node.toElement().attributes().length(); _i++)
                if(!_ch_node.toElement().attributes().item(_i).toAttr().isNull())
                {
                    if(_ch_node.toElement().attributes().item(_i).toAttr().name() == "formalParameter")
                        _out._formalParameter = _ch_node.toElement().attributes().item(_i).toAttr().value();
                }
            QDomNode _out_node = _ch_node.firstChild();
            while(!_out_node.isNull())
            {
                QString _out_name = _out_node.toElement().tagName();
                if(_out_name == "relPosition")
                {
                    for(int _i = 0;  _i < _out_node.toElement().attributes().length(); _i++)
                        if(!_out_node.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_out_node.toElement().attributes().item(_i).toAttr().name() == "x")
                                _out._rel_position_x = _out_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                            if(_out_node.toElement().attributes().item(_i).toAttr().name() == "y")
                                _out._rel_position_y = _out_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                        }
                }
                _out_node = _out_node.nextSibling();
            }
            _item->_point_out_action.push_back(_out);
        }
        _ch_node = _ch_node.nextSibling();
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void PLCopenXmlParser::checkPOUbodySFC_selection_convergence(QDomNode _node, T_POU_SFC_ITEM *_item)
{
    QDomNode _main_node = _node;

    for(int _i = 0;  _i < _main_node.toElement().attributes().length(); _i++)
        if(!_main_node.toElement().attributes().item(_i).toAttr().isNull())
        {
            if(_main_node.toElement().attributes().item(_i).toAttr().name() == "localId")
                _item->_localId = _main_node.toElement().attributes().item(_i).toAttr().value().toUInt();
            if(_main_node.toElement().attributes().item(_i).toAttr().name() == "width")
                _item->_width = _main_node.toElement().attributes().item(_i).toAttr().value().toUInt();
            if(_main_node.toElement().attributes().item(_i).toAttr().name() == "height")
                _item->_height = _main_node.toElement().attributes().item(_i).toAttr().value().toUInt();
        }
    QDomNode _ch_node = _main_node.firstChild();
    while(!_ch_node.isNull())
    {
        QString _tag_name = _ch_node.toElement().tagName();
        if(_tag_name == "position")
        {
            for(int _i = 0;  _i < _ch_node.toElement().attributes().length();  _i++)
                if(!_ch_node.toElement().attributes().item(_i).toAttr().isNull())
                {
                    if(_ch_node.toElement().attributes().item(_i).toAttr().name() == "x")
                        _item->_position_x = _ch_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                    if(_ch_node.toElement().attributes().item(_i).toAttr().name() == "y")
                        _item->_position_y = _ch_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                }
        }
        if(_tag_name == "connectionPointIn")
        {
            T_SFC_CONNECTION_POINT_IN _in;

            QDomNode _in_node = _ch_node.firstChild();
            while(!_in_node.isNull())
            {
                QString _in_name = _in_node.toElement().tagName();
                if(_in_name == "relPosition")
                {
                    for(int _i = 0;  _i < _in_node.toElement().attributes().length(); _i++)
                        if(!_in_node.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_in_node.toElement().attributes().item(_i).toAttr().name() == "x")
                                _in._rel_position_x = _in_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                            if(_in_node.toElement().attributes().item(_i).toAttr().name() == "y")
                                _in._rel_position_y = _in_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                        }
                }
                if(_in_name == "connection")
                {
                    T_CONNECT_POSITION _pos;
                    for(int _i = 0;  _i < _in_node.toElement().attributes().length(); _i++)
                        if(!_in_node.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_in_node.toElement().attributes().item(_i).toAttr().name() == "refLocalId")
                                _in._connection._refLocalId = _in_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                        }

                    QDomNode _pos_node = _in_node.firstChild();
                    while(!_pos_node.isNull())
                    {
                        if(_pos_node.toElement().tagName() == "position")
                        {
                            for(int _i = 0;  _i < _pos_node.toElement().attributes().length(); _i++)
                                if(!_pos_node.toElement().attributes().item(_i).toAttr().isNull())
                                {
                                    if(_pos_node.toElement().attributes().item(_i).toAttr().name() == "x")
                                        _pos._x = _pos_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                                    if(_pos_node.toElement().attributes().item(_i).toAttr().name() == "y")
                                        _pos._y = _pos_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                                }
                            _in._connection._position.push_back(_pos);
                        }
                        _pos_node = _pos_node.nextSibling();
                    }
                }
                _in_node = _in_node.nextSibling();
            }
            _item->_point_in.push_back(_in);
        }
        if(_tag_name == "connectionPointOut")
        {
            T_SFC_CONNECTION_POINT_OUT _out;
            for(int _i = 0;  _i < _ch_node.toElement().attributes().length(); _i++)
                if(!_ch_node.toElement().attributes().item(_i).toAttr().isNull())
                {
                    if(_ch_node.toElement().attributes().item(_i).toAttr().name() == "formalParameter")
                        _out._formalParameter = _ch_node.toElement().attributes().item(_i).toAttr().value();
                }
            QDomNode _out_node = _ch_node.firstChild();
            while(!_out_node.isNull())
            {
                QString _out_name = _out_node.toElement().tagName();
                if(_out_name == "relPosition")
                {
                    for(int _i = 0;  _i < _out_node.toElement().attributes().length(); _i++)
                        if(!_out_node.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_out_node.toElement().attributes().item(_i).toAttr().name() == "x")
                                _out._rel_position_x = _out_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                            if(_out_node.toElement().attributes().item(_i).toAttr().name() == "y")
                                _out._rel_position_y = _out_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                        }
                }
                _out_node = _out_node.nextSibling();
            }
            _item->_point_out.push_back(_out);
        }
        if(_tag_name == "connectionPointOutAction")
        {
            T_SFC_CONNECTION_POINT_OUT _out;
            for(int _i = 0;  _i < _ch_node.toElement().attributes().length(); _i++)
                if(!_ch_node.toElement().attributes().item(_i).toAttr().isNull())
                {
                    if(_ch_node.toElement().attributes().item(_i).toAttr().name() == "formalParameter")
                        _out._formalParameter = _ch_node.toElement().attributes().item(_i).toAttr().value();
                }
            QDomNode _out_node = _ch_node.firstChild();
            while(!_out_node.isNull())
            {
                QString _out_name = _out_node.toElement().tagName();
                if(_out_name == "relPosition")
                {
                    for(int _i = 0;  _i < _out_node.toElement().attributes().length(); _i++)
                        if(!_out_node.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_out_node.toElement().attributes().item(_i).toAttr().name() == "x")
                                _out._rel_position_x = _out_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                            if(_out_node.toElement().attributes().item(_i).toAttr().name() == "y")
                                _out._rel_position_y = _out_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                        }
                }
                _out_node = _out_node.nextSibling();
            }
            _item->_point_out_action.push_back(_out);
        }
        _ch_node = _ch_node.nextSibling();
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void PLCopenXmlParser::checkPOUbodySFC_transition(QDomNode _node, T_POU_SFC_ITEM *_item)
{
    QDomNode _main_node = _node;

    for(int _i = 0;  _i < _main_node.toElement().attributes().length(); _i++)
        if(!_main_node.toElement().attributes().item(_i).toAttr().isNull())
        {
            if(_main_node.toElement().attributes().item(_i).toAttr().name() == "localId")
                _item->_localId = _main_node.toElement().attributes().item(_i).toAttr().value().toUInt();
            if(_main_node.toElement().attributes().item(_i).toAttr().name() == "width")
                _item->_width = _main_node.toElement().attributes().item(_i).toAttr().value().toUInt();
            if(_main_node.toElement().attributes().item(_i).toAttr().name() == "height")
                _item->_height = _main_node.toElement().attributes().item(_i).toAttr().value().toUInt();
            if(_main_node.toElement().attributes().item(_i).toAttr().name() == "executionOrderId")
                _item->_executionOrderId = _main_node.toElement().attributes().item(_i).toAttr().value().toUInt();
        }
    QDomNode _ch_node = _main_node.firstChild();
    while(!_ch_node.isNull())
    {
        QString _tag_name = _ch_node.toElement().tagName();
        if(_tag_name == "position")
        {
            for(int _i = 0;  _i < _ch_node.toElement().attributes().length();  _i++)
                if(!_ch_node.toElement().attributes().item(_i).toAttr().isNull())
                {
                    if(_ch_node.toElement().attributes().item(_i).toAttr().name() == "x")
                        _item->_position_x = _ch_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                    if(_ch_node.toElement().attributes().item(_i).toAttr().name() == "y")
                        _item->_position_y = _ch_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                }
        }
        if(_tag_name == "connectionPointIn")
        {
            T_SFC_CONNECTION_POINT_IN _in;

            QDomNode _in_node = _ch_node.firstChild();
            while(!_in_node.isNull())
            {
                QString _in_name = _in_node.toElement().tagName();
                if(_in_name == "relPosition")
                {
                    for(int _i = 0;  _i < _in_node.toElement().attributes().length(); _i++)
                        if(!_in_node.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_in_node.toElement().attributes().item(_i).toAttr().name() == "x")
                                _in._rel_position_x = _in_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                            if(_in_node.toElement().attributes().item(_i).toAttr().name() == "y")
                                _in._rel_position_y = _in_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                        }
                }
                if(_in_name == "connection")
                {
                    T_CONNECT_POSITION _pos;
                    for(int _i = 0;  _i < _in_node.toElement().attributes().length(); _i++)
                        if(!_in_node.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_in_node.toElement().attributes().item(_i).toAttr().name() == "refLocalId")
                                _in._connection._refLocalId = _in_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                        }

                    QDomNode _pos_node = _in_node.firstChild();
                    while(!_pos_node.isNull())
                    {
                        if(_pos_node.toElement().tagName() == "position")
                        {
                            for(int _i = 0;  _i < _pos_node.toElement().attributes().length(); _i++)
                                if(!_pos_node.toElement().attributes().item(_i).toAttr().isNull())
                                {
                                    if(_pos_node.toElement().attributes().item(_i).toAttr().name() == "x")
                                        _pos._x = _pos_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                                    if(_pos_node.toElement().attributes().item(_i).toAttr().name() == "y")
                                        _pos._y = _pos_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                                }
                            _in._connection._position.push_back(_pos);
                        }
                        _pos_node = _pos_node.nextSibling();
                    }
                }
                _in_node = _in_node.nextSibling();
            }
            _item->_point_in.push_back(_in);
        }
        if(_tag_name == "connectionPointOut")
        {
            T_SFC_CONNECTION_POINT_OUT _out;
            for(int _i = 0;  _i < _ch_node.toElement().attributes().length(); _i++)
                if(!_ch_node.toElement().attributes().item(_i).toAttr().isNull())
                {
                    if(_ch_node.toElement().attributes().item(_i).toAttr().name() == "formalParameter")
                        _out._formalParameter = _ch_node.toElement().attributes().item(_i).toAttr().value();
                }
            QDomNode _out_node = _ch_node.firstChild();
            while(!_out_node.isNull())
            {
                QString _out_name = _out_node.toElement().tagName();
                if(_out_name == "relPosition")
                {
                    for(int _i = 0;  _i < _out_node.toElement().attributes().length(); _i++)
                        if(!_out_node.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_out_node.toElement().attributes().item(_i).toAttr().name() == "x")
                                _out._rel_position_x = _out_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                            if(_out_node.toElement().attributes().item(_i).toAttr().name() == "y")
                                _out._rel_position_y = _out_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                        }
                }
                _out_node = _out_node.nextSibling();
            }
            _item->_point_out.push_back(_out);
        }
        if(_tag_name == "connectionPointOutAction")
        {
            T_SFC_CONNECTION_POINT_OUT _out;
            for(int _i = 0;  _i < _ch_node.toElement().attributes().length(); _i++)
                if(!_ch_node.toElement().attributes().item(_i).toAttr().isNull())
                {
                    if(_ch_node.toElement().attributes().item(_i).toAttr().name() == "formalParameter")
                        _out._formalParameter = _ch_node.toElement().attributes().item(_i).toAttr().value();
                }
            QDomNode _out_node = _ch_node.firstChild();
            while(!_out_node.isNull())
            {
                QString _out_name = _out_node.toElement().tagName();
                if(_out_name == "relPosition")
                {
                    for(int _i = 0;  _i < _out_node.toElement().attributes().length(); _i++)
                        if(!_out_node.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_out_node.toElement().attributes().item(_i).toAttr().name() == "x")
                                _out._rel_position_x = _out_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                            if(_out_node.toElement().attributes().item(_i).toAttr().name() == "y")
                                _out._rel_position_y = _out_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                        }
                }
                _out_node = _out_node.nextSibling();
            }
            _item->_point_out_action.push_back(_out);
        }
        if(_tag_name == "condition")
        {
            T_SFC_CONDITION _cond;

            QDomNode _cond_node = _ch_node.firstChild();
            while(!_cond_node.isNull())
            {
                QString _cond_name = _cond_node.toElement().tagName();
                if(_cond_name == "inline")
                {
                    for(int _i = 0;  _i < _cond_node.toElement().attributes().length(); _i++)
                        if(!_cond_node.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_cond_node.toElement().attributes().item(_i).toAttr().name() == "name")
                                _cond._name = _cond_node.toElement().attributes().item(_i).toAttr().value();
                        }
                    QDomNode _st_node = _cond_node.firstChild();
                    if(_st_node.toElement().tagName() == "ST")
                        _cond._ST_code = _st_node.firstChild().firstChild().nodeValue();

                    _item->_condition.push_back(_cond);
                }
                _cond_node = _cond_node.nextSibling();
            }
        }
        _ch_node = _ch_node.nextSibling();
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void PLCopenXmlParser::checkPOUbodySFC_action_block(QDomNode _node, T_POU_SFC_ITEM *_item)
{
    QDomNode _main_node = _node;

    for(int _i = 0;  _i < _main_node.toElement().attributes().length(); _i++)
        if(!_main_node.toElement().attributes().item(_i).toAttr().isNull())
        {
            if(_main_node.toElement().attributes().item(_i).toAttr().name() == "localId")
                _item->_localId = _main_node.toElement().attributes().item(_i).toAttr().value().toUInt();
            if(_main_node.toElement().attributes().item(_i).toAttr().name() == "width")
                _item->_width = _main_node.toElement().attributes().item(_i).toAttr().value().toUInt();
            if(_main_node.toElement().attributes().item(_i).toAttr().name() == "height")
                _item->_height = _main_node.toElement().attributes().item(_i).toAttr().value().toUInt();
            if(_main_node.toElement().attributes().item(_i).toAttr().name() == "executionOrderId")
                _item->_executionOrderId = _main_node.toElement().attributes().item(_i).toAttr().value().toUInt();
        }
    QDomNode _ch_node = _main_node.firstChild();
    while(!_ch_node.isNull())
    {
        QString _tag_name = _ch_node.toElement().tagName();
        if(_tag_name == "position")
        {
            for(int _i = 0;  _i < _ch_node.toElement().attributes().length();  _i++)
                if(!_ch_node.toElement().attributes().item(_i).toAttr().isNull())
                {
                    if(_ch_node.toElement().attributes().item(_i).toAttr().name() == "x")
                        _item->_position_x = _ch_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                    if(_ch_node.toElement().attributes().item(_i).toAttr().name() == "y")
                        _item->_position_y = _ch_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                }
        }
        if(_tag_name == "connectionPointIn")
        {
            T_SFC_CONNECTION_POINT_IN _in;

            QDomNode _in_node = _ch_node.firstChild();
            while(!_in_node.isNull())
            {
                QString _in_name = _in_node.toElement().tagName();
                if(_in_name == "relPosition")
                {
                    for(int _i = 0;  _i < _in_node.toElement().attributes().length(); _i++)
                        if(!_in_node.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_in_node.toElement().attributes().item(_i).toAttr().name() == "x")
                                _in._rel_position_x = _in_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                            if(_in_node.toElement().attributes().item(_i).toAttr().name() == "y")
                                _in._rel_position_y = _in_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                        }
                }
                if(_in_name == "connection")
                {
                    T_CONNECT_POSITION _pos;
                    for(int _i = 0;  _i < _in_node.toElement().attributes().length(); _i++)
                        if(!_in_node.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_in_node.toElement().attributes().item(_i).toAttr().name() == "refLocalId")
                                _in._connection._refLocalId = _in_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                        }

                    QDomNode _pos_node = _in_node.firstChild();
                    while(!_pos_node.isNull())
                    {
                        if(_pos_node.toElement().tagName() == "position")
                        {
                            for(int _i = 0;  _i < _pos_node.toElement().attributes().length(); _i++)
                                if(!_pos_node.toElement().attributes().item(_i).toAttr().isNull())
                                {
                                    if(_pos_node.toElement().attributes().item(_i).toAttr().name() == "x")
                                        _pos._x = _pos_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                                    if(_pos_node.toElement().attributes().item(_i).toAttr().name() == "y")
                                        _pos._y = _pos_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                                }
                            _in._connection._position.push_back(_pos);
                        }
                        _pos_node = _pos_node.nextSibling();
                    }
                }
                _in_node = _in_node.nextSibling();
            }
            _item->_point_in.push_back(_in);
        }
        if(_tag_name == "connectionPointOut")
        {
            T_SFC_CONNECTION_POINT_OUT _out;
            for(int _i = 0;  _i < _ch_node.toElement().attributes().length(); _i++)
                if(!_ch_node.toElement().attributes().item(_i).toAttr().isNull())
                {
                    if(_ch_node.toElement().attributes().item(_i).toAttr().name() == "formalParameter")
                        _out._formalParameter = _ch_node.toElement().attributes().item(_i).toAttr().value();
                }
            QDomNode _out_node = _ch_node.firstChild();
            while(!_out_node.isNull())
            {
                QString _out_name = _out_node.toElement().tagName();
                if(_out_name == "relPosition")
                {
                    for(int _i = 0;  _i < _out_node.toElement().attributes().length(); _i++)
                        if(!_out_node.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_out_node.toElement().attributes().item(_i).toAttr().name() == "x")
                                _out._rel_position_x = _out_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                            if(_out_node.toElement().attributes().item(_i).toAttr().name() == "y")
                                _out._rel_position_y = _out_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                        }
                }
                _out_node = _out_node.nextSibling();
            }
            _item->_point_out.push_back(_out);
        }
        if(_tag_name == "connectionPointOutAction")
        {
            T_SFC_CONNECTION_POINT_OUT _out;
            for(int _i = 0;  _i < _ch_node.toElement().attributes().length(); _i++)
                if(!_ch_node.toElement().attributes().item(_i).toAttr().isNull())
                {
                    if(_ch_node.toElement().attributes().item(_i).toAttr().name() == "formalParameter")
                        _out._formalParameter = _ch_node.toElement().attributes().item(_i).toAttr().value();
                }
            QDomNode _out_node = _ch_node.firstChild();
            while(!_out_node.isNull())
            {
                QString _out_name = _out_node.toElement().tagName();
                if(_out_name == "relPosition")
                {
                    for(int _i = 0;  _i < _out_node.toElement().attributes().length(); _i++)
                        if(!_out_node.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_out_node.toElement().attributes().item(_i).toAttr().name() == "x")
                                _out._rel_position_x = _out_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                            if(_out_node.toElement().attributes().item(_i).toAttr().name() == "y")
                                _out._rel_position_y = _out_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                        }
                }
                _out_node = _out_node.nextSibling();
            }
            _item->_point_out_action.push_back(_out);
        }
        if(_tag_name == "action")
        {
            T_SFC_ACTION _act;

            for(int _i = 0;  _i < _ch_node.toElement().attributes().length(); _i++)
                if(!_ch_node.toElement().attributes().item(_i).toAttr().isNull())
                {
                    if(_ch_node.toElement().attributes().item(_i).toAttr().name() == "localId")
                        _act._localId = _ch_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                    if(_ch_node.toElement().attributes().item(_i).toAttr().name() == "qualifier")
                        _act._qualifier = _ch_node.toElement().attributes().item(_i).toAttr().value();
                    if(_ch_node.toElement().attributes().item(_i).toAttr().name() == "indicator")
                        _act._indicator = _ch_node.toElement().attributes().item(_i).toAttr().value();
                }

            QDomNode _act_node = _ch_node.firstChild();
            while(!_act_node.isNull())
            {
                QString _cond_name = _act_node.toElement().tagName();
                if(_cond_name == "relPosition")
                {
                    QDomNode _pos_node = _act_node.firstChild();
                    for(int _i = 0;  _i < _pos_node.toElement().attributes().length(); _i++)
                        if(!_pos_node.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_pos_node.toElement().attributes().item(_i).toAttr().name() == "x")
                                _act._pel_position_x = _pos_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                            if(_pos_node.toElement().attributes().item(_i).toAttr().name() == "y")
                                _act._pel_position_y = _pos_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                        }
                }
                if(_cond_name == "inline")
                {
                    QDomNode _st_node = _act_node.firstChild();
                    if(_st_node.toElement().tagName() == "ST")
                        _act._ST_code = _st_node.firstChild().firstChild().nodeValue();
                }
                _act_node = _act_node.nextSibling();
            }
            _item->_action.push_back(_act);
        }
        _ch_node = _ch_node.nextSibling();
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void PLCopenXmlParser::checkPOUbodySFC_jump_step(QDomNode _node, T_POU_SFC_ITEM *_item)
{
    QDomNode _main_node = _node;

    for(int _i = 0;  _i < _main_node.toElement().attributes().length(); _i++)
        if(!_main_node.toElement().attributes().item(_i).toAttr().isNull())
        {
            if(_main_node.toElement().attributes().item(_i).toAttr().name() == "localId")
                _item->_localId = _main_node.toElement().attributes().item(_i).toAttr().value().toUInt();
            if(_main_node.toElement().attributes().item(_i).toAttr().name() == "targetName")
                _item->_targetName = _main_node.toElement().attributes().item(_i).toAttr().value();
            if(_main_node.toElement().attributes().item(_i).toAttr().name() == "width")
                _item->_width = _main_node.toElement().attributes().item(_i).toAttr().value().toUInt();
            if(_main_node.toElement().attributes().item(_i).toAttr().name() == "height")
                _item->_height = _main_node.toElement().attributes().item(_i).toAttr().value().toUInt();
        }
    QDomNode _ch_node = _main_node.firstChild();
    while(!_ch_node.isNull())
    {
        QString _tag_name = _ch_node.toElement().tagName();
        if(_tag_name == "position")
        {
            for(int _i = 0;  _i < _ch_node.toElement().attributes().length();  _i++)
                if(!_ch_node.toElement().attributes().item(_i).toAttr().isNull())
                {
                    if(_ch_node.toElement().attributes().item(_i).toAttr().name() == "x")
                        _item->_position_x = _ch_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                    if(_ch_node.toElement().attributes().item(_i).toAttr().name() == "y")
                        _item->_position_y = _ch_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                }
        }
        if(_tag_name == "connectionPointIn")
        {
            T_SFC_CONNECTION_POINT_IN _in;

            QDomNode _in_node = _ch_node.firstChild();
            while(!_in_node.isNull())
            {
                QString _in_name = _in_node.toElement().tagName();
                if(_in_name == "relPosition")
                {
                    for(int _i = 0;  _i < _in_node.toElement().attributes().length(); _i++)
                        if(!_in_node.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_in_node.toElement().attributes().item(_i).toAttr().name() == "x")
                                _in._rel_position_x = _in_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                            if(_in_node.toElement().attributes().item(_i).toAttr().name() == "y")
                                _in._rel_position_y = _in_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                        }
                }
                if(_in_name == "connection")
                {
                    T_CONNECT_POSITION _pos;
                    for(int _i = 0;  _i < _in_node.toElement().attributes().length(); _i++)
                        if(!_in_node.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_in_node.toElement().attributes().item(_i).toAttr().name() == "refLocalId")
                                _in._connection._refLocalId = _in_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                        }

                    QDomNode _pos_node = _in_node.firstChild();
                    while(!_pos_node.isNull())
                    {
                        if(_pos_node.toElement().tagName() == "position")
                        {
                            for(int _i = 0;  _i < _pos_node.toElement().attributes().length(); _i++)
                                if(!_pos_node.toElement().attributes().item(_i).toAttr().isNull())
                                {
                                    if(_pos_node.toElement().attributes().item(_i).toAttr().name() == "x")
                                        _pos._x = _pos_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                                    if(_pos_node.toElement().attributes().item(_i).toAttr().name() == "y")
                                        _pos._y = _pos_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                                }
                            _in._connection._position.push_back(_pos);
                        }
                        _pos_node = _pos_node.nextSibling();
                    }
                }
                _in_node = _in_node.nextSibling();
            }
            _item->_point_in.push_back(_in);
        }
        if(_tag_name == "connectionPointOut")
        {
            T_SFC_CONNECTION_POINT_OUT _out;
            for(int _i = 0;  _i < _ch_node.toElement().attributes().length(); _i++)
                if(!_ch_node.toElement().attributes().item(_i).toAttr().isNull())
                {
                    if(_ch_node.toElement().attributes().item(_i).toAttr().name() == "formalParameter")
                        _out._formalParameter = _ch_node.toElement().attributes().item(_i).toAttr().value();
                }
            QDomNode _out_node = _ch_node.firstChild();
            while(!_out_node.isNull())
            {
                QString _out_name = _out_node.toElement().tagName();
                if(_out_name == "relPosition")
                {
                    for(int _i = 0;  _i < _out_node.toElement().attributes().length(); _i++)
                        if(!_out_node.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_out_node.toElement().attributes().item(_i).toAttr().name() == "x")
                                _out._rel_position_x = _out_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                            if(_out_node.toElement().attributes().item(_i).toAttr().name() == "y")
                                _out._rel_position_y = _out_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                        }
                }
                _out_node = _out_node.nextSibling();
            }
            _item->_point_out.push_back(_out);
        }
        if(_tag_name == "connectionPointOutAction")
        {
            T_SFC_CONNECTION_POINT_OUT _out;
            for(int _i = 0;  _i < _ch_node.toElement().attributes().length(); _i++)
                if(!_ch_node.toElement().attributes().item(_i).toAttr().isNull())
                {
                    if(_ch_node.toElement().attributes().item(_i).toAttr().name() == "formalParameter")
                        _out._formalParameter = _ch_node.toElement().attributes().item(_i).toAttr().value();
                }
            QDomNode _out_node = _ch_node.firstChild();
            while(!_out_node.isNull())
            {
                QString _out_name = _out_node.toElement().tagName();
                if(_out_name == "relPosition")
                {
                    for(int _i = 0;  _i < _out_node.toElement().attributes().length(); _i++)
                        if(!_out_node.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_out_node.toElement().attributes().item(_i).toAttr().name() == "x")
                                _out._rel_position_x = _out_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                            if(_out_node.toElement().attributes().item(_i).toAttr().name() == "y")
                                _out._rel_position_y = _out_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                        }
                }
                _out_node = _out_node.nextSibling();
            }
            _item->_point_out_action.push_back(_out);
        }
        _ch_node = _ch_node.nextSibling();
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void PLCopenXmlParser::checkPOUbodyFBD_block(QDomNode _node, T_POU_FBD_ITEM *_item)
{
    T_POU_FBD_ITEM_VARIABLE _block_var;
    QDomNode _block_node = _node;

    _block_var._connection._refLocalId = -1;

    for(int _i = 0;  _i < _block_node.toElement().attributes().length(); _i++)
        if(!_block_node.toElement().attributes().item(_i).toAttr().isNull())
        {
            if(_block_node.toElement().attributes().item(_i).toAttr().name() == "localId")
                _item->_localId = _block_node.toElement().attributes().item(_i).toAttr().value().toUInt();
            if(_block_node.toElement().attributes().item(_i).toAttr().name() == "typeName")
                _item->_typeName = _block_node.toElement().attributes().item(_i).toAttr().value();
            if(_block_node.toElement().attributes().item(_i).toAttr().name() == "instanceName")
                _item->_instanceName = _block_node.toElement().attributes().item(_i).toAttr().value();
            if(_block_node.toElement().attributes().item(_i).toAttr().name() == "executionOrderId")
                _item->_executionOrderId = _block_node.toElement().attributes().item(_i).toAttr().value().toUInt();
            if(_block_node.toElement().attributes().item(_i).toAttr().name() == "width")
                _item->_width = _block_node.toElement().attributes().item(_i).toAttr().value().toUInt();
            if(_block_node.toElement().attributes().item(_i).toAttr().name() == "height")
                _item->_height = _block_node.toElement().attributes().item(_i).toAttr().value().toUInt();
        }

    QDomNode _ch_node = _block_node.firstChild();
    while(!_ch_node.isNull())
    {
        if(_ch_node.toElement().tagName() == "position")
        {
            for(int _i = 0;  _i < _ch_node.toElement().attributes().length();  _i++)
                if(!_ch_node.toElement().attributes().item(_i).toAttr().isNull())
                {
                    if(_ch_node.toElement().attributes().item(_i).toAttr().name() == "x")
                        _item->_pos_x = _ch_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                    if(_ch_node.toElement().attributes().item(_i).toAttr().name() == "y")
                        _item->_pos_y = _ch_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                }
        }
        if(_ch_node.toElement().tagName() == "inputVariables")
        {
            QDomNode _in_var_node = _ch_node.firstChild();
            while(!_in_var_node.isNull())
            {
                if(_in_var_node.toElement().tagName() == "variable")
                {
                    for(int _i = 0;  _i < _in_var_node.toElement().attributes().length();  _i++)
                        if(!_in_var_node.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_in_var_node.toElement().attributes().item(_i).toAttr().name() == "formalParameter")
                                _block_var._formalParameter = _in_var_node.toElement().attributes().item(_i).toAttr().value();
                            if(_in_var_node.toElement().attributes().item(_i).toAttr().name() == "edge")
                                _block_var._edge = _in_var_node.toElement().attributes().item(_i).toAttr().value();
                        }
                }
                QDomNode _point_in = _in_var_node.firstChild();
                while(!_point_in.isNull())
                {
                    if(_point_in.toElement().tagName() == "connectionPointIn")
                    {
                        QDomNode _param_node = _point_in.firstChild();
                        while(!_param_node.isNull())
                        {
                            if(_param_node.toElement().tagName() == "relPosition")
                            {
                                for(int _i = 0;  _i < _param_node.toElement().attributes().length();  _i++)
                                    if(!_param_node.toElement().attributes().item(_i).toAttr().isNull())
                                    {
                                        if(_param_node.toElement().attributes().item(_i).toAttr().name() == "x")
                                            _block_var._relPosition._x = _param_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                                        if(_param_node.toElement().attributes().item(_i).toAttr().name() == "y")
                                            _block_var._relPosition._y = _param_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                                    }
                            }
                            if(_param_node.toElement().tagName() == "connection")
                            {
                                for(int _i = 0;  _i < _param_node.toElement().attributes().length();  _i++)
                                    if(!_param_node.toElement().attributes().item(_i).toAttr().isNull())
                                    {
                                        if(_param_node.toElement().attributes().item(_i).toAttr().name() == "refLocalId")
                                            _block_var._connection._refLocalId = _param_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                                        if(_param_node.toElement().attributes().item(_i).toAttr().name() == "formalParameter")
                                            _block_var._connection._formalParameter = _param_node.toElement().attributes().item(_i).toAttr().value();
                                    }
                                T_CONNECT_POSITION _connect_pos;
                                QDomNode _connect_node = _param_node.firstChild();
                                while(!_connect_node.isNull())
                                {
                                    if(_connect_node.toElement().tagName() == "position")
                                    {
                                        for(int _i = 0;  _i < _connect_node.toElement().attributes().length();  _i++)
                                            if(!_connect_node.toElement().attributes().item(_i).toAttr().isNull())
                                            {
                                                if(_connect_node.toElement().attributes().item(_i).toAttr().name() == "x")
                                                    _connect_pos._x = _connect_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                                                if(_connect_node.toElement().attributes().item(_i).toAttr().name() == "y")
                                                    _connect_pos._y = _connect_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                                            }
                                        _block_var._connection._position.push_back(_connect_pos);
                                    }
                                    _connect_node = _connect_node.nextSibling();
                                }
                            }
                            _param_node = _param_node.nextSibling();
                        }
                    }
                    _point_in = _point_in.nextSibling();
                }
                _item->_inputVariables.push_back(_block_var);
                _block_var._formalParameter = "";
                _block_var._edge = "";
                _block_var._connection._refLocalId = -1;
                _block_var._connection._formalParameter = "";
                _block_var._connection._position.clear();
                _in_var_node = _in_var_node.nextSibling();
            }
        }
        if(_ch_node.toElement().tagName() == "inOutVariables")
        {
            QDomNode _in_var_node = _ch_node.firstChild();
            while(!_in_var_node.isNull())
            {
                if(_in_var_node.toElement().tagName() == "variable")
                {
                    for(int _i = 0;  _i < _in_var_node.toElement().attributes().length();  _i++)
                        if(!_in_var_node.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_in_var_node.toElement().attributes().item(_i).toAttr().name() == "formalParameter")
                                _block_var._formalParameter = _in_var_node.toElement().attributes().item(_i).toAttr().value();
                            if(_in_var_node.toElement().attributes().item(_i).toAttr().name() == "edge")
                                _block_var._edge = _in_var_node.toElement().attributes().item(_i).toAttr().value();
                        }
                }
                QDomNode _point_in = _in_var_node.firstChild();
                while(!_point_in.isNull())
                {
                    if(_point_in.toElement().tagName() == "connectionPointInOut")
                    {
                        QDomNode _param_node = _point_in.firstChild();
                        while(!_param_node.isNull())
                        {
                            if(_param_node.toElement().tagName() == "relPosition")
                            {
                                for(int _i = 0;  _i < _param_node.toElement().attributes().length();  _i++)
                                    if(!_param_node.toElement().attributes().item(_i).toAttr().isNull())
                                    {
                                        if(_param_node.toElement().attributes().item(_i).toAttr().name() == "x")
                                            _block_var._relPosition._x = _param_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                                        if(_param_node.toElement().attributes().item(_i).toAttr().name() == "y")
                                            _block_var._relPosition._y = _param_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                                    }
                            }
                            if(_param_node.toElement().tagName() == "connection")
                            {
                                for(int _i = 0;  _i < _param_node.toElement().attributes().length();  _i++)
                                    if(!_param_node.toElement().attributes().item(_i).toAttr().isNull())
                                    {
                                        if(_param_node.toElement().attributes().item(_i).toAttr().name() == "refLocalId")
                                            _block_var._connection._refLocalId = _param_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                                        if(_param_node.toElement().attributes().item(_i).toAttr().name() == "formalParameter")
                                            _block_var._connection._formalParameter = _param_node.toElement().attributes().item(_i).toAttr().value();
                                    }
                                T_CONNECT_POSITION _connect_pos;
                                QDomNode _connect_node = _param_node.firstChild();
                                while(!_connect_node.isNull())
                                {
                                    if(_connect_node.toElement().tagName() == "position")
                                    {
                                        for(int _i = 0;  _i < _connect_node.toElement().attributes().length();  _i++)
                                            if(!_connect_node.toElement().attributes().item(_i).toAttr().isNull())
                                            {
                                                if(_connect_node.toElement().attributes().item(_i).toAttr().name() == "x")
                                                    _connect_pos._x = _connect_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                                                if(_connect_node.toElement().attributes().item(_i).toAttr().name() == "y")
                                                    _connect_pos._y = _connect_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                                            }
                                        _block_var._connection._position.push_back(_connect_pos);
                                    }
                                    _connect_node = _connect_node.nextSibling();
                                }
                            }
                            _param_node = _param_node.nextSibling();
                        }
                    }
                    _point_in = _point_in.nextSibling();
                }
                _item->_inOutVariables.push_back(_block_var);
                _block_var._formalParameter = "";
                _block_var._edge = "";
                _block_var._connection._refLocalId = -1;
                _block_var._connection._formalParameter = "";
                _block_var._connection._position.clear();
                _in_var_node = _in_var_node.nextSibling();
            }
        }
        if(_ch_node.toElement().tagName() == "outputVariables")
        {
            QDomNode _in_var_node = _ch_node.firstChild();
            while(!_in_var_node.isNull())
            {
                if(_in_var_node.toElement().tagName() == "variable")
                {
                    for(int _i = 0;  _i < _in_var_node.toElement().attributes().length();  _i++)
                        if(!_in_var_node.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_in_var_node.toElement().attributes().item(_i).toAttr().name() == "formalParameter")
                                _block_var._formalParameter = _in_var_node.toElement().attributes().item(_i).toAttr().value();
                            if(_in_var_node.toElement().attributes().item(_i).toAttr().name() == "edge")
                                _block_var._edge = _in_var_node.toElement().attributes().item(_i).toAttr().value();
                        }
                }
                QDomNode _point_in = _in_var_node.firstChild();
                while(!_point_in.isNull())
                {
                    if(_point_in.toElement().tagName() == "connectionPointOut")
                    {
                        QDomNode _param_node = _point_in.firstChild();
                        while(!_param_node.isNull())
                        {
                            if(_param_node.toElement().tagName() == "relPosition")
                            {
                                for(int _i = 0;  _i < _param_node.toElement().attributes().length();  _i++)
                                    if(!_param_node.toElement().attributes().item(_i).toAttr().isNull())
                                    {
                                        if(_param_node.toElement().attributes().item(_i).toAttr().name() == "x")
                                            _block_var._relPosition._x = _param_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                                        if(_param_node.toElement().attributes().item(_i).toAttr().name() == "y")
                                            _block_var._relPosition._y = _param_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                                    }
                            }
                            if(_param_node.toElement().tagName() == "connection")
                            {
                                for(int _i = 0;  _i < _param_node.toElement().attributes().length();  _i++)
                                    if(!_param_node.toElement().attributes().item(_i).toAttr().isNull())
                                    {
                                        if(_param_node.toElement().attributes().item(_i).toAttr().name() == "refLocalId")
                                            _block_var._connection._refLocalId = _param_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                                        if(_param_node.toElement().attributes().item(_i).toAttr().name() == "formalParameter")
                                            _block_var._connection._formalParameter = _param_node.toElement().attributes().item(_i).toAttr().value();
                                    }
                                T_CONNECT_POSITION _connect_pos;
                                QDomNode _connect_node = _param_node.firstChild();
                                while(!_connect_node.isNull())
                                {
                                    if(_connect_node.toElement().tagName() == "position")
                                    {
                                        for(int _i = 0;  _i < _connect_node.toElement().attributes().length();  _i++)
                                            if(!_connect_node.toElement().attributes().item(_i).toAttr().isNull())
                                            {
                                                if(_connect_node.toElement().attributes().item(_i).toAttr().name() == "x")
                                                    _connect_pos._x = _connect_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                                                if(_connect_node.toElement().attributes().item(_i).toAttr().name() == "y")
                                                    _connect_pos._y = _connect_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                                            }
                                        _block_var._connection._position.push_back(_connect_pos);
                                    }
                                    _connect_node = _connect_node.nextSibling();
                                }
                            }
                            _param_node = _param_node.nextSibling();
                        }
                    }
                    _point_in = _point_in.nextSibling();
                }
                _item->_outputVariables.push_back(_block_var);
                _block_var._formalParameter = "";
                _block_var._edge = "";
                _block_var._connection._refLocalId = -1;
                _block_var._connection._formalParameter = "";
                _block_var._connection._position.clear();
                _in_var_node = _in_var_node.nextSibling();
            }
        }
        _ch_node = _ch_node.nextSibling();
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void PLCopenXmlParser::checkPOUbodyFBD_in_var(QDomNode _node, T_POU_FBD_ITEM *_item)
{
    QDomNode _var_node = _node;

    _item->_connection._refLocalId = -1;
    _item->_connection._formalParameter = "";

    for(int _i = 0;  _i < _var_node.toElement().attributes().length(); _i++)
        if(!_var_node.toElement().attributes().item(_i).toAttr().isNull())
        {
            if(_var_node.toElement().attributes().item(_i).toAttr().name() == "localId")
                _item->_localId = _var_node.toElement().attributes().item(_i).toAttr().value().toUInt();
            if(_var_node.toElement().attributes().item(_i).toAttr().name() == "negated")
                _item->_negated = _var_node.toElement().attributes().item(_i).toAttr().value().toInt();
            if(_var_node.toElement().attributes().item(_i).toAttr().name() == "executionOrderId")
                _item->_executionOrderId = _var_node.toElement().attributes().item(_i).toAttr().value().toUInt();
            if(_var_node.toElement().attributes().item(_i).toAttr().name() == "width")
                _item->_width = _var_node.toElement().attributes().item(_i).toAttr().value().toUInt();
            if(_var_node.toElement().attributes().item(_i).toAttr().name() == "height")
                _item->_height = _var_node.toElement().attributes().item(_i).toAttr().value().toUInt();
        }

    QDomNode _ch_node = _var_node.firstChild();
    while(!_ch_node.isNull())
    {
        if(_ch_node.toElement().tagName() == "position")
        {
            for(int _i = 0;  _i < _ch_node.toElement().attributes().length();  _i++)
                if(!_ch_node.toElement().attributes().item(_i).toAttr().isNull())
                {
                    if(_ch_node.toElement().attributes().item(_i).toAttr().name() == "x")
                        _item->_pos_x = _ch_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                    if(_ch_node.toElement().attributes().item(_i).toAttr().name() == "y")
                        _item->_pos_y = _ch_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                }
        }

        if(_ch_node.toElement().tagName() == "expression")
            _item->_expression = _ch_node.toElement().text();

        if(_ch_node.toElement().tagName() == "connectionPointOut")
        {
            QDomNode _param_node = _ch_node.firstChild();
            while(!_param_node.isNull())
            {
                if(_param_node.toElement().tagName() == "relPosition")
                {
                    for(int _i = 0;  _i < _param_node.toElement().attributes().length();  _i++)
                        if(!_param_node.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_param_node.toElement().attributes().item(_i).toAttr().name() == "x")
                                _item->_relPositionOut._x = _param_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                            if(_param_node.toElement().attributes().item(_i).toAttr().name() == "y")
                                _item->_relPositionOut._y = _param_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                        }
                }
                if(_param_node.toElement().tagName() == "connection")
                {
                    for(int _i = 0;  _i < _param_node.toElement().attributes().length();  _i++)
                        if(!_param_node.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_param_node.toElement().attributes().item(_i).toAttr().name() == "refLocalId")
                                _item->_connection._refLocalId = _param_node.toElement().attributes().item(_i).toAttr().value().toInt();
                            if(_param_node.toElement().attributes().item(_i).toAttr().name() == "formalParameter")
                                _item->_connection._formalParameter = _param_node.toElement().attributes().item(_i).toAttr().value();
                        }
                    QDomNode _position_node = _param_node.firstChild();
                    while(!_position_node.isNull())
                    {
                        T_CONNECT_POSITION _pos;

                        for(int _i = 0;  _i < _position_node.toElement().attributes().length();  _i++)
                            if(!_position_node.toElement().attributes().item(_i).toAttr().isNull())
                            {
                                if(_position_node.toElement().attributes().item(_i).toAttr().name() == "x")
                                    _pos._x = _position_node.toElement().attributes().item(_i).toAttr().value().toInt();
                                if(_position_node.toElement().attributes().item(_i).toAttr().name() == "y")
                                    _pos._y = _position_node.toElement().attributes().item(_i).toAttr().value().toInt();
                            }
                        _item->_connection._position.push_back(_pos);
                        _position_node = _position_node.nextSibling();
                    }
                }
                _param_node = _param_node.nextSibling();
            }
        }
        _ch_node = _ch_node.nextSibling();
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void PLCopenXmlParser::checkPOUbodyFBD_out_var(QDomNode _node, T_POU_FBD_ITEM *_item)
{
    QDomNode _var_node = _node;

    _item->_connection._refLocalId = -1;
    _item->_connection._formalParameter = "";

    for(int _i = 0;  _i < _var_node.toElement().attributes().length(); _i++)
        if(!_var_node.toElement().attributes().item(_i).toAttr().isNull())
        {
            if(_var_node.toElement().attributes().item(_i).toAttr().name() == "localId")
                _item->_localId = _var_node.toElement().attributes().item(_i).toAttr().value().toUInt();
            if(_var_node.toElement().attributes().item(_i).toAttr().name() == "negated")
                _item->_negated = _var_node.toElement().attributes().item(_i).toAttr().value().toInt();
            if(_var_node.toElement().attributes().item(_i).toAttr().name() == "executionOrderId")
                _item->_executionOrderId = _var_node.toElement().attributes().item(_i).toAttr().value().toUInt();
            if(_var_node.toElement().attributes().item(_i).toAttr().name() == "width")
                _item->_width = _var_node.toElement().attributes().item(_i).toAttr().value().toUInt();
            if(_var_node.toElement().attributes().item(_i).toAttr().name() == "height")
                _item->_height = _var_node.toElement().attributes().item(_i).toAttr().value().toUInt();
        }

    QDomNode _ch_node = _var_node.firstChild();
    while(!_ch_node.isNull())
    {
        if(_ch_node.toElement().tagName() == "position")
        {
            for(int _i = 0;  _i < _ch_node.toElement().attributes().length();  _i++)
                if(!_ch_node.toElement().attributes().item(_i).toAttr().isNull())
                {
                    if(_ch_node.toElement().attributes().item(_i).toAttr().name() == "x")
                        _item->_pos_x = _ch_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                    if(_ch_node.toElement().attributes().item(_i).toAttr().name() == "y")
                        _item->_pos_y = _ch_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                }
        }

        if(_ch_node.toElement().tagName() == "expression")
            _item->_expression = _ch_node.toElement().text();

        if(_ch_node.toElement().tagName() == "connectionPointIn")
        {
            QDomNode _param_node = _ch_node.firstChild();
            while(!_param_node.isNull())
            {
                if(_param_node.toElement().tagName() == "relPosition")
                {
                    for(int _i = 0;  _i < _param_node.toElement().attributes().length();  _i++)
                        if(!_param_node.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_param_node.toElement().attributes().item(_i).toAttr().name() == "x")
                                _item->_relPositionIn._x = _param_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                            if(_param_node.toElement().attributes().item(_i).toAttr().name() == "y")
                                _item->_relPositionIn._y = _param_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                        }
                }
                if(_param_node.toElement().tagName() == "connection")
                {
                    for(int _i = 0;  _i < _param_node.toElement().attributes().length();  _i++)
                        if(!_param_node.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_param_node.toElement().attributes().item(_i).toAttr().name() == "refLocalId")
                                _item->_connection._refLocalId = _param_node.toElement().attributes().item(_i).toAttr().value().toInt();
                            if(_param_node.toElement().attributes().item(_i).toAttr().name() == "formalParameter")
                                _item->_connection._formalParameter = _param_node.toElement().attributes().item(_i).toAttr().value();
                        }
                    QDomNode _position_node = _param_node.firstChild();
                    while(!_position_node.isNull())
                    {
                        T_CONNECT_POSITION _pos;

                        for(int _i = 0;  _i < _position_node.toElement().attributes().length();  _i++)
                            if(!_position_node.toElement().attributes().item(_i).toAttr().isNull())
                            {
                                if(_position_node.toElement().attributes().item(_i).toAttr().name() == "x")
                                    _pos._x = _position_node.toElement().attributes().item(_i).toAttr().value().toInt();
                                if(_position_node.toElement().attributes().item(_i).toAttr().name() == "y")
                                    _pos._y = _position_node.toElement().attributes().item(_i).toAttr().value().toInt();
                            }
                        _item->_connection._position.push_back(_pos);
                        _position_node = _position_node.nextSibling();
                    }
                }
                _param_node = _param_node.nextSibling();
            }
        }
        _ch_node = _ch_node.nextSibling();
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void PLCopenXmlParser::checkPOUbodyFBD_in_out_var(QDomNode _node, T_POU_FBD_ITEM *_item)
{
    QDomNode _var_node = _node;

    _item->_connection._refLocalId = -1;
    _item->_connection._formalParameter = "";

    for(int _i = 0;  _i < _var_node.toElement().attributes().length(); _i++)
        if(!_var_node.toElement().attributes().item(_i).toAttr().isNull())
        {
            if(_var_node.toElement().attributes().item(_i).toAttr().name() == "localId")
                _item->_localId = _var_node.toElement().attributes().item(_i).toAttr().value().toUInt();
            if(_var_node.toElement().attributes().item(_i).toAttr().name() == "negatedIn")
                _item->_negatedIn = _var_node.toElement().attributes().item(_i).toAttr().value().toInt();
            if(_var_node.toElement().attributes().item(_i).toAttr().name() == "negatedOut")
                _item->_negatedOut = _var_node.toElement().attributes().item(_i).toAttr().value().toInt();
            if(_var_node.toElement().attributes().item(_i).toAttr().name() == "executionOrderId")
                _item->_executionOrderId = _var_node.toElement().attributes().item(_i).toAttr().value().toUInt();
            if(_var_node.toElement().attributes().item(_i).toAttr().name() == "width")
                _item->_width = _var_node.toElement().attributes().item(_i).toAttr().value().toUInt();
            if(_var_node.toElement().attributes().item(_i).toAttr().name() == "height")
                _item->_height = _var_node.toElement().attributes().item(_i).toAttr().value().toUInt();
        }

    QDomNode _ch_node = _var_node.firstChild();
    while(!_ch_node.isNull())
    {
        if(_ch_node.toElement().tagName() == "position")
        {
            for(int _i = 0;  _i < _ch_node.toElement().attributes().length();  _i++)
                if(!_ch_node.toElement().attributes().item(_i).toAttr().isNull())
                {
                    if(_ch_node.toElement().attributes().item(_i).toAttr().name() == "x")
                        _item->_pos_x = _ch_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                    if(_ch_node.toElement().attributes().item(_i).toAttr().name() == "y")
                        _item->_pos_y = _ch_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                }
        }

        if(_ch_node.toElement().tagName() == "expression")
            _item->_expression = _ch_node.toElement().text();

        if(_ch_node.toElement().tagName() == "connectionPointIn")
        {
            QDomNode _param_node = _ch_node.firstChild();
            while(!_param_node.isNull())
            {
                if(_param_node.toElement().tagName() == "relPosition")
                {
                    for(int _i = 0;  _i < _param_node.toElement().attributes().length();  _i++)
                        if(!_param_node.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_param_node.toElement().attributes().item(_i).toAttr().name() == "x")
                                _item->_relPositionIn._x = _param_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                            if(_param_node.toElement().attributes().item(_i).toAttr().name() == "y")
                                _item->_relPositionIn._y = _param_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                        }
                }
                if(_param_node.toElement().tagName() == "connection")
                {
                    for(int _i = 0;  _i < _param_node.toElement().attributes().length();  _i++)
                        if(!_param_node.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_param_node.toElement().attributes().item(_i).toAttr().name() == "refLocalId")
                                _item->_connection._refLocalId = _param_node.toElement().attributes().item(_i).toAttr().value().toInt();
                            if(_param_node.toElement().attributes().item(_i).toAttr().name() == "formalParameter")
                                _item->_connection._formalParameter = _param_node.toElement().attributes().item(_i).toAttr().value();
                        }
                    QDomNode _position_node = _param_node.firstChild();
                    while(!_position_node.isNull())
                    {
                        T_CONNECT_POSITION _pos;

                        for(int _i = 0;  _i < _position_node.toElement().attributes().length();  _i++)
                            if(!_position_node.toElement().attributes().item(_i).toAttr().isNull())
                            {
                                if(_position_node.toElement().attributes().item(_i).toAttr().name() == "x")
                                    _pos._x = _position_node.toElement().attributes().item(_i).toAttr().value().toInt();
                                if(_position_node.toElement().attributes().item(_i).toAttr().name() == "y")
                                    _pos._y = _position_node.toElement().attributes().item(_i).toAttr().value().toInt();
                            }
                        _item->_connection._position.push_back(_pos);
                        _position_node = _position_node.nextSibling();
                    }
                }
                _param_node = _param_node.nextSibling();
            }
        }

        if(_ch_node.toElement().tagName() == "connectionPointOut")
        {
            QDomNode _param_node = _ch_node.firstChild();
            while(!_param_node.isNull())
            {
                if(_param_node.toElement().tagName() == "relPosition")
                {
                    for(int _i = 0;  _i < _param_node.toElement().attributes().length();  _i++)
                        if(!_param_node.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_param_node.toElement().attributes().item(_i).toAttr().name() == "x")
                                _item->_relPositionOut._x = _param_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                            if(_param_node.toElement().attributes().item(_i).toAttr().name() == "y")
                                _item->_relPositionOut._y = _param_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                        }
                }
                if(_param_node.toElement().tagName() == "connection")
                {
                    for(int _i = 0;  _i < _param_node.toElement().attributes().length();  _i++)
                        if(!_param_node.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_param_node.toElement().attributes().item(_i).toAttr().name() == "refLocalId")
                                _item->_connection._refLocalId = _param_node.toElement().attributes().item(_i).toAttr().value().toInt();
                            if(_param_node.toElement().attributes().item(_i).toAttr().name() == "formalParameter")
                                _item->_connection._formalParameter = _param_node.toElement().attributes().item(_i).toAttr().value();
                        }
                    QDomNode _position_node = _param_node.firstChild();
                    while(!_position_node.isNull())
                    {
                        T_CONNECT_POSITION _pos;

                        for(int _i = 0;  _i < _position_node.toElement().attributes().length();  _i++)
                            if(!_position_node.toElement().attributes().item(_i).toAttr().isNull())
                            {
                                if(_position_node.toElement().attributes().item(_i).toAttr().name() == "x")
                                    _pos._x = _position_node.toElement().attributes().item(_i).toAttr().value().toInt();
                                if(_position_node.toElement().attributes().item(_i).toAttr().name() == "y")
                                    _pos._y = _position_node.toElement().attributes().item(_i).toAttr().value().toInt();
                            }
                        _item->_connection._position.push_back(_pos);
                        _position_node = _position_node.nextSibling();
                    }
                }
                _param_node = _param_node.nextSibling();
            }
        }
        _ch_node = _ch_node.nextSibling();
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void PLCopenXmlParser::checkPOUbodyFBD_connector(QDomNode _node, T_POU_FBD_ITEM *_item)
{
    QDomNode _var_node = _node;

    for(int _i = 0;  _i < _var_node.toElement().attributes().length(); _i++)
        if(!_var_node.toElement().attributes().item(_i).toAttr().isNull())
        {
            if(_var_node.toElement().attributes().item(_i).toAttr().name() == "name")
                _item->_name = _var_node.toElement().attributes().item(_i).toAttr().value();
            if(_var_node.toElement().attributes().item(_i).toAttr().name() == "localId")
                _item->_localId = _var_node.toElement().attributes().item(_i).toAttr().value().toUInt();
            if(_var_node.toElement().attributes().item(_i).toAttr().name() == "width")
                _item->_width = _var_node.toElement().attributes().item(_i).toAttr().value().toUInt();
            if(_var_node.toElement().attributes().item(_i).toAttr().name() == "height")
                _item->_height = _var_node.toElement().attributes().item(_i).toAttr().value().toUInt();
        }

    QDomNode _ch_node = _var_node.firstChild();
    while(!_ch_node.isNull())
    {
        if(_ch_node.toElement().tagName() == "position")
        {
            for(int _i = 0;  _i < _ch_node.toElement().attributes().length();  _i++)
                if(!_ch_node.toElement().attributes().item(_i).toAttr().isNull())
                {
                    if(_ch_node.toElement().attributes().item(_i).toAttr().name() == "x")
                        _item->_pos_x = _ch_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                    if(_ch_node.toElement().attributes().item(_i).toAttr().name() == "y")
                        _item->_pos_y = _ch_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                }
        }

        if(_ch_node.toElement().tagName() == "connectionPointIn")
        {
            QDomNode _param_node = _ch_node.firstChild();
            while(!_param_node.isNull())
            {
                if(_param_node.toElement().tagName() == "relPosition")
                {
                    for(int _i = 0;  _i < _param_node.toElement().attributes().length();  _i++)
                        if(!_param_node.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_param_node.toElement().attributes().item(_i).toAttr().name() == "x")
                                _item->_relPositionIn._x = _param_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                            if(_param_node.toElement().attributes().item(_i).toAttr().name() == "y")
                                _item->_relPositionIn._y = _param_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                        }
                }
                if(_param_node.toElement().tagName() == "connection")
                {
                    for(int _i = 0;  _i < _param_node.toElement().attributes().length();  _i++)
                        if(!_param_node.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_param_node.toElement().attributes().item(_i).toAttr().name() == "refLocalId")
                                _item->_connection._refLocalId = _param_node.toElement().attributes().item(_i).toAttr().value().toInt();
                            if(_param_node.toElement().attributes().item(_i).toAttr().name() == "formalParameter")
                                _item->_connection._formalParameter = _param_node.toElement().attributes().item(_i).toAttr().value();
                        }
                    QDomNode _position_node = _param_node.firstChild();
                    while(!_position_node.isNull())
                    {
                        T_CONNECT_POSITION _pos;

                        for(int _i = 0;  _i < _position_node.toElement().attributes().length();  _i++)
                            if(!_position_node.toElement().attributes().item(_i).toAttr().isNull())
                            {
                                if(_position_node.toElement().attributes().item(_i).toAttr().name() == "x")
                                    _pos._x = _position_node.toElement().attributes().item(_i).toAttr().value().toInt();
                                if(_position_node.toElement().attributes().item(_i).toAttr().name() == "y")
                                    _pos._y = _position_node.toElement().attributes().item(_i).toAttr().value().toInt();
                            }
                        _item->_connection._position.push_back(_pos);
                        _position_node = _position_node.nextSibling();
                    }
                }
                _param_node = _param_node.nextSibling();
            }
        }
        _ch_node = _ch_node.nextSibling();
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void PLCopenXmlParser::checkPOUbodyFBD_continuation(QDomNode _node, T_POU_FBD_ITEM *_item)
{
    QDomNode _var_node = _node;

    for(int _i = 0;  _i < _var_node.toElement().attributes().length(); _i++)
        if(!_var_node.toElement().attributes().item(_i).toAttr().isNull())
        {
            if(_var_node.toElement().attributes().item(_i).toAttr().name() == "name")
                _item->_name = _var_node.toElement().attributes().item(_i).toAttr().value();
            if(_var_node.toElement().attributes().item(_i).toAttr().name() == "localId")
                _item->_localId = _var_node.toElement().attributes().item(_i).toAttr().value().toUInt();
            if(_var_node.toElement().attributes().item(_i).toAttr().name() == "width")
                _item->_width = _var_node.toElement().attributes().item(_i).toAttr().value().toUInt();
            if(_var_node.toElement().attributes().item(_i).toAttr().name() == "height")
                _item->_height = _var_node.toElement().attributes().item(_i).toAttr().value().toUInt();
        }

    QDomNode _ch_node = _var_node.firstChild();
    while(!_ch_node.isNull())
    {
        if(_ch_node.toElement().tagName() == "position")
        {
            for(int _i = 0;  _i < _ch_node.toElement().attributes().length();  _i++)
                if(!_ch_node.toElement().attributes().item(_i).toAttr().isNull())
                {
                    if(_ch_node.toElement().attributes().item(_i).toAttr().name() == "x")
                        _item->_pos_x = _ch_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                    if(_ch_node.toElement().attributes().item(_i).toAttr().name() == "y")
                        _item->_pos_y = _ch_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                }
        }

        if(_ch_node.toElement().tagName() == "connectionPointOut")
        {
            QDomNode _param_node = _ch_node.firstChild();
            while(!_param_node.isNull())
            {
                if(_param_node.toElement().tagName() == "relPosition")
                {
                    for(int _i = 0;  _i < _param_node.toElement().attributes().length();  _i++)
                        if(!_param_node.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_param_node.toElement().attributes().item(_i).toAttr().name() == "x")
                                _item->_relPositionOut._x = _param_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                            if(_param_node.toElement().attributes().item(_i).toAttr().name() == "y")
                                _item->_relPositionOut._y = _param_node.toElement().attributes().item(_i).toAttr().value().toUInt();
                        }
                }
                if(_param_node.toElement().tagName() == "connection")
                {
                    for(int _i = 0;  _i < _param_node.toElement().attributes().length();  _i++)
                        if(!_param_node.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_param_node.toElement().attributes().item(_i).toAttr().name() == "refLocalId")
                                _item->_connection._refLocalId = _param_node.toElement().attributes().item(_i).toAttr().value().toInt();
                            if(_param_node.toElement().attributes().item(_i).toAttr().name() == "formalParameter")
                                _item->_connection._formalParameter = _param_node.toElement().attributes().item(_i).toAttr().value();
                        }
                    QDomNode _position_node = _param_node.firstChild();
                    while(!_position_node.isNull())
                    {
                        T_CONNECT_POSITION _pos;

                        for(int _i = 0;  _i < _position_node.toElement().attributes().length();  _i++)
                            if(!_position_node.toElement().attributes().item(_i).toAttr().isNull())
                            {
                                if(_position_node.toElement().attributes().item(_i).toAttr().name() == "x")
                                    _pos._x = _position_node.toElement().attributes().item(_i).toAttr().value().toInt();
                                if(_position_node.toElement().attributes().item(_i).toAttr().name() == "y")
                                    _pos._y = _position_node.toElement().attributes().item(_i).toAttr().value().toInt();
                            }
                        _item->_connection._position.push_back(_pos);
                        _position_node = _position_node.nextSibling();
                    }
                }
                _param_node = _param_node.nextSibling();
            }
        }
        _ch_node = _ch_node.nextSibling();
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void PLCopenXmlParser::checkPOUbodyFBD_comment(QDomNode _node, T_POU_FBD_ITEM *_item)
{
    QDomNode _comment_node = _node;

    for(int _i = 0;  _i < _comment_node.toElement().attributes().length(); _i++)
        if(!_comment_node.toElement().attributes().item(_i).toAttr().isNull())
        {
            if(_comment_node.toElement().attributes().item(_i).toAttr().name() == "localId")
                _item->_localId = _comment_node.toElement().attributes().item(_i).toAttr().value().toUInt();
            if(_comment_node.toElement().attributes().item(_i).toAttr().name() == "width")
                _item->_width = _comment_node.toElement().attributes().item(_i).toAttr().value().toUInt();
            if(_comment_node.toElement().attributes().item(_i).toAttr().name() == "height")
                _item->_height = _comment_node.toElement().attributes().item(_i).toAttr().value().toUInt();
        }
    QDomNode _ch_node = _comment_node.firstChild();
    while(!_ch_node.isNull())
    {
        if(_ch_node.toElement().tagName() == "position")
        {
            for(int _i = 0;  _i < _ch_node.toElement().attributes().length();  _i++)
                if(!_ch_node.toElement().attributes().item(_i).toAttr().isNull())
                {
                    if(_ch_node.toElement().attributes().item(_i).toAttr().name() == "x")
                        _item->_pos_x = _ch_node.toElement().attributes().item(_i).toAttr().value().toInt();
                    if(_ch_node.toElement().attributes().item(_i).toAttr().name() == "y")
                        _item->_pos_y = _ch_node.toElement().attributes().item(_i).toAttr().value().toInt();
                }
        }else
        if(_ch_node.toElement().tagName() == "content")
        {
            QDomNode _content_node = _ch_node.firstChild();
            _item->_comment_content = _content_node.firstChild().nodeValue();
        }
        _ch_node = _ch_node.nextSibling();
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void PLCopenXmlParser::checkPOUbodyST(QDomNode _node, T_POU *_pou)
{
    QDomNode _ST_node = _node.firstChild();

    _pou->_body._type = PBT_ST;

    if(_ST_node.toElement().tagName() == "p")
    {
        QDomNode _code_node = _ST_node.firstChild();
        QStringList _list;
        _list << _code_node.nodeValue().split("\n");
        for(int _i = 0; _i < _list.size(); _i++)
            _pou->_body._ST._ST_code << _list.at(_i).trimmed();
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void PLCopenXmlParser::checkPOUdocumentation(QDomNode _node, T_POU *_pou)
{
    QDomNode _doc_node = _node.firstChild();
    if(_doc_node.toElement().tagName() == "p")
    {
        QDomNode _text_node = _doc_node.firstChild();
        _pou->_body._documentation = _text_node.nodeValue();
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void PLCopenXmlParser::checkPOUbodyIL(QDomNode _node, T_POU *_pou)
{
    QDomNode _IL_node = _node.firstChild();

    _pou->_body._type = PBT_IL;

    if(_IL_node.toElement().tagName() == "p")
    {
        QDomNode _code_node = _IL_node.firstChild();
        QStringList _list;
        _list << _code_node.nodeValue().split("\n");
        for(int _i = 0; _i < _list.size(); _i++)
            _pou->_body._IL._IL_code << _list.at(_i).trimmed();
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void PLCopenXmlParser::checkPOUbodyLD(QDomNode _node, T_POU *_pou)
{
    Q_UNUSED(_node)
    _pou->_body._type = PBT_LD;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool PLCopenXmlParser::instancesParser(QDomNode _node)
{
    _m_instances_node = _node;
    return true;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool PLCopenXmlParser::readXmlFile()
{
    bool _result = false;
    return _result;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool PLCopenXmlParser::writeXmlFile()
{
    bool _result = false;
    return _result;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
bool PLCopenXmlParser::checkRedifinitionBaseType(QDomNode _node, T_UDT *_udt)
{
    bool _result = false;
    QString _s = _node.toElement().tagName();
    for(int _i = 0; _i < ARRAY_SIZE(_base_type_name); _i++)
        if(_base_type_name[_i] == _node.toElement().tagName())
        {
            _udt->_type = DT_REDEFINE;
            _udt->_redefined_name = _node.toElement().tagName();
            _result = true;
            break;
        }
    return _result;
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
