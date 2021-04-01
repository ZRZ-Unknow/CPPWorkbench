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
    int plant_index;
    int cursor_x, cursor_y;
    bool shopping_mode;
    char logs[128];
    Store store;
    CourtYard courtyard;
public:
    Game(){
        score = total_sun = 0;
        plant_index = -1;
        cursor_x = cursor_y = -1;
        shopping_mode = false;
        memset(&logs[0], '\0', 128);
    }
    void init(){
        store.init();
        courtyard.init();
    }
    bool is_cursor_available(){
        return cursor_x!=-1 && cursor_y !=-1;
    }
    void gen_sun(){
        if(Rand(10)<7)
            total_sun += 20;
    }
    void gen_zombie(){
        if(Rand(1000)<10 && courtyard.can_add_zomble()){
            Zombie *z = new Zombie;
            courtyard.new_zomble(z);
        }
    }
    void buy_plant(ObjectType plant_type){
        if(!courtyard.can_add_plant(cursor_x, cursor_y)){
            strcat(&logs[0], "Warning!This Yard Has Plant\n");
            return;
        }
        if(!store.buy(plant_type, total_sun)){
            return;
        }
        switch(plant_type){
            case sunflower:{
                SunFlower *p = new SunFlower;
                courtyard.add_plant(p, cursor_x, cursor_y);
                break;
            }
            case peashooter:{
                PeaShooter *p = new PeaShooter;
                courtyard.add_plant(p, cursor_x, cursor_y);
                break;
            }
        }
    }
    void render(){
        store.render(plant_index);
        printf("Total Sun:%d | Score:%d\n", total_sun, score);
        courtyard.render(cursor_x, cursor_y);
        printf(logs);
        fflush(stdout);
        memset(&logs[0], '\0', 128);
    }
    void loop(){
        gen_sun();
        gen_zombie();
        store.update();
        courtyard.update();
    }
    void start(){
        char input;
        int tty_set_flag;
        tty_set_flag = tty_set();
        while(true){
            system("clear");
            render();
            while(!kbhit()) continue;
            /*while(!kbhit()){
                loop();
                continue;
            }*/
            //if(kbhit()){
                input = getchar();
                if(input == 'q') break;
                process_key(input);
            //}
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
    void process_key(char key){
        switch(key){
            case KEYU: printf("KEY u\n");break;
            case KEYENTER:{
                printf("KEY ENTER\n");
                if(plant_index!=-1 && shopping_mode){
                    ObjectType plant_type = ObjectType(plant_index);
                    buy_plant(plant_type);
                }
                break;
            } 
            case KEYB:{
                printf("KEY b\n");
                shopping_mode = true;
                if(!is_cursor_available()){
                    cursor_x = cursor_y = 0;
                }
                break;
            }
            case KEYX:{
                printf("KEY x\n");
                shopping_mode = false;
                cursor_x = cursor_y = -1;
                break;
            }
            case KEY1:case KEY2:case KEY3:case KEY4:{
                plant_index = key-'1';
                break;
            }
            case KEYA:{
                if(is_cursor_available()){
                    if(cursor_y > 0) cursor_y -= 1;
                }
                printf("KEY LEFT\n");
                break;
            }
            case KEYD:{
                if(is_cursor_available()){
                    if(cursor_y < COURTYARD_COLUMN-1) cursor_y += 1;
                }
                printf("KEY RIGHT\n");
                break;
            }
            case KEYW:{
                if(is_cursor_available()){
                    if(cursor_x > 0) cursor_x -= 1;
                }
                printf("KEY UP\n");
                break;
            }
            case KEYS:{
                if(is_cursor_available()){
                    if(cursor_x < COURTYARD_ROW-1) cursor_x += 1;
                }
                printf("KEY DOWN\n");
                break;
            }
            default:break;
        }
    }
};