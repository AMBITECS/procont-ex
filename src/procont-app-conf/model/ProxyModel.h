#ifndef PROXYMODEL_H
#define PROXYMODEL_H

#include <QSortFilterProxyModel>

#include <QModelIndex>
#include <QDomNode>

class ProxyModelTree_pou : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit ProxyModelTree_pou(QObject *parent = nullptr);

public:
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

protected:
    bool hasParent(const QDomNode &node, const QString &name) const;
};

class ProxyModelTree_dev : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit ProxyModelTree_dev(QObject *parent = nullptr);

public:
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

protected:
    bool hasParent(const QDomNode &node, const QString &name) const;
};

class ProxyModelTable_var : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit ProxyModelTable_var(QObject *parent = nullptr);

public:
    [[nodiscard]] Qt::ItemFlags flags(const QModelIndex &index) const override;
    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;
    [[nodiscard]] bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    [[nodiscard]] QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
};

#endif // PROXYMODEL_H
