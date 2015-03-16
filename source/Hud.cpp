//////////////////////////////////////////////////////////////////////////
// GeoWarp
// By Adam Hulbert
// Hud.cpp
// For AIE Advanced Diploma - Game Development Using CPP
/////////////////////////////////////////////////////////////////////////

#include "Hud.h"
#include <string>
#include "FrameworkHelpers.h"
#include "DatabaseManager.h"
#include "AIE.h"
#include <iostream>

Hud::Hud(){	
	tableLoaded = false;	
	name = "";
	timer = 0.0f;
	powerUpTimer = -1.0f; //set to off state (0 is start)
	displayLoading = false;
	ReloadData();
	textColour = SColour(205,24,214,255);
	scoreSubmitted = false;
	powerUpY = -1.f;
	powerUpX = -1.f;

	displayCombo = 0;
	comboTimer = 0.0f;

#ifdef USE_FILE_HIGH_SCORES
	highScoreFile.Open("HighScores.csv");
	highScoreFile.SortData(3);
#endif
}

Hud::~Hud(){}

void
Hud::InitHudSprites()
{
	//create lives sprites
	for ( int i = 0 ; i < MAX_LIVES; ++i )	
		hudLives[i] = CreateSprite("./images/PNG/UI/playerLife1_blue.png", dm.GetValueInt(0, "PLAYER_HUD_WIDTH"), dm.GetValueInt(0, "PLAYER_HUD_HEIGHT"), false );
	
	//create waves sprites
	for ( int i = 0 ; i < MAX_WAVES; ++i )	{
		hudWaves[i] = CreateSprite("./images/PNG/Power-ups/powerupBlue_star.png", dm.GetValueInt(0, "WAVES_HUD_WIDTH"), dm.GetValueInt(0, "WAVES_HUD_HEIGHT"), false );
	}

	tableLoaded = true;
}

void 
Hud::InputHighScoreName()
{
	SetFont(NUMBERS_FONT);
	
	DrawString( "GAME OVER", dm.GetValueInt(0, "GAME_OVER_X"), dm.GetValueInt(0, "GAME_OVER_Y"), dm.GetValueFloat(0, "INITIALS_SIZE"), textColour);	
	DrawString("ENTER INITIALS", dm.GetValueInt(0, "ENTER_INITIALS_X"), dm.GetValueInt(0, "ENTER_INITIALS_Y"), dm.GetValueFloat(0, "INITIALS_SIZE"), textColour);
	DrawString(name.c_str(), dm.GetValueInt(0, "INITIALS_X"), dm.GetValueInt(0, "INITIALS_Y"), dm.GetValueFloat(0, "INITIALS_SIZE"), textColour);
	
	timer += GetDeltaTime();	

	for ( int i = KEY_A; i <= KEY_Z; ++i )
	{
		if ( IsKeyDown(i) && timer > dm.GetValueFloat(0, "CHAR_ENTRY_TIMER"))
		{
			if ( name.size() < 3 ) 
			{
				timer = 0.0f;
				name += (char)i;
			}
		}
	}
	if ( IsKeyDown(KEY_BACKSPACE) && timer > dm.GetValueFloat(0, "CHAR_ENTRY_TIMER"))
	{
		timer = 0.0f;
		if ( name.size() > 0 )
			name.pop_back();
	}
	if ( IsKeyDown(KEY_ENTER) && !scoreSubmitted )
	{
		timer = 0.0f;

		//SUBMIT SCORE AND SELECT TOP 10
#ifdef USE_DB_HIGH_SCORES
		char* errorMsg = NULL; 
		DatabaseManager dm;
		string insertString = "";
		insertString += "'" + name + "',";
		insertString += to_string(info.score) + ",";
		insertString += to_string(info.waveNum) + ",";
		//insertString += to_string(info.levelComplete) + ",";
		insertString += to_string(info.currentCombo);
		dm.Insert("HighScores.db", "SCORES", "NAME, SCORE, WAVE, COMBO_COUNTER", insertString, errorMsg);
		dmScoreQuery.Select("HighScores.db", "SCORES", "*", "", "SCORE DESC", errorMsg, 10);

#endif
#ifdef USE_FILE_HIGH_SCORES		
		highScoreFile.AddHighScore(name, to_string(info.waveNum), to_string(info.currentCombo), to_string(info.score));
		highScoreFile.Open("HighScores.csv");
		highScoreFile.SortData(3);
#endif

		scoreSubmitted = true;
	}
}

