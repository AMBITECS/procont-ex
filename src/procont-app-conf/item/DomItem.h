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
        typeName    = QStandardItem::UserType + 5,
        typeProject = QStandardItem::UserType + 6
    };
public:
    DomItem(const QDomNode &node);
    virtual ~DomItem() = default;

public:
    [[nodiscard]] DomItem * insertChild(int row, int column, const QDomNode & node, int shift = 0);
    void removeChild(int row, int column, const QDomNode & childNode);
    void removeChildren();
    [[nodiscard]] virtual bool hasChild(const QString & name_, int row = -1);

    virtual void updateNode(const QDomNode &new_node_);
    virtual QDomNode defaultNode() const { return QDomNode(); }

    [[nodiscard]] DomItem * parentItem() const;
    [[nodiscard]] QDomNode node() const;
    [[nodiscard]] int rowCount();
    [[nodiscard]] int columnCount();

    [[nodiscard]] virtual QVariant data(int role = Qt::DisplayRole) const override;
    virtual void setData(const QVariant &value, int role) override;
    [[nodiscard]] int type() const override { return m_itemType; }

    [[nodiscard]] QString print() const;

public:
    [[nodiscard]] static ItemType assignType(const QDomNode &node);
    [[nodiscard]] static QString printNode(const QDomNode &);

protected:
    void setItemValue(ItemValue *item);

protected:
    [[nodiscard]] std::pair<int, int> insertChildren(const QDomNode & parentNode, int shift = 0);
    [[nodiscard]] virtual QDomNodeList filterChildren(const QDomNode &node) const;
    virtual void buildChildren(const QDomNode &node, int row, int shift = 0);

protected:
    static QScopedPointer<DomItem_builder> m_ItemBuilder;
    [[nodiscard]] DomItem_builder * itemBuilder() { return m_ItemBuilder.get(); }

protected:
    ItemType m_itemType;
    QScopedPointer<ItemValue> m_value;

protected:
    std::vector<QDomNode> _v_child_nodes;
    std::vector<bool> _v_child_creation;

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
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** DomItemType
class DomItemType : public DomItemName
{
public:
    DomItemType(const QDomNode &node) :
        DomItemName(node)
    {}

    void updateNode(const QDomNode &new_node_)
    {
        qDebug() << __PRETTY_FUNCTION__;

        if(new_node_.nodeName() == "baseType")
        {
            node().removeChild(node().namedItem("baseType"));
            node().appendChild(new_node_.cloneNode());

            return;
        }

        DomItem::updateNode(new_node_);
    }

};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** DomItemProject
class DomItemProject : public DomItem
{
public:
    DomItemProject(const QDomNode &node) :
        DomItem(node)
    {}

    [[nodiscard]] QVariant data(int role) const override
    {
        Q_UNUSED(role);

        return node().namedItem("contentHeader").toElement().attribute("name");
    }
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** DomItemVar
class DomItemVar : public DomItem
{
public:
    DomItemVar(const QDomNode &node);

    virtual QDomNode defaultNode() const override;

protected:
    virtual void buildChildren(const QDomNode &node, int row, int shift = 0) override;
    void buildChild(const QDomNode &node, int row);
    virtual void setupChildren(const QDomNode &, int row);
    [[nodiscard]] int countChildren(const QDomNode &node_) const;
    [[nodiscard]] virtual QDomNodeList listChildren(const QDomNode &node_) const;

protected:
    [[nodiscard]] static QString getDefaultVariableName(const QDomNodeList &list_);
};
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** DomItemPou
class DomItemPou : public DomItemVar
{
public:
    DomItemPou(const QDomNode &node);

    [[nodiscard]] QVariant data(int role) const override;

    virtual QDomNode defaultNode() const override;
    virtual void updateNode(const QDomNode &new_node_) override;

protected:
    [[nodiscard]] virtual QDomNodeList filterChildren(const QDomNode &node) const override;
    [[nodiscard]] virtual QDomNodeList listChildren(const QDomNode &node_) const override;
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
// *** DomItemType_creator
class DomItemType_creator : public DomItem_creator
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
// *** DomItemProject_creator
class DomItemProject_creator : public DomItem_creator
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
