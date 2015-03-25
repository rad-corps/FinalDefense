#include "bullet.h"
#include "CONSTS.H"
#include "FrameworkHelpers.h"

Bullet::Bullet()
{
	isActive = false;
	missed = false;
	
	//TODO Draw from centre

	sprite = CreateSprite( "./images/PNG/Lasers/laserBlue01.png", BULLET_WIDTH, BULLET_HEIGHT);
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
		SDL_Point origin;
		origin.x = 0;
		origin.y = 4;

		MoveSprite(sprite, x, y);
		DrawSprite(sprite, false, 1.0f, &origin);
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
Bullet::InitialiseBullet(float x, float y, Vector2 dir)
{
	this->dir = dir;
	RotateSprite(sprite, dir.InverseY().GetAngle());
	this->x = x;
	this->y = y;

	this->velocityX = dir.x * PLAYER_BULLET_VELOCITY;
	this->velocityY = dir.y * PLAYER_BULLET_VELOCITY;

	isActive = true;
}

void 
Bullet::UninitialiseBullet()
{
	isActive = false;
}