void Hud::DrawHighScores()
{
	int magicValx = dm.GetValueInt(0, "TOP_TEN_X");
	int magicValy = dm.GetValueInt(0, "TOP_TEN_Y");
	int spacing = dm.GetValueInt(0, "TOP_TEN_ROW_SPACE");
	float fontSize = dm.GetValueFloat(0, "TOP_TEN_SIZE");
	int colSpacing = dm.GetValueInt(0, "TOP_TEN_COL");
	

#ifdef USE_DB_HIGH_SCORES	
	for( int i = 0; i < dmScoreQuery.Rows(); ++i )
	{	
		string name = dmScoreQuery.GetValueString(i, "NAME");
		string score = dmScoreQuery.GetValueString(i, "SCORE");

		DrawString(name.c_str(), magicValx, magicValy, fontSize, textColour);
		DrawString(score.c_str(), magicValx + colSpacing, magicValy, fontSize, textColour);

		magicValy -= spacing;
	}
#endif 
#ifdef USE_FILE_HIGH_SCORES
	if ( scoreSubmitted )
	{
		int rows = 10;
		
		//set the number of scores to display on screen
		if ( rows > highScoreFile.Rows() )
			rows = highScoreFile.Rows();

		for( int i = 0; i < rows; ++i )
		{
			string name = highScoreFile.GetField(i, "NAME");
			string score = highScoreFile.GetField(i, "SCORE");
		
			DrawString(name.c_str(), magicValx, magicValy, fontSize, textColour);
			DrawString(score.c_str(), magicValx + colSpacing, magicValy, fontSize, textColour);

			magicValy -= spacing;
		}
	}
#endif

}

void Hud::DisplayPowerUpScore()
{
	float textSize = dm.GetValueFloat(0, "POWER_UP_TEXT_SIZE");
	float maxTime = dm.GetValueFloat(0, "POWER_UP_TIME");
	if ( powerUpTimer >= -0.01 )
	{
		if ( powerUpTimer < maxTime )
		{
			if ( info.fireRate < MAX_POWER_UPS ) 
				DrawString("FIRE UP", (int)powerUpX, (int)powerUpY, textSize, textColour);
			else 
				DrawString("MAX FIRE", (int)powerUpX, (int)powerUpY, textSize, textColour);
			powerUpTimer  += GetDeltaTime();
		}
	}

	if ( powerUpTimer >= maxTime ) //finished
	{
		powerUpTimer = -1.0f;
		powerUpX = -1.f;
		powerUpY = -1.f;
	}
}

