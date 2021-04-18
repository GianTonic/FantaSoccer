#include <iostream>
#include <string>
#include <map>  

using namespace std;

class mapParams{
public:    
    static mapParams *getInstance();
    mapParams(string s);
    virtual ~mapParams();
    void insertParam(string key, string value);
    void printParams();
    string findParamByKey(string key);    
    map<string,string> getMap();
    void clearMap();

private:
    static mapParams *instance;
    mapParams();
    map<string,string> params; 
    
};



