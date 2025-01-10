#include "ComboBoxMultiListWidget.h"
#include <QStylePainter>

struct Unselectable
{
    const QString SCOPE         = "Scope";
    const QString FLAGS         = "Flags";

    bool operator==(const QString &item)
    {
        return item == FLAGS || item == SCOPE;
    }
};

struct Selectable
{
    const QString VAR           = "VAR";
    const QString VAR_INPUT     = "VAR_INPUT";
    const QString VAR_OUTPUT    = "VAR_OUTPUT";
    const QString VAR_IN_OUT    = "VAR_IN_OUT";
    const QString VAR_TEMP      = "VAR_TEMP";
    const QString VAR_EXTERNAL  = "VAR_EXTERNAL";
    const QString VAR_GLOBAL    = "VAR_GLOBAL";

    bool operator==(const QString &item)
    {
        return item == VAR ||
               item == VAR_INPUT ||
               item == VAR_OUTPUT ||
               item == VAR_IN_OUT||
               item ==  VAR_TEMP ||
               item ==  VAR_EXTERNAL ||
               item ==  VAR_GLOBAL;
    }
};

struct Checkable
{
    const QString CONSTANT      = "CONSTANT";
    const QString PERSISTENT    = "PERSISTENT";
    const QString RETAIN        = "RETAIN";

    bool operator==(const QString &item)
    {
        return item == CONSTANT ||
               item == PERSISTENT ||
               item == RETAIN;
    }
};

ComboBoxMultiListWidget::ComboBoxMultiListWidget
    (QWidget *parent) : QComboBox(parent)
{
    setStyleSheet("QComboBox { combobox-popup: 1px }");

    connect(model(), SIGNAL(rowsInserted(QModelIndex,int,int)), this, SLOT(slotModelRowsInserted(QModelIndex,int,int)));
    connect(model(), SIGNAL(rowsRemoved(QModelIndex,int,int)), this, SLOT(slotModelRowsRemoved(QModelIndex,int,int)));

    QStandardItemModel *standardModel = qobject_cast<QStandardItemModel*>(model());

    connect(standardModel, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(slotModelItemChanged(QStandardItem*)));
    connect(this, &ComboBoxMultiListWidget::activated, this, &ComboBoxMultiListWidget::slotUpdateVarText);
}

ComboBoxMultiListWidget::~ComboBoxMultiListWidget()
{

}

QStringList ComboBoxMultiListWidget::checkedItems() const
{
    return m_checkedItems;
}

void ComboBoxMultiListWidget::setCheckedItems(const QStringList &items)
{
    QStandardItemModel *standardModel = qobject_cast<QStandardItemModel*>(model());

    disconnect(standardModel, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(slotModelItemChanged(QStandardItem*)));

    for(int i = 0; i < items.count(); ++i)
    {
        int index = findText(items.at(i));

        if(index != -1)
        {
            standardModel->item(index)->setData(Qt::Checked, Qt::CheckStateRole);
        }
    }

    connect(standardModel, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(slotModelItemChanged(QStandardItem*)));

    collectCheckedItems();
}

void ComboBoxMultiListWidget::setUnSelectableItem(const QString &text, QStandardItem *item)
{
    item->setText(text);
    item->setSelectable(false);
    QFont font = item->font();
    font.setUnderline(true);
    item->setFont(font);
}

void ComboBoxMultiListWidget::setSelectableItem(const QString &text, QStandardItem *item)
{
    QString path;
    QPixmap pix;

    if(text == varText())
    {
        // paint rect under icon
        path = ":/icon/images/" + varText().toLower() + "_select.png";
        pix = QPixmap(path);
    }
    else
    {
        path = ":/icon/images/" + text.toLower() + ".png";
        pix = QPixmap(path);
    }

    item->setIcon(pix);
    item->setText(text);
}

void ComboBoxMultiListWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QStylePainter painter(this);
    painter.setPen(palette().color((QPalette::Text)));

    // draw the combobox frame, focusrect and selected etc.
    QStyleOptionComboBox option;

    initStyleOption(&option);
    painter.drawComplexControl(QStyle::CC_ComboBox, option);

    // draw the icon and text
    int i = findText(varText());

    QStandardItemModel *currentModel = qobject_cast<QStandardItemModel*>(model());
    QStandardItem *currentItem = currentModel->item(i);

    option.currentIcon = currentItem->icon();
    option.currentText = m_displayText;

    painter.drawControl(QStyle::CE_ComboBoxLabel, option);
}

void ComboBoxMultiListWidget::resizeEvent(QResizeEvent *event)
{
    //qDebug() << "*********Start resizeEvent*************" << '\n';
    Q_UNUSED(event)
    //qDebug() << "resizeEvent - current Text: " << currentText() << '\n';
    //qDebug() << "Resize event - call updateDisplayText()" << '\n';

    updateDisplayText();

    //qDebug() << "*********End resizeEvent*************" << '\n';
}

