#pragma once
#include <iostream>
#include "common.h"
#include "store.h"
#include "plant.h"
#include "input.h"
#include "courtyard.h"
#include "zombie.h"
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
        if(Rand(100)<7)
            total_sun += 20;
    }
    void gen_zombie(){
        if(Rand(1000)<10 && courtyard.can_add_zomble()){
            Zombie *z = new Zombie;
            courtyard.new_zomble(z);
        }
    }
    void render(){
        store.render();
        printf("Total Sun:%d | Score:%d\n", total_sun, score);
        courtyard.render();
    }
    void loop(){
        gen_sun();
        gen_zombie();
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