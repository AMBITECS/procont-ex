#include "Translator.h"

// ----------------------------------------------------------------------------
// *** Translator_ST ***

#include "editor-st/XmlParser.h"

Translator_ST::Translator_ST() : ITranslator()
{
}

QString Translator_ST::translate(const QDomNode &node_) const
{
    QString _text = {};
    _text += XmlParser::getPouVarsText(node_);
    _text += XmlParser::getPouBodyText(node_);

    return _text;
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** Translator_FBD ***

#include "translator-fbd/FbdTranslator.h"

Translator_FBD::Translator_FBD() : ITranslator()
{
}

QString Translator_FBD::translate(const QDomNode &node_) const
{
    FbdTranslator translator;
    return translator.getSTCode_pou(node_);
}
// ----------------------------------------------------------------------------
