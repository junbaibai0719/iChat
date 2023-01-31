#ifndef TREECOLUMN_H
#define TREECOLUMN_H

#include <QQmlEngine>
#include <QtQml>

class TreeColumn:public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString prop READ prop WRITE setProp NOTIFY propChanged)
    Q_PROPERTY(QString label READ label WRITE setLabel NOTIFY labelChanged)
    Q_PROPERTY(QString roleName READ roleName WRITE setRoleName NOTIFY roleNameChanged)

    Q_PROPERTY(QJSValue display READ display WRITE setDisplay NOTIFY displayChanged FINAL)
    QML_ELEMENT;
public:
    using QObject::QObject;

    QString prop() const;
    void setProp(const QString &prop);
    QString label() const;
    void setLabel(const QString &label);
    QString roleName() const;
    void setRoleName(const QString &roleName);

    QJSValue display() const;
    void setDisplay(const QJSValue &stringOrFunction);
    QJSValue getSetDisplay() const;
    void setSetDisplay(const QJSValue &function);

    QJSValue decoration() const;
    void setDecoration(const QJSValue &stringOrFunction);
    QJSValue getSetDecoration() const;
    void setSetDecoration(const QJSValue &function);




    QJSValue getterAtRole(const QString &roleName);
    QJSValue setterAtRole(const QString &roleName);

    const QHash<QString, QJSValue> getters() const;

    static const QHash<int, QString> supportedRoleNames();

signals:
    void propChanged();
    void labelChanged();
    void roleNameChanged();

    void displayChanged();
    void setDisplayChanged();
    void decorationChanged();
    void setDecorationChanged();

private:
    QString m_prop;
    QString m_label;
    QString m_roleName;

    QHash<QString, QJSValue> mGetters;
    QHash<QString, QJSValue> mSetters;
};

#endif // TREECOLUMN_H
