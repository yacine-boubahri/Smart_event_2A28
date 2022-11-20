#ifndef RECLAMATION_H
#define RECLAMATION_H
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
#include <QTableView>
class reclamation
{
    QString  nom,prenom,type;
    int id;
    QDate datee;
public:
    reclamation(){}
    reclamation(int,QString,QString,QString,QDate) ;
    // getters
    int getid(){return id;}
    QString getnom() {return nom;}
    QString getprenom() {return prenom;}
    QString gettype() {return type;}
    QDate getdatee() {return datee;}
    //setters
    void setid (int id);
    void setnom(QString n) {nom = n;}
    void setprenom(QString pr) {prenom = pr;}
    void settype (QString t) {type =t ;}
    void setdate(QDate dat) {datee = dat;}
    // fonctionalités
    bool ajouter();
    QSqlQueryModel * afficher() ;
    bool supprimer (int);
    QSqlQueryModel*tri();
    QSqlQueryModel *chercher(int id );
     QSqlQueryModel * stat() ;
     bool modifier ();






};

#endif // RECLAMATION_H
