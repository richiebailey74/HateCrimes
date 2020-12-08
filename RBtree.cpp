#include "RBtree.h"

//default constructor sets the root to NULL and size to 0
RBtree::RBtree() {
	root = nullptr;
	treeSize = 0;
}

//compares two treenode pointers to see if they point to the same object
bool RBtree::compareTreenodes(treenode* N1, treenode* N2) {
	if (N1 == N2) {
		return true;
	}
	else {
		return false;
	}
}

//recursively traverses tree with recursive call
//it is an in order traversal
void RBtree::inOrderRecursive(treenode* currentnode) {

	//base case returns if currentnode is null
	if (!(currentnode)) {
		return;
	}

	inOrderRecursive(currentnode->left);
	cout << currentnode->date << " ";
	inOrderRecursive(currentnode->right);

}

//iteratively traverses tree with queue and while loop that makes temporary treenode*
//performs a level order traversal
void RBtree::levelOrderRecursive(treenode* currentnode) {

	if (!(currentnode)) {
		return;
	}

	//initializes queue with the root
	queue<treenode*> theQueue;
	theQueue.push(currentnode);

	//when the last node is popped from the queue and it points to two nulls that means the level order traversal has completed and the loop can break
	while (!theQueue.empty()) {

		//creates a temp node that points to the front of the queue
		treenode* tempNode = theQueue.front();
		//print out that nodes date
		cout << tempNode->date << " ";
		//pop that node from the queue
		theQueue.pop();

		//if the left pointer is not null push it
		if (tempNode->left) {
			theQueue.push(tempNode->left);
		}
		//if the right pointer is not null push it
		if (tempNode->right) {
			theQueue.push(tempNode->right);
		}
	}

}

//recursive helper that checks to see if the incident that is attempted to be added has a date in common with any other node in the tree
void RBtree::traversalIncidentDate(treenode* currentnode, Incident* incidentToAdd, bool& searchSuccess) {
	//base case is that the node is null, then it doesn't enter the if statement
	if (currentnode) {
		if (currentnode->date == incidentToAdd->date) { //will be the incident's date (or the date passed in)
			searchSuccess = true;
			//if there is a date in common then that incident is pushed into that respective nodes incident container
			currentnode->incidentsContainer.push_back(incidentToAdd);
			//size of overall tree is incremented
			treeSize++;

		}
		//performs the preorder traversal of the tree
		traversalIncidentDate(currentnode->left, incidentToAdd, searchSuccess);
		traversalIncidentDate(currentnode->right, incidentToAdd, searchSuccess);
	}
}

//assumes the search success passed by reference will be false unless made true in the recursive helper
bool RBtree::searchAddIncident(Incident* incidentToAdd) {
	bool searchSuccess = false;
	traversalIncidentDate(root, incidentToAdd, searchSuccess);
	return searchSuccess;
}

//recursive helper to check how many incidents exist for a sought after year
void RBtree::searchYearIncidentDateRecursive(treenode* currentnode, int& incidentSum, int year) {
	//base case is if the currentnode is null
	if(currentnode == NULL) {
		return;
	}
	
	//performs an in order traversal checking every node to see if the year of the node matches the input year
	searchYearIncidentDateRecursive(currentnode->left, incidentSum, year);
	//divides by 10000 to get the year since integer division yields an integer not a floating point
	if((currentnode->date / 10000) == year) {
		incidentSum += currentnode->incidentsContainer.size();
	}
	searchYearIncidentDateRecursive(currentnode->right, incidentSum, year);
}

//passes by reference the number of times an incident appears for a certain year (not date)
int RBtree::searchYearIncidentNumber(int year) {
	int incidentNumberForYear = 0;
	searchYearIncidentDateRecursive(root, incidentNumberForYear, year);
	return incidentNumberForYear;
}

