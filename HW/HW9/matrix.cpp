#include <iostream>
using namespace std;

template<class Type>
class Matrix;

template<class Type>
class Array{
    Type *data;
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
        data = new Type[c];
    }
    Type &operator[] (int j){
        return data[j];
    }
    friend class Matrix<Type>;
};

template<class Type>
class Matrix{
    Array<Type> *p_data;
    int row, col; 
    void init(int r, int c){
        row = r;
        col = c;
        p_data = new Array<Type>[r];
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
    Array<Type> &operator[] (int i){ 
        return p_data[i];
    }
    Matrix<Type> &operator= (const Matrix &m){ 
        if(&m == this) return *this;
        if(row != m.row || col != m.col){
            delete []p_data;
            init(m.row, m.col); 
        }
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                Type tmp = m.p_data[i].data[j] ;
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
    Matrix<Type> operator+ (const Matrix &m) const{ 
        Matrix tmp(row, col);
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                tmp[i][j] = p_data[i][j] + m.p_data[i][j];
            }
        }
        return tmp;
    }
    Matrix<Type> operator* (const Matrix &m) const{
        Matrix tmp(this->row, m.col);
        for(int i=0;i<tmp.row;i++){
            for(int j=0;j<tmp.col;j++){
                Type sum;
                for(int p=0;p<col;p++){
                    if(p==0)
                        sum = p_data[i][p] * m.p_data[p][j];
                    else
                        sum = sum + p_data[i][p] * m.p_data[p][j];
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
    void set(Type p){
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                p_data[i].data[j] = p;
            }
        }
    }
};

class Complex{
    double real, imag;
public:
    Complex(){
        real = 0;
        imag = 0;
    }
    Complex(double r, double i){
        real = r;
        imag = i;
    }
    bool operator ==(const Complex& x) const{
        return (real == x.real) && (imag == x.imag);
    }
    bool operator !=(const Complex& x) const{
        return (real != x.real) || (imag != x.imag);
    }
    Complex operator +(const Complex& x){
        return Complex(real + x.real, imag + x.imag);
    }
    Complex operator *(const Complex& x){
        return Complex(real * x.real- imag * x.imag, real * x.imag + imag * x.real);
    } 
    friend ostream &operator<<(ostream &out, const Complex &c){
        out<<c.real<<"+"<<c.imag<<"i";
        return out;
    }
};



int main(){
    cout<<"============Test int============"<<endl;
    do{
        Matrix<int> a(2,2);
        a.set(1);
        Matrix<int> b;
        b = a; 
        Matrix<int> c = a+b;
        Matrix<int> d(2,4);
        d.set(3);
        Matrix<int> e = a*d;
        cout<<"a"<<endl;
        a.print();
        cout<<"b"<<endl;
        b.print();
        cout<<"c=a+b"<<endl;
        c.print();
        cout<<"d"<<endl;
        d.print();
        cout<<"e=a*d"<<endl;
        e.print();
    }while(0);
    cout<<"============Test complex============"<<endl;
    Complex c1(2, 4.5);
    Complex c2(1.2, 4);
    Complex c3(2, 2.3);
    Complex c4 = c1*c3;
    Matrix<Complex> a(2,2);
    a.set(c1);
    Matrix<Complex> b;
    b = a; 
    Matrix<Complex> c = a+b;
    cout<<"a"<<endl;
    a.print();
    cout<<"b"<<endl;
    b.print();
    cout<<"c=a+b"<<endl;
    c.print();
    Matrix<Complex> d(2,4);
    d.set(c2);
    Matrix<Complex> e = a*d;
    cout<<"d"<<endl;
    d.print();
    cout<<"e=a*d"<<endl;
    e.print();
    return 0;
}