#ifndef STAT_DIALOG_H
#define STAT_DIALOG_H

#include <QDialog>


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
class stat_Dialog;
}

class stat_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit stat_Dialog(QWidget *parent = nullptr);
    ~stat_Dialog();

    QChartView *chartView ;
      void choix_bar();
      void choix_pie();

private:
    Ui::stat_Dialog *ui;
};

#endif // STAT_DIALOG_H
