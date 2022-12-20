#ifndef TREEITEM_H
#define TREEITEM_H

#include <QVariant>
#include <QList>
#include <QJSValue>

class TreeItem
{
public:
    explicit TreeItem(const QJSValue &data, TreeItem *parent=nullptr);
    ~TreeItem();

    TreeItem *child(int num);
    bool insertChild(int pos, TreeItem *child);
    int rowInParent() const;
    void setRowInParent(int row);
    TreeItem *parent();

    QJSValue m_data;

private:
    int m_rowInParent=0;
    QList<TreeItem *> childItems;
    TreeItem *parentItem;

};

#endif // TREEITEM_H
