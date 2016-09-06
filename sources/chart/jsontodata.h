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
    QVector<double> getData(QString dataName = "grease");//grease, moisture, temperature, ph

private:
    QJsonDocument m_jsonDocument;
};

#endif // JSONTODATA_H
