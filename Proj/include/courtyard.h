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
    ObjectType get_plant_type(){
        assert(is_planted());
        return plant->get_type();
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
};