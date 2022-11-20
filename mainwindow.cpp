#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "reclamation.h"
#include <QMessageBox>
#include <QDate>
#include <QDesktopServices>
#include <QFile>
#include <QTextDocument>
#include <QTextStream>
#include <QPdfWriter>
#include <QPainter>
#include <QSqlQuery>
#include <QFileDialog>
#include <QSslSocket>
#include <QAbstractSocket>
#include "smtp.h"
#include <QtSvg/QSvgRenderer>
#include <fstream>
#include <QPixmap>
#include<QDirModel>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->tableView->setModel(rtmp.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
ui->tabWidget->removeTab(index);
}


 void MainWindow::on_ajouter_clicked()
{
     QFile f("C:/Users/Ouaiss/Downloads/Atelier_Connexion/historic.txt");
         if(!f.open(QFile::WriteOnly |QIODevice::Append | QFile::Text))
         {
        // QMessageBox::warning(this,"title","file not open");
         }
         QTextStream outt(&f);
         QString text = "  ajouter une reclamation \r\n";
         QString sDate = QDateTime::currentDateTime().toString("dddd dd MMMM yyyy hh:mm:ss.zzz :");
         outt << sDate;
         outt << text ;
         f.flush();
         f.close();

    int id=ui->LE1->text().toInt();
    QString nom=ui->LE2->text();
    QString prenom=ui->LE3->text();
    QString type=ui->LE->text();
    QDate datee=ui->dateTimeEdit->date();
    reclamation R(  id,nom,prenom,type,datee);
    bool test=R.ajouter();

     if (test)
     {

            QMessageBox::information(nullptr,QObject::tr("ok"),
                    QObject::tr("ajout effectue\n"
                                "click cancel to exit."),QMessageBox::Cancel);
}
     else {
         QMessageBox::critical(nullptr,QObject::tr(" not ok"),
                 QObject::tr("ajout non effectue\n"
                             "click cancel to exit."),QMessageBox::Cancel);
     }
}


void MainWindow::on_supprimer_clicked()
{
    int id=ui->LE6->text().toInt();
    bool test=rtmp.supprimer(id);

    if (test)
    {

           QMessageBox::information(nullptr,QObject::tr("ok"),
                   QObject::tr("suppression effectue\n"
                               "click cancel to exit."),QMessageBox::Cancel);
}


}



