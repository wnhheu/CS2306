#ifndef FILTER_H
#define FILTER_H
#include "mainwindow.h"
#include "./ui_mainwindow.h"
void MainWindow::User_ID_Filter(int para, bool flag, QVector<int> &loc)
{
    QVector<checkin> tmp;
//    for(int i = 0; i < 20; ++i)
//        tmp.push_back(dataset[i]);
    if(!flag)   //  if flag == true, we will cout the result when para is involved in the User_ID
    {
        for(int i = 0; i < dataset.size(); ++i)
        {
            if(dataset[i].User_ID == para)
                loc.push_back(i);
        }
    }
}

void MainWindow::Loc_ID_Filter(int para, bool flag, QVector<int> &loc)
{
    QVector<checkin> tmp;
//    for(int i = 0; i < 20; ++i)
//        tmp.push_back(dataset[i]);
    if(!flag)   //  if flag == true, we will cout the result when para is involved in the User_ID
    {
        for(int i = 0; i < dataset.size(); ++i)
        {
            if(dataset[i].Loc_ID == para)
                loc.push_back(i);
        }
    }
}

void MainWindow::Time_Filter(const QString &para, bool flag, QVector<int> &loc)
{
    QVector<checkin> tmp;
//    for(int i = 0; i < 20; ++i)
//        tmp.push_back(dataset[i]);
    if(!flag)   //  if flag == true, we will cout the result when para is involved in the User_ID
    {
        for(int i = 0; i < dataset.size(); ++i)
        {
            if(dataset[i].Time.ti_to_qstr() == para)
                loc.push_back(i);
        }
    }
}

void MainWindow::Lati_Filter(double para, bool flag, QVector<int> &loc)
{
    QVector<checkin> tmp;
//    for(int i = 0; i < 20; ++i)
//        tmp.push_back(dataset[i]);
    if(!flag)   //  if flag == true, we will cout the result when para is involved in the User_ID
    {
        for(int i = 0; i < dataset.size(); ++i)
        {
            if(dataset[i].Lati == para)
                loc.push_back(i);
        }
    }
}

void MainWindow::Long_Filter(double para, bool flag, QVector<int> &loc)
{
    QVector<checkin> tmp;
//    for(int i = 0; i < 20; ++i)
//        tmp.push_back(dataset[i]);
    if(!flag)   //  if flag == true, we will cout the result when para is involved in the User_ID
    {
        for(int i = 0; i < dataset.size(); ++i)
        {
            if(dataset[i].Long == para)
                loc.push_back(i);
        }
    }
}




#endif // FILTER_H
