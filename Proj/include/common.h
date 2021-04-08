#pragma once
#include <iostream>
#include <utility>
#include <assert.h>
#include <stdlib.h>
#include <vector>
#include <sys/time.h> 

using namespace std;


#define GRID_YLEN 14
#define GRID_XLEN 5
#define COURTYARD_ROW 3
#define COURTYARD_COLUMN 7
#define PLANT_NUM 2
#define ZOMBIE_NUM 1
#define INFO_DISPLAY_POS (4+PLANT_NUM+(GRID_XLEN+1)*COURTYARD_ROW+1)

#define REFRESH_RATE 10000
#define GAME_CLICK 100

#define Rand(n) (rand()%n)

#define print(color_pair_type, format, ...) do{\
    attron(A_BOLD | COLOR_PAIR(color_pair_type));\
    printw(format, ## __VA_ARGS__);\
    attroff(A_BOLD | COLOR_PAIR(color_pair_type));}while(0);\

enum ObjectType{
    sunflower, peashooter, zombie, bullet,
};

struct InitTable{
    char name[16];
    int health;
    int attack_damage;
    int sun_cost;
    int prod_sun;
    int cd_time;
    int speed;
    int act_time;  //隔多久产生动作
    int kill_score;
    int color_pair;
}static init_table[] = {
    {"SunFlower", 70, 0, 50, 50, 5, 0, 800, 0, 2},
    {"PeaShooter", 70, 0, 100, 0, 5, 0, 50, 0, 1},
    {"Zombie", 100, 20, 0, 0, 0, 1, 500, 50, 3},
    {"Bullet", 1, 2, 0, 0, 0, 2, 10, 0, 4},
};


class LivingObject{
protected:
    int coord_x, coord_y;
    int dx, dy;
    int health;
    int attack_damage;
    int act_time;
    int counter;
    int kill_score;
    ObjectType type;
public:
    LivingObject(){}
    int get_health() const{
        return health;
    }
    int get_coord_x() const{
        return coord_x;
    }
    int get_coord_y() const{
        return coord_y;
    }
    int get_dx(){
        return dx;
    }
    int get_dy(){
        return dy;
    }
    bool equal_position(int x, int y) const{
        return coord_x==x && coord_y==y;
    }
    ObjectType get_type(){
        return type;
    }
    pair<int,int> get_coord() const{
        return make_pair(coord_x, coord_y);
    }
    void attacked(int attack_damage){
        health -= attack_damage;
    }
    void set_coord(int x, int y){
        coord_x = x;
        coord_y = y;
    }
    void set_dxy(int dx, int dy){
        this->dx = dx;
        this->dy = dy;
    }
    int attack() const{
        return attack_damage;
    }
    bool is_dead() const{
        return health <= 0;
    }
    void make_dead(){
        health = 0;
    }
    void increase_counter(){
        counter = (counter+1)%act_time;
    }
    int get_counter(){
        return counter;
    }
    int get_kill_score(){
        return kill_score;
    }
    bool can_act(){
        return counter == 0;
    }
    virtual void update(){}
};




#define KEY1 '1'
#define KEY2 '2'
#define KEY3 '3'
#define KEY4 '4'
#define KEYQ 'q'
#define KEYB 'b'
#define KEYX 'x'
#define KEYU 'u'
#define KEYW 'w'
#define KEYA 'a'
#define KEYS 's'
#define KEYD 'd'
#define KEYENTER 10
#define KEYLEFT 4
#define KEYRIGHT 5
#define KEYUP 3
#define KEYDOWN 2

