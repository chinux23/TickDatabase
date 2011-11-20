#include <QtSql>
#include <iostream>

#define DRIVER "QSQLITE"

using namespace std;

int main() {
    bool ret = false;

    QSqlDatabase db = QSqlDatabase::addDatabase(DRIVER);
    db.setDatabaseName("test_corn_12_11.sqlite3.db");
    bool ok = db.open();

    if ( ok )
    {
        QSqlQuery query;
        ret = query.exec("create table person"
                "(id integer primary key, "
                "firstname varchar(20), "
                "lastname varchar(30), "
                "age integer)");
        
        if ( ret == true) cout<< "Query is successful" << endl;
        ret = query.exec(QString("insert into person values(NULL,'%1','%2',%3)").arg("Chen").arg("Huang").arg(27));
        if ( ret == true) cout<< "Query is successful" << endl;
    }else{
        std::cout<< "Database failed to open" << endl;
    }  

}
