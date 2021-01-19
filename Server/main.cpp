#include <iostream>
#include <string>
#include <cpprest/http_listener.h>              // HTTP server
#include <cpprest/json.h>


using namespace std;
using namespace web::http;                  // Common HTTP functionality
using namespace web::http::experimental::listener;
namespace json=web::json;

//map<utility::string_t, utility::string_t> dictionary;   //includere la lib in caso

void handleGet(http_request request);

int main(){
string URI="http://localhost:8030/GET";
http_listener listener =  http_listener(URI);
listener.support(methods::GET,&handleGet);
  try{
  listener.open().then([&listener]() {cout<<"starting to listen"<<endl; }).wait();
  while (true);
  }catch (exception const & e){
      wcout << e.what() << endl;
   }
return 0;
}


void handleGet(http_request request)
{
   cout << "Received GET request" << endl;
   //wstring word=L"hello";
   //wcout<<word<<endl;
   auto abs_uri = request.absolute_uri();
   auto params = abs_uri.query().c_str();
   string params_string="";
   params_string = string(params);
   cout<<params_string<<endl;

   auto answer = json::value::object();
   /*Take value from Map
   for (auto const & p : dictionary)
   {
      answer[p.first] = json::value::string(p.second);
   }
   */
   answer["key"] = json::value::string("Value");
   request.reply(status_codes::OK,answer); 
   

   return;
}
