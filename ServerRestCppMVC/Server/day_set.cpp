#include "header/day_set.h"
int actual_day = 0;
bool append_csv_header = false;


void update_day(){
    if (!is_file_exist("day.txt")) {
        ofstream day_file("day.txt", ios::out); // crea file e setta giorno 1
        actual_day = 1;
        day_file << actual_day;
        day_file.close();
        std::this_thread::sleep_for(chrono::minutes(3));
        update_day();        
    }
    else{
        ifstream day_file("day.txt", ios::in);
        day_file>>actual_day;
        while(actual_day < 39){
            ofstream day_file("day.txt", ios::trunc);
            actual_day += 1;
            day_file << actual_day;
            day_file.close();
            std::this_thread::sleep_for(chrono::minutes(3)); //ogni 4 minuti aggiorno actual_day
        } 
    }    
}

void writePointsOnFile(string squadName,string numberDay,string points){
	if (!is_file_exist("points.csv")) {
        ofstream points_file("points.csv", ios::out); 
        string header = "squad;day;point\n";
        string row = header + squadName+";"+numberDay+";"+points+"\n";
        points_file <<row;
        points_file.close();
    }
    else{
        if(is_file_exist("points.csv")){
            ofstream points_file("points.csv", ios::app);
            string row = squadName+";"+numberDay+";"+points+"\n";
            points_file << row;
            points_file.close();
        }

    }

}

bool is_file_exist(string fileName){
    std::ifstream infile(fileName);
    return infile.good();
}