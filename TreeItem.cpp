#include "TreeItem.h"

TreeItem::TreeItem(const QList<QVariant> &data, TreeItem *parent)
    : itemData(data), parentItem(parent)
{

}

TreeItem::~TreeItem()
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

int TreeItem::childCount() const
{
    return childItems.count();
}

int TreeItem::childNumber() const
{
    if (parentItem) {
        return parentItem->childItems.indexOf(const_cast<TreeItem *> (this));
    }
    return 0;
}

int TreeItem::columnCount() const
{
    return itemData.count();
}

QVariant TreeItem::data(int col) const
{
    if (col < 0 || col >= itemData.size()) {
        return QVariant();
    }
    return itemData.at(col);
}

bool TreeItem::insertChildren(int pos, int count, int columns)
{
    if (pos < 0 || pos > childItems.size()) {
        return false;
    }
    for (int row = 0; row < count; ++row) {
        QList<QVariant> data(columns);
        TreeItem *item = new TreeItem(data, this);
        childItems.insert(pos, item);
    }
    return true;
}

bool TreeItem::insertColumns(int pos, int columns)
{
    if (pos < 0 || pos > itemData.size()) {
        return false;
    }
    for (int column = 0; column < columns; ++column) {
        itemData.insert(pos, QVariant());
    }
    for (TreeItem *child : std::as_const(childItems)) {
        child->insertColumns(pos, columns);
    }
    return true;
}

TreeItem *TreeItem::parent()
{
    return parentItem;
}

bool TreeItem::removeChildren(int pos, int count)
{
    if (pos < 0 || pos + count > childItems.size()) {
        return false;
    }
    for (int row = 0; row < count; ++row) {
        delete childItems.takeAt(pos);
    }
    return true;
}

bool TreeItem::removeColumns(int pos, int columns)
{
    if (pos < 0 || pos + columns > itemData.size()) {
        return false;
    }
    for (int column = 0; column < columns; ++column) {
        itemData.remove(pos);
    }
    for (TreeItem *child : std::as_const(childItems)) {
        child->removeColumns(pos, columns);
    }
    return true;
}

bool TreeItem::setData(int column, const QVariant &value)
{
    if (column < 0 || column >= itemData.size()) {
        return false;
    }
    itemData[column] = value;
    return true;
}
