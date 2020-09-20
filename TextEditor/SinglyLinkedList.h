#pragma once
#include "Node.h"

class SinglyLinkedList
{
private:
	Node* Head{};
	Node* Tail{};
	int Count{};
public:
	SinglyLinkedList();
	~SinglyLinkedList();
	bool IsEmpty();
	void DisplayList();
	void Add(char letter);
	bool Remove(char letter);
	Node* Find(char letter);
	bool Contains(char letter);
};

