//this the red black tree node header

#pragma once
#include <iostream>
#include <vector>
#include "Incident.h"
using namespace std;

//red black node
class treenode {
public:
	int date;
	bool color; //true is black, false is red
	vector<Incident*> incidentsContainer; //contains all incidents for a particular date
	treenode* left;
	treenode* right;
	treenode* parent; //doubly linked to make way easier implementation

	treenode(int input); //constructor
	~treenode(); //destructor
	void operator = (const treenode& node); //operator overload
};


//avl node
class treeNode {
public:
	int date;
	int height; //equivalent in balancing functionality to RB color boolean
	vector<Incident*> incidentsContainer; //contains all incidents for a particular date
	treeNode* left;
	treeNode* right;
	//does not need a parent node for effective functionality

	treeNode(int input); //constructor
	~treeNode(); //destructor
	void operator = (const treeNode& node); //operator overload
};

