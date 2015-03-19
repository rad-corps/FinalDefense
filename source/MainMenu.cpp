//////////////////////////////////////////////////////////////////////////
// GeoWarp
// By Adam Hulbert
// MainMenu.cpp
// For AIE Advanced Diploma - Game Development Using CPP
/////////////////////////////////////////////////////////////////////////

#include "MainMenu.h"
#include "FrameworkHelpers.h"

using namespace std;

MainMenu::MainMenu(void)
{
#ifdef USE_FILE_HIGH_SCORES
	highScoreFile.Open("HighScores.csv");
	
	//apologies, magic numbers: 3 (score column, the parameter hasnt been implemented in SortData either
	highScoreFile.SortData(3);
#endif

	tableLoaded = false;
	//only do this once
	GetHighScores();
	
	//Load the Main Menu Coordinates
	ReloadData();

	//Menu Selection Initialisation
	menuSelections.push_back(START_GAME);
	menuSelections.push_back(CONTROL_SCHEME);
	menuSelections.push_back(HIGH_SCORES);
	menuSelections.push_back(CREDITS);
	menuSelections.push_back(QUIT);
	menuSelection = menuSelections.begin();

	//Menu Display Names
	menuDisplayName[START_GAME] = "START GAME";
	menuDisplayName[CONTROL_SCHEME] = "CONTROL SCHEME";
	menuDisplayName[HIGH_SCORES] = "HIGH SCORES";
	menuDisplayName[QUIT] = "QUIT";
	menuDisplayName[CREDITS] = "CREDITS";
	
	//Control Scheme Initialisation
	myControlScheme = KEYBOARD_AND_MOUSE_CONTROL;
	
	//Menu Text Colour Initialisation
	activeMenuItemColour = SColour(10,255,86,255);
	inactiveMenuItemColour = SColour(155,209,156,255);
	highScoreTextColor = SColour(255,255,255,255);
	
	//counter variable so we cant select too quickly
	minTimeBetweenSelection = 0.f;	

	//Main Menu Sprite
	mainMenuSprite = CreateSprite( "./images/GeoWrapMenu.png", 1024, 768, false );
	kbmouseSprite = CreateSprite("./images/kbmouse.png", 1024, 768, false );
	retroSprite = CreateSprite("./images/retro.png", 1024, 768, false );
	creditsSprite = CreateSprite("./images/credits.png", 1024, 768, false );
	startScreen = CreateSprite("./images/title.png", 1024, 768, false );

	//Initialise Menu Sounds
	// soundChangeSelection = BASS_StreamCreateFile(false,SOUND_CHANGE_SELECTION,0,0,0);
	// soundConfirmSelection = BASS_StreamCreateFile(false,SOUND_CONFIRM_SELECTION,0,0,0);
	// soundMenuMusic = BASS_StreamCreateFile(false,SOUND_WAVE_AMBIENCE,0,0,0);

	// BASS_ChannelSetAttribute(soundChangeSelection, BASS_ATTRIB_VOL, 0.25f);
	// BASS_ChannelSetAttribute(soundConfirmSelection, BASS_ATTRIB_VOL, 0.5f);
	// BASS_ChannelSetAttribute(soundMenuMusic, BASS_ATTRIB_VOL, 0.35f);

	// BASS_ChannelPlay(soundMenuMusic, true);
}


MainMenu::~MainMenu(void)
{
//	BASS_ChannelStop(soundMenuMusic);
}

void
MainMenu::ReloadData()
{
	char * error = NULL;
	dmMenu.Select("Highscores.db", "MAIN_MENU", "*", "", "", error);
}



//string MainMenu::DrawControlMethod()
//{
//	string controlStr;
//	if ( myControlScheme == CONTROL_SCHEME_DEFINIITIONS::KEYBOARD_CONTROL )
//		controlStr = "KEYBOARD";
//	if ( myControlScheme == CONTROL_SCHEME_DEFINIITIONS::KEYBOARD_AND_MOUSE_CONTROL )
//		controlStr = "KB AND MOUSE";
//
//	return controlStr;
//}



