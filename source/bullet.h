//////////////////////////////////////////////////////////////////////////
//\ Geo-Warp
// By Adam Hulbert
// Bullet.h
// For AIE Advanced Diploma - Game Development Using CPP
/////////////////////////////////////////////////////////////////////////

#pragma once 

#include "GLAHGraphics.h"
#include "Vector.h"
#include "SDL2/SDL.h"

class Bullet
{
public:
	Bullet();
	~Bullet();

	float GetX();
	float GetY();

	void Update(float delta);
	void Draw();
	void InitialiseBullet(float x, float y, Vector2 dir);
	void UninitialiseBullet();
	bool Active();
	bool Missed();

private:
	float x;
	float y;
	float width;
	float height; 

	SDL_Texture* sprite;

	float velocityX;
	float velocityY;
	Vector2 dir;
	bool isActive;
	bool missed;
};