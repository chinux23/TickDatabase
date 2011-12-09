#include "include/libOTD.h"
#include <iostream>
#include "gtest/gtest.h"

using namespace libOTD;

TEST ( InstrumentClass, CreateDelete ) {
    Instrument::Instrument * corn = new Instrument::Instrument ( "ZC", "0711"); 
    
    delete corn;
}


/*
TEST(TickClass, CreateDelete){
    Tick::Tick * tick1 = new Tick::Tick(125.5, 100, 2000);
    Tick::Tick * tick2 = new Tick::Tick(124.5, 30, 1000);
    // cout << "Tick1 volume is " << tick1->getVolume() << endl;
    // cout << "Tick2 price is " << tick2->getPrice() << endl;
    EXPECT_EQ ( 100, tick1->getVolume() );
    EXPECT_EQ ( 124.5, tick2->getPrice() );
    delete tick2;
    delete tick1;
}
*/

int main (int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