//inserts a node into a tree - it is a recurisve function 
treenode* RBtree::treeInsert(treenode* root, treenode* currentnode) {

	//base case finds the correct spot for the added node with BST implementation, essentially inserts it here at end of recursive call
	if (root == NULL) {
		return currentnode;
	}

	//BST traversal
	if (currentnode->date < root->date) {
		root->left = treeInsert(root->left, currentnode);
		root->left->parent = root; //implementing parent is good for fixImbalance()
	}
	//BST traversal
	else if (currentnode->date > root->date) {
		root->right = treeInsert(root->right, currentnode);
		root->right->parent = root; //implementing parent is good for fixImbalance()
	}

	return root; //always returns root at the very end of all function calls

}

//uses a temp bool to swap the colors of two nodes passed in
void RBtree::swapColors(treenode*& N1, treenode*& N2) {
	bool tempBool = N1->color;
	N1->color = N2->color;
	N2->color = tempBool;
}

//sets the color of the treenode to black
void RBtree::setColorBlack(treenode*& node) {
	node->color = true;
}

//sets the color of the treenode to red
void RBtree::setColorRed(treenode*& node) {
	node->color = false;
}

//checks to see if the color of a treenode is black
bool RBtree::isBlack(treenode* node) {
	if (node->color) {
		return true;
	}
	else {
		return false;
	}
}

//checks to see if the color of the treenode is red
bool RBtree::isRed(treenode* node) {
	if (node->color) {
		return false;
	}
	else {
		return true;
	}
}

//some inspiration was drawn from https://www.geeksforgeeks.org/c-program-red-black-tree-insertion/ for this function
//for when there is a double red imbalance and the uncle node is black (rotation won't cause another double red imbalance)
void RBtree::leftRotation(treenode*& root, treenode*& currentnode) {

	treenode* currentnodesR = currentnode->right;
	currentnode->right = currentnodesR->left; //takes care of the shifted grandchild node due to rotation
	//if the currentnode pointing to the right (which really is the to be shifted grandchild) is not null then reassign its parent to currentnode
	if (currentnode->right) {
		currentnode->right->parent = currentnode;
	}
	//moves the parent to aprropriate new spot
	currentnodesR->parent = currentnode->parent;

	//next if else block makes sure the parent was assigned correctly in the rotation
	//accounts for if rotation occurs at root
	if (!(currentnode->parent)) {
		root = currentnodesR;
	}
	//if the current node is the left child then it becomes the initial current nodes right pointer
	else if (compareTreenodes(currentnode, currentnode->parent->left)) {
		currentnode->parent->left = currentnodesR;
	}
	//otherwise the current node is the right child then it becomes the initial current nodes left pointer
	else {
		currentnode->parent->right = currentnodesR;
	}

	//finalizing reassignment by flipping who current node and current node's initial right pointer point to
	currentnodesR->left = currentnode;
	currentnode->parent = currentnodesR;

}

//some inspiration was drawn from https://www.geeksforgeeks.org/c-program-red-black-tree-insertion/ for this function
//same as above but flipped for the right rotation from a left left effective imbalance from double red imblance
void RBtree::rightRotation(treenode*& root, treenode*& currentnode) {

	treenode* currentnodesL = currentnode->left;
	currentnode->left = currentnodesL->right;
	if (currentnode->left) {
		currentnode->left->parent = currentnode;
	}
	currentnodesL->parent = currentnode->parent;

	//makes sure parent is assigned properly
	if (!(currentnode->parent)) {
		root = currentnodesL;
	}
	else if (compareTreenodes(currentnode, currentnode->parent->left)) {
		currentnode->parent->left = currentnodesL;
	}
	else {
		currentnode->parent->right = currentnodesL;
	}

	currentnodesL->right = currentnode;
	currentnode->parent = currentnodesL;

}

