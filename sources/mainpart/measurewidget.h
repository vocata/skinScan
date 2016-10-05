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

    /* 照片 */
    QPixmap m_photh;

    /* 数据保存 */
    DataStore m_dataStore[4];

    /* 测量的线程 */
    UsbMeasure m_usbMeasure;

    /* 网络管理 */
    CustomNetwork *m_manager;

    /* 提交数据标志 */
    bool m_commit = false;


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

constexpr quint8 Moisture = 0x01;
constexpr quint8 Grease = 0x02;
constexpr quint8 PH = 0x04;
constexpr quint8 Temperature = 0x08;

#endif // MEASUREWIDGET_H
