#pragma once
#include <memory>
class Node
{
private:

public:
	char letter;
	Node* prev{};
	Node* next{};
	Node(); 
	~Node()
	{
		delete prev, next;
	}
	Node(char input) :letter(input){} //initialization list
};

