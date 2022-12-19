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


static const QString displayRoleName = QStringLiteral("display");
static const QString decorationRoleName = QStringLiteral("decoration");
static const QString editRoleName = QStringLiteral("edit");
static const QString toolTipRoleName = QStringLiteral("toolTip");
static const QString statusTipRoleName = QStringLiteral("statusTip");
static const QString whatsThisRoleName = QStringLiteral("whatsThis");

static const QString fontRoleName = QStringLiteral("font");
static const QString textAlignmentRoleName = QStringLiteral("textAlignment");
static const QString backgroundRoleName = QStringLiteral("background");
static const QString foregroundRoleName = QStringLiteral("foreground");
static const QString checkStateRoleName = QStringLiteral("checkState");

static const QString accessibleTextRoleName = QStringLiteral("accessibleText");
static const QString accessibleDescriptionRoleName = QStringLiteral("accessibleDescription");

static const QString sizeHintRoleName = QStringLiteral("sizeHint");



#define DEFINE_ROLE_PROPERTIES(getterGetterName, getterSetterName, getterSignal, setterGetterName, setterSetterName, setterSignal, roleName) \
QJSValue TreeColumn::getterGetterName() const \
{ \
    return mGetters.value(roleName); \
} \
\
void TreeColumn::getterSetterName(const QJSValue &stringOrFunction) \
{ \
    if (!stringOrFunction.isString() && !stringOrFunction.isCallable()) { \
        qmlWarning(this).quote() << "getter for " << roleName << " must be a function"; \
        return; \
    } \
    if (stringOrFunction.strictlyEquals(decoration())) \
        return; \
\
    mGetters[roleName] = stringOrFunction; \
    emit decorationChanged(); \
} \
\
QJSValue TreeColumn::setterGetterName() const \
{ \
    return mSetters.value(roleName); \
} \
\
void TreeColumn::setterSetterName(const QJSValue &function) \
{ \
    if (!function.isCallable()) { \
        qmlWarning(this).quote() << "setter for " << roleName << " must be a function"; \
        return; \
    } \
\
    if (function.strictlyEquals(getSetDisplay())) \
        return; \
\
    mSetters[roleName] = function; \
    emit setDisplayChanged(); \
}

DEFINE_ROLE_PROPERTIES(display, setDisplay, displayChanged,
    getSetDisplay, setSetDisplay, setDisplayChanged, displayRoleName)
DEFINE_ROLE_PROPERTIES(decoration, setDecoration, decorationChanged,
    getSetDecoration, setSetDecoration, setDecorationChanged, decorationRoleName)

QJSValue TreeColumn::getterAtRole(const QString &roleName)
{
    auto it = mGetters.find(roleName);
    if (it == mGetters.end())
        return QJSValue();
    return *it;
}

QJSValue TreeColumn::setterAtRole(const QString &roleName)
{
    auto it = mSetters.find(roleName);
    if (it == mSetters.end())
        return QJSValue();
    return *it;
}

const QHash<QString, QJSValue> TreeColumn::getters() const
{
    return mGetters;
}

const QHash<int, QString> TreeColumn::supportedRoleNames()
{
    QHash<int, QString> names;
    names[Qt::DisplayRole] = QLatin1String("display");
    names[Qt::DecorationRole] = QLatin1String("decoration");
    names[Qt::EditRole] = QLatin1String("edit");
    names[Qt::ToolTipRole] = QLatin1String("toolTip");
    names[Qt::StatusTipRole] = QLatin1String("statusTip");
    names[Qt::WhatsThisRole] = QLatin1String("whatsThis");
    names[Qt::FontRole] = QLatin1String("font");
    names[Qt::TextAlignmentRole] = QLatin1String("textAlignment");
    names[Qt::BackgroundRole] = QLatin1String("background");
    names[Qt::ForegroundRole] = QLatin1String("foreground");
    names[Qt::CheckStateRole] = QLatin1String("checkState");
    names[Qt::AccessibleTextRole] = QLatin1String("accessibleText");
    names[Qt::AccessibleDescriptionRole] = QLatin1String("accessibleDescription");
    names[Qt::SizeHintRole] = QLatin1String("sizeHint");
    return names;
}
