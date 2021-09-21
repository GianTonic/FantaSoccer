GitHub repository:
https://github.com/GianTonic/FantaSoccer

# FantaSoccer 1.0
Client-server application to manage a fanta-football tournament. The languages used are: python, C++, R.

# Client Py
Client with GUI written in python v.3.
The client simulates access to the application via login. There are two type of user: 
-Admin can create teams for each partecipant in the tournament, add players for each team and update the votes/score via website scraping.
-Users (team owners) can publish the team every matchday of Serie A.

dependencies gui tkinter python
>>pip3 install tk
or
>>apt-get install python3-tk 

dependencies scrapy e xpath
>>pip3 install scrapy
>>pip3 install xpath-py

To execute the code use the following command:
python3 main.py

# Server C++
Server REST written in C ++ using the Model View Controller pattern. The server exposes REST end-points to listen for any incoming request from the py client. The server manages the requests and executes sql queries on mysql relational db to process data. 
The server updates a .csv file to keep track of the score of all the teams for each day of the tournament.

The library used are:
-cpprestsdk (to perform REST request)
https://github.com/Microsoft/cpprestsdk/wiki/Getting-Started-Tutorial

-libmysqlcppconn-dev (to perform mysql call)
https://dev.mysql.com/doc/connector-cpp/8.0/en/connector-cpp-installation-binary.html 
or use this command to install 
>>sudo apt-get install libmysqlcppconn-dev

To compile the code use the following command:
>>g++ -g -std=c++11 main.cpp mapParams.cpp  modelSql.cpp Controller.cpp View.cpp day_set.cpp -o server -lboost_system -lcrypto -lssl -lcpprest -lmysqlcppconn -lpthread

# Scrip R
R script to read from csv files and represent data on a .png file

To execute the code use the following command:
>> Rscript plotter.R


