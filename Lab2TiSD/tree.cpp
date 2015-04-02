#include "tree.h"

Queue::Queue()
{
	_begin = NULL;
	_end = NULL;
}

void Queue::Enqueue(Node *element)
{
	QueueElement *queueElement;
	queueElement = new QueueElement;
	queueElement->data = element;
	queueElement->next = NULL;

	if (_begin == NULL)
	{
		_begin = queueElement;
	}
	else
	{
		_end->next = queueElement;
	}
	_end = queueElement;
}

void Queue::Dequeue()
{
	QueueElement *temp;
	temp = _begin;
	_begin = temp->next;
	delete temp;
}

bool Queue::isEmpty()
{
	if (_begin == NULL)
	{
		return true;
	}
	return false;
}

Node* Queue::GetTop()
{
	return _begin->data;
}

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

void BinaryTree::Print(Node *root, int spacesCount)
{
	if (root != NULL)
	{
		Print(root->right, spacesCount + 2);
		for (int i = 0; i < spacesCount; i++)
		{
			cout << " ";
		}
		cout << root->data << endl;
		Print(root->left, spacesCount + 2);
	}
}

void BinaryTree::PrintByLevel(Node *root)
{
	Queue queue;
	queue.Enqueue(root);
	while (!queue.isEmpty())
	{
		if (queue.GetTop()->left != NULL)
		{
			queue.Enqueue(queue.GetTop()->left);
		}
		if (queue.GetTop()->right != NULL)
		{
			queue.Enqueue(queue.GetTop()->right);
		}
		cout << queue.GetTop()->data << " ";
		queue.Dequeue();
	}
}

Node* BinaryTree::GetRoot()
{
	return _root;
}