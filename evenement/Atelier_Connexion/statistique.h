#ifndef STATISTIQUE_H
#define STATISTIQUE_H

#include <QDialog>
#include <QDesktopServices>
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>


#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

namespace Ui {
class statistique;
}

class statistique : public QDialog
{
    Q_OBJECT

public:
    explicit statistique(QWidget *parent = nullptr);
    ~statistique();
    QChartView *chartView ;
     void choix_bar();
     void choix_pie();

private:
    Ui::statistique *ui;

};

#endif // STATISTIQUE_H
