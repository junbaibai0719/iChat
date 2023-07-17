#include "TreeModel.h"

TreeModel::TreeModel(QObject *parent)
    :QAbstractItemModel(parent)
{
//    qDebug() << "1";
//    QJSEngine myEngine;
//    qDebug() << "1";
//    rootItem = myEngine.newObject();
//    qDebug() << "1";
//    qDebug() << rootItem.isObject();
//    qDebug() << "1";
//    this->rootItem.setProperty(m_childrenKey, this->m_rows);
//    qDebug() << this->rootItem.isObject();
//    qDebug() << "1";
    rootItem = new TreeItem(QJSValue());


}

TreeModel::~TreeModel()
{
}


/*
* Property method
*/


QQmlListProperty<TreeColumn> TreeModel::headers()
{
    return QQmlListProperty<TreeColumn>(this, nullptr,
                                        &TreeModel::columns_append,
                                        &TreeModel::columns_count,
                                        &TreeModel::columns_at,
                                        &TreeModel::columns_clear,
                                        &TreeModel::columns_replace,
                                        &TreeModel::columns_removeLast);
}


void TreeModel::columns_append(QQmlListProperty<TreeColumn> *property,
                               TreeColumn *value)
{
    TreeModel *model = static_cast<TreeModel *>(property->object);
    TreeColumn *column = qobject_cast<TreeColumn *>(value);
    if (column)
        model->m_headers.append(column);
}

qsizetype TreeModel::columns_count(QQmlListProperty<TreeColumn> *property)
{
    const TreeModel *model = static_cast<TreeModel *>(property->object);
    return model->m_headers.count();
}

TreeColumn *TreeModel::columns_at(QQmlListProperty<TreeColumn> *property, qsizetype index)
{
    const TreeModel *model = static_cast<TreeModel *>(property->object);
    return model->m_headers.at(index);
}

void TreeModel::columns_clear(QQmlListProperty<TreeColumn> *property)
{
    TreeModel *model = static_cast<TreeModel *>(property->object);
    return model->m_headers.clear();
}

void TreeModel::columns_replace(QQmlListProperty<TreeColumn> *property, qsizetype index, TreeColumn *value)
{
    TreeModel *model = static_cast<TreeModel *>(property->object);
    if (TreeColumn *column = qobject_cast<TreeColumn *>(value))
        return model->m_headers.replace(index, column);
}

void TreeModel::columns_removeLast(QQmlListProperty<TreeColumn> *property)
{
    TreeModel *model = static_cast<TreeModel *>(property->object);
    model->m_headers.removeLast();
}

QVariant TreeModel::rows() const
{
    return QVariant::fromValue(this->m_rows);
}

void TreeModel::setRows(const QVariant &rows)
{
    if (rows.userType() != qMetaTypeId<QJSValue>()) {
        qmlWarning(this) << "setRows(): \"rows\" must be an array; actual type is " << rows.typeName();
        return;
    }
    QJSValue rowsAsJSValue = rows.value<QJSValue>();
    if (!rowsAsJSValue.isArray()) {
        qmlWarning(this) << "setRows():\"rows\" must be an array;";
        return;
    }
    this->m_rows = rowsAsJSValue;
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

/*
 * override func
 */


int TreeModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return m_headers.length();
}

QVariant TreeModel::data(const QModelIndex &index, const QString &role) const
{
    qDebug() << role;
    const int iRole = m_roleNames.key(role.toUtf8(), -1);
    if (iRole >= 0)
        return data(index, iRole);
    return QVariant();
}

QVariant TreeModel::data(const QModelIndex &index, int role) const
{
//    qDebug() << index.row() << index.column() << role;
    if (!index.isValid()) {
        return QVariant();
    }
    if (role != Qt::DisplayRole && role != Qt::EditRole) {
        return QVariant();
    }

    QString roleName = QString::fromUtf8(roleNames().value(role));
    TreeColumn * column = m_headers[index.column()];
    QJSValue keyName = column->getterAtRole(roleName);
//    qDebug() << "keyname:" << keyName.toString() ;
    TreeItem *item = getItem(index);
    QJSValue data = item->m_data;
//    qDebug() << "value: " << data.property(keyName.toString()).toString();
    return QVariant::fromValue(data.property(keyName.toString()));
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const
{
    if (!index.isValid()) {
        return Qt::NoItemFlags;
    }

    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}



TreeItem *TreeModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        TreeItem *item = static_cast<TreeItem *>(index.internalPointer());
        if (item) {
            return item;
        }
    }
    return rootItem;
}


QVariant TreeModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
//        return rootItem.data(section);
    }

    return QVariant();
}


QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const
{
//    qDebug() << column;
    if (parent.isValid() && parent.column() != 0) {
        return QModelIndex();
    }

    TreeItem *parentItem = getItem(parent);
    TreeItem *childItem = parentItem->child(row);
    if (!childItem) {
        QJSValue childData;
        if (parentItem == rootItem) {
            childData = m_rows.property(row);
        } else {
            childData = parentItem->m_data.property(m_childrenKey).property(row);
        }
        childItem = new TreeItem(childData, parentItem);
        parentItem->insertChild(row, childItem);
    }
    return createIndex(row, column, childItem);
}


bool TreeModel::insertColumns(int position, int columns, const QModelIndex &parent)
{
    beginInsertColumns(parent, position, position + columns - 1);
//    const bool success = rootItem.insertColumns(position, columns);
    endInsertColumns();

//    return success;
    return false;
}

bool TreeModel::insertRows(int position, int rows, const QModelIndex &parent)
{
//    TreeItem *parentItem = getItem(parent);
//    if (!parentItem) {
//        return false;
//    }

//    beginInsertRows(parent, position, position + rows - 1);
//    const bool success = parentItem->insertChildren(position,
//                         rows,
//                         rootItem.columnCount());
//    endInsertRows();

//    return success;
    return false;
}


QModelIndex TreeModel::parent(const QModelIndex &index) const
{
    if (!index.isValid()) {
        return QModelIndex();
    }
    // qDebug\(\)[\s\S]+
    TreeItem *childItem = getItem(index);
    if (rootItem == childItem) {
        return QModelIndex();
    }
    TreeItem *parent = childItem->parent();

    if (!parent) {
        return QModelIndex();
    }
    return createIndex(parent->rowInParent(), 0, parent);
}

QHash<int, QByteArray> TreeModel::roleNames() const
{
    return m_roleNames;
}


bool TreeModel::removeColumns(int position, int columns, const QModelIndex &parent)
{
//    beginRemoveColumns(parent, position, position + columns - 1);
//    const bool success = rootItem.removeColumns(position, columns);
//    endRemoveColumns();

//    if (rootItem.columnCount() == 0) {
//        removeRows(0, rowCount());
//    }

//    return success;
    return false;
}

bool TreeModel::removeRows(int position, int rows, const QModelIndex &parent)
{
//    TreeItem *parentItem = getItem(parent);
//    if (!parentItem) {
//        return false;
//    }

//    beginRemoveRows(parent, position, position + rows - 1);
//    const bool success = parentItem->removeChildren(position, rows);
//    endRemoveRows();

//    return success;
    return false;
}


int TreeModel::rowCount(const QModelIndex &parent) const
{

    if (parent.isValid() && parent.column() > 0) {
        return 0;
    }

    TreeItem *parentItem = getItem(parent);
    if (rootItem == parentItem) {
        return m_rows.property(LENGTH).toInt();
    }
    int len = parentItem->m_data.property(m_childrenKey).property(LENGTH).toInt();
    return len;
}


bool TreeModel::setData(const QModelIndex &index, const QVariant &value, int role)
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
