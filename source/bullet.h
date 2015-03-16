//////////////////////////////////////////////////////////////////////////
//\ Geo-Warp
// By Adam Hulbert
// Bullet.h
// For AIE Advanced Diploma - Game Development Using CPP
/////////////////////////////////////////////////////////////////////////

#pragma once 

#include "AIE.h"
#include "Vector2D.h"

class Bullet
{
public:
	Bullet();
	~Bullet();

	float GetX();
	float GetY();

	void Update(float delta);
	void Draw();
	void InitialiseBullet(float x, float y, Vector2D dir);
	void UninitialiseBullet();
	bool Active();
	bool Missed();

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
	bool missed;
};