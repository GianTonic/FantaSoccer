#include <iostream>
#include <string>
#include <map>  

using namespace std;

class mapResponse{
public:    
    static mapResponse *getInstance();
    virtual ~mapResponse();
    void insertParam(string key, string value);
    void printResponse();
    string findParamByKey(string key);    
    map<string,string> getMap();
    void clearMap();

private:
    static mapResponse *instance;
    mapResponse();
    map<string,string> params; 
    
};



