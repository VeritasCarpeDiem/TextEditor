#pragma once
#include "Node.h"
#include <fstream>
class LinkedList
{
private:
	Node* Head{};
	Node* Tail{};
	int Count{};
public:
	LinkedList();
	~LinkedList();

	bool IsEmpty();
	void DisplayList();

	void Write();

	void Add(char letter);

	bool DeleteInMiddle(char letter);

	Node* Find(char letter);
	bool Contains(char letter);
	void Clear();
};

