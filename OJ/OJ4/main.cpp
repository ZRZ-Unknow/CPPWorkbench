#include <iostream>
#include "Polynomial.h"
using namespace std;


int main(){
    Polynomial poly1("x4+2x8-10x5+x2+1");
    Polynomial poly2("2x2-5+3x2");
    Polynomial poly11(poly1);
    Polynomial poly_("-x3+2x2");
    Polynomial poly__("x-1");
    poly2.printExpression();
    poly_.printHighest();
    poly__.printHighest();
    poly1.printHighest();
    // 输出 2x8
    poly1.printExpression();
    // 输出 2x8-10x5+x4+x2+1
    cout << poly2.computeValue(1)<<" "<<poly1.computeValue(1)<<endl;
    // 输出 -3
    cout << poly1.getOriginal()<<endl;
    //poly11.printHighest();
    // 输出 2x8
    //poly11.printExpression();
    //cout<<(poly1==poly11)<<" "<<(poly2==poly1)<<endl;
    //poly2 = poly1;
    //poly2.printExpression();
    // 输出 x4+2x8-10x5+x2+1
    Polynomial poly3 = poly1 + poly2;
    // Polynomial + 操作
    poly3.printExpression();
    // 输出 2x8-10x5+x4+3x2-4
    Polynomial poly4 = poly1 - poly2;
    // Polynomial - 操作
    poly4.printExpression();
    // 输出 2x8-10x5+x4-x2+6
    Polynomial poly5 = poly1 - poly1;
    poly5.printExpression();
    // 输出 0
    Polynomial poly6(poly1);
    poly6.printExpression();
    // 输出 2x8-10x5+x4+x2+1
    cout << poly6.getOriginal()<<endl;
    // 输出 x4+2x8-10x5+x2+1
    poly6 = poly6;
    poly6.printExpression();
    Polynomial x = poly6;
    x.printExpression();

    return 0;
}