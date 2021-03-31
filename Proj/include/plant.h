#pragma once
#include "common.h"
#include <string.h>


class SunFlower: public LivingObject{
    int prod_sun;
public:
    SunFlower(){
        this->type = sunflower;
        this->health = init_table[sunflower].health;
        this->prod_sun = init_table[sunflower].prod_sun;
    }
    void update();
};

class PeaShooter: public LivingObject{
public:
    PeaShooter(){
        this->type = peashooter;
        this->health = init_table[peashooter].health;
    }
    void update();
};