//////////////////////////////////////////////////////////////////////////
// GeoWarp
// By Adam Hulbert
// Enemy1.h
// For AIE Advanced Diploma - Game Development Using CPP
/////////////////////////////////////////////////////////////////////////

#include "Enemy2.h"
#include "CONSTS.H"
#include <math.h>
#include <iostream>
#include "FrameworkHelpers.h"

//Enemy1::Enemy1(Player* player, const float& spawnAt) : EnemyBase(player,spawnAt,10)
Enemy2::Enemy2(float* plyrX, float* plyrY,const float& spawnTime, const Vector2D& pos) : EnemyBase(spawnTime,10, pos, plyrX, plyrY)
{
	sprite = CreateSprite("./images/PNG/Enemies/enemyRed2.png", ENEMYSINE_WIDTH, ENEMYSINE_HEIGHT, true);
	frameCount = 0;
	timeSinceFireCheck = 0.0f;
}

//todo implement
Enemy2::~Enemy2()
{

}

void 
Enemy2::Move(const float& plyrX, const float& plyrY, bool playerAlive)
{
	if ( spawned )	{
		if ( !playerAlive )
			MoveAway(velocity);
		else { 
			GravitateToPlayer(plyrX, plyrY, playerAlive);
			if ( health > 0 ) 
				RandomiseShoot();
		}

		MoveSprite(sprite, X(), Y());	
		RotateSpriteToAngle(sprite, AngleToPlayer(plyrX, plyrY));
	}
}

void
Enemy2::RandomiseShoot()
{
	//should we fire? only check 10 times per second
	timeSinceFireCheck += UPDATE_INTERVAL;
	if ( timeSinceFireCheck > ENEMY2_SHOOT_POLL_INTERVAL )
	{

		timeSinceFireCheck = 0.0f;
		if (RandomPercentage() <= ENEMY2_SHOOT_CHANCE)
			Shoot();
	}
}

void
Enemy2::GravitateToPlayer(const float& plyrX, const float& plyrY, bool playerAlive)
{
	Vector2D direction = Vector2D(plyrX, plyrY) - pos;
	direction.Normalise();

	if (!playerAlive)
	{
		direction.SetX(-direction.GetX());
		direction.SetY(-direction.GetY());
	}

	float dist = DistanceToPlayer(plyrX, plyrY);
	velocity += direction * (dist * dist * ENEMY2_FORCE_MULTIPLIER);
	float magnitude = velocity.GetLength();
	if ( magnitude > maxSpeed ) 
		velocity.SetLength(maxSpeed);
	//Vector2D scaledVelocity = velocity * GetDeltaTime();
	pos += velocity;
}