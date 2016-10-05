#ifndef STATISTICSWIDGET_H
#define STATISTICSWIDGET_H

#include <QWidget>

#include "sources/userclass/customnetwork.h"

class QPushButton;
class QStackedWidget;
class PlotWidget;
class TableWidget;
class SyncDialog;

class StatisticsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StatisticsWidget(QWidget *parent = 0);
    void setPlotData(const QJsonDocument &document);
    void getData();
    void clear();

signals:

public slots:

private:
    QPushButton *m_chartButton;
    QPushButton *m_tableButton;
    QPushButton *m_moistureButton;
    QPushButton *m_greaseButton;
    QPushButton *m_temperatureButton;
    QPushButton *m_PHButton;
    QPushButton *m_localButton;
    QStackedWidget *m_stackedWidget;

    PlotWidget *m_moistureWidget;
    PlotWidget *m_greaseWidget;
    PlotWidget *m_tempWidget;
    PlotWidget *m_PHWidget;

    TableWidget *m_moistureTable;
    TableWidget *m_greaseTable;
    TableWidget *m_tempTable;
    TableWidget *m_PHTable;

    /* newwork */
    QVariantMap m_lastData;
    CustomNetwork *m_manager;

    /* dialog */
    SyncDialog *m_syncDialog;

    int m_row = 0;
    int m_column = 0;

private slots:
    void m_showSyncDialog();
    void m_downloadDataReply(CustomNetwork::Status status);
};

#endif // STATISTICSWIDGET_H
