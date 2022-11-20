#include "reclamation.h"
#include <QSqlQuery>
#include <QTableView>





reclamation::reclamation(int id,QString nom,QString prenom,QString type,QDate datee)
{
    this->id=id;
    this->nom=nom;
    this->prenom=prenom;
    this->type=type;
    this->datee=datee;




}
bool reclamation::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO rec(ID,NOM,PRENOM,TYPE,DATEE)" "VALUES(:id,:nom,:prenom,:type,:datee)");
    query.bindValue(":id",id);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":type",type);
    query.bindValue(":datee",datee);
    return query.exec();
}
bool reclamation::supprimer( int id) {
    QSqlQuery querry;
    int res=int(id);
    querry.prepare("delete  from rec where ID= :id");
     querry.bindValue(":id",res);

     return querry.exec();
}
QSqlQueryModel* reclamation::afficher()
{
    QSqlQueryModel*model=new QSqlQueryModel();
    model->setQuery("select * from rec ");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr(" ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr(" nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr(" prenom"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr(" type"));

    return  model;

}

QSqlQueryModel * reclamation::tri()
{
    QSqlQueryModel * model =new QSqlQueryModel();
    model->setQuery("SELECT * FROM rec ORDER  BY id DESC   ");
    model->setHeaderData  (0, Qt:: Horizontal,QObject::tr    (" ID"));
    model->setHeaderData  (1, Qt::Horizontal,QObject::tr    (" nom"));
    model->setHeaderData (2, Qt:: Horizontal,QObject::tr("  prenom"));
    model->setHeaderData (3, Qt:: Horizontal,QObject::tr ("  type "));
   model->setHeaderData   (4, Qt:: Horizontal,QObject::tr  (" date"));

    return model;
}
QSqlQueryModel* reclamation::chercher(int id)
{

   QSqlQueryModel* model=new QSqlQueryModel() ;
   QString id_string = QString::number(id);

    QString ID = QString::number(id);

   model->setQuery("select *  from rec where id=='"+id_string+"'");
   model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
   model->setHeaderData  (1, Qt::Horizontal,QObject::tr    (" nom"));
   model->setHeaderData (2, Qt:: Horizontal,QObject::tr("  prenom"));
   model->setHeaderData (3, Qt:: Horizontal,QObject::tr ("  type "));
  model->setHeaderData   (4, Qt:: Horizontal,QObject::tr  (" date"));




   return model;
}
QSqlQueryModel * reclamation::stat()
{
    QSqlQueryModel * model =new QSqlQueryModel();
       model->setQuery("SELECT  COUNT(ID) FROM rec; ");
       model->setHeaderData (0, Qt:: Horizontal,QObject::tr    ("  ID"));

   return model;
}
bool reclamation::modifier()
{
    QSqlQuery query;
  //  QString res= QString(cin);
    QString ID=QString::number(id);


    query.prepare("UPDATE rec SET type='"+type+"' WHERE id='"+ID+"'");

     query.bindValue(0,id);
     query.bindValue(1,type);


      return query.exec();

}


