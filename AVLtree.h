#pragma once
#include "treeNode.h"
#include "Incident.h"
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

class AVLtree {
private:
	//member variables
	treeNode* root;
	int treeSize;

	//rotation functions
	treeNode* leftRotation(treeNode*& currentnode);
	treeNode* rightRotation(treeNode*& currentnode);
	treeNode* leftRightRotation(treeNode*& currentnode);
	treeNode* rightLeftRotation(treeNode*& currentnode);

	//helper functions - don't need public access
	void updateHeight(treeNode* node);
	int height(treeNode* node);
	treeNode* treeInsert(treeNode* currentnode, treeNode* insertnode);
	void inOrderRecursive(treeNode* currentnnode);
	void levelOrderRecursive(treeNode* currentnode);
	int BF(treeNode* node);
	void traversalIncidentDate(treeNode* currentnode, Incident* incidentToAdd, bool& searchSuccess);
	void searchYearIncidentDateRecursive(treeNode* currentnode, int& incidentSum, int year);
	void deleteTreeRecursive(treeNode* &currNode);
	void deleteTree();


public:
	AVLtree();
	~AVLtree();
	void insertNode(int val, Incident* incident);
	void inOrder();
	void levelOrder();
	bool searchAddIncident(Incident* incidentToAdd);
	int getTreeSize();
	int searchYearIncidentNumber(int year);
};

