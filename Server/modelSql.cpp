#include "header/modelSql.h"

modelSql::modelSql(){
   this->driv = get_driver_instance();
   this->conn = getDriver()->connect(URI,user,pass);
   getConnection()->setSchema("dbCpp");
   this->stmt= getConnection()->createStatement();
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
   
/* SELECT columns_to_return
 * FROM table_to_query
 * WHERE search_condition;*/
mapResponse modelSql::selectById(mapParams map){
   mapResponse *mr = mapResponse::getInstance();
   string queryToken0="SELECT * FROM test ";
   string id="id";
   string query = queryToken0;
   string queryTokenId=map.findParamByKey(id);
   if (!queryTokenId.empty())
   {
   string queryToken0="SELECT * FROM test ";
   string queryToken1="WHERE id IN ('";
   string queryToken2="')"; 
   query=queryToken0+queryToken1+queryTokenId+queryToken2;
   }
   string resp ="";
   try{
      Statement* st = getStatement();
      ResultSet* re = st->executeQuery(query);
      sql::ResultSetMetaData *res_meta = re -> getMetaData();
      int columns = res_meta -> getColumnCount();
      while (re->next()) {
         string strToReturn = "";
    /* Access column data by numeric offset, 1 is the first column */
         for (int i = 2; i <= columns; i++) {
            resp = resp + re->getString(i);
            if(i<columns)
            resp = resp + " ";
         }
         mr->insertParam(re->getString(1),resp);
         resp = "";
      }
   }catch (sql::SQLException &e){
      cout << "# ERR: SQLException in " << __FILE__;
      cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
      cout << "# ERR: " << e.what();
      cout << " (MySQL error code: " << e.getErrorCode();
      cout << ", SQLState: " << e.getSQLState() << " )" << endl;
   }
   return *mr;
}


