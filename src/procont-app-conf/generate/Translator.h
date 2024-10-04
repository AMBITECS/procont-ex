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
    ITranslator(const QDomNode &node_) : _m_node(node_)
    {}

    virtual QString translate() const = 0;

protected:
    QDomNode _m_node;
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
    Translator_ST(const QDomNode &node_);

    QString translate() const override;
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
    Translator_FBD(const QDomNode &node_);

    QString translate() const override;
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

    virtual ITranslator * create(const QDomNode &node_) const = 0;
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** Translator_creator_ST ***

/*!
 * \brief The Translator_creator_ST class
 */

class Translator_creator_ST : public ITranslator_creator
{
public:
    Translator_creator_ST() = default;

    ITranslator * create(const QDomNode &node_) const override;
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** Translator_creator_FBD ***

/*!
 * \brief The Translator_creator_FBD class
 */

class Translator_creator_FBD : public ITranslator_creator
{
public:
    Translator_creator_FBD() = default;

    ITranslator * create(const QDomNode &node_) const override;
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
private:
    Translator_builder();

public:
    ~Translator_builder();

public:
    static Translator_builder * instance();

    ITranslator * build(const QDomNode &) const;

private:
    static ITranslator::eTranslatorType assignType(const QDomNode &);

private:
    static Translator_builder * _m_instance;
    QHash<ITranslator::eTranslatorType, ITranslator_creator*> _m_hCreators;
};
// ----------------------------------------------------------------------------
#endif
