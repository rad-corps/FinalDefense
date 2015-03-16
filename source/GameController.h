//////////////////////////////////////////////////////////////////////////
// GeoWarp
// By Adam Hulbert
// GameController.h
// For AIE Advanced Diploma - Game Development Using CPP
/////////////////////////////////////////////////////////////////////////

#pragma once
#include "GLAHGraphics.h"
#include "EnemyBase.h"
#include "Player.h"
#include "CONSTS.h"
#include "LevelBase.h"
#include "Fps.h"
#include <string>
#include "Hud.h"
#include "MainMenu.h"
#include "bass.h"
#include "PauseMenu.h"



class GameController
{
public:
	GameController();
	//~GameController();
	void GameLoop();					//called by main()

private:
	//METHODS
	void FrameworkInit();				//Initialise the AIE framework
	void GameInitialise();				//Intialise all game objects
	void UpdateGameState();				//calls update on all game objects	
	void FixedUpdate();					//called once every UPDATE_INTERVAL
	void DestroyGameObjects();			//destroy all gameObjects (may not be required since using shared_ptr)
	void DoCollisionChecks();			//Do all in game collision checks
	void UpdateHudInfo();				//populate the hudInfo variable
	GAMESTATES ShowPauseScreen();		//return paused if nothing selected
	
	//GAME OBJECTS
	shared_ptr<LevelBase> currentLevel; //level ( a level has many waves )
	shared_ptr<MainMenu> mainMenu;		//mainMenu object
	shared_ptr<Player> player;			//player game object
	WaveInfo waveInfo;
	//shared_ptr<EnemyList> enemies;		//enemies game object ( the current wave )
	//shared_ptr<PowerUpList> powerUps;		//powerups game object ( the current wave )
	shared_ptr<Hud> hud;				//HUD object
	GAMESTATES currentState;			//MAINMENU or GAMEPLAY	
	HudInfo hudInfo;					//HUD object requires a hudInfo on update
	Fps fps;							//FPS game object
	HSTREAM soundWaveComplete;			//Wave complete sound
	bool soundWaveCompletePlaying;		
	HSTREAM soundCurrentLevel;				//play this underneath a wave
	vector<HSTREAM> soundLevels;

	//Pause Menu
	shared_ptr<PauseMenu> pauseMenu;

	//TIMERS AND LOGIC VARIABLES
	float timeBetweenWaves;				//time elapsed since wave complete
	float timeSincePlayerDeath;			//time elapsed since player died
	bool waveEnd;						//has the wave just ended? (havent started a new one yet)
	bool levelComplete;					//has the player complete the level? (all waves)
	float fixedUpdateTimer;
	bool timerRunning;					//True if we do not want to add delta time for this frame (used for loading game waves)
	//bool paused;						
	unsigned int pauseScreenSprite;		//the image overlayed when user pauses game
};

