#include "include/libOTD.h"
#include <iostream>

using namespace libOTD;

int main () {
    Tick::Tick * tick1 = new Tick::Tick(125.5, 100, 2000);
    Tick::Tick * tick2 = new Tick::Tick(125.5, 100, 2000);
    
    cout << "Tick1 volume is " << tick1->getVolume() << endl;
    cout << "Tick2 price is " << tick2->getPrice() << endl;
    
    delete tick2;
    delete tick1;

    return 0;
}
