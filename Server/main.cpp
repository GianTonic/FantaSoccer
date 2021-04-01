#include <iostream>
#include <string>
#include <cpprest/http_listener.h>              // HTTP server
#include <cpprest/json.h>
#include "header/mapParams.h"
#include "header/modelSql.h"


using namespace std;
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::experimental::listener;
namespace json=web::json;

//map<utility::string_t, utility::string_t> dictionary;   //includere la lib in caso

void handleGet(http_request request);
mapParams splitParamsQuery(string params);
void response(http_request request, map<string,string> map);

int main(){
string URI="http://localhost:8030/GET";
http_listener listener =  http_listener(URI);
listener.support(methods::GET,&handleGet);
  try{
  listener.open().then([&listener]() {cout<<"starting to listen"<<endl<<"..."<<endl<<endl; }).wait();
  while (true);
  }catch (exception const & e){
      wcout << e.what() << endl;
   }

return 0;
}

mapParams splitParamsQuery(string paramsQuery){
   string delimiter_a= "=";
   string delimiter_b= "&";
   size_t pos = 0; 
   string token_k;
   //string token_rem;
   string token_v;
   mapParams *map = mapParams::getInstance();
   //cout<<paramsQuery<<endl;
   //funzione find restituisce la posizione della prima occorrenza di str nella stringa o npos se la stringa non viene trovata.
   //La substr(size_t pos = 0, size_t n = npos)funzione restituisce una sottostringa dell'oggetto, a partire dalla posizione pos e dalla lunghezza npos
   //Se hai più delimitatori, dopo aver estratto un token, puoi rimuoverlo (delimitatore incluso) per procedere con le estrazioni successive (se vuoi conservare la stringa originale, usa semplicemente s = s.substr(pos + delimiter.length());)
   if((pos=paramsQuery.find(delimiter_a))!= std::string::npos){
      token_k = paramsQuery.substr(0, pos);
      //cout<< token_k << endl;
      paramsQuery.erase(0, pos + delimiter_a.length());
      //cout<<"token_remaining: "<< token_rem << endl;
      token_v = paramsQuery.substr(0, pos);
      map->insertParam(token_k,token_v);
      //cout << token_v << endl;
         if((pos=paramsQuery.find(delimiter_b))!= std::string::npos){       
         //token_rem=paramsQuery.erase(0, pos + delimiter_b.length());
         //cout<<"token_remaining: "<< token_rem << endl;
            splitParamsQuery(paramsQuery.erase(0, pos + delimiter_b.length()));      
         }
   }
   return *map; 
}

void response(http_request request, map<string,string> map){
   auto answer = json::value::object();
   for (auto const & p : map){
      answer[p.first] = json::value::string(p.second);
   }
  // answer["key"] = json::value::string("Value");
   request.reply(status_codes::OK,answer); 
   return;
}

void handleGet(http_request request)
{
   cout << "Received GET request" << endl;
   //wstring word=L"hello";
   //wcout<<word<<endl;
   auto abs_uri = request.absolute_uri();
   auto params = abs_uri.query().c_str();
   string params_string="";
   params_string = string(params);
   mapParams map = splitParamsQuery(params_string);
   map.printParams();
   response(request, map.getMap());
   modelSql *ms = new modelSql;
   return;
}

