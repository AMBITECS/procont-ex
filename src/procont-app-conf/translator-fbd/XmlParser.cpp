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
bool PLCopenXmlParser::parseUDT(const QDomNode &node_, T_UDT * data_)
{
    // node is dataType
    if(node_.nodeName() != "dataType")
        return false;

    for(int _i = 0;  _i < node_.toElement().attributes().length();  _i++)
        if(!node_.toElement().attributes().item(_i).toAttr().isNull())
        {
            if(node_.toElement().attributes().item(_i).toAttr().name() == "name")
            {
                data_->_name = node_.toElement().attributes().item(_i).toAttr().value();
            }
        }
    QDomNode _baseTypenode_ = node_.firstChild(); // baseType
    QDomNode _typenode_ = _baseTypenode_.firstChild();

    //------------------------------------------------------------
    if(!checkRedifinitionBaseType(_typenode_, data_))
    {
        //------------------------------------------------------------
        if(_typenode_.toElement().tagName() == "struct")
        {
            T_UDT_VARIABLE _var = {};
            data_->_type = DT_STRUCT;

            QDomNode _varnode_ = _typenode_.firstChild(); // variable
            while(!_varnode_.isNull())
            {
                for(int _i = 0;  _i < _varnode_.toElement().attributes().length();  _i++)
                    if(!_varnode_.toElement().attributes().item(_i).toAttr().isNull())
                    {
                        if(_varnode_.toElement().attributes().item(_i).toAttr().name() == "name")
                            _var._name = _varnode_.toElement().attributes().item(_i).toAttr().value();
                    }
                QDomNode _type_varnode_ = _varnode_.firstChild().firstChild(); // type
                if(_type_varnode_.toElement().tagName() == "derived")
                {
                    for(int _i = 0;  _i < _type_varnode_.toElement().attributes().length();  _i++)
                        if(!_type_varnode_.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(_type_varnode_.toElement().attributes().item(_i).toAttr().name() == "name")
                                _var._type = _type_varnode_.toElement().attributes().item(_i).toAttr().value();
                        }
                }else{
                    _var._type = _type_varnode_.toElement().tagName();
                }
                data_->_struct.push_back(_var);
                _varnode_ = _varnode_.nextSibling();
            }
        }else
            //------------------------------------------------------------
            if(_typenode_.toElement().tagName() == "array")
            {
                data_->_type = DT_ARRAY;
                QDomNode _dimensionnode_ = _typenode_.firstChild(); // dimension

                data_->_array._range.clear();
                while(!_dimensionnode_.isNull())
                {
                    if(_dimensionnode_.toElement().tagName() == "dimension")
                    {
                        T_UDT_RANGE_ARRAY _range;
                        for(int _i = 0;  _i < _dimensionnode_.toElement().attributes().length();  _i++)
                            if(!_dimensionnode_.toElement().attributes().item(_i).toAttr().isNull())
                            {
                                if(_dimensionnode_.toElement().attributes().item(_i).toAttr().name() == "lower")
                                    _range._begin = _dimensionnode_.toElement().attributes().item(_i).toAttr().value().toInt();
                                if(_dimensionnode_.toElement().attributes().item(_i).toAttr().name() == "upper")
                                    _range._end = _dimensionnode_.toElement().attributes().item(_i).toAttr().value().toInt();
                            }
                        data_->_array._range.push_back(_range);
                    }else
                        if(_dimensionnode_.toElement().tagName() == "baseType")
                        {
                            data_->_array._type = _dimensionnode_.firstChild().toElement().tagName();
                        }
                    _dimensionnode_ = _dimensionnode_.nextSibling();
                }

                data_->_initial_value_present = false;
                data_->_initial_value.clear();
                QDomNode initialValuenode_ = _baseTypenode_.nextSibling(); // initialValue
                QDomNode arrayValuenode_ = initialValuenode_.firstChild(); // arrayValue
                QDomNode valuenode_ = arrayValuenode_.firstChild(); // value
                while(!valuenode_.isNull())
                {
                    QDomNode simpleValuenode_ = valuenode_.firstChild(); // simpleValue
                    QString _init_val;
                    for(int _i = 0;  _i < simpleValuenode_.toElement().attributes().length();  _i++)
                        if(!simpleValuenode_.toElement().attributes().item(_i).toAttr().isNull())
                        {
                            if(simpleValuenode_.toElement().attributes().item(_i).toAttr().name() == "value")
                                _init_val = simpleValuenode_.toElement().attributes().item(_i).toAttr().value();
                        }
                    data_->_initial_value_present = true;
                    data_->_initial_value.push_back(_init_val);
                    valuenode_ = valuenode_.nextSibling();
                }
            }else
                //------------------------------------------------------------
                if(_typenode_.toElement().tagName() == "enum")
                {
                    QString _name;
                    data_->_type = DT_ENUM;
                    QDomNode _valuesnode_ = _typenode_.firstChild(); // values
                    QDomNode _valuenode_ = _valuesnode_.firstChild(); // value

                    data_->_enum._value.clear();
                    while(!_valuenode_.isNull())
                    {
                        for(int _i = 0;  _i < _valuenode_.toElement().attributes().length();  _i++)
                            if(!_valuenode_.toElement().attributes().item(_i).toAttr().isNull())
                            {
                                if(_valuenode_.toElement().attributes().item(_i).toAttr().name() == "name")
                                    _name = _valuenode_.toElement().attributes().item(_i).toAttr().value();
                            }
                        data_->_enum._value.push_back(_name);
                        _valuenode_ = _valuenode_.nextSibling();
                    }

                    data_->_initial_value_present = false;
                    data_->_initial_value.clear();
                    QDomNode initialValuenode_ = _baseTypenode_.nextSibling(); // initialValue
                    QDomNode simpleValuenode_ = initialValuenode_.firstChild(); // simpleValue
                    while(!simpleValuenode_.isNull())
                    {
                        QString _init_val;
                        for(int _i = 0;  _i < simpleValuenode_.toElement().attributes().length();  _i++)
                            if(!simpleValuenode_.toElement().attributes().item(_i).toAttr().isNull())
                            {
                                if(simpleValuenode_.toElement().attributes().item(_i).toAttr().name() == "value")
                                    _init_val = simpleValuenode_.toElement().attributes().item(_i).toAttr().value();
                            }
                        data_->_initial_value_present = true;
                        data_->_initial_value.push_back(_init_val);
                        simpleValuenode_ = simpleValuenode_.nextSibling();
                    }
                }else
                    //------------------------------------------------------------
                    if(_typenode_.toElement().tagName() == "subrangeUnsigned")
                    {
                        data_->_type = DT_SUBRANGE_UNSIGNED;
                        QDomNode _rangenode_ = _typenode_.firstChild(); // range
                        for(int _i = 0;  _i < _rangenode_.toElement().attributes().length();  _i++)
                            if(!_rangenode_.toElement().attributes().item(_i).toAttr().isNull())
                            {
                                if(_rangenode_.toElement().attributes().item(_i).toAttr().name() == "lower")
                                    data_->_sign_unsign_range._begin = _rangenode_.toElement().attributes().item(_i).toAttr().value().toInt();
                                if(_rangenode_.toElement().attributes().item(_i).toAttr().name() == "upper")
                                    data_->_sign_unsign_range._end = _rangenode_.toElement().attributes().item(_i).toAttr().value().toInt();
                            }
                        QDomNode _Typenode_ = _rangenode_.nextSibling(); // baseType
                        data_->_sign_unsign_range._type = _Typenode_.firstChild().toElement().tagName();

                        data_->_initial_value_present = false;
                        data_->_initial_value.clear();
                        QDomNode initialValuenode_ = _baseTypenode_.nextSibling(); // initialValue
                        QDomNode simpleValuenode_ = initialValuenode_.firstChild(); // simpleValue
                        while(!simpleValuenode_.isNull())
                        {
                            QString _init_val;
                            for(int _i = 0;  _i < simpleValuenode_.toElement().attributes().length();  _i++)
                                if(!simpleValuenode_.toElement().attributes().item(_i).toAttr().isNull())
                                {
                                    if(simpleValuenode_.toElement().attributes().item(_i).toAttr().name() == "value")
                                        _init_val = simpleValuenode_.toElement().attributes().item(_i).toAttr().value();
                                }
                            data_->_initial_value_present = true;
                            data_->_initial_value.push_back(_init_val);
                            simpleValuenode_ = simpleValuenode_.nextSibling();
                        }
                    }else
                        //------------------------------------------------------------
                        if(_typenode_.toElement().tagName() == "subrangeSigned")
                        {
                            data_->_type = DT_SUBRANGE_SIGNED;
                            QDomNode _rangenode_ = _typenode_.firstChild(); // range
                            for(int _i = 0;  _i < _rangenode_.toElement().attributes().length();  _i++)
                                if(!_rangenode_.toElement().attributes().item(_i).toAttr().isNull())
                                {
                                    if(_rangenode_.toElement().attributes().item(_i).toAttr().name() == "lower")
                                        data_->_sign_unsign_range._begin = _rangenode_.toElement().attributes().item(_i).toAttr().value().toInt();
                                    if(_rangenode_.toElement().attributes().item(_i).toAttr().name() == "upper")
                                        data_->_sign_unsign_range._end = _rangenode_.toElement().attributes().item(_i).toAttr().value().toInt();
                                }
                            QDomNode _Typenode_ = _rangenode_.nextSibling(); // baseType
                            data_->_sign_unsign_range._type = _Typenode_.firstChild().toElement().tagName();

                            data_->_initial_value_present = false;
                            data_->_initial_value.clear();
                            QDomNode initialValuenode_ = _baseTypenode_.nextSibling(); // initialValue
                            QDomNode simpleValuenode_ = initialValuenode_.firstChild(); // simpleValue
                            while(!simpleValuenode_.isNull())
                            {
                                QString _init_val;
                                for(int _i = 0;  _i < simpleValuenode_.toElement().attributes().length();  _i++)
                                    if(!simpleValuenode_.toElement().attributes().item(_i).toAttr().isNull())
                                    {
                                        if(simpleValuenode_.toElement().attributes().item(_i).toAttr().name() == "value")
                                            _init_val = simpleValuenode_.toElement().attributes().item(_i).toAttr().value();
                                    }
                                data_->_initial_value_present = true;
                                data_->_initial_value.push_back(_init_val);
                                simpleValuenode_ = simpleValuenode_.nextSibling();
                            }
                        }
        //------------------------------------------------------------
    }

    return true;
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
    // documentation
    _child = node_.toElement().namedItem("documentation");
    if(!_child.isNull())
        checkPOUdocumentation(_child, data_);

    return true;
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
                _pou->_pouType = _node.toElement().attributes().item(_i).toAttr().value();
            }
        }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void PLCopenXmlParser::checkPOUinterface(QDomNode _node, T_POU *_pou)
{
    QDomNode _if_node = _node.firstChild();

    while(!_if_node.isNull())
    {
        if(_if_node.toElement().tagName() == "localVars")
        {
            checkPOUinterfaceLocalVar(_if_node, _pou);
        }else
        if(_if_node.toElement().tagName() == "globalVars")
        {
            checkPOUinterfaceGlobalVar(_if_node, _pou);
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

    _pou->_interface._localVars.clear();
    QDomNode _var_node = _node.firstChild(); // variable

    while(!_var_node.isNull())
    {
        for(int _i = 0;  _i < _var_node.toElement().attributes().length();  _i++)
            if(!_var_node.toElement().attributes().item(_i).toAttr().isNull())
            {
                if(_var_node.toElement().attributes().item(_i).toAttr().name() == "name")
                {
                    _var._name = _var_node.toElement().attributes().item(_i).toAttr().value();
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
                                        {
                                            _var._type_name = _type_node_val.toElement().attributes().item(_i).toAttr().value();
                                        }
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
                                        {
                                            _var._initialValue._simpleValue = _simpl_val_node.toElement().attributes().item(_i).toAttr().value();
                                        }
                                    }
                            }
                        }
                        _type_node = _type_node.nextSibling();
                    }
                }
            }
        _pou->_interface._localVars.push_back(_var);
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

    _pou->_interface._localVars.clear();
    QDomNode _var_node = _node.firstChild();

    while(!_var_node.isNull())
    {
        for(int _i = 0;  _i < _var_node.toElement().attributes().length();  _i++)
            if(!_var_node.toElement().attributes().item(_i).toAttr().isNull())
            {
                if(_var_node.toElement().attributes().item(_i).toAttr().name() == "name")
                {
                    _var._name = _var_node.toElement().attributes().item(_i).toAttr().value();
                    QDomNode _type_node = _var_node.firstChild();
                    QDomNode _type_node_val = _type_node.firstChild();
                    if(_type_node_val.toElement().tagName() == "derived")
                    {
                        _var._type = VT_DERIVED;
                        for(int _i = 0;  _i < _type_node_val.toElement().attributes().length();  _i++)
                            if (!_type_node_val.toElement().attributes().item(_i).toAttr().isNull())
                            {
                                if(_type_node_val.toElement().attributes().item(_i).toAttr().name() == "name")
                                {
                                    _var._type_name = _type_node_val.toElement().attributes().item(_i).toAttr().value();
                                }
                            }
                    }else{
                        _var._type = VT_BASE;
                        _var._type_name = _type_node_val.toElement().tagName();
                    }
                }
            }
        _pou->_interface._localVars.push_back(_var);
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
        _body_node = _body_node.nextSibling();
    }
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void PLCopenXmlParser::checkPOUbodyFBD(QDomNode _node, T_POU *_pou)
{
    QDomNode _item_node = _node.firstChild();

    while(!_item_node.isNull())
    {
        T_POU_FBD_ITEM _item;
        QString _name = _item_node.toElement().tagName();
        if(_name == "block")
        {
            checkPOUbodyFBD_block(_item_node, &_item);
            if(_item._instanceName != "")   _item._type = IT_BLOCK;
            else                            _item._type = IT_FUNCTION;
            _pou->_body._FBD._item.push_back(_item);
        }else
        if(_name == "inVariable")
        {
            checkPOUbodyFBD_in_var(_item_node, &_item);
            _item._type = IT_INPUT;
            _pou->_body._FBD._item.push_back(_item);
        }else
        if(_name == "outVariable")
        {
            checkPOUbodyFBD_out_var(_item_node, &_item);
            _item._type = IT_OUTPUT;
            _pou->_body._FBD._item.push_back(_item);
        }else
        if(_name == "inOutVariable")
        {
            checkPOUbodyFBD_in_out_var(_item_node, &_item);
            _item._type = IT_INPUT_OUTPUT;
            _pou->_body._FBD._item.push_back(_item);
        }else
        if(_name == "connector")
        {
            checkPOUbodyFBD_connector(_item_node, &_item);
            _item._type = IT_CONNECTOR;
            _pou->_body._FBD._item.push_back(_item);
        }else
        if(_name == "continuation")
        {
            checkPOUbodyFBD_continuation(_item_node, &_item);
            _item._type = IT_CONTINUATION;
            _pou->_body._FBD._item.push_back(_item);
        }else
        if(_name == "comment")
        {
            checkPOUbodyFBD_comment(_item_node, &_item);
            _item._type = IT_COMMENT;
            _pou->_body._FBD._item.push_back(_item);
        }
        _item_node = _item_node.nextSibling();
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
    if(_ST_node.toElement().tagName() == "p")
    {
        QDomNode _code_node = _ST_node.firstChild();
        _pou->_body._ST._code_string = _code_node.nodeValue();
    }
//    <ST>
//      <xhtml:p><![CDATA[Q1 := S1 OR ((NOT R) AND Q1);]]></xhtml:p>
//    </ST>
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
//    <documentation>
//      <xhtml:p><![CDATA[The SR bistable is a latch where the Set dominates.]]></xhtml:p>
//    </documentation>
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
void PLCopenXmlParser::checkPOUbodySFC(QDomNode _node, T_POU *_pou)
{
    Q_UNUSED(_node)
    Q_UNUSED(_pou)
}
//-----------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------
