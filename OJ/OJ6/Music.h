#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;


class Music{
    string name, singer, date, nation;
    int count;
public:
    Music(string name, string singer, int count, string date, string nation){
        this->name = name;
        this->singer = singer;
        this->count = count;
        this->date = date;
        this->nation = nation;
    }
    string getName(){
        return name;
    }
    string getSinger(){
        return singer;
    }
    string getDate(){
        return date;
    }
    string getNation(){
        return nation;
    }
    int getCount(){
        return count;
    }
    friend ostream& operator << (ostream& out, const Music& music){
        out<<music.name<<","<<music.singer<<","<<music.count<<","<<music.date<<","<<music.nation;
        return out;
    }
    bool dateLessthan(const Music &m){
        int year1 = stoi(date.substr(0, 4));
        int month1 = stoi(date.substr(5,2));
        int day1 = stoi(date.substr(8,2));
        string tmp = m.date;
        int year2 = stoi(tmp.substr(0, 4));
        int month2 = stoi(tmp.substr(5,2));
        int day2 = stoi(tmp.substr(8,2));
        if(year1<year2){
            return true;
        }else if(year1==year2){
            if(month1<month2){
                return true;
            }else if(month1==month2){
                if(day1<day2){
                    return true;
                }else{
                    return false;
                }
            }else{
                return false;
            }
        }else{
            return false;
        }
    }
};