#ifndef DOMMODEL_H
#define DOMMODEL_H

#include <QAbstractItemModel>
#include <QDomDocument>
#include <QModelIndex>

QT_FORWARD_DECLARE_CLASS(QAbstractProxyModel)

QT_FORWARD_DECLARE_CLASS(DomItem)

class DomModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit DomModel(const QDomDocument &document, QObject *parent = nullptr);
    ~DomModel();

    const QDomDocument & document() const { return domDocument; }

    [[nodiscard]] DomItem * item(const QModelIndex &index) const;
    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;
    [[nodiscard]] bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    [[nodiscard]] QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    [[nodiscard]] QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    [[nodiscard]] QModelIndex parent(const QModelIndex &child) const override;
    [[nodiscard]] int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    [[nodiscard]] int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    [[nodiscard]] bool hasChildren(const QModelIndex &index) const override;
    [[nodiscard]] bool insertRows(int position, int rows, const QModelIndex &parent = {}) override;
    [[nodiscard]] bool removeRows(int position, int rows, const QModelIndex &parent = {}) override;

    void update(const QModelIndex &index_) { emit dataChanged(index_, index_, {Qt::DisplayRole, Qt::EditRole}); }

public:
    static QModelIndex s_index(const QModelIndex &index, QAbstractItemModel * proxy = nullptr);
    static QModelIndex p_index(const QModelIndex &index, QAbstractItemModel * proxy);
    static QAbstractProxyModel * toProxy(QAbstractItemModel *);
    static DomItem * toItem(const QModelIndex &index, bool source = false, QAbstractItemModel * proxy = nullptr);
    static DomModel * toModel(QAbstractItemModel *);

private:
    const QDomDocument & domDocument;
    DomItem * rootItem;
};

#endif // DOMMODEL_H
