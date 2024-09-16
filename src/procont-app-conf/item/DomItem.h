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
        typePou     = QStandardItem::UserType + 3
    };
public:
    DomItem(const QDomNode &node);
    virtual ~DomItem() = default;

public:
    [[nodiscard]] DomItem * insertChild(int row, int column, const QDomNode & node, int shift = 0);
    void removeChild(int row, int column, const QDomNode & childNode);
    void removeChildren();
    virtual void updateNode(const QDomNode &) {;}
    virtual void addEmptyNode() {;}

    [[nodiscard]] DomItem * parentItem() const;
    [[nodiscard]] QDomNode node() const;
    [[nodiscard]] int rowCount();
    [[nodiscard]] int columnCount();

    [[nodiscard]] virtual QVariant data(int role) const override;
    virtual void setData(const QVariant &value, int role) override;
    [[nodiscard]] int type() const override { return m_itemType; }

public:
    [[nodiscard]] static ItemType assignType(const QDomNode &node);

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
// *** DomItemVar
class DomItemVar : public DomItem
{
public:
    DomItemVar(const QDomNode &node);

    virtual void addEmptyNode() override;

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

    virtual void addEmptyNode() override;
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
