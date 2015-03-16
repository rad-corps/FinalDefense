#include "bullet.h"
#include "CONSTS.H"
#include "FrameworkHelpers.h"

Bullet::Bullet()
{
	isActive = false;
	missed = false;
	sprite = CreateSprite( "./images/PNG/Lasers/laserBlue01.png", BULLET_WIDTH, BULLET_HEIGHT, true );
}

Bullet::~Bullet()
{}

float Bullet::GetX()
{
	return x;
}

float Bullet::GetY()
{
	return y;
}

bool
Bullet::Active()
{
	return isActive;
}

void
Bullet::Draw()
{
	if (isActive)
	{
		MoveSprite(sprite, x, y);
		DrawSprite(sprite);
	}
}

void Bullet::Update(float delta)
{
	if (isActive)
	{
		x += velocityX * delta;
		y += velocityY * delta;
		if ( y > SCREEN_HEIGHT || y < 0.f || x < 0.f || x > SCREEN_WIDTH )
		{
			isActive = false;
			missed = true;
		}
	}
}

bool 
Bullet::Missed()
{
	bool ret = missed;
	missed = false; //reset so we only ever get true once. 
	return ret; 
}

void 
Bullet::InitialiseBullet(float x, float y, Vector2D dir)
{
	this->dir = dir;
	RotateSpriteToVector(sprite, dir);
	this->x = x;
	this->y = y;

	this->velocityX = dir.GetX() * PLAYER_BULLET_VELOCITY;
	this->velocityY = dir.GetY() * PLAYER_BULLET_VELOCITY;

	isActive = true;
}

void 
Bullet::UninitialiseBullet()
{
	isActive = false;
}

