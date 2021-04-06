#include "CareerTalk.h"
#pragma once
using namespace std;


struct Talk{
    CareerTalk *talk;
    Talk *next;
};


class ReservationTable{
private:
    Talk *head;
    bool IntervalOverlap(int start1, int end1, int start2, int end2){
        if(end1 <= start2 || end2 <= start1)
            return false;
        return true;
    }
    bool IsConflict(CareerTalk *talk){
        for(Talk *p=head;p!=NULL;p=p->next){
            if(p->talk->GetDay()==talk->GetDay() && IntervalOverlap(p->talk->GetStartTime(), p->talk->GetEndTime(),
                                                                    talk->GetStartTime(), talk->GetEndTime())){
                return true;
            }
        }
        return false;
    }
    void AddList(CareerTalk *talk){
        Talk *tmp = new Talk;
        tmp->talk = talk;
        tmp->next = NULL;
        if(!head)
            head = tmp;
        else{
            Talk *p = head;
            while (p->next!=NULL)
                p = p->next;
            p->next = tmp;
        }
    }
public:
    ReservationTable(){
        head = NULL;
    }
    bool AddTalk(CareerTalk *career_talk){
        if(!career_talk->IsOpen())
            return false;
        if(IsConflict(career_talk))
            return false;
        AddList(career_talk);
        return true; 
    }
    bool CancelTalk(CareerTalk *career_talk){
        Talk *p, *pprev;
        for(p=head, pprev=head;p!=NULL;p=p->next){
            if(p->talk == career_talk){
                if(p==head){
                    head = head->next;
                    delete p;
                }else{
                    Talk *tmp = p->next;
                    pprev->next = tmp;
                    delete p;
                }
                return true;
            }
            if(p!=head)
                pprev = pprev->next;
        }
        return false;
    }
    CareerTalk *QueryTalk(int day, int time){
        for(Talk *p=head; p!=NULL; p=p->next){
            if(p->talk->GetDay() == day){
                if(p->talk->GetStartTime() <= time && p->talk->GetEndTime() >= time+1){
                    return p->talk;
                }
            }
        }
        return NULL;
    }
    int TalksInADay(int day){
        int res = 0;
        for(Talk *p=head;p!=NULL;p=p->next){
            if(day == p->talk->GetDay())
                res++;
        }
        return res;
    }
    bool AdjustTalk(CareerTalk *career_talk){
        bool flag = false;
        for(Talk *p=head;p!=NULL;p=p->next){
            if(p->talk == career_talk){
                CancelTalk(p->talk);
                flag = true;
                break;
            }
        }
        if(!flag) return false;
        if(IsConflict(career_talk))
            return false;
        AddList(career_talk);
        return true;
    }
};