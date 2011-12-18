#include "libOTD.h"
#include <boost/lexical_cast.hpp>
using namespace libOTD;

// OpenInstrument{}

// start of Class Tick Implementation
Tick::Tick(double price, unsigned long volume, unsigned long ms_elapsed):price_(price),volume_(volume),time_since_start_of_the_session_(ms_elapsed){ }
double Tick::getPrice() const { return this->price_; }

Tick & Tick::setPrice(double price ){ this->price_ = price; return *this; }
unsigned long Tick::getVolume() const { return this->volume_; }
Tick & Tick::setVolume( unsigned long volume ) { this->volume_ = volume_; return *this; }
unsigned long Tick::get_ms_elapsed() const { return this->time_since_start_of_the_session_; }
Tick & Tick::set_ms_elapsed( unsigned long ms_elapsed ) { this->time_since_start_of_the_session_ = ms_elapsed ; return *this; } 
// end of Class Tick Implementation

// start of Class Instrument implementation
Instrument::Instrument( const string & inst, const string & Contract_Month ):instrument_id_(inst),contract_month_(Contract_Month){
    connection_name_ = instrument_id_ + contract_month_;
    db_ = QSqlDatabase::addDatabase(DRIVER, QString::fromStdString (connection_name_) );
    db_.setDatabaseName( QString::fromStdString ( connection_name_ + ".db" ) );
    string session_name = "";
}
Instrument::Instrument ( const Instrument & inst ) {
    instrument_id_ = inst.instrument_id_;
    contract_month_ = inst.contract_month_;
    connection_name_ = inst.connection_name_;
    db_ = QSqlDatabase::addDatabase(DRIVER, QString::fromStdString (connection_name_) );
    db_.setDatabaseName( QString::fromStdString ( connection_name_ + ".db" ) );
    string session_name = "";
}
OTD_INSTRUMENT_RESPONSE Instrument::insertTick(const Tick & val){
    
    if ( is_session_open() ){
        bool ret = false;
        QSqlQuery query(db_);
        QString queryString;
        queryString = QString::fromStdString("insert into " + session_name + 
                                                " (tick_price, volume, time_elapsed) values (" + boost::lexical_cast<std::string>(val.getPrice()) + ", "
                                                + boost::lexical_cast<std::string>(val.getVolume()) + ", "
                                                + boost::lexical_cast<std::string>(val.get_ms_elapsed()) + ")"
                                                ); 
        std::cout << queryString.toStdString() << std::endl; 
        ret = query.exec( queryString );
        
        if ( ret == true )
            return OTD_SUCCESS;
        else
            std::cout << query.lastError().text().toStdString()<< std::endl;
            return OTD_QUERY_EXECUTION_ERROR;
    }else{
        return OTD_QUERY_FAIL_SESSION_NOT_OPEN;
    }
}


bool Instrument::operator< ( const Instrument & other ) { }
Instrument & Instrument::operator= ( const Instrument & other ) { }
Instrument::~Instrument (){ return; }

string Instrument::get_instrument_id(){
    return this->instrument_id_; 
}

string Instrument::get_contract_month_(){ 
    return this->contract_month_; 
}

OTD_INSTRUMENT_RESPONSE Instrument::start_session(const date & today ){
    bool ret = false;
    session_name = "corn" + to_iso_string ( today );
    QString queryString;
    
    if ( db_.open() ){
        if ( db_.isOpen() ){
            std::cout << "Database is open" << std::endl;
        }
        QSqlQuery query(db_);
        queryString = QString::fromStdString( "create table " + session_name +
                "(id integer primary key, "
                "tick_price double, "
                "volume UNSIGNED BIG INT, "
                "time_elapsed UNSIGNED BIG INT);" );
        std::cout << queryString.toStdString() << std::endl;
        ret = query.exec( queryString );

        if ( ret == true ){
            return OTD_SUCCESS;
            std::cout << "Successfully executed session " << std::endl;
        }
        else
        {   
            std::cout << "Query unsuccessful!" << std::endl;
            std::cout << query.lastError().text().toStdString()<< std::endl;
            return OTD_QUERY_EXECUTION_ERROR;
        }

    }else{
        QLOG_DEBUG() << "Database failed to open";
        return OTD_OPEN_DATABASE_ERROR;
    }

}

OTD_INSTRUMENT_RESPONSE Instrument::stop_session(){
    session_name = "";
    return OTD_SUCCESS;
}

bool Instrument::is_session_open(){
    return session_name != "";

}

// end of Class Instrument implementation

