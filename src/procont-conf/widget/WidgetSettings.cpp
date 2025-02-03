#include "WidgetSettings.h"

#include "model/DomModel.h"
#include "item/DomItem.h"
#include "view/Section.h"

#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QCheckBox>
#include <QComboBox>
#include <QLineEdit>
#include <QFormLayout>

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
// *** LogViewer ***

#include <QToolBar>
#include <QTreeView>
#include <QSortFilterProxyModel>
#include <QApplication>

LogViewer::LogViewer()
{
    auto _toolbar = new QToolBar;
    _toolbar->setIconSize(QSize(24, 24));
    _toolbar->addAction(new QAction(QIcon(":/icon/images/arrow-2-up-top.svg"), tr("Load the newest log entries and activate auto scrolling")));
    _toolbar->addAction(new QAction(QIcon(":/icon/images/arrow-5-up.svg"), tr("Load the next log page with newer entries")));
    _toolbar->addAction(new QAction(QIcon(":/icon/images/arrow-5-down.svg"), tr("Load the previous log page with older entries")));
    _toolbar->addAction(new QAction(QIcon(":/icon/images/arrow-2-down-bottom.svg"), tr("Load the log page with the oldest log entries")));
    _toolbar->addSeparator();
    auto _action = new QAction(qApp->style()->standardIcon(QStyle::SP_MessageBoxCritical), tr("0 error(s)")); _action->setCheckable(true);
    auto _button = new QToolButton; _button->setToolButtonStyle(Qt::ToolButtonTextBesideIcon); _button->setDefaultAction(_action);
    _toolbar->addWidget(_button);
    _action = new QAction(qApp->style()->standardIcon(QStyle::SP_MessageBoxWarning), tr("0 warning(s)")); _action->setCheckable(true);
    _button = new QToolButton; _button->setToolButtonStyle(Qt::ToolButtonTextBesideIcon); _button->setDefaultAction(_action);
    _toolbar->addWidget(_button);
    _action = new QAction(qApp->style()->standardIcon(QStyle::SP_MessageBoxInformation), tr("0 information(s)")); _action->setCheckable(true);
    _button = new QToolButton; _button->setToolButtonStyle(Qt::ToolButtonTextBesideIcon); _button->setDefaultAction(_action);
    _toolbar->addWidget(_button);
    _toolbar->addSeparator();
    auto _lineedit = new QLineEdit;
    _lineedit->setMinimumWidth(250);
    _lineedit->setPlaceholderText(tr("Search in messages"));
    _toolbar->addWidget(_lineedit);
    _toolbar->addAction(new QAction(QIcon(":/icon/images/find-up.svg"), tr("")));
    _toolbar->addAction(new QAction(QIcon(":/icon/images/find-down.svg"), tr("")));
    _toolbar->addSeparator();
    _toolbar->addWidget(new QCheckBox(tr("UTC Time")));
    _toolbar->addSeparator();
    _toolbar->addAction(new QAction(QIcon(":/icon/images/import-1.svg"), tr("Import entries via existing XML file")));
    _toolbar->addAction(new QAction(QIcon(":/icon/images/export-1.svg"), tr("Export the displayed entries to a XML file")));

    auto _model = new QStandardItemModel;
    _model->setColumnCount(4);
    _model->setHeaderData(0, Qt::Horizontal, tr("Severity"));
    _model->setHeaderData(1, Qt::Horizontal, tr("Time Stamp"));
    _model->setHeaderData(2, Qt::Horizontal, tr("Description"));
    _model->setHeaderData(3, Qt::Horizontal, tr("Component"));
    auto _proxy = new QSortFilterProxyModel;
    _proxy->setSourceModel(_model);
    auto _listview = new QTreeView;
    _listview->setEditTriggers(QAbstractItemView::NoEditTriggers);
    _listview->setModel(_proxy);

    auto _layout = new QVBoxLayout;
    _layout->addWidget(_toolbar);
    _layout->addWidget(_listview);

    setLayout(_layout);
}
// ----------------------------------------------------------------------------


// ----------------------------------------------------------------------------
// *** IOMapping ***

#include <QGroupBox>

IOMapping_default::IOMapping_default() :
    IOMapping()
{
    createContent();
}

void IOMapping_default::createContent()
{
    auto _combobox = new QComboBox;
    _combobox->addItems(QStringList() << "Use parrent bus cycle setting");
    _combobox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    auto _layout_group = new QFormLayout;
    _layout_group->addRow(new QLabel(tr("Bus cycle task")), _combobox);

    auto _group = new QGroupBox(tr("Bus Cycle Options"));
    _group->setLayout(_layout_group);
    _group->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    auto _layout = new QHBoxLayout;
    _layout->addWidget(_group, Qt::AlignTop);
    _layout->addWidget(new QPushButton(tr("Recreate required tasks")));
    _layout->addStretch();

    auto _l = new QVBoxLayout;
    _l->addLayout(_layout);
    _l->addStretch();

    setLayout(_l);
}

IOMapping_CANopen_remote_device::IOMapping_CANopen_remote_device() :
    IOMapping()
{
    createContent();
}

