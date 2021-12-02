#include "loading.h"
#include "ui_loading.h"

#include <QFileDialog>
#include <QMessageBox>
Loading::Loading(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Loading)
{
    ui->setupUi(this);
}

Loading::~Loading()
{
    delete ui;
}


void Loading::read_and_show_progressbar(QString &lines, QVector<checkin> &dataset)
{
//    this->hide();
    QString fileName = QFileDialog::getOpenFileName(this, "Open File", QCoreApplication::applicationFilePath(), "*.csv");
//    this->show();
    if(fileName.isEmpty())
    {
        QMessageBox::warning(this, "warning", "Please select a file!");
    }
    else
    {
        QFile file(fileName);
        int cnt = 0;
        if(file.open(QIODevice::ReadOnly))
        {

            QTextStream stream(&file);
            ui->progressBar->setRange(0, 150236);
            while (!stream.atEnd())
            {
                lines = stream.readLine();
                QStringList split = lines.split(",");
                dataset.push_back(checkin(split.at(0).toInt(), split.at(1).toInt(), split.at(2), split.at(3).toDouble(), split.at(4).toDouble()));
                ++cnt;
                ui->progressBar->setValue(cnt);
            }
            file.close();
        }
    }
}
