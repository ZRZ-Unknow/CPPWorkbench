#pragma once
#include "common.h"


class Zombie: public LivingObject{
    int speed;
public:
    Zombie(){
        this->type = zombie;
        this->health = init_table[zombie].health;
        this->attack_damage = init_table[zombie].attack_damage;
        this->speed = init_table[zombie].speed;
    }
    void update();
};

