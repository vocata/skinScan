#ifndef DATEEDIT_H
#define DATEEDIT_H

#include <QWidget>

class QComboBox;

class DateEdit : public QWidget
{
    Q_OBJECT
public:
    explicit DateEdit(QWidget *parent = 0);
    void setDate(const QDate &date);

signals:
    void dateChanged(const QString &date);

public slots:

private:
    QComboBox *m_yearEdit;
    QComboBox *m_monthEdit;
    QComboBox *m_dayEdit;

private slots:
    void m_updateDay();
    void m_currentDay();
};

#endif // DATEEDIT_H
