#include <iostream>
#include "../include/plant.h"
using namespace std;


int main(){
    Plant p1(2,5,1);
    cout<<p1.get_health()<<endl;
    return 0;
}