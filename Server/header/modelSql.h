#include "mapParams.h"
#include "mapResponse.h"
#include <iostream>
#include <string>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>



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
    mapResponse selectById(mapParams map);


private:
    Driver *driv;
    Connection *conn;
    Statement *stmt;
    ResultSet *resu;
    string URI="tcp://localhost:3306";
    string user="root";
    string pass="";
    //string queryToken0="SELECT nome FROM test WHERE id='id1'";
    
};