bool MainMenu::CheckSelection()
{
	bool selectionMade = false;
	//do we change selection? 
	if ((IsKeyDown(SDLK_DOWN) || IsKeyDown(SDLK_UP)) && minTimeBetweenSelection > 0.2f)
	{
//		BASS_ChannelPlay(soundChangeSelection, true);
		minTimeBetweenSelection = 0.f;
		
		if ( IsKeyDown(SDLK_DOWN) )
		{
			++menuSelection;
			if ( menuSelection == menuSelections.end() )
			{
				menuSelection = menuSelections.begin();
			}
		}
		if ( IsKeyDown(SDLK_UP) )
		{
			if ( menuSelection == menuSelections.begin() )
			{
				menuSelection = menuSelections.end() - 1;
			}
			else
			{
				--menuSelection;
			}
		}
		selectionMade = true;
	}
	return selectionMade;
}

void MainMenu::StopMusic()
{
//	BASS_ChannelStop(soundMenuMusic);
}

void MainMenu::CheckControlMethod()
{
	//check if we want to change the control scheme
	if ( *menuSelection == CONTROL_SCHEME )
	{
		if ( (IsKeyDown(SDLK_LEFT) || IsKeyDown(SDLK_RIGHT)) && minTimeBetweenSelection > 0.2f )
		{
//			BASS_ChannelPlay(soundChangeSelection, true);
			minTimeBetweenSelection = 0.f;
			if ( myControlScheme == KEYBOARD_CONTROL ) 
				myControlScheme = KEYBOARD_AND_MOUSE_CONTROL;
			else if ( myControlScheme == KEYBOARD_AND_MOUSE_CONTROL) 
				myControlScheme = KEYBOARD_CONTROL;
		}
	}
}

void MainMenu::GetHighScores()
{
	char* error = NULL;
	dmScores.Select("HighScores.db", "SCORES", "*", "", "SCORE DESC", error, 10);
}

int MainMenu::HighScore()
{
	return dmScores.GetValueInt(0, "SCORE");
}

void MainMenu::DrawScoreHeading(string heading, int& colNum, int offset)
{
	const int HIGH_SCORES_X_STARTING_POINT = dmMenu.GetValueInt(0, "HIGH_SCORES_X_STARTING_POINT");
	const int HIGH_SCORES_X_COLUMN_SPACING = dmMenu.GetValueInt(0, "HIGH_SCORES_X_COLUMN_SPACING");
	const int HIGH_SCORES_Y_STARTING_POINT = dmMenu.GetValueInt(0, "HIGH_SCORES_Y_STARTING_POINT");
	const int HIGH_SCORES_Y_ROW_SPACING = dmMenu.GetValueInt(0, "HIGH_SCORES_Y_ROW_SPACING");
	const float HIGH_SCORES_FONT_SIZE = dmMenu.GetValueFloat(0, "HIGH_SCORES_FONT_SIZE");

	DrawString(heading.c_str(),
			(HIGH_SCORES_X_STARTING_POINT + HIGH_SCORES_X_COLUMN_SPACING * colNum) + offset, 
			HIGH_SCORES_Y_STARTING_POINT,
			HIGH_SCORES_FONT_SIZE, 
			highScoreTextColor);
	++colNum;
}

