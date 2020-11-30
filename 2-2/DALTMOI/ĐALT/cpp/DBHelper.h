#pragma once

#include <windows.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <sql.h>
#include "Bread.h"
class DBHelper
{
	int question = 1;
	#define SQL_RESULT_LEN 240
	#define SQL_RETURN_CODE_LEN 1000
	//define handles and variables
	SQLHANDLE sqlConnHandle;
	SQLHANDLE sqlStmtHandle;
	SQLHANDLE sqlEnvHandle;
	SQLWCHAR retconstring[SQL_RETURN_CODE_LEN];
public:
	void init();
	void execute();
	void command(char ch);
	void renameCharac(int ID, string name, string price, string detail);
	Bread* getBreads();
	void close();
	boolean executedata();

};

