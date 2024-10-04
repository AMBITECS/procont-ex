#include "Translator.h"

#include <QDebug>

// ----------------------------------------------------------------------------
// *** Translator_ST ***

#include "editor-st/XmlParser.h"

Translator_ST::Translator_ST(const QDomNode &node_) : ITranslator(node_)
{
}

QString Translator_ST::translate() const
{
    qDebug() << __PRETTY_FUNCTION__;

    QString _text = {};
    _text += XmlParser::getPouVarsText(_m_node);
    _text += XmlParser::getPouBodyText(_m_node);

    return _text;
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** Translator_FBD ***

#include "translator-fbd/FbdTranslator.h"

Translator_FBD::Translator_FBD(const QDomNode &node_) : ITranslator(node_)
{
}

QString Translator_FBD::translate() const
{
    qDebug() << __PRETTY_FUNCTION__;

    FbdTranslator translator;
    return translator.getSTCode_pou(_m_node);
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** Translator_creator_ST ***

ITranslator * Translator_creator_ST::create(const QDomNode &node_) const
{
    return new Translator_ST(node_);
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** Translator_creator_FBD ***

ITranslator * Translator_creator_FBD::create(const QDomNode &node_) const
{
    return new Translator_FBD(node_);
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** Translator_builder ***

Translator_builder * Translator_builder::_m_instance = nullptr;

Translator_builder::Translator_builder()
{
    _m_hCreators.insert(ITranslator::eTranslatorType::typeST, new Translator_creator_ST);
    _m_hCreators.insert(ITranslator::eTranslatorType::typeFBD, new Translator_creator_FBD);
}

Translator_builder::~Translator_builder()
{
    for(const auto & creator : std::as_const(_m_hCreators))
        delete creator;

    delete _m_instance;
}

Translator_builder * Translator_builder::instance()
{
    if(_m_instance == nullptr)
        _m_instance = new Translator_builder;

    return _m_instance;
}

ITranslator::eTranslatorType Translator_builder::assignType(const QDomNode &node_)
{
    if(!node_.namedItem("body").namedItem("ST").isNull())
        return ITranslator::eTranslatorType::typeST;
    if(!node_.namedItem("body").namedItem("FBD").isNull())
        return ITranslator::eTranslatorType::typeFBD;

    return ITranslator::eTranslatorType::typeUnknown;
}

ITranslator * Translator_builder::build(const QDomNode &node_) const
{
    auto type = assignType(node_);
    if(_m_hCreators.contains(type))
        return _m_hCreators.value(type)->create(node_);

    return nullptr;
}
// ----------------------------------------------------------------------------
