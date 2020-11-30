#pragma once
#include "Bread.h"
#include <iostream>
using namespace std;
class Node {
public:
	Bread data;
	Node* next;
};

class LinkedList {
private:
	Node* head;
public:
	LinkedList()
	{
		head = NULL;
	}
	~LinkedList() {};
	void addNode(Bread b);
	void reverseList();
	void display();
};