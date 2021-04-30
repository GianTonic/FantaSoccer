#include <iostream>
#include <string>
#include <cpprest/http_listener.h>              // HTTP server
#include <cpprest/json.h>

using namespace std;
using namespace web::http;                  // Common HTTP functionality
namespace json=web::json;

class View{
public:
    View();
    virtual ~View();
    void response(http_request request, map<string, string> map);
};