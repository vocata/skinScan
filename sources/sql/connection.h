#ifndef CONNECTION_H
#define CONNECTION_H
#include <QString>
#include <QSqlQuery>
#include <QSqlError>

bool createConnection(const QString &dbName = QString("main.db"));
void closeConnection(const QString &dbName = QString("main.db"));

#endif // CONNECTION_H
