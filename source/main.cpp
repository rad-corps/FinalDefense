//////////////////////////////////////////////////////////////////////////
// GeoWarp
// By Adam Hulbert
// For AIE Advanced Diploma - Game Development Using CPP
//\
/////////////////////////////////////////////////////////////////////////
#include "GameController.h"
#include "DatabaseManager.h"
#include <time.h>
#include <iostream>
#include <string>
#include <iostream>

#include "HighScoreFile.h"


using namespace std;


//The below code demonstrates creating table and column schemas programtically through my DatabaseManager wrapper.
//The database has grown beyond the scope of the below code, but i have left it there for demonstration purposes. 
//----------------------------------------------------------------------------------------------------------------
//
//void createHudTable()
//{
//	DatabaseManager dm;
//	map<string, DB_SQLITE_DATATYPE> colNames;
//
//	colNames["PLAYER_HUD_WIDTH"] = DB_SQLITE_DATATYPE::SQLITE_TYPE_INTEGER;
//	colNames["PLAYER_HUD_HEIGHT"] = DB_SQLITE_DATATYPE::SQLITE_TYPE_INTEGER;
//	colNames["WAVES_HUD_WIDTH"] = DB_SQLITE_DATATYPE::SQLITE_TYPE_INTEGER;
//	colNames["WAVES_HUD_HEIGHT"] = DB_SQLITE_DATATYPE::SQLITE_TYPE_INTEGER;
//	colNames["GENERIC_MARGIN"] = DB_SQLITE_DATATYPE::SQLITE_TYPE_INTEGER;
//	colNames["HUD_LEFT_MARGIN"] = DB_SQLITE_DATATYPE::SQLITE_TYPE_INTEGER;
//	colNames["HUD_WAVE_MARGIN"] = DB_SQLITE_DATATYPE::SQLITE_TYPE_INTEGER;
//	colNames["HUD_WAVE_NUM_MARGIN"] = DB_SQLITE_DATATYPE::SQLITE_TYPE_INTEGER;
//	colNames["HUD_COMPLETE_MARGIN"] = DB_SQLITE_DATATYPE::SQLITE_TYPE_INTEGER;
//	colNames["HUD_MARGINS"] = DB_SQLITE_DATATYPE::SQLITE_TYPE_INTEGER;
//	colNames["HUD_BOTTOM_ROW"] = DB_SQLITE_DATATYPE::SQLITE_TYPE_INTEGER;
//	colNames["HUD_RIGHT_MARGIN"] = DB_SQLITE_DATATYPE::SQLITE_TYPE_INTEGER;
//	colNames["LEVEL_COMPLETE_MARGIN"] = DB_SQLITE_DATATYPE::SQLITE_TYPE_INTEGER;
//	colNames["TEXT_HEIGHT"] = DB_SQLITE_DATATYPE::SQLITE_TYPE_INTEGER;
//	colNames["CHAR_ENTRY_TIMER"] = DB_SQLITE_DATATYPE::SQLITE_TYPE_REAL;
//
//	char* error = NULL;
//	
//	if (!dm.Create("HighScores.db", "HUD", colNames, error) ) 
//	{
//		std::cout << error << endl;
//	}
//}
//
//void CreatePhysicsTable()
//{
//	DatabaseManager dm;
//	map<string, DB_SQLITE_DATATYPE> colNames;
//
//	colNames["THRUST_POWER"] = DB_SQLITE_DATATYPE::SQLITE_TYPE_REAL;
//	colNames["ROTATION_SPEED"] = DB_SQLITE_DATATYPE::SQLITE_TYPE_REAL;
//	colNames["MAX_SPEED"] = DB_SQLITE_DATATYPE::SQLITE_TYPE_REAL;
//	colNames["FRICTION"] = DB_SQLITE_DATATYPE::SQLITE_TYPE_REAL;
//
//	char* error = NULL;
//	
//	if (!dm.Create("HighScores.db", "PLAYER", colNames, error) ) 
//	{
//		std::cout << error << endl;
//	}
//}
//
//void CreateMainMenuTable()
//{
//	DatabaseManager dm;
//	map<string, DB_SQLITE_DATATYPE> colNames;
//
//	colNames["HIGH_SCORES_Y_STARTING_POINT"] = DB_SQLITE_DATATYPE::SQLITE_TYPE_INTEGER;
//	colNames["HIGH_SCORES_X_STARTING_POINT"] = DB_SQLITE_DATATYPE::SQLITE_TYPE_INTEGER;
//	colNames["HIGH_SCORES_X_COLUMN_SPACING"] = DB_SQLITE_DATATYPE::SQLITE_TYPE_INTEGER;
//	colNames["HIGH_SCORES_Y_ROW_SPACING"] = DB_SQLITE_DATATYPE::SQLITE_TYPE_INTEGER;
//	colNames["HIGH_SCORES_FONT_SIZE"] = DB_SQLITE_DATATYPE::SQLITE_TYPE_REAL;
//
//	
//	char* error = NULL;
//	
//	if (!dm.Create("HighScores.db", "MAIN_MENU", colNames, error) ) 
//	{
//		std::cout << error << endl;
//	}
//}

int main( int argc, char* argv[] )
{	
	//createHudTable();
	//CreatePhysicsTable();
	//CreateMainMenuTable();
	//system("pause");

	
	//HighScoreFile Testing Suite
	////////////////////////////
	//HighScoreFile hsf("HighScores.csv");
	//
	////hsf.SortData(3); //3 corresponds to the column position to sort (i.e. score) sample CSV below
	////teg,19,30,397875
	////rad,15,6,100000
	////ads,11,3,12000
	//for ( int row = 0; row < hsf.Rows(); ++row )
	//{
	//	for (int col = 0; col < hsf.Cols(); ++col )
	//	{
	//		cout << hsf.GetField(row,col) << ", ";
	//	}
	//	cout << endl;
	//}

	//hsf.AddHighScore("AGA", "10", "3", "10000");

	//system("pause");
	

	srand((unsigned int)time(NULL));
	GameController gc;
	gc.GameLoop();
	return 0;
}