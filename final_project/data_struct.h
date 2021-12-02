#ifndef DATA_STRUCT_H
#define DATA_STRUCT_H
#include <QString>
#include <QVector>
struct checkin
{

    struct time
    {
        int year;
        int month;
        int day;
        int hour;
        int minute;
        int second;
        int operator[](int loc)
        {
            if(loc == 0)
                return year;
            else if(loc == 1)
                return month;
            else if(loc == 2)
                return day;
            else if(loc == 3)
                return hour;
            else if(loc == 4)
                return minute;
            else
                return second;

        }
        bool operator<(time const &oth)
        {
            if(year < oth.year)
                return true;
            else if (year > oth.year)
                return false;
            if(month < oth.month)
                return true;
            else if(month > oth.month)
                return false;
            if(day < oth.day)
                return true;
            else if(day > oth.day)
                return false;
            if(hour < oth.hour)
                return true;
            else if(hour > oth.hour)
                return false;
            if(minute < oth.minute)
                return true;
            else if(minute > oth.minute)
                return false;
            if(second < oth.second)
                return true;
            else
                return false;

        }

        bool operator>(time const &oth)
        {
            if(year > oth.year)
                return true;
            else if (year < oth.year)
                return false;
            if(month > oth.month)
                return true;
            else if(month < oth.month)
                return false;
            if(day > oth.day)
                return true;
            else if(day < oth.day)
                return false;
            if(hour > oth.hour)
                return true;
            else if(hour < oth.hour)
                return false;
            if(minute > oth.minute)
                return true;
            else if(minute < oth.minute)
                return false;
            if(second > oth.second)
                return true;
            else
                return false;

        }

        bool operator==(time const &oth)
        {
            return year == oth.year && month == oth.month && day == oth.day && hour == oth.hour && minute == oth.minute && second == oth.second;
        }

        QString ti_to_qstr()
        {
            QString tmp;
            tmp.append(QString::number(year));tmp.append('-');
            if(month < 10)
                tmp.append('0');
            tmp.append(QString::number(month));tmp.append('-');
            if(day < 10)
                tmp.append('0');
            tmp.append(QString::number(day));tmp.append('T');
            if(hour < 10)
                tmp.append('0');
            tmp.append(QString::number(hour));tmp.append(':');
            if(minute < 10)
                tmp.append('0');
            tmp.append(QString::number(minute));tmp.append(':');
            if(second < 10)
                tmp.append('0');
            tmp.append(QString::number(second));tmp.append('Z');
            return tmp;
        }
        void qstr_to_ti(QString &str)
        {
            int cnt = 0;
            int loc = -1;
            for(int i = 0; i < str.size(); ++i)
            {
                if(str[i] == 'T')
                {
                    loc = i;
                     break;
                }
            }
            for(int i = 0; i < loc; ++i)
            {
                int j = i;
                QString tmp;
                while(str[j] != '-' && j < loc)
                {
                    tmp.push_back(str[j]);
                    ++j;
                }
                i = j;
                if(cnt == 0)
                {
                    year = tmp.toInt();
                    ++cnt;
                }
                else if(cnt == 1)
                {
                    month = tmp.toInt();
                    ++cnt;
                }
                else if(cnt == 2)
                {
                    day = tmp.toInt();
                }
            }
            loc += 1;
            cnt = 0;
            for(int i = loc; i < str.size() - 1; ++i)
            {
                int j = i;
                QString tmp;
                while(str[j] != ':' && j < str.size() - 1)
                {
                    tmp.push_back(str[j]);
                    ++j;
                }
                i = j;
                if(cnt == 0)
                {
                    hour = tmp.toInt();
                    ++cnt;
                }
                else if(cnt == 1)
                {
                    minute = tmp.toInt();
                    ++cnt;
                }
                else if(cnt == 2)
                {
                    second = tmp.toInt();
                }
            }
        }


    };
    int User_ID;
    int Loc_ID;
    time Time;
    double Lati;
    double Long;

    checkin(int u, int l, QString t, double la, double lo)
    {
        User_ID = u;
        Loc_ID = l;
        Time.qstr_to_ti(t);
        Lati = la;
        Long = lo;
    }
};



int divide_time(QVector<checkin> &a, int low, int high)
{
    checkin k = a[low];
    do
    {
        while(low < high && a[high].Time > a[low].Time)
            --high;
        if(low < high)
        {
            a[low] = a[high];
            ++low;
        }
        while(low < high && a[low].Time < a[low].Time)
            ++low;
        if(low < high)
        {
            a[high] = a[low];
        }

    }while(low != high);
    a[low] = k;
    return low;
}

void quicksort_time(QVector<checkin> &a, int low, int high)
{
    int mid;
    if(low >= high)
        return;
    mid = divide_time(a, low, high);
    quicksort_time(a, low, mid - 1);
    quicksort_time(a, mid + 1, high);
}



int divide_user_id(QVector<checkin> &a, int low, int high)
{
    checkin k = a[low];
    do
    {
        while(low < high && a[high].User_ID <= a[low].User_ID)
            --high;
        if(low < high)
        {
            a[low] = a[high];
            ++low;
        }
        while(low < high && a[low].User_ID >= a[low].User_ID)
            ++low;
        if(low < high)
        {
            a[high] = a[low];
        }

    }while(low != high);
    a[low] = k;
    return low;
}

void quicksort_user_id(QVector<checkin> &a, int low, int high)
{
    int mid;
    if(low >= high)
        return;
    mid = divide_user_id(a, low, high);
    quicksort_user_id(a, low, mid - 1);
    quicksort_user_id(a, mid + 1, high);
}




#endif // DATA_STRUCT_H
