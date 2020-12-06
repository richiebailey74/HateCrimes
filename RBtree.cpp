#include "RBtree.h"

RBtree::RBtree() {
	root = nullptr;
	treeSize = 0;
}

bool RBtree::compareTreenodes(treenode* N1, treenode* N2) {
	if (N1 == N2) {
		return true;
	}
	else {
		return false;
	}
}

//recursively traverses tree with recursive call
void RBtree::inOrderRecursive(treenode* currentnode) {

	if (!(currentnode)) {
		return;
	}

	inOrderRecursive(currentnode->left);
	cout << currentnode->date << " ";
	inOrderRecursive(currentnode->right);

}

//iteratively traverses tree with queue and while loop that makes temporary treenode*
void RBtree::levelOrderRecursive(treenode* currentnode) {

	if (!(currentnode)) {
		return;
	}

	queue<treenode*> theQueue;
	theQueue.push(currentnode);

	while (!theQueue.empty()) {

		treenode* tempNode = theQueue.front();
		cout << tempNode->date << " ";
		theQueue.pop();

		if (tempNode->left) {
			theQueue.push(tempNode->left);
		}
		if (tempNode->right) {
			theQueue.push(tempNode->right);
		}
	}

}

void RBtree::traversalIncidentDate(treenode* currentnode, Incident* incidentToAdd, bool& searchSuccess) {
	if (currentnode) {
		if (currentnode->date == incidentToAdd->date) { //will be the incident's date (or the date passed in)
			searchSuccess = true;
			currentnode->incidentsContainer.push_back(incidentToAdd);
			treeSize++;

		}
		traversalIncidentDate(currentnode->left, incidentToAdd, searchSuccess);
		traversalIncidentDate(currentnode->right, incidentToAdd, searchSuccess);
	}
}

bool RBtree::searchAddIncident(Incident* incidentToAdd) {
	bool searchSuccess = false;
	traversalIncidentDate(root, incidentToAdd, searchSuccess);
	return searchSuccess;
}

void RBtree::searchYearIncidentDateRecursive(treenode* currentnode, int& incidentSum, int year) {
	if(currentnode == NULL) {
		return;
	}
	
	searchYearIncidentDateRecursive(currentnode->left, incidentSum, year);
	if((currentnode->date / 10000) == year) {
		incidentSum += currentnode->incidentsContainer.size();
	}
	searchYearIncidentDateRecursive(currentnode->right, incidentSum, year);
}

int RBtree::searchYearIncidentNumber(int year) {
	int incidentNumberForYear = 0;
	searchYearIncidentDateRecursive(root, incidentNumberForYear, year);
	return incidentNumberForYear;
}

treenode* RBtree::treeInsert(treenode* root, treenode* currentnode) {

	if (root == NULL) {
		return currentnode;
	}

	if (currentnode->date < root->date) {
		root->left = treeInsert(root->left, currentnode);
		root->left->parent = root; //implementing parent is good for fixImbalance()
	}
	else if (currentnode->date > root->date) {
		root->right = treeInsert(root->right, currentnode);
		root->right->parent = root; //implementing parent is good for fixImbalance()
	}

	return root; //always returns root at the very end of all function calls

}

void RBtree::swapColors(treenode*& N1, treenode*& N2) {
	bool tempBool = N1->color;
	N1->color = N2->color;
	N2->color = tempBool;
}

void RBtree::setColorBlack(treenode*& node) {
	node->color = true;
}

void RBtree::setColorRed(treenode*& node) {
	node->color = false;
}

bool RBtree::isBlack(treenode* node) {
	if (node->color) {
		return true;
	}
	else {
		return false;
	}
}

bool RBtree::isRed(treenode* node) {
	if (node->color) {
		return false;
	}
	else {
		return true;
	}
}

void RBtree::leftRotation(treenode*& root, treenode*& currentnode) {

	treenode* currentnodesR = currentnode->right;
	currentnode->right = currentnodesR->left; //takes care of the shifted grandchild node due to rotation
	if (currentnode->right) {
		currentnode->right->parent = currentnode;
	}
	currentnodesR->parent = currentnode->parent;

	//next if else block makes sure the parent was assigned correctly in the rotation
	if (!(currentnode->parent)) {
		root = currentnodesR;
	}
	else if (compareTreenodes(currentnode, currentnode->parent->left)) {
		currentnode->parent->left = currentnodesR;
	}
	else {
		currentnode->parent->right = currentnodesR;
	}

	currentnodesR->left = currentnode;
	currentnode->parent = currentnodesR;

}

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

void RBtree::imbalanceFix(treenode*& root, treenode*& currentnode) {

	treenode* currentnodeP = NULL;
	treenode* currentnodeGP = NULL;

		//for colors, true is black and false is red
		while (!(isBlack(currentnode)) && !(compareTreenodes(currentnode, root)) && (isRed(currentnode->parent))) {

			currentnodeP = currentnode->parent;
			currentnodeGP = currentnode->parent->parent;

			if (currentnodeP == currentnodeGP->left) {
				treenode* currentnodeU = currentnodeGP->right;

				if ((currentnodeU) && (isRed(currentnodeU))) {
					setColorBlack(currentnodeGP);
					setColorBlack(currentnodeU);
					currentnode = currentnodeGP;
				}
				else {


					if (compareTreenodes(currentnode, currentnodeP->right)) {
						leftRotation(root, currentnodeP);
						currentnode = currentnodeP;
						currentnodeP = currentnode->parent;
					}

					rightRotation(root, currentnodeGP);
					swapColors(currentnodeP, currentnodeGP);
					currentnode = currentnodeP;
				}
			}
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

		root->color = true;
}

void RBtree::insertNode(int val, Incident* incident) {
	treenode* newVal = new treenode(val);
	newVal->incidentsContainer.push_back(incident);
	treeSize++;
	
	root = treeInsert(root, newVal);

	imbalanceFix(root, newVal);

}

void RBtree::inOrder() {
	inOrderRecursive(root);
}

void RBtree::levelOrder() {
	levelOrderRecursive(root);
}

int RBtree::getTreeSize() {
	return treeSize;
}
