#include "variantitem.h"

VariantItem::VariantItem(const QVariant &data, VariantItem *parent)
{
    m_data = data;
    parentItem = parent;
}

VariantItem::~VariantItem ()
{
//    qDeleteAll(childItems);
}

VariantItem *VariantItem::child(int index)
{
    if (index < 0 || index >= childItems.size()) {
        return nullptr;
    }
    return childItems.at(index);
}

bool VariantItem::insertChild(int pos, VariantItem *child)
{
    if (pos < 0 || pos > childItems.size()) {
        return false;
    }
    childItems.insert(pos, child);
    child->setRowInParent(pos);
    return true;
}

int VariantItem::rowInParent() const
{
    return m_rowInParent;
}

void VariantItem::setRowInParent(int row)
{
    m_rowInParent = row;
}

VariantItem *VariantItem::parent()
{
    return parentItem;
}

int VariantItem::childNum() const
{
    return childItems.length();
}
