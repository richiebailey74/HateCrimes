//this the red black tree node header

#pragma once
#include <iostream>
#include <vector>
#include "Incident.h"
using namespace std;

class treenode {
public:
	int date;
	bool color; //true is black, false is red
	vector<Incident> incidentsContainer; //will have incident objects instead of int
	treenode* left;
	treenode* right;
	treenode* parent; //doubly linked to make way easier implementation

	treenode(int input);
	void operator = (const treenode& node);

};

