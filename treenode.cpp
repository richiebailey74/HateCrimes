#include "treenode.h"


//red black
treenode::treenode(int input) {
	date = input;
	left = NULL;
	right = NULL;
	parent = NULL;
	color = false;
}

void treenode::operator = (const treenode& node) {
	date = node.date;
	left = node.left;
	right = node.right;
	parent = node.parent;
	color = node.color;
	for (unsigned int i = 0; i < node.incidentsContainer.size(); i++) {
		incidentsContainer.push_back(node.incidentsContainer[i]);
	}
}



//avl
treeNode::treeNode(int input) {
	date = input;
	left = NULL;
	right = NULL;
	height = 1;
}

void treeNode::operator = (const treeNode& node) {
	date = node.date;
	left = node.left;
	right = node.right;
	height = node.height;
	for (unsigned int i = 0; i < node.incidentsContainer.size(); i++) {
		incidentsContainer.push_back(node.incidentsContainer[i]);
	}
}