//some inspiration was drawn from https://www.geeksforgeeks.org/c-program-red-black-tree-insertion/ for this function
//this function is for when there is a double red imbalance and the uncle node is red, meaning a rotation would cause another double red imbalance
void RBtree::imbalanceFix(treenode*& root, treenode*& currentnode) {

	//initialize here so they can maintain values with loops
	treenode* currentnodeP = NULL;
	treenode* currentnodeGP = NULL;

		//for colors, true is black and false is red
		//this is essentially saying that the propogation of rotations must continue up the tree for it to be balanced until a double red imbalance no linger exists
		while (!(isBlack(currentnode)) && !(compareTreenodes(currentnode, root)) && (isRed(currentnode->parent))) {

			currentnodeP = currentnode->parent;
			currentnodeGP = currentnode->parent->parent;

			//if the imbalance comes from the left
			if (currentnodeP == currentnodeGP->left) {
				//define the uncle node
				treenode* currentnodeU = currentnodeGP->right;

				//if the uncle red (and not null obviously) then a rotation would still cause a double red imbalance
				//propgate up changing of colors
				if ((currentnodeU) && (isRed(currentnodeU))) {
					setColorBlack(currentnodeGP);
					setColorBlack(currentnodeU);
					currentnode = currentnodeGP;
				}
				//for if the uncle is black (a rotation would not cause a double red imbalance)
				else {

					//if the imbalance comes from a left right double red imbalance then rotate left
					if (compareTreenodes(currentnode, currentnodeP->right)) {
						leftRotation(root, currentnodeP);
						currentnode = currentnodeP;
						currentnodeP = currentnode->parent;
					}

					//will always need to rotate this right here if the uncle is black and the imbalance comes from the left side of the grandparent
					rightRotation(root, currentnodeGP);
					swapColors(currentnodeP, currentnodeGP);
					currentnode = currentnodeP;
				}
			}
			//if the imbalance comes from the right
			//exact same code as if statement above except flipped functionally
			else {

				treenode* currentnodeU = currentnodeGP->left;

				if ((currentnodeU) && (isRed(currentnodeU))) {
					setColorRed(currentnodeGP);
					setColorBlack(currentnodeP);
					setColorBlack(currentnodeU);
					currentnode = currentnodeGP;
				}
				else {

					if (compareTreenodes(currentnode, currentnodeP->left)) {
						rightRotation(root, currentnodeP);
						currentnode = currentnodeP;
						currentnodeP = currentnode->parent;
					}

					leftRotation(root, currentnodeGP);
					swapColors(currentnodeP, currentnodeGP);
					currentnode = currentnodeP;
				}
			}
		}
		//makes sure root is always black
		root->color = true;
}

//public function called to insert a node in the tree
void RBtree::insertNode(int val, Incident* incident) {
	//creates a new treenode on the heap
	treenode* newVal = new treenode(val);
	//pushes back the incident and incrememnts the treesize
	newVal->incidentsContainer.push_back(incident);
	treeSize++;
	
	//insert the tree
	root = treeInsert(root, newVal);

	//make sure all imbalances are fixed
	imbalanceFix(root, newVal);

}

//calls the in order recursive helper, used in testing
void RBtree::inOrder() {
	inOrderRecursive(root);
}

//calls the level order recursive helper, used in testing
void RBtree::levelOrder() {
	levelOrderRecursive(root);
}

//returns private member of the treesize
int RBtree::getTreeSize() {
	return treeSize;
}

//delete tree recursive helper
void RBtree::deleteTreeRecursive(treenode* &currNode) {
    if(currNode != nullptr) {
        deleteTreeRecursive(currNode->left);
        deleteTreeRecursive(currNode->right);
	currNode->incidentsContainer.clear();
        delete currNode;
    }
    currNode = nullptr;
}

//when the program is done, memory must be deallocated so it calls the delete tree recursvie functions
void RBtree::deleteTree()
{
    if(root != nullptr) {
        deleteTreeRecursive(root);
    }
    root = nullptr;
}

//destructor that calls the delete tree functionality
RBtree::~RBtree() {
    //destructor
    deleteTree();
}
