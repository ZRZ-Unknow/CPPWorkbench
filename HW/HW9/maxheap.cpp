#include <iostream>
#include <assert.h>
using namespace std;



template<class Type>
class MaxHeap {
private:
    Type* Data;
    int Size; //当前大小
    int Capacity; //总容量
    void shiftup(int start){
        int curr = start;
        int parent = (curr-1)/2;
        while(curr>0){
            if(Data[parent] < Data[curr]){
                Type tmp = Data[curr];
                Data[curr] = Data[parent];
                Data[parent] = tmp;
                curr = parent;
                parent = (parent-1)/2;
            }else{
                break;
            }
        }

    }
    void shiftdown(int start){
        int curr = start;
        int child = 2*curr + 1;
        while(child < Size){ 
            if(child < Size-1 && Data[child] < Data[child+1])
                child++;
            if(Data[curr] < Data[child]){
                Type tmp = Data[curr];
                Data[curr] = Data[child];
                Data[child] = tmp;
                curr = child;
                child = 2*child+1;
            }else{
                break;
            }
        }
    }
public:
    MaxHeap(){
        Size = 0;
        Capacity = 10;
        Data = new Type[Capacity];
    }
    MaxHeap(int Capacity){
        Size = 0;
        this->Capacity = Capacity;
        Data = new Type[Capacity];
    }
    ~MaxHeap(){
        delete []Data;
    }
    bool Insert(Type element){
        if(IsFull())
            return false;
        Data[Size] = element;
        shiftup(Size);
        Size++;
        return true;
    }
    Type DeleteMax(){
        Type _max = Data[0];
        Size--;
        Data[0] = Data[Size];
        shiftdown(0);
        return _max;
    }
    bool IsFull(){
        return Size == Capacity;
    }
    bool IsEmpty(){
        return Size == 0;
    }
    void Print(){
        for(int i=0;i<Size;i++){
            cout<<Data[i]<<" ";
        }
        cout<<endl;
    }
};

int main(){
    MaxHeap<int> heap(20);
    for(int i=0;i<15;i++){
        heap.Insert(i);
    }
    heap.Print();
    cout<<"delete max:"<<heap.DeleteMax()<<endl;
    heap.Print();
    cout<<"delete max:"<<heap.DeleteMax()<<endl;
    heap.Print();
    MaxHeap<double> _heap(20);
    for(int i=0;i<15;i++){
        _heap.Insert(i*1.5);
    }
    _heap.Print();
    cout<<"delete max:"<<_heap.DeleteMax()<<endl;
    _heap.Print();
    cout<<"delete max:"<<_heap.DeleteMax()<<endl;
    _heap.Print();
    return 0;
}
