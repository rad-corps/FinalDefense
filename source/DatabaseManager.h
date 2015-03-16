//////////////////////////////////////////////////////////////////////////
// GeoWarp
// By Adam Hulbert
// DatabaseManager.h
// For AIE Advanced Diploma - Game Development Using CPP
/////////////////////////////////////////////////////////////////////////

#pragma once

#include <string>
#include <vector>
#include <map>

using namespace std;

enum DB_SQLITE_DATATYPE
{
	SQLITE_TYPE_NULL,
	SQLITE_TYPE_INTEGER,
	SQLITE_TYPE_REAL,
	SQLITE_TYPE_TEXT,
	SQLITE_TYPE_BLOB
};

class DatabaseManager
{
public:
	//Constructor/Destructor
	DatabaseManager();
	~DatabaseManager();
	
	//DatabaseManager::Insert
	//table		- the table to insert to
	//colNames  - comma seperated string the column names to insert to
	//values	- comma seperated values to insert
	//errorMsg	- pointer to errorMsg to fill on error
	//returns true if no error
	bool Insert(string dbFile, string table, string colNames, string values, char* errorMsg); 
	
	//DatabaseManager::Select
	//table		- the table to select from	
	//columns	- columns to select
	//sqlWhere	- where sql clause
	//orderBy	- sort criteria
	bool Select(string dbFile, string tableName, string columns, string sqlWhere, string orderBy, char* errorMsg, int limit = 0); //values

	//Create a database table with the colNames and datatypes
	bool Create(string dbFile, string tableName, map<string, DB_SQLITE_DATATYPE> colNames, char* errorMsg);


	//returns the value at row row for col
	string GetValueString(unsigned int row, string col); 
	int GetValueInt(int row, string col);
	float GetValueFloat(int row, string col);

	//Number of rows in the database response
	int Rows(); 

private:
	static int s_Callback(void* dmInstance, int numArgs, char **data, char **columnName);
	int Callback(int numArgs, char **data, char **columnName);
	bool locked;

	vector<map<string, string>> databaseResponse;	//colname, value
	map<DB_SQLITE_DATATYPE, string> sqlDataTypes;
};

