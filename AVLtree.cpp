#include "AVLtree.h"
#include "Incident.h"


//default constructor sets the root to NULL and treesize to 0
AVLtree::AVLtree() {
	root = nullptr;
	treeSize = 0;
}

//helper function to print elements in order
void AVLtree::inOrderRecursive(treeNode* currentnode) {
	//base case returns nothing if the pointer is null
	if (currentnode == NULL) {
		return;
	}

	//in order because L root R
	inOrderRecursive(currentnode->left);
	cout << currentnode->date << " ";
	inOrderRecursive(currentnode->right);
}

//level order recursive helper
void AVLtree::levelOrderRecursive(treeNode* currentnode) {
	//base case returns nothing if the pointer is null
	if (currentnode == NULL) {
		return;
	}

	//creates a queue and adds the root to allow for proper level order traversal
	queue<treeNode*> Q;
	Q.push(currentnode);

	//loop only breaks when the last element in the queue points to both nulls, so we know the traversal is done
	while (!Q.empty()) {
		//prints out date of the front node
		treeNode* tempNode = Q.front();
		cout << tempNode->date << " ";
		//pops the front node
		Q.pop();
		//adds the left if it isn't null
		if (tempNode->left != NULL) {
			Q.push(tempNode->left);
		}
		//adds the right if it isn't null
		if (tempNode->right != NULL) {
			Q.push(tempNode->right);
		}
	}
}

//recursive helper exists to deem whether or not a particular sought for incident has a date in common with any node in the tree
void AVLtree::traversalIncidentDate(treeNode* currentnode, Incident* incidentToAdd, bool& searchSuccess) {
	//base case is that the currentnode is null, in that case it doesn't enter into the if statement
	if (currentnode != NULL) {
		//if the date mathces then search success is true and the incident is pushed back to the respective node and size is incremented
		if (currentnode->date == incidentToAdd->date) {
			searchSuccess = true;
			currentnode->incidentsContainer.push_back(incidentToAdd);
			treeSize++;
		}
		traversalIncidentDate(currentnode->left, incidentToAdd, searchSuccess);
		traversalIncidentDate(currentnode->right, incidentToAdd, searchSuccess);
	}
}

//passes by reference the search success
//search success is assumed false until proven true in the recursive helper
bool AVLtree::searchAddIncident(Incident* incidentToAdd) {
	bool searchSuccess = false;
	traversalIncidentDate(root, incidentToAdd, searchSuccess);
	return searchSuccess;
}

void AVLtree::searchYearIncidentDateRecursive(treeNode* currentnode, int& incidentSum, int year) {
	//base case returns nothing if the currentnode is null
	if(currentnode == NULL) {
		return;
	}
	
	//in order traversal of the tree
	searchYearIncidentDateRecursive(currentnode->left, incidentSum, year);
	//if the date matches then add size of incident container (use /10000 to get year since integer division truncates decimal values)
	if((currentnode->date / 10000) == year) {
		incidentSum += currentnode->incidentsContainer.size();
	}
	searchYearIncidentDateRecursive(currentnode->right, incidentSum, year);
}

//passes by reference a count to see how many incidents occur for a particular year (not date)
int AVLtree::searchYearIncidentNumber(int year) {
	int incidentNumberForYear = 0;
	searchYearIncidentDateRecursive(root, incidentNumberForYear, year);
	return incidentNumberForYear;
}

//returns the height of the tree
int AVLtree::height(treeNode* node) {
	if (node == NULL) {
		return 0;
	}
	else {
		return node->height;
	}
}

//updates height by finding the max depth between the right and left subtrees of the node and add one to include the node itself
void AVLtree::updateHeight(treeNode* node) {
	node->height = max(height(node->left), height(node->right)) + 1;
}

//returns balance factor which is height of the left subtree minus height of the right subtree - used in balancing implementation
int AVLtree::BF(treeNode* node) {
	if (node == NULL) {
		return 0;
	}
	else {
		return (height(node->left) - height(node->right));
	}
}

