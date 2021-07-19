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
>>g++ -g -std=c++11 main.cpp mapParams.cpp  modelSql.cpp Controller.cpp View.cpp day_set.cpp -o server -lboost_system -lcrypto -lssl -lcpprest -lmysqlcppconn -lpthread

#Client Py
Client with GUI written in python v.3

dependencies gui tkinter python
>>pip3 install tk
or
>>apt-get install python3-tk 

dependencies scrapy e xpath
>>pip3 install scrapy
>>pip3 install xpath-py

To execute the code use the following command:
python3 main.py

#Client R
To execute the code use the following command:
>> Rscript plotter.R


