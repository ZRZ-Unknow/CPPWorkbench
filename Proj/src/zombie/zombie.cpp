#include "../../include/zombie.h"



Zombie::Zombie(){
    this->type = zombie;
    this->health = init_table[zombie].health;
    this->attack_damage = init_table[zombie].attack_damage;
    this->speed = init_table[zombie].speed;
    this->act_time = init_table[zombie].act_time;
    this->kill_score = init_table[zombie].kill_score;
    this->counter = 1;
    this->dx = 0;
    this->dy = 0;
    this->frozen = false;
    this->frozen_time = 0;
}

void Zombie::update(){
    if(this->frozen){
        if(this->act_time == init_table[this->type].act_time){
            this->act_time *= 2;
        }
        this->frozen_time++;
    }else{
        if(this->act_time != init_table[this->type].act_time){
            this->act_time = init_table[this->type].act_time;
        }
    }
    if(frozen_time > act_time*2)
        frozen = false;
}