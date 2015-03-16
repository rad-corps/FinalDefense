//////////////////////////////////////////////////////////////////////////
// GeoWarp
// By Adam Hulbert
// LevelBase.cpp
// For AIE Advanced Diploma - Game Development Using CPP
/////////////////////////////////////////////////////////////////////////

#include "LevelBase.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "FrameworkHelpers.h"
#include <iostream>

int LevelBase::test = 0;

LevelBase::LevelBase(float* plyrX, float* plyrY)
{
	Start();
	this->plyrX = plyrX;
	this->plyrY = plyrY;
	
//	currentWave = waves.begin();
//	currentPowerUpList = powerUps.begin();
	timer = 0.f;
	allEnemiesHaveBeenPwned = false;
	difficultyScalar = 1.0f;
	firstWave = true;
	spawnInterval = STARTING_ENEMY_SPAWN_SPEED;
	currentWaveNum = 1;

	//background 2D array
	for ( int i = 0; i < BG_TILE_ROWS; ++i ) {
		for (int j = 0; j < BG_TILE_COLS; ++j ) {
			
			//gameBgSprite[j][i] = CreateSprite( "./images/bg/BackdropBlackLittleSparkBlack.png", BG_TILE_WIDTH, BG_TILE_HEIGHT, false );
			gameBgSprite[j][i] = CreateSprite( "./images/bg/starsonly.png", BG_TILE_WIDTH, BG_TILE_HEIGHT, false );
			gameBg2Sprite[j][i] = CreateSprite( "./images/bg/starsonly2.png", BG_TILE_WIDTH, BG_TILE_HEIGHT, false );

			//gameBgSprite[j][i] = CreateSprite( "./images/bg/Parallax100.png", BG_TILE_WIDTH, BG_TILE_HEIGHT, false );
			//gameBg2Sprite[j][i] = CreateSprite( "./images/bg/Parallax80.png", BG_TILE_WIDTH, BG_TILE_HEIGHT, false );
		}
	}
	bgYoffset = BG_TILE_HEIGHT;

	++LevelBase::test;

	//soundWaveAmbience = BASS_StreamCreateFile(false,SOUND_WAVE_AMBIENCE,0,0,BASS_SAMPLE_LOOP);

}

LevelBase::~LevelBase()
{

}

WaveInfo
LevelBase::InitialiseWave()
{
	WaveInfo ret;
	//create a new enemy list (wave)
	ret.enemies = make_shared<EnemyList>();
	ret.powerUpList = make_shared<PowerUpList>();
	//push up the difficulty for this wave
	IncrementDifficulty();
	return ret;
}

//returns true if list.count() == 0 after clean i.e. next wave
bool LevelBase::CleanCurrentEnemyList()
{
	return false;
}

void LevelBase::UpdateEnemies(bool playerAlive)
{
	bool tempSwitch = false;
	for ( EnemyList::iterator enemy = currentWave.enemies->begin(); enemy != currentWave.enemies->end(); ++enemy )
	{
		//if this enemy is either alive or hasnt spawned yet.
		if ( !(*enemy)->ThrowAway() )
		{
			tempSwitch = true;
		}
		(*enemy)->Move(*plyrX, *plyrY, playerAlive); 		
	}
	
	//have all enemies been pwned yet?
	if ( tempSwitch == false )
	{
		allEnemiesHaveBeenPwned = true;
	}
}

void LevelBase::UpdatePowerUps(bool playerAlive)
{	
	for ( PowerUpList::iterator powerUp = currentWave.powerUpList->begin(); powerUp != currentWave.powerUpList->end(); ++powerUp )
	{
		//if this power up is either alive or hasnt spawned yet.
		if ( !(*powerUp)->ThrowAway() )
		{
			(*powerUp)->Move(*plyrX, *plyrY, playerAlive); 			
		}
	}
}

void LevelBase::UpdateEnemyBullets()
{
	//static call to EnemyBase::UpdateBullets
	EnemyBase::UpdateBullets();
}

void LevelBase::UpdateBackground()
{
	//move the 3 backgrounds
	bgYoffset -= (BG_Y_OFFSET_SPEED );
	bgY2offset -= (BG_Y_OFFSET2_SPEED );
	bgY3offset -= (BG_Y_OFFSET3_SPEED );
	
	//reset if < 0
	if ( bgYoffset < 0 )
		bgYoffset = BG_TILE_HEIGHT;
	if ( bgY2offset < 0 )
		bgY2offset = BG_TILE_HEIGHT;
	if ( bgY3offset < 0 )
		bgY3offset = BG_TILE_HEIGHT;
}

