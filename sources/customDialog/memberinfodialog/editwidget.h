#ifndef EDITWIDGET_H
#define EDITWIDGET_H

#include <QVariantMap>
#include <QWidget>

class QLabel;
class QLineEdit;
class QComboBox;
class QPushButton;
class DateEdit;

class EditWidget : public QWidget
{
    Q_OBJECT
public:
    explicit EditWidget(QWidget *parent = 0);

    void setInfo(QVariantMap info);
    QVariantMap getInfo() const;
    void save();
    void cancel();

signals:
    void infoEdited(bool isEdited);

public slots:

private:
    QLabel *m_phone;
    QLineEdit *m_phoneInfo;
    QLabel *m_name;
    QLineEdit *m_nameInfo;
    QLabel *m_qq;
    QLineEdit *m_qqInfo;
    QLabel *m_email;
    QLineEdit *m_emailInfo;
    QLabel *m_sex;
    QComboBox *m_sexInfo;
    QLabel *m_birthday;
    QPushButton *m_birthdayInfo;
    QLabel *m_age;
    QComboBox *m_ageInfo;

    DateEdit *m_dateEdit;

    QVariantMap m_info;
private slots:
    void m_infoEdited();
    void m_dateUpdate(const QString &date);
    void m_dateEditPopup();
};

#endif // EDITWIDGET_H