void
Hud::Update(HudInfo info)
{
	

	//We need to wait for the database to fetch data before we can initialise the HUD sprites.
	if ( dm.Rows() > 0 && !tableLoaded )
		InitHudSprites();

	//textColour = SColour(dm.GetValueInt(0, "TEXT_COLOR" ));
	int colourR = dm.GetValueInt(0, "TEXT_COLOUR_R");
	int colourG = dm.GetValueInt(0, "TEXT_COLOUR_G");
	int colourB = dm.GetValueInt(0, "TEXT_COLOUR_B");
	textColour = SColour(colourR, colourG, colourB, 255);

	this->info = info;

	SetFont( NUMBERS_FONT );

	if ( info.waveEnd )
	{
		//WAVE X COMPLETE
		string waveCompleteStr = "WAVE " + to_string(info.waveNum+1) + " BEGIN";
		DrawString(waveCompleteStr.c_str(), dm.GetValueInt(0, "WAVE_BEGIN_X"), dm.GetValueInt(0, "WAVE_BEGIN_Y"), 0.75f, textColour);
	}

	//show accuracy stats	
	//string strAccuracy = "ACCURACY: " + FloatToPerc(info.accuracy);
	//DrawString(strAccuracy.c_str(), dm.GetValueInt(0, "HUD_LEFT_MARGIN"), dm.GetValueInt(0, "HUD_BOTTOM_ROW") + 2 * (dm.GetValueInt(0, "PLAYER_HUD_HEIGHT") +  (dm.GetValueInt(0, "GENERIC_MARGIN"))));

	//LEVEL COMPLETE
	if ( info.levelComplete )
	{
		DrawString("LEVEL COMPLETE", dm.GetValueInt(0, "LEVEL_COMPLETE_MARGIN"), SCREEN_HEIGHT/2, 0.5f, textColour);
	}

	//COMBO
	if ( info.currentCombo > 1 ) 
	{
		displayCombo = info.currentCombo;
		string combo = to_string(info.currentCombo) + "x COMBO";		
		comboTimer = 0.0f;
	}
	if ( displayCombo > 0 && comboTimer < 0.5f)
	{
		comboTimer += GetDeltaTime();
		int comboScore = displayCombo * 25;
		string comboStr = to_string(displayCombo) + "X COMBO - " + to_string(comboScore);
		DrawString( comboStr.c_str(), (int)info.plyrX + 70, (int)info.plyrY, 0.5f, textColour);	
	}
	if ( comboTimer > 0.5f ) 
	{
		comboTimer = 0.0f;
		displayCombo = 0;
	}


	
	//GET READY SCREEN
	else if ( !info.alive && info.lives > 0 )
	{
		int time = (int)(TIME_BETWEEN_PLAYER_RESPAWN - info.timeSincePlayerDeath);
		string strGetReady = "DONT PANIC - " + to_string(time + 1);
		DrawString( strGetReady.c_str(), dm.GetValueInt(0, "HUD_LEFT_MARGIN"), SCREEN_HEIGHT/2 - 100, 0.5f, textColour);	
	}

	////Display FPS
	//int ifps = info.fps;
	//string sfps = "FPS: " + to_string(ifps);
	//DrawString( sfps.c_str(), SCREEN_WIDTH - dm.GetValueInt(0, "HUD_RIGHT_MARGIN"), SCREEN_HEIGHT-dm.GetValueInt(0, "HUD_TOP_ROW"));	
	
	//display player points
	string pointsDisplay = "SCORE: " + to_string(info.score);
	DrawString(pointsDisplay.c_str(), dm.GetValueInt(0, "HUD_LEFT_MARGIN"), SCREEN_HEIGHT - dm.GetValueInt(0, "HUD_TOP_ROW"), 0.5f, textColour);

	//display high score
	string highScoreDisplay = "HIGH SCORE: " + to_string(info.highScore);
	DrawString(highScoreDisplay.c_str(), dm.GetValueInt(0, "HIGH_SCORE_X"), SCREEN_HEIGHT - dm.GetValueInt(0, "HUD_TOP_ROW"), 0.5f, textColour);

	//display loading next wave
	if ( displayLoading )
	{		
		DrawString("LOADING NEXT WAVE", dm.GetValueInt(0, "LOADING_WAVE_X"), dm.GetValueInt(0, "LOADING_WAVE_Y"), 1.0f, textColour);
	}

	//Display wave number
	string waveStr = "WAVE: " + to_string(info.waveNum);
	DrawString(waveStr.c_str(), dm.GetValueInt(0, "HUD_LEFT_MARGIN"), dm.GetValueInt(0, "HUD_BOTTOM_ROW") + dm.GetValueInt(0, "PLAYER_HUD_HEIGHT") + dm.GetValueInt(0, "GENERIC_MARGIN"), 0.5f, textColour);

	//draw player lives
	for (int i = 0; i < info.lives; ++i )
	{
		MoveSprite(hudLives[i], (i * dm.GetValueFloat(0, "PLAYER_HUD_WIDTH"))+dm.GetValueFloat(0, "HUD_LEFT_MARGIN"), dm.GetValueFloat(0, "HUD_BOTTOM_ROW"));
		DrawSprite(hudLives[i]);
	}

	//Display Fire Rate
	string fireRateStr = "";
	if  ( info.fireRate < MAX_POWER_UPS )
		fireRateStr = "FIRE: " + to_string(info.fireRate);
	else
		fireRateStr = "MAX FIRE";

	DrawString(fireRateStr.c_str(), dm.GetValueInt(0, "FIRE_RATE_X") , dm.GetValueInt(0, "FIRE_RATE_Y"), 0.5f, textColour);

	//Display Current PowerUp Bonus
	if ( info.powerUpPickupX > -1 )
	{		
		//just picked up a power up, reset the display timer
		powerUpTimer = 0.0f;
		powerUpX = info.powerUpPickupX;
		powerUpY = info.powerUpPickupY;
	}

	if ( info.lives < 0 )
	{
		this->InputHighScoreName();
	}

	DrawHighScores();
	DisplayPowerUpScore();
}

void Hud::ReloadData()
{
	char* error = NULL;
	dm.Select("Highscores.db", "HUD", "*", "", "", error);
}

void Hud::DisplayLoading()
{
	displayLoading = true;
}
void Hud::FinishedLoading()
{
	displayLoading = false;
}