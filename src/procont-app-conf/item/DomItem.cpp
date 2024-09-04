#include "DomItem.h"

#include "ItemValue.h"

#include <QtXml>

// ----------------------------------------------------------------------------
// *** DomItem ***

QScopedPointer<DomItem_builder> DomItem::m_ItemBuilder = QScopedPointer<DomItem_builder>(new DomItem_builder);
QScopedPointer<ItemValue_builder> DomItem::m_ValueBuilder = QScopedPointer<ItemValue_builder>(new ItemValue_builder);
QStringList DomItem::m_discard = { "types", "pous", "instances", "configurations" };

DomItem::DomItem(const QDomNode &node, const QDomNode &parent) :
    m_itemType(assignType(node)),
    m_value(new ItemValue_Default(node, parent))
{
}

DomItem::~DomItem()
{
}

DomItem::ItemType DomItem::assignType(const QDomNode &node)
{
    if(node.nodeName() == "pou")
        return DomItem::typePou;
    if(node.nodeName() == "globalVars")
        return DomItem::typeVar;

    return DomItem::typeItem;
}

QDomNode DomItem::node() const
{
    return m_value->node();
}

DomItem * DomItem::parentItem() const
{
    Q_ASSERT(dynamic_cast<DomItem *>(QStandardItem::parent()));

    return dynamic_cast<DomItem *>(QStandardItem::parent());
}

int DomItem::rowCount()
{
    if (!QStandardItem::rowCount())
        insertChildren(node());

    return QStandardItem::rowCount();
}

int DomItem::columnCount()
{
    if (!QStandardItem::columnCount())
        insertChildren(node());

    return QStandardItem::columnCount();
}

QDomNodeList DomItem::filterChildren(const QDomNode &node) const
{
    return node.childNodes();
}

std::pair<int, int> DomItem::insertChildren(const QDomNode & parentNode, int shift)
{
    QDomNodeList children = filterChildren(parentNode);

    int ch = 0; int cn = 0; std::pair<int, int> res1 = std::make_pair(0,0);
    for (int i=0;i<children.count();i++)
    {
        QDomNode child = children.at(i);
        if(!m_discard.contains(child.nodeName()))
        {
            int rr_c = (res1.first>0)?res1.first-i:shift;
            insertChild(i, 0, parentNode, rr_c+cn);
            ch++;
        }
        else
        {
            int rr_c = (res1.first>0)?res1.first:shift;
            int cn_c = cn; cn_c += (res1.first>0)?0:ch;
            res1 = insertChildren(child, rr_c+cn_c);
            cn += res1.second;
        }
    }

    return std::make_pair(shift, ch+cn);
}

DomItem * DomItem::insertChild(int row, int column, const QDomNode & node, int shift)
{
    auto childItem = dynamic_cast<DomItem *>(child(shift+row, column));
    if (childItem)
        return childItem;

    buildChildren(node, row, shift);

    childItem = dynamic_cast<DomItem *>(child(shift+row, column));

    return childItem;
}

void DomItem::removeChild(int row, int column, const QDomNode & childNode)
{
    Q_UNUSED(column);

    childNode.parentNode().removeChild(childNode);

    m_lChildNodes.remove(row); m_lChildCreated.remove(row);
}

void DomItem::buildChildren(const QDomNode &node, int row, int shift)
{
    auto childNode = node.childNodes().item(row);
    auto childItem = itemBuilder()->build(childNode);
    setChild(shift+row, 0, childItem);
}

QVariant DomItem::data(int role) const
{
    Q_UNUSED(role);

    return m_value->get();
}

void DomItem::setData(const QVariant &value, int role)
{
    Q_UNUSED(role);

    qDebug() << __PRETTY_FUNCTION__ << dynamic_cast<DomItem *>(parentItem()->child(row(), 6))->node().nodeName();

    m_value->set(value.toString());
}

ItemValue * DomItem::itemValue() const
{
    return m_value.get();
}

