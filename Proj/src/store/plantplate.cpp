#include "../../include/store.h"


void PlantPlate::set_params(ObjectType type, int sun_cost, int cd_time){
    this->type = type;
    this->sun_cost = sun_cost;
    this->cd_time = cd_time;
    this->counter = 0;
    this->inner_counter = 0;
}

void PlantPlate::cooling(){
    if(counter > 0){
        inner_counter = (inner_counter+1) % GAME_CLICK;
        if(inner_counter == 0)
            counter--;
    }
}

bool PlantPlate::can_buy(){
    return counter==0;
}

void PlantPlate::buy(){
    assert(can_buy());
    counter = cd_time;
    inner_counter = 0;
}

const char* PlantPlate::get_name(){
    return &init_table[type].name[0];
}