#ifndef DATASTORE_H
#define DATASTORE_H

#include <QString>

struct DataStore
{
    QString account;
    QString measureTime;
    quint64 deviceId = 0;
    double data = 0;

    bool hasData() const
    {
        return deviceId;
    }

    void clear()
    {
        data = 0;
        measureTime.clear();
        deviceId = 0;
        account.clear();
    }
};

#endif // DATASTORE_H

