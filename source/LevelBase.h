#pragma once

//////////////////////////////////////////////////////////////////////////
// GeoWarp
// By Adam Hulbert
// LevelBase.h
// For AIE Advanced Diploma - Game Development Using CPP
/////////////////////////////////////////////////////////////////////////

#include "EnemyBase.h"
#include <list>
#include "bass.h"
#include "PowerUp.h"

typedef list<shared_ptr<EnemyList>> EnemyWaves;
typedef list<shared_ptr<PowerUpList>> PowerUps;

struct WaveInfo
{
	shared_ptr<EnemyList> enemies;
	shared_ptr<PowerUpList> powerUpList;
};

class LevelBase
{
public:
	//Constructor / Destructor
	LevelBase(float* plyrX, float* plyrY);
	~LevelBase();
	
	//EnemyList Methods
	WaveInfo GetCurrentEnemyList();	//clean current list, 0 or NULL if all waves complete
	WaveInfo GetNextEnemyList();		//get the next enemy list (this one becomes current) 0 or NULL if there are no more
	//shared_ptr<PowerUpList> GetCurrentPowerUpList();//clean current list, 0 or NULL if all waves complete
	//shared_ptr<PowerUpList> GetNextPowerUpList();	//get the next power up list (this one becomes current) 0 or NULL if there are no more
	int GetCurrentWaveNum();	

	//PowerUpList Methods
	//shared_ptr<PowerUpList> GetCurrentPowerUpList();	
	//shared_ptr<PowerUpList> GetNextPowerUpList();		
	
	bool Update(bool playerAlive);						//return allEnemiesHaveBeenPwned	
	void Draw();
	void Start();

	virtual WaveInfo CreateNextWave() = 0;
protected:
	//EnemyWaves waves;
	//EnemyWaves::iterator currentWave;
	WaveInfo currentWave;
	//PowerUps powerUps;
	//PowerUps::iterator currentPowerUpList;


	WaveInfo InitialiseWave();
	void CreateEnemy(ENEMY_TYPE enemyType, ENEMY_SPAWN_POINTS spawnPoint, float spawnTime); //a helper function to create an enemy
	void CreatePowerUp(POWER_UP_TYPES powerUpType, ENEMY_SPAWN_POINTS spawnPoint, float spawnTime); //a helper function to create a power up
	float spawnInterval;
	int currentWaveNum;
private:
	Vector2D CreateSpawnPointTop();
	Vector2D CreateSpawnPointLeft();
	Vector2D CreateSpawnPointRight();
	Vector2D CreateSpawnPointBottom();

	//background sprites
	unsigned int gameBgSprite[3][3];
	unsigned int gameBg2Sprite[3][3];
	float bgYoffset;
	float bgY2offset;
	float bgY3offset;
	
	//
	void IncrementDifficulty();
	void UpdateBackground();
	void UpdateEnemies(bool playerAlive);
	void UpdatePowerUps(bool playerAlive);
	void UpdateEnemyBullets();

	void SpawnEnemies();
	void SpawnPowerUps();
	bool CleanCurrentEnemyList();		//returns true if list.count() == 0 after clean i.e. next wave
	float timer;
	float* plyrX;
	float* plyrY;
	bool firstWave;
	float difficultyScalar;

	//this switch set to true if there are no alive enemies left and all have spawned
	bool allEnemiesHaveBeenPwned;
	bool started;
	static int test;
	//HSTREAM soundWaveAmbience;
	
};