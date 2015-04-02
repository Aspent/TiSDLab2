#include "tree.h"

BinaryTree::BinaryTree()
{
	root = NULL;
}

Node *BinaryTree::CreateBinaryTree(ifstream &inputFile, int elementsCount)
{
	int leftTreeLength, rightTreeLength;
	Node *node;
	if (elementsCount > 0)
	{
		leftTreeLength = elementsCount / 2;
		rightTreeLength = elementsCount - leftTreeLength - 1;
		node = new Node;
		inputFile >> node->data;
		node->left = CreateBinaryTree(inputFile, leftTreeLength);
		node->right = CreateBinaryTree(inputFile, rightTreeLength);
	}
	else
	{
		node = NULL;
	}
	return node;
}