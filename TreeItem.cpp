#include "TreeItem.h"

TreeItem::TreeItem(const QJSValue &data, TreeItem *parent)
{
    m_data = data;
    parentItem = parent;
}

TreeItem::~TreeItem ()
{
    qDeleteAll(childItems);
}

TreeItem *TreeItem::child(int index)
{
    if (index < 0 || index >= childItems.size()) {
        return nullptr;
    }
    return childItems.at(index);
}

bool TreeItem::insertChild(int pos, TreeItem *child)
{
    if (pos < 0 || pos > childItems.size()) {
        return false;
    }
    childItems.insert(pos, child);
    child->setRowInParent(pos);
    return true;
}

int TreeItem::rowInParent() const
{
    return m_rowInParent;
}

void TreeItem::setRowInParent(int row)
{
    m_rowInParent = row;
}

TreeItem *TreeItem::parent()
{
    return parentItem;
}

