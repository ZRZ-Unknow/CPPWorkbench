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
    void buy_plant(ObjectType plant_type){
        switch(plant_type){
            case sunflower:{
                SunFlower *p = new SunFlower;
                courtyard.add_plant(p);
                break;
            }
            case peashooter:{
                PeaShooter *p = new PeaShooter;
                courtyard.add_plant(p);
                break;
            }
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
        if(Rand(5)<3){
            buy_plant(sunflower);
        }else{
            buy_plant(peashooter);
        }
    }
    void start(){
        char input;
        int tty_set_flag;
        tty_set_flag = tty_set();
        while(true){
            system("clear");
            render();
            //test_key();
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
    void test_key(){
        char ch;
        while(true){
            while(!kbhit()) continue;
            ch = getchar();
            switch(ch){
                case KEY1: printf("KEY 1\n");break;
                case KEY2: printf("KEY 2\n");break;
                case KEY3: printf("KEY 3\n");break;
                case KEY4: printf("KEY 4\n");break;
                case KEYQ: printf("KEY q\n");break;
                case KEYB: printf("KEY b\n");break;
                case KEYX: printf("KEY x\n");break;
                case KEYU: printf("KEY u\n");break;
                case KEYENTER: printf("KEY ENTER\n");break;
                case KEYLEFT: printf("KEY LEFT\n");break;
                case KEYRIGHT: printf("KEY RIGHT\n");break;
                case KEYUP: printf("KEY UP\n");break;
                case KEYDOWN: printf("KEY DOWN\n");break;
                default:break;
            }
        }
    }
};