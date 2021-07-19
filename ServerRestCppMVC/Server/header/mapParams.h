#include <iostream>
#include <string>
#include <map>  
#include <vector>

using namespace std;

class mapParams{
public:    
    mapParams();
    virtual ~mapParams();
    void insertParam(string key, string value);
    void printParams();
    string findParamByKey(string key);    
    bool findKeyByKey(string key);
    string returnKey();
    map<string,string> getMap();
    void clearMap();

private:
    map<string,string> params; 
    
};



