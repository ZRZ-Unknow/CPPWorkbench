#include "../include/game.h"
#include "../include/plant.h"
#include "../include/zombie.h"
#include "../include/input.h"


Game::Game(){
    score = total_sun = counter = 0;
    cursor_x = cursor_y = 0;
    shopping_mode = game_lose = false;
    show_cursor = true;
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
    init_pair(WHITE_BLACK, COLOR_WHITE, COLOR_BLACK);
    init_pair(GREEN_BLACK, COLOR_GREEN, COLOR_BLACK);
    init_pair(YELLOW_BLACK, COLOR_YELLOW, COLOR_BLACK);
    init_pair(MAGENTA_BLACK, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(CYAN_BLACK, COLOR_CYAN, COLOR_BLACK);
    init_pair(RED_BLACK, COLOR_RED, COLOR_BLACK);
    init_pair(BLUE_BLACK, COLOR_BLUE, COLOR_BLACK);
}

void Game::init(){
    store.init();
    courtyard.init();
    init_curse();
    /*if(LINES<40 || COLS<113){
        endwin();
        printf("\33[1;34mMake Sure That The Length And Width Of The Terminal Meet The Requirements By Entering \33[0m");
        printf("\33[1;31mecho $LINES,$COLUMNS\33[0m\33[1;34m.\33[0m\n");
        printf("\33[1;34mOr You Can Simply Maxmize The Terminal.\33[0m\n");
        exit(-1);
    }*/
}

bool Game::is_cursor_available(){
    return show_cursor; 
}

void Game::gen_sun(){
    if(Rand(10000)<500)
        total_sun += 25;
}
void Game::gen_zombie(){
    if(counter >= 300){
        if(Rand(4000)<10 && courtyard.can_add_zomble()){
            int ind = Rand(ZOMBIE_NUM);
            ObjectType zombie_type = ObjectType(ind+PLANT_NUM);
            switch (zombie_type){
                case zombie:{
                    Zombie *z = new Zombie;
                    courtyard.new_zomble(z);
                    break;
                }
                case barricadezombie:{
                    BarricadeZombie *z = new BarricadeZombie;
                    courtyard.new_zomble(z);
                    break;
                }
                case newspaperzombie:{
                    NewspaperZombie *z = new NewspaperZombie;
                    courtyard.new_zomble(z);
                    break;
                }
                case polezombie:{
                    PoleZombie *z = new PoleZombie;
                    courtyard.new_zomble(z);
                    break;
                }
                case clownzombie:{
                    ClownZombie *z = new ClownZombie;
                    courtyard.new_zomble(z);
                    break;
                }
                case slingzombie:{
                    SlingZombie *z = new SlingZombie;
                    courtyard.new_zomble(z);
                    break;
                }
            }
        }
        if(counter>=10000000)    //10000
            counter = 0;
    }
    counter++;
}

void Game::buy_plant(ObjectType plant_type){
    bool mount = plant_type==pumpkin;
    if(!courtyard.can_add_plant(cursor_x, cursor_y, mount)){
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
        case cherrybomb:{
            CherryBomb *p = new CherryBomb;
            courtyard.add_plant(p, cursor_x, cursor_y);
            break;
        }
        case doubleshooter:{
            DoubleShooter *p = new DoubleShooter;
            courtyard.add_plant(p, cursor_x, cursor_y);
            break;
        }
        case iceshooter:{
            IceShooter *p = new IceShooter;
            courtyard.add_plant(p, cursor_x, cursor_y);
            break;
        }
        case wugua:{
            Wugua *p = new Wugua;
            courtyard.add_plant(p, cursor_x, cursor_y);
            break;
        }
        case nutwall:{
            NutWall *p = new NutWall;
            courtyard.add_plant(p, cursor_x, cursor_y);
            break;
        }
        case highnutwall:{
            HighNutWall *p = new HighNutWall;
            courtyard.add_plant(p, cursor_x, cursor_y);
            break;
        }
        case garlic:{
            Garlic *p = new Garlic;
            courtyard.add_plant(p, cursor_x, cursor_y);
            break;
        }
        case pumpkin:{
            Pumpkin *p = new Pumpkin;
            courtyard.add_plant(p, cursor_x, cursor_y, mount);
            break;
        }
    }
}

void Game::this_render(){
    move(0, 0);
    print(BLUE_BLACK, "=====================================================================================");
    print(GREEN_BLACK, "GAME");
    print(BLUE_BLACK, "=======================================================================================\n");
    print(WHITE_BLACK, "Total Sun:");
    print(YELLOW_BLACK, "%d", total_sun);
    print(WHITE_BLACK, " | Score:");
    print(CYAN_BLACK, "%d\n", score);
}

void Game::curse_render(){
    this_render(); 
    store.curse_render();
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
            print(RED_BLACK, "Lose Game!!!Total Score: %d\n", score);
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
            if(!shopping_mode && store.plant_index!=-1){
                ObjectType plant_type = ObjectType(store.plant_index);
                buy_plant(plant_type);
            }
            break;
        } 
        case KEYB:{
            shopping_mode = true;
            show_cursor = false;
            if(store.plant_index == -1)
                store.plant_index = 0;
            break;
        }
        case KEYX:{
            shopping_mode = false;
            show_cursor = true;
            break;
        }
        case KEYLEFT:{
            if(!shopping_mode && is_cursor_available()){
                if(cursor_y > 0) cursor_y -= 1;
            }
            break;
        }
        case KEYRIGHT:{
            if(!shopping_mode && is_cursor_available()){
                if(cursor_y < COURTYARD_COLUMN-2) cursor_y += 1;  //-2代表最后一列不能种
            }
            break;
        }
        case KEYUP:{
            if(shopping_mode){
                if(store.plant_index>0)
                    store.plant_index--;
            }else if(is_cursor_available()){
                if(cursor_x > 0) cursor_x -= 1;
            }
            break;
        }
        case KEYDOWN:{
            if(shopping_mode){
                if(store.plant_index<PLANT_NUM-1)
                    store.plant_index++;
            }else if(is_cursor_available()){
                if(cursor_x < COURTYARD_ROW-1) cursor_x += 1;
            }
            break;
        }
        default:break;
    }
}
