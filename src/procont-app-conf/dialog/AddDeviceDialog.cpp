#include "AddDeviceDialog.h"

#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QLabel>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QGroupBox>
#include <QRadioButton>
#include <QButtonGroup>
#include <QComboBox>
#include <QTreeView>
#include <QSortFilterProxyModel>
#include <QStandardItemModel>
#include <QCheckBox>
#include <QTextEdit>

#include <QDebug>

AddDeviceDialog::AddDeviceDialog()
{
    setWindowTitle(tr("Add device"));
    setMinimumSize(850, 750);

    // name
    _m_lineEdit_name = new QLineEdit;
    auto _name_layout = new QFormLayout;
    _name_layout->addRow(new QLabel(tr("Name")), _m_lineEdit_name);
    _name_layout->setRowWrapPolicy(QFormLayout::WrapAllRows);

    // action group
    auto _action_radio1 = new QRadioButton(tr("Add device"));
    _action_radio1->setChecked(true);
    auto _action_radio2 = new QRadioButton(tr("Insert device"));
    _action_radio2->setEnabled(false);
    auto _action_radio3 = new QRadioButton(tr("Plug device"));
    _action_radio3->setEnabled(false);
    auto _action_radio4 = new QRadioButton(tr("Update device"));
    _action_radio4->setEnabled(false);
    auto _action_buttonGroup = new QButtonGroup;
    _action_buttonGroup->addButton(_action_radio1);
    _action_buttonGroup->addButton(_action_radio2);
    _action_buttonGroup->addButton(_action_radio3);
    _action_buttonGroup->addButton(_action_radio4);
    connect(_action_buttonGroup, &QButtonGroup::idToggled, this, &AddDeviceDialog::slot_action_buttonGroup_toggled);
    auto _action_layout = new QHBoxLayout;
    _action_layout->addWidget(_action_radio1, eDT_Add);
    _action_layout->addWidget(_action_radio2, eDT_Insert);
    _action_layout->addWidget(_action_radio3, eDT_Plug);
    _action_layout->addWidget(_action_radio4, eDT_Update);
    auto _action_groupBox = new QGroupBox(tr("Action"));
    _action_groupBox->setLayout(_action_layout);

    // device group
    // vendor
    auto _vendor_search_lineEdit = new QLineEdit;
    auto _vendor_list_comboBox = new QComboBox;
    auto _vendor_layout = new QHBoxLayout;
    _vendor_layout->addWidget(_vendor_search_lineEdit);
    _vendor_layout->addWidget(new QLabel(tr("Vendor")));
    _vendor_layout->addWidget(_vendor_list_comboBox);
    // device
    auto _device_treeView = new QTreeView;
    _device_treeView->setMinimumHeight(300);
    _device_treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    auto _device_treeView_proxy = new QSortFilterProxyModel;
    _device_treeView->setModel(_device_treeView_proxy);
    auto _device_treeView_model= new QStandardItemModel;
    _device_treeView_model->setColumnCount(4);
    _device_treeView_model->setHeaderData(0, Qt::Horizontal, tr("Name"));
    _device_treeView_model->setHeaderData(1, Qt::Horizontal, tr("Vendor"));
    _device_treeView_model->setHeaderData(2, Qt::Horizontal, tr("Version"));
    _device_treeView_model->setHeaderData(3, Qt::Horizontal, tr("Description"));
    setDeviceModelData(_device_treeView_model);
    _device_treeView_proxy->setSourceModel(_device_treeView_model);
    _device_treeView->expandAll();
    _device_treeView->setColumnWidth(0, 300);
    // connect(_m_tab2_treeview_result->selectionModel(), &QItemSelectionModel::currentChanged, this, &InputDialog::slot_typeCurrentChanged_tab2);
    // connect(tab2_lineedit_query, &QLineEdit::textChanged, this, &InputDialog::slot_filterTextChanged);
    // checkbox
    auto _category_checkBox = new QCheckBox(tr("Group by category"));
    _category_checkBox->setChecked(true);
    auto _checkbox_layout = new QHBoxLayout;
    _checkbox_layout->addWidget(_category_checkBox);
    auto _device_layout = new QVBoxLayout;
    _device_layout->addLayout(_vendor_layout);
    _device_layout->addWidget(_device_treeView);
    _device_layout->addLayout(_checkbox_layout);
    auto _device_groupBox = new QGroupBox();
    _device_groupBox->setLayout(_device_layout);

    // documentation
    auto _documentation_textEdit = new QTextEdit;
    _documentation_textEdit->setReadOnly(true);
    _documentation_textEdit->setMinimumHeight(75);
    _documentation_textEdit->setMaximumHeight(125);

    // information
    auto _information_textEdit = new QTextEdit;
    auto _information_textEdit_palette = _information_textEdit->palette();
    _information_textEdit_palette.setColor(QPalette::Base, QColor(255,255,237));
    _information_textEdit->setPalette(_information_textEdit_palette);
    _information_textEdit->setReadOnly(true);
    _information_textEdit->setMinimumHeight(50);
    _information_textEdit->setMaximumHeight(75);

    // button
    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Add device"));
    buttonBox->button(QDialogButtonBox::Cancel)->setText(tr("Cancel"));
    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    auto _layout = new QVBoxLayout;
    _layout->addLayout(_name_layout);
    _layout->addWidget(_action_groupBox);
    _layout->addWidget(_device_groupBox);
    _layout->addWidget(_documentation_textEdit);
    _layout->addWidget(_information_textEdit);
    _layout->addWidget(buttonBox);

    setLayout(_layout);
}

