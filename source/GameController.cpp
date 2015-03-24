//////////////////////////////////////////////////////////////////////////
// GeoWarp
// By Adam Hulbert
// GameController.cpp
// For AIE Advanced Diploma - Game Development Using CPP
/////////////////////////////////////////////////////////////////////////

//#pragma comment(lib, "winmm")
 
//#include <windows.h>

#include "GameController.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include <math.h> //pow, sqrt
#include "Level1.h"
#include <string>
#include "bass.h"

using namespace std;

GameController::GameController()
{
	FrameworkInit();
	GameInitialise();
	// soundWaveComplete = BASS_StreamCreateFile(false,SOUND_WAVE_COMPLETE,0,0,0);
	// soundCurrentLevel = BASS_StreamCreateFile(false,SOUND_WAVE_AMBIENCE,0,0,0);
	
	// soundLevels.push_back(BASS_StreamCreateFile(false,"./sound/Level01_trim.mp3",0,0,BASS_SAMPLE_LOOP));
	// soundLevels.push_back(BASS_StreamCreateFile(false,"./sound/Level02_trim.mp3",0,0,BASS_SAMPLE_LOOP));
	// soundLevels.push_back(BASS_StreamCreateFile(false,"./sound/Level03_trim.mp3",0,0,BASS_SAMPLE_LOOP));
	// soundLevels.push_back(BASS_StreamCreateFile(false,"./sound/Level05_trim.mp3",0,0,BASS_SAMPLE_LOOP));
	// soundLevels.push_back(BASS_StreamCreateFile(false,"./sound/Level05_trim.mp3",0,0,BASS_SAMPLE_LOOP));
	// soundLevels.push_back(BASS_StreamCreateFile(false,"./sound/Level07_trim.mp3",0,0,BASS_SAMPLE_LOOP));
	// soundLevels.push_back(BASS_StreamCreateFile(false,"./sound/Level07_trim.mp3",0,0,BASS_SAMPLE_LOOP));
	// soundLevels.push_back(BASS_StreamCreateFile(false,"./sound/Level08_trim.mp3",0,0,BASS_SAMPLE_LOOP));
	// soundLevels.push_back(BASS_StreamCreateFile(false,"./sound/Level09_trim.mp3",0,0,BASS_SAMPLE_LOOP));
	// soundLevels.push_back(BASS_StreamCreateFile(false,"./sound/Level10_trim.mp3",0,0,BASS_SAMPLE_LOOP)); 
	
	//soundCurrentLevel = soundLevels[0];

	soundWaveCompletePlaying = false;
	timerRunning = true; //run timer from startup
	fixedUpdateTimer = 0.0f;
	hudInfo.powerUpPickupY = -100;
	hudInfo.powerUpPickupX = -100;
}

void
GameController::FrameworkInit()
{
	//INITIALISE AIE FRAMEWORK AND WINDOW
	Initialise( SCREEN_WIDTH, SCREEN_HEIGHT, false, "Geowarp" );
	
	//SetBackgroundColour( BG_COLOUR );
	AddFont( INVADERS_FONT );
	AddFont( NUMBERS_FONT );

	//Initialise BASE engine
//	BASS_Init(-1,44100,0,0,0);
}

void
GameController::DestroyGameObjects()
{
	player.reset();
	currentLevel.reset();
	mainMenu.reset();
	EnemyBase::ResetBullets();
}

//Set up:
// - State
// - Player
// - Enemies
// - main menu
void
GameController::GameInitialise()
{
	//Game Objects
	player = make_shared<Player>();
	mainMenu = make_shared<MainMenu>();
	hud = make_shared<Hud>();
	pauseMenu = make_shared<PauseMenu>();

	currentLevel = shared_ptr<Level1>( new Level1(player->XPtr(), player->YPtr() ));
	currentState = MAIN_MENU;
	
	//init class variables
	timeBetweenWaves = 0.f;
	waveEnd = false;
	levelComplete = false;
	fps.SetIncrementInterval(0.25f);
	timeSincePlayerDeath = 0.f;
}


