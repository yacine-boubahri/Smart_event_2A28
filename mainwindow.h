#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "billeterie.h"
#include <QFile>
#include <QFileDialog>
#include "smtp.h"
#include <QDialog>
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

    void on_pb_ajouter_clicked();

    void on_pb_supprimer_2_clicked();

    //void on_pb_modifier_clicked();

   //void on_Tab_Billeterie_activated(const QModelIndex &index);

    //void on_pb_ajouter_2_clicked();

   // void on_pb_modifier1_clicked();

  //  void on_modifier_clicked();

    void on_pb_modivicated_clicked();

    void on_pb_tri_clicked();

   // void on_pushButton_6_clicked();

    void on_pdf_clicked();

    void on_pb_rechercher_clicked();

  //  void on_Reduction_clicked();

    //void on_pushButton_clicked();


    void mailSent(QString);
    void sendMail();
    void browse();

    //void on_browse_clicked();

    //void on_sendBtn_clicked();

    void on_Qrcode_clicked();



private:
    Ui::MainWindow *ui;
    Billeterie b;
    QStringList files ;
    QTcpSocket *socket;
};

#endif // MAINWINDOW_H
