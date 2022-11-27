#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "map.h"
#include <QMainWindow>
#include <evenement.h>
#include <QDesktopServices>
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>


namespace Ui {
class MainWindow;
}

class QCamera ;
class QCameraViewfinder ;
class QCameraImageCapture ;
class QVBoxLayout ;
class QMenu ;
class QAction ;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
   // void on_confirmer_clicked();


    void on_pb_confirmer_clicked();

    void on_afficher_clicked();

    void on_supprimer_1_clicked();
    void on_ok_1_clicked();

    void on_localisation_clicked();


    void on_modifier_clicked();

    void on_rechercher_clicked();

    void on_modifier_con_clicked();

    void on_tab_evenement_activated(const QModelIndex &index);

    void on_tri_clicked();

    void on_pdf_clicked();

    void on_statistique_clicked();



private:
    Ui::MainWindow *ui;
    Evenement E ;
    Map *map ;


    QCamera *mCamera ;
    QCameraViewfinder *mCameraViewfinder ;
    QCameraImageCapture *mCameraImageCapture ;
    QVBoxLayout *mLayout ;
    QMenu *mOptionMenu ;
    QAction *mEncenderAction ;
    QAction *mApagarAction ;
    QAction *mCapturarAction ;

};

#endif // MAINWINDOW_H
