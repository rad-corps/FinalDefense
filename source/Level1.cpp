#include "Level1.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include <iostream>

Level1::Level1(float * plyrX, float * plyrY) : LevelBase(plyrX, plyrY)
{
	CreateNextWave();
	this->plyrX = plyrX;
	this->plyrY = plyrY;	
}

Level1::~Level1()
{

}

//Just like the drinking game
//     1         2            3          4           5                6                7 (in order)
//tap, top, tap, bottom, tap, left, tap, right, tap, top bottom, tap, left right, tap, top bottom-left right
//8               9                  10
//left top right, left bottom right, all directions!
WaveInfo
Level1::CreateNextWave()
{
	//currentWaveNum [1, MAX_WAVES] or [1, 10]
	int levelToLoad = currentWaveNum % MAX_WAVES;
	switch (levelToLoad)
	{
	case 1: 
		currentWave = Wave1();
		break;
	case 2: 
		currentWave = Wave2();
		break;
	case 3: 
		currentWave = Wave3();
		break;
	case 4: 
		currentWave = Wave4();
		break;
	case 5: 
		currentWave = Wave5();
		break;
	case 6: 
		currentWave = Wave6();
		break;
	case 7: 
		currentWave = Wave7();
		break;
	case 8: 
		currentWave = Wave8();
		break;
	case 9: 
		currentWave = Wave9();
		break;
	case 10: 
		currentWave = Wave10();
		break;
	default:
		currentWave = Wave10();
		break;
	} 
	return currentWave;
}

WaveInfo
Level1::Wave1()
{
	const int ENEMY1_COUNT = 1;

	currentWave = InitialiseWave();

	//spawn from top
	for ( int i = 0; i < ENEMY1_COUNT; ++i ) 
	{
		CreateEnemy(ENEMY1, TOP, i * spawnInterval);
	}
	
	CreatePowerUp(POWER_UP_FIRE_RATE, TOP, (ENEMY1_COUNT/2) * spawnInterval);
	
	return currentWave;
}

WaveInfo
Level1::Wave2()
{
	const int ENEMY1_COUNT = 20;

	currentWave = InitialiseWave();

	//spawn from top
	for ( int i = 0; i < ENEMY1_COUNT; ++i ) 
	{
		CreateEnemy(ENEMY1, BOTTOM, i * spawnInterval);
	}
	
	CreateEnemy(ENEMY2, LEFT_OR_RIGHT, ENEMY1_COUNT * (spawnInterval / 2) );

	CreatePowerUp(POWER_UP_FIRE_RATE, TOP, (ENEMY1_COUNT/2) * spawnInterval);

	return currentWave;
}

WaveInfo
Level1::Wave3()
{
	const int ENEMY1_COUNT = 30;
	const int ENEMY2_COUNT = 2;

	currentWave = InitialiseWave();

	//Do Enemy1 Spawn
	for ( int i = 0; i < ENEMY1_COUNT; ++i ) 
	{
		CreateEnemy(ENEMY1, LEFT, i * spawnInterval);
	}

	//Do Enemy2 Spawn
	for ( int i = 0; i < ENEMY2_COUNT; ++i ) 
	{
		CreateEnemy(ENEMY2, RANDOM_OFF_SCREEN, i * (spawnInterval * 12.f) );
	}

	CreatePowerUp(POWER_UP_FIRE_RATE, TOP, (ENEMY1_COUNT/2) * spawnInterval);

	return currentWave;
}

WaveInfo
Level1::Wave4()
{
	const int ENEMY1_COUNT = 40;
	const int ENEMY2_COUNT = 4;

	currentWave = InitialiseWave();

	//Do Enemy1 Spawn
	for ( int i = 0; i < ENEMY1_COUNT; ++i ) 
	{
		CreateEnemy(ENEMY1, RIGHT, i * spawnInterval);
	}

	//Do Enemy2 Spawn
	for ( int i = 0; i < ENEMY2_COUNT; ++i ) 
	{
		CreateEnemy(ENEMY2, LEFT, i * (spawnInterval * 6.f) );
	}
	
	CreatePowerUp(POWER_UP_FIRE_RATE, TOP, (ENEMY1_COUNT/2) * spawnInterval);
	return currentWave;
}

WaveInfo
Level1::Wave5()
{
	const int ENEMY1_COUNT = 50;
	const int ENEMY2_COUNT = 8;

	currentWave = InitialiseWave();

	//Do Enemy1 Spawn
	for ( int i = 0; i < ENEMY1_COUNT; ++i ) 
	{
		CreateEnemy(ENEMY1, TOP_OR_BOTTOM, i * spawnInterval);
	}

	//Do Enemy2 Spawn
	for ( int i = 0; i < ENEMY2_COUNT; ++i ) 
	{
		CreateEnemy(ENEMY2, LEFT_OR_RIGHT, i * (spawnInterval * 3.f) );
	}

	CreatePowerUp(POWER_UP_FIRE_RATE, TOP, (ENEMY1_COUNT/2) * spawnInterval);

	return currentWave;
}

