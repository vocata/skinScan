#include "jsontodata.h"

JsonToData::JsonToData(const QJsonDocument &jsonDocument) : m_jsonDocument(jsonDocument)
{
}

JsonToData::~JsonToData()
{
}

QVector<double> JsonToData::getData(const QString &dataName)
{
    QVector<double> data;
    QVariantMap result = m_jsonDocument.toVariant().toMap();

    /* sort date */
    QStringList dateStringList;
    for(QVariant eachVariant : result[dataName].toList())
    {
        QVariantMap eachVariantMap =  eachVariant.toMap();
        dateStringList << eachVariantMap["date"].toString();
    }
    qSort(dateStringList.begin(), dateStringList.end());

    /* rearrage data */
    for(QString dateString : dateStringList)
    {
        for(QVariant eachVariant : result[dataName].toList())//依据每一个时间寻找相应的数据
        {
            QVariantMap eachVariantMap =  eachVariant.toMap();
            if(dateString == eachVariantMap["date"].toString())
            {
                data.append(eachVariantMap["value"].toDouble());
            }
        }
    }
    return data;
}

QStringList JsonToData::getOther(const QString &dataName, const QStringList &dataAttributeList)//"date" << "deviceId" << "phone"
{
    QVariantMap result = m_jsonDocument.toVariant().toMap();

    /* sort date */
    QStringList dateStringList;
    for(QVariant eachVariant : result[dataName].toList())
    {
        QVariantMap eachVariantMap =  eachVariant.toMap();
        dateStringList << eachVariantMap["date"].toString();
    }
    qSort(dateStringList.begin(), dateStringList.end());
    QStringList stringList;
    for(QString dateString : dateStringList)
    {
        for(QVariant eachVariant : result[dataName].toList())//依据每一个时间寻找相应的数据
        {
            QVariantMap eachVariantMap =  eachVariant.toMap();
            if(dateString == eachVariantMap["date"].toString())
            {
                for(QString dataAttribute : dataAttributeList)
                    stringList << eachVariantMap[dataAttribute].toString();
            }
        }
    }
    return stringList;
}
