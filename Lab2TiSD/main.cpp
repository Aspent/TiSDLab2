#include "tree.h"

void main(int argc, char argv[])
{
	ifstream inputFile("Input.txt");
	BinaryTree tree(inputFile, 26);
	
	tree.InOrderWalk(tree.GetRoot());

	system("pause");
}