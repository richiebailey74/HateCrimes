#pragma once
#include "treeNode.h"
#include "Incident.h"
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

class AVLtree {
private:
	treeNode* root;
	int treeSize;

	treeNode* leftRotation(treeNode*& currentnode);
	treeNode* rightRotation(treeNode*& currentnode);
	treeNode* leftRightRotation(treeNode*& currentnode);
	treeNode* rightLeftRotation(treeNode*& currentnode);

	//helper functions
	void updateHeight(treeNode* node);
	int height(treeNode* node);
	treeNode* treeInsert(treeNode* currentnode, treeNode* insertnode);
	void inOrderRecursive(treeNode* currentnnode);
	void levelOrderRecursive(treeNode* currentnode);
	int BF(treeNode* node);
	void traversalIncidentDate(treeNode* currentnode, Incident* incidentToAdd, bool& searchSuccess); //might need to add a date
	//add away functions to abstract away functionality later
	void searchYearIncidentDateRecursive(treeNode* currentnode, int& incidentSum, int year);


public:
	AVLtree();
	void insertNode(int val, Incident* incident);
	void inOrder();
	void levelOrder();
	bool searchAddIncident(Incident* incidentToAdd);
	int getTreeSize();
	int searchYearIncidentNumber(int year);
};

