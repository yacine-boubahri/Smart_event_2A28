#ifndef EVENEMENT_H
#define EVENEMENT_H
#include <QString>
#include <QSqlQueryModel>
#include <QPrinter>

#include <QChartView>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QGridLayout>
#include <QChartView>
QT_CHARTS_USE_NAMESPACE
class Evenement
{
public:
    Evenement();
    Evenement(int id,QString d ,QString h ,QString type) ;

    void setid(int d ) ;
    void setHoraire(QString h) ;
    void setdate(QString d) ;
    void settype_event( QString t) ;
    int getid();
   QString getHoraire();
    QString gettypeevent() ;
    QString getdate() ;
    void settypeevent() ;
    bool confirmer() ;
    QSqlQueryModel* afficher() ;
    bool supprimer(int) ;
    bool modifier() ;
   QSqlQueryModel* rechercher(int id) ;
    QString ID_string() ;
     bool confirmer_con() ;
     QSqlQueryModel* tri() ;
     void genererPDFact() ;
      QChartView * stat() ;




private:
    int id ;
    QString type_evenement ;
    QString date ;
    QString Horaire ;



};

#endif // EVENEMENT_H
