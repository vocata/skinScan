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
        /* 测试 */
//        query.exec(QString("insert into userInfo values('13715661201', 'admin', 'admin', 0, '0', '男', '%1')").arg(
//                       QDateTime::currentDateTime().toString("yyyy-MM-dd")));
//        query.exec(QString("insert into adminInfo values('b', 'b')"));
//        QPixmap pix("D:/d.jpg");
//        QByteArray bytes;
//        QBuffer buffer(&bytes);
//        buffer.open(QIODevice::WriteOnly);
//        pix.save(&buffer, "JPG");
//        buffer.close();

//        QSqlDatabase::database().transaction();
//        for(int i = 0; i < 100; ++i) {
//            query.prepare(QString("insert into measureResult values('%1', '13715661201', 1.3, 1.9, 5.4, 4.3, '凉爽', '皮肤干燥', ?)").arg(QString::number(i)));
//            query.addBindValue(bytes);
//            query.exec();
//        }
//        QSqlDatabase::database().commit();

        return true;
    }
    return false;
}

void closeConnection(const QString &dbName) {
    Q_UNUSED(dbName)

    QSqlDatabase::database().close();
}
