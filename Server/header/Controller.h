#include "modelSql.h"
#include "View.h"

using namespace web::http::experimental::listener;

class Controller{
public:
    Controller(modelSql *m, View *v);
    virtual ~Controller();
    void handleGet(http_request request);
    mapParams splitParamsQuery(string paramsQuery);
    
private:
    modelSql *m;
    View *v;
    string URL = "http://localhost:8030/GET";
    http_listener listener;
};