//////////////////////////////////////////////////////////////////////////
//\ Geo-Warp
// By Adam Hulbert
// EnemyBullet.h
// For AIE Advanced Diploma - Game Development Using CPP
/////////////////////////////////////////////////////////////////////////

#pragma once 

#include "AIE.h"
#include "Vector2D.h"
#include "CONSTS.H"

class EnemyBullet
{
public:
	EnemyBullet();
	~EnemyBullet();

	float GetX();
	float GetY();

	void Update();
	void Draw();
	void InitialiseBullet(float x, float y, Vector2D dir);
	void UninitialiseBullet();
	bool Active();


private:
	float x;
	float y;
	float width;
	float height; 

	unsigned int sprite;

	float velocityX;
	float velocityY;
	Vector2D dir;
	bool isActive;
};

typedef shared_ptr<EnemyBullet> EnemyBulletPtr;