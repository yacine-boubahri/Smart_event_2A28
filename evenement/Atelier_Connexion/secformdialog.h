#ifndef SECFORMDIALOG_H
#define SECFORMDIALOG_H

#include <QDialog>

namespace Ui {
class secformdialog;
}

class secformdialog : public QDialog
{
    Q_OBJECT

public:
    explicit secformdialog(QWidget *parent = nullptr);
    ~secformdialog();

private:
    Ui::secformdialog *ui;
};

#endif // SECFORMDIALOG_H
