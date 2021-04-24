#include <iostream>
#include <assert.h>
using namespace std;


class Queue{
protected:
    struct Node{
        int data;
        Node *next;
        Node *prev;
    }*top;
public:
    Queue():top(NULL){}
    virtual bool enqueue(int num) = 0;
    virtual bool dequeue(int &num) = 0;
    void print(){
        for(Node *p=top;p!=NULL;p=p->next){
            cout<<p->data<<" ";
        }
        cout<<endl;
    }
};

class Queue1:public Queue{
    Node *tail;
public:
    Queue1():tail(NULL){}
    bool enqueue(int num){
        Node *p = new Node;
        p->data = num;
        p->next = NULL;
        if(tail==NULL){
            top = tail = p;
            p->prev = NULL;
        }else{
            assert(tail->next==NULL);
            tail->next = p;
            p->prev = tail;
            tail = p;
        }
        return true;
    }
    bool dequeue(int &num){
        if(top==NULL){
            cout<<"The Queue is empty!"<<endl;
            return false;
        }
        if(top==tail){
            num = top->data;
            delete top;
            top = tail = NULL;
        }else{
            assert(top->next!=NULL);
            Node *p = top;
            top = top->next;
            top->prev = NULL;
            num = p->data;
            delete p;
        }
        return true;
    }
};

class Queue2:public Queue{
    Node *min;
    void find_min(){
        min = top;
        for(Node *p=top->next;p!=NULL;p=p->next){
            if(min->data > p->data)
                min = p;
        }
    }
public:
    Queue2():min(NULL){}
    bool enqueue(int num){
        Node *p = new Node;
        p->data = num;
        p->prev = NULL;
        if(top==NULL){
            p->next = NULL;
            top = min = p;
        }else{
            p->next = top;
            top->prev = p;
            top = p;
            if(min->data > top->data)
                min = top;
        }
        return true;
    }
    bool dequeue(int &num){
        if(top==NULL){
            cout<<"The Queue is empty!"<<endl;
            return false;
        }
        if(top->next==NULL){
            num = top->data;
            delete top;
            top = min = NULL;
        }else{
            if(min==top){
                Node *p = top;
                top = top->next;
                top->prev = NULL;
                num = p->data;
                delete p;
                min = NULL;
            }else{
                assert(min->prev!=NULL);
                Node *prev = min->prev;
                Node *next = min->next;
                prev->next = next;
                if(next)
                    next->prev = prev;
                num = min->data;
                delete min;
                min = NULL;
            }
            find_min();
        }
        return true;
    }
};

class Queue3:public Queue{
    Node *max;
    void find_max(){
        max = top;
        for(Node *p=top->next;p!=NULL;p=p->next){
            if(max->data < p->data)
                max = p;
        }
    }
public:
    Queue3():max(NULL){}
    bool enqueue(int num){
        Node *p = new Node;
        p->data = num;
        p->prev = NULL;
        if(top==NULL){
            p->next = NULL;
            top = max = p;
        }else{
            p->next = top;
            top->prev = p;
            top = p;
            if(max->data < top->data)
                max = top;
        }
        return true;
    }
    bool dequeue(int &num){
        if(top==NULL){
            cout<<"The Queue is empty!"<<endl;
            return false;
        }
        if(top->next==NULL){
            num = top->data;
            delete top;
            top = max = NULL;
        }else{
            if(max==top){
                Node *p = top;
                top = top->next;
                top->prev = NULL;
                num = p->data;
                delete p;
                max = NULL;
            }else{
                assert(max->prev!=NULL);
                Node *prev = max->prev;
                Node *next = max->next;
                prev->next = next;
                if(next)
                    next->prev = prev;
                num = max->data;
                delete max;
                max = NULL;
            }
            find_max();
        }
        return true;
    }
};


int main(){
    Queue2 *queue = new Queue2();
    int q;
    queue->enqueue(1);
    queue->enqueue(2);
    queue->enqueue(9);
    queue->dequeue(q);
    queue->enqueue(3);
    queue->print();
    queue->dequeue(q);
    queue->print();
    queue->enqueue(0);
    queue->enqueue(1);
    queue->print();
    queue->dequeue(q);
    queue->print();
    queue->dequeue(q);
    queue->print();
    queue->dequeue(q);
    queue->print();
    queue->dequeue(q);
    queue->print();
    return 0;
}