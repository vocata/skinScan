#ifndef MEMBERINFODIALOG_H
#define MEMBERINFODIALOG_H

#include <QWidget>

#include "sources/userclass/customdialog.h"
#include "sources/userclass/customnetwork.h"

class QPushButton;
class InfoWidget;
class EditWidget;
class QStackedWidget;
class QToolButton;
class CustomNetwork;

class MemberInfoDialog : public CustomDialog
{
    Q_OBJECT
public:
    explicit MemberInfoDialog(QWidget *parent = 0);

signals:
    void infoChanged();

public slots:

private:
    QPushButton *m_icon;
    InfoWidget *m_infoWidget;
    EditWidget *m_editWidget;
    QStackedWidget *m_stackedWidget;
    QToolButton *m_editButton;
    QToolButton *m_confirmButton;
    QToolButton *m_cancelButton;
    CustomNetwork *m_manager;

private slots:
    void m_edit();
    void m_save();
    void m_cancel();
    void m_showEditWidget();
    void m_showInfoWidget();
    void m_setIcon();

    void m_getUserInfoReply(CustomNetwork::Status status);
    void m_updateUserInfoReply(CustomNetwork::Status status);
};

#endif // MEMBERINFODIALOG_H
