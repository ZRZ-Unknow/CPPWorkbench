#include "../../include/zombie.h"

#define CONSTRUCTOR() do{\
    this->health = init_table[this->type].health;\
    this->attack_damage = init_table[this->type].attack_damage;\
    this->speed = init_table[this->type].speed;\
    this->act_time = init_table[this->type].act_time;\
    this->kill_score = init_table[this->type].kill_score;\
    this->defense = init_table[this->type].defense;\
    this->counter = 1;\
    this->dx = 0;\
    this->dy = 0;\
    this->frozen = false;\
    this->frozen_time = 0;}while(0)\

#define UPDATE() do{\
    if(this->frozen){\
        if(this->act_time == init_table[this->type].act_time){\
            this->act_time *= 2;\
        }\
        this->frozen_time++;\
    }else{\
        if(this->act_time != init_table[this->type].act_time){\
            this->act_time = init_table[this->type].act_time;\
        }\
    }\
    if(frozen_time > act_time*2)\
        frozen = false;}while(0)\


Zombie::Zombie(){
    this->type = zombie;
    CONSTRUCTOR();
}

void Zombie::update(){
    UPDATE();
}

BarricadeZombie::BarricadeZombie(){
    this->type = barricadezombie;
    CONSTRUCTOR();
}

void BarricadeZombie::update(){
    UPDATE();
}

NewspaperZombie::NewspaperZombie(){
    this->type = newspaperzombie;
    this->have_paper = true;
    CONSTRUCTOR();
}

bool NewspaperZombie::having_paper(){
    return have_paper;
}

void NewspaperZombie::update(){
    if(have_paper && health < init_table[this->type].health/2){
        have_paper = false;
        this->act_time = init_table[this->type].act_time/2;
    }
    if(have_paper){
        if(this->frozen){
            if(this->act_time == init_table[this->type].act_time)
                this->act_time *= 2;
            this->frozen_time++;
        }else{
            if(this->act_time != init_table[this->type].act_time)
                this->act_time = init_table[this->type].act_time;
        }
        if(frozen_time > act_time*2){
            frozen = false;
            frozen_time = 0;
        }
    }else{
        if(this->frozen){
            if(this->act_time == init_table[this->type].act_time/2)
                this->act_time *= 2;
            this->frozen_time++;
        }else{
            if(this->act_time != init_table[this->type].act_time/2)
                this->act_time = init_table[this->type].act_time/2;
        }
        if(frozen_time > act_time*2){
            frozen = false;
            frozen_time = 0;
        }
    }
        
}

PoleZombie::PoleZombie(){
    this->type = polezombie;
    this->have_pole = true;
    CONSTRUCTOR();
}

bool PoleZombie::having_pole(){
    return have_pole;
}

void PoleZombie::use_pole(){
    have_pole = false;
}

void PoleZombie::update(){
    UPDATE();
}

ClownZombie::ClownZombie(){
    this->type = clownzombie;
    CONSTRUCTOR();
}

void ClownZombie::update(){
    UPDATE();
}

SlingZombie::SlingZombie(){
    this->type = slingzombie;
    this->have_ball = true;
    CONSTRUCTOR();
}

bool SlingZombie::having_ball(){
    return have_ball;
}

void SlingZombie::use_ball(){
    have_ball = false;
}

void SlingZombie::update(){
    UPDATE();
}