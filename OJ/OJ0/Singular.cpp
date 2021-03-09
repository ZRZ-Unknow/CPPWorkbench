#include <cstring>
#include <iostream>
#include "Singular.h"
using namespace std;

void get_min_asc(char *str){
    char min = *str;
    char *point = str; 
    for(int i=0;i<strlen(str);i++){
        if(*point<min)  min = *point;
        point++;
    }
    cout<<min<<endl;
}

void reorder(char *str){
    for(char *p=str;*p!='\0';p++){
        for(char *q=p+1;*q!='\0';q++){
            if(*p>*q){
                char tmp=*p;
                *p = *q;
                *q = tmp;
            }
        }
    }
    cout<<str<<endl;
}