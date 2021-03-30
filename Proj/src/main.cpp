#include <iostream>
#include <stdio.h>
#include "../include/plant.h"
#include "../include/zombie.h"
#include "../include/courtyard.h"
#include "../include/input.h"
using namespace std;


int main(){
    SunFlower p1;
    PeaShooter p2;
    Zombie p3;
    cout<<p1.get_health()<<" "<<p2.get_health()<<endl;
    CourtYard c;
    c.init();
    char input;
    int tty_set_flag;
    tty_set_flag = tty_set();
    while(true){
        c.render();
        while(!kbhit()) continue;
        input = getchar();
        printf("%c\n",input);
        if(input == 'q') break;
    }
    if(tty_set_flag == 0)
        tty_reset();
    return 0;
}