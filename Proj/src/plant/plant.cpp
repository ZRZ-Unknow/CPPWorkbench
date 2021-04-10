#include "../../include/plant.h"


SunFlower::SunFlower(){
    this->type = sunflower;
    this->health = init_table[sunflower].health;
    this->prod_sun = init_table[sunflower].prod_sun;
    this->act_time = init_table[sunflower].act_time;
    this->counter = 1;
}

int SunFlower::gen_sun(){
    return prod_sun;
}

PeaShooter::PeaShooter(){
    this->type = peashooter;
    this->health = init_table[peashooter].health;
    this->act_time = init_table[peashooter].act_time;
    this->counter = 0;
}

CherryBomb::CherryBomb(){
    this->type = cherrybomb;
    this->health = init_table[cherrybomb].health;
    this->attack_damage = init_table[cherrybomb].attack_damage;
    this->act_time = init_table[cherrybomb].act_time;
    this->counter = 1;
}