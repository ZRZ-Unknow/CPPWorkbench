#pragma once
#include "iostream"
#include <string.h>
using namespace std;

class Mask{
    string name;
    int price;
    int number;
public:
    Mask(const string& name, int price, int number){
        this->name = name;
        this->price = price;
        this->number = number;
    }
    string GetName(){
        return name;
    }
    int GetPrice(){
        return price;
    }
    int GetNumber(){
        return number;
    }
    int GetCost(){
        return price*number;
    }
    int GetBound(){
        return 99999999;
    }
    void AddNumber(int added){
        number += added;
    }
    
};