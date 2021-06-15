#pragma once
#include "Polynomial.h"
#include<iostream>

struct Item {// 多项式的单个项数据结构
    int coef;
    int power;
    Item() {}
    Item(int a, int b) { coef = a; power = b; }
};


class ArrayPoly: public Polynomial {
private:
    Item* item_array;
    int max_size, size;
public:
    ArrayPoly(){
        max_size = 10;
	size = 0;
	item_array = new Item[max_size];
    }
    ArrayPoly(ArrayPoly const& a){
        max_size = a.max_size;
	size = a.size;
	item_array = new Item[max_size];
	for(int i=0;i<size;i++){
	    item_array[i].coef = a.item_array[i].coef;
	    item_array[i].power = a.item_array[i].power;
	}
    }
    ~ArrayPoly(){
        delete []item_array;
	item_array = NULL;
    }
    ArrayPoly& operator = (const ArrayPoly& p){
	if(item_array){
	    delete []item_array;
	    item_array = NULL;
	}
        max_size = p.max_size;
	size = p.size;
	item_array = new Item[max_size];
	for(int i=0;i<size;i++){
	    item_array[i].coef = p.item_array[i].coef;
	    item_array[i].power = p.item_array[i].power;
	}
	return *this;
    }
    void addTerm(int coef, int power){
        for(int i=0;i<size;i++){
	    if(item_array[i].power == power){
		item_array[i].coef += coef;
		if(item_array[i].coef == 0){
		    for(int j=i+1;j<size;j++){
		        item_array[j-1].coef = item_array[j].coef;
			item_array[j-1].power = item_array[j].power;
		    }   
		    size--;
		}
		return;
	    }
	}
	if(size == max_size){
	    //new
	    max_size *= 2;
	    Item *tmp = new Item[max_size];
	    for(int i=0;i<size;i++){
		tmp[i].coef = item_array[i].coef;
		tmp[i].power = item_array[i].power;
	    }
	    delete []item_array;
	    item_array = tmp;
	    tmp = NULL;
	}
	item_array[size].coef = coef;
	item_array[size].power = power;
	size++;
    }
    void setIthCoe(int i, int coef){
	item_array[i].coef = coef;
    }
    void setIthPow(int i,int power){
	item_array[i].power = power;
    }
    int getIthCoe(int i){
	return item_array[i].coef;
    }
    int getIthPow(int i){
	return item_array[i].power;
    }
    int getSize(){
	return size;
    }
};
