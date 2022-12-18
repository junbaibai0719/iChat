#ifndef TREEITEM_H
#define TREEITEM_H

#include <QVariant>
#include <QList>

class TreeItem
{
public:
    explicit TreeItem(const QList<QVariant> &data, TreeItem *parent = nullptr);
    ~TreeItem();

    TreeItem *child(int num);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    bool insertChildren(int pos, int count, int columns);
    bool insertColumns(int pos, int columns);
    TreeItem *parent();
    bool removeChildren(int pos, int count);
    bool removeColumns(int pos, int columns);
    int childNumber() const;
    bool setData(int column, const QVariant &value);

private:
    QList<TreeItem *> childItems;
    QList<QVariant> itemData;
    TreeItem *parentItem;

};

#endif // TREEITEM_H
