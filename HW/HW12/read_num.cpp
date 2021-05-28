#include <iostream>
#include <fstream>
#include <memory.h>
using namespace std;

int main(){
    int x;
    ofstream out_file("./number.txt",ios::out);
    if(out_file.fail()) exit(-1);
    cout<<"Generated Number ended with 0:"<<endl;
    for(int i=0;i<1000;i++){
        x = rand()%100+1;
        out_file<<x;
        if(x%10 == 0) cout<<x<<" ";
    }
    cout<<endl;
    out_file<<endl;
    out_file.close();
    ifstream file("./number.txt",ios::in);
    if(file.fail()) exit(-1);
    char t[5]="\0";
    int i=0;
    cout<<"Found Number ended with 0:"<<endl;
    while(true){
        file.seekg(i, ios::beg);
        file.read(t, 2);
        if(t[1]=='\n') break;
        if(t[0]=='0' && t[1]=='0'){
            file.seekg(i-1, ios::beg);
            file.read(t, 3);
            cout<<t<<" ";
            memset(t, '\0', 5);
            i+=2;
        }else if(t[0]=='0'){
            file.seekg(i-1, ios::beg);
            file.read(t, 2);
            cout<<t<<" ";
            memset(t, '\0', 5);
            i++;
        }else{
            i++;
        }
    }
    cout<<endl;
    file.close();
    return 0;
}