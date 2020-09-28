#include "LinkedList.h"
#include "Node.h"
#include <iostream>
#include <fstream>
#include "conio.h";
#include "XY.h";
#include <Windows.h>
using namespace std;

LinkedList::LinkedList()
{
	Head = nullptr;
	Tail = nullptr;
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

void LinkedList::sleepDot(int milliseconds)
{
	for (int i = 0; i < 4; i++)
	{
		cout << ". ";
		Sleep(milliseconds);
	}
}
void LinkedList::Write()
{
	ofstream OutPutFile;
	char letter = '\0';
	XY xy;
	int x, y;
	x = y = 0;
	Node* current = nullptr;
	Node* Head = nullptr;
	Node* Tail = nullptr;
	Node* rows[10];

	for (int i = 0; i < 10; i++)
	{
		rows[i] = nullptr;
	}
	while (letter != 27) //27 = ESC
	{
		xy.gotoXY(x, y);
		letter = _getch();

		if (letter == -32) //Arrow Key 
		{
			letter = _getch();
			if (letter == 75) //75 = LEFT arrow
			{
				if (x < 0) 
				{
					//If you press LEFT arrow at edge of window, do nothing
				}
				else if (x != 0 && current->prev != nullptr)
				{
					current = current->prev;
					x--;
				}
				else //left arrow at the start of file
				{
					current = Head;
					x = 0;
				}
			}
			if (letter == 77) //77 = right arrow
			{
				if (current->next !=nullptr)//Cursor can go right as long as next node is not NULL
				{
					x++;
					current = current->next;
				}
			}
			if (letter == 72) //72 = UP arrow
			{
				if (y>0)
				{
					y--; //Move Cursor UP
					Head =Tail=current= rows[y];
					for (int i = 0; i < x - 1; i++)
					{
						current = current->next;
					}
				}
			}
			if (letter == 80) //80 = DOWN arrow
			{
				if (y < 10 && rows[y + 1] != nullptr) //if there is a row below, go down a row
				{
					y++;
					Head =Tail= current=rows[y];
					for (int i = 0; i < x - 1; i++)
					{
						current = current->next;
					}
				}
			}
		}
		else if (letter == 13) //13 = enter (start new row)
		{
			x = 0;
			y++;
			Head = Tail = current = nullptr;
		}
		else if (letter == 27) // 27 = ESC
		{
			//do nothing
		}
		else if (letter == 8)// 8 = Backspace
		{
			if (current == Head)
			{
				current = nullptr;
				Head = current;
				if (x != 0)
				{
					x -= 1;
				}
				rows[y]->letter = ' ';
			}
			else if (rows[y] != 0 && current == Head) //delete carriage return
			{
				y--; 
				Head = rows[y];
				current = Head;
				while (current->next)
				{
					current = current->next;
				}
			}
			else if ((current->next == nullptr) && (current->prev)) //Delete at end
			{
				if (current != nullptr)
				{
					x--;
					current = current->prev;
					delete(current->next);
					current->next = nullptr;
					//DeleteLast();
				}
			}
			else if (current->next != nullptr && current->prev != nullptr)//delete in middle
			{
				current->prev->next = current->next;
				current->next->prev = current->prev;
				Node* temp = current->next;
				delete(current);
				current = temp;
				x--;
			}
		}
		else //regular character
		{
			if (Head == nullptr)//first character of file
			{
				Node* temp = new Node(letter);
				Head =Tail= temp;
				current = Head;
				rows[y] = Head;
				//AddFirst(letter, current, rows, y);
			}
			else
			{
				if (x==0)//inserts at front after typing
				{
					Node* temp = new Node(letter);
					temp->next = Head;
					Head->prev = temp;
					temp->prev = nullptr;
					Head = temp;
					rows[y] = Head;
				}
				else if (current->next ==nullptr)//Add at end 
				{
					Node* temp = new Node(letter);
					current->next = temp;
					temp->prev = current;
					Tail = temp;
					current = current->next;
				}
				else //Add character in middle (current->next != nullptr && current -> prev != nullptr)
				{
					Node* temp = new Node(letter);
					temp->next = current->next;
					current->next->prev = temp;
					temp->prev = current;
					current->next = temp;
					current = temp;
				}
			}	
			cout << letter;
			x++;
		}
		system("cls");
		for (int i = 0; i < 10; i++) //Displays Linked List
		{
			if (rows[i] != nullptr)
			{
				Node* current = rows[i];
				while (current != nullptr)
				{
					cout << current->letter;
					current = current->next;
				}
				cout << endl;
			}
		}
		xy.gotoXY(0,11);
		cout << "Row: " << y + 1 << " Column: " << x << " | "<< "ESC to exit";
		xy.gotoXY(x, y);
	}
	//Save to file:
	char input;
	xy.gotoXY(0,10);
	cout<< "Would you like to save? (Y/N)" << endl;
	cin >> input;
	if (input == 'y' ||input =='Y')
	{
		string fileName;
		cout << "Name of file: ";
		cin >> fileName;
		ofstream File;
		File.open(fileName, ios::app);
 
		for (int i = 0; i < 10; i++)
		{
			if (rows[i] != nullptr)
			{
				Node* current = rows[i];
				while (current != nullptr)
				{
					File << current->letter;
					current = current->next;
				}
				File << endl;
			}
		}
		xy.gotoXY(x, y);
		cout << "Saving file ";
		sleepDot(500);
		File.close();
	}
	else 
	{
		exit(0);
	}
}

void LinkedList::AddFirst(char letter, Node* current, Node* rows[10], int y)
{
	Node* temp = new Node();
	temp->letter = letter;
	Head = temp;
	current = Head;
	rows[y] = Head;
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

}

void LinkedList::DeleteFirst()
{
	if (IsEmpty())
	{
		throw exception("Empty List!");
	}
	else
	{
		Node* temp = Head;
		Head = Head->next;
		delete(temp);
	}

}

bool LinkedList::DeleteInMiddle(char letter)
{
	Node* current = Head;
	while (current != nullptr)
	{
		if (current->next != nullptr && current->next->letter == letter)
		{
			current->next = current->next->next;

			return true;
		}
		current = current->next;
	}
	return false;
}

void LinkedList::DeleteLast()
{
	Tail = Tail->prev;
	delete(Tail->next);
	Tail->next = nullptr;
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

}
