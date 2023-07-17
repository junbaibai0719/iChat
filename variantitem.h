#ifndef VARIANTITEM_H
#define VARIANTITEM_H

#include <QAbstractItemModel>

class VariantItem
{
public:
    explicit VariantItem(const QVariant &data, VariantItem *parent=nullptr);
    ~VariantItem();

    VariantItem *child(int num);
    bool insertChild(int pos, VariantItem *child);
    int rowInParent() const;
    void setRowInParent(int row);
    VariantItem *parent();
    int childNum() const;

    QVariant m_data;

private:
    int m_rowInParent=0;
    QList<VariantItem *> childItems;
    VariantItem *parentItem;
};

#endif // VARIANTITEM_H
