#include <iostream>
#include <fstream>
#include <unordered_map>
#include "RBNode.h"
#include "AVLNode.h"
#include "Incident.h"
using namespace std;
int reformatDate(string str) {
    //this function will change the format of DD-MON-YYYY to YYYYMMDD
    string date;
    //segment the string into day, month, and year
    string day = str.substr(0, 2);
    string month = str.substr(3, 3);
    //swap the string of month out with the number
    for (int i = 0; i < month.length(); i++) {
        //convert all letters to lower case
        month.at(i) = (tolower(month[i]));
    }

    if (month == "jan") {
        month = "01";
    } else if (month == "feb") {
        month = "02";
    } else if (month == "mar") {
        month = "03";
    } else if (month == "apr") {
        month = "04";
    } else if (month == "may") {
        month = "05";
    } else if (month == "jun") {
        month = "06";
    } else if (month == "jul") {
        month = "07";
    } else if (month == "aug") {
        month = "08";
    } else if (month == "sep") {
        month = "09";
    } else if (month == "oct") {
        month = "10";
    } else if (month == "nov") {
        month = "11";
    } else if (month == "dec") {
        month = "12";
    } else {
        cout << "WARNING: Not a valid month. See main.cpp, reformatDate()" << endl;
    }

    string year_temp = str.substr(7);
    string twenty = "20";
    string nineteen = "19";
    string year;
    //append 19 or 20 onto the beginning of the year depending on if the given number starts with 9
    if (year_temp.at(0) == '9') {
        year = nineteen + year_temp;
    } else {
        year = twenty + year_temp;
    }

    date = year + month + day;
    return stoi(date);
}

bool checkState(string input) {
    //this function checks the validity of the input of the states
    for (int i = 0; i < input.length(); i++) {
        if (isdigit(input.at(i))) {
            return false;
        }
    }

    //TODO also have to check if the state is in an ENUM or something?
    //input.at(i) = tolower(input.at(i));
    //TODO then we would have to add each state to some sort of vector I think and like parse the string input
    return true;
}

int main() {
    //menu boolean values
    int input;
    string stateInput;
    bool isRBTree = false;
    bool valid = false;
    //Program introduction
    cout << "Welcome to the Hate Crime dataset! This program allows the user to analyze hate crime incidents";
    cout << " recorded by the FBI from 1991 to 2018. This program allows users to parse the data by";
    cout << " organizing the data based on the state and the date that the hate crime occured.";
    cout << " Behind the scenes, the dataset can be loaded and traversed through either a Red-Black Tree";
    cout << " data structure or an AVL tree data structure, based on the user's discretion.";
    cout << " Thank you and happy parsing!" << endl;

    while (!valid) {
        //Type of tree menu
        cout << "Please select a self-balancing tree data structure to parse: " << endl;
        cout << "1. Red-Black Tree" << endl;
        cout << "2. AVL Tree" << endl;
        cin >> input;

        if (input == 1 || input == 2) {
            valid = true;
            continue;
        }
        cout << "Error: Invalid input." << endl;
    }
    if (input == 1) {
        isRBTree = true;
    }

    //reset valid bool
    valid = false;
    while (!valid) {
        //Number of states menu (//TODO: I don't think we need two menu options here)
        cout << "Please input the names of the states you would like to conduct your search with.";
        cout << "You may input one or multiple states. The format should be as follows: Florida, Georgia";
        cin >> stateInput;

        if (checkState(stateInput)) {
            //the input is valid
            valid = true;
            break;
        }
        cout << "Error: Invalid input." << endl;
    }


    //initialize the hate crime data file
    ifstream file("hate_crime.csv");
    int treeSize = 0;

    //create a red black tree root
    RBNode* RBroot = new RBNode;
    //create an AVL tree root
    AVLNode* AVLroot = new AVLNode;

    //set up the unordered map data structure
    unordered_map<string, RBNode*> RBMap; //nodes are dates (identifier form: YYYMMDD)
    unordered_map<string, AVLNode*> AVLMap; //nodes are dates (identifier form: YYYMMDD)


    //the first 28 lines of input are the column headers which we have no use for so just skip over them
    string firstRow;
    getline(file, firstRow);

    //while(input.good()) { TODO: UNCOMMENT
        //this loop will visit each row of the csv file until the file has ended
        string state;
        for (int i = 1; i <= 8; i++) {
            //this loop will loop through the unnecessary data columns until it reaches the state name column
            getline(file, state, ',');
        }

        string date_str;
        for (int i = 1; i <= 7; i++) {
            //this loop will loop through the unnecessary data columns until it reaches the date column
            getline(file, date_str, ',');
        }

        //reformat the date string from the CSV file to have the format of YYYYMMDD
        int date = reformatDate(date_str);

        //with this date, add an incident class object (TODO INSERT OTHER NECESSARY DATA HERE FOR INCIDENT CLASS)
        Incident newIncident(state, date);

        if (isRBTree) {
            //if the tree specified by the user was a Red Black Tree

            //Make a RB node with this new incident or add it to an existing date's vector
            //TODO RBroot = RBroot->insert();

            //check if the state has been added to the RBMap or AVLMap
            if (RBMap.find(state) == RBMap.end()) {
                treeSize++;
                RBMap[state] = RBroot;
            }
        } else {
            //if the tree specified by the user was an AVL tree

            //Make an AVL node with this new incident or add it to an existing date's vector
            AVLroot = AVLroot->insert(AVLroot, date, newIncident);

            //check if the state has been added to the RBMap or AVLMap
            if (AVLMap.find(state) == AVLMap.end()) {
                treeSize++;
                AVLMap[state] = AVLroot;
            }
        }

    //}

    return 0;
}
