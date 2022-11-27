#include "evenement.h"
#include <QString>
#include <QSqlQuery>
#include <QtDebug>
#include <QSqlQueryModel>
#include <QObject>
#include <QPdfWriter>
#include <QPainter>
#include <QDesktopServices>
#include <QPrinter>
#include <QFileDialog>
#include <QTextDocument>
#include <QDateTime>
#include <QTextStream>


Evenement::Evenement()
{
     id =0 ;
    type_evenement="" ;
     Horaire="" ;
     date="" ;
}

Evenement::Evenement(int id,QString d ,QString h ,QString  type)
{
    this->id =id ;
    this->type_evenement=type ;
     this->date=d ;
    this->Horaire=h ;

}

////////////////////////////GET//////////////////

int Evenement::getid()
{return id ; }

QString Evenement::getdate()
{return date ; }


QString Evenement::getHoraire()
{return Horaire ; }

QString Evenement::gettypeevent()
{return type_evenement ; }


//////////////////////SET//////////////////

   void Evenement::setid(int d )
   {this->id=d ; }

   void Evenement::setdate(QString d)
   {this->date = d ; }

   void Evenement::setHoraire(QString h)
   {this->Horaire=h ; }

   void Evenement::settype_event(QString t)
   {this->type_evenement= t ; }

//********************************************AJOUTER********************************************

     bool Evenement::confirmer()
     {


         QSqlQuery query;
         QString id_string = QString::number(id) ;
              query.prepare("INSERT INTO EVENEMENTS (ID,DATE_EVENT,HORAIRE,TYPE) "
                            "VALUES (:id_string, :date, :Horaire, :type_evenement)");
              query.bindValue(0, id_string);
              query.bindValue(1, date);
              query.bindValue(2, Horaire);
              query.bindValue(3, type_evenement);

              return query.exec();


     }

     bool Evenement::confirmer_con()
     {
         QSqlQuery query;
         QString id_string = QString::number(id) ;
              query.prepare("UPDATE EVENEMENTS set ID='"+id_string+"',DATE_EVENT= '"+date+"',HORAIRE="+Horaire+"',TYPE='"+type_evenement+"'WHERE ID="+id_string+"'");
              /*query.bindValue(0, id_string);
              query.bindValue(1, date);
              query.bindValue(2, Horaire);
              query.bindValue(3, type_evenement);*/

              return query.exec();
     }
     //************************************SUPPRIMER************************************

     bool Evenement::supprimer(int id )
     {
         QSqlQuery query;

              query.prepare(" Delete from EVENEMENTS where id=:id ");
              query.bindValue(0, id);
               return query.exec();


     }
     //************************************AFFICHER*********************************************

     QSqlQueryModel* Evenement::afficher()
     {
         QSqlQueryModel* model = new QSqlQueryModel() ;

         model->setQuery("SELECT * from EVENEMENTS ") ;
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("Id"));
         model->setHeaderData(3,Qt::Horizontal,QObject::tr("Type"));
         model->setHeaderData(1,Qt::Horizontal,QObject::tr("Date_event"));
         model->setHeaderData(2,Qt::Horizontal,QObject::tr("Horaire"));


         return model ;

     }

     //*******************************UPDATE***********************************


     bool Evenement::modifier()
     {
         QSqlQuery query ;
          QString id_string = QString::number(id) ;

         query.prepare("UPDATE EVENEMENTS SET ID='"+id_string+"', DATE_EVENT='"+date+"' ,HORAIRE='"+Horaire+ "',TYPE='"+type_evenement+"'WHERE ID ='"+id_string+"'") ;

         /*query.bindValue(0,id) ;
         query.bindValue(1,date) ;
         query.bindValue(2,Horaire) ;
         query.bindValue(3,type_evenement) ;*/

         return query.exec() ;

     }
     //******************************RECHERCHER***********************************************


      QSqlQueryModel* Evenement::rechercher(int id)
      {
          QSqlQuery query  ;
          QString id_string = QString::number(id) ; //chaine

         /* query.prepare("SELECT *  FROM EVENEMENTS WHERE ID=:id") ;
          query.bindValue(":ID",id_string) ;
          query.exec() ;
          QSqlQueryModel *model= new QSqlQueryModel;

          model->setHeaderData(0,Qt::Horizontal,QObject::tr("Id"));
           model->setHeaderData(3,Qt::Horizontal,QObject::tr("Type"));
           model->setHeaderData(1,Qt::Horizontal,QObject::tr("Date_event"));
           model->setHeaderData(2,Qt::Horizontal,QObject::tr("Horaire"));

          model->setQuery(query) ;*/

          QSqlQueryModel *model = new QSqlQueryModel ;

          model->setQuery("select * from  EVENEMENTS where ID like '%"+id_string+"%'"); //affichage


         return model;

      }

      //************************************************************************

       QString Evenement::ID_string()
       {
            QString id_string = QString::number(id) ;

            return id_string ;
       }


     //******************************TRI************************

      QSqlQueryModel* Evenement::tri()
      {
          QSqlQueryModel * model =new QSqlQueryModel();

             model->setQuery("SELECT * FROM EVENEMENTS ORDER BY ID ASC ");

             model->setHeaderData(0,Qt::Horizontal,QObject::tr("Id"));
              model->setHeaderData(3,Qt::Horizontal,QObject::tr("Type"));
              model->setHeaderData(1,Qt::Horizontal,QObject::tr("Date_event"));
              model->setHeaderData(2,Qt::Horizontal,QObject::tr("Horaire"));


               return model;
      }

      //********************************************PDF**************************************


      void Evenement::genererPDFact()
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
              q.prepare("SELECT * FROM EVENEMENTS ");
              q.exec();
              QString pdf="<br> <h1  style='color:blue'>LISTE DES EVENEMENTS  <br></h1>\n <br> <table>  <tr>  <th>ID </th> <th>DATE_EVENT </th> <th>HORAIRE   </th> </tr>" ;
          //br traja ll star oel tr tzidlek colonne th tzidlek ligne h1 asghrr size o akbr size h6 //

              while ( q.next())
                  {

                  pdf= pdf+ " <br> <tr> <td>"+ q.value(0).toInt()+" " + q.value(1).toString() +"</td>   <td>" +q.value(2).toString() +" <td>" +q.value(3).toString() +" "" " "</td> </td>" ;
              }
              doc.setHtml(pdf);
              doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
              doc.print(&printer);


          }
