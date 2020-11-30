#include "Bread.h"
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
	void print();
};
template <typename DATA>
LinkedList<DATA>::LinkedList() {
	this->length = 0;
	this->head = nullptr;
}
template <typename DATA>
LinkedList<DATA>::~LinkedList() {
	std::cout << "LIST DELETED";
}
template <class DATA>
void LinkedList<DATA>::addfirst(DATA data) {
	Node<DATA>* node = new Node<DATA>();
	node->data = data;
	node->next = this->head;
	this->head = node;
	this->length++;
}
template <class DATA>
void LinkedList<DATA>::addtail(DATA data) {
	Node<DATA>* node = new Node<DATA>();
	Node<DATA>* temp = new Node<DATA>();
	node->data = data;
	node->next = NULL;
	temp = head;
	if (head == NULL) {
		node->next = this->head;
		this->head = node;
	}
	else
	{
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = node;
	}
	this->length++;
}
template <class DATA>
bool LinkedList<DATA>::find(string data) {
	Node<DATA>* node = new Node<DATA>();
	if (this->head == NULL) {
		return false;
	}
	Bread* temp = new Bread;
	temp = node->data;
	while (temp->getname() != data)
	{
		if (node->next = NULL) {
			cout << "\nKhong co trong danh sach." << endl;
			return false;
		}
		else {
			node = node->next;
		}
		temp = node->data;
	}
	/*Bread* temp = new Bread;
	temp = node->data;*/
	temp->xuat();
	return true;
}
template <class DATA>
void LinkedList<DATA>::remove(string data) {
	Node<DATA>* node = new Node<DATA>();
	node = head;
	Node<DATA>* temp = new Node<DATA>();
	temp = NULL;
	Bread* bm = new Bread();
	bm = node->data;
	if (find(data)) {
		while (bm->getname() != data)
		{
			node = node->next;
			bm = node->data;
		}
		if (node == head) {
			temp = head;
			head = node->next;
			delete temp;
		}
		else if (node->next == NULL) {
			node = head;
			while (node->next->next != NULL) {
				node = node->next;
			}
			temp = node;
			delete node->next;
			temp->next = NULL;
		}
		else {
			temp = node;
			bm = temp->data;
			Bread* tmp = new Bread();
			node = head;
			while (tmp->getname() != bm->getname()) {
				node = node->next;
				tmp = (node->next)->data;
			}
			/* while (SoSanh(tmp->getname(), nv->getname())) {
				 node = node->next;
				 tmp = (node->next)->data;
			 }*/
			node->next = temp->next;
			delete temp;
		}
	}
	else {
		cout << "\nban da nhap sai thong tin";
	}
}
template <typename DATA>
void LinkedList<DATA>::Print() {
	Node<DATA>* head = this->head;
	int i = 1;
	while (head) {
		Bread* temp = new Bread;
		temp = head->data;
		cout << i << ": ";
		temp->xuat();
		cout << endl;
		head = head->next;
		i++;
	}
}