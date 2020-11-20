#pragma once
using namespace std;
class Incident {
public:
    string state;
    int date;

    //functions
    Incident() : state(""), date(-1) {}
    Incident(string state, int date) {this->state = state; this->date = date;}

};

