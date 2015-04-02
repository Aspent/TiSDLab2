#include "tree.h"

void main(int argc, char argv[])
{
	ifstream inputFile("Input.txt");
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


	system("pause");
}