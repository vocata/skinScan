#ifndef MEASUREWIDGET_H
#define MEASUREWIDGET_H

#include "sources/thread/usbmeasure.h"
#include "sources/userstruct/datastore.h"
#include "sources/userclass/customnetwork.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QWidget>

class QPushButton;
class QPlainTextEdit;
class BarChart;

class MeasureWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MeasureWidget(QWidget *parent = 0);

signals:

public slots:
    void clear();

private:
    QPushButton *m_startMeasureButton= nullptr;
    QPushButton *m_skinEvaluationButton = nullptr;
    QPushButton *m_takePhotoButton = nullptr;
    QPushButton *m_showPhotoButton = nullptr;
    QPushButton *m_printReasultButton = nullptr;
    QPushButton *m_saveResultButton = nullptr;

    QPushButton *m_moisture = nullptr;
    QPushButton *m_grease = nullptr;
    QPushButton *m_temperature = nullptr;
    QPushButton *m_PH = nullptr;
    QPlainTextEdit *m_moistureInfo = nullptr;
    QPlainTextEdit *m_greaseInfo = nullptr;
    QPlainTextEdit *m_temperatureInfo = nullptr;
    QPlainTextEdit *m_PHInfo = nullptr;

    BarChart *m_moistureBar = nullptr;
    BarChart *m_greaseBar = nullptr;
    BarChart *m_temperatureBar = nullptr;
    BarChart *m_PHBar = nullptr;

    /* photo */
    QPixmap m_photh;

    /* data store */
    DataStore m_dataStore[4];

    /* measure thread */
    UsbMeasure m_usbMeasure;

    /* network manager */
    CustomNetwork *m_manager;


private slots:
    void m_startMeasure();
    void m_skinEvaluation();
    void m_takePhoto();
    void m_showPhoto();
    void m_printReasult();
    void m_saveReasult();

    void m_usbPullOut();
    void m_dataHandle(const QByteArray &data);
    void m_setSuggestion(const double &data, const qint16 &dataIndex);

    /* network */
    void m_uploadDataReply(CustomNetwork::Status status);

    /* sql */
    void m_saveUserData();


    QJsonDocument m_formatUploadData();
};

const quint8 Moisture = 0x01;
const quint8 Grease = 0x02;
const quint8 PH = 0x04;
const quint8 Temperature = 0x08;



#endif // MEASUREWIDGET_H