QString ComboBoxMultiListWidget::varText() const
{
    return m_varText;
}

void ComboBoxMultiListWidget::setVarText(const QString &newVarText)
{
    m_varText = newVarText;
}

void ComboBoxMultiListWidget::collectCheckedItems()
{
    //qDebug() << "*********Start collectCheckedItems*************" << '\n';
    QStandardItemModel *standardModel = qobject_cast<QStandardItemModel*>(model());

    //foreach(QString str, m_checkedItems)
    //{
    //    qDebug() << "CollectCheckedItem - m_checkedItems: "
    //             << str << '\n';
    //}

    m_checkedItems.clear();

    for(int i = 0; i < count(); ++i)
    {
        QStandardItem *currentItem = standardModel->item(i);

        Qt::CheckState checkState = static_cast<Qt::CheckState>(currentItem->data(Qt::CheckStateRole).toInt());

        if(checkState == Qt::Checked)
        {
            //qDebug() << "collectCheckedItems - currentItem-text: " << currentItem->text() << '\n';
            m_checkedItems.push_back(currentItem->text());
        }
    }
    //qDebug() << "collectCheckedItems - call updateDisplayText()" << '\n';

    updateDisplayText();

    repaint();
    //qDebug() << "*********End collectCheckedItems*************" << '\n';
}

QString ComboBoxMultiListWidget::displayText() const
{
    return m_displayText;
}

void ComboBoxMultiListWidget::setDisplayText(const QString &newDisplayText)
{
    m_displayText = newDisplayText;
}

void ComboBoxMultiListWidget::updateDisplayText()
{
    //qDebug() << "*********Start updateDisplayText*************" << '\n';
    //qDebug() << "UpdateDisplayText - current Text: " << currentText() << '\n';

    //qDebug() << "UpdateDisplayText - m_varText: " << m_varText << '\n';

    m_displayText = m_checkedItems.empty() ?
                        varText() : (varText() + " " + m_checkedItems.join(" "));
    //qDebug() << "UpdateDisplayText after join - m_displayText: " << m_displayText << '\n';
    //qDebug() << "*********End updateDisplayText*************" << '\n';

}

void ComboBoxMultiListWidget::slotModelRowsInserted(const QModelIndex &parent, int start, int end)
{
    Q_UNUSED(parent)

    QStandardItemModel *standardModel = qobject_cast<QStandardItemModel*>(model());

    disconnect(standardModel, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(slotModelItemChanged(QStandardItem*)));

    for(int i = start; i <= end; ++i)
    {
        QString itemText = standardModel->item(i)->text();
        //qDebug() << "slotModelRowsInsereted - current text: " << itemText << '\n';

        if(Unselectable().operator ==(itemText))
        {
            setUnSelectableItem(itemText, standardModel->item(i));
        }
        else if(Selectable().operator ==(itemText))
        {
            setSelectableItem(itemText, standardModel->item(i));
        }
        else if(Checkable().operator ==(itemText))
        {
            standardModel->item(i)->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
            standardModel->item(i)->setData(Qt::Unchecked, Qt::CheckStateRole);
        }
        else{ break;}
    }

    connect(standardModel, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(slotModelItemChanged(QStandardItem*)));

}

void ComboBoxMultiListWidget::slotModelRowsRemoved(const QModelIndex &parent, int start, int end)
{
    Q_UNUSED(parent)
    Q_UNUSED(start)
    Q_UNUSED(end)

    collectCheckedItems();
}

void ComboBoxMultiListWidget::slotModelItemChanged(QStandardItem *item)
{
    //qDebug() << "*********Start slotModelItemChanged*************" << '\n';

    //QString currentText = item->text();

    //qDebug() << "slotModelItemChanged - current Text: " << currentText << '\n';


    Q_UNUSED(item)
    //qDebug() << "slotModelItemChanged - call collectCheckedItems();" << '\n';
    collectCheckedItems();

    //qDebug() << "*********End slotModelItemChanged*************" << '\n';
}

void ComboBoxMultiListWidget::slotUpdateVarText(int index)
{
    //qDebug() << "*********Start slotUpdateVarText*************" << '\n';
    QStandardItemModel *standardModel = qobject_cast<QStandardItemModel*>(model());

    QStandardItem *currentItem = standardModel->item(index);

    QString text = currentItem->text();
    //qDebug() << "slotModelItemChanged - currentItem-text: " << text << '\n';

        if(text[0] == 'V')
        {
            setVarText(text);            
        }

    //qDebug() << "slotUpdateVarText - call collectCheckedItems();" << '\n';

    collectCheckedItems();

    //qDebug() << "*********End slotUpdateVarText*************" << '\n';
}
