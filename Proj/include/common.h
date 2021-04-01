#pragma once
#include <iostream>
#include <utility>
#include <assert.h>
#include <stdlib.h>
#include <vector>

using namespace std;


#define GRID_YLEN 14
#define GRID_XLEN 5
#define COURTYARD_ROW 3
#define COURTYARD_COLUMN 7
#define PLANT_NUM 2
#define ZOMBIE_NUM 1

#define Rand(n) (rand()%n)

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
    int act_time;
    int kill_score;
}static init_table[] = {
    {"SunFlower", 100, 0, 50, 50, 5, 0, 5, 0},
    {"PeaShooter", 100, 0, 100, 0, 5, 0, 2, 0},
    {"Zombie", 100, 20, 0, 0, 0, 1, 5, 50},
    {"Bullet", 1, 25, 0, 0, 0, 2, 1, 0},
};


class LivingObject{
protected:
    int coord_x, coord_y;
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
#define KEYLEFT 68
#define KEYRIGHT 67
#define KEYUP 65
#define KEYDOWN 66

