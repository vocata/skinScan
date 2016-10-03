#ifndef NETWORKWIDGET_H
#define NETWORKWIDGET_H

#include <QWidget>

class QLabel;
class QRadioButton;
class QButtonGroup;

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
    QRadioButton *m_autoSyncRadioButton = nullptr;
    QRadioButton *m_manualSyncRadioButton = nullptr;
    QButtonGroup *m_syncButtonGroup = nullptr;

private slots:
    void m_recovery();
};

#endif // NETWORKWIDGET_H
