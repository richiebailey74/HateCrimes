#include <iostream>
#include <fstream>
#include <set>
#include <unordered_map>
#include <chrono>
#include <iomanip>
#include "treenode.h"
#include "treeNode.h"
#include "RBtree.h"
#include "AVLtree.h"
#include "Incident.h"
#include <string>
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
        cout << "WARNING: Not a valid month." << endl;
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

int reformatUserDate(string str) {
    //this function will change the format of DD-MM-YYYY to YYYYMMDD
    string date;
    //segment the string into day, month, and year
    string day = str.substr(0, 2);
    cout << "day is " << day << endl;
    string month = str.substr(3, 2);
    cout << "month is " << month << endl;
    string year = str.substr(6);
    cout << "year is " << year << endl;
    string twenty = "20";
    string nineteen = "19";

    date = year + month + day;
    return stoi(date);
}

bool checkState(string stateArr[], string input) {
    //this function checks the validity of the input of the states

    //convert all the letters in the input to lowercase
    for (int i = 0; i < input.length(); i++) {
        input.at(i) = tolower(input.at(i));
    }

    for (int i = 0; i < stateArr->length(); i++) {
        //checks if input equals one of the states in the array
        if (input == stateArr[i]) {
            return true;
        }
    }
    return false;
}

/*void initializeTrees(fstream& file, unordered_map<string, RBNode*> rbMap, unordered_map<string, AVLNode*> avlMap) {

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

} */

void initializeMaps(string stateArr[], unordered_map<string, AVLtree*>& AVLMap, unordered_map<string, RBtree*>& RBMap) {
    //this function will initialize the state maps for both AVL and RB trees

    //initialize the maps to hold the states as the keys
    for(int i = 0; i < stateArr->length(); i++) {
        AVLMap[stateArr[i]] = nullptr;
        RBMap[stateArr[i]] = nullptr;
    }
}