void AddDeviceDialog::setDeviceModelData(QStandardItemModel *model_)
{
    auto _Fieldbus_category_item = new QStandardItem("Fieldbuses");
    model_->insertRow(model_->rowCount(), _Fieldbus_category_item);

    auto _CANbus_category_item = new QStandardItem("CANbus");
    _Fieldbus_category_item->insertRow(_Fieldbus_category_item->rowCount(), _CANbus_category_item);

    auto _CANbus_device_items = QList<QStandardItem *>();
    _CANbus_device_items << new QStandardItem("CANbus");
    _CANbus_device_items << new QStandardItem("AMBITECS");
    _CANbus_device_items << new QStandardItem("1.0.0.0");
    _CANbus_device_items << new QStandardItem(tr("Need for all fieldbusses which communicate over the CANbus"));
    _CANbus_category_item->insertRow(_CANbus_category_item->rowCount(), _CANbus_device_items);

    auto _CANopen_category_item = new QStandardItem("CANOpen");
    _CANbus_category_item->insertRow(_CANbus_category_item->rowCount(), _CANopen_category_item);

    auto _CANopen_manager_category_item = new QStandardItem("CANOpen Manager");
    _CANopen_category_item->insertRow(_CANopen_category_item->rowCount(), _CANopen_manager_category_item);

    auto _CANopen_manager_device_items = QList<QStandardItem *>();
    _CANopen_manager_device_items << new QStandardItem("CANopen manager");
    _CANopen_manager_device_items << new QStandardItem("AMBITECS");
    _CANopen_manager_device_items << new QStandardItem("1.0.0.0");
    _CANopen_manager_device_items << new QStandardItem(tr("CANopen manager"));
    _CANopen_manager_category_item->insertRow(_CANopen_manager_category_item->rowCount(), _CANopen_manager_device_items);

    auto _CANopen_manager_remote_category_item = new QStandardItem("Remote Device");
    _CANopen_manager_category_item->insertRow(_CANopen_manager_category_item->rowCount(), _CANopen_manager_remote_category_item);

    auto _CANopen_manager_remote_device_items = QList<QStandardItem *>();
    _CANopen_manager_remote_device_items << new QStandardItem("CANopen remote device");
    _CANopen_manager_remote_device_items << new QStandardItem("AMBITECS");
    _CANopen_manager_remote_device_items << new QStandardItem("1.0.0.0");
    _CANopen_manager_remote_device_items << new QStandardItem(tr("CANopen remote device"));
    _CANopen_manager_remote_category_item->insertRow(_CANopen_manager_remote_category_item->rowCount(), _CANopen_manager_remote_device_items);

    auto _CANopen_device_category_item = new QStandardItem("Local device");
    _CANopen_category_item->insertRow(_CANopen_category_item->rowCount(), _CANopen_device_category_item);

    auto _CANopen_device_device_items = QList<QStandardItem *>();
    _CANopen_device_device_items << new QStandardItem("CANopen device");
    _CANopen_device_device_items << new QStandardItem("AMBITECS");
    _CANopen_device_device_items << new QStandardItem("1.0.0.0");
    _CANopen_device_device_items << new QStandardItem(tr("CANopen device"));
    _CANopen_device_category_item->insertRow(_CANopen_device_category_item->rowCount(), _CANopen_device_device_items);

    auto _Ethernet_category_item = QList<QStandardItem *>();
    _Ethernet_category_item << new QStandardItem("Ethernet adapter");
    _Ethernet_category_item << new QStandardItem("AMBITECS");
    _Ethernet_category_item << new QStandardItem("1.0.0.0");
    _Fieldbus_category_item->insertRow(_Fieldbus_category_item->rowCount(), _Ethernet_category_item);

    auto _EtherCAT_category_item = QList<QStandardItem *>();
    _EtherCAT_category_item << new QStandardItem("EtherCAT");
    _EtherCAT_category_item << new QStandardItem("AMBITECS");
    _EtherCAT_category_item << new QStandardItem("1.0.0.0");
    _Fieldbus_category_item->insertRow(_Fieldbus_category_item->rowCount(), _EtherCAT_category_item);

    auto _Modbus_category_item = QList<QStandardItem *>();
    _Modbus_category_item << new QStandardItem("Modbus");
    _Modbus_category_item << new QStandardItem("AMBITECS");
    _Modbus_category_item << new QStandardItem("1.0.0.0");
    _Fieldbus_category_item->insertRow(_Fieldbus_category_item->rowCount(), _Modbus_category_item);
}

void AddDeviceDialog::slot_action_buttonGroup_toggled(int id_, bool checked_)
{
    qDebug() << __PRETTY_FUNCTION__ << id_ << checked_;
}

