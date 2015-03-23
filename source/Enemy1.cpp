//////////////////////////////////////////////////////////////////////////
// GeoWarp
// By Adam Hulbert
// Enemy1.h
// For AIE Advanced Diploma - Game Development Using CPP
/////////////////////////////////////////////////////////////////////////

#include "Enemy1.h"
#include "CONSTS.H"
#include <math.h>
#include <iostream>
#include "FrameworkHelpers.h"

//Enemy1::Enemy1(Player* player, const float& spawnAt) : EnemyBase(player,spawnAt,10)
Enemy1::Enemy1(float* plyrX, float* plyrY, const float& spawnTime, const Vector2& pos) : EnemyBase(spawnTime,10, pos, plyrX, plyrY)
{
	sprite = CreateSprite("./images/PNG/Enemies/enemyBlack1.png", ENEMYSINE_WIDTH, ENEMYSINE_HEIGHT);
	frameCount = 0;
}

//todo implement
Enemy1::~Enemy1()
{

}

void 
Enemy1::Move(const float& plyrX, const float& plyrY, bool playerAlive)
{
	//if ( health > 0 && spawned )
	if ( spawned )
	{
		if ( !playerAlive )
			MoveAway(velocity);
		else 
			GravitateToPlayer(plyrX, plyrY, playerAlive);	
	}
}

void
Enemy1::GravitateToPlayer(const float& plyrX, const float& plyrY, bool playerAlive)
{
	Vector2 direction = Vector2(plyrX, plyrY) - pos;
	direction.Normalise();

	if (!playerAlive)
	{
		direction.x=(-direction.x);
		direction.y=(-direction.y);
	}

	velocity += direction * (DistanceToPlayer(plyrX, plyrY) * ENEMY1_FORCE_MULTIPLIER);
	if ( velocity.GetMagnitude() > maxSpeed ) 	
		velocity.SetMagnitude(maxSpeed);
	//Vector2 scaledVelocity = velocity * GetDeltaTime();
	pos += velocity;
}

