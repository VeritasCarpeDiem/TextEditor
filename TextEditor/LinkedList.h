#pragma once
#include "Node.h"
#include <fstream>
class LinkedList
{
private:
	Node* Head{};
	Node* Tail{};
	
public:
	LinkedList();
	~LinkedList();

	bool IsEmpty();
	void DisplayList();

	//function to Write on Notepad
	void Write();

	//Add functions:
	void AddFirst(char letter, Node* current, Node* rows[10], int y);
	void Add(char letter);
	void AddLast(char letter);

	//Delete functions:
	void DeleteFirst();
	bool DeleteInMiddle(char letter);
	void DeleteLast();

	Node* Find(char letter);
	bool Contains(char letter);
	void Clear();
};