void GameController::GameLoop()
{
	bool quit = false;
	do 
	{
		ClearScreen();

		switch (currentState )
		{
		case RESET_TO_MENU:
			player->TurnOffEngine();
			DestroyGameObjects();
			GameInitialise();
			currentState = MAIN_MENU;
			break;
		case MAIN_MENU:
			currentState = mainMenu->Update();
			
			//should we swap to gameplay state? 
			if ( currentState == GAMEPLAY )	{
				mainMenu->StopMusic();				
				player->SetControlScheme(mainMenu->ControlScheme());
				player->TurnOnEngine();
				
				//TODO start ambience
//				BASS_ChannelPlay(soundCurrentLevel, true);
//				BASS_ChannelSetAttribute(soundCurrentLevel, BASS_ATTRIB_VOL, 0.5f);
			}
			break;
		case GAMEPLAY:
			UpdateGameState();	

			//do we want to escape to main menu? 
			if( IsKeyDown( SDLK_ESCAPE ) ) {
				
//				BASS_ChannelPause(soundCurrentLevel);
				currentState = ShowPauseScreen();
			}	
			break;
		case PAUSED:
			player->TurnOffEngine();			
			UpdateGameState();
			if ( currentState == PAUSED )
				currentState = ShowPauseScreen();
			if ( currentState == GAMEPLAY ){}
//				BASS_ChannelPlay(soundCurrentLevel, false);
			break;
		default:
			break;
		}
		quit = FrameworkUpdate();
	//} while ( FrameworkUpdate() == false );
	//} while ( currentState != SHUTDOWN );
	} while ( !quit );
	
	Shutdown();
}

GAMESTATES GameController::ShowPauseScreen()
{
	//MoveSprite(pauseScreenSprite, 0, SCREEN_HEIGHT);
	//DrawSprite(pauseScreenSprite);

	if ( IsKeyDown(SDLK_q) )
	{
		return MAIN_MENU;
	}
	else if ( IsKeyDown(SDLK_RETURN) )
	{
		return GAMEPLAY;
	}
	else
	{
		return PAUSED;
	}
}

void GameController::UpdateHudInfo()
{
	hudInfo.alive = player->Alive();
	hudInfo.currentCombo = player->Combo();
	hudInfo.fps = fps.get();
	hudInfo.levelComplete = levelComplete;
	hudInfo.lives = player->Lives();
	hudInfo.score = player->Points();
	hudInfo.highScore = mainMenu->HighScore();
	hudInfo.waveEnd = this->waveEnd;
	hudInfo.waveNum = currentLevel->GetCurrentWaveNum();
	hudInfo.plyrX = player->X();
	hudInfo.plyrY = player->Y();
	hudInfo.timeSincePlayerDeath = timeSincePlayerDeath;
	hudInfo.accuracy = player->Accuracy();
	hudInfo.fireRate = player->FireRate();
}

void GameController::FixedUpdate()
{
	//Player and Bullets
}

void 
GameController::UpdateGameState()
{
	if ( currentState == PAUSED )
	{
		currentState = pauseMenu->Update();
		pauseMenu->Draw();
		if ( currentState == GAMEPLAY )
			player->TurnOnEngine();
	}

	//HACK: TODO FIX
	if ( currentLevel.get() == nullptr )
	{
		//TODO Commented out for testing.
		currentLevel->CreateNextWave();
	}

	if ( IsKeyDown( SDLK_h ) )
	{
		hud->ReloadData();
	}
	if ( IsKeyDown( SDLK_p ) )
	{
		player->ReloadData();
	}

	


	//update the FPS object
	fps.Update();
	
	//if player is dead check if we should respawn
	if ( !player->Alive() && player->Lives() >= 0 ) 
	{
		timeSincePlayerDeath += GetDeltaTime();
		if ( timeSincePlayerDeath > TIME_BETWEEN_PLAYER_RESPAWN )
		{
			player->Respawn();
			timeSincePlayerDeath = 0.0f;
		}
	}

	//this will get us the current wave (enemies and power ups). 
	waveInfo = currentLevel->GetCurrentEnemyList();

	//check for collisions
	DoCollisionChecks();


	//do we call fixed update?
	float delta = GetDeltaTime();
	
	//only update the timer if timer is running.
	if ( timerRunning )
		fixedUpdateTimer += delta;
	else
		timerRunning = true;

	while ( fixedUpdateTimer > UPDATE_INTERVAL )
	{
		//current level controls the enemies, background, power ups
		if ( currentState == GAMEPLAY )
			//todo comment waveEnd back in
			currentLevel->Update(player->Alive());
			//waveEnd = currentLevel->Update(player->Alive());

		//If we are at the end of a wave
		if ( waveEnd  )
		{
			if  (soundWaveCompletePlaying == false)
			{
//				BASS_ChannelStop(soundCurrentLevel);
				
//				soundCurrentLevel = soundLevels[hudInfo.waveNum % MAX_WAVES];

//				BASS_ChannelPlay(soundWaveComplete, true);
				soundWaveCompletePlaying = true;
			}

			//timeBetweenWaves += GetDeltaTime();
			timeBetweenWaves += UPDATE_INTERVAL;
			if ( timeBetweenWaves > TIME_BETWEEN_WAVES )
			{
				timerRunning = false;
				hud->DisplayLoading();
				hud->Update(hudInfo);
				waveInfo = currentLevel->GetNextEnemyList();
				hud->FinishedLoading();
				//enemies = currentLevel->GetNextEnemyList();
				//powerUps = currentLevel->GetNextPowerUpList();
				player->ResetAccuracyStats();
//				BASS_ChannelPlay(soundCurrentLevel, true);

				if ( waveInfo.enemies.get() == nullptr )
				{
					levelComplete = true;
				}
				timeBetweenWaves = 0.0f;
				waveEnd = false;
				soundWaveCompletePlaying = false;
			}
		}

		if ( currentState == GAMEPLAY )
			player->UpdatePlayer();
		fixedUpdateTimer -= UPDATE_INTERVAL;
	}

	currentLevel->Draw();
	if ( currentState == GAMEPLAY )
		player->UpdateBullets();
	player->Draw();
	

	//HUD
	UpdateHudInfo();
	hud->Update(hudInfo);
}

