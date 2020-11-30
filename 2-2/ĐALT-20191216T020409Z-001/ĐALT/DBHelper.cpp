#include "DBHelper.h"
#include "Bread.h"
#include <iostream>
#include<string>
#include<sql.h>
#include<sqltypes.h>
#include<stdlib.h>
#include<Windows.h>
#include<iomanip>
using namespace std;
string createDeleteBrString(int ID3)
{
	return "Delete from Bread where ID = " + to_string(ID3);
}

void DBHelper::command(char ch) {
	cin.ignore(1);
	if (toupper(ch) == 'C') execute();
	else if (toupper(ch) == 'K') exit(0);
	else cout << "Unknown" << endl;
}
string CreatString(int ID, string name, string price, string detail)
{
	string h = ",";
	string e = "'";
	string l = ");";
	string str1 = "insert into Bread values (" + to_string(ID) + h + e + name + e + h + e + price + e + h + e + detail + e + l;

	// 
	return str1;
}

wstring s2ws(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}
void DBHelper::init()
{
	//initializations
	sqlConnHandle = NULL;
	sqlStmtHandle = NULL;
	//allocations
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlEnvHandle))
		close();

	if (SQL_SUCCESS != SQLSetEnvAttr(sqlEnvHandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
		close();

	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, sqlEnvHandle, &sqlConnHandle))
		close();

	//output
	cout << "Attempting connection to SQL Server...";
	cout << "\n";

	//connect to SQL Server	
	//I am using a trusted connection and port 14808
	//it does not matter if you are using default or named instance
	//just make sure you define the server name and the port
	//You have the option to use a username/password instead of a trusted connection
	//but is more secure to use a trusted connection
	switch (SQLDriverConnect(sqlConnHandle,
		NULL,
		//(SQLWCHAR*)L"DRIVER={SQL Server};SERVER=localhost, 1433;DATABASE=master;UID=username;PWD=password;",
		(SQLWCHAR*)L"DRIVER={SQL Server};SERVER=LAPTOP-2D5RT7KK\MSSQLSERVER01;DATABASE=Bakery;Trusted=true;",
		SQL_NTS,
		retconstring,
		1024,
		NULL,
		SQL_DRIVER_NOPROMPT)) {

	case SQL_SUCCESS:
		cout << "Successfully connected to SQL Server";
		cout << "\n";
		break;

	case SQL_SUCCESS_WITH_INFO:
		cout << "Successfully connected to SQL Server";
		cout << "\n";
		break;

	case SQL_INVALID_HANDLE:
		cout << "Could not connect to SQL Server";
		cout << "\n";
		close();
		break;

	case SQL_ERROR:
		cout << "Could not connect to SQL Server";
		cout << "\n";
		close();
		break;

	default:
		break;
	}

	//if there is a problem connecting then exit application
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sqlConnHandle, &sqlStmtHandle))
		close();

}

