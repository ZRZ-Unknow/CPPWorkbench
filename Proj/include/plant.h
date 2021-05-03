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

class DoubleShooter: public LivingObject{
public:
    DoubleShooter();
    void update(){}
};

class IceShooter: public LivingObject{
public:
    IceShooter();
    void update(){}
};

class Wugua: public LivingObject{
public:
    Wugua();
    void update(){}
};

class NutWall: public LivingObject{
public:
    NutWall();
    void update(){}
};

class HighNutWall: public LivingObject{
public:
    HighNutWall();
    void update(){}
};

class Garlic: public LivingObject{
public:
    Garlic();
    void update(){}
};

class Pumpkin: public LivingObject{
public:
    Pumpkin();
    void update(){}
};