//////////////////////////////////////////////////////////////////////////
// GeoWarp
// By Adam Hulbert
// Vector2D.h
// For AIE Advanced Diploma - Game Development Using CPP
/////////////////////////////////////////////////////////////////////////

#pragma once

#include <ostream>

class Vector2D
{
public:
	//constructor/destructor
	Vector2D();
	Vector2D(float x, float y);
	~Vector2D();

	//setters and getters
	void SetX(float x);
	void SetY(float y);
	void SetX(int x);
	void SetY(int y);
	float GetX();
	float GetY();
	float* XPtr();
	float* YPtr();	
	void SetAngle(float angle);
	float GetAngle();
	void SetLength(float length);
	const float GetLength();
	static Vector2D Lerp(Vector2D origin, Vector2D velocity, float scalar);	//scalar between 0 - 1

	Vector2D Rotate90(bool clockwise);

	void Normalise();
	
	//overloaded operators
	Vector2D& operator+=(const Vector2D& vec);
	Vector2D& operator-=(const Vector2D& vec);
	Vector2D& operator*=(const Vector2D& vec);
	Vector2D& operator*=(float& vec);
	Vector2D& operator/=(const Vector2D& vec);
	void operator=(Vector2D vec); //ok
	Vector2D operator-(Vector2D vec);
	Vector2D& operator*=(const float& vec);
	Vector2D operator*(float vec);
	Vector2D operator*(Vector2D vec);
	


	bool operator > (float vec);

	bool operator!=(const Vector2D& vec);
	bool operator==(const Vector2D& vec);

private:
	float x;
	float y;
};

std::ostream& operator<<(std::ostream& os, Vector2D obj);