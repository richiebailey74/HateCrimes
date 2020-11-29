#pragma once
#include "treeNode.h"
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

class AVLtree {
private:
	treeNode* root;

	treeNode* leftRotation(treeNode*& currentnode);
	treeNode* rightRotation(treeNode*& currentnode);
	treeNode* leftRightRotation(treeNode*& currentnode);
	treeNode* rightLeftRotation(treeNode*& currentnode);
	bool searchAddIncident(int incidentToAdd);

	//helper functions
	void updateHeight(treeNode* node);
	int height(treeNode* node);
	treeNode* treeInsert(treeNode* currentnode, treeNode* insertnode);
	void inOrderRecursive(treeNode* currentnnode);
	void levelOrderRecursive(treeNode* currentnode);
	int BF(treeNode* node);
	void traversalIncidentDate(treeNode* currentnode, int incidentToAdd, bool& searchSuccess);
	//add away functions to abstract away functionality later


public:
	AVLtree();
	void insertNode(int val);
	void inOrder();
	void levelOrder();
};

