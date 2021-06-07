#include <iostream>
#include <string>
#include <cstring>
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
        if(j>=length || j<0){
            throw (string)"Index Out Of Range!";
        }
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
        if(i>=row || i<0){
            throw (string)"Index Out Of Range!";
        }
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
        if(this->row!=m.row || this->col!=m.col){
            throw (string)"Dimension Not Match!";
        }
        Matrix tmp(row, col);
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                tmp[i][j] = p_data[i][j] + m.p_data[i][j];
            }
        }
        return tmp;
    }
    Matrix operator* (const Matrix &m) const{
        if(this->col!=m.row){
            throw (string)"Dimension Not Match!";
        }
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
    friend ostream &operator<<(ostream &output, const Matrix &M){
        output<<M.row<<" "<<M.col<<"(dimension)"<<endl;
        for(int i=0;i<M.row;i++){
            for(int j=0;j<M.col;j++){
                cout<<M.p_data[i][j]<<" ";
            }
            cout<<endl;
        }
        return output;
    }
    friend istream &operator>>(istream &input, Matrix &M){
        char tmp;
        input>>M.row>>M.col;
        M.init(M.row, M.col);
        for(int i=0;i<M.row;i++){
            for(int j=0;j<M.col;j++){
                input>>M.p_data[i][j];
            }
        }
        return input;
    }
};

void f(){
    Matrix a, b;
    bool right = false;
    while(!right){
        try{
            char op;
            cout<<"请输入操作符+或*:"<<endl;
            cin>>op;
            if (op!='+' && op!='*'){
                throw (string)"No Matching Operator!";
            }
            cout<<"请输入矩阵A:"<<endl;
            cin>>a;
            cout<<"请输入矩阵B:"<<endl;
            cin>>b;
            cout<<"结果为:"<<endl;
            cout<<((op=='+')?(a+b):(a*b));
            right = true;
        }
        catch(const string &s){
            cerr<<s<<endl;
            cout<<"请重新输入!"<<endl;
            right = false;
        }
    }
}

int main(){
    try{
        f();
    }
    catch(...){
        cout<<"请重新运行本程序"<<endl;
        exit(0);
    }
    return 0;
}