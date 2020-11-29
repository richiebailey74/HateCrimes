#pragma once
#include <iostream>
#include <vector>
using namespace std;

class treeNode {
public:
	int date;
	int height; //equivalent in balancing functionality to RB color boolean
	vector<int> incidentsContainer;
	treeNode* left;
	treeNode* right;
	//does not need a parent node for effective functionality

	treeNode(int input);
	void operator = (const treeNode& node);


};

