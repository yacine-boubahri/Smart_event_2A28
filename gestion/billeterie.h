#ifndef BILLETERIE_H
#define BILLETERIE_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QAbstractSocket>
#include <QSslSocket>

class Billeterie
{
public:
    Billeterie();
    Billeterie(int,QString,QString,int,int,int);
    int getCIN_Client();
    QString getNom_Client();
    QString getPrenom_Client();
    int getNum_Tel();
    int getAge_Client();
    int getNb_Billet();
    void setCIN_Client(int);
    void setNom_Client(QString);
    void setPrenom_Client(QString);
    void setNum_Tel(int);
    void setAge_Client(int Age_Client);
    void setNb_Billet(int);
    bool ajouter_client();
    QSqlQueryModel * afficher_client();
    bool supprimer_client(int CIN_Client);
    bool modifier();
    QSqlQueryModel * tri();
    void CREATION_PDF();
    //bool rechercher(int CIN_Client);
    int reduction(int Nb_Billet);
    QSqlQueryModel* recherche(int CIN_Client);
    int billet_res();
    QString rec_billet(int Nb_Billet);

private:
    int CIN_Client,Num_Tel,Age_Client,Nb_Billet;
    QString Nom_Client,Prenom_Client;

};

#endif // BILLETERIE_H