//*******************************************STATISTIQUE***************************************


      QChartView * Evenement::stat()
        {
            //fzfezz
            //int row_count = 0;
            int row_count1 = 0;
            int row_count2 = 0;
            int row_count3 = 0;
            int row_count4 = 0;

                    QSqlQuery query,query2,query3,query4,query5 ;

                    /*query.prepare("SELECT TYPE FROM EVENEMENTS ");
                    query.exec();*/

                    query2.prepare("SELECT TYPE FROM EVENEMENTS  WHERE TYPE='mariage'");
                    query2.exec();

                    query3.prepare("SELECT TYPE FROM EVENEMENTS  WHERE TYPE='art'");
                    query3.exec();

                    query4.prepare("SELECT TYPE FROM EVENEMENTS  WHERE TYPE='fete'");
                    query4.exec();

                    query5.prepare("SELECT TYPE FROM EVENEMENTS  WHERE TYPE='conference'");
                    query5.exec();

                    while(query2.next())

                        ++row_count1;

                    while(query3.next())

                        ++row_count2;

                    while(query4.next())

                        ++row_count3;

                    while(query5.next())

                        ++row_count4;



                    /*while(query.next())
                        row_count++;*/

                    qDebug()<<"row1="<<row_count1<<row_count2<<row_count3<<row_count4;

            QPieSeries *series = new QPieSeries();

            series->append("mariage", row_count1);
            series->append("art", row_count2);
            series->append("fete", row_count3);
            series->append("conference", row_count4);
            QChart *chart = new QChart();
            chart->addSeries(series);
            chart->setTitle("Pie chart for the events");
            chart->legend()->setAlignment(Qt::AlignRight);
            chart->legend()->setBackgroundVisible(true);
            chart->legend()->setBrush(QBrush(QColor(128, 128, 128, 128)));
            chart->legend()->setPen(QPen(QColor(192, 192, 192, 192)));
            series->setLabelsVisible();

            QChartView *chartView = new QChartView(chart);
            chartView->setRenderHint(QPainter::Antialiasing);
            return chartView;
        }

 //*************************CALENDRIER**************************************




