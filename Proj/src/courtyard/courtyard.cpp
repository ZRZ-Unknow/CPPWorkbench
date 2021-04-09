#include <vector>
#include <curses.h>
#include <unistd.h>
#include "../../include/courtyard.h"
#include "../../include/plant.h"
#include "../../include/zombie.h"
#include "../../include/common.h"
using namespace std;

void CourtYard::init(){}

bool has_bullet_in_pos(vector<BulletStruct> &all_bullets, int coord_x, int coord_y, int dy){
    for(int i=0;i<all_bullets.size();i++){
        if(all_bullets[i].bullet->is_dead() || all_bullets[i].bullet->beyond_boundary()){
            continue;
        }
        if(all_bullets[i].bullet->equal_position_withdy(coord_x, coord_y, dy)){
            return true;
        }
    }
    return false;
}

void CourtYard::curse_render(WINDOW *win, int cursor_x, int cursor_y, bool show_cursor, vector<BulletStruct> &all_bullets){
    print(9, "==============================================");
    print(1, "YARD");
    print(9, "================================================\n");
    int begin_y, begin_x;
    getyx(win, begin_y, begin_x);
    for(int i=0;i<GRID_YLEN*COURTYARD_COLUMN;i++)
        printw("#");
    printw("\n");
    for(int i=0;i<COURTYARD_ROW;i++){
        for(int p=0;p<GRID_XLEN;p++){
            for(int j=0;j<COURTYARD_COLUMN;j++){
                if(p%2 == 0){
                    if(p == (GRID_XLEN/2) && yard[i][j].is_planted()){
                        char *pname = yard[i][j].get_plant_name();
                        printw("# ");
                        int color_pair_type = init_table[yard[i][j].get_plant_type()].color_pair;
                        print(color_pair_type, "%s", pname);
                        for(int q=0;q<GRID_YLEN-2-strlen(pname)-1;q++) printw(" ");
                        printw("#"); 
                    }else if(p == (GRID_XLEN/2) && yard[i][j].has_zombie()){
                        char *pname = yard[i][j].get_zombie_name();
                        printw("# ");
                        int color_pair_type = init_table[yard[i][j].get_zombie_type()].color_pair;
                        print(color_pair_type, "%s", pname);
                        for(int q=0;q<GRID_YLEN-2-strlen(pname)-1;q++) printw(" ");
                        printw("#"); 
                    }else if(p == GRID_XLEN-1){
                        for(int t=0;t<GRID_YLEN;t++){
                            if(t==0 || t==GRID_YLEN-1) printw("#");
                            else printw(" ");
                        }
                    }else{
                        printw("#");
                        for(int q=0;q<GRID_YLEN-2;q++) printw(" ");
                        printw("#");
                    }
                }
                else{
                    if(show_cursor && cursor_x == i && cursor_y == j){
                        for(int q=0;q<GRID_YLEN;q++){
                            print(7, "*");
                        }
                    }else{
                        for(int q=0;q<GRID_YLEN;q++) 
                            printw(" ");
                    }
                }
            }
            printw("\n");
        }
        for(int i=0;i<GRID_YLEN*COURTYARD_COLUMN;i++)
            printw("#");
        printw("\n");
    }
    int last_y, last_x;
    getyx(win, last_y, last_x);
    for(int i=0;i<all_bullets.size();i++){
        if(all_bullets[i].bullet->is_dead() || all_bullets[i].bullet->beyond_boundary()){
            continue;
        }
        int x = all_bullets[i].bullet->get_coord_x();
        int y = all_bullets[i].bullet->get_coord_y()*GRID_YLEN + all_bullets[i].bullet->get_dy();
        move(begin_y + 2*x*(GRID_XLEN/2+1) + GRID_XLEN/2 + 1, y);
        int color_pair_type = init_table[all_bullets[i].bullet->get_type()].color_pair;
        print(color_pair_type, "+");
    }
    move(last_y, last_x);
}

void CourtYard::new_zomble(LivingObject *zom){
    vector<int> tmp;
    for(int i=0;i<COURTYARD_ROW;i++){
        if(!yard[i][COURTYARD_COLUMN-1].has_zombie()){
            tmp.push_back(i); 
        }
    }
    int index = tmp[Rand(tmp.size())];
    yard[index][COURTYARD_COLUMN-1].set_zombie(zom);
}

