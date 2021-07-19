#include "mapParams.h"
#include <iostream>
#include <string>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include "day_set.h"

using namespace std;
using namespace sql;

class modelSql{
public:    
    modelSql();
    virtual ~modelSql();
    void setDriver(Driver *dri);
    Driver* getDriver();
    void setConnection(Connection *con);
    Connection* getConnection();
    void setStatement(Statement *stm);
    Statement* getStatement();
    void setResultSet(ResultSet *res);
    ResultSet* getResultSet();
    void clearMap();
    mapParams select(mapParams map);
    mapParams insert(mapParams map);
    mapParams update(mapParams map);
    string getsumVotes(string squad, string numberDay);
    string getActualDay();
    void insertSquadDayPoints(string nameSquad, string numberDay, string points);
    //mapResponse updateVote(mapParams map);
    void deleteRowsPlayerOnDayVote(string query);
    void deleteRowsSquadOnPlayer(string query);
    mapParams deleteRow(mapParams map);
    string login(string name,string pass);

private:
    Driver *driv;
    Connection *conn;
    Statement *stmt;
    ResultSet *resu;
    string URI="tcp://localhost:3306";
    string user="root";
    string pass="";
    mapParams *mr;    
};