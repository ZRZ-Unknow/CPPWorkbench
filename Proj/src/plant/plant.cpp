#include "../../include/plant.h"


SunFlower::SunFlower(){
    this->type = sunflower;
    this->health = init_table[this->type].health;
    this->prod_sun = init_table[this->type].prod_sun;
    this->act_time = init_table[this->type].act_time;
    this->defense = init_table[this->type].defense;
    this->counter = 1;
}

int SunFlower::gen_sun(){
    return prod_sun;
}

PeaShooter::PeaShooter(){
    this->type = peashooter;
    this->health = init_table[this->type].health;
    this->act_time = init_table[this->type].act_time;
    this->defense = init_table[this->type].defense;
    this->counter = 0;
}

CherryBomb::CherryBomb(){
    this->type = cherrybomb;
    this->health = init_table[this->type].health;
    this->attack_damage = init_table[this->type].attack_damage;
    this->act_time = init_table[this->type].act_time;
    this->defense = init_table[this->type].defense;
    this->counter = 1;
}

DoubleShooter::DoubleShooter(){
    this->type = doubleshooter;
    this->health = init_table[this->type].health;
    this->act_time = init_table[this->type].act_time;
    this->defense = init_table[this->type].defense;
    this->counter = 0;
}

IceShooter::IceShooter(){
    this->type = iceshooter;
    this->health = init_table[this->type].health;
    this->act_time = init_table[this->type].act_time;
    this->defense = init_table[this->type].defense;
    this->counter = 0;
}

Wugua::Wugua(){
    this->type = wugua;
    this->health = init_table[this->type].health;
    this->attack_damage = init_table[this->type].attack_damage;
    this->act_time = init_table[this->type].act_time;
    this->defense = init_table[this->type].defense;
    this->counter = 1;
}

NutWall::NutWall(){
    this->type = nutwall;
    this->health = init_table[this->type].health;
    this->act_time = init_table[this->type].act_time;
    this->defense = init_table[this->type].defense;
    this->counter = 0;
}

HighNutWall::HighNutWall(){
    this->type = highnutwall;
    this->health = init_table[this->type].health;
    this->act_time = init_table[this->type].act_time;
    this->defense = init_table[this->type].defense;
    this->counter = 0;
}

Garlic::Garlic(){
    this->type = garlic;
    this->health = init_table[this->type].health;
    this->act_time = init_table[this->type].act_time;
    this->defense = init_table[this->type].defense;
    this->counter = 0;
}

Pumpkin::Pumpkin(){
    this->type = pumpkin;
    this->health = init_table[this->type].health;
    this->act_time = init_table[this->type].act_time;
    this->defense = init_table[this->type].defense;
    this->counter = 0;
}