void DomItem::setItemValue(ItemValue *pointer)
{
    m_value.reset(pointer);
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** DomItemVar ***
DomItemVar::DomItemVar(const QDomNode &node, const QDomNode &parent) :
    DomItem(node, parent)
{
}

void DomItemVar::addEmptyNode()
{
    QDomNode parentNode = node();
    QDomElement el_variable = parentNode.ownerDocument().createElement("variable");
    QDomElement el_variable_type = parentNode.ownerDocument().createElement("type");
    QDomElement el_variable_type_int = parentNode.ownerDocument().createElement("WORD");
    el_variable_type.appendChild(el_variable_type_int);
    el_variable.appendChild(el_variable_type);
    parentNode.appendChild(el_variable);
}

void DomItemVar::setupChildren(const QDomNode & node)
{
    setupChild(node, "variable");
}

void DomItemVar::setupChild(const QDomNode & node, const QString & name)
{
    auto vars = node.toElement().elementsByTagName(name);
    for(auto i=0;i<vars.count();i++)
    {
        if(!m_lChildNodes.contains(vars.at(i)))
        {
            m_lChildNodes.append(vars.at(i));
            m_lChildCreated.append(false);
        }
    }
}

void DomItemVar::buildChildren(const QDomNode &node, int row, int shift)
{
    if(m_lChildNodes.size() <= row)
        setupChildren(node);

    for(auto i=0;i<m_lChildNodes.size();i++)
    {
        if(!m_lChildCreated.at(i))
        {
            buildChild(m_lChildNodes.at(i), shift+i);
            m_lChildCreated[i] = true;
        }
    }
}

void DomItemVar::buildChild(const QDomNode &node, int row)
{
    // item
    auto childNode = node;
    auto childItem = itemBuilder()->build(childNode);
    setChild(row, 0, childItem);
    // number
    childItem = itemBuilder()->build(QDomNode());
    setChild(row, 1, childItem);
    // var type
    childItem = itemBuilder()->build(node.parentNode());
    setChild(row, 2, childItem);
    // name
    childNode = node.attributes().namedItem("name");
    childItem = itemBuilder()->build(childNode);
    childItem->setItemValue(new ItemValue_Name(childNode));
    setChild(row, 3, childItem);
    // address
    childNode = node.attributes().namedItem("address");
    childItem = itemBuilder()->build(childNode, node);
    childItem->setItemValue(new ItemValue_Address(childNode, node));
    setChild(row, 4, childItem);
    // data type
    childNode = node.toElement().elementsByTagName("type").at(0).toElement().firstChild();
    childItem = itemBuilder()->build(childNode, node.toElement().elementsByTagName("type").at(0));
    childItem->setItemValue(valueBuilder()->build(childNode, node.toElement().elementsByTagName("type").at(0)));
    setChild(row, 5, childItem);
    // initial value
    childNode = node.namedItem("initialValue");
    childItem = itemBuilder()->build(childNode, node);
    childItem->setItemValue(new ItemValue_SimpleValue(childNode, node));
    setChild(row, 6, childItem);
    // doc
    childNode = node.namedItem("documentation");
    childItem = itemBuilder()->build(childNode, node);
    childItem->setItemValue(valueBuilder()->build(childNode, node));
    setChild(row, 7, childItem);
    // attributes
    childItem = itemBuilder()->build(QDomNode());
    setChild(row, 8, childItem);
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** DomItemPou ***
DomItemPou::DomItemPou(const QDomNode &node, const QDomNode &parent) :
    DomItemVar(node, parent)
{
}

QVariant DomItemPou::data(int role) const
{
    Q_UNUSED(role);

    return node().attributes().namedItem("name").nodeValue();
}

void DomItemPou::addEmptyNode()
{
    QDomNode parentNode = node();
    QDomElement el_variable = parentNode.ownerDocument().createElement("variable");
    el_variable.setAttribute("name", "localVar");
    QDomElement el_variable_type = parentNode.ownerDocument().createElement("type");
    QDomElement el_variable_type_int = parentNode.ownerDocument().createElement("REAL");
    el_variable_type.appendChild(el_variable_type_int);
    el_variable.appendChild(el_variable_type);
    QDomNode el_localVars = parentNode.namedItem("interface").namedItem("localVars");
    if(el_localVars.isNull())
    {
        el_localVars = parentNode.ownerDocument().createElement("localVars");
        parentNode.namedItem("interface").appendChild(el_localVars);
    }
    el_localVars.appendChild(el_variable);
}

QDomNodeList DomItemPou::filterChildren(const QDomNode &node) const
{
    return node.toElement().elementsByTagName("interface");
}

void DomItemPou::setupChildren(const QDomNode & node)
{
    auto ifaces = node.toElement().elementsByTagName("interface");
    if(ifaces.count())
    {
        auto vars = ifaces.at(0).toElement().elementsByTagName("inputVars");
        setupChild(vars.at(0), "variable");
        vars = ifaces.at(0).toElement().elementsByTagName("outputVars");
        setupChild(vars.at(0), "variable");
        vars = ifaces.at(0).toElement().elementsByTagName("localVars");
        setupChild(vars.at(0), "variable");
        vars = ifaces.at(0).toElement().elementsByTagName("tempVars");
        setupChild(vars.at(0), "variable");
        vars = ifaces.at(0).toElement().elementsByTagName("inOutVars");
        setupChild(vars.at(0), "variable");
        vars = ifaces.at(0).toElement().elementsByTagName("externalVars");
        setupChild(vars.at(0), "variable");
        vars = ifaces.at(0).toElement().elementsByTagName("globalVars");
        setupChild(vars.at(0), "variable");
        vars = ifaces.at(0).toElement().elementsByTagName("accessVars");
        setupChild(vars.at(0), "variable");
    }
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** DomItem_creator ***
DomItem * DomItem_creator::create(const QDomNode &node, const QDomNode &parent)
{
    return new DomItem(node, parent);
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** DomItemVar_creator ***
DomItem * DomItemVar_creator::create(const QDomNode &node, const QDomNode &parent)
{
    return new DomItemVar(node, parent);
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** DomItemPou_creator ***
DomItem * DomItemPou_creator::create(const QDomNode &node, const QDomNode &parent)
{
    return new DomItemPou(node, parent);
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** DomItem_builder ***
DomItem_builder::DomItem_builder()
{
    m_creators.insert(DomItem::typeItem, new DomItem_creator);
    m_creators.insert(DomItem::typeVar, new DomItemVar_creator);
    m_creators.insert(DomItem::typePou, new DomItemPou_creator);
}

DomItem_builder::~DomItem_builder()
{
    for(const auto & creator : std::as_const(m_creators))
        delete creator;
}

DomItem * DomItem_builder::build(const QDomNode &node, const QDomNode &parent)
{
    auto type = DomItem::assignType(node);
    if(m_creators.contains(type))
        return m_creators.value(type)->create(node, parent);

    return nullptr;
}
// ----------------------------------------------------------------------------
