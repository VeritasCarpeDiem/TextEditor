#include <iostream>
#include <memory>
#include <conio.h>
#include "Node.h";
#include "SinglyLinkedList.h";

int main()
{
	char input;
	SinglyLinkedList Editor{};
	std::cout << "Start typing: " << std::endl;
	while (true)
	{
		input = _getch();
		std::cout << input;
		if (input == 27)
		{
			break;
		}
		Editor.Add(input);

	}
	
	system("cls");
	Editor.DisplayList();

	return 0;
}