#pragma once
#include <iostream>
#include "common.h"
#include "store.h"
#include "plant.h"
#include "input.h"
#include "courtyard.h"
using namespace std;



class Game{
    int score;
    int total_sun;
    Store store;
    CourtYard courtyard;
public:
    Game(){
        score = total_sun = 0;
    }
    void init(){
        store.init();
        courtyard.init();
    }
    void gen_sun(){
        if(Rand()<7)
            total_sun += 10*Rand();
    }
    void render(){
        store.render();
        printf("Total Sun:%d | Score:%d\n", total_sun, score);
        courtyard.render();
    }
    void loop(){
        //gen_sun();
    }
    void start(){
        char input;
        int tty_set_flag;
        tty_set_flag = tty_set();
        while(true){
            system("clear");
            render();
            /*while(!kbhit()){
                loop();
                continue;
            }*/
            if(kbhit()){
                input = getchar();
                printf("%c\n",input);
                if(input == 'q') break;
            }
            loop();
        }
        if(tty_set_flag == 0)
            tty_reset();
    }
};