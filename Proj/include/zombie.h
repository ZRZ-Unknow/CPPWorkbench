#pragma once
#include "common.h"


class Zombie: public LivingObject{
    int speed;
    int frozen_time;
public:
    Zombie();
    void update();
};




