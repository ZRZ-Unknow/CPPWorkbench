# HW2

*181220076 周韧哲*

1、构造函数的成员初始化列表的作用是什么？

+ 用来初始化常量、引用变量等。

2、C++的成员对象是什么？当创建包含成员对象的类的对象时，构造函数的调用顺序是什么样的？

+ 一个类的数据成员如果是另一个类则叫做成员对象。
+ 首先调用本身类的构造函数，但在进入本身类的构造函数函数体前会先调用成员对象类的构造函数，然后再执行本身类的构造函数函数体。当包含多个成员对象时，对成员对象构造函数的调用次序由成员对象在类中的说明次序决定。

3、时间类Time。

```c++
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
```

