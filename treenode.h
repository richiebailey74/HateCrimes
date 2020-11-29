#pragma once
#include <iostream>
#include <vector>
using namespace std;

class treenode {
public:
	int date;
	bool color; //true is black, false is red
	vector<int> incidentsContainer; //will have incident objects instead of int
	treenode* left;
	treenode* right;
	treenode* parent; //doubly linked to make way easier implementation

	treenode(int input);
	void operator = (const treenode& node);

};

