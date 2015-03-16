#pragma once

/////////////////////////////////////////////////////////////////////////
// GeoWarp
// By Adam Hulbert
// Hud.h
// For AIE Advanced Diploma - Game Development Using CPP
/////////////////////////////////////////////////////////////////////////

#include "CONSTS.H"
#include "DatabaseManager.h"
#include "HighScoreFile.h"

class Hud
{
public:
	Hud();
	~Hud();
	void Update(HudInfo info);

	void ReloadData();
	void DisplayLoading();
	void FinishedLoading();

private:
	void DisplayPowerUpScore();
	bool scoreSubmitted;
	bool displayLoading;

	void InputHighScoreName();
	void InitHudSprites();

	void DrawHighScores();

	bool tableLoaded;

	SDL_Texture* hudLives[MAX_LIVES]; //5 is max num of lives
	SDL_Texture* hudWaves[MAX_WAVES];
	HudInfo info;
	string name;
	float timer;
	float powerUpTimer;
	float powerUpX;
	float powerUpY;

	DatabaseManager dm;
	DatabaseManager dmScoreQuery;

	int displayCombo;
	float comboTimer;

	SColour textColour;

	HighScoreFile highScoreFile;
};