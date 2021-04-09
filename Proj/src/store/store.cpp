#include "../../include/store.h"

Store::Store(){
    for(int i=0;i<PLANT_NUM;i++){
        ObjectType plant_type = ObjectType(i);
        plants[i].set_params(plant_type, init_table[plant_type].sun_cost, init_table[plant_type].cd_time);
    }
}

bool Store::buy(ObjectType type, int &total_sun){
    if(total_sun >= plants[type].sun_cost && plants[type].can_buy()){
        plants[type].buy();
        total_sun -= plants[type].sun_cost;
        return true;
    }
    return false;
}

void Store::update(){
    for(int i=0;i<PLANT_NUM;i++){
        plants[i].cooling();
    }
}

void Store::curse_render(int plant_index){
    print(9, "==============================================");
    print(1, "STORE");
    print(9, "===============================================\n");
    for(int i=0;i<PLANT_NUM;i++){
        if(plant_index == i){
            print(8, "%d.%s:%d, CD Time:%d\n", i+1, plants[i].get_name(), plants[i].sun_cost, plants[i].counter);
        }else{
            print(6, "%d.%s:%d, CD Time:%d\n", i+1, plants[i].get_name(), plants[i].sun_cost, plants[i].counter);
        }
    }
}