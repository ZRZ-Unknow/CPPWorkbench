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
}