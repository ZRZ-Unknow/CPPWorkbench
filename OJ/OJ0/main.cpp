#include <iostream>
#include "Singular.h"
#include "Binary.h"
using namespace std;




int main(){
    char a[9]="dstabc";
    char b[9]="asdg";
    get_min_asc(&a[0]);
    reorder(&a[0]);
    sum_len(&a[0], &b[0]);
    merge(&a[0], &b[0]);
    return 0;
}
