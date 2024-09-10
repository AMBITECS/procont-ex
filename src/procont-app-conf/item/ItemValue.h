#ifndef ITEMVALUE_H
#define ITEMVALUE_H

#include <QDomNode>
#include <QScopedPointer>
#include <QSharedPointer>
#include <QList>
#include <QHash>
#include <QDebug>

// #include "DomItem.h"

// ----------------------------------------------------------------------------
// *** ItemValue ***

/*!
 * \brief The ItemValue interface
 */

class ItemValue
{
public:

    ItemValue(const QDomNode &node/*, const QDomNode &parent = {}*/);

    [[nodiscard]] virtual QString get() const = 0;
    virtual void set(const QString &value) = 0;

public:
    [[nodiscard]] inline QDomNode node() const { return m_node; }
    [[nodiscard]] inline QDomNode parent() const { return m_node.parentNode(); }

protected:
    QDomNode m_node;/*
    QDomNode m_parent;*/
};
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// *** ItemValue_default ***

/*!
 * \brief The ItemValue_Default class
 */

class ItemValue_Default : public ItemValue
{
public:
    ItemValue_Default(const QDomNode &node/*, const QDomNode &parent*/);

    [[nodiscard]] QString get() const override;
    void set(const QString &value) override;
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_NodeName ***

/*!
 * \brief The ItemValue_NodeName class
 */

class ItemValue_NodeName: public ItemValue
{
public:
    ItemValue_NodeName(const QDomNode &node/*, const QDomNode &parent*/);

    [[nodiscard]] QString get() const override;
    void set(const QString &value) override;
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_NodeValue ***

/*!
 * \brief The ItemValue_NodeValue class
 */

class ItemValue_NodeValue: public ItemValue
{
public:
    ItemValue_NodeValue(const QDomNode &node/*, const QDomNode &parent*/);

    [[nodiscard]] QString get() const override;
    void set(const QString &value) override;
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_SubNodeValue ***

/*!
 * \brief The ItemValue_SubNodeValue class
 */

class ItemValue_SubNodeValue: public ItemValue
{
public:
    ItemValue_SubNodeValue(const QDomNode &node/*, const QDomNode &parent*/);

    [[nodiscard]] QString get() const override;
    void set(const QString &value) override;

    void setName(const QString &name);

private:
    QString m_name = QString();
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_Attr_opt ***

/*!
 * \brief The ItemValue_Attr_opt class
 */

class ItemValue_Attr_opt: public ItemValue
{
public:
    ItemValue_Attr_opt(const QDomNode &node/*, const QDomNode &parent*/);

    [[nodiscard]] QString get() const override;
    void set(const QString &value) override;

    void setName(const QString &name);

private:
    QString m_name = QString();
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_Attr_req ***

/*!
 * \brief The ItemValue_Attr_req class
 */

class ItemValue_Attr_req: public ItemValue
{
public:
    ItemValue_Attr_req(const QDomNode &node/*, const QDomNode &parent*/);

    [[nodiscard]] QString get() const override;
    void set(const QString &value) override;

    void setName(const QString &name);

private:
    QString m_name = QString();
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_SubNodeAttr ***

/*!
 * \brief The ItemValue_SubNodeAttr class
 */

class ItemValue_SubNodeAttr: public ItemValue
{
public:
    ItemValue_SubNodeAttr(const QDomNode &node/*, const QDomNode &parent*/);

    [[nodiscard]] virtual QString get() const override;
    virtual void set(const QString &value) override;

    void setNodeName(const QString &name);
    void setChNodeName(const QString &name);
    void setChAttrName(const QString &name);

protected:
    QString m_nodeName = QString();
    QString m_chNodeName = QString();
    QString m_chAttrName = QString();
};
// ----------------------------------------------------------------------------

#endif // ITEMVALUE_H