void IOMapping_CANopen_remote_device::createContent()
{
    auto _toolbar = new QToolBar;
    _toolbar->setIconSize(QSize(24, 24));
    _toolbar->setContentsMargins(0, 0, 100, 0);
    _toolbar->addWidget(new QLabel(tr("Find")));
    _toolbar->addWidget(new QLabel(tr("  ")));
    auto _lineedit = new QLineEdit;
    _lineedit->setMinimumWidth(250);
    _lineedit->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    _toolbar->addWidget(_lineedit);
    _toolbar->addWidget(new QLabel(tr("  ")));
    _toolbar->addWidget(new QLabel(tr("Filter")));
    _toolbar->addWidget(new QLabel(tr("  ")));
    auto _combobox = new QComboBox;
    _combobox->addItems(QStringList() << tr("Show all") << tr("Show only inputs") << tr("Show only mapped variables") << tr("Show only mapping to existing variables")
                                      << tr("Show only mapping to new variables") << tr("Show only outputs") << tr("Show only unmapped variables"));
    _combobox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    _toolbar->addWidget(_combobox);
    _toolbar->addWidget(new QLabel(tr("  ")));
    auto _action = new QAction(QIcon(":/icon/images/plus2.svg"), tr("Add FB for IO channel..."));
    _toolbar->addAction(_action);
    // auto _button = new QToolButton; _button->setToolButtonStyle(Qt::ToolButtonTextBesideIcon); _button->setDefaultAction(_action);
    // _toolbar->addWidget(_button);
    _action = new QAction(QIcon(":/icon/images/arrow-right.svg"), tr("Go to instance"));
    _toolbar->addAction(_action);
    // _button = new QToolButton; _button->setToolButtonStyle(Qt::ToolButtonTextBesideIcon); _button->setDefaultAction(_action);
    // _toolbar->addWidget(_button);

    auto _model = new QStandardItemModel;
    _model->setColumnCount(7);
    _model->setHeaderData(0, Qt::Horizontal, tr("Variable"));
    _model->setHeaderData(1, Qt::Horizontal, tr("Mapping"));
    _model->setHeaderData(2, Qt::Horizontal, tr("Channel"));
    _model->setHeaderData(3, Qt::Horizontal, tr("Address"));
    _model->setHeaderData(4, Qt::Horizontal, tr("Type"));
    _model->setHeaderData(5, Qt::Horizontal, tr("Unit"));
    _model->setHeaderData(6, Qt::Horizontal, tr("Description"));
    auto _proxy = new QSortFilterProxyModel;
    _proxy->setSourceModel(_model);
    auto _listview = new QTreeView;
    _listview->setEditTriggers(QAbstractItemView::NoEditTriggers);
    _listview->setModel(_proxy);

    _lineedit = new QLineEdit;
    _lineedit->setMinimumWidth(350);
    auto _pushbutton = new QPushButton(tr("Reset mapping"));
    _pushbutton->setMinimumWidth(200);
    _pushbutton->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    _combobox = new QComboBox;
    _combobox->addItems(QStringList() << tr("Use parent device setting"));
    auto _layout_combo = new QFormLayout;
    _layout_combo->addRow(new QLabel(tr("Always update variables")), _combobox);
    auto _layout_bottom = new QHBoxLayout;
    _layout_bottom->addWidget(_lineedit);
    _layout_bottom->addWidget(_pushbutton);
    _layout_bottom->addLayout(_layout_combo);

    auto _layout = new QVBoxLayout;
    _layout->addWidget(_toolbar);
    _layout->addWidget(_listview);
    _layout->addLayout(_layout_bottom);

    setLayout(_layout);
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** PDO ***

#include <QToolBar>
#include <QTreeView>

PDO_widget::PDO_widget()
{
    auto _toolbar = new QToolBar;
    _toolbar->setIconSize(QSize(24, 24));
    _toolbar->addAction(new QAction(QIcon(":/icon/images/plus-large.svg"), tr("Add PDO")));
    _toolbar->addAction(new QAction(QIcon(":/icon/images/plus-large.svg"), tr("Add Mapping")));
    _toolbar->addAction(new QAction(QIcon(":/icon/images/edit-1.svg"), tr("Edit")));
    _toolbar->addAction(new QAction(QIcon(":/icon/images/delete2.svg"), tr("Delete")));
    _toolbar->addAction(new QAction(QIcon(":/icon/images/arrow-5-up.svg"), tr("Move up")));
    _toolbar->addAction(new QAction(QIcon(":/icon/images/arrow-5-down.svg"), tr("Mode down")));
    // _toolbar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    auto _model = new QStandardItemModel;
    _model->setColumnCount(3);
    _model->setHeaderData(0, Qt::Horizontal, tr("Name"));
    _model->setHeaderData(1, Qt::Horizontal, tr("Object"));
    _model->setHeaderData(2, Qt::Horizontal, tr("Bit length"));
    auto _proxy = new QSortFilterProxyModel;
    _proxy->setSourceModel(_model);
    auto _listview = new QTreeView;
    _listview->setEditTriggers(QAbstractItemView::NoEditTriggers);
    _listview->setModel(_proxy);

    auto _layout = new QVBoxLayout;
    _layout->setSpacing(0);
    _layout->setContentsMargins(0, 0, 0, 0);
    _layout->addWidget(_toolbar);
    _layout->addWidget(_listview);

    setLayout(_layout);
}

PDO::PDO()
{
    auto _layout = new QHBoxLayout;

    auto _group = new QGroupBox(tr("Receive PDOs (Master => Slave)"));
    _group->setContentsMargins(0, 0, 0, 0);
    auto _layout_group = new QVBoxLayout;
    _layout_group->setSpacing(0);
    _layout_group->setContentsMargins(2, 2, 2, 2);
    _layout_group->addWidget(new PDO_widget);
    _group->setLayout(_layout_group);

    _layout->addWidget(_group);

    _group = new QGroupBox(tr("Transmit PDOs (Slave => Master)"));
    _layout_group = new QVBoxLayout;
    _layout_group->setSpacing(0);
    _layout_group->setContentsMargins(2, 2, 2, 2);
    _layout_group->addWidget(new PDO_widget);
    _group->setLayout(_layout_group);

    _layout->addWidget(_group);
    _layout->setSpacing(0);

    setLayout(_layout);
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** SDO ***

#include <QToolBar>
#include <QTreeView>
#include <QSortFilterProxyModel>

SDO::SDO()
{
    auto _toolbar = new QToolBar;
    _toolbar->setIconSize(QSize(24, 24));
    _toolbar->addAction(new QAction(QIcon(":/icon/images/plus-large.svg"), tr("Add SDO")));
    _toolbar->addAction(new QAction(QIcon(":/icon/images/edit-1.svg"), tr("Edit")));
    _toolbar->addAction(new QAction(QIcon(":/icon/images/delete2.svg"), tr("Delete")));
    _toolbar->addAction(new QAction(QIcon(":/icon/images/arrow-5-up.svg"), tr("Move up")));
    _toolbar->addAction(new QAction(QIcon(":/icon/images/arrow-5-down.svg"), tr("Mode down")));
    // _toolbar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    auto _model = new QStandardItemModel;
    _model->setColumnCount(9);
    _model->setHeaderData(0, Qt::Horizontal, tr("Line"));
    _model->setHeaderData(1, Qt::Horizontal, tr("Index:Subindex"));
    _model->setHeaderData(2, Qt::Horizontal, tr("Name"));
    _model->setHeaderData(3, Qt::Horizontal, tr("Value"));
    _model->setHeaderData(4, Qt::Horizontal, tr("Bit length"));
    _model->setHeaderData(5, Qt::Horizontal, tr("Abort on error"));
    _model->setHeaderData(6, Qt::Horizontal, tr("Jump to line if error"));
    _model->setHeaderData(7, Qt::Horizontal, tr("Next line"));
    _model->setHeaderData(8, Qt::Horizontal, tr("Comment"));
    auto _proxy = new QSortFilterProxyModel;
    _proxy->setSourceModel(_model);
    auto _listview = new QTreeView;
    _listview->setEditTriggers(QAbstractItemView::NoEditTriggers);
    _listview->setModel(_proxy);

    auto _spinbox = new QSpinBox;
    _spinbox->setFixedWidth(100);
    auto _layout_form = new QFormLayout;
    _layout_form->addRow(new QLabel(tr("SDO timeout (ms)")), _spinbox);

    auto _layout_h = new QHBoxLayout;
    // _layout_h->addSpacing(5);
    _layout_h->addLayout(_layout_form);
    _layout_h->addWidget(new QCheckBox(tr("Create all SDOs")));
    _layout_h->addWidget(new QCheckBox(tr("Write complite PDO configuration")));
    _layout_h->addStretch();

    auto _layout = new QVBoxLayout;
    // _layout->setSpacing(0);
    // _layout->setContentsMargins(0, 0, 0, 0);
    _layout->addWidget(_toolbar);
    _layout->addWidget(_listview);
    _layout->addLayout(_layout_h);

    setLayout(_layout);
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** ObjectDictionary ***

#include <QToolBar>
#include <QTreeView>
#include <QSortFilterProxyModel>
#include <QHeaderView>
#include <QSplitter>

ObjectDictionary::ObjectDictionary()
{
    auto _toolbar = new QToolBar;
    _toolbar->setIconSize(QSize(24, 24));
    _toolbar->addAction(new QAction(QIcon(":/icon/images/plus-large.svg"), tr("Add object")));
    _toolbar->addAction(new QAction(QIcon(":/icon/images/plus-large.svg"), tr("Add subobject")));
    _toolbar->addAction(new QAction(QIcon(":/icon/images/delete2.svg"), tr("Delete")));
    _toolbar->addAction(new QAction(QIcon(":/icon/images/clone.svg"), tr("Clone")));
    _toolbar->addAction(new QAction(QIcon(":/icon/images/import-2.svg"), tr("Export")));
    // _toolbar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    auto _model = new QStandardItemModel;
    _model->setColumnCount(6);
    _model->setHeaderData(0, Qt::Horizontal, tr("Index"));
    _model->setHeaderData(1, Qt::Horizontal, tr("Name"));
    _model->setHeaderData(2, Qt::Horizontal, tr("Data type"));
    _model->setHeaderData(3, Qt::Horizontal, tr("Default value"));
    _model->setHeaderData(4, Qt::Horizontal, tr("Access type"));
    _model->setHeaderData(5, Qt::Horizontal, tr("Variable mapping"));
    auto _proxy = new QSortFilterProxyModel;
    _proxy->setSourceModel(_model);
    auto _listview = new QTreeView;
    _listview->setEditTriggers(QAbstractItemView::NoEditTriggers);
    _listview->setModel(_proxy);

    auto _toolbar_properties = new QToolBar;
    _toolbar_properties->setIconSize(QSize(16, 16));
    _toolbar_properties->addAction(new QAction(QIcon(":/icon/images/category-1.svg"), tr("Categorized")));
    _toolbar_properties->addAction(new QAction(QIcon(":/icon/images/alphabet.svg"), tr("Alphabetical")));
    _toolbar_properties->addSeparator();
    _toolbar_properties->addAction(new QAction(QIcon(":/icon/images/config-2.svg"), tr("Property pages")));

    auto _model_properties = new QStandardItemModel;
    _model_properties->setColumnCount(2);
    auto _item_parent = new QStandardItem("Parent item 1");
    auto _items = QList<QStandardItem *>();
    _items << new QStandardItem("name1") << new QStandardItem("value1");
    _items << new QStandardItem("name2") << new QStandardItem("value2");
    _items << new QStandardItem("name3") << new QStandardItem("value3");
    _items << new QStandardItem("name4") << new QStandardItem("value4");
    _item_parent->insertRow(0, _items);
    _model_properties->insertRow(0, _item_parent);
    _item_parent = new QStandardItem("Parent item 2");
    _items.clear();
    _items << new QStandardItem("name1") << new QStandardItem("value1");
    _items << new QStandardItem("name2") << new QStandardItem("value2");
    _items << new QStandardItem("name3") << new QStandardItem("value3");
    _items << new QStandardItem("name4") << new QStandardItem("value4");
    _item_parent->insertRow(0, _items);
    _model_properties->insertRow(0, _item_parent);
    // _model_properties->setHeaderData(0, Qt::Horizontal, tr("Name"));
    // _model_properties->setHeaderData(1, Qt::Horizontal, tr("Value"));
    auto _proxy_properties = new QSortFilterProxyModel;
    _proxy_properties->setSourceModel(_model_properties);
    auto _listview_properties = new QTreeView;
    _listview_properties->header()->hide();
    _listview_properties->setEditTriggers(QAbstractItemView::NoEditTriggers);
    _listview_properties->setModel(_proxy_properties);
    _listview_properties->expandAll();
    for(auto i = 0; i<_proxy_properties->columnCount();i++)
        _listview_properties->resizeColumnToContents(i);

    auto _layout_v = new QVBoxLayout;
    _layout_v->setSpacing(0);
    _layout_v->setContentsMargins(0, 0, 0, 0);
    _layout_v->addWidget(_toolbar_properties);
    _layout_v->addWidget(_listview_properties);

    auto _container = new QWidget;
    _container->setLayout(_layout_v);

    auto _splitter = new QSplitter;
    _splitter->addWidget(_listview);
    _splitter->addWidget(_container);

    auto _layout = new QVBoxLayout;
    // _layout->setSpacing(0);
    // _layout->setContentsMargins(0, 0, 0, 0);
    _layout->addWidget(_toolbar);
    _layout->addWidget(_splitter);

    setLayout(_layout);
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** WidgetSettings ***

WidgetSettings::WidgetSettings(const QModelIndex & index_) :
    _m_index(index_)
{
    setTabPosition(QTabWidget::West);

    tabBar()->setStyle(new CustomTabStyle);

    setStyleSheet("QTabBar::tab { min-width: 50px; }");
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
    auto _tab1 = new QScrollArea; _tab1->setWidget(createTab1());
    addTab(_tab1, tr("General"));
    addTab(new LogViewer, tr("Log"));
    addTab(new QLabel(tr("CANbus - CANbus IEC Objects")), tr("CANbus IEC Objects"));
    addTab(new QLabel(tr("CANbus - Status")), tr("Status"));
    addTab(new QLabel(tr("CANbus - Information")), tr("Information"));
}
QWidget * WidgetSettings_CANbus::createTab1()
{
    // *** section - General
    auto _section_general_spinbox_network = new QSpinBox;
    _section_general_spinbox_network->setFixedWidth(150);
    _section_general_spinbox_network->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    auto _section_general_combobox_rate = new QComboBox;
    _section_general_combobox_rate->addItems(QStringList() << "10" << "20" << "50" << "100" << "125" << "250" << "500" << "800" << "1000" << tr("Use current setting"));
    _section_general_combobox_rate->setCurrentText(tr("Use current setting"));
    _section_general_combobox_rate->setFixedWidth(200);
    _section_general_combobox_rate->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    auto _section_general_1_can_logo_label = new QLabel;
    auto _can_logo_pixmap = QPixmap(":/icon/images/can-2.svg");
    _section_general_1_can_logo_label->setPixmap(_can_logo_pixmap);
    _section_general_1_can_logo_label->setScaledContents(true);
    _section_general_1_can_logo_label->setFixedSize(240, 56);

    auto _section_general_layout = new QGridLayout;
    _section_general_layout->addWidget(new QLabel(tr("Network")), 0, 0, 1, 1);
    _section_general_layout->addWidget(_section_general_spinbox_network, 0, 1, 1, 1);
    _section_general_layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding), 0, 2, 1, 1);
    _section_general_layout->addWidget(new QLabel(tr("Baud rate (kbit/s)")), 1, 0, 1, 1);
    _section_general_layout->addWidget(_section_general_combobox_rate, 1, 1, 1, 1);
    _section_general_layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding), 1, 2, 1, 1);
    _section_general_layout->addWidget(_section_general_1_can_logo_label, 0, 3, 2, 1);

    Section* _section_general = new Section(tr("General"), true);
    _section_general->setContentLayout(*_section_general_layout);

    // *** layout
    auto _tab1_layout = new QGridLayout;
    _tab1_layout->addWidget(_section_general, 0, 0, 1, 2, Qt::AlignTop);
    _tab1_layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding), 1, 0, 1, 2, Qt::AlignTop);

    // *** container
    auto _tab1 = new QWidget;
    _tab1->setLayout(_tab1_layout);
    _tab1->setMinimumWidth(900);
    _tab1->setMinimumHeight(400);

    return _tab1;
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** WidgetSettings_CANopen_manager ***

