#ifndef TREEVARIANTMODEL_H
#define TREEVARIANTMODEL_H

#include <QAbstractItemModel>
#include <TreeColumn.h>
#include <variantitem.h>

class TreeVariantModel : public QAbstractItemModel
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<TreeColumn> headers READ headers NOTIFY headersChanged)
    Q_PROPERTY(QVariant rows READ rows WRITE setRows NOTIFY rowsChanged FINAL)
    Q_CLASSINFO("DefaultProperty", "headers")
    QML_ELEMENT;
public:
    explicit TreeVariantModel(QObject *parent = nullptr);

    /*
    * Property method
    */
    QQmlListProperty<TreeColumn> headers();
    QVariant rows() const;
    void setRows(const QVariant &rows);

    static void columns_append(QQmlListProperty<TreeColumn> *property, TreeColumn *value);
    static qsizetype columns_count(QQmlListProperty<TreeColumn> *property);
    static TreeColumn *columns_at(QQmlListProperty<TreeColumn> *property, qsizetype index);
    static void columns_clear(QQmlListProperty<TreeColumn> *property);
    static void columns_replace(QQmlListProperty<TreeColumn> *property, qsizetype index, TreeColumn *value);
    static void columns_removeLast(QQmlListProperty<TreeColumn> *property);




    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    QHash<int, QByteArray> roleNames() const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    Q_INVOKABLE QVariant data(const QModelIndex &index, const QString &role) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

signals:
    void headersChanged();
    void rowsChanged();
private:
    VariantItem *getItem(const QModelIndex &index) const;
    QList<TreeColumn *> m_headers;
    QHash<int, QByteArray> m_roleNames;
    VariantItem *rootItem;
    QVariantList m_rows;
};

#endif // TREEVARIANTMODEL_H
