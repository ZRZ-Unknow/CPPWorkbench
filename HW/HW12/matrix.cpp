#include <iostream>
#include <fstream>
using namespace std;


template<class Type> class Matrix;

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
    friend ostream &operator<<(ostream &output, const Complex &C){
        output<<C.real<<"+"<<C.imag<<"i";
        return output;
    }
    friend istream &operator>>(istream &input, Complex &C){
        char tmp;
        input>>C.real>>tmp>>C.imag;
        return input;
    }
};

template<class Type> class Array{
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

template<class Type> class Matrix{
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
    friend ostream &operator<<(ostream &output, const Matrix<Type> &M){
        output<<M.row<<" "<<M.col<<endl;
        for(int i=0;i<M.row;i++){
            for(int j=0;j<M.col;j++){
                cout<<M.p_data[i][j]<<" ";
            }
            cout<<endl;
        }
        return output;
    }
    friend istream &operator>>(istream &input, Matrix<Type> &M){
        char tmp;
        input>>M.row>>M.col;
        M.init(M.row, M.col);
        Complex c;
        for(int i=0;i<M.row;i++){
            for(int j=0;j<M.col;j++){
                input>>M.p_data[i][j];
            }
        }
        return input;
    }
};

int main(){
    Complex c;
    cin>>c;
    cout<<c<<endl;
    Matrix<Complex> a;
    ifstream in_file("./matrix_test.txt",ios::in);
    if(!in_file) exit(-1);
    for(int i=0;i<4;i++){
        in_file>>a;
        cout<<a;
    }
    in_file.close();
    return 0;
}