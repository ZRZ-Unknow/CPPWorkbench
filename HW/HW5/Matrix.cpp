#include <iostream>
using namespace std;

class Array{
    int *data;
    int length;
public:
    Array(){
        length = 0;
    }
    Array(int c){
        set(c);
    }
    ~Array(){
        delete []data;
    }
    void set(int c){
        length = c;
        data = new int[c];
    }
    int &operator[] (int j){
        return data[j];
    }
    friend class Matrix;
};

class Matrix{
    Array *p_data;
    int row, col; 
    void init(int r, int c){
        row = r;
        col = c;
        p_data = new Array[r];
        for(int i=0;i<row;i++){
            p_data[i].set(c);
        }
    }
public:
    Matrix(){
        row = col = 0;
        p_data = NULL;
    }
    Matrix(int r, int c){
        init(r, c); 
    }
    ~Matrix(){
        delete []p_data;
    }
    Array &operator[] (int i){ 
        return p_data[i];
    }
    Matrix &operator= (const Matrix &m){ 
        if(&m == this) return *this;
        if(row != m.row || col != m.col){
            delete []p_data;
            init(m.row, m.col); 
        }
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                int tmp = m.p_data[i].data[j] ;
                p_data[i].data[j] = tmp;
            }
        }
        return *this;
    }
    bool operator== (const Matrix &m) const{
        if(row != m.row || col != m.col)
            return false;
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                if(p_data[i][j]!=m.p_data[i][j])
                    return false;
            }
        }
        return true;
    }
    Matrix operator+ (const Matrix &m) const{ 
        Matrix tmp(row, col);
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                tmp[i][j] = p_data[i][j] + m.p_data[i][j];
            }
        }
        return tmp;
    }
    Matrix operator* (const Matrix &m) const{
        Matrix tmp(this->row, m.col);
        for(int i=0;i<tmp.row;i++){
            for(int j=0;j<tmp.col;j++){
                int sum = 0;
                for(int p=0;p<col;p++){
                    sum += p_data[i][p] * m.p_data[p][j];
                }
                tmp[i][j] = sum;
            }
        }
        return tmp;
    }
    void print(){
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                cout<<p_data[i].data[j]<<" ";
            }
            cout<<endl;
        }
    }
    void set(int p){
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                p_data[i].data[j] = p;
                p++;
            }
        }
    }
};


int main(){
    Matrix a(2,2);
    a.set(1);
    Matrix b;
    b = a; 
    Matrix c = a+b;
    Matrix d(2,4);
    d.set(0);
    Matrix e = a*d;
    a.print();
    b.print();
    c.print();
    d.print();
    e.print();
    return 0;
}