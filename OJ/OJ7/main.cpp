#include "ArrayPoly.h"
#include "ListPoly.h"
#include <iostream>
using namespace std;

template<class T> void sortPoly(T *polys) {// 实现多项式按照指数降序排序
    int n = polys->getSize();
    while (n>1) {
        int i_min = 0;
        for (int i = 1; i<n; i++)
            if (polys->getIthPow(i) < polys->getIthPow(i_min))
                i_min = i;
        if (i_min != n-1) {
            int p = polys->getIthCoe(i_min),
                q = polys->getIthPow(i_min);
            polys->setIthCoe(i_min, polys->getIthCoe(n-1));
            polys->setIthPow(i_min, polys->getIthPow(n-1));
            polys->setIthCoe(n-1, p);
            polys->setIthPow(n-1,q);
        };
        n--;
    }
}

template<class T> void print(T *polys) {// 实现多项式的打印功能
    unsigned int n = polys->getSize();
    for (int i = 0; i < n; i++)
        cout << polys->getIthCoe(i) << " " << polys->getIthPow(i) << endl;
}

int main(){
    Polynomial* poly1 = new ArrayPoly();
    poly1->addTerm(3, 4);
    poly1->addTerm(7, 8);
    poly1->addTerm(8, 3);
    unsigned n = poly1->getSize();
    sortPoly(poly1);
    print(poly1);
    delete poly1;
    
    ListPoly lp1;
    lp1.addTerm(5, 6);
    lp1.addTerm(7, 8);
    lp1.addTerm(3, 3);
    ListPoly lp2 = lp1;
    sortPoly(&lp1);
    print(&lp2);

    ArrayPoly* ap1 = new ArrayPoly();
    ap1->addTerm(2, 4);
    ap1->addTerm(5, 4);
    ap1->addTerm(8, 3);
    ap1->setIthCoe(1, 1);
    ArrayPoly ap2(*ap1);
    delete ap1;
    print(&ap2);

    ListPoly lp3;
    lp3 = lp2;
    lp2.setIthCoe(2, 2);
    print(&lp3);

    return 0;
}