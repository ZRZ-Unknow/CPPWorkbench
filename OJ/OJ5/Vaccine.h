#pragma once
#include "iostream"
#include <string.h>
using namespace std;

class Vaccine{
    string name;
    int price;
    int number;
    int bound;
public:
    Vaccine(const string& name, int price, int number, int bound){
        this->name = name;
        this->price = price;
        this->number = number;
        this->bound = bound;
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
        return bound;
    }
    void AddNumber(int added){
        number += added;
    }
};