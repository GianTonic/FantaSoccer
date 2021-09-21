#include "header/mapParams.h"

mapParams::mapParams(){ 
}


mapParams::~mapParams(){
}

map<string,string> mapParams::getMap(){
return this->params;
}

void mapParams::insertParam(string key, string value){
    size_t index = 0;
    while (value.find(";")) {   //; o %3B
     /* Locate the substring to replace. */
      index = value.find(";", index); //%3B
      if (index == std::string::npos) break;
     /* Make the replacement. */
      value.replace(index, 1, "','");  //3
     /* Advance index forward so the next iteration doesn't pick it up as well. */
      index += 1;  //3
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
string value="";
  for (iter = this->params.begin(); iter != this->params.end(); ++iter){
    if (iter->first == key){
        return iter->second;
    }
    else  
         value="key not found";
  }
  return value;
}

bool mapParams::findKeyByKey(string key){
map<string, string>::iterator iter;
bool var;
  for (iter = this->params.begin(); iter != this->params.end(); ++iter){
    if (iter->first == key){
      return true;
    }
    else  
      var = false;
  }
  return var;
}

string mapParams::returnKey(){
map<string, string>::iterator iter;
pair<string,string> p;
string v;
  for (iter = this->params.begin(); iter != this->params.end(); ++iter){
    if (iter->first != ""){
        v=iter->first;
        return v;
    }
    else  
        return "Key is empty";
  }
  return "Map is empty";
}

void mapParams::clearMap(){
  this->params.clear();
}
