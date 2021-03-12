#include <iostream>
#include <assert.h>
using namespace std;

class ListQueue{
private:
    struct Node{
        int data;
        Node *next;
    }*top, *tail;
    int count;
public:
    ListQueue(){
        top = tail = NULL;
        count = 0;
    }
    void enQueue(int i){
        if(count==100){
            cout<<"The Queue is overflow!"<<endl;
            exit(-1);
        }
        Node *p = new Node;
        p->data = i;
        p->next = NULL;
        if(tail==NULL){
            top = tail = p;
        }else{
            assert(tail->next==NULL);
            tail->next = p;
            tail = p;
        }
        count++;
    }
    void deQueue(int &i){
        if(top==NULL){
            cout<<"The Queue is empty!"<<endl;
            exit(-1);
        }
        if(top==tail){
            i = top->data;
            delete top;
            top = tail = NULL;
        }else{
            assert(top->next!=NULL);
            Node *p = top;
            top = top->next;
            i = p->data;
            delete p;
        }
        count--;
    }
    void printAll(){
        if(top!=NULL){
            for(Node *p=top;p!=NULL;p=p->next){
                cout<<p->data<<endl;
            }
        }
    }
};

class ArrayQueue{
private:
    int *array, top, tail, size, count;
public:
    ArrayQueue(){
        size = 10;
        array = new int[size];
        top = tail = count = 0;
    }
    void enQueue(int i){
        if(count==size){
            if(size==100){
                cout<<"The Queue is overflow!"<<endl;
                exit(-1);
            }
            int *tmp = new int[size+10];
            for(int i=0;i<count;i++){
                int p = (top+i)%size;
                tmp[i] = array[p];
            }
            size += 10;
            top = 0;
            tail = count;
            delete array;
            array = tmp;
        }
        array[tail] = i;
        tail = (tail+1)%size;
        count++;
    }
    void deQueue(int &i){
        if(count==0){
            cout<<"The Queue is empty!"<<endl;
            exit(-1);
        }
        i = array[top];
        top = (top+1)%size;
        count--;
    }
    void printAll(){
        for(int i=0;i<count;i++){
            int p = (top+i)%size;
            cout<<array[p]<<endl;
        }
        cout<<"Total number: "<<count<<endl;
    }
};



int main(){
    ArrayQueue queue;
    int q=0;
    printf("q=%d\n",q);
    /*
    queue.enQueue(1);
    queue.enQueue(2);
    queue.deQueue(i);
    queue.enQueue(3);
    printf("i=%d\n",i);*/
    for(int i=0;i<15;i++){
        queue.enQueue(i);
    }
    for(int i=0;i<4;i++){
        queue.deQueue(q);
    }
    for(int i=15;i<104;i++){
        queue.enQueue(i);
    }
    printf("dddddddddddddddddd\n");
    queue.printAll();
    return 0;
}