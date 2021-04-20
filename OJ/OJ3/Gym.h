#pragma once
#include "Seat.h"
#include <vector>


struct RS{
    RegularSeat *seat;
    bool is_buy;
};
struct VS{
    VIPSeat *seat;
    bool is_buy;
};

class Gym{
protected:
    int regular_seat_num, vip_seat_num;
    int rs_num, vs_num;
    vector<RS> rs_seats;
    vector<VS> vs_seats;
public:
    Gym(int RegularSeatNum, int VIPSeatNum){
        regular_seat_num = RegularSeatNum;
        vip_seat_num = VIPSeatNum;
        rs_num = vs_num = 0;
    } 
    bool AddSeat(Seat *seat, int type){
        if(type==0){
            if(rs_num >= regular_seat_num) return false;
            for(int i=0;i<rs_seats.size();i++){
                if(rs_seats[i].seat->GetCol() == seat->GetCol() && rs_seats[i].seat->GetRow() == seat->GetRow()){
                    return false;
                }
            }
            rs_num++;
            RS tmp;
            tmp.seat = (RegularSeat*) seat;
            tmp.is_buy = false;
            rs_seats.push_back(tmp);
            return true;
        }else if(type==1){
            if(vs_num >= vip_seat_num) return false;
            for(int i=0;i<vs_seats.size();i++){
                if(vs_seats[i].seat->GetCol() == seat->GetCol() && vs_seats[i].seat->GetRow() == seat->GetRow()){
                    return false;
                }
            }
            vs_num++;
            VS tmp;
            tmp.seat = (VIPSeat*) seat;
            tmp.is_buy = false;
            vs_seats.push_back(tmp);
            return true;
        }
    }
    bool DeleteSeat(Seat *seat, int type){
        if(type==0){
            for(int i=0;i<rs_seats.size();i++){
                if(rs_seats[i].seat->GetCol() == seat->GetCol() && rs_seats[i].seat->GetRow() == seat->GetRow()){
                    rs_seats.erase(rs_seats.begin()+i);
                    return true;
                }
            }
            return false;
        }else if(type==1){
            for(int i=0;i<vs_seats.size();i++){
                if(vs_seats[i].seat->GetCol() == seat->GetCol() && vs_seats[i].seat->GetRow() == seat->GetRow()){
                    vs_seats.erase(vs_seats.begin()+i);
                    return true;
                }
            }
            return false;
        }
    }
    Seat *Buy(int row, int col){
        for(int i=0;i<rs_seats.size();i++){
            if(rs_seats[i].seat->GetCol() == col && rs_seats[i].seat->GetRow() == row){
                if(!rs_seats[i].is_buy){
                    rs_seats[i].is_buy = true;
                    return rs_seats[i].seat;
                }
            }
        }
        for(int i=0;i<vs_seats.size();i++){
            if(vs_seats[i].seat->GetCol() == col && vs_seats[i].seat->GetRow() == row){
                if(!vs_seats[i].is_buy){
                    vs_seats[i].is_buy = true;
                    return vs_seats[i].seat;
                }
            }
        }
        return NULL;
    }
    Seat *Refund(int row, int col){
        for(int i=0;i<rs_seats.size();i++){
            if(rs_seats[i].seat->GetCol() == col && rs_seats[i].seat->GetRow() == row){
                if(rs_seats[i].is_buy){
                    rs_seats[i].is_buy = false;
                    return rs_seats[i].seat;
                }
            }
        }
        for(int i=0;i<vs_seats.size();i++){
            if(vs_seats[i].seat->GetCol() == col && vs_seats[i].seat->GetRow() == row){
                if(vs_seats[i].is_buy){
                    vs_seats[i].is_buy = false;
                    return vs_seats[i].seat;
                }
            }
        }
        return NULL;
    }
    int Income(){
        int income = 0;
        for(int i=0;i<rs_seats.size();i++){
            if(rs_seats[i].is_buy){
                income += rs_seats[i].seat->Price();
            }
        }
        for(int i=0;i<vs_seats.size();i++){
            if(vs_seats[i].is_buy){
                income += vs_seats[i].seat->Price();
            }
        }
        return income;
    }
   
   
};