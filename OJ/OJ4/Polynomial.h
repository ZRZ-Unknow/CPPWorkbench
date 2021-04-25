#include <iostream>
#include <string.h>
#include <math.h>
using namespace std;

#define ARRAY_LEN 100
#define EXPR_LEN 256

class Polynomial {
private:
    int* coefficient_array;
    char* original_expr;
public:
    Polynomial(const char* ch);
    Polynomial(const Polynomial& poly){
        coefficient_array = new int[ARRAY_LEN];
        memcpy(coefficient_array, poly.coefficient_array, ARRAY_LEN);
        original_expr = new char[EXPR_LEN];
        strcpy(original_expr, poly.original_expr);
    }
    ~Polynomial();
    void printExpression();
    void printHighest();
    char *getOriginal(){
        return original_expr;
    }
    int computeValue(int x1){
        int sum = 0;
        for(int i=0;i<ARRAY_LEN;i++){
            if(coefficient_array[i] != 0)
                sum += coefficient_array[i] * pow(x1, i);
        }
        return sum;
    }
    bool operator == (const Polynomial& poly) const{
        for(int i=0;i<ARRAY_LEN;i++){
            if(coefficient_array[i] != poly.coefficient_array[i])
                return false;
        }
        return true;
    }
    void operator = (const Polynomial& poly){
        if(&poly == this)
            return;
        coefficient_array = new int[ARRAY_LEN];
        memcpy(coefficient_array, poly.coefficient_array, ARRAY_LEN);
        original_expr = new char[EXPR_LEN];
        strcpy(original_expr, poly.original_expr);
    }
    Polynomial operator + (const Polynomial& poly) const{
        Polynomial tmp("");
        for(int i=0;i<ARRAY_LEN;i++){
            tmp.coefficient_array[i] = coefficient_array[i] + poly.coefficient_array[i];
        }
        return tmp;
    }
    Polynomial operator - (const Polynomial& poly) const{
        Polynomial tmp("");
        for(int i=0;i<ARRAY_LEN;i++){
            tmp.coefficient_array[i] = coefficient_array[i] - poly.coefficient_array[i];
        }
        return tmp;
    }
};