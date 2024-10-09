#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QDomNode>

// ----------------------------------------------------------------------------
// *** ITranslator_POU ***

/*!
 * \brief The ITranslator_POU interface
 */

class ITranslator_POU
{
public:
    enum class eTranslatorPOUType
    {
        typeST,
        typeFBD,
        typeUnknown
    };
public:
    ITranslator_POU(const QDomNode &node_) : _m_node(node_)
    {}

    virtual QString translate() const = 0;

protected:
    QDomNode _m_node;
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** Translator_POU_ST ***

/*!
 * \brief The Translator_POU_ST class
 */

class Translator_POU_ST : public ITranslator_POU
{
public:
    Translator_POU_ST(const QDomNode &node_);

    QString translate() const override;
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** Translator_POU_FBD ***

/*!
 * \brief The Translator_POU_FBD class
 */

class Translator_POU_FBD : public ITranslator_POU
{
public:
    Translator_POU_FBD(const QDomNode &node_);

    QString translate() const override;
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ITranslator_POU_creator ***

/*!
 * \brief The ITranslator_POU_creator interface
 */

class ITranslator_POU_creator
{
public:
    ITranslator_POU_creator() = default;
    virtual ~ITranslator_POU_creator() = default;

    virtual ITranslator_POU * create(const QDomNode &node_) const = 0;
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** Translator_POU_creator_ST ***

/*!
 * \brief The Translator_POU_creator_ST class
 */

class Translator_POU_creator_ST : public ITranslator_POU_creator
{
public:
    Translator_POU_creator_ST() = default;

    ITranslator_POU * create(const QDomNode &node_) const override;
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** Translator_POU_creator_FBD ***

/*!
 * \brief The Translator_POU_creator_FBD class
 */

class Translator_POU_creator_FBD : public ITranslator_POU_creator
{
public:
    Translator_POU_creator_FBD() = default;

    ITranslator_POU * create(const QDomNode &node_) const override;
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** Translator_POU_builder ***

#include <QHash>

/*!
 * \brief The Translator_POU_builder class
 */

class Translator_POU_builder
{    
private:
    Translator_POU_builder();

public:
    virtual ~Translator_POU_builder();

public:
    static Translator_POU_builder * instance();

    ITranslator_POU * build(const QDomNode &) const;

private:
    static ITranslator_POU::eTranslatorPOUType assignType(const QDomNode &);

private:
    static Translator_POU_builder * _m_instance;
    QHash<ITranslator_POU::eTranslatorPOUType, ITranslator_POU_creator*> _m_hCreators;
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** Translator ***

/*!
 * \brief The Translator class
 */

class Translator
{
public:
    Translator() = default;

    static QString translate(const QDomDocument &doc_);
};
// ----------------------------------------------------------------------------

#endif
