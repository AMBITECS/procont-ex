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
    if(childItem)
         return childItem;

    buildChildren(node_, row, shift);

    childItem = dynamic_cast<DomItem *>(child(shift+row, column));

    Q_ASSERT(childItem);

    return childItem;
}

void DomItem::removeChild(int row, int column, const QDomNode & childNode)
{
    Q_UNUSED(column);

    childNode.parentNode().removeChild(childNode);

    if(_v_child_nodes.size() > row)
        _v_child_nodes.erase(_v_child_nodes.begin()+row);
    if(_v_child_creation.size() > row)
        _v_child_creation.erase(_v_child_creation.begin()+row);
}

void DomItem::removeChildren()
{
    _v_child_nodes.clear();
    _v_child_creation.clear();
}

bool DomItem::hasChild(const QString & name_, int row)
{
    for(auto i=0;i<rowCount();i++)
    {
        if(i == row)
            continue;

        auto _name = reinterpret_cast<DomItem*>(child(i, 0))->node().toElement().attribute("name");
        if(_name == name_)
            return true;
    }

    return false;
}

void DomItem::buildChildren(const QDomNode &node_, int row, int shift)
{
    auto childNode = node_.childNodes().item(row);

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
    qDebug() << __PRETTY_FUNCTION__ << m_value.get();

    m_value->set(value.toString());
}

void DomItem::setItemValue(ItemValue *pointer)
{
    m_value.reset(pointer);
}

void DomItem::updateNode(const QDomNode &new_node_)
{
    // qDebug() << __PRETTY_FUNCTION__;

    auto parent = node().parentNode();
    parent.removeChild(node());
    auto _node = parent.appendChild(new_node_);
    m_value->updateNode(_node);
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

QDomNode DomItemVar::defaultNode() const
{
    QDomDocument _doc;

    auto _variable_type_int = _doc.createElement("INT");
    auto _variable_type = _doc.createElement("type");
    _variable_type.appendChild(_variable_type_int);
    auto _variable = _doc.createElement("variable");
    _variable.appendChild(_variable_type);
    _variable.setAttribute("name", getDefaultVariableName(listChildren(node())));

    _doc.appendChild(_variable);

    return _doc;
}

void DomItemVar::buildChildren(const QDomNode &node_, int row, int)
{
    // qDebug() << __PRETTY_FUNCTION__ << node_.nodeName() << row << countChildren(node_) << _v_child_nodes.size();

    if(_v_child_nodes.size() < countChildren(node_))
        setupChildren(node_, row);

    for(auto i=0;i<_v_child_creation.size();i++)
    {
        if(!_v_child_creation[i])
        {
            buildChild(_v_child_nodes.at(i), i);
            _v_child_creation[i] = true;
        }
    }
}

QDomNodeList DomItemVar::listChildren(const QDomNode &node_) const
{
    return node_.toElement().elementsByTagName("variable");
}

int DomItemVar::countChildren(const QDomNode &node_) const
{
    return listChildren(node_).count();
}

void DomItemVar::setupChildren(const QDomNode &node_, int row)
{
    // qDebug() << __PRETTY_FUNCTION__ << node_.nodeName() << row;

    auto vars = listChildren(node_);

    if(!_v_child_nodes.size())
    {
        // qDebug() << __PRETTY_FUNCTION__ << "1";

        for(auto i=0;i<vars.count();i++)
        {
            _v_child_nodes.insert(_v_child_nodes.begin()+i, vars.at(i));
            _v_child_creation.insert(_v_child_creation.begin()+i, false);
        }
    }
    else
    {
        // qDebug() << __PRETTY_FUNCTION__ << "2";

        QDomNode _new_node = {};
        for(auto i=0;i<vars.count();i++)
        {
            if(_v_child_nodes.cend() ==
                std::find_if(_v_child_nodes.cbegin(), _v_child_nodes.cend(),
                             [i,&vars](const QDomNode &value_){ return value_ == vars.at(i); }))
            {
                _new_node = vars.at(i);
                break;
            }
        }

        Q_ASSERT(!_new_node.isNull());

        _v_child_nodes.insert(_v_child_nodes.begin()+row, _new_node);
        _v_child_creation.insert(_v_child_creation.begin()+row, false);
    }
}

void DomItemVar::buildChild(const QDomNode &node, int row)
{
    // qDebug() << __PRETTY_FUNCTION__ << row;

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

QString DomItemVar::getDefaultVariableName(const QDomNodeList &list_)
{
    QString _var_name = {};
    for(auto i=1;i<std::numeric_limits<int>::max();i++)
    {
        auto _tmp_name = QString("newVar%1").arg(i);
        for(auto j=0;j<list_.count();j++)
        {
            if(_tmp_name == list_.at(j).toElement().attribute("name"))
            {
                _tmp_name.clear();
                break;
            }
        }

        if(!_tmp_name.isEmpty())
        {
            _var_name = _tmp_name;
            break;
        }
    }

    return _var_name;
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

QDomNode DomItemPou::defaultNode() const
{
    QDomDocument _doc;

    auto _variable_type_int = _doc.createElement("INT");
    auto _variable_type = _doc.createElement("type");
    _variable_type.appendChild(_variable_type_int);
    auto _variable = _doc.createElement("variable");
    _variable.appendChild(_variable_type);
    _variable.setAttribute("name", getDefaultVariableName(listChildren(node())));
    // auto _localVars = _doc.createElement("localVars");
    // _localVars.appendChild(_variable);

    _doc.appendChild(_variable);

    return _doc;
}

void DomItemPou::updateNode(const QDomNode &new_node_)
{
    qDebug() << "1" << new_node_.toElement().attribute("name") << __PRETTY_FUNCTION__;

    if(new_node_.nodeName() == "interface")
    {
        qDebug() << "interface" << __PRETTY_FUNCTION__;

        node().removeChild(node().namedItem("interface"));
        node().appendChild(new_node_.cloneNode());

        return;
    }

    qDebug() << "2" << new_node_.toElement().attribute("name") << __PRETTY_FUNCTION__;

    if(new_node_.nodeName() == "body" &&
        node().namedItem("body").firstChild().nodeName() == new_node_.firstChild().nodeName())
    {
        qDebug() << "body" << __PRETTY_FUNCTION__;

        node().removeChild(node().namedItem("body"));
        node().appendChild(new_node_.cloneNode());

        return;
    }

    qDebug() << "3" << new_node_.toElement().attribute("name") << __PRETTY_FUNCTION__;

    DomItem::updateNode(new_node_);
}

QDomNodeList DomItemPou::filterChildren(const QDomNode &node) const
{
    return node.toElement().elementsByTagName("interface");
}

QDomNodeList DomItemPou::listChildren(const QDomNode &node_) const
{
    return node_.namedItem("interface").toElement().elementsByTagName("variable");
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
