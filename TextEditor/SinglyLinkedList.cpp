#include "SinglyLinkedList.h"
#include "Node.h"
#include <iostream>
SinglyLinkedList::SinglyLinkedList()
{
	Head = nullptr;
	Tail = nullptr;
	Count = 0;
}

SinglyLinkedList::~SinglyLinkedList()
{
	delete Head, Tail;
}

bool SinglyLinkedList::IsEmpty()
{
	if (Head == nullptr)
	{
		return true;
	}
	return false;
}

void SinglyLinkedList::DisplayList()
{
	Node* current = Head;
	std::cout << "You entered: ";
	while (current != nullptr)
	{
		std::cout << current->letter;
		current = current->next;
	}
}


void SinglyLinkedList::Add(char letter)
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

bool SinglyLinkedList::Remove(char letter)
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

Node* SinglyLinkedList::Find(char letter)
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

bool SinglyLinkedList::Contains(char letter)
{
	return Find(letter) != nullptr;
}
