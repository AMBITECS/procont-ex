#ifndef DOMITEM_H
#define DOMITEM_H

#include <QStandardItem>
#include <QDomNode>

#include "ItemValue.h"

// ----------------------------------------------------------------------------
// *** DomItem ***
class DomItem_builder;

class DomItem : public QStandardItem
{
    friend class DomItemVar;
public:
    enum ItemType
    {
        typeItem    = QStandardItem::UserType + 1,
        typeVar     = QStandardItem::UserType + 2,
        typePou     = QStandardItem::UserType + 3,
        typeType    = QStandardItem::UserType + 4,
    };
public:
    DomItem(const QDomNode &node);
    virtual ~DomItem() = default;

public:
    [[nodiscard]] DomItem * insertChild(int row, int column, const QDomNode & node, int shift = 0);
    void removeChild(int row, int column, const QDomNode & childNode);
    void removeChildren();
    virtual void updateNode(const QDomNode &) {;}
    virtual void addNode(const QDomNode & = QDomNode());

    [[nodiscard]] DomItem * parentItem() const;
    [[nodiscard]] QDomNode node() const;
    [[nodiscard]] int rowCount();
    [[nodiscard]] int columnCount();

    [[nodiscard]] virtual QVariant data(int role) const override;
    virtual void setData(const QVariant &value, int role) override;
    [[nodiscard]] int type() const override { return m_itemType; }

    [[nodiscard]] QString print() const;

public:
    [[nodiscard]] static ItemType assignType(const QDomNode &node);
    [[nodiscard]] static QString printNode(const QDomNode &);

public:
    [[nodiscard]] std::pair<int, int> insertChildren(const QDomNode & parentNode, int shift = 0);
    void setItemValue(ItemValue *item);

protected:
    [[nodiscard]] virtual QDomNodeList filterChildren(const QDomNode &node) const;
    virtual void buildChildren(const QDomNode &node, int row, int shift = 0);
    virtual void setupChildren(const QDomNode &) {;}

protected:
    static QScopedPointer<DomItem_builder> m_ItemBuilder;
    [[nodiscard]] DomItem_builder * itemBuilder() { return m_ItemBuilder.get(); }

protected:
    ItemType m_itemType;
    QScopedPointer<ItemValue> m_value;

protected:
    QList<QDomNode> m_lChildNodes;
    QList<bool> m_lChildCreated;

private:
    static QStringList m_discard;
    bool start = true;
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** DomItemName
class DomItemName : public DomItem
{
public:
    DomItemName(const QDomNode &node) :
        DomItem(node)
    {}

    [[nodiscard]] QVariant data(int role) const override
    {
        Q_UNUSED(role);

        return node().attributes().namedItem("name").nodeValue();
    }

    virtual void updateNode(const QDomNode & new_node_) override
    {
        // qDebug() << node().nodeName() << node().parentNode().nodeName();

        // node().parentNode().appendChild(new_node_.cloneNode());
        // node().parentNode().removeChild(node());
    }
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** DomItemVar
class DomItemVar : public DomItem
{
public:
    DomItemVar(const QDomNode &node);

    virtual void addNode(const QDomNode & = QDomNode()) override;

protected:
    virtual void buildChildren(const QDomNode &node, int row, int shift = 0) override;
    void buildChild(const QDomNode &node, int row);
    virtual void setupChildren(const QDomNode &) override;
    void setupChild(const QDomNode & node, const QString & name);
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** DomItemPou
class DomItemPou : public DomItemVar
{
public:
    DomItemPou(const QDomNode &node);

    [[nodiscard]] QVariant data(int role) const override;

    virtual void addNode(const QDomNode & = QDomNode()) override;
    virtual void updateNode(const QDomNode &) override;

protected:
    [[nodiscard]] virtual QDomNodeList filterChildren(const QDomNode &node) const override;
    virtual void setupChildren(const QDomNode &) override;
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** DomItem_creator
class DomItem_creator
{
public:
    [[nodiscard]] virtual DomItem * create(const QDomNode &node);
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** DomItemName_creator
class DomItemName_creator : public DomItem_creator
{
public:
    [[nodiscard]] virtual DomItem * create(const QDomNode &node);
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** DomItemVar_creator
class DomItemVar_creator : public DomItem_creator
{
public:
    [[nodiscard]] virtual DomItem * create(const QDomNode &node);
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** DomItemPou_creator
class DomItemPou_creator : public DomItem_creator
{
public:
    [[nodiscard]] virtual DomItem * create(const QDomNode &node);
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** DomItem_builder
class DomItem_builder
{
public:
    DomItem_builder();
    ~DomItem_builder();

    [[nodiscard]] DomItem * build(const QDomNode &node);

private:
    QHash<DomItem::ItemType, DomItem_creator*> m_creators;
};
// ----------------------------------------------------------------------------

#endif // DOMITEM_H
