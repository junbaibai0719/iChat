#ifndef TREECOLUMN_H
#define TREECOLUMN_H

#include <QQmlEngine>

class TreeColumn:public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString prop READ prop WRITE setProp NOTIFY propChanged)
    Q_PROPERTY(QString label READ label WRITE setLabel NOTIFY labelChanged)
    Q_PROPERTY(QString roleName READ roleName WRITE setRoleName NOTIFY roleNameChanged)
    QML_ELEMENT;
public:
    using QObject::QObject;

    QString prop() const;
    void setProp(const QString &prop);
    QString label() const;
    void setLabel(const QString &label);
    QString roleName() const;
    void setRoleName(const QString &roleName);
signals:
    void propChanged();
    void labelChanged();
    void roleNameChanged();
private:
    QString m_prop;
    QString m_label;
    QString m_roleName;
};

#endif // TREECOLUMN_H
