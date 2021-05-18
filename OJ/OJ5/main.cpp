#include <iostream>
#include "CombinedOrder.h"
using namespace std;


int main(){
    Mask mask1("Mask1",5,5);
    Mask mask2("Mask2",10,1);
    Mask mask3("Mask3",15,20);
    Mask mask4("Mask1", 5, 10);
    Vaccine vaccine1("Vaccine1",300,2,10);
    Vaccine vaccine2("Vaccine2",400,1,3);
    cout << mask2.GetName() << " " << vaccine1.GetBound() << endl;
    CombinedOrder<Mask> order1;
    CombinedOrder<Vaccine> order2;
    
    order1.AddOrder(mask1);
    order1.AddOrder(mask2);
    order1.AddOrder(mask3);
    order1.AddOrder(mask4);
    order2.AddOrder(vaccine1);
    order2.AddOrder(vaccine2);

    cout << order1.GetTotalCost() << endl;
    cout << order2.GetTotalCost() << endl;
    cout << order2[1].GetName() << endl;
    cout << IsLessThan(mask1, mask2)<<endl;
    
    SortOrder(order2);
    cout << order2[1].GetName() << endl;
    return 0;
}