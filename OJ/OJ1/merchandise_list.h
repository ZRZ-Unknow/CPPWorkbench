#include <iostream>
#include <cstring>
#include "merchandise.h"
#pragma once



struct MerchandiseL{
    Merchandise *m;
    int value;
    MerchandiseL *next;
};

class MerchandiseList{
private:
    MerchandiseL *head;
public:
    MerchandiseList(){
        head = NULL;
    };
    void AddRecord(Merchandise *merchandise, int value){
        if(head==NULL){
            struct MerchandiseL *tmp = Build(merchandise, value);
            head = tmp;
            return;
        } 
        struct MerchandiseL *tmp = IsRecorded(merchandise);
        if(tmp != NULL){
            tmp->value += value;
        }
        else{
            tmp = Build(merchandise, value); 
            tmp->next = head;
            head = tmp;
        }
    }
    void ModifyRecord(Merchandise *merchandise, int new_value){
        struct MerchandiseL *tmp = IsRecorded(merchandise);
        if(tmp!=NULL){
            tmp->value = new_value;
        }
    }
    int FindRecord(Merchandise *merchandise){
        struct MerchandiseL *tmp = IsRecorded(merchandise);
        if(tmp!=NULL) return tmp->value;
        else return -1;
    }
    bool DeleteRecord(Merchandise* merchandise){
        struct MerchandiseL *p, *pp;
        for(p=head,pp=head;p!=NULL;p=p->next){
            if(strcmp(p->m->GetMerchandiseName(), merchandise->GetMerchandiseName()) == 0){
                if(p==head){
                    head = head->next;
                    delete p;
                }else{
                    pp->next = p->next;
                    delete p;
                }
                return true;
            }
            if(p!=head){
                pp = pp->next;
            }
        }
        return false;
    }
    struct MerchandiseL *IsRecorded(Merchandise *merchandise){
        for(struct MerchandiseL *p=head;p!=NULL;p=p->next){
            if(strcmp(p->m->GetMerchandiseName(), merchandise->GetMerchandiseName()) == 0)
                return p;
        }
        return NULL;
    }
    struct MerchandiseL *Build(Merchandise *merchandise, int value){
        struct MerchandiseL *tmp = new struct MerchandiseL;
        tmp->m = merchandise;
        tmp->value = value;
        tmp->next = NULL;
        return tmp;
    }
};