WidgetSettings_CANopen_manager::WidgetSettings_CANopen_manager(const QModelIndex & index_) :
    WidgetSettings(index_)
{
    auto _tab1 = new QScrollArea; _tab1->setWidget(createTab1());
    addTab(_tab1, tr("General"));
    addTab(new LogViewer, tr("Log"));
    auto _tab3 = new IOMapping_default;
    // _tab3->setFixedSize(600, 100);
    addTab(_tab3, tr("CANopen I/O Mapping"));
    addTab(new QLabel(tr("CANopen manager - CANopen IEC Objects")), tr("CANopen IEC Objects"));
    addTab(new QLabel(tr("CANopen manager - Status")), tr("Status"));
    addTab(new QLabel(tr("CANopen manager - Information")), tr("Information"));
}

QWidget * WidgetSettings_CANopen_manager::createTab1()
{
    // *** section - General
    auto _section_general_spinbox_id = new QSpinBox;
    _section_general_spinbox_id->setFixedWidth(150);
    _section_general_spinbox_id->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    auto _section_general_1_canopen_logo_label = new QLabel;
    auto _canopen_logo_pixmap = QPixmap(":/icon/images/canopen-2.svg");
    _section_general_1_canopen_logo_label->setPixmap(_canopen_logo_pixmap);
    _section_general_1_canopen_logo_label->setScaledContents(true);
    _section_general_1_canopen_logo_label->setFixedSize(240, 56);

    auto _section_general_1_layout = new QGridLayout;
    _section_general_1_layout->addWidget(new QLabel(tr("Node ID")), 0, 0, 1, 1);
    _section_general_1_layout->addWidget(_section_general_spinbox_id, 0, 1, 1, 1);
    _section_general_1_layout->addWidget(new QPushButton(tr("Check and Fix Configuration...")), 0, 2, 1, 1);
    _section_general_1_layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding), 0, 3, 1, 1);
    _section_general_1_layout->addWidget(_section_general_1_canopen_logo_label, 0, 4, 2, 1);

    auto _section_general_2_layout = new QHBoxLayout;
    _section_general_2_layout->addWidget(new QCheckBox(tr("Autostart CANopen Manager")));
    _section_general_2_layout->addWidget(new QCheckBox(tr("Polling of optional slaves")));
    _section_general_2_layout->addStretch();

    auto _section_general_3_combobox = new QComboBox;
    _section_general_3_combobox->addItems(QStringList() << tr("Restart slave") << tr("Stop slave"));

    auto _section_general_3_layout = new QHBoxLayout;
    _section_general_3_layout->addWidget(new QCheckBox(tr("Start slaves")));
    _section_general_3_layout->addSpacerItem(new QSpacerItem(125, 0));
    _section_general_3_layout->addWidget(new QLabel(tr("NMT error bahavior")));
    _section_general_3_layout->addWidget(_section_general_3_combobox);
    _section_general_3_layout->addStretch();
    _section_general_3_layout->addSpacing(20);

    auto _section_general_4_layout = new QHBoxLayout;
    _section_general_4_layout->addSpacerItem(new QSpacerItem(25, 0));
    _section_general_4_layout->addWidget(new QCheckBox(tr("NMT start all (if possible)")));

    auto* _section_general_layout = new QVBoxLayout;
    _section_general_layout->addLayout(_section_general_1_layout);
    _section_general_layout->addLayout(_section_general_2_layout);
    _section_general_layout->addLayout(_section_general_3_layout);
    _section_general_layout->addLayout(_section_general_4_layout);

    Section* _section_general = new Section(tr("General"), true);
    _section_general->setContentLayout(*_section_general_layout);

    // *** section - Guarding

    auto _section_guarding_spinbox_id = new QSpinBox;
    _section_guarding_spinbox_id->setFixedWidth(150);
    _section_guarding_spinbox_id->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    auto _section_guarding_spinbox_time = new QSpinBox;
    _section_guarding_spinbox_time->setFixedWidth(150);
    _section_guarding_spinbox_time->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    auto* _section_guarding_layout = new QFormLayout;
    _section_guarding_layout->addRow(new QCheckBox(tr("Enable heartbeat producing")));
    _section_guarding_layout->addRow(new QLabel(tr("Node ID")), _section_guarding_spinbox_id);
    _section_guarding_layout->addRow(new QLabel(tr("Producer time (ms)")), _section_guarding_spinbox_time);

    Section* _section_guarding = new Section(tr("Guarding"), false);
    _section_guarding->setContentLayout(*_section_guarding_layout);

    // *** section - SYNC

    auto _section_sync_spinbox_id = new QSpinBox;
    _section_sync_spinbox_id->setFixedWidth(150);
    _section_sync_spinbox_id->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    auto _section_sync_spinbox_period = new QSpinBox;
    _section_sync_spinbox_period->setFixedWidth(150);
    _section_sync_spinbox_period->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    auto _section_sync_spinbox_length = new QSpinBox;
    _section_sync_spinbox_length->setFixedWidth(150);
    _section_sync_spinbox_length->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    auto* _section_sync_layout = new QFormLayout;
    _section_sync_layout->addRow(new QCheckBox(tr("Enable SYNC producing")));
    _section_sync_layout->addRow(new QLabel(tr("COB ID (Hex)     16#")), _section_sync_spinbox_id);
    _section_sync_layout->addRow(new QLabel(tr("Cycle period (us)")), _section_sync_spinbox_period);
    _section_sync_layout->addRow(new QLabel(tr("Window length (us)")), _section_sync_spinbox_length);
    _section_sync_layout->addRow(new QCheckBox(tr("Enable SYNC consuming")));

    Section* _section_sync = new Section(tr("SYNC"), false);
    _section_sync->setContentLayout(*_section_sync_layout);

    // *** section - TIME

    auto _section_time_spinbox_id = new QSpinBox;
    _section_time_spinbox_id->setFixedWidth(150);
    _section_time_spinbox_id->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    auto _section_sync_spinbox_time = new QSpinBox;
    _section_sync_spinbox_time->setFixedWidth(150);
    _section_sync_spinbox_time->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    auto* _section_time_layout = new QFormLayout;
    _section_time_layout->addRow(new QCheckBox(tr("Enable TIME producing")));
    _section_time_layout->addRow(new QLabel(tr("COB ID (Hex)     16#")), _section_time_spinbox_id);
    _section_time_layout->addRow(new QLabel(tr("Producer time (ms)")), _section_sync_spinbox_time);

    Section* _section_time = new Section(tr("TIME"), false);
    _section_time->setContentLayout(*_section_time_layout);

    // *** layout
    auto _tab1_layout = new QGridLayout;
    _tab1_layout->addWidget(_section_general, 0, 0, 1, 2, Qt::AlignTop);
    _tab1_layout->addWidget(_section_guarding, 1, 0, 1, 2, Qt::AlignTop);
    _tab1_layout->addWidget(_section_sync, 2, 0, 1, 1, Qt::AlignTop);
    _tab1_layout->addWidget(_section_time, 2, 1, 1, 1, Qt::AlignTop);
    _tab1_layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding), 3, 0, 1, 2, Qt::AlignTop);

    // *** container
    auto _tab1 = new QWidget;
    _tab1->setLayout(_tab1_layout);
    _tab1->setMinimumWidth(900);
    _tab1->setMinimumHeight(600);

    return _tab1;
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** WidgetSettings_CANopen_local_device ***

