#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QDomNode>

// ----------------------------------------------------------------------------
// *** ITranslator ***

/*!
 * \brief The ITranslator interface
 */

class ITranslator
{
public:
    enum class eTranslatorType
    {
        typeST,
        typeFBD,
        typeUnknown
    };
public:
    ITranslator() = default;

    virtual QString translate(const QDomNode &node_) const = 0;
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** Translator_ST ***

/*!
 * \brief The Translator_ST class
 */

class Translator_ST : public ITranslator
{
public:
    Translator_ST();

    QString translate(const QDomNode &node_) const override;
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** Translator_FBD ***

/*!
 * \brief The Translator_FBD class
 */

class Translator_FBD : public ITranslator
{
public:
    Translator_FBD();

    QString translate(const QDomNode &node_) const override;
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ITranslator_creator ***

/*!
 * \brief The ITranslator_creator interface
 */

class ITranslator_creator
{
public:
    ITranslator_creator() = default;

    virtual ITranslator * create() = 0;
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** Translator_creator_ST ***

/*!
 * \brief The Translator_creator_ST class
 */

class Translator_creator_ST
{
public:
    Translator_creator_ST() = default;

    virtual ITranslator * create();
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** Translator_creator_FBD ***

/*!
 * \brief The Translator_creator_FBD class
 */

class Translator_creator_FBD
{
public:
    Translator_creator_FBD() = default;

    virtual ITranslator * create();
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** Translator_builder ***

#include <QHash>

/*!
 * \brief The Translator_builder class
 */

class Translator_builder
{
public:
    Translator_builder();
    ~Translator_builder();

    virtual ITranslator * build();

private:
    QHash<eTranslatorType, ITranslator_creator*> m_creators;
};
// ----------------------------------------------------------------------------
#endif
