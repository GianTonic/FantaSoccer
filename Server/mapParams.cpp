#include "header/mapParams.h"

mapParams *mapParams::instance=NULL;

mapParams *mapParams::getInstance(){
  if(instance == NULL) instance = new mapParams();
  return instance;
}

//private constructor for singleton
mapParams::mapParams(){ 
}

mapParams::mapParams(string s){ 
}

mapParams::~mapParams(){
  instance = NULL;
}

map<string,string> mapParams::getMap(){
return this->params;
}

void mapParams::insertParam(string key, string value){
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

void mapParams::printParams(){
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

string mapParams::findParamByKey(string key){
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

void mapParams::clearMap(){
  this->params.clear();
}
