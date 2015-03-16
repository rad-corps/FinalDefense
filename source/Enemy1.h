//////////////////////////////////////////////////////////////////////////
// GeoWarp
// By Adam Hulbert
// Enemy1.h
// For AIE Advanced Diploma - Game Development Using CPP
/////////////////////////////////////////////////////////////////////////

#pragma once

#include "Vector.h"
#include <list>
#include "EnemyBase.h"

//#include "Player.h"



class Enemy1 : public EnemyBase
{
public:
	//Enemy1(Player* player, const float& spawnAt);
	Enemy1(float* plyrX, float* plyrY,const float& spawnTime, const Vector2& pos);
	~Enemy1();
	void Move(const float& plyrX, const float& plyrY, bool playerAlive);

private:
	void GravitateToPlayer(const float& plyrX, const float& plyrY, bool playerAlive);
	
	unsigned int frameCount;
	Vector2 velocity;
};

