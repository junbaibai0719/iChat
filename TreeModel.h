#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QObject>
#include <QAbstractItemModel>
#include <QQmlEngine>
#include <QtQml>

#include "TreeColumn.h"
#include "TreeItem.h"

class TreeModel: public QAbstractItemModel
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<TreeColumn> headers READ headers NOTIFY headersChanged)
    Q_PROPERTY(QVariant rows READ rows WRITE setRows NOTIFY rowsChanged FINAL)
    Q_CLASSINFO("DefaultProperty", "headers")
    QML_ELEMENT;
public:
    TreeModel(QObject *parent = nullptr);
    ~TreeModel();

    /*
    * Property method
    */
    QQmlListProperty<TreeColumn> headers();
    QVariant rows() const;
    void setRows(const QVariant &rows);


    /**
     * default prop
     */

    static void columns_append(QQmlListProperty<TreeColumn> *property, TreeColumn *value);
    static qsizetype columns_count(QQmlListProperty<TreeColumn> *property);
    static TreeColumn *columns_at(QQmlListProperty<TreeColumn> *property, qsizetype index);
    static void columns_clear(QQmlListProperty<TreeColumn> *property);
    static void columns_replace(QQmlListProperty<TreeColumn> *property, qsizetype index, TreeColumn *value);
    static void columns_removeLast(QQmlListProperty<TreeColumn> *property);


    /*
     * override func
     */

    Q_INVOKABLE QVariant data(const QModelIndex &index, const QString &role) const;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    QHash<int, QByteArray> roleNames() const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;
    bool insertColumns(int position, int columns,
                       const QModelIndex &parent = QModelIndex()) override;
    bool removeColumns(int position, int columns,
                       const QModelIndex &parent = QModelIndex()) override;
    bool insertRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex()) override;
    bool removeRows(int position, int rows,
                    const QModelIndex &parent = QModelIndex()) override;

signals:
    void headersChanged();
    void rowsChanged();
private:
    QString m_childrenKey = "children";
    const QString LENGTH = "length";
    const QString PARENT = "parent";
    TreeItem *getItem(const QModelIndex &index) const;
    QList<TreeColumn *> m_headers;
    QHash<int, QByteArray> m_roleNames;
    TreeItem *rootItem;
    QJSValue m_rows;
};

QML_DECLARE_TYPE(TreeModel)
#endif // TREEMODEL_H
