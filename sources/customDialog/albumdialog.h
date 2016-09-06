#ifndef ALBUMDIALOG_H
#define ALBUMDIALOG_H

#include "sources/userclass/customdialog.h"

#include <QDir>
#include <QGridLayout>
#include <QMultiMap>

class QAbstractButton;

class AlbumDialog : public CustomDialog
{
    Q_OBJECT
public:
    explicit AlbumDialog(const QString &name, QWidget *parent = 0);

signals:

public slots:

private:
    QDir m_dir;
    QMap<int, QString> m_image;
    QGridLayout *m_hBox = nullptr;

private slots:
    void showImage(int id);
};

#endif // ALBUMDIALOG_H
