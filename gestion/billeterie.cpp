#include "billeterie.h"
#include <QSqlQuery>
#include <QtDebug>
#include<QObject>
#include <QIntValidator>
#include <QTableWidget>
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QPrinter>
#include <QFileDialog>
#include <QTextDocument>
#include<QMessageBox>

Billeterie::Billeterie()
{
CIN_Client=0;
Nom_Client="";
Prenom_Client="";
Num_Tel=0;
Age_Client=0;
Nb_Billet=0;
}
Billeterie::Billeterie(int CIN_Client,QString Nom_Client,QString Prenom_Client,int Num_Tel,int Age_Client,int Nb_Billet)
{
 this->CIN_Client=CIN_Client;
 this->Nom_Client=Nom_Client;
 this->Prenom_Client=Prenom_Client;
 this->Num_Tel=Num_Tel;
 this->Age_Client=Age_Client;
 this->Nb_Billet=Nb_Billet;
}
int Billeterie::getCIN_Client()
{
  return CIN_Client;
}
QString Billeterie::getNom_Client()
{
    return Nom_Client;
}
QString Billeterie::getPrenom_Client()
{
    return Prenom_Client;
}
int Billeterie::getNum_Tel()
{
    return Num_Tel;
}
int Billeterie::getAge_Client()
{
    return Age_Client;
}
int Billeterie::getNb_Billet()
{
    return Nb_Billet;
}
void Billeterie::setCIN_Client(int CIN_Client)
{
    this->CIN_Client=CIN_Client;
}
void Billeterie::setNom_Client(QString Nom_Client)
{
   this->Nom_Client=Nom_Client;
}
void Billeterie::setPrenom_Client(QString Prenom_Client)
{
  this->Prenom_Client=Prenom_Client;
}
void Billeterie::setNum_Tel(int Num_Tel)
{
   this->Num_Tel=Num_Tel;
}
void Billeterie::setAge_Client(int Age_Client)
{
   this->Age_Client=Age_Client;
}
void Billeterie::setNb_Billet(int Nb_Billet)
{
  this->Nb_Billet=Nb_Billet;
}
bool Billeterie::ajouter_client()
{
  QSqlQuery query;
  int idt;
  QString CIN_string=QString::number(CIN_Client);
  QString Num_string=QString::number(Num_Tel);
  QString Age_string=QString::number(Age_Client);
  QString Nb_string=QString::number(Nb_Billet);

  idt=reduction(Nb_Billet);
  QString idt_string=QString::number(idt);
        query.prepare("INSERT INTO BILLETERIE (CIN_CLIENT,NOM_CLIENT,PRENOM_CLIENT,NUM_TEL,AGE_CLIENT,NB_BILLET) "
                      "VALUES (:CIN_CLIENT,:NOM_CLIENT,:PRENOM_CLIENT,:NUM_TEL,:AGE_CLIENT,:NB_BILLET)");
        query.bindValue(":CIN_CLIENT",CIN_string );
        query.bindValue(":NOM_CLIENT", Nom_Client);
        query.bindValue(":PRENOM_CLIENT", Prenom_Client);
        query.bindValue(":NUM_TEL",Num_string );
        query.bindValue(":AGE_CLIENT", Age_string);
        query.bindValue(":NB_BILLET",/*Nb_string*/idt_string);

         return query.exec();

}
bool Billeterie::supprimer_client(int CIN_Client)
{
    QSqlQuery query;
    //QString =QString::number(CIN_Client);
    query.prepare("Delete from BILLETERIE where CIN_Client=:CIN_CLIENT");
    query.bindValue(0,CIN_Client);
    //query.bindValue(":CIN_CLIENT",CIN_Client);

     return query.exec();
}
QSqlQueryModel * Billeterie::afficher_client()
{
 QSqlQueryModel * model= new QSqlQueryModel();
      model->setQuery("select* from BILLETERIE");

      model->setHeaderData(0, Qt::Horizontal,QObject::tr("CIN_Client"));
      model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom_Client"));
      model->setHeaderData(2, Qt::Horizontal,QObject::tr("Prenom_Client"));
      model->setHeaderData(3, Qt::Horizontal, QObject::tr("Num_Tel"));
      model->setHeaderData(4, Qt::Horizontal,QObject::tr("Age_Client"));
      model->setHeaderData(5, Qt::Horizontal,QObject::tr("Nb_Billet"));

 return model;
}

