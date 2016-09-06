#include "albumdialog.h"

#include <QToolButton>
#include <QScrollArea>
#include <QButtonGroup>
#include <QDesktopServices>
#include <QUrl>

#include <QDebug>

AlbumDialog::AlbumDialog(const QString &name, QWidget *parent) : CustomDialog(parent)
{
    m_dir = QDir(QString("image/%1").arg(name));

    QWidget *widget = new QWidget(this);
    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidget(widget);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    /* layout */
    QHBoxLayout *hBox = new QHBoxLayout();
    hBox->addWidget(scrollArea);
    this->setCentralWidgetLayout(hBox);

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
        connect(group, SIGNAL(buttonClicked(int)), this, SLOT(showImage(int)));
    }

    /* window attribution */
    this->hideMinIcon();
    this->setFixedSize(720, 450);
}

void AlbumDialog::showImage(int id)
{
    const QUrl memberUrl(QDir(m_image.value(id)).absolutePath());
    QDesktopServices::openUrl(memberUrl);
}
