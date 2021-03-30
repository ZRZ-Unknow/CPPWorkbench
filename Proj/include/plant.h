#pragma once
#include "common.h"
#include <string.h>


class SunFlower: public LivingObject{
    int prod_sun;
public:
    SunFlower(){
        this->type = sunflower;
        this->health = init_table[0].health;
        this->sun_cost = init_table[0].sun_cost;
        this->prod_sun = init_table[0].prod_sun;
        this->cd_time = init_table[0].cd_time;
    }
    void update();
};

class PeaShooter: public LivingObject{
public:
    PeaShooter(){
        this->type = peashooter;
        this->health = init_table[1].health;
        this->sun_cost = init_table[1].sun_cost;
        this->cd_time = init_table[1].cd_time;
    }
    void update();
};