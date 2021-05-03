#include <assert.h>
#include "../../include/courtyard.h"

Grid::Grid(){
    plant = plant_mount = NULL;
    for(int i=0;i<ZOMBIE_SPACE;i++)
        zombies[i] = NULL;
}
void Grid::set_coord(int x, int y){
    coord_x = x;
    coord_y = y;
}
bool Grid::is_planted(bool mount) const{
    if(mount) return plant_mount != NULL;
    return plant != NULL;
}
int Grid::get_free_space(int find_first) const{
    int tmp = 0;
    for(int i=0;i<ZOMBIE_SPACE;i++){
        if(zombies[i]==NULL){
            if(find_first) return i;
            tmp++;
        }
    }
    return tmp;
}
bool Grid::has_zombie() const{
    return get_free_space() < ZOMBIE_SPACE;
}
bool Grid::has_zombie(int vec_ind) const{
    if(vec_ind>ZOMBIE_SPACE-1) return false;
    return zombies[vec_ind] != NULL;
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
    return get_free_space()>0;
}
void Grid::set_zombie(LivingObject *zombie){
    assert(can_add_zombie());
    int ind = get_free_space(true);
    zombies[ind] = zombie;
}
void Grid::del_zombie(int vec_ind){
    assert(zombies[vec_ind]!=NULL);
    zombies[vec_ind] = NULL;
}
void Grid::free_zombie(int vec_ind){
    assert(zombies[vec_ind]!=NULL);
    delete zombies[vec_ind];
    zombies[vec_ind] = NULL;
}
char* Grid::get_plant_name(){
    assert(is_planted());
    ObjectType type = plant->get_type();
    return &init_table[type].name[0]; 
}
char* Grid::get_zombie_name(int vec_ind){
    assert(zombies[vec_ind]!=NULL);
    ObjectType type = zombies[vec_ind]->get_type();
    return &init_table[type].name[0];
}
ObjectType Grid::get_plant_type(){
    assert(is_planted());
    return plant->get_type();
}
ObjectType Grid::get_zombie_type(int vec_ind){
    assert(zombies[vec_ind]!=NULL);
    return zombies[vec_ind]->get_type();
}