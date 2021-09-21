#include "header/modelSql.h"

modelSql::modelSql(){
   this->driv = get_driver_instance();
   this->conn = getDriver()->connect(URI,user,pass);
   getConnection()->setSchema("dbCpp");
   this->stmt= getConnection()->createStatement();
   this->mr = new mapParams();
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

void modelSql::clearMap(){
   this->mr->clearMap();
}

void modelSql::insertSquadDayPoints(string nameSquad,string numberDay, string points){
   //UPDATE day_point SET day=1, points = 14.5 where squad='Triestina'
   //INSERT INTO day_point(squad,day,points) VALUE ('Triestina','1','14.5')
   if(points == "0") return;
   else{
   string query = "INSERT INTO day_point(squad,day,points) VALUE ('"+nameSquad+"','"+numberDay+"','"+points+"')";
   try{
      Statement* st = getStatement();
      st->execute(query);
      writePointsOnFile(nameSquad,numberDay,points);
   }catch (sql::SQLException &e){
      cout << "# ERR: SQLException in " << __FILE__;
      cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
      cout << "# ERR: " << e.what();
      cout << " (MySQL error code: " << e.getErrorCode();
      cout << ", SQLState: " << e.getSQLState() << " )" << endl;
   }
   return;
   }
}

string modelSql::getsumVotes(string squad, string numberDay){
//SELECT sum(vote) FROM day_vote INNER JOIN player ON day_vote.number=1 AND day_vote.surname = player.surname INNER JOIN squad ON player.squad ='Triestina' AND squad.name = player.squad
string resp="";
string query="SELECT sum(vote) FROM day_vote INNER JOIN player ON day_vote.number="+numberDay+" AND day_vote.surname = player.surname INNER JOIN squad ON player.squad ='"+squad+"' AND squad.name = player.squad";
   try{
      Statement* st = getStatement();
      ResultSet* re = st->executeQuery(query);
      sql::ResultSetMetaData *res_meta = re -> getMetaData();
      int columns = res_meta -> getColumnCount();
      while (re->next())
      {
    /* Access column data by numeric offset, 1 is the first column */
            resp = re->getString(1);              
      }
   }catch (sql::SQLException &e){
      cout << "# ERR: SQLException in " << __FILE__;
      cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
      cout << "# ERR: " << e.what();
      cout << " (MySQL error code: " << e.getErrorCode();
      cout << ", SQLState: " << e.getSQLState() << " )" << endl;
   }
   insertSquadDayPoints(squad,numberDay,resp);
   return resp;
}

string modelSql::getActualDay(){
   string resp = "";
   resp = std::to_string(actual_day);
   return resp;
}

mapParams modelSql::select(mapParams map){
string resp, query, queryToken0, queryToken1, queryToken2, queryToken3 = "";
string keyOwner = "owner";
string keySquad = "squad";
string keyDay = "day";
string keyPlayer = "player";
string keyPlayers = "players";
string keyDayPoint = "day_point";
string login = "login";
string username = "name";
string keyActualDay = "actual_day";

// LOGIN = admin & pass= ...
string pass = "pass";
   if(map.findKeyByKey(login) && map.findKeyByKey(pass)){
      queryToken0 = "SELECT pass, name, type FROM ";
      queryToken1 = " WHERE name='";
      queryToken2 = map.findParamByKey(login);
      queryToken3 = "' AND pass='"+ map.findParamByKey(pass) + "'";
      query = queryToken0 + login + queryToken1 + queryToken2 + queryToken3;
   }

   //ACTUAL DAY MATCH
   else if(map.findKeyByKey(keyActualDay)){
      resp = getActualDay();
      this->mr->insertParam("actual_day",resp);
      return *this->mr;
   }

   //ALL PLAYERS OF THE SQUAD
   //players = Triestina
   else if(map.findKeyByKey(keyPlayers)){ 
      queryToken0 = "SELECT id, surname, role FROM player WHERE squad='";
      queryToken1 = map.findParamByKey(keyPlayers) + "'";
      query = queryToken0 + queryToken1;
   }

   //OWNER SQUAD to mainly get "setup" attribute
   //owner = Jenny
   else if(map.findKeyByKey(keyOwner)){
      queryToken0 = "SELECT id, owner, name, setup FROM squad WHERE owner='";
      queryToken1 = map.findParamByKey(keyOwner) + "'";
      query = queryToken0 + queryToken1;
   }

   //TEAM POINTS FOR A DAY OR ALL DAYS (day_point table)
   //squad=Triestina & day_point=1 OR day_point = ""  
   else if(map.findKeyByKey(keySquad) && map.findKeyByKey(keyDayPoint)){
      if(!map.findParamByKey(keyDayPoint).empty()){
         // day_point=1      ***TEAM POINTS FOR A DAY***
         //SELECT * FROM day_point WHERE squad='Triestina' AND day=1
         queryToken0 = "SELECT * FROM ";
         queryToken1 = " WHERE squad ='";
         queryToken2 = map.findParamByKey(keySquad);
         queryToken3 = "' AND day="+ map.findParamByKey(keyDayPoint);
         query = queryToken0 + keyDayPoint + queryToken1 + queryToken2 + queryToken3;
      }
      else{
         //day_point = ""      ***TEAM POINTS FOR ALL DAYS ***
         queryToken0 = "SELECT squad,day,points FROM ";
         queryToken1 = " WHERE squad ='";
         queryToken2 = map.findParamByKey(keySquad)+"'";
         query = queryToken0 + keyDayPoint + queryToken1 + queryToken2;
      }
   }

   //ALL THE SQUADS OR ONE SQUAD
   //squad = Triestina OR squad =
   else if (map.findKeyByKey(keySquad) && !map.findKeyByKey(keyDay) && !map.findKeyByKey(keyPlayer)){
      if(map.findParamByKey(keySquad).empty()){ //ALL THE SQUAD
         query = "SELECT * FROM "+ keySquad;
      }
      else{    //ONE SQUAD
   
         queryToken0 = "SELECT * FROM ";
         queryToken1 = " WHERE name IN ('";
         queryToken2 = map.findParamByKey(keySquad);
         queryToken3 = "')";
         query = queryToken0 + keySquad + queryToken1 + queryToken2 + queryToken3;
      }
   }

   //ALL THE VOTES OF THE PLAYERS OF A TEAM IN A DAY (calculating the sum in a day) OR IN ALL DAYS
   //squad = Triestina & day = 1 OR day = ""
   else if (map.findKeyByKey(keySquad) && map.findKeyByKey(keyDay) && !map.findKeyByKey(keyPlayer)){
      if(!map.findParamByKey(keyDay).empty()){
      //day=1     ***ALL THE VOTES OF THE PLAYERS OF A TEAM IN A DAY***
      //SELECT player.*, day_vote.number, day_vote.vote FROM player INNER JOIN day_vote ON day_vote.surname = player.surname WHERE day_vote.number=1 AND player.squad='Triestina'
         queryToken0="SELECT day_vote.number, player.surname, day_vote.vote FROM player INNER JOIN day_vote ON day_vote.surname = player.surname WHERE day_vote.number=";
         queryToken1=map.findParamByKey(keyDay)+" AND player.squad='"+map.findParamByKey(keySquad)+"'";
         query=queryToken0+queryToken1;
         this->mr->insertParam("zPoints",getsumVotes(map.findParamByKey(keySquad),map.findParamByKey(keyDay)));     
      }
      else{
      //day=""    ***ALL THE VOTES OF THE PLAYERS OF A TEAM IN ALL DAYS*** -> NOT USED
      //SELECT player.*, day_vote.number, day_vote.vote FROM player INNER JOIN day_vote ON day_vote.surname = player.surname WHERE player.squad='Triestina'
         queryToken0="SELECT player.*, day_vote.number, day_vote.vote FROM player INNER JOIN day_vote ON day_vote.surname = player.surname WHERE player.squad='";
         queryToken1=map.findParamByKey(keySquad)+"'";
         query=queryToken0+queryToken1;     
      }
   }

   //NOT USED
   //player = Zagarella 
   else if (map.findKeyByKey(keyPlayer) && !map.findKeyByKey(keyDay) && !map.findKeyByKey(keySquad)){
         queryToken0="SELECT * FROM ";
         queryToken1=" WHERE surname IN ('";
         queryToken2=map.findParamByKey(keyPlayer);
         queryToken3="')"; 
         query=queryToken0+keyPlayer+queryToken1+queryToken2+queryToken3;
   }
   
   //NOT USED   
   //VOTE OF THE PLAYER IN ONE OR ALL DAYS
   //player = Zagarella ; day = 1 OR day = ""
   else if (map.findKeyByKey(keyPlayer) && map.findKeyByKey(keyDay) && !map.findKeyByKey(keySquad)){
      if(!map.findParamByKey(keyDay).empty()){
      //day=1     ***VOTE OF THE PLAYER IN ONE DAY***
      //SELECT player.*, day_vote.number, day_vote.vote FROM player INNER JOIN day_vote ON day_vote.surname = player.surname WHERE day_vote.number=1 AND player.surname='Zagarella'
         queryToken0="SELECT player.*, day_vote.number, day_vote.vote FROM player INNER JOIN day_vote ON day_vote.surname = player.surname WHERE day_vote.number=";
         queryToken1=map.findParamByKey(keyDay)+" AND player.surname='"+map.findParamByKey(keyPlayer)+"'";
         query=queryToken0+queryToken1;       
      }
      else{
      //day=""    ***VOTE OF THE PLAYER IN ALL DAYS***
      //SELECT player.*, day_vote.number, day_vote.vote FROM player INNER JOIN day_vote ON day_vote.surname = player.surname WHERE player.surname='Zagarella'
         queryToken0="SELECT player.*, day_vote.number, day_vote.vote FROM player INNER JOIN day_vote ON day_vote.surname = player.surname WHERE player.surname='";
         queryToken1=map.findParamByKey(keyPlayer)+"'";
         query=queryToken0+queryToken1; 
      }
   }
   else{
      this->mr->insertParam("GET","NOT VALID");
      return *this->mr;
   }
   try{
      Statement* st = getStatement();
      ResultSet* re = st->executeQuery(query);
      sql::ResultSetMetaData *res_meta = re -> getMetaData();
      int columns = res_meta -> getColumnCount();
      while (re->next()) {
         string strToReturn = "";
    /* Access column data by numeric offset, 1 is the first column */
         for (int i = 2; i < columns; i++) {  //<=
            resp += re->getString(i);
            if (i < columns - 1) 
               resp += ",";
         }
         this->mr->insertParam(resp,re->getString(columns));
         resp = "";
      }
   }catch (sql::SQLException &e){
      cout << "# ERR: SQLException in " << __FILE__;
      cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
      cout << "# ERR: " << e.what();
      cout << " (MySQL error code: " << e.getErrorCode();
      cout << ", SQLState: " << e.getSQLState() << " )" << endl;
   }
   return *this->mr;
}

   

mapParams modelSql::insert(mapParams map){
//INSERT INTO squad(name,owner) VALUE ('Inter','Stefano')
//squad = Vittoria;Stefano
//player = Triestina;Muciaccia;POR
string query, queryToken1 = "";
string queryToken0="INSERT INTO ";
string queryToken3="')";
string table = map.returnKey();
string value=map.findParamByKey(table);
   //squad
   if(table == "squad"){
      queryToken1 ="(name,owner) VALUE ('";
      query= queryToken0+table+queryToken1+value+queryToken3;
   }
   //player
   else if(table == "player"){
      queryToken1="(squad,surname,role) VALUE ('";
      query = queryToken0+table+queryToken1+value+queryToken3;
   }
   //day  *** insert team of the day on table day_vote***
   else if(table=="day_vote"){
      queryToken1="(number,surname) VALUE ('";
      query=queryToken0+table+queryToken1+value+queryToken3;
   }
   else{
      mr->insertParam("Insert NOT SUCCESS",table+" or "+value+" NOT VALID");
      return *this->mr;
   }
   try{
      Statement* st = getStatement();
      st->execute(query);
      mr->insertParam("Insert "+table,"SUCCESS");
   }catch (sql::SQLException &e){
      cout << "# ERR: SQLException in " << __FILE__;
      cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
      cout << "# ERR: " << e.what();
      cout << " (MySQL error code: " << e.getErrorCode();
      cout << ", SQLState: " << e.getSQLState() << " )" << endl;
   }
   return *this->mr;
}

mapParams modelSql::update(mapParams map){
string keySquad = "squad";
string keyNumberDay = "number";
string keySurnamePlayer = "surname";
string keyVotePlayer = "vote";
string keySetup = "setup";
string query ="";
   //UPDATE attribute setup of squad 
   if(map.findKeyByKey(keySquad)){
      query = "UPDATE squad SET setup ='0' WHERE name = '"+map.findParamByKey(keySquad)+"'";
   }
   else if(map.findKeyByKey(keySetup)){
      //http://localhost:8030/PUT?setup=giornata&name=squadname
      query = "UPDATE squad SET setup ='"+map.findParamByKey(keySetup)+"' WHERE name = '"+map.findParamByKey(keySquad)+"'";
   }
   //UPDATE VOTE OF THE PLAYER ON day_vote table
   //http://localhost:8030/PUT?surname=Zagarella&number=1&vote=8
   // surname = Zagarella   number= 1  vote=8
   else if(map.findKeyByKey(keyNumberDay) && map.findKeyByKey(keySurnamePlayer)){
      query = "UPDATE day_vote SET vote ="+map.findParamByKey(keyVotePlayer)+" WHERE surname = '"+map.findParamByKey(keySurnamePlayer)+"' AND number="+map.findParamByKey(keyNumberDay);   
   }
   else this->mr->insertParam("UPDATE","NOT VALID");
   try{
      Statement* st = getStatement();
      st->execute(query);
   }catch (sql::SQLException &e){
      cout << "# ERR: SQLException in " << __FILE__;
      cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
      cout << "# ERR: " << e.what();
      cout << " (MySQL error code: " << e.getErrorCode();
      cout << ", SQLState: " << e.getSQLState() << " )" << endl;
   }  
   return *this->mr;
}

void modelSql::deleteRowsPlayerOnDayVote(string query){
   try{
      Statement* st = getStatement();
      st->execute(query);
   }catch (sql::SQLException &e){
      cout << "# ERR: SQLException in " << __FILE__;
      cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
      cout << "# ERR: " << e.what();
      cout << " (MySQL error code: " << e.getErrorCode();
      cout << ", SQLState: " << e.getSQLState() << " )" << endl;
   }
   return;
}

void modelSql::deleteRowsSquadOnPlayer(string query){
   try{
      Statement* st = getStatement();
      st->execute(query);
   }catch (sql::SQLException &e){
      cout << "# ERR: SQLException in " << __FILE__;
      cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
      cout << "# ERR: " << e.what();
      cout << " (MySQL error code: " << e.getErrorCode();
      cout << ", SQLState: " << e.getSQLState() << " )" << endl;
   }
   return;
}


mapParams modelSql::deleteRow(mapParams map){
//DELETE FROM player WHERE surname='Zagarella'
//player=Zagarella
//DELETE FROM squad WHERE name='Vittoria'
string queryToken0 = "DELETE FROM ";
string table =  map.returnKey();
string queryToken1 = " WHERE ";
string queryToken2,query="";
string value=map.findParamByKey(table);
string queryToken4="'";
   if(table=="player" && value!=""){
      queryToken2="surname='";
      query=queryToken0+table+queryToken1+queryToken2+value+queryToken4;
      deleteRowsPlayerOnDayVote(queryToken0+"day_vote"+queryToken1+queryToken2+value+queryToken4);
      this->mr->insertParam("Player "+value,"DELETE");
   }
   else if(table=="squad" && value!=""){
      queryToken2="name='";
      query=queryToken0+table+queryToken1+queryToken2+value+queryToken4;
      deleteRowsSquadOnPlayer(queryToken0+"player"+queryToken1+"squad='"+value+queryToken4);
      this->mr->insertParam("Squad "+value,"DELETE");
   }
   else {
      mr->insertParam("Delete NOT SUCCESS",table+"NOT VALID or "+value+" EMPTY");
      return *this->mr;
   }
   try{
      Statement* st = getStatement();
      st->execute(query);
   }catch (sql::SQLException &e){
      cout << "# ERR: SQLException in " << __FILE__;
      cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
      cout << "# ERR: " << e.what();
      cout << " (MySQL error code: " << e.getErrorCode();
      cout << ", SQLState: " << e.getSQLState() << " )" << endl;
   }
   return *this->mr;
}

