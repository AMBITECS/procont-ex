#include "Translator.h"

#include <QDebug>

// ----------------------------------------------------------------------------
// *** Translator_POU_ST ***

#include "editor-st/XmlParser.h"

Translator_POU_ST::Translator_POU_ST(const QDomNode &node_) : ITranslator_POU(node_)
{
}

QString Translator_POU_ST::translate() const
{
    QString _text = {};
    _text += XmlParser::getPouVarsText(_m_node);
    _text += XmlParser::getPouBodyText(_m_node);

    return _text;
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** Translator_POU_FBD ***

#include "translator-fbd/FbdTranslator.h"

Translator_POU_FBD::Translator_POU_FBD(const QDomNode &node_) : ITranslator_POU(node_)
{
}

QString Translator_POU_FBD::translate() const
{
    FbdTranslator translator;
    return translator.getSTCode_pou(_m_node);
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** Translator_POU_creator_ST ***

ITranslator_POU * Translator_POU_creator_ST::create(const QDomNode &node_) const
{
    return new Translator_POU_ST(node_);
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** Translator_POU_creator_FBD ***

ITranslator_POU * Translator_POU_creator_FBD::create(const QDomNode &node_) const
{
    return new Translator_POU_FBD(node_);
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** Translator_POU_builder ***

Translator_POU_builder * Translator_POU_builder::_m_instance = nullptr;

Translator_POU_builder::Translator_POU_builder()
{
    _m_hCreators.insert(ITranslator_POU::eTranslatorPOUType::typeST, new Translator_POU_creator_ST);
    _m_hCreators.insert(ITranslator_POU::eTranslatorPOUType::typeFBD, new Translator_POU_creator_FBD);
}

Translator_POU_builder::~Translator_POU_builder()
{
    for(const auto & creator : std::as_const(_m_hCreators))
        delete creator;

    delete _m_instance;
}

Translator_POU_builder * Translator_POU_builder::instance()
{
    if(_m_instance == nullptr)
        _m_instance = new Translator_POU_builder;

    return _m_instance;
}

ITranslator_POU::eTranslatorPOUType Translator_POU_builder::assignType(const QDomNode &node_)
{
    if(!node_.namedItem("body").namedItem("ST").isNull())
        return ITranslator_POU::eTranslatorPOUType::typeST;
    if(!node_.namedItem("body").namedItem("FBD").isNull())
        return ITranslator_POU::eTranslatorPOUType::typeFBD;

    return ITranslator_POU::eTranslatorPOUType::typeUnknown;
}

ITranslator_POU * Translator_POU_builder::build(const QDomNode &node_) const
{
    auto type = assignType(node_);
    if(_m_hCreators.contains(type))
        return _m_hCreators.value(type)->create(node_);

    return nullptr;
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** Translator ***
//
QString Translator::translate(const QDomDocument &doc_)
{
    QString _st_text = {};

    // datatypes
    {
        _st_text += FbdTranslator::getSTCode_types(doc_.elementsByTagName("dataTypes").at(0));
    }
    // pous
    {
        QDomNodeList pous_list = doc_.elementsByTagName("pous").at(0).toElement().elementsByTagName("pou");
        for(auto i=0;i<pous_list.count();i++)
            _st_text += Translator_POU_builder::instance()->build(pous_list.at(i))->translate();
    }
    // configuration
    {
        _st_text += FbdTranslator::getSTCode_instances(doc_.elementsByTagName("instances").at(0));
    }

    return _st_text;
}
// ----------------------------------------------------------------------------
