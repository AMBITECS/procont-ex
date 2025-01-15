#include "WidgetSettings.h"

#include "model/DomModel.h"
#include "item/DomItem.h"

#include <QLabel>

// ----------------------------------------------------------------------------
// *** CustomTabStyle ***

#include <QStyleOptionTab>

QSize CustomTabStyle::sizeFromContents(ContentsType type_, const QStyleOption* option_, const QSize& size_, const QWidget* widget_) const
{
    auto _size = QProxyStyle::sizeFromContents(type_, option_, size_, widget_);
    if(type_ == QStyle::CT_TabBarTab)
        _size.transpose();

    return _size;
}

void CustomTabStyle::drawControl(ControlElement element_, const QStyleOption* option_, QPainter* painter_, const QWidget* widget_) const
{
    if(element_ == CE_TabBarTabLabel)
    {
        if(const QStyleOptionTab * _tab = qstyleoption_cast<const QStyleOptionTab*>(option_))
        {
            QStyleOptionTab _opt(*_tab);
            _opt.shape = QTabBar::RoundedNorth;
            QProxyStyle::drawControl(element_, &_opt, painter_, widget_);
            return;
        }
    }
    QProxyStyle::drawControl(element_, option_, painter_, widget_);
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** WidgetSettings ***

WidgetSettings::WidgetSettings(const QModelIndex & index_) :
    _m_index(index_)
{
    setTabPosition(QTabWidget::West);

    tabBar()->setStyle(new CustomTabStyle);
}

WidgetSettings::eDeviceType WidgetSettings::assignType(const QDomNode &node_)
{
    auto _type = node_.toElement().attribute("type").toShort();

    switch(_type)
    {
    case 1: return WidgetSettings::eDT_CANbus; break;
    case 2: return WidgetSettings::eDT_CANopen_manager; break;
    case 3: return WidgetSettings::eDT_CANopen_device; break;
    case 4: return WidgetSettings::eDT_CANopen_remote_device; break;
    default: return WidgetSettings::eDT_Unknown; break;
    }

    return WidgetSettings::eDT_Unknown;
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** WidgetSettings_CANbus ***

WidgetSettings_CANbus::WidgetSettings_CANbus(const QModelIndex & index_) :
    WidgetSettings(index_)
{
    addTab(new QLabel(tr("CANbus - General")), tr("General"));
    addTab(new QLabel(tr("CANbus - Log")), tr("Log"));
    addTab(new QLabel(tr("CANbus - CANbus IEC Objects")), tr("CANbus IEC Objects"));
    addTab(new QLabel(tr("CANbus - Status")), tr("Status"));
    addTab(new QLabel(tr("CANbus - Information")), tr("Information"));
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** WidgetSettings_CANopen_manager ***

WidgetSettings_CANopen_manager::WidgetSettings_CANopen_manager(const QModelIndex & index_) :
    WidgetSettings(index_)
{
    addTab(new QLabel(tr("CANopen manager - General")), tr("General"));
    addTab(new QLabel(tr("CANopen manager - Log")), tr("Log"));
    addTab(new QLabel(tr("CANopen manager - CANopen I/O Mapping")), tr("CANopen I/O Mapping"));
    addTab(new QLabel(tr("CANopen manager - CANopen IEC Objects")), tr("CANopen IEC Objects"));
    addTab(new QLabel(tr("CANopen manager - Status")), tr("Status"));
    addTab(new QLabel(tr("CANopen manager - Information")), tr("Information"));
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** WidgetSettings_CANopen_device ***

WidgetSettings_CANopen_device::WidgetSettings_CANopen_device(const QModelIndex & index_) :
    WidgetSettings(index_)
{
    addTab(new QLabel(tr("CANopen device - General")), tr("General"));
    addTab(new QLabel(tr("CANopen device - Object Dictionary")), tr("Object Dictionary"));
    addTab(new QLabel(tr("CANopen device - PDOs")), tr("PDOs"));
    addTab(new QLabel(tr("CANopen device - Log")), tr("Log"));
    addTab(new QLabel(tr("CANopen device - CANopen I/O Mapping")), tr("CANopen I/O Mapping"));
    addTab(new QLabel(tr("CANopen device - CANopen IEC Objects")), tr("CANopen IEC Objects"));
    addTab(new QLabel(tr("CANopen device - Status")), tr("Status"));
    addTab(new QLabel(tr("CANopen device - Information")), tr("Information"));
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** WidgetSettings_CANopen_remote_device ***

WidgetSettings_CANopen_remote_device::WidgetSettings_CANopen_remote_device(const QModelIndex & index_) :
    WidgetSettings(index_)
{
    addTab(new QLabel(tr("CANopen remote device - General")), tr("General"));
    addTab(new QLabel(tr("CANopen remote device - PDOs")), tr("PDOs"));
    addTab(new QLabel(tr("CANopen remote device - SDOs")), tr("SDOs"));
    addTab(new QLabel(tr("CANopen remote device - Log")), tr("Log"));
    addTab(new QLabel(tr("CANopen remote device - CANopen I/O Mapping")), tr("CANopen I/O Mapping"));
    addTab(new QLabel(tr("CANopen remote device - CANopen IEC Objects")), tr("CANopen IEC Objects"));
    addTab(new QLabel(tr("CANopen remote device - Status")), tr("Status"));
    addTab(new QLabel(tr("CANopen remote device - Information")), tr("Information"));
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** WidgetSettings_creator_CANbus ***

WidgetSettings * WidgetSettings_creator_CANbus::create(const QModelIndex & index_)
{
    return new WidgetSettings_CANbus(index_);
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** WidgetSettings_creator_CANopen_manager ***

WidgetSettings * WidgetSettings_creator_CANopen_manager::create(const QModelIndex & index_)
{
    return new WidgetSettings_CANopen_manager(index_);
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** WidgetSettings_creator_CANopen_device ***

WidgetSettings * WidgetSettings_creator_CANopen_device::create(const QModelIndex & index_)
{
    return new WidgetSettings_CANopen_device(index_);
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** WidgetSettings_creator_CANopen_remote_device ***

WidgetSettings * WidgetSettings_creator_CANopen_remote_device::create(const QModelIndex & index_)
{
    return new WidgetSettings_CANopen_remote_device(index_);
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** WidgetSettings_builder ***

WidgetSettings_builder::WidgetSettings_builder()
{
    m_creators.insert(WidgetSettings::eDT_CANbus, new WidgetSettings_creator_CANbus);
    m_creators.insert(WidgetSettings::eDT_CANopen_manager, new WidgetSettings_creator_CANopen_manager);
    m_creators.insert(WidgetSettings::eDT_CANopen_device, new WidgetSettings_creator_CANopen_device);
    m_creators.insert(WidgetSettings::eDT_CANopen_remote_device, new WidgetSettings_creator_CANopen_remote_device);
}

WidgetSettings_builder::~WidgetSettings_builder()
{
    for(const auto & creator : std::as_const(m_creators))
        delete creator;
}

WidgetSettings * WidgetSettings_builder::build(const QModelIndex & index_)
{
    if(!index_.isValid())
        return nullptr;

    auto _item = DomModel::toItem(index_, true);
    Q_ASSERT(_item);

    auto type = WidgetSettings::assignType(_item->node());

    if(m_creators.contains(type))
        return m_creators.value(type)->create(index_);

    return nullptr;
}

// ----------------------------------------------------------------------------
