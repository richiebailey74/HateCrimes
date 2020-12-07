#include <iostream>
#include <fstream>
#include <set>
#include <unordered_map>
#include <chrono>
#include <iomanip>
#include <math.h>
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
    for (unsigned int i = 0; i < month.length(); i++) {
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
        cout << "WARNING: " << month << " is not a valid month." << endl;
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

bool validDate(int& startDate, int& endDate) {
    if (startDate > endDate) {
        cout << "Invalid date range." << endl;
        return false;
    }
    if (startDate < 19910101 || startDate > 20181231) {
        cout << "Your start date is out of range. The program will default to use the start date of the dataset." << endl;
        startDate = 19910101;
    }
    if (endDate < 19910101 || endDate > 20181231) {
        cout << "Your end date is out of range. The program will default to use the end date of the dataset." << endl;
        endDate = 20181231;
    }
    return true;

}

bool checkState(string stateArr[], string input) {
    //this function checks the validity of the input of the states

    //convert all the letters in the input to lowercase
    for (unsigned int i = 0; i < input.length(); i++) {
        input.at(i) = tolower(input.at(i));
    }

    for (int i = 0; i < 50; i++) {
        //checks if input equals one of the states in the array
        if (input == stateArr[i]) {
            return true;
        }
    }
    return false;
}

float tTest(float mean1, float sd1, int n1, float mean2, float sd2, int n2) {
    //this function calculates the t test between two data sets
    float t_test = (mean1 - mean2) / sqrt((sd1 * sd1) / n1 + (sd2 * sd2) / n2);
    return t_test;
}

void initializeMaps(string stateArr[], unordered_map<string, AVLtree*>& AVLMap, unordered_map<string, RBtree*>& RBMap) {
    //this function will initialize the state maps for both AVL and RB trees

    //initialize the maps to hold the states as the keys
    for(unsigned int i = 0; i < 50; i++) {
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
    bool valid = false;

    //initialize the hate crime data file
    ifstream file("hate_crime.csv");
    int treeSize = 0;

    //set up the unordered map data structure
    unordered_map<string, AVLtree*> AVLMap; //nodes are dates (identifier form: YYYYMMDD)
    unordered_map<string, RBtree*> RBMap; //nodes are dates (identifier form: YYYYMMDD)
    initializeMaps(stateArr, AVLMap, RBMap);

    //Program introduction
    cout << "Welcome to the Hate Crime dataset!\n" << endl;
    
    cout << "This program allows the user to analyze hate crime incidents\n"  
         << "recorded by the FBI from 1991 to 2018. This program allows\n"
         << "users to parse the data by organizing the data based on the\n"
         << "state and the date that the hate crime occured. Behind the\n"
         << "scenes, the dataset can be loaded and traversed using either\n"
         << "a Red-Black Tree data structure or an AVL tree data structure.\n" << endl;
    
    cout << "Thank you and happy parsing!\n" << endl;

    //menu function to print
    bool quit = false;
    int index = 0;

    while (!quit) {
        //menu function call
        //take in comma separated state list
        cout << "Please input the names of the states you would like to\n"
             << "conduct your search with. You may input one or multiple\n"
             << "states. The format should be as follows: Florida, Georgia\n" << endl;

        cout << "States: ";
        bool inputValid = true;
        set<string> searchStates;

        string stateInput = "";
        
        getline(cin, stateInput);
        string state = "";
        while (inputValid && stateInput != "") {
            state = stateInput.substr(0, stateInput.find(','));
            if (stateInput.find(',') == string::npos) {
                stateInput = "";
            }
            else {
                stateInput = stateInput.substr(stateInput.find(',') + 2);
            }

            if (checkState(stateArr, state)) {

                for(int i = 0; i < state.length(); i++) {
                    //convert state to lower case
                    state.at(i) = tolower(state.at(i));
                }
                searchStates.insert(state);

                AVLtree* temp1 = new AVLtree();
                AVLMap[state] = temp1;

                RBtree* temp2 = new RBtree();
                RBMap[state] = temp2;
            }
            else {
                inputValid = false;
                //empty searchStates
                searchStates.clear();
                for (auto iter = searchStates.begin(); iter != searchStates.end(); iter++) {
                    //reset AVL and RB maps
                    AVLMap[*iter] = nullptr;
                    RBMap[*iter] = nullptr;
                }
                //call error statement
                cout << "Error: Invalid state input." << endl;
            }
            if (state == "quit") {
                quit = true;
                inputValid = false;
            }
        }
        cout << endl;

        bool selectRange = false;
        int startDate;
        int endDate;
        //cout << inputValid << endl
        if (inputValid) {
            cout << "Would you like to conduct your search within a range of specific years? (Y/N)" << endl;
            string rangeChoice = "";
            cin >> rangeChoice;
            if (rangeChoice == "Y" || rangeChoice == "y") {
                selectRange = true;
                do {
                    //Lets them pick their own dates
                    cout << "Please enter the beginning year (YYYY): ";
                    string start;
                    cin >> start;
                    start += "0101";
                    startDate = stoi(start);
                    cout << "Please enter the ending year (YYYY): ";
                    string end;
                    cin >> end;
                    end += "1231";
                    endDate = stoi(end);
                } while (!validDate(startDate, endDate));
            }
            else {
                startDate = 19910101;
                endDate = 20183112;
            }
        }

        cout << endl;
    
        if (inputValid) {
            cout << "Beginning to build the AVL tree..." << endl;
            //building AVL tree with csv data
            string tableState = "";
            auto startAVL = timer::now();
            int loadingIndex = 0;
            //the first 28 lines of input are the column headers which we have no use for so just skip over them
            string blank;
            getline(file, blank);

            int i = 1;
            while (!file.eof()) {
                //this loop will visit each row of the csv file until the file has ended
                for (int i = 0; i < 8; i++) {
                    //this loop will loop through the unnecessary data columns until it reaches the state name column
                    if (!getline(file, tableState, ',')) {
                        break;
                    }
                    if (i == 3) {
                        //if it is in the column with a lot of commas
                        while (tableState.at(tableState.length() - 1) != '\"' ) {
                            getline(file, tableState, ',');
                        }
                    }
                }
                if (file.eof()) {
                    break;
                }
                tableState = tableState.substr(1, tableState.length() - 2); 
                for(int i = 0; i < tableState.length(); i++) {
                    //convert state to lower case
                    tableState.at(i) = tolower(tableState.at(i));
                }
                
                if (loadingIndex++ == 25000) {
                    cout << "..." << endl;
                    loadingIndex = 0;
                }
                if (searchStates.find(tableState) == searchStates.end()) {
                    //if the current state was not found in the searchStates vector, move onto next row
                    getline(file, blank);
                    continue;
                }
                
                string date_str;
                for (int i = 0; i < 5; i++) {
                    //this loop will loop through the unnecessary data columns until it reaches the date column
                    getline(file, date_str, ',');
                    if (i == 3) {
                        //if it is in the column with a lot of commas
                        while (date_str.at(date_str.length() - 1) != '\"' ) {
                            getline(file, date_str, ',');
                        }
                    }
                }

                //reformat the date string from the CSV file to have the format of YYYYMMDD
                int date = reformatDate(date_str);

                if (date < startDate || date > endDate) {
                    //date is out of range
                    getline(file, blank);
                    continue;
                }

                //with this date, add an incident class object (TODO INSERT OTHER NECESSARY DATA HERE FOR INCIDENT CLASS)
                Incident* incidentObj1 = new Incident(tableState, date); //will work as long as the state name and date are extracted correct

                //pass into check function (check if date is there, push back. if date is not there, add new node)
                bool incidentPresent = AVLMap[tableState]->searchAddIncident(incidentObj1);

                //if false, insert a new node and start rotations from there (push back vector too)
                if (incidentPresent == false) {
                    AVLMap[tableState]->insertNode(incidentObj1->date, incidentObj1);
                }
                getline(file, blank);
            }
            auto endAVL = timer::now();
            cout << "Finished building the AVL tree." << endl;
            chrono::duration<double> elapsedTime = endAVL - startAVL;
            cout << setprecision(5) << "Time taken to build the AVL tree " << setprecision(5) << elapsedTime.count() << " seconds" << endl << endl;

            //building RB tree with csv data

            //reset the ifstream file object
            file.clear();
            file.seekg(0, ios::beg);
            tableState = "";
            loadingIndex = 0;
            cout << "Beginning to build the Red-Black tree..." << endl;
            auto startRB = timer::now();

            //the first 28 lines of input are the column headers which we have no use for so just skip over them
            getline(file, blank);

            while (!file.eof()) {
                //this loop will visit each row of the csv file until the file has ended
                for (int i = 1; i < 8; i++) {
                    //this loop will loop through the unnecessary data columns until it reaches the state name column
                    if (!getline(file, tableState, ',')) {
                        break;
                    }
                    if (i == 3) {
                        //if it is in the column with a lot of commas
                        while (tableState.at(tableState.length() - 1) != '\"' ) {
                            getline(file, tableState, ',');
                        }
                    }
                }
                if (file.eof()) {
                    break;
                }
                
                tableState = tableState.substr(1, tableState.length() - 1);
                for(int i = 0; i < tableState.length(); i++) {
                    //convert state to lower case
                    tableState.at(i) = tolower(tableState.at(i));
                }
                if (loadingIndex++ == 25000) {
                    cout << "..." << endl;
                    loadingIndex = 0;
                }
                if (searchStates.find(tableState) == searchStates.end()) {
                    //if the current state was not found in the searchStates vector, move onto next row
                    getline(file, blank);
                    continue;
                }

                string date_str;
                for (int i = 0; i < 5; i++) {
                    //this loop will loop through the unnecessary data columns until it reaches the date column
                    getline(file, date_str, ',');
                    if (i == 3) {
                        //if it is in the column with a lot of commas
                        while (date_str.at(date_str.length() - 1) != '\"' ) {
                            getline(file, date_str, ',');
                        }
                    }
                }

                //reformat the date string from the CSV file to have the format of YYYYMMDD
                int date = reformatDate(date_str);

                if (date < startDate || date > endDate) {
                    //date is out of range
                    getline(file, blank);
                    continue;
                }

                //with this date, add an incident class object (TODO INSERT OTHER NECESSARY DATA HERE FOR INCIDENT CLASS)
                Incident* incidentObj2 = new Incident(tableState, date);

                //pass into check function (check if date is there, push back. if date is not there, add new node)
                bool incidentPresent = RBMap[tableState]->searchAddIncident(incidentObj2);

                //if false, insert a new node and start rotations from there (push back vector too)
                if (incidentPresent == false) {
                    RBMap[tableState]->insertNode(incidentObj2->date, incidentObj2);
                }
            }
            auto endRB = timer::now();
            cout << "Finished building Red-Black tree." << endl;
            elapsedTime = endRB - startRB;
            cout << setprecision(5) << "Time taken to build the RB tree " << elapsedTime.count() << " seconds" << endl << endl;

            int crimeCount;
            float mean = 0.0;

            unordered_map<string, vector<float>> csvOutput;

            if (inputValid) {
                //stats for AVL tree
                startAVL = timer::now();
                for (auto iter = searchStates.begin(); iter != searchStates.end(); iter++) {
                    //Begin statistical analysis
                    string sName = *iter;
                    sName.at(0) = tolower(sName.at(0));
                    //calculate total number of hate crimes of each state (aka how many Incident objects are in its tree)
                    crimeCount = AVLMap[sName]->getTreeSize();

                    //calculate mean hate crimes of each state per year (average #crimes/year)
                    int startYear = startDate / 10000;
                    int endYear = endDate / 10000;
                    int sum = 0;
                    int count = 0;
                    vector<int> crimesPerYear;

                    while (startYear <= endYear) {
                        int num = AVLMap[sName]->searchYearIncidentNumber(startYear);
                        crimesPerYear.push_back(num);
                        sum += num;
                        count++;
                        startYear++;
                    }
                    int temp = count;
                    mean = float(sum) / float(temp);

                    //calculate standard deviation
                    float var = 0.0;
                    float sd = 0.0;
                    for (int i = 0; i < count; ++i) {
                        var += pow(crimesPerYear.at(i) - mean, 2);
                    }

                    var = var / float(temp);
                    sd = sqrt(var);

                    //add to a map<string, vector<int>> to store to output to csv
                    csvOutput[*iter].push_back(crimeCount);
                    csvOutput[*iter].push_back(mean);
                    csvOutput[*iter].push_back(sd);
                    csvOutput[*iter].push_back(count);
                }
                endAVL = timer::now();
                elapsedTime = endAVL - startAVL;
                cout << setprecision(5) << "Time taken to run statistical analysis on AVL tree " << setprecision(5) << elapsedTime.count() << " seconds" << endl;

                //stats for RB tree
                startRB = timer::now();
                for (auto iter = searchStates.begin(); iter != searchStates.end(); iter++) {
                    //Begin statistical analysis
                    string sName = *iter;
                    sName.at(0) = tolower(sName.at(0));
                    //calculate total number of hate crimes of each state (aka how many Incident objects are in its tree)
                    crimeCount = RBMap[sName]->getTreeSize();

                    //calculate mean hate crimes of each state per year (average #crimes/year)
                    int startYear = startDate / 10000;
                    int endYear = endDate / 10000;
                    int sum = 0;
                    int count = 0;
                    vector<int> crimesPerYear;

                    while (startYear <= endYear) {
                        int num = RBMap[sName]->searchYearIncidentNumber(startYear);
                        crimesPerYear.push_back(num);
                        sum += num;
                        count++;
                        startYear++;
                    }
                    int temp = count;
                    mean = float(sum) / float(temp);

                    //calculate standard deviation
                    float var = 0.0;
                    float sd = 0.0;
                    for (int i = 0; i < count; ++i) {
                        var += pow(crimesPerYear.at(i) - mean, 2);
                    }

                    var = var / float(temp);
                    sd = sqrt(var);

                    //add to a map<string, vector<int>> to store to output to csv
                    csvOutput[*iter].push_back(crimeCount);
                    csvOutput[*iter].push_back(mean);
                    csvOutput[*iter].push_back(sd);
                    csvOutput[*iter].push_back(count);
                }
                endRB = timer::now();
                elapsedTime = endRB - startRB;
                cout << setprecision(5) << "Time taken to run statistical analysis on RB tree " << setprecision(5) << elapsedTime.count() << " seconds" << endl;
                
                //Date formatting for writing output
                string searchBegin;
                string day, month, year = "";
                day = to_string(startDate % 100);
                startDate /= 100;
                month = to_string(startDate % 100);
                startDate /= 100;
                year = to_string(startDate);
                searchBegin = month + "/" + day + "/" + year;

                string searchEnd;
                day = to_string(endDate % 100);
                endDate /= 100;
                month = to_string(endDate % 100);
                endDate /= 100;
                year = to_string(endDate);
                searchEnd = month + "/" + day + "/" + year;

                //output the stats to the console
                for (auto iter = csvOutput.begin(); iter != csvOutput.end(); iter++) {
                    //loop through the states and their data
                    string stateName = iter->first;
                    stateName.at(0) = toupper(stateName.at(0));
                    cout << endl << "Statistics for " << stateName << ":" << endl;
                    if (selectRange) {
                        //if the user specified a time range
                        cout << "Total number of hate crimes recorded from " << searchBegin << " to " << searchEnd
                             << ": " << iter->second.at(0) << endl;
                    } else {
                        //the user did not specify

                        cout << "Total number of hate crimes recorded ";
                        cout << "(whole dataset): " << iter->second.at(0) << endl;

                    }

                    cout << "Average number of hate crimes per year: " << iter->second.at(1) << endl;
                    cout << "Standard deviation of hate crimes per year: " << iter->second.at(2) << endl;
                }

                cout << endl;

                if (searchStates.size() > 1) {
                    cout << "Would you like to compare two specific states? (Y/N)" << endl;

                    string compare = "";
                    cin >> compare;

                    if (compare == "Y" || compare == "y") {
                        string state1;
                        string state2;
                        cin.ignore();
                        cout << "Enter State 1: ";
                        getline(cin, state1);
                        cout << "Enter State 2: ";
                        getline(cin, state2);
                        cout << endl;
                        
                        for(int k = 0; k < state1.size(); k++) {
                            //put all letters to lower case
                            state1.at(k) = tolower(state1.at(k));
                        }

                        for(int k = 0; k < state2.size(); k++) {
                            //put all letters to lower case
                            state2.at(k) = tolower(state2.at(k));
                        }

                        if (searchStates.find(state1) != searchStates.end() && searchStates.find(state2) != searchStates.end()) {
                            //compare these two specific states
                            float result = tTest(csvOutput[state1].at(1), csvOutput[state1].at(2), csvOutput[state1].at(3), csvOutput[state2].at(1), csvOutput[state2].at(2), csvOutput[state2].at(3));
                            state1.at(0) = toupper(state1.at(0));
                            state2.at(0) = toupper(state2.at(0));
                            cout << "A t-test between " << state1 << " and " << state2 << " results in the p-value " << result << endl;
                            if (result < -1.70 || result > 1.70) {
                                //reject H0 (there is sufficient evidence to indicate a significant difference between the data sets)
                                cout << "Interpretation: There is a significant difference between the\n"
                                     << "number of hate crimes per year in " << state1 << " compared to " << state2 << "." << endl;
                            }
                            else {
                                //fail to reject H0 (there is insufficient evidence to indicate a difference)
                                cout << "Interpretation: There is NOT a significant difference between\n"
                                     << "the number of hate crimes per year in " << state1 << " compared to " << state2 << "." << endl;
                            }

                        }
                        else {
                            cout << "Error: The two selected states were not a part of the current analysis." << endl;
                        }
                    }
                }
                

                bool valid;
                string compare;
                do {
                    cout << "Would you like to write the statistical data to a file? (Y/N)" << endl;
                    cin >> compare;

                    if (compare == "Y" || compare == "y") {
                        valid = true;
                        ofstream outputFile;
                        cout << "What would you like to name the file? ";
                        string fileName;
                        cin >> fileName;

                        outputFile.open(fileName + ".csv");

                        //Write column names
                        outputFile << "State Name" << "," << "Mean (#Crimes/Year)" << "," << "Standard Deviation\n";

                        //write data to file
                        for (auto iter = csvOutput.begin(); iter != csvOutput.end(); iter++) {
                            //loop through the states and their data
                            outputFile << iter->first << "," << iter->second.at(0) << "," << iter->second.at(1) << "\n";
                        }
                        outputFile.close();
                    }
                    else if (compare == "N" || compare == "n") {
                        valid = true;
                    }
                    else {
                        cout << "Error: Invalid choice. Please try again." << endl;
                        valid = false;
                    }
                } while (!valid);

                do {
                    cout << "Would you like to conduct another search? (Y/N)" << endl;
                    cin >> compare;

                    if (compare == "Y" || compare == "y") {
                        quit = false;
                        valid = true;
                        cin.ignore();
                        file.clear();
                        file.seekg(0, ios::beg);
                     }
                    else if (compare == "N" || compare == "n") {
                        quit = true;
                        valid = true;
                        file.close();
                    }
                    else {
                        cout << "Error: Invalid selection. Please try again." << endl;
                        valid = false;
                    }
                } while (!valid);

                searchStates.clear();
                for(auto iter = searchStates.begin(); iter != searchStates.end(); iter++) {
                    //reset AVL and RB maps and trees
                    AVLMap[*iter]->~AVLtree();
                    AVLMap[*iter] = nullptr;
                    RBMap[*iter]->~RBtree();
                    RBMap[*iter] = nullptr;
                }
            }
        }
    }

    cout << endl << "Thank you for parsing." << endl;
    return 0;
}
