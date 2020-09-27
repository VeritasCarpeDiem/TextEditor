#include "LinkedList.h"
#include "Node.h"
#include <iostream>
#include <fstream>
#include "conio.h";
#include "XY.h";
using namespace std;

LinkedList::LinkedList()
{
	Head = nullptr;
	Tail = nullptr;
	Count = 0;
}

LinkedList::~LinkedList()
{
	delete Head, Tail;
	//Clear();
}

bool LinkedList::IsEmpty()
{
	if (Head == nullptr)
	{
		return true;
	}
	return false;
}

void LinkedList::DisplayList()
{
	Node* current = Head;
	std::cout << "You entered: ";
	while (current != nullptr)
	{
		std::cout << current->letter;
		current = current->next;
	}
}

void LinkedList::Write()
{
	ofstream OutPutFile;
	char letter='\0';
	XY xy;
	int x, y;
	x = y = 0;
	Node* current = nullptr;
	Node* rows[10];
	for (int i = 0; i < 10; i++)
	{
		rows[i] = nullptr;
	}
	
	while (letter != 27) //27 = ESC
	{
		xy.gotoXY(x, y);
		
		letter = _getch(); 

		//Special character
		if (letter == -32)
		{
			letter = _getch();
			if (letter == 75) //75 = left row
			{
				if (x < 0) //if cursor is at edge of window
				{
					//do nothing
				}
				else if (x != 0 && current->prev != nullptr)
				{
					current = current->prev;
					x--;
				}
				//left rowsow at the beginning of a file
				else
				{
					current = Head;
					x = 0;
				}
			}
			// -> Right 77
			if (letter == 77)
			{
				//right rowsow as long as there is a node after current
				if (current->next != nullptr)
				{
					x++;
					current = current->next;
				}
			}
			// Up rowsow
			if (letter == 72)
			{
				if (y > 0)
				{
					//go up
					y--;
					Head = rows[y];
					current = Head;
					for (int i = 0; i < x - 1; i++)
					{
						current = current->next;
					}
				}
			}
			//Down rowsow
			if (letter == 80)
			{
				//checks to see if there is a line below and if there is
				//it will go down a line
				if (y <= 10 && rows[y + 1] != nullptr)
				{
					y++;
					Head = rows[y];
					current = Head;
					for (int i = 0; i < x - 1; i++)
					{
						current = current->next;
					}
				}
			}
		}
		//Return
		else if (letter == 13)
		{
			x = 0;
			y++;
			Head = nullptr;
			current = nullptr;
		}
		//ESC
		else if (letter == 27)
		{
			//do nothing
		}
		//Backspace
		else if (letter == 8)
		{
			if (current == Head)
			{
				current = nullptr;
				Head = current;
				if (x != 0)
					x -= 1;
				rows[y]->letter = '\0';
			}
			//deletes crowsiage return
			else if (rows[y] != 0 && current == Head)
			{
				//go up
				y--;
				Head = rows[y];
				current = Head;
				while (current->next)
				{
					current = current->next;
				}
			}
			//deletes at end
			else if ((current->next == nullptr) && (current->prev))
			{
				if (current != nullptr)
				{
					x--;
					current = current->prev;
					delete(current->next);
					current->next = nullptr;
				}
			}
			//delete in middle
			else if ((current->next != nullptr) && (current->prev != nullptr))
			{
				/*
				Node* x = current->next;
				current->prev->next = x;
				x->prev = current->prev;
				delete current;
				x = current;
				*/
				current->prev->next = current->next;
				current->next->prev = current->prev;
				Node* tmp = current->next;
				delete(current);
				current = tmp;
				x--;
			}
		}
		//regular character (number, character, special symbols)
		else
		{
			//first character of file
			if (Head == nullptr)
			{
				Node* x = new Node();
				x->letter = letter;
				Head = x;
				current = Head;
				rows[y] = Head;
			}
			else
			{
				//inserts at front after typing
				if (x == 0)
				{
					// Create a new node and assign the character
					Node* x = new Node();
					x->letter = letter;

					// Make the new node the 'Head'
					// and make its next the previous Head's node

					x->next = Head;
					Head->prev = x;
					x->prev = nullptr;
					Head = x;
					rows[y] = Head;
				}
				//insert at end
				else if (current->next == nullptr)
				{
					Node* x = new Node();
					x->letter = letter;
					current->next = x;
					x->prev = current;
					current = current->next; //move currentent
				}
				//insert character in middle
				else
				{
					Node* x = new Node();
					x->letter = letter;
					x->next = current->next;
					current->next->prev = x;
					current->next = x;
					x->prev = current;
					current = x;
				}
			}
			std::cout<< letter;
			x++;
		}
		system("cls");

		//prints linked list
		for (int i = 0; i < 10; i++)
		{
			if (rows[i] != nullptr)
			{
				Node* p;
				p = rows[i];
				while (p != nullptr)
				{
					std::cout<< p->letter;
					p = p->next;
				}
				std::cout << endl;
			}
		}

		xy.gotoXY(x, y);
	}

	//save file
	char input;
	std::cout << endl << endl << "Would you like to save? (y/n)" << endl;
	std::cin >> input;

	if (input == 'y')
	{
		string fileName;
		std::cout << "Name of file: ";
		std::cin >> fileName;
		ofstream myFile;
		myFile.open(fileName, ios::app);

		Node* nodePtr;
		nodePtr = Head;

		for (int i = 0; i < 10; i++)
		{
			if (rows[i] != nullptr)
			{
				Node* p;
				p = rows[i];
				while (p != nullptr)
				{
					myFile << p->letter;
					p = p->next;
				}
				myFile << endl;
			}
		}

		xy.gotoXY(x, y);

		myFile.close();

	}
	else {
		exit(0);
	}
}


void LinkedList::Add(char letter)
{
	Node* current = Head;
	if (IsEmpty())
	{
		Head = new Node(letter);
		Tail = Head;	
	}
	else
	{
		Tail->next = new Node(letter);
		Tail = Tail->next;
	}
	Count++;
}

bool LinkedList::DeleteInMiddle(char letter) //delete in middle
{
	Node* current = Head;
	while (current != nullptr)
	{
		if (current->next !=nullptr && current->next->letter== letter)
		{
			 current->next= current->next->next; 
			 Count--;
			 return true;
		}
		current = current->next;
	}
	return false;
}

Node* LinkedList::Find(char letter)
{
	Node* current = Head;
	while (current != nullptr)
	{
		if (current->letter == letter)
		{
			return current;
		}
		current = current->next;
	}
	return nullptr;
}

bool LinkedList::Contains(char letter)
{
	return Find(letter) != nullptr;
}

void LinkedList::Clear()
{
	Node* current = Head;
	Node* next;
	while (current != nullptr)
	{
		next = current->next;
		free(current);
		current = next;
		
	}
	Head = nullptr;
	Tail = nullptr;
	Count = 0;
}
