#include "connection.h"

#include <QBuffer>
#include <QDateTime>
#include <QPixmap>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QStringList>

#include <QDebug>

bool createConnection(const QString &dbName) {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbName);

    if(db.open()) {
        QSqlQuery query;

        QStringList tableList = QSqlDatabase::database().tables();
        qDebug() << tableList;
        if(!tableList.contains(QString("moisture"))) {
            query.exec(QString("create table moisture(phone, date, deviceId , value,"
                       "primary key(phone, date))"));
        }
        if(!tableList.contains(QString("grease"))) {
            query.exec(QString("create table grease(phone, date, deviceId , value,"
                       "primary key(phone, date))"));
        }
        if(!tableList.contains(QString("temperature"))) {
            query.exec(QString("create table temperature(phone, date, deviceId , value,"
                       "primary key(phone, date))"));
        }
        if(!tableList.contains(QString("ph"))) {
            query.exec(QString("create table ph(phone, date, deviceId , value,"
                       "primary key(phone, date))"));
        }
        return true;
    }
    return false;
}

void closeConnection(const QString &dbName) {
    Q_UNUSED(dbName)

    QSqlDatabase::database().close();
}
