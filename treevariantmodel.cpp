#include "treevariantmodel.h"

TreeVariantModel::TreeVariantModel(QObject *parent)
    : QAbstractItemModel(parent)
{
}

QQmlListProperty<TreeColumn> TreeVariantModel::headers()
{
    qDebug() << "headers" ;
    return QQmlListProperty<TreeColumn>(this, nullptr,
                                        &TreeVariantModel::columns_append,
                                        &TreeVariantModel::columns_count,
                                        &TreeVariantModel::columns_at,
                                        &TreeVariantModel::columns_clear,
                                        &TreeVariantModel::columns_replace,
                                        &TreeVariantModel::columns_removeLast);
}

void TreeVariantModel::columns_append(QQmlListProperty<TreeColumn> *property,
                               TreeColumn *value)
{
    qDebug() << "columns_append";
    TreeVariantModel *model = static_cast<TreeVariantModel *>(property->object);
    TreeColumn *column = qobject_cast<TreeColumn *>(value);
    if (column)
        model->m_headers.append(column);
}

qsizetype TreeVariantModel::columns_count(QQmlListProperty<TreeColumn> *property)
{
    const TreeVariantModel *model = static_cast<TreeVariantModel *>(property->object);
    return model->m_headers.count();
}

TreeColumn *TreeVariantModel::columns_at(QQmlListProperty<TreeColumn> *property, qsizetype index)
{
    const TreeVariantModel *model = static_cast<TreeVariantModel *>(property->object);
    return model->m_headers.at(index);
}

void TreeVariantModel::columns_clear(QQmlListProperty<TreeColumn> *property)
{
    TreeVariantModel *model = static_cast<TreeVariantModel *>(property->object);
    return model->m_headers.clear();
}

void TreeVariantModel::columns_replace(QQmlListProperty<TreeColumn> *property, qsizetype index, TreeColumn *value)
{
    TreeVariantModel *model = static_cast<TreeVariantModel *>(property->object);
    if (TreeColumn *column = qobject_cast<TreeColumn *>(value))
        return model->m_headers.replace(index, column);
}

void TreeVariantModel::columns_removeLast(QQmlListProperty<TreeColumn> *property)
{
    TreeVariantModel *model = static_cast<TreeVariantModel *>(property->object);
    model->m_headers.removeLast();
}

QVariant TreeVariantModel::rows() const
{
    return QVariant::fromValue(this->m_rows);
}

void TreeVariantModel::setRows(const QVariant &rows)
{
    if (rows.userType() != qMetaTypeId<QJSValue>()) {
        qmlWarning(this) << "setRows(): \"rows\" must be an array; actual type is " << rows.typeName();
        return;
    }
    qDebug() << "setRows";
    this->m_rows = rows.toList();
    emit this->dataChanged(createIndex(0,0), createIndex(3,3), {Qt::DisplayRole});

    static const auto supportedRoleNames = TreeColumn::supportedRoleNames();
    const auto builtInRoleKeys = supportedRoleNames.keys();
    for (const int builtInRoleKey : builtInRoleKeys) {
        const QString builtInRoleName = supportedRoleNames.value(builtInRoleKey);
        // This column now supports this specific built-in role.
        // Add it if it doesn't already exist.
        m_roleNames[builtInRoleKey] = builtInRoleName.toUtf8();
    }
    beginResetModel();
    endResetModel();
    emit this->rowsChanged();

}

QVariant TreeVariantModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
        //        return rootItem.data(section);
    }

    return QVariant();
}

QModelIndex TreeVariantModel::index(int row, int column, const QModelIndex &parent) const
{
    // FIXME: Implement me!
    if (parent.isValid() && parent.column() != 0) {
        return QModelIndex();
    }

    VariantItem *parentItem = getItem(parent);
    VariantItem *childItem = parentItem->child(row);
    if (!childItem) {
        QVariant childData;
        if (parentItem == rootItem) {
            childData = m_rows.at(row);
        } else {
            childData = parentItem->m_data;
        }
        childItem = new VariantItem(childData, parentItem);
        parentItem->insertChild(row, childItem);
    }
    return createIndex(row, column, childItem);
}

QModelIndex TreeVariantModel::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
    if (!index.isValid()) {
        return QModelIndex();
    }
    // qDebug\(\)[\s\S]+
    VariantItem *childItem = getItem(index);
    if (rootItem == childItem) {
        return QModelIndex();
    }
    VariantItem *parent = childItem->parent();

    if (!parent) {
        return QModelIndex();
    }
    return createIndex(parent->rowInParent(), 0, parent);
}

QHash<int, QByteArray> TreeVariantModel::roleNames() const
{
    return m_roleNames;
}


int TreeVariantModel::rowCount(const QModelIndex &parent) const
{

    if (parent.isValid() && parent.column() > 0) {
        return 0;
    }

    VariantItem *parentItem = getItem(parent);
    if (rootItem == parentItem) {
        return m_rows.length();
    }
    int len = parentItem->childNum();
    return len;
}

int TreeVariantModel::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;
    Q_UNUSED(parent);
    return m_headers.length();
    // FIXME: Implement me!
}

QVariant TreeVariantModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    if (role != Qt::DisplayRole && role != Qt::EditRole) {
        return QVariant();
    }

    QString roleName = QString::fromUtf8(roleNames().value(role));
    TreeColumn * column = m_headers[index.column()];
    QJSValue keyName = column->getterAtRole(roleName);
    VariantItem *item = getItem(index);
    return QVariant();
}

VariantItem *TreeVariantModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        VariantItem *item = static_cast<VariantItem *>(index.internalPointer());
        if (item) {
            return item;
        }
    }
    return rootItem;
}

QVariant TreeVariantModel::data(const QModelIndex &index, const QString &role) const
{
    qDebug() << role;
    const int iRole = m_roleNames.key(role.toUtf8(), -1);
    if (iRole >= 0)
        return data(index, iRole);
    return QVariant();
}

bool TreeVariantModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (role != Qt::EditRole) {
        return false;
    }

    //    TreeItem *item = getItem(index);
    //    bool result = item->setData(index.column(), value);

    //    if (result) {
    //        emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});
    //    }

    return false;
}

Qt::ItemFlags TreeVariantModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) {
        return Qt::NoItemFlags;
    }

    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}
