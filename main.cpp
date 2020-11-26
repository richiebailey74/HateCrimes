#include <iostream>
#include <fstream>
#include <set>
#include <unordered_map>
#include <chrono>
#include <iomanip>
#include "RBNode.h"
#include "AVLNode.h"
#include "Incident.h"
typedef std::chrono::high_resolution_clock timer;
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

void initializeTrees(fstream& file, unordered_map<string, RBNode*> rbMap, unordered_map<string, AVLNode*> avlMap) {

    //the first 28 lines of input are the column headers which we have no use for so just skip over them
    string firstRow;
    getline(file, firstRow);


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

}

void initializeMaps(unordered_map<string, AVLNode*>& AVLMap, unordered_map<string, RBNode*>& RBMap) {
    //this function will initialize the state maps for both AVL and RB trees
    
    //create an array of states
    string stateArr[] = { "Alabama", "Alaska", "Arizona", "Arkansas", "California", "Colorado", "Connecticut", "Delaware", "Florida", "Georgia",
                        "Hawaii", "Idaho", "Illinois", "Indiana", "Iowa", "Kansas", "Kentucky", "Louisiana", "Maine", "Maryland", "Massachusetts",
                        "Michigan", "Minnesota", "Mississippi", "Missouri", "Montana", "Nebraska", "Nevada", "New Hampshire", "New Jersey",
                        "New Mexico", "New York", "North Carolina", "North Dakota", "Ohio", "Oklahoma", "Oregon", "Pennsylvania", "Rhode Island",
                        "South Carolina", "South Dakota", "Tennessee", "Texas", "Utah", "Vermont", "Virginia", "Washington", "West Virginia",
                        "Wisconsin", "Wyoming" };
    
    //initialize the maps to hold the states as the keys
    for(int i = 0; i < stateArr.length(); i++) {
        AVLMap[stateArr[i]] = nullptr;
        RBMap[stateArr[i]] = nullptr;
    }
}

int main() {
    //timer variable
    typedef std::chrono::high_resolution_clock timer;
    
    //menu boolean values
    int input;
    
    bool valid = false;

    //initialize the hate crime data file
    ifstream file("hate_crime.csv");
    int treeSize = 0;

    //set up the unordered map data structure
    unordered_map<string, RBNode*> RBMap; //nodes are dates (identifier form: YYYYMMDD)
    unordered_map<string, AVLNode*> AVLMap; //nodes are dates (identifier form: YYYYMMDD)
    initializeMaps();

    
    //create a red black tree root
    RBNode* RBroot = new RBNode;
    //create an AVL tree root
    AVLNode* AVLroot = new AVLNode;
    
    //Program introduction
    cout << "Welcome to the Hate Crime dataset! This program allows the user to analyze hate crime incidents";
    cout << " recorded by the FBI from 1991 to 2018. This program allows users to parse the data by";
    cout << " organizing the data based on the state and the date that the hate crime occured.";
    cout << " Behind the scenes, the dataset can be loaded and traversed through either a Red-Black Tree";
    cout << " data structure or an AVL tree data structure, based on the user's discretion.";
    cout << " Thank you and happy parsing!" << endl;


    //menu function to print
    bool quit = false;
    string stateInput = "";
    int index = 0;
    
    while (!quit) {
        //menu function call
        //take in comma separated state list
        cout << "Please input the names of the states you would like to conduct your search with.";
        cout << "You may input one or multiple states. The format should be as follows: Florida, Georgia" << endl;
        bool inputValid = true;
        set<string> searchStates;
        
        getline(cin, stateInput);
        string state = "";

        while(inputValid && stateInput != "") {
            state = stateInput.substr(0, stateInput.find(','));
            if (stateInput.find(',') == string::npos) {
                stateInput = "";
            }
            else {
                stateInput = stateInput.substr(stateInput.find(',') + 2);
            }
                    
            if (checkState(stateInput)) {
                //cout << ++index << ". " << state << endl;
                searchStates.insert(stateInput);
            }
            else {
                inputValid = false;
                //empty searchStates
                searchStates.clear();
                //call error statement

            }
            if (state == "quit") {
                quit = true;
                inputValid = false;
            }
        }
        
        //Adding beginning and end timers for each tree
        
        auto startAVL = timer::now();
        //build AVl tree                                                                                                                                                                                                                                                                                                                                                                                  
        auto endAVL = timer::now();
        chrono::duration<double> elapsedTime = endAVL - startAVL;
        cout << setprecision(5) << "Time taken to build AVL tree " << elapsedTime.count() << setprecision(5) << " seconds" << endl;

        auto startRB = timer::now();
        //build RB tree
        auto endRB = timer::now();
        elapsedTime = endRB - startRB;
        cout << setprecision(5) << "Time taken to build RB tree " << elapsedTime.count() << " seconds" << endl;


        if (inputValid) {
            for (auto iter = searchStates.begin(); iter != searchStates.end(); iter++) {
                //This is where we will do our statistical analysis
            }

            cout << "Would you like to compare two specific states? (Y/N)" << endl;

            string compare = "";

            cin >> compare;
            
            if (compare == "Y" || compare == "y") {
                string state1;
                string state2;
                cout << "Enter State 1: ";
                cin >> state1;
                cout << endl << "Enter State 2: ";
                cin >> state2;
                cout << endl;

                if (searchStates.find(state1) != searchStates.end() && searchStates.find(state1) != searchStates.end()) {
                    //compare these two specific states
                }
                else {
                    cout << "Error: The two selected states were not a part of the current analysis." << endl;
                }


            }
           

            cout << "Would you like to write the statistical data to a file? (Y/N)" << endl;
            cin >> compare;

            if (compare == "Y" || compare == "y") {
               //write output file here
            }
        }
        

        
    }
    



    return 0;
}
