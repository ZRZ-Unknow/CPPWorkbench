#pragma once
#include <iostream>
#include "common.h"
#include "store.h"
#include "plant.h"
#include "input.h"
#include "courtyard.h"
#include "zombie.h"
#include "bullet.h"
#include <vector>
using namespace std;



class Game{
    int score;
    int total_sun;
    int plant_index;
    int cursor_x, cursor_y;
    bool shopping_mode;
    bool game_lose;
    char logs[128];
    Store store;
    CourtYard courtyard;
    vector<BulletStruct> all_bullets;
public:
    Game(){
        score = total_sun = 0;
        plant_index = -1;
        cursor_x = cursor_y = -1;
        shopping_mode = game_lose = false;
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
            total_sun += 25;
    }
    void gen_zombie(){
        if(Rand(100)<10 && courtyard.can_add_zomble()){
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
        courtyard.render(cursor_x, cursor_y, all_bullets);
        printf(logs);
        fflush(stdout);
        memset(&logs[0], '\0', 128);
    }
    void loop(){
        //首先check status，检查子弹、僵尸、植物等是否死亡，并更新分数。
        //然后update，僵尸前进，植物产生阳光，植物产生子弹，子弹前进，判断是否吃植物，是否打中僵尸。
        //最后随机产生阳光、新僵尸等。
        courtyard.check_status(all_bullets, score);
        store.update();
        courtyard.update(all_bullets, game_lose, total_sun);
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
            if(game_lose){
                printf("Lose Game!!!\n");
                exit(0);
            }
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
                if(plant_index!=-1 && shopping_mode){
                    ObjectType plant_type = ObjectType(plant_index);
                    buy_plant(plant_type);
                }
                break;
            } 
            case KEYB:{
                shopping_mode = true;
                if(!is_cursor_available()){
                    cursor_x = cursor_y = 0;
                }
                break;
            }
            case KEYX:{
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
                break;
            }
            case KEYD:{
                if(is_cursor_available()){
                    if(cursor_y < COURTYARD_COLUMN-1) cursor_y += 1;
                }
                break;
            }
            case KEYW:{
                if(is_cursor_available()){
                    if(cursor_x > 0) cursor_x -= 1;
                }
                break;
            }
            case KEYS:{
                if(is_cursor_available()){
                    if(cursor_x < COURTYARD_ROW-1) cursor_x += 1;
                }
                break;
            }
            default:break;
        }
    }
};