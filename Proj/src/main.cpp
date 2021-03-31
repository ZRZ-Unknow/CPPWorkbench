#include <iostream>
#include <stdio.h>
#include "../include/plant.h"
#include "../include/zombie.h"
#include "../include/courtyard.h"
#include "../include/input.h"
#include "../include/store.h"
#include "../include/game.h"
using namespace std;


int main(){
    //SunFlower p1;
    //PeaShooter p2;
    //Zombie p3;
    Game g;
    //cout<<p1.get_health()<<" "<<p2.get_health()<<" "<<p3.get_type() <<endl;
    //CourtYard c;
    //Store s;
    //cout<<s.plants[0].get_name()<<" "<<s.plants[1].get_name()<<endl;
    //c.init();
    g.init();
    g.start();
    /*char input;
    int tty_set_flag;
    tty_set_flag = tty_set();
    while(true){
        system("clear");
        g.render();
        while(!kbhit()) continue;
        input = getchar();
        printf("%c\n",input);
        if(input == 'q') break;
        fflush(stdout);
    }
    if(tty_set_flag == 0)
        tty_reset();*/
    return 0;
}