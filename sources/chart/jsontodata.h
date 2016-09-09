#ifndef JSONTODATA_H
#define JSONTODATA_H

#include <QVector>
#include <QString>
#include <QVariant>
#include <QMap>
#include <QJsonParseError>
#include <QJsonDocument>

class JsonToData
{
public:
    explicit JsonToData(const QJsonDocument &jsonDocument);
    ~JsonToData();
    QVector<double> getData(const QString &dataName = "grease");//grease, moisture, temperature, ph
    QStringList getOther(const QString &dataName, const QStringList &dataAttributeList);//dataName 数据名称, dataAttribute 数据里面的内容
    //"date" << "deviceId" << "phone"
private:
    QJsonDocument m_jsonDocument;
};

#endif // JSONTODATA_H
