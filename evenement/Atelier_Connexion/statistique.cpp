#include "statistique.h"
#include "ui_statistique.h"

statistique::statistique(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::statistique)
{
   /* ui->setupUi(this);
    QPieSeries *series = new QPieSeries() ;
    series->append("Mariage",80) ;
    series->append("Fetes",70) ;
    series->append("conference",60) ;
    series->append("Art",50) ;

    QChart *chart = new QChart() ;
    chart->addSeries(series) ;
    chart->setTitle("Pie chart for the EVENTS") ;

    QChartView *chartview = new QChartView(chart) ; //affichage
    chartview->setParent(ui->stat) ;*/

}

statistique::~statistique()
{
    delete ui;
}

//bar chart
/*void statistique::choix_bar()
{
QSqlQuery q1,q2,q3,q4,q5;
qreal tot=0,c1=0,c2=0,c3=0,c4=0;

q1.prepare("SELECT * FROM EVENEMENTS");
q1.exec();

/*q2.prepare("SELECT * FROM EVENEMENTS WHERE TYPE='mariage'");
q2.exec();

q2.prepare("SELECT * FROM EVENEMENTS where TYPE=:TYPE");
   q2.bindValue(":TYPE","mariage");

q3.prepare("SELECT * FROM EVENEMENTS WHERE TYPE='art'");
q3.exec();

q4.prepare("SELECT * FROM EVENEMENTS WHERE TYPE='fete' ");
q4.exec();

q5.prepare("SELECT * FROM EVENEMENTS WHERE TYPE='conference' ");
q5.exec();



while (q1.next()){tot++;}
while (q2.next()){c1++;}
while (q3.next()){c2++;}
while (q4.next()){c3++;}
while (q5.next()){c4++;}

c1=c1/tot;
c2=c2/tot;
c3=c3/tot;
c4=c4/tot ;


// Assign names to the set of bars used
        QBarSet *set0 = new QBarSet("mariage");
        QBarSet *set1 = new QBarSet("art");
        QBarSet *set2 = new QBarSet("fete");
        QBarSet *set3= new QBarSet("conference") ;

        // Assign values for each bar
        *set0 << c1;
        *set1 << c2;
        *set2 << c3;
        *set3 << c4 ;



        // Add all sets of data to the chart as a whole
        // 1. Bar Chart
        QBarSeries *series = new QBarSeries();

        // 2. Stacked bar chart
        series->append(set0);
        series->append(set1);
        series->append(set2);
        series->append(set3) ;


        // Used to define the bar chart to display, title
        // legend,
        QChart *chart = new QChart();

        // Add the chart
        chart->addSeries(series);


        // Adds categories to the axes
       // QBarCategoryAxis *axis = new QBarCategoryAxis();



        // 1. Bar chart
       // chart->setAxisX(axis, series);

        // Used to change the palette
        QPalette pal = qApp->palette();

        // Change the color around the chart widget and text
        pal.setColor(QPalette::Window, QRgb(0xffffff));
        pal.setColor(QPalette::WindowText, QRgb(0x404044));

        // Apply palette changes to the application
        qApp->setPalette(pal);


// Used to display the chart
chartView = new QChartView(chart,ui->stat);
chartView->setRenderHint(QPainter::Antialiasing);
chartView->setMinimumSize(400,400);

chartView->show();
}

//pie chart
    void statistique::choix_pie()
    {
    QSqlQuery q1,q2,q3,q4,q5;
    qreal tot=0,c1=0,c2=0,c3=0,c4=0 ;

    q1.prepare("SELECT * FROM EVENEMNTS");
    q1.exec();

    /*q2.prepare("SELECT * FROM EVENEMNTS WHERE TYPE='mariage'");
    q2.exec();

    q2.prepare("SELECT * FROM EVENEMENTS where TYPE=:TYPE");
       q2.bindValue(":TYPE","mariage");

    q3.prepare("SELECT * FROM EVENEMNTS WHERE TYPE='art'");
    q3.exec();

    q4.prepare("SELECT * FROM EVENEMENTS WHERE TYPE='fete' ");
    q4.exec();

    q5.prepare("SELECT * FROM EVENEMENTS WHERE TYPE='conference' ");
    q5.exec();

    while (q1.next()){tot++;}
    while (q2.next()){c1++;}
    while (q3.next()){c2++;}
    while (q4.next()){c3++;}
    while (q5.next()){c4++;}

    c1=c1/tot;
    c2=c2/tot;
    c3=c3/tot;
    c4=c4/tot ;

    // Define slices and percentage of whole they take up
    QPieSeries *series = new QPieSeries();
    series->append("mariage",c1);
    series->append("art",c2);
    series->append("fete",c3);
    series->append("conference",c4) ;




    // Create the chart widget
    QChart *chart = new QChart();

    // Add data to chart with title and show legend
    chart->addSeries(series);
    chart->legend()->show();


    // Used to display the chart
    chartView = new QChartView(chart,ui->stat);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(400,400);

    chartView->show();
    }*/
