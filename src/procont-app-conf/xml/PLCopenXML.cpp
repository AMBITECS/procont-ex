#include "PLCopenXML.h"

bool PLCopenXMLUtils::is_type_derived(const QDomNode &node_)
{
    return node_.firstChild().nodeName() == "derived";
}

QString PLCopenXMLUtils::type_derived_name(const QDomNode &node_)
{
    return node_.firstChild().toElement().attribute("name");
}

PLCopenXMLVariableType::PLCopenXMLVariableType(const QDomNode &node_) :
    _m_node(node_)
{
}

PLCopenXMLVariableType_elementary::PLCopenXMLVariableType_elementary(const QDomNode &node_) :
    PLCopenXMLVariableType(node_)
{
}

QString PLCopenXMLVariableType_elementary::name() const
{
    return _m_node.firstChild().nodeName();
}

PLCopenXMLVariableType_derived::PLCopenXMLVariableType_derived(const QDomNode &node_) :
    PLCopenXMLVariableType(node_)
{
}

QString PLCopenXMLVariableType_derived::name() const
{
    return _m_node.firstChild().toElement().attribute("name");
}

PLCopenXMLVariableType * PLCopenXMLVariableCreator_elementary::create(const QDomNode &node_)
{
    return new PLCopenXMLVariableType_elementary(node_);
}

PLCopenXMLVariableType * PLCopenXMLVariableCreator_derived::create(const QDomNode &node_)
{
    return new PLCopenXMLVariableType_derived(node_);
}

std::shared_ptr<PLCopenXMLVariableBuilder> PLCopenXMLVariableBuilder::_m_instance = nullptr;

PLCopenXMLVariableBuilder::PLCopenXMLVariableBuilder()
{
    _m_creators.insert(PLCopenXMLVariableType::eVT_Elementary, std::shared_ptr<PLCopenXMLVariableCreator>(new PLCopenXMLVariableCreator_elementary));
    _m_creators.insert(PLCopenXMLVariableType::eVT_Derived, std::shared_ptr<PLCopenXMLVariableCreator>(new PLCopenXMLVariableCreator_derived));
}

PLCopenXMLVariableBuilder * PLCopenXMLVariableBuilder::instance()
{
    if(_m_instance == nullptr)
        _m_instance = std::shared_ptr<PLCopenXMLVariableBuilder>(new PLCopenXMLVariableBuilder);

    return _m_instance.get();
}

PLCopenXMLVariableType::eVariableType PLCopenXMLVariableBuilder::get_type(const QDomNode &node_)
{
    if(PLCopenXMLUtils::is_type_derived(node_))
        return PLCopenXMLVariableType::eVT_Derived;

    return PLCopenXMLVariableType::eVT_Elementary;
}

std::shared_ptr<PLCopenXMLVariableType> PLCopenXMLVariableBuilder::build(const QDomNode &node_)
{
    if(_m_creators.contains(get_type(node_)))
        return std::shared_ptr<PLCopenXMLVariableType>(_m_creators.value(get_type(node_))->create(node_));

    return nullptr;
}
