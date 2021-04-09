#pragma once
#include "common.h"
#include "bullet.h"
using namespace std;

class Grid{
    int coord_x, coord_y;
    LivingObject *plant, *zombie;
public:
    Grid();
    void set_coord(int x, int y);
    bool is_planted() const;
    bool has_zombie() const;
    void set_plant(LivingObject *plant);
    void del_plant();
    void free_plant();
    void set_zombie(LivingObject *zombie);
    void del_zombie();
    void free_zombie();
    char *get_plant_name();
    char *get_zombie_name();
    ObjectType get_plant_type();
    ObjectType get_zombie_type();
    friend class CourtYard;
};

class CourtYard{
    Grid yard[COURTYARD_ROW][COURTYARD_COLUMN];
public:
    CourtYard();
    void init(){}
    void new_zomble(LivingObject *zom);
    bool can_add_zomble();
    bool can_add_plant(int i, int j);
    bool add_plant(LivingObject *pla, int i, int j);
    bool add_plant(LivingObject *pla);
    void check_status(vector<BulletStruct> &all_bullets, int &score);
    void update(vector<BulletStruct> &all_bullets, bool &game_lose, int &total_sun);
    void curse_render(WINDOW *win, int cursor_x, int cursor_y, bool show_cursor, vector<BulletStruct> &all_bullets);
};