#include "include/libOTD.h"
using namespace libOTD;
// OpenInstrument{}

// start of Class Tick Implementation
Tick::Tick(double price, unsigned long volume, unsigned long ms_elapsed):price_(price),volume_(volume),time_since_start_of_the_session_(ms_elapsed){ }
double Tick::getPrice(){ return this->price_; }
Tick & Tick::setPrice(double price ){ this->price_ = price; return *this; }
unsigned long Tick::getVolume(){ return this->volume_; }
Tick & Tick::setVolume( unsigned long volume ) { this->volume_ = volume_; return *this; }
unsigned long Tick::get_ms_elapsed() { return this->time_since_start_of_the_session_; }
Tick & Tick::set_ms_elapsed( unsigned long ms_elapsed ) { this->time_since_start_of_the_session_ = ms_elapsed ; return *this; } 
// end of Class Tick Implementation

// start of Class Instrument implementation
Instrument::Instrument( const string & inst, const string & Contract_Month ):instrument_id_(inst),contract_month_(Contract_Month){
    connection_name_ = instrument_id_ + contract_month_;
    db_ = QSqlDatabase::addDatabase(DRIVER, QString::fromStdString (connection_name_) );
    db_.setDatabaseName( QString::fromStdString ( connection_name_ + ".db" ) );
}
Instrument::Instrument ( const Instrument & inst ) {
    instrument_id_ = inst.instrument_id_;
    contract_month_ = inst.contract_month_;
    connection_name_ = inst.connection_name_;
    db_ = QSqlDatabase::addDatabase(DRIVER, QString::fromStdString (connection_name_) );
    db_.setDatabaseName( QString::fromStdString ( connection_name_ + ".db" ) );
}
const Tick & Instrument::insertTick(const Tick & val){ return val; }
bool Instrument::operator< ( const Instrument & other ) { }
Instrument & Instrument::operator= ( const Instrument & other ) { }
Instrument::~Instrument (){ return; }
string Instrument::get_instrument_id(){ return this->instrument_id_; }
string Instrument::get_contract_month_(){ return this->contract_month_; }
// end of Class Instrument implementation
