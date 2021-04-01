#include <iostream>
#include <stdio.h>
#include "../include/plant.h"
#include "../include/zombie.h"
#include "../include/courtyard.h"
#include "../include/store.h"
#include "../include/game.h"
using namespace std;


int main(){
    Game g;
    g.init();
    g.start();
    return 0;
}