//GameController::DoCollisionChecks()
//iterate over enemy list
// - if is alive
//    - if player bounds collide with enemy bounds
//       - kill player
//    - iterate over playerbullet list (loop in loop)
//        - if is active
//           - if player bullet connects with enemy
//              - damage enemy
void
GameController::DoCollisionChecks()
{
	//initialise this each frame as it may not get set. 
	hudInfo.powerUpPickupX = -100;
	hudInfo.powerUpPickupY = -100;

	if ( waveInfo.enemies.get() != nullptr )
	{
		//check power ups against player
		//check enemy against player projectiles
		//check enemy against player overlap (kill player)
		for ( PowerUpList::iterator powerup = waveInfo.powerUpList->begin(); powerup != waveInfo.powerUpList->end(); ++powerup ) 
		{
			if ( (*powerup)->Active() )
			{			
				float powerupX = (*powerup)->X();
				float powerupY = (*powerup)->Y();
			
				float d = sqrt(pow(powerupX - player->X(), 2) + pow(powerupY - player->Y(), 2));
				//give power up to player
				if ( d < POWER_UP_WIDTH && player->Alive() )
				{					
					player->AddPowerUp((*powerup)->PowerUpType());
					hudInfo.powerUpPickupX = (*powerup)->X();
					hudInfo.powerUpPickupY = (*powerup)->Y();
					(*powerup)->UsedUp();					
				}
			}
		}


		//check enemy against player projectiles
		//check enemy against player overlap (kill player)
		for ( EnemyList::iterator enemy = waveInfo.enemies->begin(); enemy != waveInfo.enemies->end(); ++enemy ) 
		{
			if ( (*enemy)->Alive() )
			{			
				float enemyX = (*enemy)->X();
				float enemyY = (*enemy)->Y();
			
				float d = sqrt(pow(enemyX - player->X(), 2) + pow(enemyY - player->Y(), 2));
				
				//kill player
				if ( d < PLAYER_WIDTH && player->Alive() )
				{
					player->Die();
					timeSincePlayerDeath = 0.0f;
					(*enemy)->Hit(100); 
				}

				//kill enemy if shot
				for (int i = 0; i < MAX_BULLETS; ++i )
				{
					
					Bullet *bullet = &(player->bullets[i]);//get a reference to the bullet
					if ( bullet->Active() )
					{							
						float d = sqrt(pow(enemyX - bullet->GetX(), 2) + pow(enemyY - bullet->GetY(), 2));
						if ( d < ENEMYSINE_WIDTH )
						{
							int points = (*enemy)->Hit(10);
							bullet->UninitialiseBullet();
							player->AddPoints(points);
							player->IncrementHitCounter();
						}
					}
				}//for (int i = 0; i < MAX_BULLETS; ++i ) 				
			}//if Enemy is alive
		}//for ( EnemyList::iterator i = enemies->begin(); i != enemies->end(); ++i ) 

		//kill player if shot
		if ( player->Alive() )
		{
			for (int i = 0; i < MAX_BULLETS; ++i )
			{
				EnemyBulletPtr bullet = (EnemyBase::bullets[i]);//get a reference to the bullet
				if ( bullet->Active() )
				{					
					float d = sqrt(pow(player->X() - bullet->GetX(), 2) + pow(player->Y() - bullet->GetY(), 2));
					if ( d < PLAYER_WIDTH )
					{
						player->Die();
						timeSincePlayerDeath = 0.0f;
						bullet->UninitialiseBullet();
					}
				}
			}//for (int i = 0; i < MAX_BULLETS; ++i )
		}
	}//if enemies != NULL
}

