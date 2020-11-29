#include "treenode.h"

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
