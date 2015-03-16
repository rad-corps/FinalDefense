//////////////////////////////////////////////////////////////////////////
// 
// By Adam Hulbert
// Vector2.h
// For AIE Advanced Diploma - Game Math And OpenGL
/////////////////////////////////////////////////////////////////////////

#pragma once

#include <ostream>
#include <string>

using namespace std;

//struct Vector4
//{
//	Vector4()
//	{
//
//	}
//
//	Vector4(float x_, float y_, float z_, float w_)
//	{
//		x = x_;
//		y = y_;
//		z = z_;
//		w = w_;
//	}
//
//	float x, y, z, w;
//
//
//	string ToString()
//	{
//		string ret = "";
//		ret += "x: " + to_string(x) + "\ty: " + to_string(y) + "\tz: " + to_string(z) + "\tw: " + to_string(w);
//		return ret;
//	}
//};
//
//struct Vector3
//{
//	Vector3();
//	Vector3(float x_, float y_, float z_);
//
//	float GetAngle();
//	void SetAngle(float angle);
//
//	void Normalise();
//
//	Vector3 operator*(float scalar_);
//	void operator+=(Vector3 vec_);
//	Vector3 operator-(Vector3 vec_);
//	float magnitude();
//	
//	const float GetMagnitude();
//	std::string ToString();
//
//	float x, y, z;
//};

class Vector2
{
public: 
	//constructor/destructor
	Vector2();
	Vector2(float x, float y);
	~Vector2();

	

	//Angle Helpers
	void SetAngle(float angle);
	float GetAngle();
	
	//Magnitude
	void SetMagnitude(float length);
	const float GetMagnitude();

	//Get Perp Vector
	Vector2 Rotate90(bool clockwise);

	//Normalisation Methods
	void Normalise();
	Vector2 GetNormal();
	
	//overloaded arithmetic operators
	Vector2& operator+=(const Vector2& vec);
	Vector2& operator-=(const Vector2& vec);
	Vector2& operator*=(const Vector2& vec);
	Vector2& operator/=(const Vector2& vec);
	Vector2 operator+(Vector2 vec);
	Vector2 operator-(Vector2 vec);
	Vector2 operator*(Vector2 vec);
	Vector2 operator/(Vector2 vec);

	//scalar multiplication
	Vector2& operator*=(const float& vec);
	Vector2 operator*(float vec);

	//dot product
	float Dot(Vector2 vec_);

	//return the angle between the two vectors (in radians)
	float AngleBetweenVectors(Vector2 vec_);
	
	//overloaded assignment operator
	void operator=(Vector2 vec); 
	
	//comparison
	bool operator > (float vec);
	bool operator!=(const Vector2& vec);
	bool operator==(const Vector2& vec);

	float x;
	float y;

	//TODO delete these
	float* XPtr() { return &x; }
	float* YPtr() { return &y; }
};

std::ostream& operator<<(std::ostream& os, Vector2 obj);

class Vector3
{
public: 
	//constructor/destructor
	Vector3();
	Vector3(float x, float y, float z);
	~Vector3();
	
	//Magnitude
	const float GetMagnitude();

	//Normalisation Methods
	void Normalise();
	Vector3 GetNormal();

	//assume 2D for this function (only works on 2D cartesian plane) and ignore z
	void SetAngle(float angle);
	
	//overloaded arithmetic operators
	Vector3& operator+=(const Vector3& vec);
	Vector3& operator-=(const Vector3& vec);
	Vector3& operator*=(const Vector3& vec);
	Vector3& operator/=(const Vector3& vec);
	Vector3 operator+(Vector3 vec);
	Vector3 operator-(Vector3 vec);
	Vector3 operator*(Vector3 vec);
	Vector3 operator/(Vector3 vec);

	//scalar multiplication
	Vector3& operator*=(const float& vec);
	Vector3 operator*(float vec);

	//dot product
	float Dot(Vector3 vec_);
	Vector3 Cross(Vector3 vec_);

	//return the angle between the two vectors (in radians)
	float AngleBetweenVectors(Vector3 vec_);
	
	//overloaded assignment operator
	void operator=(Vector3 vec); 
	
	//comparison
	bool operator > (float vec);
	bool operator!=(const Vector3& vec);
	bool operator==(const Vector3& vec);

	float x;
	float y;
	float z;
};

class Vector4
{
public: 
	//constructor/destructor
	Vector4();
	Vector4(float x, float y, float z, float w);
	~Vector4();
	
	//Magnitude
	const float GetMagnitude();

	//Normalisation Methods
	void Normalise();
	Vector4 GetNormal();
	
	//overloaded arithmetic operators
	Vector4& operator+=(const Vector4& vec);
	Vector4& operator-=(const Vector4& vec);
	Vector4& operator*=(const Vector4& vec);
	Vector4& operator/=(const Vector4& vec);
	Vector4 operator+(Vector4 vec);
	Vector4 operator-(Vector4 vec);
	Vector4 operator*(Vector4 vec);
	Vector4 operator/(Vector4 vec);

	//scalar multiplication
	Vector4& operator*=(const float& vec);
	Vector4 operator*(float vec);

	//dot product
	float Dot(Vector4 vec_);

	//cross product (assume 3 Dimensional use)
	Vector3 Cross(Vector4 vec_);

	//return the angle between the two vectors (in radians)
	float AngleBetweenVectors(Vector4 vec_);
	
	//overloaded assignment operator
	void operator=(Vector4 vec); 
	
	//comparison
	bool operator > (float vec);
	bool operator!=(const Vector4& vec);
	bool operator==(const Vector4& vec);

	float x;
	float y;
	float z;
	float w;
};