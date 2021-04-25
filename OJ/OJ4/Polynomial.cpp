#include <string>
#include <string.h>
#include "Polynomial.h"
using namespace std;

// int* convertString2Int(const char* char_array)
// 1. 将char_array指向的字符串数组转换为对应的多项式表达，用int数组表示
// 2. 返回长度为100的int型数组，每个数组元素代表对应指数项的次数
//   例如，x4 + 3x2 + 1 这一多项式返回的数组中，下标为0处的元素为1，代表+1这个项；下标为2的元素为3，代表+3x2这个项；
//        下标为4的元素为1，代表x4这个项
// 3. 函数仅供本次上机使用，在本次上机中不会影响结果，应用在其他场景不保证正确性。

void createItem(string s, int* array) {
    if(s == "")
        return;
    if(s[0] == '+')
        s.erase(s.begin());
    if(s[0] == 'x')
        s.insert(s.begin(), '1');
    else if(s[0] == '-' && s[1] == 'x')
        s.insert(s.begin() + 1, '1');
    
    int coefficent = 0;
    int power = 0;
    int index = 0;
    while(index < s.size() && s[index] != 'x') {
        index++;
    }
    coefficent = atoi(s.substr(0, index).c_str());
    if(index < s.size() - 1) {
        power = atoi(s.substr(index + 1, s.size() - index).c_str());
    } else if(index == s.size() - 1) {
        power = 1;
    } else {
        power = 0;
    }
    array[power] += coefficent;
}

int* convertString2Int(const char* c) {
    int* array = new int[ARRAY_LEN];
    for(int i = 0; i < ARRAY_LEN; i++)
        array[i] = 0;
    string str(c);
    if(str == "")
        return array;
    int preIndex = 0;
    for(int i = 0; i < str.size(); i++) {
        if(str[i] == '+' || str[i] == '-'){
            createItem(str.substr(preIndex, i - preIndex), array);
            preIndex = i;
        }
    }
    createItem(str.substr(preIndex, str.size() - preIndex), array);
    return array;
}

Polynomial::Polynomial(const char* ch){
    original_expr = new char[EXPR_LEN];
    strcpy(original_expr, ch);
    coefficient_array = convertString2Int(ch);
}

Polynomial::~Polynomial() {
    if(coefficient_array != NULL) {
        delete[] coefficient_array;
        coefficient_array = NULL;
    }
    if(original_expr != NULL) {
        delete[] original_expr;
        original_expr = NULL;
    }
}

void Polynomial::printHighest(){
    for(int i=ARRAY_LEN-1;i>=0;i--){
        if(coefficient_array[i] != 0){
            if(coefficient_array[i] == 1)
                printf("x%d\n", i);
            else if(coefficient_array[i] == -1)
                printf("-x%d\n", i);
            else
                printf("%dx%d\n", coefficient_array[i], i);
            return;
        }
    }
    printf("0\n");
}

void Polynomial::printExpression(){
    bool is_null=true;
    for(int i=ARRAY_LEN-1;i>=0;i--){
        if(i==0){
            if(coefficient_array[i] > 0){
                if(is_null == false)
                    printf("+%d", coefficient_array[i]);
                else
                    printf("%d", coefficient_array[i]);
                is_null = false;
            }else if(coefficient_array[i] < 0){
                printf("%d", coefficient_array[i]);
                is_null = false;
            }
        }else{
            if(coefficient_array[i] > 0){
                if(is_null == false){
                    if(coefficient_array[i] == 1)
                        printf("+x%d", i);
                    else
                        printf("+%dx%d", coefficient_array[i], i);
                }else{
                    if(coefficient_array[i] == 1)
                        printf("x%d", i);
                    else
                        printf("%dx%d", coefficient_array[i], i);
                }
                is_null = false;
            }else if(coefficient_array[i] < 0){
                if(coefficient_array[i] == -1)
                    printf("-x%d", i);
                else
                    printf("%dx%d", coefficient_array[i], i);
                is_null = false;
            }
        }
    }
    if(is_null)
        printf("0\n");
    else
        printf("\n");
}