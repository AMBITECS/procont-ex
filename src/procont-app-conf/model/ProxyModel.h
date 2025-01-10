#ifndef PROXYMODEL_H
#define PROXYMODEL_H

#include <QSortFilterProxyModel>

#include <QModelIndex>
#include <QDomNode>

QT_FORWARD_DECLARE_CLASS(QUndoStack)

class ProxyModelTree_pou : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit ProxyModelTree_pou(QObject *parent = nullptr);

public:
    [[nodiscard]] int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    [[nodiscard]] bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    void setUndoStack(QUndoStack *undo_stack_);

private:
    [[nodiscard]] QUndoStack * undoStack() { return _m_undo_stack; }

protected:
    [[nodiscard]] bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

protected:
    [[nodiscard]] bool hasParent(const QDomNode &node, const QString &name) const;

private:
    QUndoStack * _m_undo_stack{nullptr};
};

class ProxyModelTree_dev : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit ProxyModelTree_dev(QObject *parent = nullptr);

public:
    [[nodiscard]] int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    [[nodiscard]] bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    void setUndoStack(QUndoStack *undo_stack_);

private:
    [[nodiscard]] QUndoStack * undoStack() { return _m_undo_stack; }

protected:
    [[nodiscard]] bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

protected:
    [[nodiscard]] bool hasParent(const QDomNode &node, const QString &name) const;

private:
    QUndoStack * _m_undo_stack{nullptr};
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

    void setUndoStack(QUndoStack *undo_stack_);

private:
    [[nodiscard]] QUndoStack * undoStack() { return _m_undo_stack; }

private:
    QUndoStack * _m_undo_stack{nullptr};
};

class ProxyModelTable_global : public ProxyModelTable_var
{
    Q_OBJECT
public:
    explicit ProxyModelTable_global(QObject *parent = nullptr);

public:
    [[nodiscard]] Qt::ItemFlags flags(const QModelIndex &index) const override;
};

#endif // PROXYMODEL_H
