#ifndef ITEMVALUE_H
#define ITEMVALUE_H

#include <QDomNode>

#include "DomItem.h"

// ----------------------------------------------------------------------------
// *** ItemValue ***

/*!
 * \brief The ItemValue interface
 */

class ItemValue
{
public:
    ItemValue(const QDomNode &node, const QDomNode &parent = QDomNode());

    [[nodiscard]] virtual QString get() const = 0;
    virtual void set(const QString &value) = 0;

public:
    [[nodiscard]] inline QDomNode node() const { return m_node; }
    [[nodiscard]] inline QDomNode parent() const { return m_parent; }

protected:
    QDomNode m_node;
    QDomNode m_parent;
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
    ItemValue_Default(const QDomNode &node, const QDomNode &parent = QDomNode());

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
    ItemValue_NodeName(const QDomNode &node, const QDomNode &parent = QDomNode());

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
    ItemValue_NodeValue(const QDomNode &node, const QDomNode &parent = QDomNode());

    [[nodiscard]] QString get() const override;
    void set(const QString &value) override;
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_Attr_optional ***

/*!
 * \brief The ItemValue_Attr_optionalclass
 */

class ItemValue_Attr_optional: public ItemValue
{
public:
    ItemValue_Attr_optional(const QDomNode &node, const QDomNode &parent = QDomNode());

    [[nodiscard]] QString get() const override;
    void set(const QString &value) override;

    void setName(const QString &name);

private:
    QString m_name = QString();
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_Attr ***

/*!
 * \brief The ItemValue_Attr class
 */

class ItemValue_Attr: public ItemValue
{
public:
    ItemValue_Attr(const QDomNode &node, const QDomNode &parent = QDomNode());

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
    ItemValue_SubNodeAttr(const QDomNode &node, const QDomNode &parent = QDomNode());

    [[nodiscard]] QString get() const override;
    void set(const QString &value) override;

    void setNodeName(const QString &name);
    void setAttrName(const QString &name);

private:
    QString m_nodeName = QString();
    QString m_attrName = QString();
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_creator

/*!
 * \brief The ItemValue_creator interface
 */

class ItemValue_creator
{
public:
    ItemValue_creator() = default;
    virtual ~ItemValue_creator() = default;
    [[nodiscard]] virtual ItemValue * create(const QDomNode &node, const QDomNode &parent = QDomNode()) = 0;
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_Default_creator

class ItemValue_Default_creator : public ItemValue_creator
{
public:
    [[nodiscard]] virtual ItemValue * create(const QDomNode &node, const QDomNode &parent = QDomNode());
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_NodeName_creator

class ItemValue_NodeName_creator : public ItemValue_creator
{
public:
    [[nodiscard]] virtual ItemValue * create(const QDomNode &node, const QDomNode &parent = QDomNode());
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_NodeValue_creator

class ItemValue_NodeValue_creator : public ItemValue_creator
{
public:
    [[nodiscard]] virtual ItemValue * create(const QDomNode &node, const QDomNode &parent = QDomNode());
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_Attr_optional_creator

class ItemValue_Attr_optional_creator : public ItemValue_creator
{
public:
    [[nodiscard]] virtual ItemValue * create(const QDomNode &node, const QDomNode &parent = QDomNode());
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_Attr_creator

class ItemValue_Attr_creator : public ItemValue_creator
{
public:
    [[nodiscard]] virtual ItemValue * create(const QDomNode &node, const QDomNode &parent = QDomNode());
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_SubNodeAttr_creator

class ItemValue_SubNodeAttr_creator : public ItemValue_creator
{
public:
    [[nodiscard]] virtual ItemValue * create(const QDomNode &node, const QDomNode &parent = QDomNode());
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ItemValue_creator

class ItemValue_builder
{
public:
    ItemValue_builder();
    ~ItemValue_builder();

    [[nodiscard]] ItemValue * build(const QDomNode &node, const QDomNode &parent, DomItem::ValueType valueType);

private:
    QHash<DomItem::ValueType, ItemValue_creator*> m_creators;
};
// ----------------------------------------------------------------------------

#endif // ITEMVALUE_H
