//////////////////////////////////////////////////////////////////////////
// GeoWarp
// By Adam Hulbert
// Vector2D.cpp
// For AIE Advanced Diploma - Game Development Using CPP
/////////////////////////////////////////////////////////////////////////

#include "Vector2D.h"
#include <math.h>

Vector2D::Vector2D()
{
	this->x = 0.f;
	this->y = 0.f;
}

Vector2D::Vector2D(float x, float y)
{
	this->x = x;
	this->y = y;
}
Vector2D::~Vector2D(){}

//setters and getters
void Vector2D::SetX(float x)
{
	this->x = x;
}

void Vector2D::SetX(int x)
{
	this->x = (float)x;
}

float Vector2D::GetX()
{
	return this->x;
}

void Vector2D::SetY(float y)
{
	this->y = y;
}

void Vector2D::SetY(int y)
{
	this->y = (float)y;
}

float Vector2D::GetY()
{
	return this->y;
}

float* Vector2D::XPtr()
{
	return &x;
}
float* Vector2D::YPtr()
{
	return &y;
}
void Vector2D::SetLength(float length)
{
	float angle = this->GetAngle();
	this->x = cos(angle) * length;
	this->y = sin(angle) * length;
}
const float Vector2D::GetLength()
{
	return sqrt(this->x * this->x + this->y * this->y);
}

//Radians (between -pi and pi)
void Vector2D::SetAngle(float angle)
{
	float length = this->GetLength();
	this->x = cos(angle) * length;
	this->y = sin(angle) * length;
}

float Vector2D::GetAngle()
{
	return atan2(this->y, this->x);
}

	
//overloaded operators
Vector2D& Vector2D::operator+=(const Vector2D& vec)
{
	this->x += vec.x;
	this->y += vec.y;
	return *this;
}
Vector2D& Vector2D::operator-=(const Vector2D& vec)
{
	this->x -= vec.x;
	this->y -= vec.y;
	return *this;
}
Vector2D& Vector2D::operator*=(const Vector2D& vec)
{
	this->x *= vec.x;
	this->y *= vec.y;
	return *this;
}

Vector2D& Vector2D::operator*=(float& vec)
{
	this->x *= vec;
	this->y *= vec;
	return *this;
}
Vector2D& Vector2D::operator*=(const float& vec)
{
	this->x *= vec;
	this->y *= vec;
	return *this;
}
Vector2D& Vector2D::operator/=(const Vector2D& vec)
{
	this->x /= vec.x;
	this->y /= vec.y;
	return *this;
}
bool Vector2D::operator!=(const Vector2D& vec)
{
	if ( this->x == vec.x )
		if (this->y == vec.y )
			return false;
	return true;
}

bool Vector2D::operator==(const Vector2D& vec)
{
	if ( this->x == vec.x )
		if (this->y == vec.y )
			return true;
	return false;
}

void Vector2D::operator=(Vector2D vec)
{
	this->x = vec.x;
	this->y = vec.y;
}

//ahh cool, i will do that
Vector2D Vector2D::operator-(Vector2D vec)
{
	Vector2D temp;
	temp.x = this->x - vec.x;
	temp.y = this->y - vec.y;
	return temp;
}

void Vector2D::Normalise()
{
	//so these need to be values between or -1 and 1? 
	float mag = GetLength();
	x /= mag;
	y /= mag;

	
}

Vector2D Vector2D::operator*(float vec)
{
	Vector2D temp;
	temp.x = this->x * vec;
	temp.y = this->y * vec;
	return temp;
}

Vector2D Vector2D::operator*(Vector2D vec)
{
	vec.x = this->x * vec.x;
	vec.y = this->y * vec.y;
	return vec;
}

bool Vector2D::operator>(float vec)
{
	return GetLength() > vec;
}

Vector2D Vector2D::Rotate90(bool clockwise)
{
	Vector2D ret;
	if ( clockwise )
		ret = Vector2D( this->y, -this->x );
	else
		ret = Vector2D( -this->y, this->x );
	return ret;
}

std::ostream& operator<<(std::ostream& os, Vector2D obj)
{
	os << "X: " << obj.GetX() << ", Y: " << obj.GetY(); 
	return os;
}

Vector2D Vector2D::Lerp(Vector2D origin, Vector2D velocity, float scalar)	//scalar between 0 - 1
{
	velocity = velocity * scalar;
	origin += velocity;
	return origin;
}