void CourtYard::check_status(vector<BulletStruct> &all_bullets, int &score){
    for(int i=0;i<COURTYARD_ROW;i++){
        for(int j=0;j<COURTYARD_COLUMN;j++){
            if(yard[i][j].is_planted()){
                if(yard[i][j].plant->is_dead()){
                    yard[i][j].free_plant();
                }
            }
            if(yard[i][j].has_zombie()){
                if(yard[i][j].zombie->is_dead()){
                    score += yard[i][j].zombie->get_kill_score();
                    yard[i][j].free_zombie();
                }
            }
        }
    }
    for(int i=0;i<all_bullets.size();i++){
        if(all_bullets[i].bullet->is_dead() || all_bullets[i].bullet->beyond_boundary()){
            delete all_bullets[i].bullet;
            all_bullets.erase(all_bullets.begin()+i);
        }
    }
}

int encounter_bullet(vector<BulletStruct> &all_bullets, int x, int y){
    for(int i=0;i<all_bullets.size();i++){
        if(!all_bullets[i].bullet->is_dead() && all_bullets[i].bullet->equal_position(x, y)){
            return i;
        }
    }
    return -1;
}

void CourtYard::update(vector<BulletStruct> &all_bullets, bool &game_lose, int &total_sun){
    //process CourtYard
    for(int i=0;i<COURTYARD_ROW;i++){
        for(int j=0;j<COURTYARD_COLUMN;j++){
            if(yard[i][j].is_planted()){
                if(yard[i][j].plant->get_type() == sunflower){
                    if(yard[i][j].plant->can_act()){
                        SunFlower *tmp = (SunFlower*)yard[i][j].plant;
                        total_sun += tmp->gen_sun();
                    }
                }else if(yard[i][j].plant->get_type() == peashooter){
                    if(yard[i][j].plant->can_act()){
                        BulletStruct bs;
                        bs.bullet = new Bullet;
                        assert(j+1<COURTYARD_COLUMN);
                        bs.bullet->set_coord(i, j);
                        bs.bullet->set_dxy(0, GRID_YLEN-2);  //-2是因为后面有更新bullet位置
                        all_bullets.push_back(bs);
                    }
                }
                yard[i][j].plant->increase_counter();
            }
            if(yard[i][j].has_zombie() && encounter_bullet(all_bullets, i, j)!=-1){
                int bullet_index = encounter_bullet(all_bullets, i, j);
                yard[i][j].zombie->attacked(all_bullets[bullet_index].bullet->attack());
                all_bullets[bullet_index].bullet->make_dead();
            }
            if(j>0 && yard[i][j-1].is_planted() && yard[i][j].has_zombie()){
            //if(yard[i][j].is_planted() && yard[i][j].has_zombie()){
                if(yard[i][j].zombie->can_act())
                    yard[i][j-1].plant->attacked(yard[i][j].zombie->attack());
                yard[i][j].zombie->increase_counter();
            }else if(yard[i][j].has_zombie()){
                if(j==0){
                    if(yard[i][j].zombie->can_act()){
                        game_lose = true;
                    }else{
                        yard[i][j].zombie->increase_counter();
                    }
                }else{
                    if(yard[i][j].zombie->can_act()){
                        if(!yard[i][j-1].has_zombie()){
                            //前进
                            yard[i][j-1].set_zombie(yard[i][j].zombie);
                            yard[i][j].del_zombie();
                            yard[i][j-1].zombie->increase_counter();
                        }else{
                            yard[i][j].zombie->increase_counter();
                        }
                    }else{
                        yard[i][j].zombie->increase_counter();
                    }
                }
            }
        }
    }
    //Process Bullets, advance
    for(int i=0;i<all_bullets.size();i++){
        if(!all_bullets[i].bullet->is_dead()){
            if(all_bullets[i].bullet->can_act()){
                all_bullets[i].bullet->advance(); 
            }
            all_bullets[i].bullet->increase_counter();
        }
    }
}