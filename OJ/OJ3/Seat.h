#pragma once
#include "iostream"
#include "math.h"
using namespace std;

class Seat
{
protected:
    int row, col;
public:
    Seat(){}
    Seat(int row, int col){
        this->row = row;
        this->col = col;
    }
    int GetRow(){
        return row;
    }
    int GetCol(){
        return col;
    }
    bool operator>(const Seat &b){
        if(row>b.row) return true;
        return false;
    }
    bool operator==(const Seat &b){
        if(row==b.row) return true;
        return false;
    }
    int operator-(const Seat &b){
        if(row==b.row){
            return abs(col - b.col);
        }
        return -1;
    }
};

class RegularSeat:public Seat{
    int price;
public:
    RegularSeat(int row, int col){
        this->row = row;
        this->col = col;
        price = 100;
    }
    int Price(){
        return price;
    }
};


class VIPSeat:public Seat{
    int price;
public:
    VIPSeat(int row, int col){
        this->row = row;
        this->col = col;
        price = 500;
    }
    int Price(){
        return price;
    }
};

