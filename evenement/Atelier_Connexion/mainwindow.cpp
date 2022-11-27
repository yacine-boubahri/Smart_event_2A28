#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "evenement.h"
#include <QString>
#include <QMessageBox>
#include <QDebug>
#include <QDesktopServices>
#include <QSqlQuery>
#include <QUrl>
#include <QIntValidator>
#include "map.h"
#include <QApplication>
#include <QComboBox>
#include <QDate>
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QPrinter>
#include <QFileDialog>
#include <QTextDocument>
#include <QDateTime>
#include <QTextStream>
#include "statistique.h"


#include <QCamera>
#include <QCameraImageCapture>
#include <QCameraViewfinder>
#include <QVBoxLayout>
#include  <QFileDialog>


#include <QMenu>
#include <QAction>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    /*QPieSeries *series = new QPieSeries() ;
    series->append("Mariage",80) ;
    series->append("Fetes",70) ;
    series->append("conference",60) ;
    series->append("Art",50) ;

    QChart *chart = new QChart() ;
    chart->addSeries(series) ;
    chart->setTitle("Pie chart for the EVENTS") ;

    QChartView *chartview = new QChartView(chart) ;
    chartview->setParent(ui->stat) ;*/


    //ui->tab_evenement->setModel(E.afficher()) ;
    ui->supprimer_2->setVisible(false) ;
    ui->ok_1->setVisible(false) ;
    ui->update_id->setVisible(false) ;
    ui->modification->setVisible(false) ;
    ui->l_id->setValidator(new QIntValidator(0,999,this)) ;
     ui->stat->addWidget(E.stat()) ;

    /* QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                        QCoreApplication::organizationName(), QCoreApplication::applicationName());

     ui->WebBrowser->dynamicCall("Navigate(const QString&)", "https://www.google.com/maps/place/ESPRIT/@36.9016729,10.1713215,15z");*/

     //maps
         /*QSettings settings(QSettings::IniFormat, QSettings::UserScope,
                            QCoreApplication::organizationName(), QCoreApplication::applicationName());

         ui->map->dynamicCall("Navigate(const QString&)", "https://www.google.com/maps/place/ESPRIT/@36.9016729,10.1713215,15z");*/
       /* mCamera = new QCamera(this) ;
        mCameraViewfinder= new QCameraViewfinder(this) ;
        mCameraImageCapture= new QCameraImageCapture(mCamera,this) ;
        mLayout = new QVBoxLayout ;
        mOptionMenu = new QMenu("option", this) ;

       mEncenderAction = new QAction("Encender",this) ;
       mCapturarAction = new QAction("Capturer", this) ;
       mOptionMenu->addActions({mEncenderAction, mApagarAction, mCapturarAction }) ;
       ui->optionpushButton->setMenu(mOptionMenu) ;
       mCamera->setViewfinder(mCameraViewfinder) ;
       mLayout->addWidget(mCameraViewfinder) ;
       mLayout->setMargin(0) ;
  ui->scrollArea->setLayout(mLayout) ;

  connect(mEncenderAction, &QAction::triggered, [&]()
  {
      mCamera->start() ;
  }) ;

  connect(mApagarAction , &QAction::triggered, [&]() {
      mCamera->stop() ;
  }) ;

  connect(mCapturarAction , &QAction::triggered, [&] {
      auto filename = QFileDialog::getSaveFileName(this ,"Capturer" , "/" , "Imagen (*.jpg; *.jpeg)" ) ;
      if(filename.isEmpty() )
      {

      }
      mCameraImageCapture->setCaptureDestination(QCameraImageCapture::CaptureToFile) ;
      QImageEncoderSettings imageEcoderSettings ;
       imageEcoderSettings.setCodec("image/jpeg") ;
       imageEcoderSettings.setResolution(1600,1200) ;
       mCameraImageCapture->setEncodingSettings(imageEcoderSettings) ;
       mCamera->setCaptureMode(QCamera::CaptureStillImage) ;
       mCamera->start() ;
       mCamera->searchAndLock() ;
       mCameraImageCapture->capture(filename) ;
       mCamera->unlock() ;

  }) ;*/
}


MainWindow::~MainWindow()
{
    delete ui;
}




//*********************************AJOUTER************************************

