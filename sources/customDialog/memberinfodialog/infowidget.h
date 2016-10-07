#ifndef INFOWIDGET_H
#define INFOWIDGET_H

#include <QWidget>

class QLabel;

class InfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit InfoWidget(QWidget *parent = 0);
    void setInfo(QVariantMap info);

signals:

public slots:

private:
    QLabel *m_phone;
    QLabel *m_phoneInfo;
    QLabel *m_name;
    QLabel *m_nameInfo;
    QLabel *m_qq;
    QLabel *m_qqInfo;
    QLabel *m_email;
    QLabel *m_emailInfo;
    QLabel *m_sex;
    QLabel *m_sexInfo;
    QLabel *m_birthday;
    QLabel *m_birthdayInfo;
    QLabel *m_age;
    QLabel *m_ageInfo;
};

#endif // INFOWIDGET_H
