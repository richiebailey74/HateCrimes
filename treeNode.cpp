#include "treeNode.h"

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
