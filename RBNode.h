//YOOOO delete this file idk how

#pragma once
#include <vector>
#include <string>

using namespace std;
class RBNode {
public:
    int year;
    vector<int> incidentContainer;
    RBNode *left;
    RBNode *right;
    RBNode() :year(-1), left(nullptr), right(nullptr) {}
};
