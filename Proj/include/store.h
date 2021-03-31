#include "common.h"


class PlantPlate{
    int sun_cost;
    int cd_time;
    ObjectType type;
public:
    PlantPlate(){}
    void set_params(ObjectType type, int sun_cost, int cd_time){
        this->type = type;
        this->sun_cost = sun_cost;
        this->cd_time = cd_time;
    }
    void cooling(){}
    const char* get_name(){
        return &init_table[type].name[0];
    }
    friend class Store; 
};

class Store{
public:
    PlantPlate plants[PLANT_NUM];
public:
    Store(){
        for(int i=0;i<PLANT_NUM;i++){
            ObjectType plant_type = ObjectType(i);
            plants[i].set_params(plant_type, init_table[plant_type].sun_cost, init_table[plant_type].cd_time);
        }
    }
};