#ifndef SYNCDIALOG_H
#define SYNCDIALOG_H

#include <QJsonDocument>
#include <QWidget>

#include "sources/userclass/customnetwork.h"
#include "sources/userclass/customdialog.h"

class QSqlQueryModel;
class QTableView;
class QTabWidget;
class QToolButton;
class QProgressBar;
class CustomNetwork;

class SyncDialog : public CustomDialog
{
    Q_OBJECT
public:
    explicit SyncDialog(const QString &account, QWidget *parent = 0);
    void sync();

    ~SyncDialog();

signals:
    void syncFinish();

public slots:

protected:
    void closeEvent(QCloseEvent *);

private:
    QSqlQueryModel *m_moistureModel = nullptr;
    QSqlQueryModel *m_greaseModel = nullptr;
    QSqlQueryModel *m_temperatureModel = nullptr;
    QSqlQueryModel *m_phModel = nullptr;
    QTableView *m_moistureView = nullptr;
    QTableView *m_greaseView = nullptr;
    QTableView *m_temperatureView = nullptr;
    QTableView *m_phView = nullptr;
    QTabWidget *m_tabWidget = nullptr;
    QToolButton *m_syncButton = nullptr;
    QProgressBar *m_progressBar = nullptr;
    CustomNetwork *m_manager = nullptr;

    /* sync */
    QString m_account;
    QTimer *m_timer;
    QMultiMap<QString, QJsonDocument> m_items;
    QMultiMap<QString, QJsonDocument>::iterator m_iterator;
    int m_syncCount = 0;

private slots:
    void m_setTable();

    /* sync */
    void m_syncData();
    void m_uploadDataReply(CustomNetwork::Status status);
    QJsonDocument m_formatUploadData(const QString &date, double value, qint64 deviceId, const QString &phone);
};

#endif // SYNCDIALOG_H