void LevelBase::Draw()
{
	
		//draw background tiles
	for ( int i = 0; i < BG_TILE_ROWS; ++i ) {
		for ( int j = 0; j < BG_TILE_COLS; ++j ) { 			
			
			//calculate the new background position
			int startX = (j * BG_TILE_WIDTH);
			int startY = (i * BG_TILE_HEIGHT) + (int)bgYoffset;
			int startY2 = (i * BG_TILE_HEIGHT) + (int)bgY2offset;
			int startY3 = (i * BG_TILE_HEIGHT) + (int)bgY3offset;

			//move all of the backgrounds
			MoveSprite(gameBgSprite[j][i], (float)startX, (float)startY);
			MoveSprite(gameBg2Sprite[j][i], (float)startX, (float)startY2);
			
			//draw the backgrounds
			DrawSprite(gameBgSprite[j][i]);
			
			//commented these out as framework couldn't seem to deal with them. 
			DrawSprite(gameBg2Sprite[j][i]);
		}
	}

	for ( EnemyList::iterator enemy = currentWave.enemies->begin(); enemy != currentWave.enemies->end(); ++enemy )
	{
		(*enemy)->Draw(*plyrX, *plyrY);
	}

	for ( PowerUpList::iterator powerUp = currentWave.powerUpList->begin(); powerUp != currentWave.powerUpList->end(); ++powerUp )
	{
		(*powerUp)->Draw();
	}
}

bool LevelBase::Update(bool playerAlive)
{
	timer += UPDATE_INTERVAL;

	UpdateBackground();
	
	//if (GetCurrentEnemyList() != NULL && started )
	if ( started )
	{			
		
		SpawnEnemies();
		SpawnPowerUps();
		UpdateEnemies(playerAlive);
		UpdateEnemyBullets();	
		UpdatePowerUps(playerAlive);
	}
	return allEnemiesHaveBeenPwned;
}

//check game timer
//
void LevelBase::SpawnEnemies()
{
	for ( EnemyList::iterator enemy = currentWave.enemies->begin(); enemy !=  currentWave.enemies->end(); ++enemy)
	{
		//spawn the enemy if they havent already spawned and it is now time to spawn
		if (!(*enemy)->HasSpawned() && timer >= (*enemy)->SpawnTime() ) 
		{
			(*enemy)->Spawn();
		}
	}
}

void LevelBase::SpawnPowerUps()
{
	for ( PowerUpList::iterator powerUp = currentWave.powerUpList->begin(); powerUp !=  currentWave.powerUpList->end(); ++powerUp)
	{
		//spawn the power up if they havent already spawned and it is now time to spawn
		if (!(*powerUp)->HasSpawned() && timer >= (*powerUp)->SpawnTime() ) 
		{
			(*powerUp)->Spawn();
		}
	}
}

WaveInfo
LevelBase::GetCurrentEnemyList()
{
	//if ( currentWave == waves.end() ) { 
	//	started = false;
	//	return NULL;		
	//}
	return currentWave;
}

WaveInfo
LevelBase::GetNextEnemyList()	
{
	++currentWaveNum;
	allEnemiesHaveBeenPwned = false;
	timer = 0.f;

	//clear current enemy list
	currentWave.enemies.reset();
	currentWave.powerUpList.reset();

	//Call CreateNextWave in the derived class
	this->CreateNextWave();

	//++currentWave;
	return GetCurrentEnemyList();
}


Vector2D LevelBase::CreateSpawnPointTop()
{
	float rand = RandomPercentage();
	Vector2D startingPos;
	startingPos.SetX(rand * SCREEN_WIDTH);
	startingPos.SetY(SCREEN_HEIGHT + 100);
	return startingPos;
}
Vector2D LevelBase::CreateSpawnPointLeft()
{
	float rand = RandomPercentage();
	Vector2D startingPos;
	startingPos.SetX(-100);
	startingPos.SetY(SCREEN_HEIGHT * rand);
	return startingPos;
}
Vector2D LevelBase::CreateSpawnPointRight()
{
	float rand = RandomPercentage();
	Vector2D startingPos;
	startingPos.SetX(SCREEN_WIDTH + 100);
	startingPos.SetY(SCREEN_HEIGHT * rand);
	return startingPos;
}
Vector2D LevelBase::CreateSpawnPointBottom()
{
	float rand = RandomPercentage();
	Vector2D startingPos;
	startingPos.SetX(rand * SCREEN_WIDTH);
	startingPos.SetY(-100.f);
	return startingPos;
}

