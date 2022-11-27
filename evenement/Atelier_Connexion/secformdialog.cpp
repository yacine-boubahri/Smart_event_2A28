#include "secformdialog.h"
#include "ui_secformdialog.h"
#include <QtQml>
#include <QQuickView>
//#include "qtquickcontrolsapplication.h"
//#include "sqleventmodel.h"

secformdialog::secformdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::secformdialog)
{
    ui->setupUi(this);


    /*qmlRegisterType<SqlEventModel>("org.qtproject.examples.calendar", 1, 0, "SqlEventModel");
    ui->quickWidget->setSource(QUrl("qrc:/qml/main.qml"));
    ui->quickWidget->show();*/
}

secformdialog::~secformdialog()
{
    delete ui;
}
