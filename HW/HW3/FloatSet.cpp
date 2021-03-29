#include <iostream>
#include <set>
using namespace std;


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


int main(){
    FloatSet f1;
    FloatSet f2 = f1;
    f1.insert(2.4);
    f1.insert(2.5);
    f1.insert(2.4);
    f2.insert(2.4);
    f2.insert(2.0);
    f1.display();
    f2.display();
    FloatSet t = f1.difference2(f2);
    t.display();
    return 0;
}