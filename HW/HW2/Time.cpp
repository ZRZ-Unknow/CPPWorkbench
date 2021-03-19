#include <iostream>
#include <assert.h>
using namespace std;


#define SET(h, m, s) do{ \
              this->h = h; \
              this->m = m; \
              this->s = s;}while(0)


class Time{
private:
    int h,m,s;
public:
    Time(int h, int m, int s){
       SET(h, m, s);
    }
    void set(int h, int m, int s){
       SET(h, m ,s);
    }
    void display(){
        printf("Time is %02d:%02d:%02d.\n",h,m,s);
    }
    int timestamp(){
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


int main(){
    Time t1(14, 46, 50);
    Time t2(14, 46, 54);
    t1.display();
    t2.display();
    cout<<t1.equal(t1)<<endl;
    cout<<t1.less_then(t2)<<endl;
    t1.set(23, 59, 0);
    t1.display();
    cout<<t2.less_then(t1)<<endl;
    for(int i=0;i<4;i++){
        t1.increment();
        t1.display();
    }
    return 0;
}