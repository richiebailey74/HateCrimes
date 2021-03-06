#pragma once
#include "treenode.h"
#include "Incident.h"
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

class RBtree {
private:
	//private member variables
	treenode* root;
	int treeSize;

	//imbalance functions
	void leftRotation(treenode*& root, treenode*& currentnode);
	void rightRotation(treenode*& root, treenode*& currentnode);
	void imbalanceFix(treenode*& root, treenode*& currentnode);

	//helper functions - don't need public access
	treenode* treeInsert(treenode* root, treenode* currentnode);
	void inOrderRecursive(treenode* currentnode);
	void levelOrderRecursive(treenode* currentnode);
	void swapColors(treenode*& N1, treenode*& N2);
	void setColorBlack(treenode*& node);
	void setColorRed(treenode*& node);
	bool isRed(treenode* node);
	bool isBlack(treenode* node);
	bool compareTreenodes(treenode* N1, treenode* N2);
	void traversalIncidentDate(treenode* currentnode, Incident* incidentToAdd, bool& searchSuccess);
	void searchYearIncidentDateRecursive(treenode* currentnode, int& incidentSum, int year);
	void deleteTreeRecursive(treenode* &currNode);
	void deleteTree();

public:
	RBtree();
	~RBtree();
	void insertNode(int val, Incident* incident);
	void inOrder();
	void levelOrder();
	bool searchAddIncident(Incident* incidentToAdd); //will change to incident instead but has similar functionality
	int getTreeSize();
	int searchYearIncidentNumber(int year);
};

