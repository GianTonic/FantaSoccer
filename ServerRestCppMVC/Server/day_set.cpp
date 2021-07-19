#include "header/day_set.h"
int actual_day = 0;

void day_check(){
    fstream day_file;
	day_file.open("day.txt", ios::in);
	if (!day_file) {
        ofstream day_file("day.txt", ios::out); // crea file e setta giorno 1
        actual_day = 1;
        day_file << actual_day;
    }
    else {
        int temp;
        day_file >> temp;
        if(temp<actual_day){ //che lo è sicuramente ogni 15min
            ofstream day_file("day.txt", ios::trunc); //sostituisco il vecchio giorno con il nuovo
            day_file << actual_day;
        }
    }
    day_file.close();
}

void update_day(){
        while(actual_day < 39){
            actual_day += 1;
            day_check();
            std::this_thread::sleep_for(chrono::minutes(10)); //ogni 15 minuti aggiorno day
        }
}