#ifndef NETWORKWIDGET_H
#define NETWORKWIDGET_H

#include <QWidget>

class QLabel;
class QCheckBox;

class NetworkWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NetworkWidget(QWidget *parent = 0);
    void save();

signals:

public slots:

private:
    QLabel *m_syncLabel = nullptr;
    QCheckBox *m_moistureChecked = nullptr;
    QCheckBox *m_greaseChecked = nullptr;
    QCheckBox *m_temperatureChecked = nullptr;
    QCheckBox *m_phChecked = nullptr;

private slots:
    void m_recovery();
};

#endif // NETWORKWIDGET_H
