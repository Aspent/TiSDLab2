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
	Node *parent;
	//parent = new Node;
	if (elementsCount > 0)
	{
		leftTreeLength = elementsCount / 2;
		rightTreeLength = elementsCount - leftTreeLength - 1;

		node = new Node;
		inputFile >> node->data;

		parent = node;
		node->left = CreateBinaryTree(inputFile, leftTreeLength);
		node->right = CreateBinaryTree(inputFile, rightTreeLength);
		if (node->left != NULL)
		{
			node->left->parent = parent;
		}
		if (node->right != NULL)
		{
			node->right->parent = parent;
		}
		

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

Node* BinaryTree::Find(char data)
{
	Queue queue;
	queue.Enqueue(_root);
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
		if (queue.GetTop()->data == data)
		{
			return queue.GetTop();
		}
		queue.Dequeue();
	}
	return NULL;
}

void BinaryTree::DeleteElementWithoutChildren(Node *node)
{
	if (_root != node)
	{
		if (node->parent->left == node)
		{
			node->parent->left = NULL;
		}
		else
		{
			node->parent->right = NULL;
		}
	}
	else
	{
		_root = NULL;
	}
	delete node;
}

void BinaryTree::DeleteElementWithOneChildren(Node *node)
{
	if (node->right != NULL)
	{
		if (_root != node)
		{
			node->right->parent = node->parent;
			if (node->parent->left == node)
			{
				node->parent->left = node->right;
			}
			else
			{
				node->parent->right = node->right;
			}
		}
		else
		{
			_root = node->right;
		}
		delete node;
		return;
	}

	else
	{
		if (_root != node)
		{
			node->left->parent = node->parent;
			if (node->parent->left == node)
			{
				node->parent->left = node->left;
			}
			else
			{
				node->parent->right = node->left;
			}
		}
		else
		{
			_root = node->left;
		}
		delete node;
	}
}

void BinaryTree::DeleteElementWithTwoChildren(Node *node)
{
	Node* temp = node->right;
	while (temp->left != NULL)
	{
		temp = temp->left;
	}
	if (_root != node)
	{
		
		temp->parent->left = temp->right;
		//temp->parent->left = NULL;
		temp->parent = node->parent;
		temp->left = node->left;
		temp->right = node->right;

		node->right->parent = temp;
		node->left->parent = temp;
		
		if (node->parent->left == node)
		{
			node->parent->left = temp;
		}
		else
		{
			node->parent->right = temp;
		}
	}
	else
	{
		temp->parent->left = temp->right;
		temp->left = node->left;
		temp->right = node->right;

		node->right->parent = temp;
		node->left->parent = temp;
		temp->parent = NULL;
		_root = temp;

	}
	delete node;
}

void BinaryTree::DeleteElement(char element)
{
	Node* node;
	node = Find(element);

	if (node->left == NULL && node->right == NULL)
	{
		DeleteElementWithoutChildren(node);
		return;
	}

	if (node->left == NULL || node->right == NULL)
	{
		DeleteElementWithOneChildren(node);
		return;
	}

	if (node->left != NULL && node->right != NULL)
	{
		DeleteElementWithTwoChildren(node);
	}
}