void DBHelper::execute()
{
	//output
	cout << "\n";
	cout << "Executing T-SQL query...";
	cout << "\n";
	int question = 1;
	char ch;
	cout << "You choice the sql command to execute: 1.SELECT, 2.INSERT, 3.UPDATE, 4.DELETE:";
	cin >> question;
	//if there is a problem executing the query then exit application
	//else display query result

	switch (question) {
	case 1:
	{
		if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)L"SELECT * FROM Bread", SQL_NTS)) {
			cout << "Error querying SQL Server";
			cout << "\n";
			close();
		}
		else {

			//declare output variable and pointer
			SQLCHAR sqlVersion[SQL_RESULT_LEN];
			SQLLEN ptrSqlVersion;
			char name[50];
			char price[20];
			int ID;
			char detail[50];

			while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS) {

				SQLGetData(sqlStmtHandle, 1, SQL_C_ULONG, &ID, SQL_RESULT_LEN, &ptrSqlVersion);
				SQLGetData(sqlStmtHandle, 2, SQL_CHAR, name, SQL_RESULT_LEN, &ptrSqlVersion);
				SQLGetData(sqlStmtHandle, 3, SQL_CHAR, price, SQL_RESULT_LEN, &ptrSqlVersion);
				SQLGetData(sqlStmtHandle, 4, SQL_CHAR, detail, SQL_RESULT_LEN, &ptrSqlVersion);

				//display query result
				cout << "\nBanh: " << ID << " " << name << " " << price << " " << detail << " " << endl;
			}

			cout << "\n";
			cout << "Tiep tuc hay ko (C/K) ?: ";
			cin >> ch;
			cin.ignore(1);
			command(ch);
			break;
		}
	}
	case 2:
	{
		string name1, price1, detail1;
		int ID1;
		cout << "Nhap ID, name , price , detail: ";
		cin >> ID1 >> name1 >> price1 >> detail1;
		string str = CreatString(ID1, name1, price1, detail1);
		std::cout << str;
		wstring a = s2ws(str);
		LPCWSTR result = a.c_str();
		if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)result, SQL_NTS)) {
			cout << "  ";
			cout << "\n";
			close();
		}
		cout << "\n";
		cout << "Tiep tuc hay ko (C/K) ?: ";
		cin >> ch;
		cin.ignore(1);
		command(ch);
		break;
	}
	/*case 3:
	{
		SQLCHAR sqlVersion[SQL_RESULT_LEN];
		SQLLEN ptrSqlVersion;
		char name1[50];
		char price1[20];
		int ID1=0;
		char detail1[50];
		string str1 = createUpdateBrString(ID1, name1, price1, detail1);
		std::cout << str1;
		wstring a = s2ws(str1);
		LPCWSTR result = a.c_str();
		cout << "\n";
		cout << "Tiep tuc hay ko (C/K) ?: ";
		cin >> ch;
		cin.ignore(1);
		command(ch);
		break;
	}
	case 4:
	{
		int ID3;
		cout << "ID want to delete: ";
		cin >> ID3;
		string str2 = createDeleteBrString(ID3);
		cout << str2;
		cout << "\n";
		cout << "Tiep tuc hay ko (C/K) ?: ";
		cin >> ch;
		cin.ignore(1);
		command(ch);
		break;
	}*/
	}

}



Bread* DBHelper::getBreads()
{
	Bread* Breads[100];
	//output
	cout << "\n";
	cout << "Executing T-SQL query...";
	cout << "\n";

	//if there is a problem executing the query then exit application
	//else display query result
	if (SQL_SUCCESS != SQLExecDirect(sqlStmtHandle, (SQLWCHAR*)L"INSERT * INTO Bread", SQL_NTS)) {
		cout << "Error querying SQL Server";
		cout << "\n";
		close();
	}
	else {

		//declare output variable and pointer
		SQLCHAR sqlVersion[SQL_RESULT_LEN];
		SQLLEN  ptrSqlVersion;
		char ID[10];
		char name[50];
		char price[20];
		char detail[50];
		float result;
		int i = 0;
		while (SQLFetch(sqlStmtHandle) == SQL_SUCCESS) {

			SQLGetData(sqlStmtHandle, 1, SQL_CHAR, ID, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 2, SQL_CHAR, name, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 3, SQL_CHAR, price, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 4, SQL_CHAR, detail, SQL_RESULT_LEN, &ptrSqlVersion);
			SQLGetData(sqlStmtHandle, 5, SQL_FLOAT, &result, 0, &ptrSqlVersion);

			//display query result
			cout << "\nBread Name: " << ID << " " << name << " " << price << " " << detail << " " << result << endl;
			Breads[i] = new Bread(ID, name, price, detail, result);
			i++;
		}
	}
	return *Breads;
}

void DBHelper::close()
{
	SQLFreeHandle(SQL_HANDLE_STMT, sqlStmtHandle);
	SQLDisconnect(sqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_DBC, sqlConnHandle);
	SQLFreeHandle(SQL_HANDLE_ENV, sqlEnvHandle);
	getchar();
	exit(0);
}