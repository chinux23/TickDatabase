#include <QtSql>
#include "Logging/QsLog.h"
#include "Logging/QsLogDest.h"
#include <string>
#include "boost/date_time/posix_time/posix_time.hpp"

#ifndef LIBOTD_H
#define LIBOTD_H

#define DRIVER "QSQLITE"
namespace libOTD{
    
    // Database is one product
    class TickDatabase{
        public:
            Instrument OpenInstrument(const string & inst );
        private:
            set<Instrument> set_of_instruments_;
    };

    // Represent one instrument class
    class Instrument{
        public:
            explicit Instrument ( const string & inst, const string & Contract_Month );
            explicit Instrument ( const & Instrument );
            explicit insertTick ( const Tick & val );
            bool operator< ( const Instrument & other );
            ~Instrument ();
            bool operator= ( const Instrument & other );
        private:
            explicit Instrument ( );
            string instrument_id_;
            string contract_month_;
            string connection_name_;
            QSqlDatabase db_;
    };

    class Tick{
        public:
            explicit Tick ( unsigned double price, unsigned long volume, unsigned long ms_elapsed );
            unsigned double getPrice();
            unsigned double setPrice();
            unsigned long getVolume();
            unsigned long setVolume();
            unsigned long get_ms_elapsed();
            unsigned long set_ms_elapsed();
        private:
            Tick () ;
            unsigned double price_;
            unsigned long volume_;
            unsigned long time_since_start_of_the_session_; // milliseconds from the start of the session
    };

    //TODO: add level 2 information

}