void MainMenu::DrawScore(string col, int& colNum, int row)
{

	const int HIGH_SCORES_X_STARTING_POINT = dmMenu.GetValueInt(0, "HIGH_SCORES_X_STARTING_POINT");
	const int HIGH_SCORES_X_COLUMN_SPACING = dmMenu.GetValueInt(0, "HIGH_SCORES_X_COLUMN_SPACING");
	const int HIGH_SCORES_Y_STARTING_POINT = dmMenu.GetValueInt(0, "HIGH_SCORES_Y_STARTING_POINT");
	const int HIGH_SCORES_Y_ROW_SPACING = dmMenu.GetValueInt(0, "HIGH_SCORES_Y_ROW_SPACING");
	const float HIGH_SCORES_FONT_SIZE = dmMenu.GetValueFloat(0, "HIGH_SCORES_FONT_SIZE");

#ifdef USE_FILE_HIGH_SCORES
	string value = highScoreFile.GetField(row, col);
#endif

#ifdef USE_DB_HIGH_SCORES
	string value = dmScores.GetValueString(row,  col);
#endif

	DrawString(value.c_str(),
			HIGH_SCORES_X_STARTING_POINT + HIGH_SCORES_X_COLUMN_SPACING * colNum, 
			HIGH_SCORES_Y_STARTING_POINT - (HIGH_SCORES_Y_ROW_SPACING * row + HIGH_SCORES_Y_ROW_SPACING),
			HIGH_SCORES_FONT_SIZE, 
			highScoreTextColor);
	++colNum;
}

void MainMenu::DrawScoreRightAlign(string col, int& colNum, int row, int maxChars, int offsetPixels)
{
	const int HIGH_SCORES_X_STARTING_POINT = dmMenu.GetValueInt(0, "HIGH_SCORES_X_STARTING_POINT");
	const int HIGH_SCORES_X_COLUMN_SPACING = dmMenu.GetValueInt(0, "HIGH_SCORES_X_COLUMN_SPACING");
	const int HIGH_SCORES_Y_STARTING_POINT = dmMenu.GetValueInt(0, "HIGH_SCORES_Y_STARTING_POINT");
	const int HIGH_SCORES_Y_ROW_SPACING = dmMenu.GetValueInt(0, "HIGH_SCORES_Y_ROW_SPACING");
	const float HIGH_SCORES_FONT_SIZE = dmMenu.GetValueFloat(0, "HIGH_SCORES_FONT_SIZE");

#ifdef USE_FILE_HIGH_SCORES
	string value = highScoreFile.GetField(row, col);
#endif

#ifdef USE_DB_HIGH_SCORES
	string value = dmScores.GetValueString(row,  col);
#endif

	DrawRightAlignedString(value.c_str(),
			(HIGH_SCORES_X_STARTING_POINT + HIGH_SCORES_X_COLUMN_SPACING * colNum) + offsetPixels, 
			HIGH_SCORES_Y_STARTING_POINT - (HIGH_SCORES_Y_ROW_SPACING * row + HIGH_SCORES_Y_ROW_SPACING), maxChars, 
			HIGH_SCORES_FONT_SIZE, 
			highScoreTextColor);
	++colNum;
}

void MainMenu::DrawHighScores()
{
	SetFont( NUMBERS_FONT );
	
	int colNum = 0;
	DrawScoreHeading("NAME", colNum);
	//DrawScoreHeading("LEVEL", colNum);
	DrawScoreHeading("WAVE", colNum);
	DrawScoreHeading("COMBO", colNum);
	
	//more room for score
	//colNum++; 
	DrawScoreHeading("SCORE", colNum, 30);

	for ( int i = 0; i < dmScores.Rows(); ++i )
	{		
		colNum = 0;
		DrawScore("NAME", colNum, i);
		//DrawScore("LEVEL", colNum, i);
		DrawScoreRightAlign("WAVE", colNum, i, 3, 55);
		DrawScoreRightAlign("COMBO_COUNTER", colNum, i, 3, 66);
		
		//more room for score
		//colNum++; 
		DrawScoreRightAlign("SCORE", colNum, i, 9, 130);
	}
}

//void MainMenu::DrawControlScheme()
//{
//
//
//}

