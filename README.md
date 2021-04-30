# ServerRestCpp
Server REST written in c++ using Model View Controller pattern. 
The library used are:

-cpprestsdk (to perform REST request)
https://github.com/Microsoft/cpprestsdk/wiki/Getting-Started-Tutorial

-libmysqlcppconn-dev (to perform mysql call)
https://dev.mysql.com/doc/connector-cpp/8.0/en/connector-cpp-installation-binary.html 
or use this command to install 
>>sudo apt-get install libmysqlcppconn-dev

To compile the code use the following command:
>>g++ -g -std=c++11 main.cpp mapParams.cpp mapResponse.cpp  modelSql.cpp Controller.cpp View.cpp -o server -lboost_system -lcrypto -lssl -lcpprest -lmysqlcppconn
