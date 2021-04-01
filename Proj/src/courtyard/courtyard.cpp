#include <vector>
#include "../../include/courtyard.h"
#include "../../include/plant.h"
#include "../../include/zombie.h"
#include "../../include/common.h"
using namespace std;

void CourtYard::init(){}
void CourtYard::update(){}


void CourtYard::render(){
    for(int i=0;i<GRID_XLEN*COURTYARD_COLUMN;i++)
        printf("#");
    printf("\n");
    for(int i=0;i<COURTYARD_ROW;i++){
        for(int p=0;p<GRID_YLEN;p++){
            for(int j=0;j<COURTYARD_COLUMN;j++){
                if(p%2 == 0){
                    if(p == (GRID_YLEN/2) && yard[i][j].is_planted()){
                        char *pname = yard[i][j].get_plant_name();
                        printf("# %s", pname);
                        for(int q=0;q<GRID_XLEN-2-strlen(pname)-1;q++) printf(" ");
                        printf("#"); 
                    }
                    else if(p == 0 && yard[i][j].has_zombie()){
                        char *pname = yard[i][j].get_zombie_name();
                        printf("# %s", pname);
                        for(int q=0;q<GRID_XLEN-2-strlen(pname)-1;q++) printf(" ");
                        printf("#"); 
                    }
                    else{
                        printf("#");
                        for(int q=0;q<GRID_XLEN-2;q++) printf(" ");
                        printf("#");
                    }
                }
                else{
                    for(int q=0;q<GRID_XLEN;q++) printf(" ");
                }
            }
            printf("\n");
        }
        for(int i=0;i<GRID_XLEN*COURTYARD_COLUMN;i++)
        printf("#");
        printf("\n");
    }
}

void CourtYard::render(int cursor_x, int cursor_y){
    for(int i=0;i<GRID_XLEN*COURTYARD_COLUMN;i++)
        printf("#");
    printf("\n");
    for(int i=0;i<COURTYARD_ROW;i++){
        for(int p=0;p<GRID_YLEN;p++){
            for(int j=0;j<COURTYARD_COLUMN;j++){
                if(p%2 == 0){
                    if(p == (GRID_YLEN/2) && yard[i][j].is_planted()){
                        char *pname = yard[i][j].get_plant_name();
                        printf("# %s", pname);
                        for(int q=0;q<GRID_XLEN-2-strlen(pname)-1;q++) printf(" ");
                        printf("#"); 
                    }
                    else if(p == 0 && yard[i][j].has_zombie()){
                        char *pname = yard[i][j].get_zombie_name();
                        printf("# %s", pname);
                        for(int q=0;q<GRID_XLEN-2-strlen(pname)-1;q++) printf(" ");
                        printf("#"); 
                    }
                    else{
                        printf("#");
                        for(int q=0;q<GRID_XLEN-2;q++) printf(" ");
                        printf("#");
                    }
                }
                else{
                    if(cursor_x == i && cursor_y == j){
                        for(int q=0;q<GRID_XLEN;q++) 
                            printf("*");
                    }else{
                        for(int q=0;q<GRID_XLEN;q++) 
                            printf(" ");
                    }
                }
            }
            printf("\n");
        }
        for(int i=0;i<GRID_XLEN*COURTYARD_COLUMN;i++)
        printf("#");
        printf("\n");
    }
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