void MainWindow::on_tri_clicked()
{



         bool test = r.tri() ;

                  if (test){



               QMessageBox::information(nullptr, QObject::tr("OK"),
                           QObject::tr("tri effectué.\n"
                                       "Click Cancel to exit."), QMessageBox::Cancel);


     }


          else
              {
               QMessageBox::critical(nullptr, QObject::tr("not OK"),
                           QObject::tr("tri non effectué .\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);
         }
                ui->tableView->setModel(rtmp.tri());
}













void MainWindow::on_stat_clicked()
{

    bool test = r.tri() ;

             if (test){



          QMessageBox::information(nullptr, QObject::tr("OK"),
                      QObject::tr("statistique effectué.\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);


}


     else
         {
          QMessageBox::critical(nullptr, QObject::tr("not OK"),
                      QObject::tr("statistique non effectué .\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
    }
           ui->tableView->setModel(r.stat());
}

void MainWindow::on_modifier_clicked()
{
    {QFile f("C:/Users/Ouaiss/Downloads/Atelier_Connexion/historic.txt");
        if(!f.open(QFile::WriteOnly |QIODevice::Append | QFile::Text))
        {
       // QMessageBox::warning(this,"title","file not open");
        }
        QTextStream outt(&f);
            QString text = "  modification sur les  reclamations \r\n";
            QString sDate = QDateTime::currentDateTime().toString("dddd dd MMMM yyyy hh:mm:ss.zzz :");
            outt << sDate;
            outt << text ;
            f.flush();
            f.close();
    int id=ui->LE2->text().toInt();
    QString nom=ui->LE2->text();
    QString prenom=ui->LE3->text();
    QString type=ui->LE2_2->text();
    QDate datee=ui->dateTimeEdit->date();


      reclamation (id,nom,prenom,type,datee);
      bool test=r.modifier() ;

        QMessageBox msgBox;

        if(test)
           {
            msgBox.setText("Modification avec succes.");
          ui->TB4->setModel(r.afficher()) ;
           }
        else
            msgBox.setText("Echec de Modification.!!!");
            msgBox.exec();
    }
}
void MainWindow::on_chercher_clicked()
{
    int id=(ui->LE_2->text().toInt());
    ui->TB4->setModel(rtmp.chercher(id));
    bool test=rtmp.chercher(id) ;
    QMessageBox msgBox;

    if(test)
       {
        msgBox.setText("Modification avec succes.");
     ui->TB4->setModel(rtmp.afficher());
    }
      else
        msgBox.setText("Echec de Modification.!!!");
        msgBox.exec();
}


void MainWindow::on_exporter_clicked()
{


        QPdfWriter pdf("C:/Users/Ouaiss/Downloads/Atelier_Connexion/reclamation.pdf");

           QPainter painter(&pdf);

           int i = 4000;
           painter.setPen(Qt::black);
           painter.setFont(QFont("Konztante", 30));
           painter.drawPixmap(QRect(100,400,2000,2000),QPixmap("C:/Users/Ouaiss/Downloads/Atelier_Connexion/reclamation.pdf"));
           painter.drawText(1500,1500,"LISTE DES RECLAMATIONS");
           painter.setPen(Qt::black);
           painter.setFont(QFont("Konztante", 50));
           painter.setPen(Qt::black);
           painter.setFont(QFont("Konztante", 9));
           painter.drawText(300,3300,"ID");
           painter.drawText(2300,3300,"Nom");
           painter.drawText(4300,3300,"Prenom");
           painter.drawText(6000,3300,"type");
           painter.drawText(8300,3300,"date");
           QSqlQuery query;
           query.prepare("select * from rec");
           query.exec();
           while (query.next())
           {
               painter.drawText(300,i,query.value(0).toString());
               painter.drawText(2300,i,query.value(1).toString());
               painter.drawText(4300,i,query.value(2).toString());
               painter.drawText(6300,i,query.value(3).toString());
               painter.drawText(8000,i,query.value(4).toString());
               i = i +500;
           }

           int reponse = QMessageBox::question(this, "PDF généré", "Afficher le PDF ?", QMessageBox::Yes |  QMessageBox::No);
           if (reponse == QMessageBox::Yes)
           {
               QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/Ouaiss/Downloads/Atelier_Connexion/reclamation.pdf"));

               painter.end();
           }
           if (reponse == QMessageBox::No)
           {
               painter.end();
           }
    }

//void   MainWindow::mailSent(QString status)
//{

//    if(status == "Message sent")
//        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
//    ui->rcpt->clear();
//    ui->subject->clear();
//    ui->file->clear();
//    ui->msg->clear();
//    ui->mail_pass->clear();
//}


void MainWindow::on_Mail_clicked()
{
    Smtp* smtp = new Smtp("ouaissaeichi.chaouch@esprit.tn",ui->mail_pass->text(), "smtp.gmail.com");
      connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));

     if( !files.isEmpty() )
          smtp->sendMail("ouaissaechi.chaouch@esprit.tn", ui->rcpt->text() , ui->subject->text() ,ui->msg->text(), files );
      else
         smtp->sendMail("ouaissaechi.chaouch@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->text());

}
void   MainWindow::mailSent(QString status)
{

    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
    ui->rcpt->clear();
    ui->subject->clear();
   ui->file->clear();
    ui->msg->clear();
    ui->mail_pass->clear();
}
void  MainWindow::browse()
{
    files.clear();

    QFileDialog dialog (this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file->setText( fileListString );

}
