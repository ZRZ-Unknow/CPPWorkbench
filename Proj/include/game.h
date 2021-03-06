#pragma once
#include <vector>
#include <time.h>
#include <curses.h>
#include "common.h"
#include "store.h"
#include "courtyard.h"
#include "bullet.h"



class Game{
    int score;
    int total_sun;
    int counter;
    int cursor_x, cursor_y;
    bool shopping_mode;
    bool game_lose;
    bool show_cursor;
    Store store;
    CourtYard courtyard;
    vector<BulletStruct> all_bullets;
    vector<BallStruct> all_balls;
    clock_t last_time, curr_time;
    WINDOW *win;
public:
    Game();
    void init_curse();
    void init();
    bool is_cursor_available();
    void gen_sun();
    void gen_zombie();
    void buy_plant(ObjectType plant_type);
    void this_render();
    void curse_render();
    void loop();
    void wait();
    void start();
    void process_key(char key);
};