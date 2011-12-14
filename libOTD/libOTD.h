#include <QtSql>
#include "Logging/QsLog.h"
#include "Logging/QsLogDest.h"
#include <string>
#include "boost/date_time/posix_time/posix_time.hpp"
#include "boost/date_time/gregorian/gregorian.hpp"

#ifndef LIBOTD_H
#define LIBOTD_H

#define DRIVER "QSQLITE"
namespace libOTD{
    using namespace std;
    using namespace boost::gregorian;
    // Database is one product
    /**********************************
      class TickDatabase{
      public:
      Instrument OpenInstrument(const string & inst );
      private:
      set<Instrument> set_of_instruments_;
      };
     **********************************/
    
    enum OTD_INSTRUMENT_RESPONSE{
        OTD_SUCCESS = 0,
        OTD_OPEN_DATABASE_ERROR = 1,
        OTD_QUERY_EXECUTION_ERROR,
        OTD_QUERY_FAIL_SESSION_NOT_OPEN,
        END_OF_OTD_INSTRUMENT_ERRO
    };

    class Tick{
        public:
            explicit Tick ( double price, unsigned long volume, unsigned long ms_elapsed );
            double getPrice() const ;
            Tick & setPrice( double price);
            unsigned long getVolume() const ;
            Tick & setVolume( unsigned long volume );
            unsigned long get_ms_elapsed() const;
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
            OTD_INSTRUMENT_RESPONSE insertTick ( const Tick & val );
            bool operator< ( const Instrument & other );
            ~Instrument ();
            Instrument & operator= ( const Instrument & other );
            string get_instrument_id();
            string get_contract_month_();
            OTD_INSTRUMENT_RESPONSE start_session ( const date & );
            OTD_INSTRUMENT_RESPONSE stop_session ( );
            bool is_session_open ();
        
        private:
            explicit Instrument ( ){ };
            string instrument_id_;
            string contract_month_;
            string connection_name_;
            QSqlDatabase db_;
            string session_name;
    };

    //TODO: add level 2 information

}
#endif
