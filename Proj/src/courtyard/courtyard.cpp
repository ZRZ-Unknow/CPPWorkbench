#include "../../include/courtyard.h"
#include "../../include/plant.h"
#include "../../include/zombie.h"
#include "../../include/common.h"

void CourtYard::init(){
    /*SunFlower *a = new SunFlower();
    yard[0][3].set_plant(a);
    PeaShooter *b = new PeaShooter();
    yard[2][2].set_plant(b);
    Zombie *c = new Zombie();
    yard[0][6].set_zombie(c);*/
}

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