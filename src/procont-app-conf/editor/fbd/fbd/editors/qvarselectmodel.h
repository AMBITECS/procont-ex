#ifndef QVARIABLESSELECT_H
#define QVARIABLESSELECT_H

#include <QAbstractItemModel>
#include "editor/fbd/plc-xml/common/CVariablesAnalytics.h"
#include "CTreeItem.h"


class QVarSelectModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit QVarSelectModel(QObject *parent = nullptr);
    ~QVarSelectModel() override;
    QVarSelectModel(const QVarSelectModel &);

    QVarSelectModel & operator=(const QVarSelectModel &rhs);

    // Header:
    QVariant headerData(int section,
                        Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    // Basic functionality:
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Add data:
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    // Remove data:
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    void set_data(std::vector<s_tree_item> *variables);

private:
    std::vector<TreeItem*> m_rows;
    TreeItem    * m_root;
    void setup_data(TreeItem *item);
    QFont   m_type_font;
    QFont   m_name_font;
    QColor  m_def_color;
    QColor  m_type_color;

};

#endif // QVARIABLESSELECT_H
