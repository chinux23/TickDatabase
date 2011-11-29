#include <QtSql>
#include <iostream>
#include "Logging/QsLog.h"
#include "Logging/QsLogDest.h"

#define DRIVER "QSQLITE"
using namespace std;

int main() {
    bool ret = false;

    QSqlDatabase db = QSqlDatabase::addDatabase(DRIVER);
    db.setDatabaseName("test_corn_12_21.sqlite3.db");

    QsLogging::Logger& logger = QsLogging::Logger::instance();
    logger.setLoggingLevel(QsLogging::TraceLevel);
    const QString sLogPath("./log.txt");
    QsLogging::DestinationPtr fileDestination(
            QsLogging::DestinationFactory::MakeFileDestination(sLogPath) );
    QsLogging::DestinationPtr debugDestination(
            QsLogging::DestinationFactory::MakeDebugOutputDestination() );
    logger.addDestination(debugDestination.get());
    logger.addDestination(fileDestination.get());

    QLOG_INFO() << "Program started";
    QLOG_INFO() << "Built with Qt" << QT_VERSION_STR << "running on" << qVersion();

    QLOG_TRACE() << "Here's a" << QString("trace") << "message";
    QLOG_DEBUG() << "Here's a" << static_cast<int>(QsLogging::DebugLevel) << "message";
    QLOG_WARN()  << "Uh-oh!";
    qDebug() << "This message won't be picked up by the logger";
    QLOG_ERROR() << "An error has occurred";


    bool ok = db.open();

    if ( ok )
    {
        QSqlQuery query;
        ret = query.exec("create table person"
                "(id integer primary key, "
                "firstname varchar(20), "
                "lastname varchar(30), "
                "age integer)");
        QLOG_ERROR() << db.QSqlDatabase::connectionName(); 
        if ( ret == true) QLOG_INFO() << "Query is successful" << endl;
        else QLOG_ERROR() << query.lastError();
        // query.finish()
        ret = query.exec(QString("insert into person values(NULL,'%1','%2',%3)").arg("Chen").arg("Huang").arg(27));
        if ( ret == true) QLOG_INFO() << "Query is successful" << endl;
        else QLOG_ERROR() << query.lastError();
        // read the some of the database entries

        ret = query.exec("SELECT firstname FROM person");

        if ( query.isActive() && query.isSelect() ){
            while (query.next()){
                QLOG_DEBUG() << query.value(0).toString() << endl;

            }
        }

    }else{
        QLOG_DEBUG() << "Database failed to open" << endl;
    }  

}
