#include "EnemyBullet.h"
#include "CONSTS.H"
#include "FrameworkHelpers.h"

EnemyBullet::EnemyBullet()
{
	x = 0.f;
	y = 0.f;
	isActive = false;
	sprite = CreateSprite( "./images/PNG/Lasers/laserRed01.png", BULLET_WIDTH, BULLET_HEIGHT, true );
}

EnemyBullet::~EnemyBullet()
{}

float EnemyBullet::GetX()
{
	return x;
}

float EnemyBullet::GetY()
{
	return y;
}

bool
EnemyBullet::Active()
{
	return isActive;
}

void
EnemyBullet::Draw()
{
	if (isActive)
	{
		MoveSprite(sprite, x, y);
		DrawSprite(sprite);
	}
}

//void EnemyBullet::Update(float delta)
void EnemyBullet::Update()
{
	if (isActive)
	{
		//x += velocityX * delta;
		//y += velocityY * delta;
		x += velocityX;
		y += velocityY;
		if ( y > SCREEN_HEIGHT + 100.f || y < -100.f || x < -100.f || x > SCREEN_WIDTH + 100.f)
		{
			isActive = false;
		}
	}
}

void 
EnemyBullet::InitialiseBullet(float x, float y, Vector2 dir)
{
	this->dir = dir;
	RotateSprite(sprite, dir.GetAngle());
	this->x = x;
	this->y = y;

	this->velocityX = dir.x * ENEMY_BULLET_VELOCITY;
	this->velocityY = dir.y * ENEMY_BULLET_VELOCITY;

	isActive = true;
}

void 
EnemyBullet::UninitialiseBullet()
{
	isActive = false;
}

