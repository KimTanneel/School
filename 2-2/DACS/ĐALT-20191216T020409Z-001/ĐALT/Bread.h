#pragma once
#include<string>
#include<iostream>
#include<iomanip>
using namespace std; 
template <typename DATA>
class Node
{
public:
	Node* next;
	DATA data;
};

using namespace std;

template <typename DATA>
class LinkedList
{
public:
	int length;
	Node<DATA>* head;
	LinkedList();
	~LinkedList();
	void addfirst(DATA data);
	void addtail(DATA data);
	void remove(string data);
	bool find(string data);
	void Print();
	 string getname(DATA x);
};
class Bread
{
protected:
	char ID[10];
	char name[50];
	char price[20];
	char detail[50];
	float result;
public:
	Bread();
	Bread(char* ID, char* name,char* price,char* detail, float result);
	~Bread();
	void scan();
	void Print();
	string getname(string x);
	friend istream& operator >> (istream& is, Bread& b)
	{
		cout << "bread name: "; fflush(stdin); is.getline(b.name,50);
		cout << "bread ID: "; fflush(stdin); is.getline(b.ID,10);
		cout << "bread price: "; fflush(stdin); is.getline(b.price,20);
		cout << "bread detail: "; fflush(stdin); is.getline(b.detail,50);
		return is;
	}
	friend ostream& operator << (ostream& os, Bread& b)
	{
		os << setw(12) << left << b.ID << setw(15) << left << b.name << setw(30) << left << b.price << setw(15) << left << b.detail;
		cout << endl;
		return os;
	}
};

