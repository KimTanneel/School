#include "Bread.h"
#include <string.h>
#include <iostream>
using namespace std;
Bread::Bread()
{
	strcpy_s(ID, "");
	strcpy_s(name, "");
	strcpy_s(price, "");
	strcpy_s(detail, "");
	result = 7;
}


Bread::Bread(char* _ID, char* _name,char* _price, char* _detail, float _result)
{
	strcpy_s(ID, 10, _ID);
	strcpy_s(name, 50, _name);
	strcpy_s(price, 20, _price);
	strcpy_s(name, 50, _detail);

	result = _result;
}

Bread::~Bread()
{
}
//=================== NHAP THONG TIN SINH VIEN =======================
void Bread::scan() {
	cout << "-> Thong tin banh mi:" << endl;
	cout << "\tma banh: ";
	fflush(stdin); cin.getline(ID, 10);
	cout << "\tTen banh: ";
	fflush(stdin); cin.getline(name, 50);
	cout << "\tthanh tien: ";
	fflush(stdin); cin >> result ;
}

void Bread::Print()
{
	cout << "\tma banh\t:" << ID << endl;
	cout << "\tTen banh\t:" << name << endl;
	cout << "\tthanh tien\t:" << result << endl;
}
