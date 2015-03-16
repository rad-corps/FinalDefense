#include "AIE.h"
#include "Vector2D.h"
#include <math.h>
#include <cstdlib>
#include "FrameworkHelpers.h"
#include <time.h>


//[0][0] -1 when pointing up && +1 when pointing down
//[0][1] +1 when pointing right && -1 when pointing left
//[1][1] +1 when pointing down && -1 when pointing up 
//[1][0] +1 pointing left && -1 pointing right
//radians expressed from -1pi to pi
void RotateSpriteToAngle(const unsigned int& sprite, float radians)
{
	float x = cos(radians);
	float y = sin(radians);
	float matrix[4][4];
	GetSpriteMatrix(sprite, matrix[0]);
	matrix[0][0] = x;
	matrix[0][1] = y;
	matrix[1][1] = x;
	matrix[1][0] = -y;
	SetSpriteMatrix(sprite, matrix[0]);
}

//returns the normalised x, y vector coordinates
void GetSpriteAngleVector(const unsigned int& sprite, float& x, float& y)
{
	float matrix[4][4];
	GetSpriteMatrix(sprite, matrix[0]);
	x = matrix[0][0];
	y = matrix[0][1];
}

void GetSpriteAngleVector( const unsigned int& sprite, Vector2D& vec )
{
	float x,y;
	GetSpriteAngleVector(sprite, x, y);
	vec.SetX(x);
	vec.SetY(y);
}

float GetRadiansFromVector(Vector2D& vec)
{
	return atan2(vec.GetY(), vec.GetX());
}

void RotateSpriteToVector(const unsigned int& sprite, Vector2D& vec )
{
	float radians = GetRadiansFromVector(vec);
	RotateSpriteToAngle(sprite, radians);
}

//generate a random number from from to to inclusive
int RandomNumber(int from, int to)
{
	int diff = to - from;
	int result = rand() % diff + from;
	return result;
}

float RandomPercentage()
{
	int res = RandomNumber(0, 100);
	float fres = (float)res / 100.f;
	return fres;
}

void DrawRightAlignedString(const char* text, int xPos, int yPos, int numchars, float fSize, SColour colour)
{
	int text_len = strlen(text);
	int rightX = xPos - text_len * (int)(29.f * fSize);

	DrawString(text, rightX, yPos, fSize, colour);
}

std::string FloatToPerc(float x)
{

	int temp = (int)(x * 100);
	return std::to_string(temp) + "%";
}

float Lerp(float min, float max, float norm) //num between 0 and 1
{
	return (max - min) * norm - min;
}