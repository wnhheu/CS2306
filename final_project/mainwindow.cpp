#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "Filter.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QtCharts/QtCharts>
#include <iostream>
#include <QColor>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    chart = new QChart;
    chartview = new QChartView;
    QStringList items;
    items.append(tr("Filter"));
    items.append(tr("User_ID"));
    items.append(tr("Location_ID"));
    items.append(tr("Time"));
    items.append(tr("Latitude"));
    items.append(tr("Longitude"));
    ui->comboBox->addItems(items);
    connect(ui->actionopen, &QAction::triggered, this, &MainWindow::openActionSlot);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openActionSlot()
{
    Loading *l = new Loading();
    l->show();
    l->read_and_show_progressbar(lines, dataset);
    l->close();
}

void MainWindow::on_buttonstart_clicked()
{
    if(str.isEmpty())
    {
        QMessageBox::warning(this, "warning", "Please Select A File!");
        return;
    }

//    QString sta = ui->startweek->toPlainText();
//    QString end = ui->endweek->toPlainText();

//    int sta_week = qstr_to_int(sta);
//    int end_week = qstr_to_int(end);
//    if(sta_week < end_week)
//    {
//        QMessageBox::warning(this, "warning", "Invalid Range!");
//        return;
//    }
//    chart->removeAllSeries();
//    chart->removeAxis(chart->axisX());
//    chart->removeAxis(chart->axisY());
//    chart->setTitle("Line chart of ZTY's homweork_9:");
//    QLineSeries *series = new QLineSeries();
////    split_line(str, series, sta_week, end_week);

//    QValueAxis *axisX = new QValueAxis;
//    axisX->setTitleText("X(weeks)");
//    axisX->setLabelFormat("%d");
//    chart->addSeries(series);
//    QValueAxis *axisY = new QValueAxis;


//    axisY->setTitleText("Y(num)");
//    axisY->setLabelFormat("%d");
//    chart->setAxisX(axisX, series);
//    chart->setAxisY(axisY, series);

//    chart->legend()->hide();

//    chartview->setChart(chart);
//    chartview->setRenderHint(QPainter::Antialiasing);
//    ui->graph->addWidget(chartview);
}

void MainWindow::printf(checkin data)
{
    QString buf = "User_ID: ";
    buf.append(QString::number(data.User_ID));
    buf.append(" Loc_ID: ");
    buf.append(QString::number(data.Loc_ID));
    buf.append(" Time: ");
    buf.append(data.Time.ti_to_qstr());
    buf.append(" Latitude: ");
    buf.append(QString::number(data.Lati));
    buf.append(" Longitude: ");
    buf.append(QString::number(data.Long));
    ui->FilterOutput->appendPlainText(buf);
}


void MainWindow::on_StartFilter_clicked()
{
    QString para = ui->Parameter->text();
    QString kind = ui->comboBox->currentText();
    QVector<int> loc;
    if(kind == "User_ID")
    {
        User_ID_Filter(para.toInt(), false, loc);
    }
    else if(kind == "Location_ID")
    {
        Loc_ID_Filter(para.toInt(), false, loc);
    }
    else if(kind == "Time")
    {
        Time_Filter(para, false, loc);
    }
    else if(kind == "Latitude")
    {
        Lati_Filter(para.toDouble(), false, loc);
    }
    else
    {
        Long_Filter(para.toDouble(), false, loc);
    }
    ui->FilterOutput->clear();
    for(int i = 0; i < loc.size(); ++i)
    {
        printf(dataset[loc[i]]);
    }
}


struct location{
    int ID;
    double Lati;
    double Long;
    int sta;
    location operator=(checkin const &oth)
    {
        ID = oth.Loc_ID;
        Lati = oth.Lati;
        Long = oth.Long;
        sta = 0;
    }
    location(checkin const &oth)
    {
        ID = oth.Loc_ID;
        Lati = oth.Lati;
        Long = oth.Long;
        sta = 0;
    }
    bool  operator==(checkin const &oth)
    {
        return ID == oth.Loc_ID && Lati == oth.Lati && Long == oth.Long;
    }
};

