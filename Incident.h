#pragma once
using namespace std;

class Incident {
public:
    string state;
    int date;

    //default constructir initializes the incident to have essentially an invalid date of 1 (doesn't even adhere to format)
    Incident() : state(""), date(-1) {}
    //constructor takes in input values and assigns them to the member variables
    Incident(string state, int date) {this->state = state; this->date = date;}

};

