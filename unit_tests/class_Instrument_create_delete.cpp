#include "libOTD.h"
#include <iostream>
#include "gtest/gtest.h"

using namespace libOTD;

TEST ( InstrumentClass, CreateDelete ) {
    Instrument::Instrument * corn = new Instrument::Instrument ( "ZC", "0711"); 
    EXPECT_EQ ( false, corn->is_session_open() );

    EXPECT_EQ ( OTD_SUCCESS, corn->start_session( date(2002,Jan,10) ) );
    EXPECT_EQ ( true, corn->is_session_open() );

    EXPECT_EQ ( OTD_SUCCESS, corn->insertTick( Tick::Tick(125.5, 100, 2000) ) );
    EXPECT_EQ ( OTD_SUCCESS, corn->insertTick( Tick::Tick(125.0, 50, 3000) ) );
    EXPECT_EQ ( OTD_SUCCESS, corn->insertTick( Tick::Tick(124.5, 50, 4500) ) );

    corn->stop_session();
    EXPECT_EQ ( false, corn->is_session_open() );

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
