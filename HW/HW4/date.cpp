#include <iostream>
using namespace std;


class Date{
private:
    int _year, _month, _day;
public:
    Date(){}
    Date(int year, int month, int day){
        _year = year;
        _month = month;
        _day = day;
    }
    friend class Datetime;
};

class Time{
private:
    int _hour, _minute, _second;
public:
    Time(){}
    Time(int hour, int minute, int second){
        _hour = hour;
        _minute = minute;
        _second = second;
    }
    friend class Datetime;
};

class Datetime{
private:
    Date _date;
    Time _time;
public:
    Datetime(const Date &date, const Time &time){
        _date = date;
        _time = time;
    } 
    void print(){
        printf("%d.%02d.%02d-%02d:%02d:%02d\n", _date._year, _date._month, _date._day, _time._hour, _time._minute, _time._second);
    }
    bool operator==(const Datetime &datetime) const{
        return this->_date._day == datetime._date._day &&
               this->_date._month == datetime._date._month &&
               this->_date._year == datetime._date._year &&
               this->_time._hour == datetime._time._hour &&
               this->_time._minute == datetime._time._minute &&
               this->_time._second == datetime._time._second;
    }
    bool operator<(const Datetime &datetime) const{
        return ! (*this==datetime) &&
               this->_date._day <= datetime._date._day &&
               this->_date._month <= datetime._date._month &&
               this->_date._year <= datetime._date._year &&
               this->_time._hour <= datetime._time._hour &&
               this->_time._minute <= datetime._time._minute &&
               this->_time._second <= datetime._time._second;
    }
    void add(int &year, int &month, int &day, int &hour, int &minute, int &second, long seconds) const{
        second += seconds;
    }
    void sub(int &year, int &month, int &day, int &hour, int &minute, int &second, long seconds) const{
        second -= seconds;
    }
    Datetime operator+(long seconds) const{
        Date date = _date;
        Time time = _time;
        Datetime datetime(date, time);
        add(datetime._date._year, datetime._date._month, datetime._date._day,
            datetime._time._hour, datetime._time._minute, datetime._time._second, seconds);
        return datetime;
    }
    Datetime operator-(long seconds) const{
        Date date = _date;
        Time time = _time;
        Datetime datetime(date, time);
        sub(datetime._date._year, datetime._date._month, datetime._date._day,
            datetime._time._hour, datetime._time._minute, datetime._time._second, seconds);
        return datetime;
    }
    void operator++(int){
        add(_date._year, _date._month, _date._day, _time._hour, _time._minute, _time._second, 1);
    }
    void operator--(int){
        sub(_date._year, _date._month, _date._day, _time._hour, _time._minute, _time._second, 1);
    }

};


int main(){
    Date d1(2020, 1, 20);
    Time t1(20, 1, 40);
    Date d2(2019, 1, 20);
    Time t2(20, 1, 29);
    Datetime dt1(d1, t1);
    Datetime dt2(d1, t2);
    cout<<(dt2<dt1)<<endl;
    Datetime dt3 = dt1 + 17;
    Datetime dt4 = dt3 - 7;
    dt1++;
    dt2--;
    dt1.print();
    dt2.print();
    dt3.print();
    dt4.print();
    return 0;
}