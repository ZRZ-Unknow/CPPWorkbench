#pragma once
#include "Polynomial.h"
#include<iostream>
#include<assert.h>

struct Node {
    int coef;
    int power;
    Node *m_pre, *m_next;
    Node(int _coef, int _power) {
        m_pre = nullptr;
        m_next = nullptr;
        coef = _coef;
        power = _power;
    }
};


class ListPoly: public Polynomial {
private:
    Node* head;
public:
    ListPoly(){
	head = NULL;
    }
    ~ListPoly(){
	for(Node *tmp = head;tmp!=NULL;){
	    Node *t = tmp;
	    tmp = tmp->m_next;
	    delete t;
	}
    }
    ListPoly(ListPoly const &polynomial){
	head = NULL;
	if(!polynomial.head) return;
	head = new Node(polynomial.head->coef, polynomial.head->power);
	Node *tmp = polynomial.head->m_next;
	Node *curr = head;
	while(true){
	    if(!tmp) break;
	    Node *node = new Node(tmp->coef, tmp->power);
	    curr->m_next = node;
	    node->m_pre = curr;
	    curr = curr->m_next;
	    tmp = tmp->m_next;
	}
    }
    ListPoly& operator = (const ListPoly& p){
	if(head){
	    for(Node *tmp = head;tmp!=NULL;){
	        Node *t = tmp;
	        tmp = tmp->m_next;
	        delete t;
	    }
	    head = NULL;
	}
	if(!p.head) return *this;
	head = new Node(p.head->coef, p.head->power);
	Node *node = p.head->m_next;
	Node *curr = head;
	while(true){
	    if(!node) break;
            Node *new_node = new Node(node->coef, node->power);
	    curr->m_next = new_node;
	    new_node->m_pre = curr;
	    curr = curr->m_next;
	    node = node->m_next;
	}
	return *this;
    }
    void addTerm(int coef, int power){
	if(!head){
	    head = new Node(coef, power);
	    return;
	}
	Node *last;
        for(Node *node=head;node!=NULL;node=node->m_next){
            if(node->power == power){
		node->coef += coef;
	        if(node->coef == 0){
		    if(node == head){
                        head = head->m_next;
         	    }else{  
	                Node *pre = node->m_pre;
		        pre->m_next = node->m_next;
		        if(node->m_next){
    		            node->m_next->m_pre = pre;
		        }
		    }
                    delete node;
		    node = NULL;
	        }
	        return;
	    }
	    last = node;
        }
	assert(last && !last->m_next);
	Node *new_node = new Node(coef, power);
	last->m_next = new_node;
	new_node->m_pre = last;
    }
    void setIthCoe(int i, int coef){
	Node *node = head;
	for(int p=0;p<i;p++){
            node = node->m_next;
	}
	node->coef = coef;
    }
    void setIthPow(int i,int power){
        Node *node = head;
	for(int p=0;p<i;p++){
            node = node->m_next;
	}
	node->power = power;
    }
    int getIthCoe(int i){
        Node *node = head;
	for(int p=0;p<i;p++){
            node = node->m_next;
	}
	return node->coef;
    }
    int getIthPow(int i){
        Node *node = head;
	for(int p=0;p<i;p++){
            node = node->m_next;
	}
	return node->power;
    }
    int getSize(){
	int size = 0;
	for(Node *tmp=head;tmp!=NULL;tmp=tmp->m_next){
	    size++;
	}
	return size;
    }
};
