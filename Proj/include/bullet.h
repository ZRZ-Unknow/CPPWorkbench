#pragma once
#include "common.h"

class Bullet: public LivingObject{
protected:
    int speed;
public:
    Bullet();
    void advance();
    bool beyond_boundary();
    bool equal_position_withdy(int x, int y, int dy);
};

class IceBullet: public Bullet{
public:
    IceBullet();
};

class Ball: public LivingObject{
public:
    Ball();
    void advance();
    bool beyond_boundary();
    bool equal_position_withdy(int x, int y, int dy);
};

struct BulletStruct{
    Bullet *bullet;
};

struct BallStruct{
    Ball *ball;
};