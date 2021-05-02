#include <assert.h>
#include "../../include/courtyard.h"

Grid::Grid(){
    plant = plant_mount = NULL;
    free_space = GRID_XLEN-1;
}
void Grid::set_coord(int x, int y){
    coord_x = x;
    coord_y = y;
}
bool Grid::is_planted(bool mount) const{
    if(mount) return plant_mount != NULL;
    return plant != NULL;
}
bool Grid::has_zombie() const{
    return zombies.size() > 0;
}
bool Grid::has_zombie(int vec_ind) const{
    return zombies.size() > vec_ind;
}
void Grid::set_plant(LivingObject *plant, bool mount){
    assert(!is_planted(mount));
    if(mount) this->plant_mount = plant;
    else this->plant = plant;
}
void Grid::del_plant(bool mount){
    assert(is_planted(mount));
    if(mount) plant_mount = NULL;
    else plant = NULL;
}
void Grid::free_plant(bool mount){
    assert(is_planted(mount));
    if(mount){
        delete plant_mount;
        plant_mount = NULL;
    }else{
        delete plant;
        plant = NULL;
    }
}
bool Grid::can_add_zombie() const{
    return zombies.size()<GRID_XLEN-1;
}
void Grid::set_zombie(LivingObject *zombie){
    assert(can_add_zombie());
    zombies.push_back(zombie);
}
void Grid::del_zombie(int vec_ind){
    zombies.erase(zombies.begin()+vec_ind);
}
void Grid::free_zombie(int vec_ind){
    delete zombies[vec_ind];
    zombies.erase(zombies.begin()+vec_ind);
}
char* Grid::get_plant_name(){
    assert(is_planted());
    ObjectType type = plant->get_type();
    return &init_table[type].name[0]; 
}
char* Grid::get_zombie_name(int vec_ind){
    ObjectType type = zombies[vec_ind]->get_type();
    return &init_table[type].name[0];
}
ObjectType Grid::get_plant_type(){
    assert(is_planted());
    return plant->get_type();
}
ObjectType Grid::get_zombie_type(int vec_ind){
    return zombies[vec_ind]->get_type();
}