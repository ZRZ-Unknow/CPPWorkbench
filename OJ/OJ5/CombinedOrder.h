#pragma once
#include "Mask.h"
#include "Vaccine.h"
#include <assert.h>
#include <vector>
#include <algorithm>


template<class T>
class CombinedOrder{
public:
    vector<T> orders;
    CombinedOrder(){}
    bool AddOrder(T &order){
        for(int i=0;i<orders.size();i++){
            if(orders[i].GetName() == order.GetName()){
                if(orders[i].GetBound() <  orders[i].GetNumber() + order.GetNumber()){
                    return false;
                }else{
                    orders[i].AddNumber(order.GetNumber());
                    return true;
                }
            }
        }
        if(order.GetBound() < order.GetNumber()){
            return false;
        }
        orders.push_back(order);
        return true;
    }
    int GetTotalCost(){
        int sum = 0;
        for(int i=0;i<orders.size();i++){
            sum += orders[i].GetCost();
        }
        return sum;
    }
    T &operator[](int index){
        return orders[index];
    }
};

template<class T> bool IsLessThan(T t1, T t2){
    if(t1.GetCost() < t2.GetCost())
        return true;
    return false;
}

template<class T> void SortOrder(CombinedOrder<T> &order){
    sort(order.orders.begin(), order.orders.end(), IsLessThan<T>);
}