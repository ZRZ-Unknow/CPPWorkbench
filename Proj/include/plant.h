#pragma once
#include <iostream>
#include <utility>
using namespace std;

class Plant{
protected:
    int coord_x, coord_y;
    int health;
    int max_health;
    int sun_cost;
public:
    Plant(){}
    Plant(int health, int max_health, int sun_cost){
        this->health = health;
        this->max_health = max_health;
        this->sun_cost = sun_cost;
    }
    int get_health() const{
        return health;
    }
    void attacked(int attack_damage){
        health -= attack_damage;
    }
    bool is_dead() const{
        return health<=0;
    }
    pair<int,int> get_coord() const{
        return make_pair(coord_x, coord_y);
    }
    virtual void update(){}
};

class SunFlower: public Plant{
    const int prod_sun;
    const int prod_time;
    void update();
};