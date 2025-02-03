#ifndef COMBOBOXMULTILISTWIDGET_H
#define COMBOBOXMULTILISTWIDGET_H

#include <QObject>
#include <QComboBox>
#include <QStandardItemModel>
#include <QWidget>

class ComboBoxMultiListWidget : public QComboBox
{
    Q_OBJECT
public:
    explicit ComboBoxMultiListWidget
        (QWidget *parent = nullptr);
    virtual ~ComboBoxMultiListWidget();

    QStringList checkedItems() const;
    void setCheckedItems(const QStringList &items);

    QString displayText() const;
    void setDisplayText(const QString &newDisplayText);

    QString varText() const;
    void setVarText(const QString &newVarText);

protected:
    virtual void paintEvent(QPaintEvent *event);
    virtual void resizeEvent(QResizeEvent *event);

private:
    QStringList m_checkedItems;
    QString m_varText;

    void setUnSelectableItem(const QString &text, QStandardItem *item);

    void setSelectableItem(const QString &text, QStandardItem *item);

    void collectCheckedItems();

    QString m_displayText;    

    void updateDisplayText(); 

private slots:
    void slotModelRowsInserted(const QModelIndex &parent, int start, int end);
    void slotModelRowsRemoved(const QModelIndex &parent, int start, int end);
    void slotModelItemChanged(QStandardItem *item);
    void slotUpdateVarText(int index);
};

#endif // COMBOBOXMULTILISTWIDGET_H
