#include <iostream>
using namespace std;

int divide(int x, int y){
    if(y == 0) throw 0;
    return x/y; 
}

void f(){
    int a,b;
    bool right = false;
    while(!right){
	    try{
            cout << "请输入两个数：";
		    cin >> a >> b;
		    int r=divide(a,b);
		    cout << a << "除以" << b << "的商为：" << r << endl;
            right = true;
	    }catch(int){	
            cout << "除数不能为0，请重新输入"<<endl;
            right = false;
	    }
    }
}	

int main(){
    try{
        f();
    } 
    catch (...){
        cout<<"Error!"<<endl;
    }
    return 0;
} 