#pragma once
#include <vector>
#include "common.h"
#include "bullet.h"
using namespace std;

class Grid{
    int coord_x, coord_y;
    int free_space;
    bool space_free[GRID_XLEN-1];
    LivingObject *plant, *plant_mount;
    vector<LivingObject*> zombies;
public:
    Grid();
    void set_coord(int x, int y);
    bool is_planted(bool mount=false) const;
    bool has_zombie() const;
    bool has_zombie(int vec_ind) const;
    bool can_add_zombie() const;
    void set_plant(LivingObject *plant, bool mount=false);
    void del_plant(bool mount=false);
    void free_plant(bool mount=false);
    void set_zombie(LivingObject *zombie);
    void del_zombie(int vec_ind);
    void free_zombie(int vec_ind);
    char *get_plant_name();
    char *get_zombie_name(int vec_ind);
    ObjectType get_plant_type();
    ObjectType get_zombie_type(int vec_ind);
    friend class CourtYard;
};

class CourtYard{
    Grid yard[COURTYARD_ROW][COURTYARD_COLUMN];
public:
    CourtYard();
    void init(){}
    void new_zomble(LivingObject *zom);
    bool can_add_zomble();
    bool can_add_plant(int i, int j, int mount=false);
    bool add_plant(LivingObject *pla, int i, int j, int mount=false);
    bool add_plant(LivingObject *pla, int mount=false);
    void check_status(vector<BulletStruct> &all_bullets, int &score);
    void update(vector<BulletStruct> &all_bullets, bool &game_lose, int &total_sun);
    void curse_render(WINDOW *win, int cursor_x, int cursor_y, bool show_cursor, vector<BulletStruct> &all_bullets);
};