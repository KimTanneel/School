// StudentManagementCPlusPlus.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

//include the below additional libraries
#include <iostream>
#include <windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>
#include "DBHelper.h"
#include "Bread.h"
//use the std namespace
using namespace std;
int main()
{
	DBHelper database;
	//Student* students[100];
	database.init();
	database.execute();
	//Bread* Breads = database.getBreads();
	//for (int i = 0; i < 2; i++)
	//{
	//	Breads[i].print();
	//}
	database.close();
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