//rotates the tree left for a right right imbalance and moves the grandchild to the appropriate spot while also updating the heights
treeNode* AVLtree::leftRotation(treeNode*& currentnode) {
	treeNode* returnNode = currentnode->right;
	treeNode* gKidReplace = returnNode->left;
	returnNode->left = currentnode;
	currentnode->right = gKidReplace;

	updateHeight(currentnode);
	updateHeight(returnNode);

	return returnNode;
}

//same as above but rotates right for a left left imbalance
treeNode* AVLtree::rightRotation(treeNode*& currentnode) {
	treeNode* returnNode = currentnode->left;
	treeNode* gKidReplace = returnNode->right;
	returnNode->right = currentnode;
	currentnode->left = gKidReplace;

	updateHeight(currentnode);
	updateHeight(returnNode);

	return returnNode;
}

//for a left right imbalance, left rotate the currentnodes left child then right rotate the currentnode
treeNode* AVLtree::leftRightRotation(treeNode*& currentnode) {
	currentnode->left = leftRotation(currentnode->left);
	return rightRotation(currentnode);
}

//same as above but for a right left imbalance
treeNode* AVLtree::rightLeftRotation(treeNode*& currentnode) {
	currentnode->right = rightRotation(currentnode->right);
	return leftRotation(currentnode);
}

//some inspiration was drawn from https://www.geeksforgeeks.org/avl-tree-set-1-insertion/ for this function
//inserts the node into the tree and balances all in one function
treeNode* AVLtree::treeInsert(treeNode* currentnode, treeNode* insertnode) {
	//add the node with BST functinoality
	//base case essentially stops the recursive call and inserts the node in the apporpriate spot
	if (currentnode == NULL) {
		return insertnode;
	}
	//BST functionality
	if (insertnode->date > currentnode->date) {
		currentnode->right = treeInsert(currentnode->right, insertnode);
	}
	//BST functionality
	else if (insertnode->date < currentnode->date) {
		currentnode->left = treeInsert(currentnode->left, insertnode);
	}
	else {
		return currentnode;
	}

	//update the height
	updateHeight(currentnode);

	//get the balance factor of the currentnode to see how to properly apply rotations if necessary
	int balFac = BF(currentnode);

	//left left imbalance
	if (balFac > 1 && insertnode->date < currentnode->left->date) {
		return rightRotation(currentnode);
	}
	//right right imbalance
	if (balFac < -1 && insertnode->date > currentnode->right->date) {
		return leftRotation(currentnode);
	}
	//left right imbalance
	if (balFac > 1 && insertnode->date > currentnode->left->date) {
		return leftRightRotation(currentnode);
	}
	//right left imbalance
	if (balFac < -1 && insertnode->date < currentnode->right->date) {
		return rightLeftRotation(currentnode);
	}
	//return the current node whether rotations were performed or not
	return currentnode;
}

//public function that creates a new treenode on the heap, pushed back the incident, and adds the node
void AVLtree::insertNode(int val, Incident* incident) {
	treeNode* newVal = new treeNode(val);
	newVal->incidentsContainer.push_back(incident);
	treeSize++;
	
	root = treeInsert(root, newVal); //might have to pass an incident as well, not sure yet
}

//in order traversal used in testing
void AVLtree::inOrder() {
	inOrderRecursive(root);
}

//level order traversal used in testing
void AVLtree::levelOrder() {
	levelOrderRecursive(root);
}

//returns private treesize variable
int AVLtree::getTreeSize() {
	return treeSize;
}

//delete tree recursive helper function
void AVLtree::deleteTreeRecursive(treeNode* &currNode) {
    if(currNode != nullptr) {
        deleteTreeRecursive(currNode->left);
        deleteTreeRecursive(currNode->right);
	currNode->incidentsContainer.clear();
        delete currNode;
    }
    currNode = nullptr;
}

//function that calls the recursive helper called in the destructor
void AVLtree::deleteTree(){
    if(root != nullptr) {
        deleteTreeRecursive(root);
    }
    root = nullptr;
}

//destructor for AVL tree
AVLtree::~AVLtree() {
    //destructor
    deleteTree();
}
