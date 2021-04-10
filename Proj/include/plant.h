#pragma once
#include "common.h"


class SunFlower: public LivingObject{
    int prod_sun;
public:
    SunFlower();
    int gen_sun();
    void update(){}
};

class PeaShooter: public LivingObject{
public:
    PeaShooter();
    void update(){}
};

class CherryBomb: public LivingObject{
public:
    CherryBomb();
    void update(){}
};