#include "albumdialog.h"

#include <QToolButton>
#include <QScrollArea>
#include <QButtonGroup>
#include <QDesktopServices>
#include <QUrl>
#include <QLabel>
#include <QScrollBar>

#include <QDebug>

AlbumDialog::AlbumDialog(const QString &name, QWidget *parent) : CustomDialog(parent)
{
    m_dir = QDir(QString("image/%1").arg(name));
    m_scrollArea = new QScrollArea(this);
    QWidget *widget = new QWidget();
    widget->setObjectName("scrollWidget");

    m_scrollArea->setWidget(widget);
    m_scrollArea->setVerticalScrollBar(new QScrollBar(this));
    m_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_scrollArea->setObjectName("scrollArea");

    /* 读取图片 */
    if(m_dir.exists()) {
        auto imageList = m_dir.entryInfoList(QDir::Files);
        int row = 5;
        int column = 5;
        QButtonGroup *group = new QButtonGroup(this);
        for(auto image: imageList) {
            QToolButton *button = new QToolButton(widget);
            button->setIcon(QIcon(image.filePath()));
            button->setText(image.baseName());
            button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
            button->setIconSize(QSize(120, 120));
            button->setFixedSize(QSize(130, 130));
            button->move(row, column);
            group->addButton(button);

            m_image.insert(group->id(button), image.filePath());
            row += 135;
            if(row == 680) {
                column += 135;
                row = 5;
            }
        }
        widget->adjustSize();
        /* connect */
        connect(group, SIGNAL(buttonClicked(int)), this, SLOT(m_showImage(int)));
    }

    /* layout */
    QHBoxLayout *hBox = new QHBoxLayout();
    hBox->addWidget(m_scrollArea);
    this->setCentralWidgetLayout(hBox);

    /* window attribution */
    this->hideMinIcon();
    this->setShadow(false);
    this->resize(720, 450);
    this->setWindowTitle(new QLabel("相片"));
    this->startAnimation();
    this->centralWidget()->setObjectName("centralDialog");
}

void AlbumDialog::m_showImage(int id)
{
    const QUrl memberUrl(QDir(m_image.value(id)).absolutePath());
    QDesktopServices::openUrl(memberUrl);
}
