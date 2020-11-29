#pragma once
#include "treenode.h"
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

class RBtree {
private:
	treenode* root;

	void leftRotation(treenode*& root, treenode*& currentnode);
	void rightRotation(treenode*& root, treenode*& currentnode);
	void imbalanceFix(treenode*& root, treenode*& currentnode);

	//helper functions
	treenode* treeInsert(treenode* root, treenode* currentnode);
	void inOrderRecursive(treenode* currentnode);
	void levelOrderRecursive(treenode* currentnode);
	void swapColors(treenode*& N1, treenode*& N2);
	void setColorBlack(treenode*& node);
	void setColorRed(treenode*& node);
	bool isRed(treenode* node);
	bool isBlack(treenode* node);
	bool compareTreenodes(treenode* N1, treenode* N2);
	void traversalIncidentDate(treenode* currentnode, int incidentToAdd, bool& searchSuccess);

public:
	RBtree();
	void insertNode(int val);
	void inOrder();
	void levelOrder();
	bool searchAddIncident(int incidentToAdd); //will change to incident instead but has similar functionality

};
