#include "AVLtree.h"


AVLtree::AVLtree() {
	root = NULL;
}

void AVLtree::inOrderRecursive(treeNode* currentnode) {
	if (currentnode == NULL) {
		return;
	}

	inOrderRecursive(currentnode->left);
	cout << currentnode->date << " ";
	inOrderRecursive(currentnode->right);
}

void AVLtree::levelOrderRecursive(treeNode* currentnode) {
	if (currentnode == NULL) {
		return;
	}

	queue<treeNode*> Q;
	Q.push(currentnode);

	while (!Q.empty()) {
		treeNode* tempNode = Q.front();
		cout << tempNode->date << " ";
		Q.pop();
		if (tempNode->left != NULL) {
			Q.push(tempNode->left);
		}
		if (tempNode->right != NULL) {
			Q.push(tempNode->right);
		}
	}
}

void AVLtree::traversalIncidentDate(treeNode* currentnode, int incidentToAdd, bool& searchSuccess) {
	if (currentnode != NULL) {
		if (currentnode->date == incidentToAdd) {
			searchSuccess = true;
			currentnode->incidentsContainer.push_back(incidentToAdd);
		}
		traversalIncidentDate(currentnode->left, incidentToAdd, searchSuccess);
		traversalIncidentDate(currentnode->right, incidentToAdd, searchSuccess);
	}
}


bool AVLtree::searchAddIncident(int incidentToAdd) {
	bool searchSuccess = false;
	traversalIncidentDate(root, incidentToAdd, searchSuccess);
	return searchSuccess;
}

int AVLtree::height(treeNode* node) {
	if (node == NULL) {
		return 0;
	}
	else {
		return node->height;
	}
}

void AVLtree::updateHeight(treeNode* node) {
	node->height = max(height(node->left), height(node->right)) + 1;
}

int AVLtree::BF(treeNode* node) {
	if (node == NULL) {
		return 0;
	}
	else {
		return (height(node->left) - height(node->right));
	}
}

treeNode* AVLtree::leftRotation(treeNode*& currentnode) {
	treeNode* returnNode = currentnode->right;
	treeNode* gKidReplace = returnNode->left;
	returnNode->left = currentnode;
	currentnode->right = gKidReplace;

	updateHeight(currentnode);
	updateHeight(returnNode);

	return returnNode;
}

treeNode* AVLtree::rightRotation(treeNode*& currentnode) {
	treeNode* returnNode = currentnode->left;
	treeNode* gKidReplace = returnNode->right;
	returnNode->right = currentnode;
	currentnode->left = gKidReplace;

	updateHeight(currentnode);
	updateHeight(returnNode);

	return returnNode;
}

treeNode* AVLtree::leftRightRotation(treeNode*& currentnode) {
	currentnode->left = leftRotation(currentnode->left);
	return rightRotation(currentnode);
}

treeNode* AVLtree::rightLeftRotation(treeNode*& currentnode) {
	currentnode->right = rightRotation(currentnode->right);
	return leftRotation(currentnode);
}

treeNode* AVLtree::treeInsert(treeNode* currentnode, treeNode* insertnode) {
	if (currentnode == NULL) {
		return insertnode;
	}
	if (insertnode->date > currentnode->date) {
		currentnode->right = treeInsert(currentnode->right, insertnode);
	}
	else if (insertnode->date < currentnode->date) {
		currentnode->left = treeInsert(currentnode->left, insertnode);
	}
	else {
		return currentnode;
	}

	updateHeight(currentnode);

	int balFac = BF(currentnode);

	if (balFac > 1 && insertnode->date < currentnode->left->date) {
		return rightRotation(currentnode);
	}
	if (balFac < -1 && insertnode->date > currentnode->right->date) {
		return leftRotation(currentnode);
	}
	if (balFac > 1 && insertnode->date > currentnode->left->date) {
		return leftRightRotation(currentnode);
	}
	if (balFac < -1 && insertnode->date < currentnode->right->date) {
		return rightLeftRotation(currentnode);
	}
	return currentnode;
}

void AVLtree::insertNode(int val) { //this is the date
	treeNode* newVal = new treeNode(val);

	root = treeInsert(root, newVal); //might have to pass an incident as well, not sure yet
}

void AVLtree::inOrder() {
	inOrderRecursive(root);
}

void AVLtree::levelOrder() {
	levelOrderRecursive(root);
}

