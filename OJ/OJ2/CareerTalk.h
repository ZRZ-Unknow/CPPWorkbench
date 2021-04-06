#include <iostream>
#include <vector>
using namespace std;


class CareerTalk{
    const char *name;
    int day;
    int start_time, end_time;
    bool is_open;
    vector<int> scores;
public:
    CareerTalk(const char *company_name, int day, int start_time, int end_time){
        this->name = company_name;
        this->day = day;
        this->start_time = start_time;
        this->end_time = end_time;
    }
    const char *GetName(){
        return name;
    }
    int GetDay(){
        return day;
    }
    int GetStartTime(){
        return start_time;
    }
    int GetEndTime(){
        return end_time;
    }
    void AdjustInfo(int day, int start_time, int end_time){
        this->day = day;
        this->start_time = start_time;
        this->end_time = end_time;
    }
    void OpenAccess(){
        is_open = true;
    }
    void CloseAccess(){
        is_open = false;
    }
    bool IsOpen(){
        return is_open;
    }
    void Comment(int score){
        scores.push_back(score);
    }
    float GetScore(){
        int tmp = 0;
        for(int i=0;i<scores.size();i++){
            tmp += scores[i];
        }
        float res = (float)tmp/scores.size();
        return res;
    }
};