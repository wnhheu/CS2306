#ifndef LOADING_H
#define LOADING_H

#include <QWidget>
#include <data_struct.h>

namespace Ui {
class Loading;
}

class Loading : public QWidget
{
    Q_OBJECT

public:
    explicit Loading(QWidget *parent = nullptr);
    void read_and_show_progressbar(QString &lines, QVector<checkin> &dataset);
    ~Loading();
private:
    Ui::Loading *ui;
};

#endif // LOADING_H
