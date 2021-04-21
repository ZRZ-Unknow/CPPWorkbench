#include <iostream>
#include <assert.h>
using namespace std;

enum TimeZone{
    W12 = -12, W11, W10, W9, W8, W7, W6, W5, W4, W3,  W2,  W1,
    GMT,  E1,  E2,  E3,  E4, E5, E6, E7, E8, E9, E10, E11, E12};

#define SET(h, m, s) do{ \
              this->h = h; \
              this->m = m; \
              this->s = s;}while(0)


class Time{
    int h,m,s;
public:
    Time(){}
    Time(int h, int m, int s){
       SET(h, m, s);
    }
    void set(int h, int m, int s){
       SET(h, m ,s);
    }
    void display(){
        printf("%02d:%02d:%02d.\n",h,m,s);
    }
    int timestamp() const{
        return h*3600 + m*60 + s;
    }
    bool equal(Time &other_time){
        return this->timestamp() == other_time.timestamp(); 
    }
    bool less_then(Time &other_time){
        return this->timestamp() < other_time.timestamp(); 
    }
    void increment(){
        if(s<59)  s++;
        else{
            s = 0;
            if(m<59) m++;
            else{
                m = 0;
                if(h<23) h++;
                else{
                    h = 0;
                } 
            }
        }
    }
};

class ExtTime:private Time{
    TimeZone tz;
public:
    ExtTime(){
        Time::set(0, 0, 0);
        tz = GMT;
    }
    ExtTime(int h, int m, int s, TimeZone t){
        Time::set(h, m, s);
        tz = t;
    }
    void display(){
        cout<<"TimeZome ";
        if(tz < 0) cout<<"W"<<-tz<<": ";
        else if(tz == 0) cout<<"GMT"<<": ";
        else cout<<"E"<<tz<<": ";
        Time::display();
    }
    bool equal(const ExtTime &other_time){
        return timestamp() == other_time.timestamp() + (tz - other_time.tz)*3600; 
    }
    bool less_than(const ExtTime &other_time){
        return timestamp() < other_time.timestamp() + (tz - other_time.tz)*3600; 
    }
};

int main(){
    ExtTime t(18, 42, 02, GMT);
    ExtTime b(18, 42, 02, E1);
    t.display();
    b.display();
    cout<<t.equal(b)<<t.less_than(b)<<endl;
    return 0;
}