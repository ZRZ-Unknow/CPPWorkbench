#pragma once
#include "common.h"
#include "curses.h"

class PlantPlate{
    int sun_cost;
    int cd_time;
    int counter;
    int inner_counter;
    ObjectType type;
public:
    PlantPlate(){}
    void set_params(ObjectType type, int sun_cost, int cd_time);
    void cooling();
    bool can_buy();
    void buy();
    const char* get_name();
    friend class Store; 
};

class Store{
public:
    PlantPlate plants[PLANT_NUM];
public:
    Store();
    void init(){}
    bool buy(ObjectType type, int &total_sun);
    void update();
    void curse_render(int plant_index);
    friend class Game;
};