#ifndef PASSWORDDIALOG_H
#define PASSWORDDIALOG_H

#include <QWidget>

#include "sources/userclass/customdialog.h"

class PasswordDialog : public CustomDialog
{
    Q_OBJECT
public:
    explicit PasswordDialog(QWidget *parent = 0);

signals:

public slots:
};

#endif // PASSWORDDIALOG_H
