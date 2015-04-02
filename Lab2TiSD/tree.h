#ifndef _tree_h
#define _tree_h
#include <iostream>
#include <fstream>
#include <string>

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

struct Comand
{
	int comandNumber;
	bool isExit;
	bool isWrong;
};

class Queue
{
private:
	QueueElement *_begin, *_end;
public:
	Queue();
	void Enqueue(Node *element);
	void Dequeue();
	bool isEmpty();
	Node* GetTop();
};

class BinaryTree
{
protected:

	Node *_root;
	string _name;

	Node* CreateBinaryTree(ifstream& inputFile, int elementsCount);
	void DeleteElementWithoutChildren(Node *node);
	void DeleteElementWithOneChildren(Node *node);
	void DeleteElementWithTwoChildren(Node *node);
public:
	BinaryTree();
	BinaryTree(ifstream &inputFile, int elementsCount);
	void DeleteElement(char);
	void PreOrderWalk(Node *node);
	void Print(Node *root, int spacesCount);
	void InOrderWalk(Node *root);
	void PostOrderWalk(Node *root);
	void PrintByLevel(Node *root);
	Node* GetRoot();
	string GetName();
	virtual Node* Find(char data);
};

class BinarySearchTree : public BinaryTree
{
public:
	BinarySearchTree();
	BinarySearchTree(string name);
	void InsertNode(char data);
	Node* Find(char data);
};

class EventCreater
{
public:
	Comand GetComand();
	void PrintMenu();
};

class EventHandler
{
public:
	void Handle(Comand, BinarySearchTree lists[], int&, int&, ifstream &inputFile, ofstream &outputFile, ofstream &errorFile);
	void ListChoiceHandle(BinarySearchTree lists[], int&, int&);
};

class FileFiller
{
public:
	void Fill(ofstream &inputFile);
};

#endif