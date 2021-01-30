#include <iostream>
#include <string>
#include <map>  

using namespace std;

class mapParams{
public:    
    static mapParams *getInstance();
    virtual ~mapParams();
    void insertParam(string key, string value);
    void printParams();
    void findParamByKey();    
    map<string,string> getMap();

private:
    static mapParams *instance;
    mapParams();
    map<string,string> params; 

};



