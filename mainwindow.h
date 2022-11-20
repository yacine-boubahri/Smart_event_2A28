#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "reclamation.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_tabWidget_tabCloseRequested(int index);



    void on_ajouter_clicked();



    void on_supprimer_clicked();

    void on_tri_clicked();







    void on_stat_clicked();


    void on_modifier_clicked();

    void on_chercher_clicked();

    void on_exporter_clicked();

    void on_Mail_clicked();

               void mailSent(QString);
               void browse();




private:
    Ui::MainWindow *ui;
    reclamation rtmp,r;
QStringList files ;
 QTcpSocket *socket ;
};

#endif // MAINWINDOW_H
