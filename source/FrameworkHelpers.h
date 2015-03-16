#include "Vector.h"
#include <string>

//[0][0] -1 when pointing up && +1 when pointing down
//[0][1] +1 when pointing right && -1 when pointing left
//[1][1] +1 when pointing down && -1 when pointing up 
//[1][0] +1 pointing left && -1 pointing right
//radians expressed from -1pi to pi
//void RotateSpriteToAngle(const unsigned int& sprite, float radians);
//void GetSpriteAngleVector(const unsigned int& sprite, float& x, float& y);
//void GetSpriteAngleVector( const unsigned int& sprite, Vector2& vec );

//takes a normalised 2D vector and returns the radians (between -pi and pi)
//float GetRadiansFromVector(Vector2& vec );
void RotateSpriteToVector(const unsigned int& sprite, Vector2& vec );

int RandomNumber(int from, int to);
float RandomPercentage(); // between 0 and 1

std::string FloatToPerc(float);

float Lerp(float startRange, float endRange, float num); //num between 0 and 1

void DrawRightAlignedString(const char* text, int xPos, int yPos, int numChars, float fSize, SColour colour);