WidgetSettings_CANopen_local_device::WidgetSettings_CANopen_local_device(const QModelIndex & index_) :
    WidgetSettings(index_)
{
    auto _tab1 = new QScrollArea; _tab1->setWidget(createTab1());
    addTab(_tab1, tr("General"));
    addTab(new ObjectDictionary, tr("Object Dictionary"));
    addTab(new PDO, tr("PDOs"));
    addTab(new LogViewer, tr("Log"));
    auto _tab5 = new IOMapping_default;
    // _tab5->setFixedSize(600, 100);
    addTab(_tab5, tr("CANopen I/O Mapping"));
    addTab(new QLabel(tr("CANopen device - CANopen IEC Objects")), tr("CANopen IEC Objects"));
    addTab(new QLabel(tr("CANopen device - Status")), tr("Status"));
    addTab(new QLabel(tr("CANopen device - Information")), tr("Information"));
}

QWidget * WidgetSettings_CANopen_local_device::createTab1()
{
    // *** section - General
    auto _section_general_1_canopen_logo_label = new QLabel;
    auto _canopen_logo_pixmap = QPixmap(":/icon/images/canopen-2.svg");
    _section_general_1_canopen_logo_label->setPixmap(_canopen_logo_pixmap);
    _section_general_1_canopen_logo_label->setScaledContents(true);
    _section_general_1_canopen_logo_label->setFixedSize(240, 56);

    auto _section_general_spinbox_id = new QSpinBox;
    _section_general_spinbox_id->setFixedWidth(150);
    _section_general_spinbox_id->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    auto _section_general_spinbox_profile = new QSpinBox;
    _section_general_spinbox_profile->setFixedWidth(150);
    _section_general_spinbox_profile->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    auto _section_general_1_layout = new QGridLayout;
    _section_general_1_layout->addWidget(new QLabel(tr("Node ID")), 0, 0, 1, 1);
    _section_general_1_layout->addWidget(_section_general_spinbox_id, 0, 1, 1, 1);
    _section_general_1_layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding), 0, 2, 1, 1);
    _section_general_1_layout->addWidget(new QLabel(tr("Device profile")), 1, 0, 1, 1);
    _section_general_1_layout->addWidget(_section_general_spinbox_profile, 1, 1, 1, 1);
    _section_general_1_layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding), 1, 2, 1, 1);
    _section_general_1_layout->addWidget(_section_general_1_canopen_logo_label, 0, 3, 2, 1);

    auto _section_general_pushbutton_io = new QPushButton(tr("Edit I/O Area..."));
    _section_general_pushbutton_io->setMinimumWidth(225);

    auto _section_general_pushbutton_sd = new QPushButton(tr("Edit SDO Parameter Area..."));
    _section_general_pushbutton_sd->setMinimumWidth(225);

    auto _section_general_2_layout = new QHBoxLayout;
    _section_general_2_layout->addWidget(_section_general_pushbutton_io);
    _section_general_2_layout->addWidget(_section_general_pushbutton_sd);
    _section_general_2_layout->addStretch();

    auto* _section_general_layout = new QVBoxLayout;
    _section_general_layout->addLayout(_section_general_1_layout);
    _section_general_layout->addLayout(_section_general_2_layout);

    Section* _section_general = new Section(tr("General"), true);
    _section_general->setContentLayout(*_section_general_layout);

    // *** section - EDS File

    auto _section_guarding_editline_vendor_name = new QLineEdit;
    _section_guarding_editline_vendor_name->setFixedWidth(350);
    _section_guarding_editline_vendor_name->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    auto _section_guarding_spinbox_vendor_number = new QSpinBox;
    _section_guarding_spinbox_vendor_number->setFixedWidth(150);
    _section_guarding_spinbox_vendor_number->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    auto _section_guarding_editline_product_name = new QLineEdit;
    _section_guarding_editline_product_name->setFixedWidth(350);
    _section_guarding_editline_product_name->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    auto _section_guarding_spinbox_product_number = new QSpinBox;
    _section_guarding_spinbox_product_number->setFixedWidth(150);
    _section_guarding_spinbox_product_number->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    auto _section_guarding_spinbox_revision_number = new QSpinBox;
    _section_guarding_spinbox_revision_number->setFixedWidth(150);
    _section_guarding_spinbox_revision_number->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    auto* _section_guarding_1_layout = new QFormLayout;
    _section_guarding_1_layout->addRow(new QLabel(tr("Vendor name")), _section_guarding_editline_vendor_name);
    _section_guarding_1_layout->addRow(new QLabel(tr("Vendor number")), _section_guarding_spinbox_vendor_number);
    _section_guarding_1_layout->addRow(new QLabel(tr("Product name")), _section_guarding_editline_product_name);
    _section_guarding_1_layout->addRow(new QLabel(tr("Product number")), _section_guarding_spinbox_product_number);
    _section_guarding_1_layout->addRow(new QLabel(tr("Revision number")), _section_guarding_spinbox_revision_number);

    auto _section_eds_pushbutton_io = new QPushButton(tr("Install to Device Repository"));
    _section_eds_pushbutton_io->setMinimumWidth(225);

    auto _section_eds_pushbutton_sd = new QPushButton(tr("Export EDS File..."));
    _section_eds_pushbutton_sd->setMinimumWidth(225);

    auto _section_guarding_2_layout = new QHBoxLayout;
    _section_guarding_2_layout->addWidget(_section_eds_pushbutton_io);
    _section_guarding_2_layout->addWidget(_section_eds_pushbutton_sd);
    _section_guarding_2_layout->addStretch();

    auto* _section_guarding_layout = new QVBoxLayout;
    _section_guarding_layout->addLayout(_section_guarding_1_layout);
    _section_guarding_layout->addLayout(_section_guarding_2_layout);

    Section* _section_guarding = new Section(tr("EDS File"), false);
    _section_guarding->setContentLayout(*_section_guarding_layout);

    // *** layout
    auto _tab1_layout = new QGridLayout;
    _tab1_layout->addWidget(_section_general, 0, 0, 1, 1, Qt::AlignTop);
    _tab1_layout->addWidget(_section_guarding, 1, 0, 1, 1, Qt::AlignTop);
    _tab1_layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding), 2, 0, 1, 1, Qt::AlignTop);

    // *** container
    auto _tab1 = new QWidget;
    _tab1->setLayout(_tab1_layout);
    _tab1->setMinimumWidth(900);
    _tab1->setMinimumHeight(500);

    return _tab1;
}
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// *** WidgetSettings_CANopen_remote_device ***

