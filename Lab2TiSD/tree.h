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

struct QueueElement
{
	Node* data;
	QueueElement *next;
};

class Queue
{
private:
	QueueElement *_begin, *_end;
public:
	Queue();
	void Enqueue(Node *element);
	void Dequeue();
	void Show();
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
	void Print(Node *root, int spacesCount);
	void InOrderWalk(Node *root);
	void PrintByLevel(Node *root);
	Node* GetRoot();
};

#endif