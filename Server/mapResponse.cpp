#include "header/mapResponse.h"

mapResponse *mapResponse::instance=NULL;

mapResponse *mapResponse::getInstance(){
  if(instance == NULL) instance = new mapResponse();
  return instance;
}

//private constructor for singleton
mapResponse::mapResponse(){ 
}


mapResponse::~mapResponse(){
  instance = NULL;
}

map<string,string> mapResponse::getMap(){
return this->params;
}

void mapResponse::insertParam(string key, string value){
    size_t index = 0;
    while (value.find("%3B")) {
     /* Locate the substring to replace. */
     index = value.find("%3B", index);
     if (index == std::string::npos) break;

     /* Make the replacement. */
     value.replace(index, 3, "','");

     /* Advance index forward so the next iteration doesn't pick it up as well. */
     index += 3;
    }
    pair<string,string> row = make_pair(key,value);
    this->params.insert(row);
    return;
}

void mapResponse::printResponse(){
map<string, string>::iterator iter;
string strToReturn;
  for (iter=this->params.begin(); iter != this->params.end(); ++iter) {
           strToReturn.append(iter->first);
           strToReturn.append(":");
           strToReturn.append(iter->second);
           strToReturn.append("\n");
  }
    cout<<strToReturn<<endl;
}

string mapResponse::findParamByKey(string key){
map<string, string>::iterator iter;
  for (iter = this->params.begin(); iter != this->params.end(); ++iter){
    if (iter->first == key){
        return iter->second;
    }
    else  
        return iter->second="key not found";
  }
  return "";
}

void mapResponse::clearMap(){
  this->params.clear();
}