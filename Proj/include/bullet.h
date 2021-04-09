#pragma once
#include "common.h"

class Bullet: public LivingObject{
    int speed;
public:
    Bullet();
    void advance();
    bool beyond_boundary();
    bool equal_position_withdy(int x, int y, int dy);
};


struct BulletStruct{
    Bullet *bullet;
};