WidgetSettings_CANopen_remote_device::WidgetSettings_CANopen_remote_device(const QModelIndex & index_) :
    WidgetSettings(index_)
{
    auto _tab1 = new QScrollArea; _tab1->setWidget(createTab1());
    addTab(_tab1, tr("General"));
    addTab(new PDO, tr("PDOs"));
    addTab(new SDO, tr("SDOs"));
    addTab(new LogViewer, tr("Log"));
    auto _tab3 = new IOMapping_CANopen_remote_device;
    addTab(_tab3, tr("CANopen I/O Mapping"));
    addTab(new QLabel(tr("CANopen remote device - CANopen IEC Objects")), tr("CANopen IEC Objects"));
    addTab(new QLabel(tr("CANopen remote device - Status")), tr("Status"));
    addTab(new QLabel(tr("CANopen remote device - Information")), tr("Information"));
}

QWidget * WidgetSettings_CANopen_remote_device::createTab1()
{
    // *** section - General
    auto _section_general_1_canopen_logo_label = new QLabel;
    auto _canopen_logo_pixmap = QPixmap(":/icon/images/canopen-2.svg");
    _section_general_1_canopen_logo_label->setPixmap(_canopen_logo_pixmap);
    _section_general_1_canopen_logo_label->setScaledContents(true);
    _section_general_1_canopen_logo_label->setFixedSize(240, 56);

    auto _section_general_spinbox_id = new QSpinBox;
    _section_general_spinbox_id->setFixedWidth(150);
    _section_general_spinbox_id->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    auto _section_general_pushbutton_sdo = new QPushButton(tr("SDO Channels (1/1 Active)"));
    _section_general_pushbutton_sdo->setFixedWidth(250);
    _section_general_spinbox_id->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    auto _section_general_combobox_id = new QComboBox;
    _section_general_combobox_id->setFixedWidth(150);
    _section_general_combobox_id->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    auto _section_general_1_layout = new QGridLayout;
    _section_general_1_layout->addWidget(new QLabel(tr("Node ID")), 0, 0, 1, 1);
    _section_general_1_layout->addWidget(_section_general_spinbox_id, 0, 1, 1, 1);
    _section_general_1_layout->addWidget(_section_general_pushbutton_sdo, 0, 2, 1, 1);
    _section_general_1_layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding), 0, 3, 1, 1);
    _section_general_1_layout->addWidget(_section_general_1_canopen_logo_label, 0, 4, 2, 1);

    auto _section_general_2_layout = new QGridLayout;
    _section_general_2_layout->addWidget(new QCheckBox(tr("Enable expert settings")), 0, 0, 1, 1);
    _section_general_2_layout->addWidget(new QCheckBox(tr("Enable SYNC producing")), 1, 0, 1, 1);
    _section_general_2_layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding), 0, 3, 1, 1);
    _section_general_2_layout->addWidget(new QCheckBox(tr("Optional device")), 0, 1, 1, 1);
    _section_general_2_layout->addWidget(new QCheckBox(tr("No initialization")), 1, 1, 1, 1);
    _section_general_2_layout->addWidget(new QCheckBox(tr("Reset node")), 1, 2, 1, 1);
    _section_general_2_layout->addWidget(_section_general_combobox_id, 1, 3, 1, 1);
    _section_general_2_layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding), 1, 3, 1, 1);

    auto* _section_general_layout = new QVBoxLayout;
    _section_general_layout->addLayout(_section_general_1_layout);
    _section_general_layout->addLayout(_section_general_2_layout);

    Section* _section_general = new Section(tr("General"), true);
    _section_general->setContentLayout(*_section_general_layout);

    // *** section - Guarding

    auto _section_guarding_spinbox_guard_time = new QSpinBox;
    _section_guarding_spinbox_guard_time->setFixedWidth(150);
    _section_guarding_spinbox_guard_time->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    auto _section_guarding_spinbox_factor = new QSpinBox;
    _section_guarding_spinbox_factor->setFixedWidth(150);
    _section_guarding_spinbox_factor->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    auto _section_guarding_spinbox_producer_time = new QSpinBox;
    _section_guarding_spinbox_producer_time->setFixedWidth(150);
    _section_guarding_spinbox_producer_time->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    auto _section_general_pushbutton_heartbeat = new QPushButton(tr("SDO Channels (1/1 Active)"));
    _section_general_pushbutton_heartbeat->setFixedWidth(250);
    _section_general_pushbutton_heartbeat->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    auto _section_guarding_1_layout = new QFormLayout;
    _section_guarding_1_layout->addRow(new QCheckBox(tr("Enable nodeguarding")));
    _section_guarding_1_layout->addRow(new QLabel(tr("Guard time (ms)")), _section_guarding_spinbox_guard_time);
    _section_guarding_1_layout->addRow(new QLabel(tr("Life time factor (ms)")), _section_guarding_spinbox_guard_time);

    auto _section_guarding_2_layout = new QFormLayout;
    _section_guarding_2_layout->addRow(new QCheckBox(tr("Enable heartbeat producing")));
    _section_guarding_2_layout->addRow(new QLabel(tr("Producer time (ms)")), _section_guarding_spinbox_producer_time);
    _section_guarding_2_layout->addRow(_section_general_pushbutton_heartbeat);

    auto* _section_guarding_layout = new QHBoxLayout;
    _section_guarding_layout->addLayout(_section_guarding_1_layout);
    _section_guarding_layout->addLayout(_section_guarding_2_layout);

    Section* _section_guarding = new Section(tr("Guarding"), false);
    _section_guarding->setContentLayout(*_section_guarding_layout);

    // *** section - Emergency

    auto _section_sync_spinbox_emergency = new QSpinBox;
    _section_sync_spinbox_emergency->setFixedWidth(150);
    _section_sync_spinbox_emergency->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    auto* _section_sync_layout = new QFormLayout;
    _section_sync_layout->addRow(new QCheckBox(tr("Enable emergency (EMCY)")));
    _section_sync_layout->addRow(new QLabel(tr("COB ID")), _section_sync_spinbox_emergency);

    Section* _section_sync = new Section(tr("Emergency (EMCY)"), false);
    _section_sync->setContentLayout(*_section_sync_layout);

    // *** section - TIME

    auto _section_time_spinbox_id = new QSpinBox;
    _section_time_spinbox_id->setFixedWidth(150);
    _section_time_spinbox_id->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    auto _section_sync_spinbox_time = new QSpinBox;
    _section_sync_spinbox_time->setFixedWidth(150);
    _section_sync_spinbox_time->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    auto* _section_time_layout = new QFormLayout;
    _section_time_layout->addRow(new QCheckBox(tr("Enable TIME producing")));
    _section_time_layout->addRow(new QLabel(tr("COB ID (Hex)     16#")), _section_time_spinbox_id);
    _section_time_layout->addRow(new QLabel(tr("Producer time (ms)")), _section_sync_spinbox_time);
    _section_time_layout->addRow(new QCheckBox(tr("Enable TIME consuming")));

    Section* _section_time = new Section(tr("TIME"), false);
    _section_time->setContentLayout(*_section_time_layout);

    // *** section - Checks

    auto* _section_ckeck_layout = new QHBoxLayout;
    _section_ckeck_layout->addWidget(new QCheckBox(tr("Check vendor ID")));
    _section_ckeck_layout->addWidget(new QCheckBox(tr("Check product number")));
    _section_ckeck_layout->addWidget(new QCheckBox(tr("Check revision number")));
    _section_ckeck_layout->addStretch();

    Section* _section_check = new Section(tr("Checks at Startup"), false);
    _section_check->setContentLayout(*_section_ckeck_layout);

    // *** layout
    auto _tab1_layout = new QGridLayout;
    _tab1_layout->addWidget(_section_general, 0, 0, 1, 2, Qt::AlignTop);
    _tab1_layout->addWidget(_section_guarding, 1, 0, 1, 2, Qt::AlignTop);
    _tab1_layout->addWidget(_section_sync, 2, 0, 1, 1, Qt::AlignTop);
    _tab1_layout->addWidget(_section_time, 2, 1, 1, 1, Qt::AlignTop);
    _tab1_layout->addWidget(_section_check, 3, 0, 1, 2, Qt::AlignTop);
    _tab1_layout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding), 4, 0, 1, 2, Qt::AlignTop);

    // *** container
    auto _tab1 = new QWidget;
    _tab1->setLayout(_tab1_layout);
    _tab1->setMinimumWidth(900);
    _tab1->setMinimumHeight(600);

    return _tab1;
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
// *** WidgetSettings_creator_CANopen_local_device ***

WidgetSettings * WidgetSettings_creator_CANopen_local_device::create(const QModelIndex & index_)
{
    return new WidgetSettings_CANopen_local_device(index_);
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
    m_creators.insert(WidgetSettings::eDT_CANopen_device, new WidgetSettings_creator_CANopen_local_device);
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
