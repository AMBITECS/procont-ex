#include "DomItem.h"

#include "ItemValue.h"
#include "ItemValueVariableTable.h"

#include "tr/translation.h"

#include <QtXml>

// ----------------------------------------------------------------------------
// *** DomItem ***

QScopedPointer<DomItem_builder> DomItem::m_ItemBuilder = QScopedPointer<DomItem_builder>(new DomItem_builder);
QStringList DomItem::m_discard = { "types", /*"pous",*/ "instances", "configurations"/*, "dataTypes"*/ };

DomItem::DomItem(const QDomNode &node) :
    m_itemType(assignType(node)),
    m_value(new ItemValue_Default(node))
{
}

DomItem::ItemType DomItem::assignType(const QDomNode &node)
{
    if(node.nodeName() == "pou")
        return DomItem::typePou;
    if(node.nodeName() == "project")
        return DomItem::typeProject;
    if(
        node.nodeName() == "configuration" ||
        node.nodeName() == "resource" ||
        node.nodeName() == "task" ||
        node.nodeName() == "pouInstance"
        )
        return DomItem::typeName;
    if(node.nodeName() == "dataType")
        return DomItem::typeType;
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
    if (!QStandardItem::rowCount() && start)
    {
        insertChildren(node());
        start = false;
    }

    return QStandardItem::rowCount();
}

int DomItem::columnCount()
{
    if (!QStandardItem::columnCount() && start)
    {
        insertChildren(node());
        start = false;
    }

    return QStandardItem::columnCount();
}

QDomNodeList DomItem::filterChildren(const QDomNode &node) const
{
    return node.childNodes();
}

std::pair<int, int> DomItem::insertChildren(const QDomNode & parentNode, int shift)
{
    QDomNodeList children = filterChildren(parentNode);

    int ch = 0; int cn = 0; std::pair<int, int> res = std::make_pair(0,0);
    for (int i=0;i<children.count();i++)
    {
        QDomNode child = children.at(i);
        if(!m_discard.contains(child.nodeName()))
        {
            int rr_c = (res.first>0)?res.first-i:shift;
            insertChild(i, 0, parentNode, rr_c+cn);
            ch++;
        }
        else
        {
            int rr_c = (res.first>0)?res.first:shift;
            int cn_c = cn; cn_c += (res.first>0)?0:ch;
            res = insertChildren(child, rr_c+cn_c);
            cn += res.second;
        }
    }

    return std::make_pair(shift, ch+cn);
}

DomItem * DomItem::insertChild(int row, int column, const QDomNode & node_, int shift)
{
    auto childItem = dynamic_cast<DomItem *>(child(shift+row, column));
    if (childItem)
        return childItem;

    buildChildren(node_, row, shift);

    childItem = dynamic_cast<DomItem *>(child(shift+row, column));

    return childItem;
}

void DomItem::removeChild(int row, int column, const QDomNode & childNode)
{
    Q_UNUSED(column);

    childNode.parentNode().removeChild(childNode);

    if(m_lChildNodes.size())
        m_lChildNodes.remove(row);
    if(m_lChildCreated.size())
        m_lChildCreated.remove(row);
}

void DomItem::removeChildren()
{
    m_lChildNodes.clear(); m_lChildCreated.clear();
}

void DomItem::buildChildren(const QDomNode &node, int row, int shift)
{
    auto childNode = node.childNodes().item(row);
    auto childItem = itemBuilder()->build(childNode);
    setChild(shift+row, 0, childItem);
}

QVariant DomItem::data(int role) const
{
    // if(role == Qt::DecorationRole)
    //     return QIcon(":/icon/images/diagram.svg");

    return tr_str::instance()->ru(m_value->get());
}

void DomItem::setData(const QVariant &value, int role)
{
    m_value->set(value.toString());
}

void DomItem::setItemValue(ItemValue *pointer)
{
    m_value.reset(pointer);
}

void DomItem::addNode(const QDomNode & node_)
{
    qDebug() << __PRETTY_FUNCTION__;
    qDebug() << DomItem::printNode(node_);

    auto _node = node().ownerDocument().importNode(node_, true);
    node().appendChild(_node);
}

void DomItem::updateNode(const QDomNode &)
{
    qDebug() << __PRETTY_FUNCTION__;
}

QString DomItem::print() const
{
    return printNode(node());
}

