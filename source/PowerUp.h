//////////////////////////////////////////////////////////////////////////
// GeoWarp
// By Adam Hulbert
// PowerUp.h
// For AIE Advanced Diploma - Game Development Using CPP
/////////////////////////////////////////////////////////////////////////

#pragma once

#include "CONSTS.H"
#include "Vector.h"
#include "SDL2/SDL.h"


class PowerUp
{
public:
	PowerUp(const float& spawnTime, POWER_UP_TYPES powerUpType, ENEMY_SPAWN_POINTS spawnPoint, Vector2 startPos);
	~PowerUp();

	void Draw();
	void Move(const float& plyrX, const float& plyrY, bool playerAlive);
	
	void Spawn();	
	float SpawnTime();	
	bool HasSpawned();
	void UsedUp(); //we have finished with this powerup
	bool ThrowAway(); //have we finished with the PowerUp?
	bool Active();
	
	//X/Y Getters
	float X();
	float Y();
	
	POWER_UP_TYPES PowerUpType() { return powerUpType; } 

private:
	POWER_UP_TYPES powerUpType;
	ENEMY_SPAWN_POINTS spawnPoint;
	Vector2 pos;
	float angle;

	SDL_Texture* spriteFrame1;
	SDL_Texture* spriteFrame2;
	SDL_Texture* currentSprite;
	bool throwOut;
	bool hasSpawned;
	float spawnTime;
	float timer;

	
};

typedef list<shared_ptr<PowerUp>> PowerUpList;

typedef shared_ptr<PowerUp> PowerUpPtr;