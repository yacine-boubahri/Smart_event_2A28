#include "stat_dialog.h"
#include "ui_stat_dialog.h"

stat_Dialog::stat_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::stat_Dialog)
{
    ui->setupUi(this);
}

stat_Dialog::~stat_Dialog()
{
    delete ui;
}
