#pragma once
#include "common.h"


class PlantPlate{
    int sun_cost;
    int cd_time;
    int counter;
    ObjectType type;
public:
    PlantPlate(){}
    void set_params(ObjectType type, int sun_cost, int cd_time){
        this->type = type;
        this->sun_cost = sun_cost;
        this->cd_time = cd_time;
        this->counter = 0;
    }
    void cooling(){
        if(counter>0) counter--;
    }
    bool can_buy(){
        return counter==0;
    }
    void buy(){
        assert(can_buy());
        counter = cd_time;
    }
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
    void init(){};
    bool buy(ObjectType type, int &total_sun){
        if(total_sun >= plants[type].sun_cost && plants[type].can_buy() ){
            plants[type].buy();
            total_sun -= plants[type].sun_cost;
            return true;
        }
        return false;
    }
    void update(){
        for(int i=0;i<PLANT_NUM;i++){
            plants[i].cooling();
        }
    }
    void render(int plant_index){
        printf("==============================================STORE===============================================\n");
        for(int i=0;i<PLANT_NUM;i++){
            if(plant_index == i){
                printf("%d.%s*:%d, CD Time:%d\n", i+1, plants[i].get_name(), plants[i].sun_cost, plants[i].counter);
            }else{
                printf("%d.%s:%d, CD Time:%d\n", i+1, plants[i].get_name(), plants[i].sun_cost, plants[i].counter);
            }
        }
        printf("==============================================YARD================================================\n");
    }
    friend class Game;
};