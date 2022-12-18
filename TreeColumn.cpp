#include "TreeColumn.h"

QString TreeColumn::prop() const
{
    return this->m_prop;
}

void TreeColumn::setProp(const QString &prop)
{
    this->m_prop = prop;
    emit this->propChanged();
}

QString TreeColumn::label() const
{
    return this->m_label;
}

void TreeColumn::setLabel(const QString &label)
{
    this->m_label = label;
    emit this->labelChanged();
    if (this->m_roleName == nullptr) {
        this->setRoleName(label);
    }
}

QString TreeColumn::roleName() const
{
    return this->m_roleName;
}

void TreeColumn::setRoleName(const QString &roleName)
{
    this->m_roleName = roleName;
    emit this->roleNameChanged();
}
