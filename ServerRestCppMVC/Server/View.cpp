#include "header/View.h"

View::View(){
};

View::~View(){
};

void View::response(http_request request, map<string, string> map)
{
    auto answer = json::value::object();
    for (auto const & p : map){
        answer[p.first] = json::value::string(p.second);
    }
    request.reply(status_codes::OK,answer); 
    return;
}