int main() {
    //timer variable
    typedef std::chrono::high_resolution_clock timer;
    
    //create an array of states
    string stateArr[] = { "alabama", "alaska", "arizona", "arkansas", "california", "colorado", "connecticut", "delaware", "florida", "georgia",
                          "hawaii", "idaho", "illinois", "indiana", "iowa", "kansas", "kentucky", "louisiana", "maine", "maryland", "massachusetts",
                          "michigan", "minnesota", "mississippi", "missouri", "montana", "nebraska", "nevada", "new hampshire", "new jersey",
                          "new mexico", "new york", "north carolina", "north dakota", "ohio", "oklahoma", "oregon", "pennsylvania", "rhode island",
                          "south carolina", "south dakota", "tennessee", "texas", "utah", "vermont", "virginia", "washington", "west virginia",
                          "wisconsin", "wyoming" };

    //menu boolean values
    int input;

    bool valid = false;

    //initialize the hate crime data file
    ifstream file("hate_crime.csv");
    int treeSize = 0;

    //set up the unordered map data structure
    unordered_map<string, AVLtree*> AVLMap; //nodes are dates (identifier form: YYYYMMDD)
    unordered_map<string, RBtree*> RBMap; //nodes are dates (identifier form: YYYYMMDD)
    initializeMaps(stateArr, AVLMap, RBMap);

    //if we're going to be adding multiple trees to the map, I'm pretty sure we'll have to move these declaration but I'm not entirely sure how the interface works
    //we might need another loop if they're going to be inserting multiple states so we can have separate tree objects
    //create a red black tree root
    RBtree* RBTREE = new RBtree;
    //create an AVL tree root
    AVLtree* AVLTREE = new AVLtree;
    
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
                    
            if (checkState(stateArr, stateInput)) {
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
        int startDate;
        int endDate;
        string rangeChoice = "";
        cin >> rangeChoice;
        if (rangeChoice == "Y" || rangeChoice == "y") {
            //Lets them pick their own dates
            cout << "Please enter the start date in the format DD-MM-YYYY: " << endl;
            string start;
            cin >> start;
            startDate = reformatUserDate(start);
            cout << "Please enter the end date in the format DD-MM-YYYY: " << endl;
            string end;
            cin >> end;
            endDate = reformatUserDate(end);
        }
        else {
            startDate = 19910101;
            endDate = 20183112;
        }
        
        //building AVL tree with csv data
        auto startAVL = timer::now();
        
        //the first 28 lines of input are the column headers which we have no use for so just skip over them
        string blank;
        getline(file, blank);
        
        while(!file.eof()) {
            //this loop will visit each row of the csv file until the file has ended
            for (int i = 1; i <= 8; i++) {
                //this loop will loop through the unnecessary data columns until it reaches the state name column
                getline(file, state, ',');
            }
            
            bool found = false;
            //check if the state is in the searchStates vector (move to next row)
            for (int i = 0; i < searchStates.size(); i++) {
                if (searchStates.find(state) != searchStates.end()) {
                    //if the state has been specified
                    found = true;
                }
            }
            if (!found) {
                //if the current state was not found in the searchStates vector, move onto next row
                getline(file, blank);
                continue;
            }

            string date_str;
            for (int i = 1; i <= 7; i++) {
                //this loop will loop through the unnecessary data columns until it reaches the date column
                getline(file, date_str, ',');
            }

            //reformat the date string from the CSV file to have the format of YYYYMMDD
            int date = reformatDate(date_str);
            
            if (date < startDate || date > endDate) {
                //date is out of range
                getline(file, blank);
                continue;
            }

            //with this date, add an incident class object (TODO INSERT OTHER NECESSARY DATA HERE FOR INCIDENT CLASS)
            Incident* incidentObj1 = new Incident(state, date); //will work as long as the state name and date are extracted correct
            
            bool incidentPresent = AVLTREE->searchAddIncident(incidentObj1);
            
            if(incidentPresent == false) {
                AVLTREE->insertNode(incidentObj1->date, incidentObj1);
            }
            
            //pass into check function (check if date is there, push back. if date is not there, add new node)
                //if true, find existing tree node and push to vector (does in the search function automatically)
                //if false, insert a new node and start rotations from there (push back vector too)
            
            
        }                                                                                                                                                                                                                                                                                                                                                                                
        auto endAVL = timer::now();
        chrono::duration<double> elapsedTime = endAVL - startAVL;
        cout << setprecision(5) << "Time taken to build AVL tree " <<  setprecision(5) << elapsedTime.count() << " seconds" << endl;

        //building RB tree with csv data
        
        //reset the ifstream file object
        file.clear();
        file.seekg(0, ios::beg);
        
        auto startRB = timer::now();
        
        //the first 28 lines of input are the column headers which we have no use for so just skip over them
        getline(file, blank);
        
        while(!file.eof()) {
            //this loop will visit each row of the csv file until the file has ended
            string state;
            for (int i = 1; i <= 8; i++) {
                //this loop will loop through the unnecessary data columns until it reaches the state name column
                getline(file, state, ',');
            }
            
            bool found = false;
            //check if the state is in the searchStates vector (move to next row)
            for (int i = 0; i < searchStates.size(); i++) {
                if (searchStates.find(state) != searchStates.end()) {
                    //if the state has been specified
                    found = true;
                }
            }
            if (!found) {
                //if the current state was not found in the searchStates vector, move onto next row
                getline(file, blank);
                continue;
            }

            string date_str;
            for (int i = 1; i <= 7; i++) {
                //this loop will loop through the unnecessary data columns until it reaches the date column
                getline(file, date_str, ',');
            }

            //reformat the date string from the CSV file to have the format of YYYYMMDD
            int date = reformatDate(date_str);
            
            if (date < startDate || date > endDate) {
                //date is out of range
                getline(file, blank);
                continue;
            }

            //with this date, add an incident class object (TODO INSERT OTHER NECESSARY DATA HERE FOR INCIDENT CLASS)
            Incident* incidentObj2 = new Incident(state, date);
            
            bool incidentPresent = RBTREE->searchAddIncident(incidentObj2);
            
            if(incidentPresent == false) {
                RBTREE->insertNode(incidentObj2->date, incidentObj2);
            }
            
            //pass into check function (check if date is there, push back. if date is not there, add new node)
                //if true, find existing tree node and push to vector (done in search functionality if appliceable)
                //if false, insert a new node and start rotations from there (push back vector too)
            
            
        }                           
        auto endRB = timer::now();
        elapsedTime = endRB - startRB;
        cout << setprecision(5) << "Time taken to build RB tree " << elapsedTime.count() << " seconds" << endl;

        if (inputValid) {
            for (auto iter = searchStates.begin(); iter != searchStates.end(); iter++) {
                //This is where we will do our statistical analysis
                //This needs to be stored in a data structure so that it can be written to an output file afterwards
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
                ofstream outputFile;
                cout << "What would you like to name the file? ";
                string fileName;
                cin >> fileName;

                outputFile.open(fileName + ".csv");
                //need to know structural of analysis to design the structure of the csv file
            }
        }  
    }
    return 0;
}
