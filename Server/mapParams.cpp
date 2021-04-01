#include "header/mapParams.h"

mapParams *mapParams::instance=NULL;

mapParams *mapParams::getInstance(){
  if(instance == NULL) instance = new mapParams();
  return instance;
}

mapParams::mapParams(){ 
}

mapParams::~mapParams(){
  instance = NULL;
}

map<string,string> mapParams::getMap(){
return this->params;
}

void mapParams::insertParam(string key, string value){
    pair<string,string> row = make_pair(key,value);
        this->params.insert(row);
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

void findParamByKey(){

}

