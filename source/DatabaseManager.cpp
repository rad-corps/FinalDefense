//////////////////////////////////////////////////////////////////////////
// GeoWarp
// By Adam Hulbert
// DatabaseManager.cpp
// For AIE Advanced Diploma - Game Development Using CPP
/////////////////////////////////////////////////////////////////////////

#include "DatabaseManager.h"
#include "sqlite3.h"
#include <assert.h>
//#include <iostream>

int DatabaseManager::s_Callback(void* dmInstance, int numArgs, char **data, char **columnName)
{	
	DatabaseManager* dm = reinterpret_cast<DatabaseManager*>(dmInstance);
    return dm->Callback(numArgs, data, columnName);
}

int DatabaseManager::Callback(int numArgs, char **data, char **columnName)
{	
	map<string, string> temp;
	for ( int i = 0; i < numArgs; ++i )
	{
		temp[string(columnName[i])] = data[i];
	}	
	databaseResponse.push_back(temp);
	return 0;
}

string DatabaseManager::GetValueString(unsigned int row, string col) 
{
	if ( databaseResponse.size() > row )
		return databaseResponse[row][col];
	return "";
}
int DatabaseManager::GetValueInt(int row, string col)
{
	string value = GetValueString(row, col);
	if ( value != "" )
		return atoi(value.c_str());
	return 0;
}
float DatabaseManager::GetValueFloat(int row, string col)
{
	string value = GetValueString(row, col);
	if ( value != "" ) 	
		return (float)atof(GetValueString(row, col).c_str());
	return 0.0f;
}

//Constructor/Destructor
DatabaseManager::DatabaseManager()
{
	sqlDataTypes[DB_SQLITE_DATATYPE::SQLITE_TYPE_NULL] = " NULL ";
	sqlDataTypes[DB_SQLITE_DATATYPE::SQLITE_TYPE_INTEGER] = " INTEGER ";
	sqlDataTypes[DB_SQLITE_DATATYPE::SQLITE_TYPE_REAL] = " REAL ";
	sqlDataTypes[DB_SQLITE_DATATYPE::SQLITE_TYPE_TEXT] = " TEXT ";
	sqlDataTypes[DB_SQLITE_DATATYPE::SQLITE_TYPE_BLOB] = " BLOB ";
}
DatabaseManager::~DatabaseManager(){}

	
//DatabaseManager::Insert
//table		- the table to insert to
//colNames  - comma seperated string the column names to insert to
//values	- comma seperated values to insert
//errorMsg	- pointer to errorMsg to fill on error
//returns true if no error
bool DatabaseManager::Insert(string dbFile, string table, string colNames, string values, char* errorMsg)
{
	//reset the score info struct
	//info = EmptyScoreInfo; 
	databaseResponse.clear();

	sqlite3* db = nullptr; //this is the database object
	sqlite3_open(dbFile.c_str(), &db);

	string sql = "INSERT INTO " + table + 
		"(" + colNames + ")"
		" VALUES(" + values + ");";

	sqlite3_exec(db, sql.c_str(), this->s_Callback, this, &errorMsg);

	assert (errorMsg == NULL && "Something went wrong trying to insert a record to database");	
	return true;
}
	
//DatabaseManager::Select
//table		- the table to select from	
//columns	- columns to select
//sqlWhere	- where sql clause
//orderBy	- sort criteria
bool DatabaseManager::Select(string dbFile, string table, string columns, string sqlWhere, string orderBy, char* errorMsg, int limit) //values
{
	//reset the score info struct
	//info = EmptyScoreInfo; 
	databaseResponse.clear();

	sqlite3* db = nullptr; //this is the database object
	sqlite3_open(dbFile.c_str(), &db);

	//create the statement
	string sql = "SELECT " + columns + " FROM " + table;

	if ( sqlWhere.length() > 0 )
	{
		sql += " WHERE " + sqlWhere;
	}
	if ( orderBy.length() > 0 ) 
	{
		sql += " ORDER BY " + orderBy;
	}
	if (limit != 0 )
	{
		sql += " LIMIT " + to_string(limit);
	}

	//run the query
	sqlite3_exec(db, sql.c_str(), this->s_Callback, this, &errorMsg);
	
	if  (errorMsg != NULL )
	{
		return false;
	}
	return true;
}

bool DatabaseManager::Create(string dbFile, string tableName, map<string, DB_SQLITE_DATATYPE> colNames, char* errorMsg)
{
	map<string, DB_SQLITE_DATATYPE>::iterator colIter;
	sqlite3* db = nullptr; //this is the database object
	sqlite3_open(dbFile.c_str(), &db);

	string sql = " CREATE TABLE " + tableName;
	sql += "(";

	for ( map<string, DB_SQLITE_DATATYPE>::iterator i = colNames.begin(); i != colNames.end(); ++i )
	{
		sql += " " + i->first + " ";
		sql += " " + sqlDataTypes[i->second] + ", ";
	}
	//remove the last comma and space for SQL syntax
	sql = sql.substr(0, sql.size()-2);
	sql += ");";

	sqlite3_exec(db, sql.c_str(), this->s_Callback, this, &errorMsg);
	
	if  (errorMsg != NULL )
	{
		return false;
	}
	return true;
}

int DatabaseManager::Rows()
{
	return databaseResponse.size();
}


////Example of use/////
///////////////////////

//char* error = NULL;
//DatabaseManager dm
//dm.Select("HighScores.db", "SCORES", "*", "", "", error);
//while(gamerunning)
//{
//	for (int i = 0; i < dm.Rows(); ++i )
//	{
//		std::cout << "Score: " << dm.GetValueString(i, "SCORE") << std::endl;
//		std::cout << "Name: " << dm.GetValueString(i, "NAME") << std::endl;
//	}
//}