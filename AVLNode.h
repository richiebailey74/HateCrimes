#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include "Incident.h"

using namespace std;
class AVLNode {
public:
    int date;
    vector<Incident> incidentContainer;
    AVLNode *left;
    AVLNode *right;
    AVLNode() : date(-1), left(nullptr), right(nullptr) {}
    AVLNode(int date, Incident incident) {this->date = date; incidentContainer.push_back(incident);}

    //functions
    AVLNode* rotateLeft(AVLNode *node);
    AVLNode* rotateRight(AVLNode *node);
    AVLNode* rotateLeftRight(AVLNode *node);
    AVLNode* rotateRightLeft(AVLNode *node);
    int findHeight(AVLNode* node);
    int balanceFactor(AVLNode* current);
    AVLNode* restoreBalance(AVLNode* current);
    AVLNode* insert(AVLNode* root, int year, Incident incident);
};

//ROTATE LEFT function
AVLNode* AVLNode::rotateLeft(AVLNode *node)
{
    if (node == nullptr) {
        return nullptr;
    }
    //this function will take the current node and make it's right child the node

    AVLNode* temp = node; //this is used to store the passed in node
    AVLNode* newParent = temp->right; //this is used to store what will be the returned node

    //changes the right child of the node to be the parent
    temp->right = newParent->left;
    newParent->left = temp;

    //returns the new parent that has the old node as its left child
    return newParent;
}

//ROTATE RIGHT function
AVLNode* AVLNode::rotateRight(AVLNode *node)
{
    if (node == nullptr) {
        return nullptr;
    }
    //the node passed in to this function has a left child and grandchild

    AVLNode* temp = node;
    AVLNode* newParent = temp->left;
    //the current node will now change to its right child's left child
    temp->left = newParent->right;
    newParent->right = temp;

    return newParent;
}

//LEFT RIGHT ROTATE function
AVLNode* AVLNode::rotateLeftRight(AVLNode *node) {
    if (node == nullptr) {
        return nullptr;
    }
    AVLNode* afterRotation = new AVLNode;
    //this function will first perform the left rotation on the left child
    node->left = rotateLeft(node->left);

    //then it will perform the right rotation on the node itself
    afterRotation = rotateRight(node);

    return afterRotation;
}

//RIGHT LEFT ROTATE function
AVLNode* AVLNode::rotateRightLeft(AVLNode *node)
{
    if (node == nullptr) {
        return nullptr;
    }
    AVLNode* afterRotation = new AVLNode;
    //this function will first perform the left rotation on the left child
    node->right = rotateRight(node->right);

    //then it will perform the right rotation on the node itself
    afterRotation = rotateLeft(node);

    return afterRotation;
}

//HEIGHT function
int AVLNode::findHeight(AVLNode* node) {
    //if the node is null then the height of that node is zero
    if (node == nullptr) {
        return 0;
    }

    return 1 + max(findHeight(node->left),findHeight(node->right));
}

//BALANCE FACTOR function
int AVLNode::balanceFactor(AVLNode* current) {
    //use the height function to find the balance factor
    //formula is left subtree height - right subtree height
    return (findHeight(current->left) - findHeight(current->right));
}

//BALANCE function
AVLNode* AVLNode::restoreBalance(AVLNode* current) {
    //find the balance factor of the current node
    int bf = balanceFactor(current);
    //first check if balance factor is zero to save time
    if (bf == 0 || bf == 1 || bf == -1) {
        //this node is balanced so return the current node
        return current;
    }


    // Left Rotation
    if (bf > 1 && current->date > current->left->date) {
        return rotateRight(current);
    } else if (bf < -1 && current->date < current->right->date) {
        //right rotate
        return rotateLeft(current);
    } else if (bf < -1 && current->date > current->right->date) {
        //right left rotate
        return rotateRightLeft(current);
    } else if (bf > 1 && current->date < current->left->date) {
        //left right rotate
        return rotateLeftRight(current);
    }
    return current;
}

//INSERT function
AVLNode* AVLNode::insert(AVLNode* root, int date, Incident incident) {
    //this will only execute if valid == true
    if (root == nullptr) {
        //if the passed in node is null, add the new node here
        AVLNode* newNode = new AVLNode(date, incident);
        cout << "successful" << endl;
        return newNode;
    } else if (date == root->date) {
        //the year already exists within the tree, so add it to the vector
        incidentContainer.push_back(incident);
        return root; //TODO I'm not sure if this is the right thing to return
    } else if (date < root->date) {
        //if the id is less than the root's id, send to the left subtree
        root->left = insert(root->left, date, incident);
    } else if (date > root->date) {
        //if the id is greater than the root's id, send to the right subtree
        root->right = insert(root->right, date, incident);
    }

    if (root == nullptr) {
        return nullptr;
    } else {
        return restoreBalance(root);
    }
}