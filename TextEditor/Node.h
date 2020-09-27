#pragma once
#include <memory>
class Node
{
private:

public:
	char letter;
	Node* prev{};
	Node* next{};
	Node()
	{
		letter = ' ';
		next = prev = nullptr;
	}
	~Node()
	{

	}
	Node(char input) :letter(input){} //initialization list
};

