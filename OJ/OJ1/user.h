#include <iostream>
#include <cstring>
#include "merchandise.h"
#include "merchandise_list.h"
#pragma once



class User{
private:
    const char* name;
    MerchandiseList browse_history, buy_history;
public:
    User(const char* user_name){
        name = user_name;
    }
    void BrowseMerchandise(Merchandise* merchandise){
        browse_history.AddRecord(merchandise, 1);
    }
    MerchandiseList* GetBrowseHistory(){
        return &browse_history;
    }
    void BuyMerchandise(Merchandise *merchandise, int number){
        buy_history.AddRecord(merchandise, number);
    }
    MerchandiseList* GetBuyHistory(){
        return &buy_history;
    }

};