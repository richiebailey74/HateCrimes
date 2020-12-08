#include "treenode.h"


//red black
//initialize date to constructor input and all pointers to null and color to red/false
treenode::treenode(int input) {
	date = input;
	left = NULL;
	right = NULL;
	parent = NULL;
	color = false;
}

//operator overload
void treenode::operator = (const treenode& node) {
	date = node.date;
	left = node.left;
	right = node.right;
	parent = node.parent;
	color = node.color;
	//loops through incidents container and copie them over to complete the deep copy
	for (unsigned int i = 0; i < node.incidentsContainer.size(); i++) {
		incidentsContainer.push_back(node.incidentsContainer[i]);
	}
}

treenode::~treenode() {
    //destructor must loop through incidents container while it is not empty (vector is linked list so indices restart)
    while (!incidentsContainer.empty()) {
        //delete the incidents
        delete incidentsContainer.at(0);
    }
    delete left;
    delete right;
    delete parent;
}



//avl
//initialize height to one, date to constructor input, and pointers to null
treeNode::treeNode(int input) {
	date = input;
	left = NULL;
	right = NULL;
	height = 1;
}

//operator overload
void treeNode::operator = (const treeNode& node) {
	date = node.date;
	left = node.left;
	right = node.right;
	height = node.height;
	//loops through incidents container and copie them over to complete the deep copy
	for (unsigned int i = 0; i < node.incidentsContainer.size(); i++) {
		incidentsContainer.push_back(node.incidentsContainer[i]);
	}
}

treeNode::~treeNode() {
    //destructor must loop through incidents container while it is not empty (vector is linked list so indices restart)
    while (!incidentsContainer.empty()) {
        //delete the incidents
        delete incidentsContainer.at(0);
    }
    delete left;
    delete right;
}
