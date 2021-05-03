#pragma once
#include <iostream>
#include <utility>
#include <assert.h>
#include <curses.h>
#include <stdlib.h>
#include <vector>
#include <sys/time.h> 

using namespace std;


#define GRID_YLEN 23
#define GRID_XLEN 5
#define COURTYARD_ROW 4
#define COURTYARD_COLUMN 8
#define PLANT_NUM 10
#define ZOMBIE_NUM 6
#define ZOMBIE_SPACE 4 

#define REFRESH_RATE 10000
#define GAME_CLICK 100

#define WHITE_BLACK 0
#define GREEN_BLACK 1
#define YELLOW_BLACK 2
#define MAGENTA_BLACK 3
#define CYAN_BLACK 4
#define RED_BLACK 5
#define BLUE_BLACK 6


#define Rand(n) (rand()%n)

#define print(color_pair_type, format, ...) do{\
    attron(A_BOLD | COLOR_PAIR(color_pair_type));\
    printw(format, ## __VA_ARGS__);\
    attroff(A_BOLD | COLOR_PAIR(color_pair_type));}while(0);\

enum ObjectType{
    sunflower, peashooter, cherrybomb, doubleshooter, iceshooter,  wugua, nutwall, highnutwall, garlic, pumpkin,
    zombie, barricadezombie, newspaperzombie, polezombie, clownzombie, slingzombie, bullet, icebullet,
};

struct InitTable{
    char name[32];
    int health;
    int attack_damage;
    int sun_cost;
    int defense;
    int prod_sun;
    int cd_time;
    int speed;
    int act_time;  //隔多久产生动作
    int kill_score;
    int color_pair;
}static init_table[] = {
    {      "SunFlower",  70,    0,  50,  1, 50,  5,  0, 800,  0, YELLOW_BLACK},
    {     "PeaShooter",  70,    0, 100,  1,  0,  5,  0,  50,  0, GREEN_BLACK},
    {     "CherryBomb",  70, 1000, 150,  1,  0, 10,  0, 200,  0, RED_BLACK},
    {  "DoubleShooter",  70,    0, 200,  1,  0,  5,  0,  25,  0, GREEN_BLACK},
    {     "IceShooter",  70,    0, 200,  1,  0,  5,  0,  50,  0, GREEN_BLACK},
    {          "Wugua",  70, 1000, 125,  1,  0,  5,  0, 200,  0, GREEN_BLACK},
    {        "NutWall", 200,    0, 70,   1,  0,  5,  0,   1,  0, YELLOW_BLACK},
    {    "HighNutWall", 400,    0, 200,  1,  0,  5,  0,  50,  0, YELLOW_BLACK},
    {         "Garlic",  70,    0, 125,  1,  0,  5,  0,   1,  0, RED_BLACK},
    {        "Pumpkin", 200,    0, 125,  1,  0,  5,  0,   1,  0, RED_BLACK},
    {         "Zombie", 100,    5,   0,  1,  0,  0,  1, 500, 50, MAGENTA_BLACK},
    {"BarricadeZombie", 100,    5,   0,  2,  0,  0,  1, 500, 50, MAGENTA_BLACK},
    {"NewspaperZombie", 100,    5,   0,  1,  0,  0,  1, 500, 50, MAGENTA_BLACK},
    {     "PoleZombie", 100,    5,   0,  1,  0,  0,  1, 500, 50, MAGENTA_BLACK},
    {    "ClownZombie", 100,    5,   0,  1,  0,  0,  1, 500, 50, MAGENTA_BLACK},
    {    "SlingZombie", 100,    5,   0,  1,  0,  0,  1, 800, 50, MAGENTA_BLACK},
    {         "Bullet",   1,    2,   0,  1,  0,  0,  2,  10,  0, GREEN_BLACK},
    {      "IceBullet",   1,    2,   0,  1,  0,  0,  2,  10,  0, WHITE_BLACK},
};


class LivingObject{
protected:
    int coord_x, coord_y;
    int dx, dy;
    int health;
    int attack_damage;
    int defense;
    int act_time;
    int counter;
    int kill_score;
    bool frozen;
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
        health -= attack_damage/defense;
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
    bool can_eat(){
        return counter % 100 == 0;
    }
    bool is_frozen(){
        return frozen;
    }
    void make_frozen(){
        if(!frozen)
            frozen = true;
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
#define KEYENTER 10
#define KEYLEFT 4
#define KEYRIGHT 5
#define KEYUP 3
#define KEYDOWN 2

