#include <iostream>
#include <assert.h>
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
    bool is_leap_year(int year) const{
        if(year%4 != 0)
            return false;
        if(year%100 != 0)
            return true;
        if(year%400 != 0)
            return false;
        return true;
    }
    bool is_31(int month) const{
        return month==1 || month==3 || month==7 || month==8 || month==10 || month==12;
    }
    bool is_30(int month) const{
        return month==4 || month==6 || month==9 || month==11;
    }
    bool is_28(int year, int month) const{
        return month==2 && !is_leap_year(year);
    }
    bool is_29(int year, int month) const{
        return month==2 && is_leap_year(year);
    }
    //increment 1
    void increment(int &year, int &month, int &day, int &hour, int &minute, int &second) const{
        if(second<59) second++;
        else{
            second = 0;
            if(minute<59) minute++;
            else{
                minute = 0;
                if(hour<23) hour++;
                else{
                    hour = 0;
                    if((is_31(month) && day<31) || 
                       (is_30(month) && day<30) ||
                       (is_29(year, month) && day<29) ||
                       (is_28(year, month) && day<28)){
                           day++;
                    }else{
                        day = 1;
                        if(month<12) month++;
                        else{
                            month = 1;
                            year++;
                        }
                    }
                } 
            }
        }
    }
    //decrement 1
    void decrement(int &year, int &month, int &day, int &hour, int &minute, int &second) const{
        if(second>0) second--;
        else{
            second = 59;
            if(minute>0) minute--;
            else{
                minute = 59;
                if(hour>0) hour--;
                else{
                    hour = 23;
                    if(day>1) day--;
                    else{
                        if(month==1) day = 31;
                        else if(is_31(month-1)) day = 31;
                        else if(is_30(month-1)) day = 30;
                        else if(is_29(year, month-1)) day = 29;
                        else if(is_28(year, month-1)) day = 28;
                        else assert(0); 
                        if(month>1) month--;
                        else{
                            month = 12;
                            year--;
                        }
                    }
                } 
            }
        }
    }
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
    Datetime operator+(long seconds) const{
        Date date = _date;
        Time time = _time;
        Datetime datetime(date, time);
        for(int i=0;i<seconds;i++)
            increment(datetime._date._year, datetime._date._month, datetime._date._day,
                      datetime._time._hour, datetime._time._minute, datetime._time._second);
        return datetime;
    }
    Datetime operator-(long seconds) const{
        Date date = _date;
        Time time = _time;
        Datetime datetime(date, time);
        for(int i=0;i<seconds;i++)
            decrement(datetime._date._year, datetime._date._month, datetime._date._day,
                      datetime._time._hour, datetime._time._minute, datetime._time._second);
        return datetime;
    }
    void operator++(int){
        increment(_date._year, _date._month, _date._day, _time._hour, _time._minute, _time._second);
    }
    void operator--(int){
        decrement(_date._year, _date._month, _date._day, _time._hour, _time._minute, _time._second);
    }
};


int main(){
    Date d1(2021, 1, 1);
    Time t1(0, 0, 40);
    Datetime dt1(d1, t1);
    long s = 61;
    long ss = 60;
    Datetime dt2 = dt1 + s;
    dt1.print();
    printf("add %d seconds\n", s); 
    dt2.print();
    printf("sub %d seconds\n", ss);
    Datetime dt3 = dt1 - ss;
    dt3.print();
    return 0;
}