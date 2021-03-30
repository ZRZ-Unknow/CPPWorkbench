#pragma once
#include <iostream>
#include <utility>
using namespace std;

class Zombie{
protected:
    int coord_x, coord_y;
    int health;
    int max_health;
    int speed;
    int attack_damage;
public:
    Zombie(){}
    int get_health() const{
        return health;
    }
    pair<int,int> get_coord() const{
        return make_pair(coord_x, coord_y);
    }
    void attacked(int attack_damage){
        health -= attack_damage;
    }
    bool is_dead() const{
        return health<=0;
    }
    virtual void update(){}
};