bool Billeterie::modifier()
{
    QSqlQuery query;
      //  QString res= QString(cin);
    QString Cin_string = QString::number(CIN_Client) ;
    QString Nb_string = QString::number(Nb_Billet) ;
    QString Age_string = QString::number(Age_Client) ;
   QString Num_string = QString::number(Num_Tel) ;

        query.prepare("UPDATE BILLETERIE SET CIN_CLIENT='"+Cin_string+"' , NOM_CLIENT='"+Nom_Client+"' ,PRENOM_CLIENT='"+Prenom_Client+ "',NUM_TEL='"+Num_string+"',AGE_CLIENT='"+Age_string+"',NB_BILLET='"+Nb_string+ "' WHERE CIN_CLIENT='"+Cin_string+"'");

           query.bindValue(0,Cin_string);
           query.bindValue(1,Nom_Client);
           query.bindValue(2,Prenom_Client );
           query.bindValue(3,Num_string);
           query.bindValue(4,Age_string );
           query.bindValue(5,Nb_string);

          return query.exec();
}

QSqlQueryModel * Billeterie::tri()
{
    QSqlQueryModel * model =new QSqlQueryModel();
    model->setQuery("SELECT * FROM BILLETERIE ORDER BY NB_BILLET DESC ");
    model->setHeaderData(0, Qt::Horizontal,QObject::tr("CIN_Client"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom_Client"));
    model->setHeaderData(2, Qt::Horizontal,QObject::tr("Prenom_Client"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Num_Tel"));
    model->setHeaderData(4, Qt::Horizontal,QObject::tr("Age_Client"));
    model->setHeaderData(5, Qt::Horizontal,QObject::tr("Nb_Billet"));
    return model;

}
void Billeterie::CREATION_PDF()
{
    QString fileName = QFileDialog::getSaveFileName((QWidget* )0, "Export PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty())
        { fileName.append(".pdf"); }

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(fileName);

    QTextDocument doc;
    QSqlQuery q;
    q.prepare("SELECT * FROM BILLETERIE");
    q.exec();
    QString pdf="<br> <h1  style='color:blue'>LISTE DES BILLETERIE   <br></h1>\n <br> <table>  <tr>  <th>CIN_CLIENT </th> <th>NOM_CLIENT </th> <th>PRENOM_CLIENT  </th> <th>AGE_CLIENT  </th><th>NUM_TEL  </th><th>   </th> </tr>" ;
//br traja ll star oel tr tzidlek colonne th tzidlek ligne h1 asghrr size o akbr size h6 //

    while ( q.next())
        {

        pdf= pdf+ " <br> <tr> <td>"+ q.value(0).toString()+" " + q.value(1).toString() +"</td>   <td>" +q.value(2).toString() +" <td>" +q.value(3).toString() +" <td>" +q.value(4).toString() +" <td>" +q.value(5).toString() +" "" " "</td> </td>" ;
    }
    doc.setHtml(pdf);
    doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
    doc.print(&printer);


}
/*bool Billeterie::rechercher(int CIN_Client)
{
    QSqlQuery query;
        QString cin_string = QString::number(CIN_Client);

       query.prepare("select* from BILLETERIE where where CIN_CLIENT="+cin_string+'"');
        //query.bindValue(0,numvol );
        return query.exec();
}*/







QSqlQueryModel* Billeterie::recherche(int CIN_Client)
      {

          QSqlQueryModel* model=new QSqlQueryModel() ;
          QString cin_string = QString::number(CIN_Client) ; //chaine

          model->setQuery("select * from billeterie where CIN_CLIENT='"+cin_string+"'");
          model->setHeaderData(0, Qt::Horizontal,QObject::tr("CIN_Client"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("Nom_Client"));
          model->setHeaderData(2, Qt::Horizontal,QObject::tr("Prenom_Client"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("Num_Tel"));
          model->setHeaderData(4, Qt::Horizontal,QObject::tr("Age_Client"));
          model->setHeaderData(5, Qt::Horizontal,QObject::tr("Nb_Billet"));
          return model;
      }

int Billeterie::reduction(int Nb_Billet)
{
    QSqlQuery query;
     QMessageBox msgBox;
    QString nb_string = QString::number(Nb_Billet);
query.prepare("select* from BILLETERIE where NB_BILLET="+nb_string+'"');
if(Nb_Billet>=5)
{
         return  ++Nb_Billet;
}
else
 return Nb_Billet;

msgBox.exec();
}

/*int Billeterie::billet_res()
{
    int s;
  //s=somme_billet(Nb_Billet);
  s=s-1;
    return  s;
}*/



    /*int s=0;
    QSqlQuery query;
     QMessageBox msgBox;
    QString nb_string = QString::number(Nb_Billet);
query.prepare("select* from BILLETERIE where NB_BILLET="+nb_string+'"');
     s=s+Nb_Billet;
     return s;*/

