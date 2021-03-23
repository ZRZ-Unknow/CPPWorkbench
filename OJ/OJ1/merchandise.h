#pragma once


class Merchandise{
private:
    int price;
    const char *name;
public:
    Merchandise(const char *name, int price){
        this->price = price;
        this->name = name;
    }
    const char *GetMerchandiseName(){
        return name;
    }
    int GetMerchandisePrice(){
        return price;
    }
};