QString DomItem::printNode(const QDomNode &node_)
{
    QDomDocument _doc;

    _doc.appendChild(_doc.importNode(node_, true));

    return _doc.toString();
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** DomItemVar ***
DomItemVar::DomItemVar(const QDomNode &node) :
    DomItem(node)
{
}

void DomItemVar::addNode(const QDomNode &)
{
    QDomNode parentNode = node();
    QDomElement el_variable = parentNode.ownerDocument().createElement("variable");
    el_variable.setAttribute("name", "globalVar1");
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
    childItem = itemBuilder()->build({});
    setChild(row, 1, childItem);
    // var type
    childItem = itemBuilder()->build(node);
    childItem->setItemValue(new ItemValue_Type(node));
    setChild(row, 2, childItem);
    // name
    childNode = node.attributes().namedItem("name");
    childItem = itemBuilder()->build(childNode);
    childItem->setItemValue(new ItemValue_Name(childNode));
    setChild(row, 3, childItem);
    // address
    childNode = node;
    childItem = itemBuilder()->build(childNode);
    childItem->setItemValue(new ItemValue_Address(childNode));
    setChild(row, 4, childItem);
    // data type
    childNode = node.namedItem("type");
    childItem = itemBuilder()->build(childNode);
    childItem->setItemValue(new ItemValue_DataType(childNode));
    setChild(row, 5, childItem);
    // initial value
    childNode = node.namedItem("initialValue");
    childItem = itemBuilder()->build(childNode);
    childItem->setItemValue(new ItemValue_InitialValue(childNode, node));
    setChild(row, 6, childItem);
    // doc
    childNode = node.namedItem("documentation");
    childItem = itemBuilder()->build(childNode);
    childItem->setItemValue(new ItemValue_Documentation(childNode, node));
    setChild(row, 7, childItem);
    // attributes
    childItem = itemBuilder()->build({});
    setChild(row, 8, childItem);
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** DomItemPou ***
DomItemPou::DomItemPou(const QDomNode &node) :
    DomItemVar(node)
{
}

QVariant DomItemPou::data(int role) const
{
    Q_UNUSED(role);

    auto _pou_type = node().attributes().namedItem("pouType").nodeValue();
    if(_pou_type == "functionBlock")
        _pou_type = "FB";
    if(_pou_type == "program")
        _pou_type = "PRG";
    if(_pou_type == "function")
        _pou_type = "FUN";

    return QString("%1 (%2)").arg(node().attributes().namedItem("name").nodeValue(), _pou_type);
}

void DomItemPou::addNode(const QDomNode &node_)
{


    QDomNode parentNode = node();
    QDomElement el_variable = parentNode.ownerDocument().createElement("variable");
    el_variable.setAttribute("name", "localVar1");
    QDomElement el_variable_type = parentNode.ownerDocument().createElement("type");
    QDomElement el_variable_type_int = parentNode.ownerDocument().createElement("INT");
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

void DomItemPou::updateNode(const QDomNode & new_node_)
{
    qDebug() << __PRETTY_FUNCTION__;

    if(new_node_.nodeName() == "interface")
    {
        node().removeChild(node().namedItem("interface"));
        node().appendChild(new_node_.cloneNode());
    }

    if
        (
        new_node_.nodeName() == "body" &&
        node().namedItem("body").firstChild().nodeName() == new_node_.firstChild().nodeName()
        )
    {
        node().removeChild(node().namedItem("body"));
        node().appendChild(new_node_.cloneNode());
    }
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
        for(auto i=0;i<vars.count();i++)
            setupChild(vars.at(i), "variable");
        vars = ifaces.at(0).toElement().elementsByTagName("outputVars");
        for(auto i=0;i<vars.count();i++)
            setupChild(vars.at(i), "variable");
        vars = ifaces.at(0).toElement().elementsByTagName("localVars");
        for(auto i=0;i<vars.count();i++)
            setupChild(vars.at(i), "variable");
        vars = ifaces.at(0).toElement().elementsByTagName("tempVars");
        for(auto i=0;i<vars.count();i++)
            setupChild(vars.at(i), "variable");
        vars = ifaces.at(0).toElement().elementsByTagName("inOutVars");
        for(auto i=0;i<vars.count();i++)
            setupChild(vars.at(i), "variable");
        vars = ifaces.at(0).toElement().elementsByTagName("externalVars");
        for(auto i=0;i<vars.count();i++)
            setupChild(vars.at(i), "variable");
        vars = ifaces.at(0).toElement().elementsByTagName("globalVars");
        for(auto i=0;i<vars.count();i++)
            setupChild(vars.at(i), "variable");
        vars = ifaces.at(0).toElement().elementsByTagName("accessVars");
        for(auto i=0;i<vars.count();i++)
            setupChild(vars.at(i), "variable");
    }
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** DomItem_creator ***
DomItem * DomItem_creator::create(const QDomNode &node)
{
    return new DomItem(node);
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** DomItemName_creator ***
DomItem * DomItemName_creator::create(const QDomNode &node)
{
    return new DomItemName(node);
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** DomItemType_creator ***
DomItem * DomItemType_creator::create(const QDomNode &node)
{
    return new DomItemType(node);
}
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// *** DomItemVar_creator ***
DomItem * DomItemVar_creator::create(const QDomNode &node)
{
    return new DomItemVar(node);
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** DomItemPou_creator ***
DomItem * DomItemPou_creator::create(const QDomNode &node)
{
    return new DomItemPou(node);
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** DomItemProject_creator ***
DomItem * DomItemProject_creator::create(const QDomNode &node)
{
    return new DomItemProject(node);
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** DomItem_builder ***
DomItem_builder::DomItem_builder()
{
    m_creators.insert(DomItem::typeItem, new DomItem_creator);
    m_creators.insert(DomItem::typeType, new DomItemType_creator);
    m_creators.insert(DomItem::typeVar, new DomItemVar_creator);
    m_creators.insert(DomItem::typePou, new DomItemPou_creator);
    m_creators.insert(DomItem::typeName, new DomItemName_creator);
    m_creators.insert(DomItem::typeProject, new DomItemProject_creator);
}

DomItem_builder::~DomItem_builder()
{
    for(const auto & creator : std::as_const(m_creators))
        delete creator;
}

DomItem * DomItem_builder::build(const QDomNode &node)
{
    auto type = DomItem::assignType(node);
    if(m_creators.contains(type))
        return m_creators.value(type)->create(node);

    return nullptr;
}
// ----------------------------------------------------------------------------
