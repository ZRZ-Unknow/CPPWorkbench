#include "../../include/bullet.h"

Bullet::Bullet(){
    this->type = bullet;
    this->speed = init_table[bullet].speed;
    this->health = init_table[bullet].health;
    this->attack_damage = init_table[bullet].attack_damage;
    this->act_time = init_table[bullet].act_time;
    this->counter = 0;
    this->dx = 0;
    this->dy = 0;
}

void Bullet::advance(){
    dy += 1;
    if(dy == GRID_YLEN){
        dy = 0;
        coord_y += 1;
    }
}

bool Bullet::beyond_boundary(){
    return coord_y > COURTYARD_COLUMN-1;
}

bool Bullet::equal_position_withdy(int x, int y, int dy){
    return this->coord_x == x && this->coord_y == y && this->dy == dy;
}