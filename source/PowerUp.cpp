#include "PowerUp.h"
#include <string>
#include "GLAHGraphics.h"
#include <cmath>
#include <iostream>

PowerUp::PowerUp(const float& spawnTime, POWER_UP_TYPES powerUpType, ENEMY_SPAWN_POINTS spawnPoint, Vector2 startPos)
{
	this->pos = startPos;
	this->spawnPoint = spawnPoint;
	this->spawnTime = spawnTime;
	this->powerUpType = powerUpType;

	angle = 0.0f;
	timer = 0.0f;	
	throwOut = false;
	hasSpawned = false;
	

	string spritePath1;
	string spritePath2;

	if ( this->powerUpType == POWER_UP_WING_GUNS ) {
		spritePath1 = ANIM_1_POWER_UP_WING_GUNS;
		spritePath2 = ANIM_2_POWER_UP_WING_GUNS;
	}
	else if ( this->powerUpType == POWER_UP_BACK_GUN ) { 
		spritePath1 = ANIM_1_POWER_UP_BACK_GUN;
		spritePath2 = ANIM_2_POWER_UP_BACK_GUN;
	}
	else if ( this->powerUpType == POWER_UP_FIRE_RATE ) { 
		spritePath1 = ANIM_1_POWER_FIRE_RATE;
		spritePath2 = ANIM_2_POWER_FIRE_RATE;
	}
	else if ( this->powerUpType == POWER_UP_SHIELD ) { 
		spritePath1 = ANIM_1_POWER_UP_SHIELD;
		spritePath2 = ANIM_2_POWER_UP_SHIELD;
	}
	else if ( this->powerUpType == POWER_UP_SPEED_UP ) { 
		spritePath1 = ANIM_1_POWER_UP_SPEED;
		spritePath2 = ANIM_2_POWER_UP_SPEED;
	}
	spriteFrame1 = CreateSprite(spritePath1.c_str(), POWER_UP_WIDTH, POWER_UP_HEIGHT, true);
	spriteFrame2 = CreateSprite(spritePath2.c_str(), POWER_UP_WIDTH, POWER_UP_HEIGHT, true);
	currentSprite = spriteFrame1;
}

PowerUp::~PowerUp()
{}

//X/Y Getters
float PowerUp::X()
{
	return pos.x;
}
float PowerUp::Y()
{
	return pos.y;
}

void PowerUp::Draw()
{
	if ( !throwOut )
	{
		timer += GetDeltaTime();
		if ( timer > POWER_UP_ANIMATION_SPEED ) 
		{		
			if ( currentSprite == spriteFrame1 ) 
				currentSprite = spriteFrame2;
			else
				currentSprite = spriteFrame1;
			timer = 0.0f;
		}
		MoveSprite(currentSprite, pos.x, pos.y);
		DrawSprite(currentSprite);
	}
}

void PowerUp::Move(const float& plyrX, const float& plyrY, bool playerAlive)	
{
	//float delta = GetDeltaTime();
	if ( hasSpawned && !throwOut ) 
	{
		//calculate xpos
		angle += POWERUP_SINE_SPEED;
		float xpos = (sin(angle) * POWERUP_SINE_DEPTH) + pos.x;

		//calculate ypos	
		float ypos = pos.y;
		if ( spawnPoint == ENEMY_SPAWN_POINTS::TOP )
			ypos += POWERUP_Y_SPEED;
		if ( spawnPoint == ENEMY_SPAWN_POINTS::BOTTOM )
			ypos -= POWERUP_Y_SPEED;

		//set positions
		pos.x =  xpos ;
		pos.y =  ypos ;
	}
}

bool PowerUp::ThrowAway()
{
	return throwOut;
}

void PowerUp::Spawn()
{
	hasSpawned = true;
}

float PowerUp::SpawnTime()
{
	return spawnTime;
}

bool PowerUp::HasSpawned()
{
	return hasSpawned;
}

void PowerUp::UsedUp()
{
	throwOut = true;
}

bool PowerUp::Active()
{
	if (!HasSpawned()) 
		return false;
	if (ThrowAway())
		return false;
	return true;
}