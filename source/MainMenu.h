//////////////////////////////////////////////////////////////////////////
// GeoWarp
// By Adam Hulbert
// MainMenu.h
// For AIE Advanced Diploma - Game Development Using CPP
/////////////////////////////////////////////////////////////////////////

#pragma once

#include "CONSTS.H"
//#include "bass.h"
#include <vector>
#include "DatabaseManager.h"
#include "HighScoreFile.h"
#include "SDL2/SDL.h"


class MainMenu
{
public:
	MainMenu();
	~MainMenu();

	GAMESTATES Update();
	CONTROL_SCHEME_DEFINIITIONS ControlScheme();

	void ReloadData();

	int HighScore();

	void StopMusic();

private:
	void DrawMenuItem(MENU_SELECTION item, int row, int menuItemX, int menuItemY, int ySpacing, float fontSize);
	void CheckControlMethod();
	//string DrawControlMethod();						//return the string to write in the menu
	bool CheckSelection();							//true if a new selection was made
	void GetHighScores();
	void DrawHighScores();
	//void DrawControlScheme();
	void DrawScoreHeading(string col, int& colNum, int offset = 0);
	void DrawScore(string col, int& colNum, int row);
	void DrawScoreRightAlign(string col, int& colNum, int row, int maxChars, int offsetPixels);

	DatabaseManager dmScores;
	DatabaseManager dmMenu;

	vector<MENU_SELECTION> menuSelections;
	vector<MENU_SELECTION>::iterator menuSelection;
	map<MENU_SELECTION,string> menuDisplayName;
	SColour highScoreTextColor;
	SColour activeMenuItemColour;
	SColour inactiveMenuItemColour;
	float minTimeBetweenSelection;
	CONTROL_SCHEME_DEFINIITIONS myControlScheme;
	SDL_Texture* mainMenuSprite;
	SDL_Texture* kbmouseSprite;
	SDL_Texture* retroSprite;	
	SDL_Texture* creditsSprite;
	SDL_Texture* startScreen;

//	HSTREAM soundChangeSelection;
//	HSTREAM soundConfirmSelection;
//	HSTREAM soundMenuMusic;

	bool tableLoaded;

	HighScoreFile highScoreFile;
};

