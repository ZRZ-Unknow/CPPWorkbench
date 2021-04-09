#include "../include/game.h"
#include "../include/plant.h"
#include "../include/zombie.h"
#include "../include/input.h"


Game::Game(){
    score = total_sun = 0;
    plant_index = -1;
    cursor_x = cursor_y = 0;
    shopping_mode = game_lose = show_cursor = false;
}

void Game::init_curse(){
    win = initscr();
    cbreak();
    curs_set(0);  
    keypad(stdscr, true);
    noecho();
    if(!has_colors()){
        endwin();
        fprintf(stderr, "终端不支持颜色显示\n");
        exit(1);
    }
    if(start_color() != OK){
        endwin();
        fprintf(stderr, "无法初始化颜色\n");
        exit(2);
    }
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
    init_pair(5, COLOR_WHITE, COLOR_RED);
    init_pair(6, COLOR_WHITE, COLOR_BLACK);
    init_pair(7, COLOR_CYAN, COLOR_BLACK);
    init_pair(8, COLOR_RED, COLOR_BLACK);
    init_pair(9, COLOR_BLUE, COLOR_BLACK);
}

void Game::init(){
    store.init();
    courtyard.init();
    init_curse();
}

bool Game::is_cursor_available(){
    return show_cursor; 
}

void Game::gen_sun(){
    if(Rand(100)<5)
        total_sun += 25;
}
void Game::gen_zombie(){
    if(Rand(10000)<10 && courtyard.can_add_zomble()){
        Zombie *z = new Zombie;
        courtyard.new_zomble(z);
    }
}

void Game::buy_plant(ObjectType plant_type){
    if(!courtyard.can_add_plant(cursor_x, cursor_y)){
            return;
    }
    if(!store.buy(plant_type, total_sun)){
        return;
    }
    switch(plant_type){
        case sunflower:{
            SunFlower *p = new SunFlower;
            courtyard.add_plant(p, cursor_x, cursor_y);
            break;
        }
        case peashooter:{
            PeaShooter *p = new PeaShooter;
            courtyard.add_plant(p, cursor_x, cursor_y);
            break;
        }
    }
}

void Game::this_render(){
    move(0, 0);
    print(9, "==============================================");
    print(1, "GAME");
    print(9, "================================================\n");
    print(6, "Total Sun:");
    print(2, "%d", total_sun);
    print(6, " | Score:");
    print(7, "%d\n", score);
}

void Game::curse_render(){
    this_render(); 
    store.curse_render(plant_index);
    courtyard.curse_render(win, cursor_x, cursor_y, show_cursor, all_bullets);
    refresh();
};

void Game::loop(){
    //首先check status，检查子弹、僵尸、植物等是否死亡，并更新分数。
    //然后update，僵尸前进，植物产生阳光，植物产生子弹，子弹前进，判断是否吃植物，是否打中僵尸。
    //最后随机产生阳光、新僵尸等。
    courtyard.check_status(all_bullets, score);
    store.update();
    courtyard.update(all_bullets, game_lose, total_sun);
    gen_sun();
    gen_zombie();
}

void Game::wait(){
    while(((curr_time=clock())-last_time)<REFRESH_RATE){}
    last_time = curr_time;
}

void Game::start(){
    int tty_set_flag = tty_set();
    curse_render();
    last_time = curr_time = clock();
    while(true){
        wait();
        curse_render();
        if(game_lose){
            print(8, "Lose Game!!!Total Score: %d\n", score);
            refresh();
            sleep(10);
            endwin();
            printf("Lose Game!!!Total Score: %d\n", score);
            exit(0);
        }
        if(kbhit()){
            char ch = getch();
            if(ch == KEYQ)
                break;
            process_key(ch);
        }
        loop();
    }
}

void Game::process_key(char key){
    switch(key){
        case KEYU: printf("KEY u\n");break;
        case KEYENTER:{
            if(plant_index!=-1 && shopping_mode){
                ObjectType plant_type = ObjectType(plant_index);
                buy_plant(plant_type);
            }
            break;
        } 
        case KEYB:{
            shopping_mode = true;
            show_cursor = true;
            break;
        }
        case KEYX:{
            shopping_mode = false;
            show_cursor = false;
            break;
        }
        case KEY1:case KEY2:case KEY3:case KEY4:{
            plant_index = key-'1';
            break;
        }
        case KEYLEFT:{
            if(is_cursor_available()){
                if(cursor_y > 0) cursor_y -= 1;
            }
            break;
        }
        case KEYRIGHT:{
            if(is_cursor_available()){
                if(cursor_y < COURTYARD_COLUMN-2) cursor_y += 1;  //-2代表最后一列不能种
            }
            break;
        }
        case KEYUP:{
            if(is_cursor_available()){
                if(cursor_x > 0) cursor_x -= 1;
            }
            break;
        }
        case KEYDOWN:{
            if(is_cursor_available()){
                if(cursor_x < COURTYARD_ROW-1) cursor_x += 1;
            }
            break;
        }
        default:break;
    }
}
