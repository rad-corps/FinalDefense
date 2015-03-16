#pragma once

#include "SDL2/SDL.h"
#include "../source/Vector.h"

struct GLAHEntity
{
	//SDL_Texture* spriteID;
	//Matrix3x3 translation;
	Vector3 position;
	unsigned int parentSpriteID; //if null, no parent. 
	Vector2 size; //x=width,y=height
	Vector3 origin;
	float rotation;
	float scaleX;
	float scaleY;
	float UV[4];
	//float circleColliderRadius; //0 if no collider

	GLAHEntity() : rotation(0.0f), scaleX(1.0f), scaleY(1.0f) /*,circleColliderRadius(0.0f)*/ 
	{
		UV[0] = 0;
		UV[1] = 0;
		UV[2] = 1;
		UV[3] = 1;
	}
};