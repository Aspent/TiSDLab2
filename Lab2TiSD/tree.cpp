#include "tree.h"

BinaryTree::BinaryTree()
{
	_root = NULL;
}

BinaryTree::BinaryTree(ifstream &inputFile, int elementsCount)
{
	_root = CreateBinaryTree(inputFile, elementsCount);
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

void BinaryTree::InOrderWalk(Node *root)
{
	if (root != NULL)
	{
		InOrderWalk(root->left);
		cout << root->data << " ";
		InOrderWalk(root->right);
	}

}

Node* BinaryTree::GetRoot()
{
	return _root;
}