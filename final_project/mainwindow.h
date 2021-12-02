#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "loading.h"
#include "data_struct.h"
#include <QtWidgets>
#include <QMainWindow>
#include <QtCharts/QtCharts>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void openActionSlot();
    void on_buttonstart_clicked();

    void on_StartFilter_clicked();

    void on_Start_User_visit_POIs_clicked();

private:
    void User_ID_Filter(int para, bool flag, QVector<int> &loc);
    void Loc_ID_Filter(int para, bool flag, QVector<int> &loc);
    void Time_Filter(QString const &para, bool flag, QVector<int> &loc);
    void Lati_Filter(double para, bool flag, QVector<int> &loc);
    void Long_Filter(double para, bool flag, QVector<int> &loc);
    void printf(checkin data);
    QChart *chart;
    QChartView *chartview;
    Ui::MainWindow *ui;
    QString str;
    QString lines;
    QVector<checkin> dataset;
};
#endif // MAINWINDOW_H
