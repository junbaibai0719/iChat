#include "SqlExecutor.h"

SqlExecutor::SqlExecutor()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    qDebug() << db;
}
