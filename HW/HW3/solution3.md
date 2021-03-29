# HW3

*181220076 周韧哲*

### 一. 概念题

1. 什么时候需要定义析构函数？

   + 若对象在创建后申请了一些资源，并且在对象消亡前没有归还这些资源，则要自定义析构函数来归还资源。

2. 什么时候会调用拷⻉构造函数？使用默认的拷⻉构造函数有什么需要特别注意的情况？

   + 在创建一个对象时，如果用另一个同类的对象对其初始化，这时会调用拷贝构造函数。
   + 当调用默认拷贝构造函数，有可能两个类实例的成员指针指向同一块内存区域。

3. 请说明C++中 const 和 static 关键词的作用。

   + const限定变量为不可修改，或限定成员函数不可以修改任何数据成员。

   + 用static修饰类的数据成员实际使其成为类的全局变量，会被类的所有对象共享，包括派生类的对象。用static修饰成员函数，使这个类只存在这一份函数，所有对象共享该函数，不含this指针。

4. 简述C++友元的特性以及其利弊。

   + 友元能访问类的private和protected成员，提高对数据存取效率与面向对象设计的灵活性，但破坏了类的封装性，有可能损害数据保护。

### 二. 编程题

1. Merchandise

   + 调用默认拷贝构造函数， 类中的成员指针name会指向同一片空间，而类中的一些成员函数会修改name，会造成错误。且调用m2的析构函数时，会造成name被归还两次。

   + set_name后加了const，则不能在函数体内修改数据成员的值，而set_name里改变了name的值。
   
   + 静态数据成员MerchandiseCnt未定义并初始化。 

2. FloatSet

```c++
#define EXPANDSTEP 10

class FloatSet{
    float *numbers;
    int num;
    int capacity;
public:
    FloatSet(){
        num = 0;
        capacity = 10;
        numbers = new float[capacity];
        for(int i=0;i<capacity;i++){
            numbers[i] = 0;
        }
    } 
    ~FloatSet(){
        delete numbers;
    }
    FloatSet(const FloatSet &s){
        num = s.num;
        capacity = s.capacity;
        numbers = new float[capacity];
        for(int i=0;i<capacity;i++){
            numbers[i] = s.numbers[i];
        }
    }
    bool is_empty() const{
        return num==0;
    }
    int size() const{
        return num;
    }
    bool is_element(float e) const{
        for(int i=0;i<num;i++){
            if(numbers[i] == e)
                return true;
        }
        return false;
    }
    void expand(){
        float *tmp = new float[capacity+EXPANDSTEP];
        for(int i=0;i<capacity;i++){
            tmp[i] = numbers[i];
        }
        delete numbers;
        numbers = tmp;
        capacity += EXPANDSTEP;
    }
    bool insert(float e){
        if(is_element(e)) return false;
        if(num == capacity) expand();
        numbers[num] = e;
        num++;
        return true;
    } 
    bool remove(float e){
        for(int i=0;i<num;i++){
            if(numbers[i] == e){
                for(int j=i+1;j<num;j++){
                    numbers[j-1] = numbers[j];
                }
                numbers[num-1] = 0;
                num--;
                return true;
            }
        }
        return false;
    }
    void display() const{
        for(int i=0;i<num;i++){
            cout<<numbers[i]<<" ";
        }
        cout<<endl;
    }
    bool is_subset(const FloatSet &s) const{
        if(num > s.num) return false;
        for(int i=0;i<num;i++){
            if(!s.is_element(numbers[i]))
                return false;
        }
        return true;
    }
    bool is_equal(const FloatSet &s) const{
        return (num==s.num) && is_subset(s);
    }
    FloatSet union2(const FloatSet &s) const{
        FloatSet tmp;
        for(int i=0;i<num;i++){
            tmp.insert(numbers[i]);
        }
        for(int i=0;i<s.num;i++){
            tmp.insert(s.numbers[i]);
        }
        return tmp;
    }
    FloatSet intersection2(const FloatSet &s) const{
        FloatSet tmp;
        for(int i=0;i<num;i++){
            if(s.is_element(numbers[i])){
                tmp.insert(numbers[i]);
            }
        }
        return tmp;
    }
    FloatSet difference2(const FloatSet &s) const{
        FloatSet tmp;
        for(int i=0;i<num;i++){
            if(!s.is_element(numbers[i])){
                tmp.insert(numbers[i]);
            }
        }
        return tmp;
    }
};
```