//a helper function to create an enemy
void
LevelBase::CreateEnemy(ENEMY_TYPE enemyType, ENEMY_SPAWN_POINTS spawnPoint, float spawnTime) //a helper function to create an enemy
{
	float rand = RandomPercentage();
	float rand2 = RandomPercentage();
	Vector2D startingPos;

	if ( spawnPoint == ENEMY_SPAWN_POINTS::BOTTOM ) 
	{
		startingPos = CreateSpawnPointBottom();
	}
	else if ( spawnPoint == ENEMY_SPAWN_POINTS::TOP )
	{
		startingPos = CreateSpawnPointTop();
	}
	else if ( spawnPoint == ENEMY_SPAWN_POINTS::LEFT )
	{
		startingPos = CreateSpawnPointLeft();
	}
	else if ( spawnPoint == ENEMY_SPAWN_POINTS::RIGHT )
	{
		startingPos = CreateSpawnPointRight();
	}
	else if (spawnPoint == ENEMY_SPAWN_POINTS::LEFT_OR_RIGHT )
	{
		if ( rand < 0.5f )
			startingPos = CreateSpawnPointLeft();
		else
			startingPos = CreateSpawnPointRight();

	}
	else if (spawnPoint == ENEMY_SPAWN_POINTS::TOP_OR_BOTTOM )
	{
		if ( rand < 0.5f )
			startingPos = CreateSpawnPointTop();
		else
			startingPos = CreateSpawnPointBottom();
	}
	else if ( spawnPoint == ENEMY_SPAWN_POINTS::RANDOM_OFF_SCREEN ) 
	{

		//top or bottom
		if ( rand < 0.25f )
			startingPos = CreateSpawnPointTop();
		else if ( rand < 0.5f )
			startingPos = CreateSpawnPointRight();
		else if ( rand < 0.75f ) 
			startingPos = CreateSpawnPointBottom();
		else
			startingPos = CreateSpawnPointLeft();
	}


	//create enemy
	EnemyBasePtr enemy;
	if ( enemyType == ENEMY_TYPE::ENEMY1 )
	{
		enemy = EnemyBasePtr(new Enemy1(plyrX, plyrY, spawnTime, startingPos ));
	}
	if ( enemyType == ENEMY_TYPE::ENEMY2 )
	{
		enemy = EnemyBasePtr(new Enemy2(plyrX, plyrY, spawnTime, startingPos ));
	}
	
	currentWave.enemies->push_back(enemy);
	
}

void LevelBase::CreatePowerUp(POWER_UP_TYPES powerUpType, ENEMY_SPAWN_POINTS spawnPoint, float spawnTime) //a helper function to create a power up
{
	Vector2D startingPos;

	if ( spawnPoint == ENEMY_SPAWN_POINTS::BOTTOM ) 
	{
		startingPos.SetX(SCREEN_WIDTH/2);
		startingPos.SetY(-100.f);
	}
	else if ( spawnPoint == ENEMY_SPAWN_POINTS::TOP )
	{
		startingPos.SetX(SCREEN_WIDTH/2);
		startingPos.SetY(SCREEN_HEIGHT + 100.f);
	}

	//create powerup
	PowerUpPtr powerUp;
	powerUp = PowerUpPtr(new PowerUp(spawnTime, powerUpType, spawnPoint, startingPos));
	currentWave.powerUpList->push_back(powerUp);
}

void LevelBase::IncrementDifficulty()
{
	difficultyScalar += 0.1f;
	spawnInterval *= ENEMY_SPAWN_SPEED_MULTIPLYER;
	EnemyBase::SetMaxSpeedCeiling(ENEMY_MAXSPEED*difficultyScalar);
	EnemyBase::SetMaxSpeedFloor((ENEMY_MAXSPEED*0.6f)*difficultyScalar);
}

int LevelBase::GetCurrentWaveNum()
{
	return currentWaveNum;
}

void LevelBase::Start()
{
//	BASS_ChannelPlay(soundWaveAmbience, true);
	started = true;
}