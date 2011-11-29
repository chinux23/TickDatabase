#include <QtSql>
#include "Logging/QsLog.h"
#include "Logging/QsLogDest.h"
#include <string>
#include "boost/date_time/posix_time/posix_time.hpp"

#ifndef LIBOTD_H
#define LIBOTD_H

#define DRIVER "QSQLITE"
namespace libOTD{
    using namespace std;
    // Database is one product
    /**********************************
      class TickDatabase{
      public:
      Instrument OpenInstrument(const string & inst );
      private:
      set<Instrument> set_of_instruments_;
      };
     **********************************/

    class Tick{
        public:
            explicit Tick ( double price, unsigned long volume, unsigned long ms_elapsed );
            double getPrice();
            Tick & setPrice( double price);
            unsigned long getVolume();
            Tick & setVolume( unsigned long volume );
            unsigned long get_ms_elapsed();
            Tick & set_ms_elapsed( unsigned long ms_elapsed );
        private:
            Tick (){ } ;
            double price_;
            unsigned long volume_;
            unsigned long time_since_start_of_the_session_; // milliseconds from the start of the session
    };


    // Represent one instrument class
    // same Instrument can be instantiated multiple times
    class Instrument{
        public:
            explicit Instrument ( const string & inst, const string & Contract_Month );
            explicit Instrument ( const Instrument & inst );
            const Tick & insertTick ( const Tick & val );
            bool operator< ( const Instrument & other );
            ~Instrument ();
            Instrument & operator= ( const Instrument & other );
            string get_instrument_id();
            string get_contract_month_();
        private:
            explicit Instrument ( ){ };
            string instrument_id_;
            string contract_month_;
            string connection_name_;
            QSqlDatabase db_;
    };

    //TODO: add level 2 information

}
#endif
