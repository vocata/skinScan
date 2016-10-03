#ifndef REGULARWIDGET_H
#define REGULARWIDGET_H

#include <QWidget>

class QLabel;
class QRadioButton;
class QButtonGroup;

class RegularWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RegularWidget(QWidget *parent = 0);
    void save();

signals:

public slots:

private:
    QLabel *m_loginLabel = nullptr;
    QLabel *m_dataLabel = nullptr;
    QRadioButton *m_saveLoginInfoButton = nullptr;
    QRadioButton *m_notSaveLoginInfoButton = nullptr;
    QRadioButton *m_saveToCloudButton = nullptr;
    QRadioButton *m_saveToLocalButton = nullptr;
    QButtonGroup *m_loginButtonGroup = nullptr;
    QButtonGroup *m_dataButtonGroup = nullptr;

private slots:
    void m_recovery();
};

#endif // REGULARWIDGET_H
