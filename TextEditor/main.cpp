#include <iostream>
#include <memory>
#include <conio.h>
#include <fstream>
#include "Node.h";
#include "LinkedList.h";
#include "XY.h";
#include "changeColor.h";
using namespace std;

int displayMenu()
{
	changeColor color{};
	XY xy{};
	char input;
	int option = 1; //1= New file 2= Open File 3= Exit

	color.changeTextColor(143);
	cout << "[FILE]" << " " << "[EDIT]" << " " << "[FORMAT]" << " " << "[VIEW]" << " " << "[HELP]";
	color.changeTextColor(240);
	xy.gotoXY(40, 13);
	cout << "   1. New   " << endl;
	xy.gotoXY(40, 14);
	cout << "   2. Open   " << endl;
	xy.gotoXY(40, 15);
	color.changeTextColor(252);
	cout << "   3. Exit   " << endl;
	color.changeTextColor(240);
	xy.gotoXY(43, 20);
	cout << "Press Enter to select";

	while (true)
	{
		if (_kbhit())
		{
			input = _getch();
			if (input == 13) //32 =spacebar
			{
				break;
			}
			if (input == -32) //arrow key
			{
				input = _getch();
				if (input == 72) //72 = UP arrow
				{
					if (option > 1)
					{
						xy.gotoXY(40, 13);
						cout << "   1. New   ";
						xy.gotoXY(40, 14);
						cout << "   2. Open   ";
						xy.gotoXY(40, 15);
						color.changeTextColor(252);
						cout << "   3. Exit   ";
						color.changeTextColor(240);
						option--;
					}
				}
				else if (input == 80) //80 = DOWN arrow
				{
					if (option < 3) 
					{
						xy.gotoXY(40, 13);
						cout << "   1. New   ";
						xy.gotoXY(40, 14);
						cout << "   2. Open   ";
						xy.gotoXY(40, 15);
						color.changeTextColor(252);
						cout << "   3. Exit   ";
						color.changeTextColor(240);
						option++;
					}
				}
			}
		}
		if (option == 1) 
		{
			xy.gotoXY(40, 13);
			Sleep(500);
			xy.gotoXY(40, 13);
			cout << "-> 1. New <-";
			Sleep(500);
		}
		if (option == 2) 
		{
			xy.gotoXY(40, 14);
			Sleep(500);
			xy.gotoXY(40, 14);
			cout << "-> 2. Open <-";
			Sleep(500);
		}
		if (option == 3)
		{
			xy.gotoXY(40, 15);
			Sleep(500);
			xy.gotoXY(40, 15);
			color.changeTextColor(252);
			cout << "-> 3. Exit <-";
			color.changeTextColor(240);
			Sleep(500);
		}

	}
	return option;
}
void openFile()
{
	LinkedList Editor{};
	std::string fileName, text;
	std::cout << "Enter path of your file:";
	std::cin >> fileName;
	system("cls");

	ifstream file;
	file.open(fileName, ios::app); //append to the existing file

	while (!file.eof())
	{
		while (file >> text)
			cout << text << " ";
	}

	Editor.Write();
}

int main()
{
	LinkedList Editor{};
	int option = 0;
	system("color F0");
	option = displayMenu();
	
	switch (option)
	{
	case 1:
		system("cls");
		Editor.Write();
		break;
	case 2:
		system("cls");
		openFile();
		break;
	default:
		break;
	}

	return 0;
}