#pragma once
#include <iostream>
#include <utility>
#include <assert.h>
#include <stdlib.h>

using namespace std;


#define GRID_XLEN 14
#define GRID_YLEN 5
#define COURTYARD_ROW 3
#define COURTYARD_COLUMN 7
#define PLANT_NUM 2

#define Rand(n) (rand()%n)

enum ObjectType{
    sunflower, peashooter, zombie,
};

struct InitTable{
    char name[16];
    int health;
    int attack_damage;
    int sun_cost;
    int prod_sun;
    int cd_time;
    int speed;
}static init_table[] = {
    {"SunFlower", 100, 0, 50, 100, 10, 0 },
    {"PeaShooter", 100, 30, 100, 0, 10, 0},
    {"Zombie", 100, 50, 0, 0, 0, 10},
};


class LivingObject{
protected:
    int coord_x, coord_y;
    int health;
    int attack_damage;
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










