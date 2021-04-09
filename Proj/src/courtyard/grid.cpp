#include <assert.h>
#include "../../include/courtyard.h"

Grid::Grid(){
    plant = zombie = NULL;
}
void Grid::set_coord(int x, int y){
    coord_x = x;
    coord_y = y;
}
bool Grid::is_planted() const{
    return plant != NULL;
}
bool Grid::has_zombie() const{
    return zombie != NULL;
}
void Grid::set_plant(LivingObject *plant){
    assert(!is_planted());
    this->plant = plant;
}
void Grid::del_plant(){
    assert(is_planted());
    plant = NULL;
}
void Grid::free_plant(){
    assert(is_planted());
    delete plant;
    plant = NULL;
}
void Grid::set_zombie(LivingObject *zombie){
    assert(!has_zombie());
    this->zombie = zombie;
}
void Grid::del_zombie(){
    assert(has_zombie());
    zombie = NULL;
}
void Grid::free_zombie(){
    assert(has_zombie());
    delete zombie;
    zombie = NULL;
}
char* Grid::get_plant_name(){
    assert(is_planted());
    ObjectType type = plant->get_type();
    return &init_table[type].name[0]; 
}
char* Grid::get_zombie_name(){
    assert(has_zombie());
     ObjectType type = zombie->get_type();
    return &init_table[type].name[0];
}
ObjectType Grid::get_plant_type(){
    assert(is_planted());
    return plant->get_type();
}
ObjectType Grid::get_zombie_type(){
    assert(has_zombie());
    return zombie->get_type();
}