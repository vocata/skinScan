#ifndef MESSAGEDIALOG_H
#define MESSAGEDIALOG_H

#include "sources/userclass/customdialog.h"

class QPushButton;
class QLabel;

class MessageDialog : public CustomDialog
{
    Q_OBJECT
public:
    enum Button { Ok, Yes, No };

    explicit MessageDialog(QWidget *parent = 0);
    void execWarning(const QString &msg, const QString title);
    void execInformation(const QString &msg, const QString title);

signals:

public slots:

private:
    QPushButton *m_okButton = nullptr;
    QPushButton *m_yesButton= nullptr;
    QPushButton *m_noButton = nullptr;
    QPushButton *m_messageIcon = nullptr;
    QLabel *m_messageLabel = nullptr;

private slots:
    void m_okButtonClicked();
    void m_yesButtonClicked();
    void m_noButtonClicked();
};

#endif // MESSAGEDIALOG_H