GAMESTATES
MainMenu::Update()
{
	if ( IsKeyDown( SDLK_m ) )
	{
		ReloadData();
	}
	//We need to wait for the database to fetch data before we can initialise the HUD sprites.
	if ( dmMenu.Rows() > 0 && !tableLoaded )
		tableLoaded = true;	
	if ( !tableLoaded )
		return MAIN_MENU;

	minTimeBetweenSelection += GetDeltaTime();

	bool newSelectionMade = CheckSelection();

	CheckControlMethod();

	if ( *menuSelection == QUIT )
	{
		if ( IsKeyDown(SDLK_RETURN)  && minTimeBetweenSelection > 0.2f )
		{
//			BASS_ChannelPlay(soundChangeSelection, true);
			minTimeBetweenSelection = 0.f;
			//Shutdown();
			return SHUTDOWN;
		}
	}

	
	MoveSprite( mainMenuSprite, (float)0, (float)SCREEN_HEIGHT);			
	DrawSprite(mainMenuSprite );

	if ( *menuSelection == CREDITS )
	{
		MoveSprite(this->creditsSprite, (float)0, (float)SCREEN_HEIGHT);			
		DrawSprite(this->creditsSprite);	
	}

	//text on buttons
	SetFont( INVADERS_FONT );

	//string controlStr = DrawControlMethod();

	int menuItemsX = dmMenu.GetValueInt(0, "MENU_ITEMS_X");
	int menuItemsY = dmMenu.GetValueInt(0, "MENU_ITEMS_Y");
	int menuItemsYSpacing = dmMenu.GetValueInt(0, "MENU_ITEMS_Y_SPACING");
	float menuTextSize = dmMenu.GetValueFloat(0, "MENU_TEXT_SIZE");

	for ( unsigned int i = 0; i < menuSelections.size(); ++i ) 
	{
		DrawMenuItem(menuSelections[i], i, menuItemsX, menuItemsY, menuItemsYSpacing, menuTextSize);
	}

	if ( *menuSelection == HIGH_SCORES )
	{
		DrawHighScores();
	}
	if ( *menuSelection == START_GAME )
	{
		//DrawString("PRESS ENTER TO START GEO", dmMenu.GetValueInt(0, "START_GAME_X"), dmMenu.GetValueInt(0, "START_GAME_Y"));
		MoveSprite( this->startScreen, (float)0, (float)SCREEN_HEIGHT);			
		DrawSprite(this->startScreen);
	}
	else if ( *menuSelection == CONTROL_SCHEME )
	{
		if ( myControlScheme == KEYBOARD_AND_MOUSE_CONTROL )
		{
			//display kb mouse sprite
			MoveSprite( kbmouseSprite, (float)0, (float)SCREEN_HEIGHT);			
			DrawSprite(kbmouseSprite );
		}
		else if ( myControlScheme == KEYBOARD_CONTROL )
		{
			//display keyboard sprite
			MoveSprite( retroSprite, (float)0, (float)SCREEN_HEIGHT);			
			DrawSprite(retroSprite );			
		}
	}

	if ( minTimeBetweenSelection > 0.2f )
	{
		if( IsKeyDown( SDLK_RETURN ) && *menuSelection == START_GAME )
		{
//			BASS_ChannelPlay(soundConfirmSelection, true);
			return GAMEPLAY;
		}
	}
	return MAIN_MENU;
}

void 
MainMenu::DrawMenuItem(MENU_SELECTION item, int row, int menuItemX, int menuItemY, int ySpacing, float fontSize)
{
	int ypos = menuItemY - ( ySpacing * row );
	SColour colour = inactiveMenuItemColour;
	if ( *menuSelection == item ) 
	{		
		colour = activeMenuItemColour;
	}
	DrawString(menuDisplayName[item].c_str(), menuItemX, ypos, fontSize, colour);
}

CONTROL_SCHEME_DEFINIITIONS 
MainMenu::ControlScheme()
{
	return myControlScheme;
}