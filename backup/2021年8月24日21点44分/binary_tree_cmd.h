#ifndef BINARY_TREE_CMD_H
#define BINARY_TREE_CMD_H
#include <iostream>
#include <QDebug>
using namespace std;

class BinarySearchTree {
private:
    int data;
    BinarySearchTree* lchild;
    BinarySearchTree* rchild;
public:
    BinarySearchTree* FindMin(BinarySearchTree* BST);	//completed
    BinarySearchTree* FindMax(BinarySearchTree* BST);	//completed
    BinarySearchTree* Find(BinarySearchTree* BST, int data);	//completed
    BinarySearchTree* Insert(BinarySearchTree* BST, int data);	//completed
    BinarySearchTree* Create(int* data, int size);				//completed
    void PreorderTraversal(BinarySearchTree* T);				//completed
    void InorderTraversal(BinarySearchTree* T);					//in progress
    void PostorderTraversal(BinarySearchTree* T);				//in progress
    BinarySearchTree* Delete(BinarySearchTree* BST, int data);	//completed
    int GetData(BinarySearchTree* BST);							//completed
    int GetHeight(BinarySearchTree* BST);                       //completed, may be buggy
    BinarySearchTree* Getlchild(BinarySearchTree* BST);         //in progress
    BinarySearchTree* Getrchild(BinarySearchTree* BST);         //in progress
};
#endif