void MainWindow::on_pb_confirmer_clicked()
{
    int id = ui->l_id->text().toInt() ;
   // QString type_evenement= ui->l_type->text() ;
    //QString date = ui->l_date->text() ;
    QDate d = ui->l_date->date() ;
    QString date = d.toString() ;
    QString Horaire = ui->l_horaire->text() ;
    QString type_evenement = ui->l_type->currentText() ;

    Evenement E(id,date,Horaire,type_evenement) ;
    bool test=E.confirmer();
    if (test){
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("ajout effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


}
    else
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                    QObject::tr("ajout non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    //ui->tab_evenement->setModel(E.afficher()) ;
}

//*********************************AFFICHER*************************************


void MainWindow::on_afficher_clicked()
{
    Evenement E1 ;
    ui->tab_evenement->setModel(E1.afficher()) ;
}

//******************************supprimer********************************


void MainWindow::on_ok_1_clicked()
{
    Evenement E1; E1.setid(ui->supprimer_2->text().toInt()) ;
    bool test=E1.supprimer(E1.getid()) ;
    if (test){
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("suppression effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


  }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                    QObject::tr("Echec de suppression .\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    ui->tab_evenement->setModel(E1.afficher()) ;

}

void MainWindow::on_supprimer_1_clicked()
{
    ui->supprimer_2->setVisible(true) ;
    ui->ok_1->setVisible(true) ;

}


//*****************************************LOCALISATION*****************************

void MainWindow::on_localisation_clicked()
{
   //QDesktopServices::openUrl(QUrl("https://www.google.tn/maps/@36.6043608,10.0988642,10z?hl=fr")) ;

/*Map map ;
map.setModal(true) ;
map.exec() ; //show my window*/

    map = new Map(this) ;
    map->show() ;


}


//*********************************UPDATE_VISIBLE********************************************

void MainWindow::on_modifier_clicked()
{
    ui->update_id->setVisible(true) ;
    ui->modification->setVisible(true) ;

}


//*********************************RECHERCHER****************************************

void MainWindow::on_rechercher_clicked()
{


    Evenement E ;


    int lid = ui->l_rechercher->text().toInt() ;


    //QString id_string = QString::number(lid) ;

    ui->tab_evenement->setModel(E.rechercher(lid)) ;
}


//******************************UPDATE**************************************

void MainWindow::on_modifier_con_clicked()
{

    int id = ui->update_id->text().toInt() ;
    //QString date = ui->up_date->text() ;
    QDate d = ui->up_date->date() ;
    QString date = d.toString() ;
    QString Horaire= ui->up_horaire->text();
    QString type_evenement= ui->up_type->currentText() ;

   Evenement E(id,date,Horaire,type_evenement) ;
   bool test = E.modifier() ;
           if (test){
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("modification effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


}


    else
        {
        QMessageBox::critical(nullptr, QObject::tr("not OK"),
                    QObject::tr("Echec de modification .\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

           ui->tab_evenement->setModel(E.afficher()) ;

}


//******************************************TAB_VIEW****************************************

void MainWindow::on_tab_evenement_activated(const QModelIndex &index)
{
    int id=ui->tab_evenement->model()->data(index).toInt() ;
     QString id_string = QString::number(id) ;

    QSqlQuery qry ;
    qry.prepare("SELECT* FROM EVENEMENTS WHERE ID='"+id_string+"' or DATE_EVENT='"+id_string+"' or HORAIRE='"+id_string+"'or TYPE='"+id_string+"'" ) ;
    if(qry.exec())
    {
        while(qry.next())
        {
            ui->update_id->setText(qry.value(0).toString()) ;
           // ui->up_date->setText(qry.value(1).toString()) ;
            ui->up_horaire->setText(qry.value(2).toString()) ;
            //ui->up_type->setText(qry.value(3).toString()) ;
             ui->up_type->setEditText(qry.value(3).toString()) ;

        }
    }

}

//****************************************TRI*****************************************


void MainWindow::on_tri_clicked()
{
    Evenement E ;

       ui->tab_evenement->setModel(E.tri());
       bool test = E.tri() ;
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

}

//**********************************************PDF*******************************





void MainWindow::on_pdf_clicked()
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

                         const int rowCount = ui->tab_evenement->model()->rowCount();
                         const int columnCount = ui->tab_evenement->model()->columnCount();
                         QString TT = QDateTime::currentDateTime().toString();
                         out <<"<html>\n"
                               "<head>\n"
                                "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                             << "<title>ERP - COMmANDE LIST<title>\n "
                             << "</head>\n"
                             "<body bgcolor=#ffffff link=#5000A0>\n"
                                "<h1 style=\"text-align: center;\"><strong> "+TT+"</strong></h1>"
                               +"<img src=C:\\Users\\asus\\Desktop\\pdf\\logo_projet />" //path
                             "<h1 style=\"text-align: center;\"><strong> ***LISTE DES EVENEMENTS*** </strong></h1>"

                             "<table style=\"text-align: center; font-size: 10px;\" border=1>\n "
                               "</br> </br>";
                         // headers
                         out << "<thead><tr bgcolor=#d6e5ff>";
                         for (int column = 0; column < columnCount; column++)
                             if (!ui->tab_evenement->isColumnHidden(column))
                                 out << QString("<th>%1</th>").arg(ui->tab_evenement->model()->headerData(column, Qt::Horizontal).toString());
                         out << "</tr></thead>\n";

                         // data table
                         for (int row = 0; row < rowCount; row++) {
                             out << "<tr>";
                             for (int column = 0; column < columnCount; column++)
                           {
                                 if (!ui->tab_evenement->isColumnHidden(column)) {
                                     QString data =ui->tab_evenement->model()->data(ui->tab_evenement->model()->index(row, column)).toString().simplified();
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

void MainWindow::on_statistique_clicked()
{

/*statistique stat ;
stat.setModal(true) ;
stat.exec() ;*/

//statistique stat ;
/*stat = new statistique() ;
stat->setWindowTitle("statistique") ;
stat->choix_pie() ;
stat->show() ;*/
/*stat.setWindowTitle("statistique") ;
stat.choix_pie() ;
stat.show() ;*/
 ui->stat->addWidget(E.stat()) ;

}


