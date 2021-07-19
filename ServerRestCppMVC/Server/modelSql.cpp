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
   //UPDATE day_point SET day=1, points = 14.5 where squad='Palestina'
   //INSERT INTO day_point(squad,day,points) VALUE ('Palestina','1','14.5')
   if(points == "0") return;
   else{
   string query = "INSERT INTO day_point(squad,day,points) VALUE ('"+nameSquad+"','"+numberDay+"','"+points+"')";
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
}

string modelSql::getsumVotes(string squad, string numberDay){
//SELECT sum(vote) FROM day_vote INNER JOIN player ON day_vote.number=1 AND day_vote.surname = player.surname INNER JOIN squad ON player.squad ='Palestina' AND squad.name = player.squad
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
// login = admin & pass= ...
string pass = "pass";
   if(map.findKeyByKey(login) && map.findKeyByKey(pass)){
      queryToken0 = "SELECT pass, name, type FROM ";
      queryToken1 = " WHERE name='";
      queryToken2 = map.findParamByKey(login);
      queryToken3 = "' AND pass='"+ map.findParamByKey(pass) + "'";
      query = queryToken0 + login + queryToken1 + queryToken2 + queryToken3;
   }
   else if(map.findKeyByKey(keyActualDay)){
      resp = getActualDay();
      this->mr->insertParam("actual_day",resp);
      return *this->mr;
   }
   else if(map.findKeyByKey(keyPlayers)){ 
   //players = Triestina   ***all squad's players***
      queryToken0 = "SELECT id, surname, role FROM player WHERE squad='";
      queryToken1 = map.findParamByKey(keyPlayers) + "'";
      query = queryToken0 + queryToken1;
   }
   else if(map.findKeyByKey(keyOwner)){
      queryToken0 = "SELECT id, owner, name, setup FROM squad WHERE owner='";
      queryToken1 = map.findParamByKey(keyOwner) + "'";
      query = queryToken0 + queryToken1;
   }
   else if(map.findKeyByKey(keySquad) && map.findKeyByKey(keyDayPoint)){
   //squad=Palestina ; day_point=1 
   //SELECT * FROM day_point WHERE squad='Palestina' AND day=1
      queryToken0 = "SELECT * FROM ";
      queryToken1 = " WHERE squad ='";
      queryToken2 = map.findParamByKey(keySquad);
      queryToken3 = "' AND day="+ map.findParamByKey(keyDayPoint);
      query = queryToken0 + keyDayPoint + queryToken1 + queryToken2 + queryToken3;
   }
   else if (map.findKeyByKey(keySquad) && !map.findKeyByKey(keyDay) && !map.findKeyByKey(keyPlayer)){
      //FORSE NON SERVE
      if(map.findParamByKey(keySquad).empty()){
         query = "SELECT * FROM "+ keySquad;
      }
      else{
   //squad = Triestina
         queryToken0 = "SELECT * FROM ";
         queryToken1 = " WHERE name IN ('";
         queryToken2 = map.findParamByKey(keySquad);
         queryToken3 = "')";
         query = queryToken0 + keySquad + queryToken1 + queryToken2 + queryToken3;
      }
   }
   else if (map.findKeyByKey(keySquad) && map.findKeyByKey(keyDay) && !map.findKeyByKey(keyPlayer)){
//squad = Palestina ; day = 1 OR day = ""
      if(!map.findParamByKey(keyDay).empty()){
      //day=1     ***All the votes of the players of the team of the match's day***
      //SELECT player.*, day_vote.number, day_vote.vote FROM player INNER JOIN day_vote ON day_vote.surname = player.surname WHERE day_vote.number=1 AND player.squad='Triestina'
         queryToken0="SELECT day_vote.number, player.surname, day_vote.vote FROM player INNER JOIN day_vote ON day_vote.surname = player.surname WHERE day_vote.number=";
         queryToken1=map.findParamByKey(keyDay)+" AND player.squad='"+map.findParamByKey(keySquad)+"'";
         query=queryToken0+queryToken1;
         // this->mr->insertParam(map.findParamByKey(keySquad),"list of players : vote");
         this->mr->insertParam("zPoints",getsumVotes(map.findParamByKey(keySquad),map.findParamByKey(keyDay)));     
      }
      else{
      //day=""    ***All the votes of the players of the team of all matches*** 
      //SELECT player.*, day_vote.number, day_vote.vote FROM player INNER JOIN day_vote ON day_vote.surname = player.surname WHERE player.squad='Palestina'
         queryToken0="SELECT player.*, day_vote.number, day_vote.vote FROM player INNER JOIN day_vote ON day_vote.surname = player.surname WHERE player.squad='";
         queryToken1=map.findParamByKey(keySquad)+"'";
         query=queryToken0+queryToken1;     
      }
   }
   else if (map.findKeyByKey(keyPlayer) && !map.findKeyByKey(keyDay) && !map.findKeyByKey(keySquad)){
//player = Zagarella  FORSE NON SERVE 
         queryToken0="SELECT * FROM ";
         queryToken1=" WHERE surname IN ('";
         queryToken2=map.findParamByKey(keyPlayer);
         queryToken3="')"; 
         query=queryToken0+keyPlayer+queryToken1+queryToken2+queryToken3;
   }
   else if (map.findKeyByKey(keyPlayer) && map.findKeyByKey(keyDay) && !map.findKeyByKey(keySquad)){
//player = Zagarella ; day = 1 OR day = ""
      if(!map.findParamByKey(keyDay).empty()){
      //day=1     ***Player's vote of the match's day***
      //SELECT player.*, day_vote.number, day_vote.vote FROM player INNER JOIN day_vote ON day_vote.surname = player.surname WHERE day_vote.number=1 AND player.surname='Zagarella'
         queryToken0="SELECT player.*, day_vote.number, day_vote.vote FROM player INNER JOIN day_vote ON day_vote.surname = player.surname WHERE day_vote.number=";
         queryToken1=map.findParamByKey(keyDay)+" AND player.surname='"+map.findParamByKey(keyPlayer)+"'";
         query=queryToken0+queryToken1;       
      }
      else{
      //day=""    ***All player's votes of all matches***
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
            //i=1 is id or login-pass
            resp += re->getString(i);
            // resp = resp + res_meta->getColumnName(i) + ":" + re->getString(i);
            if (i < columns - 1) //i<columns
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
   if(table == "squad"){
      queryToken1 ="(name,owner) VALUE ('";
      query= queryToken0+table+queryToken1+value+queryToken3;
   }
   //player
   else if(table == "player"){
      queryToken1="(squad,surname,role) VALUE ('";
      query = queryToken0+table+queryToken1+value+queryToken3;
   }
   //day  *** insert team of the day ***
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
   if(map.findKeyByKey(keySquad)){
      //UPDATE player_day SET vote = 8 WHERE surname = 'Zagarella'
      query = "UPDATE squad SET setup ='0' WHERE name = '"+map.findParamByKey(keySquad)+"'";
   }
   else if(map.findKeyByKey(keySetup)){
      //http://localhost:8030/PUT?setup=giornata&name=squadname
      query = "UPDATE squad SET setup ='"+map.findParamByKey(keySetup)+"' WHERE name = '"+map.findParamByKey(keySquad)+"'";
   }
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
   //this->mr->insertParam("SETUPPED "+idSquad,"UPDATE");
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

