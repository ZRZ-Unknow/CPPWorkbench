#include <vector>
#include <curses.h>
#include <string.h>
#include "../../include/courtyard.h"
#include "../../include/plant.h"
#include "../../include/zombie.h"
using namespace std;

static bool has_bullet_in_pos(vector<BulletStruct> &all_bullets, int coord_x, int coord_y, int dy){
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

static int encounter_bullet(vector<BulletStruct> &all_bullets, int x, int y){
    for(int i=0;i<all_bullets.size();i++){
        if(!all_bullets[i].bullet->is_dead() && all_bullets[i].bullet->equal_position(x, y)){
            return i;
        }
    }
    return -1;
}

// x为行index，y为列index
static inline bool legal_pos_in_yard(int x, int y){
    return x>=0 && x<COURTYARD_ROW && y>=0 && y<COURTYARD_COLUMN;
}

CourtYard::CourtYard(){
    for(int i=0;i<COURTYARD_ROW;i++){
        for(int j=0;j<COURTYARD_COLUMN;j++){
            yard[i][j].set_coord(i, j);
        }
    }
}

void CourtYard::new_zomble(LivingObject *zom){
    vector<int> tmp;
    for(int i=0;i<COURTYARD_ROW;i++){
        if(yard[i][COURTYARD_COLUMN-1].can_add_zombie()){
            tmp.push_back(i); 
        }
    }
    int index = tmp[Rand(tmp.size())];
    yard[index][COURTYARD_COLUMN-1].set_zombie(zom);
}

bool CourtYard::can_add_zomble(){
    for(int i=0;i<COURTYARD_ROW;i++){
        if(yard[i][COURTYARD_COLUMN-1].can_add_zombie())
            return true;
    }
    return false;
}

bool CourtYard::can_add_plant(int i, int j, int mount){
    return !yard[i][j].is_planted(mount);
}

bool CourtYard::add_plant(LivingObject *pla, int i, int j, int mount){
    assert(can_add_plant(i, j, mount));
    yard[i][j].set_plant(pla, mount);
    return true;
}

bool CourtYard::add_plant(LivingObject *pla, int mount){
    for(int i=0;i<COURTYARD_ROW;i++){
        for(int j=0;j<COURTYARD_COLUMN;j++){
            if(can_add_plant(i, j, mount)){
                add_plant(pla, i, j, mount);
                return true;
            }
        }
    }
    return false;
}

void CourtYard::check_status(vector<BulletStruct> &all_bullets, int &score){
    for(int i=0;i<COURTYARD_ROW;i++){
        for(int j=0;j<COURTYARD_COLUMN;j++){
            if(yard[i][j].is_planted(true)){
                if(yard[i][j].plant_mount->is_dead()){
                    yard[i][j].free_plant(true);
                }
            }
            if(yard[i][j].is_planted()){
                if(yard[i][j].plant->is_dead()){
                    yard[i][j].free_plant();
                }
            }
            if(yard[i][j].has_zombie()){
                for(int p=0;p<yard[i][j].zombies.size();i++){
                    if(yard[i][j].zombies[p]->is_dead()){
                        score += yard[i][j].zombies[p]->get_kill_score();
                        yard[i][j].free_zombie(p);
                    }
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
                }else if(yard[i][j].plant->get_type() == cherrybomb){
                    if(yard[i][j].plant->can_act()){
                        /*if(legal_pos_in_yard(i-1,j) && yard[i-1][j].has_zombie()){
                            yard[i-1][j].zombie->make_dead();
                        } 
                        if(legal_pos_in_yard(i+1,j) && yard[i+1][j].has_zombie()){
                            yard[i+1][j].zombie->make_dead();
                        } 
                        if(legal_pos_in_yard(i,j-1) && yard[i][j-1].has_zombie()){
                            yard[i][j-1].zombie->make_dead();
                        } 
                        if(legal_pos_in_yard(i,j+1) && yard[i][j+1].has_zombie()){
                            yard[i][j+1].zombie->make_dead();
                        } 
                        yard[i][j].plant->make_dead();*/
                    }
                }
                yard[i][j].plant->increase_counter();
            }
            if(yard[i][j].has_zombie() && encounter_bullet(all_bullets, i, j)!=-1){
                int bullet_index = encounter_bullet(all_bullets, i, j);
                yard[i][j].zombies[0]->attacked(all_bullets[bullet_index].bullet->attack());
                all_bullets[bullet_index].bullet->make_dead();
            }
            if(yard[i][j].is_planted() && yard[i][j].has_zombie()){
                for(int p=0;p<yard[i][j].zombies.size();p++){
                    if(yard[i][j].zombies[p]->can_act()){
                        if(yard[i][j].is_planted(true))
                            yard[i][j].plant_mount->attacked(yard[i][j].zombies[p]->attack());
                        else
                            yard[i][j].plant->attacked(yard[i][j].zombies[p]->attack());
                    }
                    yard[i][j].zombies[p]->increase_counter();
                }
            }else if(yard[i][j].has_zombie()){
                if(j==0){
                    for(int p=0;p<yard[i][j].zombies.size();p++){
                        if(yard[i][j].zombies[p]->can_act() && !yard[i][j].zombies[p]->is_dead()){
                            game_lose = true;
                        }else{
                            yard[i][j].zombies[p]->increase_counter();
                        }
                    }
                }else{
                    for(int p=0;p<yard[i][j].zombies.size();){
                        if(yard[i][j].zombies[p]->can_act() && !yard[i][j].zombies[p]->is_dead()){
                            if(yard[i][j-1].can_add_zombie()){
                                //前进
                                yard[i][j].zombies[p]->increase_counter();
                                yard[i][j-1].set_zombie(yard[i][j].zombies[p]);
                                yard[i][j].del_zombie(p);
                            }else{
                                yard[i][j].zombies[p]->increase_counter();
                            }
                        }else{
                            yard[i][j].zombies[p]->increase_counter();
                            p++;
                        }
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

void CourtYard::curse_render(WINDOW *win, int cursor_x, int cursor_y, bool show_cursor, vector<BulletStruct> &all_bullets){
    print(BLUE_BLACK, "=====================================================");
    print(GREEN_BLACK, "YARD");
    print(BLUE_BLACK, "=======================================================\n");
    int begin_y, begin_x;
    getyx(win, begin_y, begin_x);
    for(int i=0;i<GRID_YLEN*COURTYARD_COLUMN;i++)
        printw("#");
    printw("\n");
    for(int i=0;i<COURTYARD_ROW;i++){
        for(int p=0;p<GRID_XLEN;p++){
            for(int j=0;j<COURTYARD_COLUMN;j++){
                bool zombie_on_curse = false;
                if(p == (GRID_XLEN/2)){
                    if(yard[i][j].is_planted()){
                        char *pname = yard[i][j].get_plant_name();
                        printw("# ");
                        int color_pair_type = init_table[yard[i][j].get_plant_type()].color_pair;
                        print(color_pair_type, "%s", pname);
                        if(yard[i][j].is_planted(true)){
                            print(color_pair_type, "|");
                            for(int q=0;q<GRID_YLEN-2-strlen(pname)-2;q++) printw(" ");
                        }else{
                            for(int q=0;q<GRID_YLEN-2-strlen(pname)-1;q++) printw(" ");
                        }
                        printw("#"); 
                    }else{
                        printw("#");
                        for(int q=0;q<GRID_YLEN-2;q++) printw(" ");
                        printw("#");
                    }
                }else if(p == (GRID_XLEN/2-1) || p == (GRID_XLEN/2+1)){
                    if(show_cursor && cursor_x == i && cursor_y == j){
                        for(int q=0;q<GRID_YLEN;q++){
                            print(CYAN_BLACK, "*");
                        }
                    }else{
                        for(int q=0;q<GRID_YLEN;q++) 
                            printw(" ");
                    }
                }else if(yard[i][j].has_zombie(p)){
                    char *pname = yard[i][j].get_zombie_name(p);
                    printw("# ");
                    int color_pair_type = init_table[yard[i][j].get_zombie_type(p)].color_pair;
                    print(color_pair_type, "%s", pname);
                    for(int q=0;q<GRID_YLEN-2-strlen(pname)-1;q++) printw(" ");
                    printw("#"); 
                }
                else{
                    printw("#");
                    for(int q=0;q<GRID_YLEN-2;q++) printw(" ");
                    printw("#");
                }
            }
            printw("\n");
        }
        for(int q=0;q<GRID_YLEN*COURTYARD_COLUMN;q++)
            printw("#");
        printw("\n");
    }
    int last_y, last_x;
    getyx(win, last_y, last_x);
    for(int i=0;i<all_bullets.size();i++){
        if(all_bullets[i].bullet->is_dead() || all_bullets[i].bullet->beyond_boundary()) continue;
        int x = all_bullets[i].bullet->get_coord_x();
        int y = all_bullets[i].bullet->get_coord_y()*GRID_YLEN + all_bullets[i].bullet->get_dy();
        move(begin_y + 2*x*(GRID_XLEN/2+1) + GRID_XLEN/2 + 1, y);
        int color_pair_type = init_table[all_bullets[i].bullet->get_type()].color_pair;
        print(color_pair_type, "+");
    }
    move(last_y, last_x);
}