void analyze_month(int sta, int end, QVector<checkin> &user_datas, QVector<checkin> &used)
{

    for(int i = sta; i <= end; ++i)
    {
        bool flag = true;
        for(int j = 0; j < used.size(); ++j)
        {
            if(used[j].Loc_ID == user_datas[i].Loc_ID)
            {
                flag = false;
                used[j].User_ID++;
                break;
            }
        }
        if(flag)
        {
            used.append(user_datas[i]);
            used[used.size() - 1].User_ID = 1;
        }
    }
    quicksort_user_id(used, 0, used.size() - 1);
}

void traverse_months(int start_year, int end_year, int start_month, int end_month, QVector<checkin> &user_datas)
{
    int beg = 0;
    int end = 0;
    QVector<location> locs;
    QVector<checkin> used;

    for(int i = 0; i < user_datas.size(); ++i)
    {
        bool flag = true;
        for(int j = 0; j < locs.size(); ++j)
        {
            if(locs[j] == user_datas[i])
            {
                flag = false;
                break;
            }
        }
        if(flag)
            locs.append(location(user_datas[i]));
    }

    for(int i = start_year; i <= end_year; ++i)
    {
        for(int j = start_month; i <= start_month; ++j)
        //for(int j = start_month; j <= (end_year - i) * 12 + end_month && j <= 12; ++j)
        {
            for(int k = 0; k < user_datas.size(); ++k)
            {
                if(k == user_datas.size() - 1)
                {
                    end = k;
                    break;
                }
                if(user_datas[k].Time.month != j)
                {
                    end = k - 1;
                    break;
                }
            }
            beg = end + 1;
            analyze_month(beg, end, user_datas, used);
            int cnt = 0;
            for(int k = 0; k < locs.size(); ++k)
            {
                for(int l = used.size() - 1; l >= 0; --l)
                {
                    if(used[l].Loc_ID == locs[k].ID)
                    {
                        if(cnt < 5)
                            locs[k].sta = 2;
                        else
                            locs[k].sta = 1;
                        ++cnt;
                    }
                }
            }
            QScatterSeries *series0 = new QScatterSeries;
            series0->setName("scatter1");
            series0->setMarkerShape(QScatterSeries::MarkerShapeCircle);
            series0->setMarkerSize(3.0);
            series0->setColor(QColor(Qt::gray));
            QScatterSeries *series1 = new QScatterSeries;
            series1->setName("scatter1");
            series1->setMarkerShape(QScatterSeries::MarkerShapeCircle);
            series1->setMarkerSize(3.0);
            series1->setColor(QColor(Qt::blue));
            QScatterSeries *series2 = new QScatterSeries;
            series2->setName("scatter1");
            series2->setMarkerShape(QScatterSeries::MarkerShapeCircle);
            series2->setMarkerSize(3.0);
            series2->setColor(QColor(Qt::red));
            for(int k = 0; k < locs.size(); ++k)
            {
                if(locs[k].sta == 0)
                {
                    series0->append(locs[k].Long, locs[k].Lati);
                }
                else if(locs[k].sta == 1)
                {
                    series1->append(locs[k].Long, locs[k].Lati);
                }
                else
                {
                    series2->append(locs[k].Long, locs[k].Lati);
                }
            }
            QChart *chart = new QChart;
            chart->addSeries(series0);
            chart->addSeries(series1);
            chart->addSeries(series2);

            chart->setTitle("Simple scatterchart example");
            chart->createDefaultAxes();
            chart->setDropShadowEnabled(false);



            QChartView *chartView = new QChartView;
            chartView->setRenderHint(QPainter::Antialiasing);
            QMainWindow window;
            window.setCentralWidget(chartView);
            window.resize(400, 300);
            window.show();
        }
    }


}

void MainWindow::on_Start_User_visit_POIs_clicked()
{
    QString str = ui->User_visit_POIs->text();
    QVector<int> loc;
    QVector<checkin> user_datas;
    User_ID_Filter(str.toInt(), false, loc);
    for(int i = 0; i < loc.size(); ++i)
    {
        user_datas.push_back(dataset[loc[i]]);
    }
    quicksort_time(user_datas, 0, user_datas.size() - 1);
    int start_month = user_datas[0].Time.month;
    int start_year = user_datas[0].Time.year;
    int end_month = user_datas[user_datas.size() - 1].Time.month;
    int end_year = user_datas[user_datas.size() - 1].Time.year;
    traverse_months(start_year, end_year, start_month, end_month, user_datas);
}







