#include "tree.h"
#include <string>

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

void BinaryTree::PreOrderWalk(Node *root)
{
	if (root != NULL)
	{
		cout << root->data << " ";
		PreOrderWalk(root->left);
		InOrderWalk(root->right);
	}
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

void BinaryTree::PostOrderWalk(Node *root)
{
	if (root != NULL)
	{
		PreOrderWalk(root->left);
		InOrderWalk(root->right);
		cout << root->data << " ";
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

string BinaryTree::GetName()
{
	return _name;
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

BinarySearchTree::BinarySearchTree()
{
	_root = NULL;
}

BinarySearchTree::BinarySearchTree(string name)
{
	_root = NULL;
	_name = name;
}

Node* BinarySearchTree::Find(char data)
{
	Node *node = _root;
	while (node != NULL)
	{
		if (data < node->data)
		{
			node = node->left;
		}
		if (data > node->data)
		{
			node = node->right;
		}
		if (data == node->data)
		{
			return node;
		}
	}
	return NULL;
}

void BinarySearchTree::InsertNode(char data)
{
	Node *currentNode;
	Node *node;
	node = new Node;
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;

	if (_root == NULL)
	{
		_root = node;
	}
	else
	{
		currentNode = _root;
		while (!((data < currentNode->data && currentNode->left == NULL) ||
			(data > currentNode->data && currentNode->right == NULL)))
		{

			if (data < currentNode->data)
			{
				currentNode = currentNode->left;
			}
			else
			{
				currentNode = currentNode->right;
			}
		}
		if (data < currentNode->data)
		{
			currentNode->left = node;
		}
		else
		{
			currentNode->right = node;
		}
		node->parent = currentNode;
	}

}


void EventCreater::PrintMenu()
{
	cout << "Press 1 to create binary tree with alphabet and delete all vowels " << endl << endl;;
	cout << "Press 2 to insert element to tree" << endl << endl;
	cout << "Press 3 to delete element from tree" << endl << endl;
	cout << "Press 4 to walk tree" << endl << endl;
	cout << "Press 5 to show list" << endl << endl;
	cout << "Press 6 to change list" << endl << endl;
	cout << "Press 0 to exit" << endl << endl;
}

Comand EventCreater::GetComand()
{
	const int minComandNum = 0;
	const int maxComandNum = 8;
	PrintMenu();
	int comandNum;
	cin >> comandNum;
	Comand comand;
	comand.comandNumber = comandNum;
	if ((comandNum < minComandNum) || (comandNum > maxComandNum))
	{
		comand.isWrong = true;
	}
	else
	{
		comand.isWrong = false;
	}
	return comand;
}

void EventHandler::Handle(Comand comand, BinarySearchTree trees[], int &numOfList, int &numOfLastList, ifstream &inputFile, ofstream &outputFile, ofstream &errorFile)
{
	int count;
	char ch;
	switch (comand.comandNumber)
	{
	case 0:
		break;
	case 1:
	{
			  BinaryTree tree(inputFile, 26);

			  tree.Print(tree.GetRoot(), 1);
			  cout << endl;
			  tree.InOrderWalk(tree.GetRoot());
			  cout << endl;
			  tree.PrintByLevel(tree.GetRoot());
			  cout << endl;

			  tree.DeleteElement('A');
			  tree.DeleteElement('E');
			  tree.DeleteElement('O');
			  tree.DeleteElement('I');
			  tree.DeleteElement('U');

			  tree.Print(tree.GetRoot(), 1);
			  cout << endl;
			  tree.InOrderWalk(tree.GetRoot());
			  cout << endl;
			  tree.PrintByLevel(tree.GetRoot());
			  cout << endl;

	}
		break;
	case 2:
		cout << "Input count of elements you want to add" << endl;
		cin >> count;
		for (int i = 0; i < count; i++)
		{
			cout << "Input char element you want to insert" << endl;
			char elementValue;
			cin >> elementValue;

			int position;
			cin >> position;
			trees[numOfList].InsertNode(elementValue);
		}
		break;
	case 3:
		cout << "Input count of elements you want to delete" << endl;
		cin >> count;
		for (int i = 0; i < count; i++)
		{
			cout << "Input char element you want to delete." << endl;
			char element;
			cin >> element;
			try
			{
				trees[numOfList].DeleteElement(element);
			}
			catch (invalid_argument& error)
			{
				errorFile << "Wrong position to delete" << '\n';
			}
		}
		break;
	case 4:
		cout << "Press 1 for preorder walk" << endl << endl;;
		cout << "Press 2 for inorder walk" << endl << endl;
		cout << "Press 3 for postorder walk" << endl << endl;
		cout << "Press 4 to print by levels" << endl << endl;


		cin >> ch;

		switch (ch)
		{
		case '1':
			trees[numOfList].PreOrderWalk(trees[numOfList].GetRoot());
			break;
		case '2':
			trees[numOfList].InOrderWalk(trees[numOfList].GetRoot());
			break;
		case '3':
			trees[numOfList].PostOrderWalk(trees[numOfList].GetRoot());
			break;
		case '4':
			trees[numOfList].PrintByLevel(trees[numOfList].GetRoot());
			break;
		}
	case 5:
		trees[numOfList].Print(trees[numOfList].GetRoot(), 1);
		break;
	case 6:
		try
		{
			ListChoiceHandle(trees, numOfList, numOfLastList);
		}
		catch (invalid_argument& error)
		{
			errorFile << "Wrong choice of list" << '\n';
		}
		break;
	default:
		cout << "Wrong input" << endl;
		break;
		cin >> ch;
	}
		
	
}


void EventHandler::ListChoiceHandle(BinarySearchTree trees[], int &numOfList, int &numOfLastList)
{
	cout << "Press 1 to create new tree" << endl << endl;
	cout << "Press 2 to choose tree" << endl << endl;
	cout << "Press 0 to exit" << endl;
	int com;
	cin >> com;
	cout << endl;
	while (com != 0)
	{
		switch (com)
		{
		case 1:
		{
				  string str;
				  getline(cin, str);
				  cout << "Input name of tree" << endl;
				  getline(cin, str);
				  BinarySearchTree list(str);
				  numOfLastList++;
				  trees[numOfLastList] = list;
		}
			break;
		case 2:
			for (int i = 1; i <= numOfLastList; i++)
			{
				cout << "Input " << i << " to choose " << trees[i].GetName() << endl;
			}
			int choice;
			cin >> choice;
			if (choice >= 1 && choice <= numOfLastList)
			{
				numOfList = choice;
			}
			else
			{
				throw invalid_argument("Wrong choice of tree");
			}
			break;
		}

		cout << "Press 1 to create new tree" << endl << endl;
		cout << "Press 2 to choose tree" << endl << endl;
		cout << "Press 0 to exit" << endl;
		cin >> com;
		cout << endl;
	}
}



void FileFiller::Fill(ofstream &inputFile)
{
	for (char i = 'A'; i <= 'Z'; i++)
	{
		inputFile << i;
	}
}

