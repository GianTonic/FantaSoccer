#include "modelSql.h"
#include "View.h"
// #include "day_set.h"

using namespace web::http::experimental::listener;

class Controller{
public:
    Controller(modelSql *m, View *v);
    virtual ~Controller();
    void handleGet(http_request request);
    void handlePost(http_request request);
    void handlePut(http_request request);
    void handleDel(http_request request);
    mapParams& splitParamsQuery(string paramsQuery);

private:
    modelSql *m;
    View *v;
    string URL = "http://localhost:8030/";
    http_listener listener;
    mapParams *mp;
};