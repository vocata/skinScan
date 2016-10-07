#include "passworddialog.h"

PasswordDialog::PasswordDialog(QWidget *parent) : CustomDialog(parent)
{

//    this->setWindowTitle(titleLabel);
//    this->setCentralWidgetLayout(vBox);
    this->setShadow(true);
    this->hideMinIcon();
    this->setFixedSize(500, 400);
    this->startAnimation();
    this->centralWidget()->setObjectName("centralDialog");
}
