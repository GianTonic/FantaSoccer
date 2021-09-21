#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <future>

using namespace std;
extern int actual_day;
void update_day();
void writePointsOnFile(string squadName,string numberDay,string points);
bool is_file_exist(string fileName);