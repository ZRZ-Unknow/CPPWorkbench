#pragma once
#include <iostream>
#include <assert.h>
#include "common.h"
using namespace std;




class Grid{
    int coord_x, coord_y;
    LivingObject *plant, *zombie;
public:
    Grid(){
        plant = zombie = NULL;
    }
    void set_coord(int x, int y){
        coord_x = x;
        coord_y = y;
    }
    bool is_planted() const{
        return plant != NULL;
    }
    bool has_zombie() const{
        return zombie != NULL;
    }
    void set_plant(LivingObject *plant){
        assert(!is_planted());
        this->plant = plant;
    }
    void set_zombie(LivingObject *zombie){
        assert(!has_zombie());
        this->zombie = zombie;
    }
    char *get_plant_name(){
        assert(is_planted());
        ObjectType type = plant->get_type();
        return &init_table[type].name[0]; 
    }
    char *get_zombie_name(){
        assert(has_zombie());
        ObjectType type = zombie->get_type();
        return &init_table[type].name[0];
    }
    ObjectType get_plant_type(){
        assert(is_planted());
        return plant->get_type();
    }
    ObjectType get_zombie_type(){
        assert(has_zombie());
        return zombie->get_type();
    }
};

class CourtYard{
    Grid yard[COURTYARD_ROW][COURTYARD_COLUMN];
public:
    CourtYard(){
        for(int i=0;i<COURTYARD_ROW;i++){
            for(int j=0;j<COURTYARD_COLUMN;j++){
                yard[i][j].set_coord(i, j);
            }
        }
    }
    void init();
    void update();
    void render();
    void new_zomble(LivingObject *zom);
    bool can_add_zomble(){
        for(int i=0;i<COURTYARD_ROW;i++){
            if(!yard[i][COURTYARD_COLUMN-1].has_zombie())
                return true;
        }
        return false;
    }
    bool can_add_plant(int i, int j){
        return !yard[i][j].is_planted();
    }
    bool add_plant(LivingObject *pla, int i, int j){
        assert(can_add_plant(i, j));
        yard[i][j].set_plant(pla);
        return true;
    }
    bool add_plant(LivingObject *pla){
        for(int i=0;i<COURTYARD_ROW;i++){
            for(int j=0;j<COURTYARD_COLUMN;j++){
                if(can_add_plant(i, j)){
                    add_plant(pla, i, j);
                    return true;
                }
            }
        }
        return false;
    }
};