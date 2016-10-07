#ifndef HELPWIDGET_H
#define HELPWIDGET_H

#include <QWidget>

class QLabel;
class QPushButton;

class HelpWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HelpWidget(QWidget *parent = 0);

signals:

public slots:

private:
    QLabel *m_descriptionLabel;
    QLabel *m_imageLabel;
    QPushButton *m_showButton;

private slots:
    void m_showVedio();
};

#endif // HELPWIDGET_H