WaveInfo
Level1::Wave6()
{
	const int ENEMY1_COUNT = 60;
	const int ENEMY2_COUNT = 10;

	currentWave = InitialiseWave();

	//Do Enemy1 Spawn
	for ( int i = 0; i < ENEMY1_COUNT; ++i ) 
	{
		CreateEnemy(ENEMY1, LEFT_OR_RIGHT, i * spawnInterval);
	}

	//Do Enemy2 Spawn
	for ( int i = 0; i < ENEMY2_COUNT; ++i ) 
	{
		CreateEnemy(ENEMY2, LEFT_OR_RIGHT, i * (ENEMY1_COUNT*0.1f) * spawnInterval );
	}

	CreatePowerUp(POWER_UP_FIRE_RATE, TOP, (ENEMY1_COUNT/2) * spawnInterval);

	return currentWave;
}

WaveInfo
Level1::Wave7()
{
	const int ENEMY1_COUNT = 70;
	const int ENEMY2_COUNT = 16;

	currentWave = InitialiseWave();

	//Do Enemy1 Spawn
	for ( int i = 0; i < ENEMY1_COUNT/2; ++i ) 
	{
		CreateEnemy(ENEMY1, TOP_OR_BOTTOM, i * spawnInterval);
	}
	//Do Enemy1 Spawn
	for ( int i = ENEMY1_COUNT/2; i < ENEMY1_COUNT; ++i ) 
	{
		CreateEnemy(ENEMY1, LEFT_OR_RIGHT, i * spawnInterval);
	}

	//Do Enemy2 Spawn
	for ( int i = 0; i < ENEMY2_COUNT; ++i ) 
	{
		CreateEnemy(ENEMY2, TOP, i * (spawnInterval * 3.f) );
	}
	
	CreatePowerUp(POWER_UP_FIRE_RATE, TOP, (ENEMY1_COUNT/2) * spawnInterval);

	return currentWave;	
}

WaveInfo
Level1::Wave8()
{
	const int ENEMY1_COUNT = 80;
	const int ENEMY2_COUNT = 20;

	currentWave = InitialiseWave();

	//Do Enemy1 Spawn
	for ( int i = 0; i < ENEMY1_COUNT; ++i ) 
	{
		CreateEnemy(ENEMY1, LEFT_OR_RIGHT, i * spawnInterval);
	}

	//Do Enemy2 Spawn
	for ( int i = 0; i < ENEMY2_COUNT; ++i ) 
	{
		CreateEnemy(ENEMY2, TOP_OR_BOTTOM, i * (spawnInterval * 3.f) );
	}

	CreatePowerUp(POWER_UP_FIRE_RATE, TOP, 0);
	
	return currentWave;
	
}

WaveInfo
Level1::Wave9()
{
	const int ENEMY1_COUNT = 90;
	const int ENEMY2_COUNT = 24;

	currentWave = InitialiseWave();

	//Do Enemy1 Spawn
	for ( int i = 0; i < ENEMY1_COUNT; ++i ) 
	{
		CreateEnemy(ENEMY1, RANDOM_OFF_SCREEN, i * spawnInterval);
	}

	//Do Enemy2 Spawn
	for ( int i = 0; i < ENEMY2_COUNT; ++i ) 
	{
		CreateEnemy(ENEMY2, RANDOM_OFF_SCREEN, i * (spawnInterval * 3.f) );
	}

	CreatePowerUp(POWER_UP_FIRE_RATE, TOP, (ENEMY1_COUNT/2) * spawnInterval);

	return currentWave;
}

WaveInfo
Level1::Wave10()
{
	const int ENEMY1_COUNT = 100;
	const int ENEMY2_COUNT = 30;

	currentWave = InitialiseWave();

	//Do Enemy1 Spawn
	for ( int i = 0; i < ENEMY1_COUNT; ++i ) 
	{
		CreateEnemy(ENEMY1, RANDOM_OFF_SCREEN, i * spawnInterval);
	}

	//Do Enemy2 Spawn
	for ( int i = 0; i < ENEMY2_COUNT; ++i ) 
	{
		CreateEnemy(ENEMY2, RANDOM_OFF_SCREEN, i * (spawnInterval * 3.f) );
	}

	CreatePowerUp(POWER_UP_FIRE_RATE, TOP, (ENEMY1_COUNT/2) * spawnInterval);

	return currentWave;
}