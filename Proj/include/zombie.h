#pragma once
#include "common.h"


class Zombie: public LivingObject{
    int speed;
    int frozen_time;
public:
    Zombie();
    void update();
};

class BarricadeZombie: public LivingObject{
    int speed;
    int frozen_time;
public:
    BarricadeZombie();
    void update();
};

class NewspaperZombie: public LivingObject{
    int speed;
    int frozen_time;
    bool have_paper;
public:
    NewspaperZombie();
    void update();
    bool having_paper();
};

class PoleZombie: public LivingObject{
    int speed;
    int frozen_time;
    bool have_pole;
public:
    PoleZombie();
    void update();
    bool having_pole();
    void use_pole();
};

class ClownZombie: public LivingObject{
    int speed;
    int frozen_time;
public:
    ClownZombie();
    void update();
};

class SlingZombie: public LivingObject{
    int speed;
    int frozen_time;
    bool have_ball;
public:
    SlingZombie();
    void update();
    bool having_ball();
    void use_ball();
};

