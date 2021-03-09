#include <cstring>
#include <iostream>
#include "Binary.h"
#include "Singular.h"
using namespace std;



void sum_len(char *str1, char *str2){
    cout<<strlen(str1)+strlen(str2)<<endl;
}

void merge(char *str1, char *str2){
    int len = strlen(str1) + strlen(str2) + 1;
    char *str = (char*)malloc(len);
    strcpy(str, str1);
    strcat(str, str2);
    reorder(str);
}
