#ifndef _tree_h
#define _tree_h
#include <iostream>
#include <fstream>

using namespace std;

struct Node
{
	char data;
	Node *left, *right, *parent;
};

class BinaryTree
{
private:
	Node *_root;
public:
	BinaryTree();
	BinaryTree(ifstream &inputFile, int elementsCount);
	Node* CreateBinaryTree(ifstream& inputFile, int elementsCount);
	void DeleteElement(char element);
	void InOrderWalk(Node *root);
	void PrintByLevel();
	Node* GetRoot();
};

#endif