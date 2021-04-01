#include "header/modelSql.h"

modelSql::modelSql(){
   this->driv = get_driver_instance();
   this->conn = getDriver()->connect(URI,user,pass);
   getConnection()->setSchema("dbCpp");
   this->stmt= getConnection()->createStatement();
   select(query);
}

modelSql::~modelSql(){
    
}

void modelSql::setDriver(Driver *dri){
    this->driv = dri;
}

Driver* modelSql::getDriver(){
   return this->driv;
}

void modelSql::setConnection(Connection *con){
   this->conn = con;
}

Connection* modelSql::getConnection(){
   return this->conn;
}

void modelSql::setStatement(Statement *stm){
   this->stmt = stm; 
}

Statement* modelSql::getStatement(){
   return this->stmt;
}

void modelSql::setResultSet(ResultSet *res){
  this->resu=res;
}

ResultSet* modelSql::getResultSet(){
   return this->resu;
}

   

void modelSql::select(string query){
   try{
      Statement* st = getStatement();
      ResultSet* re = st->executeQuery(query);
       while (re->next()) {
         cout << "MySQL replies: "<<endl;
    /* Access column data by alias or column name */
         cout << re->getRow() << endl;  //N^o dei risultati
         cout << "MySQL says it again: " <<endl;
    /* Access column data by numeric offset, 1 is the first column */
         cout << re->getString(1) << endl;
         return;
       }
    }catch (sql::SQLException &e) {
      cout << "# ERR: SQLException in " << __FILE__;
      cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
      cout << "# ERR: " << e.what();
      cout << " (MySQL error code: " << e.getErrorCode();
      cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}


