#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "billeterie.h"
#include <QMessageBox>
#include <QtWidgets>
#include <QIntValidator>
#include <QTableWidget>
#include <QtPrintSupport/QPrinter>
#include <QPdfWriter>
#include <QPainter>
#include <QDate>
#include <QFileDialog>
#include <QFile>
#include <QTextDocument>
#include <QTextStream>
#include <QPdfWriter>
#include <QFileInfo>
#include "smtp.h"
#include <QAbstractSocket>
#include <QSslSocket>
#include <fstream>
#include <QPixmap>
#include<QDirModel>
#include <QtSvg/QSvgRenderer>
#include  "qrcode.h"
#include  "arduino.h"
#include <QDebug>

using qrcodegen::QrCode ;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    Billeterie b;
    QSqlQuery query;
    QMessageBox msgBox;
    ui->setupUi(this);
     //ui->le_cin->setValidator( new QIntValidator(0, 99999999, this));
    ui->Tab_Billeterie->setModel(b.afficher_client());
    ui->le_cin->setValidator(new QIntValidator(0,999999999,this));
    connect(ui->sendBtn,SIGNAL(clicked()),this,SLOT(sendMail()));
    connect(ui->browse,SIGNAL(clicked()),this,SLOT(browse()));


    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
    }
     QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
     //le slot update_label suite à la reception du signal readyRead (reception des données).
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_label()
{
    Billeterie b;
    QSqlQuery query;
    QMessageBox msgBox;

    int Nb_Billet;
   QString Nb_Billet1;
   data=A.read_from_arduino();
    if(data=="1")
{
        ui->label_res->setText("ON"); // si les données reçues de arduino via la liaison série sont égales à 1
        query.prepare("select NB_BILLET from BILLETERIE where CIN_CLIENT=777 ");

        query.exec();
        query.first();
        Nb_Billet=query.value(0).toInt();
        qDebug()<<query.value(0);
        Nb_Billet=Nb_Billet-1;

        Nb_Billet1=QString::number(Nb_Billet);
        ui->label_nb->setText(Nb_Billet1);
    // alors afficher ON
}
    else if (data=="0")
        ui->label_res2->setText("OFF");   // si les données reçues de arduino via la liaison série sont égales à 0
     //alors afficher OFF
}
void MainWindow::on_pb_ajouter_clicked()
{
    int CIN_Client=ui->le_cin->text().toInt();
    int Age_Client=ui->le_age->text().toInt();
    int Nb_Billet=ui->le_nbbillet->text().toInt();
    int Num_Tel=ui->le_num->text().toInt();
    QString Nom_Client=ui->le_nom->text();
    QString Prenom_Client=ui->le_prenom->text();
    Billeterie b(CIN_Client,Nom_Client,Prenom_Client,Num_Tel,Age_Client,Nb_Billet);
bool test=b.ajouter_client();
bool testt=b.reduction(Nb_Billet);
if(test)
{
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("ajout effectue .\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->Tab_Billeterie->setModel(b.afficher_client());
}
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                    QObject::tr("ajout non effectue.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
if(testt&&test){
   QMessageBox::information(nullptr, QObject::tr("OK"),
               QObject::tr("reduction effectuee avec succes.\n"
                           "Click Cancel to exit."), QMessageBox::Cancel);
}
}




void MainWindow::on_pb_supprimer_2_clicked()
{
  Billeterie b1;
b1.setCIN_Client(ui->le_cin_asupprimer->text().toInt());
bool test=b1.supprimer_client(b1.getCIN_Client());
if(test)
{

        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("suppression effectue.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->Tab_Billeterie->setModel(b.afficher_client());

}
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                    QObject::tr("suppression non effectue.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

/*void MainWindow::on_Tab_Billeterie_activated(const QModelIndex &index)
{
       int CIN_Client=ui->Tab_Billeterie->model()->data(index).toInt() ;
         QString cin_string = QString::number(CIN_Client) ;

        QSqlQuery qry ;
        qry.prepare("SELECT * FROM BIllETTERIE WHERE CIN_CLIENT='"+cin_string+"' or NOM_CLIENT='"+cin_string+"' or PRENOM_CLIENT='"+cin_string+"'or NUM_TEL='"+cin_string+"' or AGE_CLIENT='"+cin_string+"'  or NB_BILLET='"+cin_string+"'") ;
        if(qry.exec())
        {
            while(qry.next())
            {
                ui->up_cin->setText(qry.value(0).toString()) ;
                ui->up_nom->setText(qry.value(1).toString()) ;
                ui->up_prenom->setText(qry.value(2).toString()) ;
                ui->up_num->setText(qry.value(3).toString()) ;
                ui->up_age->setText(qry.value(4).toString()) ;
                ui->up_nb->setText(qry.value(5).toString());
            }
        }


}*/


void MainWindow::on_pb_modivicated_clicked()
{
            int CIN_Client = ui->up_cin->text().toInt() ;
            int Num_Tel = ui->up_num->text().toInt() ;
            int Nb_Billet = ui->up_nb->text().toInt() ;
            int Age_Client = ui->up_age->text().toInt() ;
            QString Nom_Client = ui->up_nom->text() ;
            QString Prenom_Client = ui->up_prenom->text() ;

          Billeterie b(CIN_Client,Nom_Client,Prenom_Client,Num_Tel, Age_Client,Nb_Billet);
          //Cito.setcin(ui->le_cin_2->text().toInt()) ;
          bool test=b.modifier() ;
            QMessageBox msgBox;
            if(test)
               {
                msgBox.setText("Modification avec succes.");
                ui->Tab_Billeterie->setModel(b.afficher_client()) ;
               }
            else
                msgBox.setText("Echec de Modification.!!!");
                msgBox.exec();
}

void MainWindow::on_pb_tri_clicked()
{
    Billeterie b;
        ui->Tab_Billeterie->setModel(b.tri());
}


void MainWindow::on_pdf_clicked()
{
    {
        QString strStream;
            strStream = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
                if (QFileInfo(strStream).suffix().isEmpty())
                    { strStream.append(".pdf"); }

                QPrinter printer(QPrinter::PrinterResolution);
                printer.setOutputFormat(QPrinter::PdfFormat);
                printer.setPaperSize(QPrinter::A4);
                printer.setOutputFileName(strStream);



                      QTextStream out(&strStream);

                      const int rowCount = ui->Tab_Billeterie->model()->rowCount();
                      const int columnCount = ui->Tab_Billeterie->model()->columnCount();
                      QString TT = QDateTime::currentDateTime().toString();
                      out <<"<html>\n"
                            "<head>\n"
                             "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                          << "<title>ERP - COMmANDE LIST<title>\n "
                          << "</head>\n"
                          "<body bgcolor=#ffffff link=#5000A0>\n"
                             "<h1 style=\"text-align: center;\"><strong> "+TT+"</strong></h1>"
                            +"<img src=C:\\Users\\asus\\Desktop\\pdf\\logo_projet />"
                          "<h1 style=\"text-align: center;\"><strong> ****LISTE DES BILLETERIE **** </strong></h1>"

                          "<table style=\"text-align: center; font-size: 10px;\" border=1>\n "
                            "</br> </br>";
                      // headers
                      out << "<thead><tr bgcolor=#d7e5ff>";
                      for (int column = 0; column < columnCount; column++)
                          if (!ui->Tab_Billeterie->isColumnHidden(column))
                              out << QString("<th>%1</th>").arg(ui->Tab_Billeterie->model()->headerData(column, Qt::Horizontal).toString());
                      out << "</tr></thead>\n";

                      // data table
                      for (int row = 0; row < rowCount; row++) {
                          out << "<tr>";
                          for (int column = 0; column < columnCount; column++)
                        {
                              if (!ui->Tab_Billeterie->isColumnHidden(column)) {
                                  QString data =ui->Tab_Billeterie->model()->data(ui->Tab_Billeterie->model()->index(row, column)).toString().simplified();
                                  out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;")); //pas compriis
                              }
                          }
                          out << "</tr>\n";
                      }
                      out <<  "</table>\n"
                          "</body>\n"
                          "</html>\n";

                      QTextDocument document;
                      document.setHtml(strStream);
                      document.print(&printer);

    }
}

void MainWindow::on_pb_rechercher_clicked()
{
   int CIN_Client=(ui->le_cin_arechercher->text().toInt());
   ui->Tab_Billeterie->setModel(b.recherche(CIN_Client));

      //ui->Tab_Billeterie->setModel(b.rechercher(CIN_Client)) ;

}


//mailing
/*void MainWindow::browse()
{
    files.clear();

        QFileDialog dialog(this);
        dialog.setDirectory(QDir::homePath());
        dialog.setFileMode(QFileDialog::ExistingFiles);

        if (dialog.exec())
            files = dialog.selectedFiles();

        QString fileListString;
        foreach(QString file, files)
            fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );
        ui->file->setText(fileListString);
}*/
void  MainWindow::browse()
{
    files.clear();

    QFileDialog dialog(this);
    dialog.setDirectory(QDir::homePath());
    dialog.setFileMode(QFileDialog::ExistingFiles);

    if (dialog.exec())
        files = dialog.selectedFiles();

    QString fileListString;
    foreach(QString file, files)
        fileListString.append( "\"" + QFileInfo(file).fileName() + "\" " );

    ui->file->setText( fileListString );

}
void   MainWindow::sendMail()
{
    Smtp* smtp = new Smtp("salhi.nour@esprit.tn",ui->mail_pass->text(), "smtp.gmail.com");
    connect(smtp,SIGNAL(status(QString)),this,SLOT(mailSent(QString)));

    if( !files.isEmpty() )
        smtp->sendMail("salhi.nour@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText(), files );
    else
        smtp->sendMail("salhi.nour@esprit.tn", ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
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

void MainWindow::on_Qrcode_clicked()
    {
      Billeterie A;
        if(ui->Tab_Billeterie->currentIndex().row()==-1)
               QMessageBox::information(nullptr, QObject::tr("Suppression"),
                                        QObject::tr("Veuillez Choisir une personne du Tableau.\n"
                                                    "Click Ok to exit."), QMessageBox::Ok);
           else
           {

                       A.setNom_Client(ui->le_nom ->text());
                       A.setPrenom_Client(ui->le_prenom ->text());
                       A.setCIN_Client(ui->le_cin ->text().toInt());
                       A.setAge_Client(ui->le_age ->text().toInt());
                       A.setNb_Billet(ui->le_nbbillet->text().toInt());
                       A.setNum_Tel(ui->le_num ->text().toInt());

               // int idAnim=ui->tab_animaux->model()->data(ui->tab_animaux->model()->index(ui->tab_animaux->currentIndex().row(),0)).toInt();


             QString  rawQr = "NOM_CLIENT:%1 CIN_CLIENT:%2 NB_BILLET:%3 NUM_TEL:%4 NOM_CLIENT:%5 PRENOM_CLIENT:%6" ;
                rawQr = rawQr.arg(A.getNom_Client()).arg(A.getCIN_Client()).arg(A.getNb_Billet()).arg(A.getNum_Tel()).arg(A.getNom_Client()).arg(A.getPrenom_Client());
                QrCode qr = QrCode::encodeText(rawQr.toUtf8().constData(), QrCode::Ecc::HIGH);


              //  const QrCode qr = QrCode::encodeText(std::to_string(idAnim).c_str(), QrCode::Ecc::LOW);
                std::ofstream myfile;
                myfile.open ("qrcode.svg") ;
                myfile << qr.toSvgString(1);
                myfile.close();
                QSvgRenderer svgRenderer(QString("qrcode.svg"));
                QPixmap pix( QSize(140, 140) );
                QPainter pixPainter( &pix );
                svgRenderer.render( &pixPainter );
                ui->label_qrcode->setPixmap(pix);
           }
    }
void MainWindow::on_pushButton_2_clicked()
{
    A.write_to_arduino("0");
}

void MainWindow::on_pushButton_clicked()
{
    A.write_to_arduino("1");
}
