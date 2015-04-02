#include "tree.h"

void main(int argc, char *argv[])
{
	BinarySearchTree trees[10];
	ofstream file(argv[1]);
	ofstream outputFile(argv[2]);
	ofstream errorFile(argv[3]);

	Comand comand;
	EventCreater eventCreater;
	EventHandler handler;
	FileFiller fileFiller;

	fileFiller.Fill(file);
	file.close();

	ifstream inputFile(argv[1]);
	int currentPos = 0;
	BinarySearchTree defaultList("Default list");
	trees[1] = defaultList;
	int finalPos = 1;
	try
	{
		handler.ListChoiceHandle(trees, currentPos, finalPos);
	}
	catch (invalid_argument& error)
	{
		errorFile << "Wrong choice of list" << '\n';
	}
	while (currentPos == 0)
	{
		cout << "You don't choose any list. Please choose" << endl << endl;
		try
		{
			handler.ListChoiceHandle(trees, currentPos, finalPos);
		}
		catch (invalid_argument& error)
		{
			errorFile << "Wrong choice of list" << '\n';
		}
	}

	cout << "Your list is " << trees[currentPos].GetName() << endl << endl;
	comand = eventCreater.GetComand();
	while (comand.comandNumber != 0)
	{
		if (comand.isWrong)
		{
			cout << "Wrong input. Please try again" << endl << endl;
		}
		else
		{
			handler.Handle(comand, trees, currentPos, finalPos, inputFile, outputFile, errorFile);
		}
		cout << endl;
		cout << "Your list is " << trees[currentPos].GetName() << endl << endl;
		comand = eventCreater.GetComand();
	}

	system("pause");
}