//////////////////////////////////////////////////////////////////////////
// By Adam Hulbert
// Vector2.cpp
// For AIE Advanced Diploma - Game Math And OpenGL
/////////////////////////////////////////////////////////////////////////

#include "Vector.h"
#include <math.h>
#include <string>

using namespace std;


//VECTOR2//////////////////////////
///////////////////////////////////
//CTORS / DSTOR
Vector2::Vector2()
{
	this->x = 1.f;
	this->y = 0.f;
}

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2::~Vector2(){}

//Magnitude Functions
void Vector2::SetMagnitude(float length)
{
	float angle = this->GetAngle();
	this->x = cos(angle) * length;
	this->y = sin(angle) * length;
}

const float Vector2::GetMagnitude()
{
	return sqrt(this->x * this->x + this->y * this->y);
}

//Angle Functions
void Vector2::SetAngle(float angle)//angle in Radians (between -pi and pi)
{
	float length = this->GetMagnitude();
	this->x = cos(angle) * length;
	this->y = sin(angle) * length;
}

//returns radians (between -pi and pi)
float Vector2::GetAngle()
{
	return atan2(this->y, this->x);
}

//overloaded arithmetic operators
Vector2& Vector2::operator+=(const Vector2& vec)
{
	this->x += vec.x;
	this->y += vec.y;
	return *this;
}
Vector2& Vector2::operator-=(const Vector2& vec)
{
	this->x -= vec.x;
	this->y -= vec.y;
	return *this;
}
Vector2& Vector2::operator*=(const Vector2& vec)
{
	this->x *= vec.x;
	this->y *= vec.y;
	return *this;
}

Vector2& Vector2::operator*=(const float& vec)
{
	this->x *= vec;
	this->y *= vec;
	return *this;
}
Vector2& Vector2::operator/=(const Vector2& vec)
{
	this->x /= vec.x;
	this->y /= vec.y;
	return *this;
}

Vector2 Vector2::operator+(Vector2 vec)
{
	Vector2 temp;
	temp.x = this->x + vec.x;
	temp.y = this->y + vec.y;
	return temp;
}

Vector2 Vector2::operator-(Vector2 vec)
{
	Vector2 temp;
	temp.x = this->x - vec.x;
	temp.y = this->y - vec.y;
	return temp;
}

Vector2 Vector2::operator*(Vector2 vec)
{
	Vector2 temp;
	temp.x = this->x * vec.x;
	temp.y = this->y * vec.y;
	return temp;
}

Vector2 Vector2::operator/(Vector2 vec)
{
	Vector2 temp;
	temp.x = this->x / vec.x;
	temp.y = this->y / vec.y;
	return temp;
}

Vector2 Vector2::operator*(float vec)
{
	Vector2 temp;
	temp.x = this->x * vec;
	temp.y = this->y * vec;
	return temp;
}

//assignment
void Vector2::operator=(Vector2 vec)
{
	this->x = vec.x;
	this->y = vec.y;
}

//normalisation
void Vector2::Normalise()
{
	float mag = this->GetMagnitude();
	x /= mag;
	y /= mag;	
}

Vector2 
Vector2::GetNormal()
{
	Vector2 normal(x, y);
	normal.Normalise();
	return normal;
}

//comparison
bool Vector2::operator!=(const Vector2& vec)
{
	if ( this->x == vec.x )
		if (this->y == vec.y )
			return false;
	return true;
}

bool Vector2::operator==(const Vector2& vec)
{
	if ( this->x == vec.x )
		if (this->y == vec.y )
			return true;
	return false;
}

bool Vector2::operator>(float vec)
{
	return this->GetMagnitude() > vec;
}

//rotation helper
Vector2 Vector2::Rotate90(bool clockwise)
{
	Vector2 ret;
	if ( clockwise )
		ret = Vector2( this->y, -this->x );
	else
		ret = Vector2( -this->y, this->x );
	return ret;
}

//ostream operator
std::ostream& operator<<(std::ostream& os, Vector2 obj)
{
	os << "X: " << obj.x << ", Y: " << obj.y; 
	return os;
}

//dot product
float Vector2::Dot(Vector2 vec_)
{
	return this->x * vec_.x + this->y * vec_.y;
}

//return the angle between 2 vectors expressed as radians (-PI to PI)
float Vector2::AngleBetweenVectors(Vector2 vec_)
{
	Vector2 vec1 = this->GetNormal();
	Vector2 vec1_perp = vec1.Rotate90(true);	
	Vector2 vec2 = vec_.GetNormal();
	if ( vec1_perp.Dot(vec2) >= 0 )
		return acos(vec1.Dot(vec2));
	else
		return -acos(vec1.Dot(vec2));
}

//VECTOR3///////////////////////////////////////
/////////////////////////////////////////////////
//CTORS / DSTOR
Vector3::Vector3()
{
	this->x = 1.f;
	this->y = 0.f;
	this->z = 0.f;
}

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::~Vector3(){}

const float Vector3::GetMagnitude()
{
	return sqrt(x * x + y * y + z * z);
}

//overloaded arithmetic operators
Vector3& Vector3::operator+=(const Vector3& vec)
{
	this->x += vec.x;
	this->y += vec.y;
	this->z += vec.z;
	return *this;
}
Vector3& Vector3::operator-=(const Vector3& vec)
{
	this->x -= vec.x;
	this->y -= vec.y;
	this->z -= vec.z;
	return *this;
}
Vector3& Vector3::operator*=(const Vector3& vec)
{
	this->x *= vec.x;
	this->y *= vec.y;
	this->z *= vec.z;
	return *this;
}

Vector3& Vector3::operator*=(const float& vec)
{
	this->x *= vec;
	this->y *= vec;
	this->z *= vec;
	return *this;
}
Vector3& Vector3::operator/=(const Vector3& vec)
{
	this->x /= vec.x;
	this->y /= vec.y;
	this->z /= vec.z;
	return *this;
}

Vector3 Vector3::operator+(Vector3 vec)
{
	Vector3 temp;
	temp.x = this->x + vec.x;
	temp.y = this->y + vec.y;
	temp.z = this->z + vec.z;
	return temp;
}

Vector3 Vector3::operator-(Vector3 vec)
{
	Vector3 temp;
	temp.x = this->x - vec.x;
	temp.y = this->y - vec.y;
	temp.z = this->z - vec.z;
	return temp;
}

Vector3 Vector3::operator*(Vector3 vec)
{
	Vector3 temp;
	temp.x = this->x * vec.x;
	temp.y = this->y * vec.y;
	temp.z = this->z * vec.z;
	return temp;
}

Vector3 Vector3::operator/(Vector3 vec)
{
	Vector3 temp;
	temp.x = this->x / vec.x;
	temp.y = this->y / vec.y;
	temp.z = this->z / vec.z;
	return temp;
}

Vector3 Vector3::operator*(float vec)
{
	Vector3 temp;
	temp.x = this->x * vec;
	temp.y = this->y * vec;
	temp.z = this->z * vec;
	return temp;
}

//assignment
void Vector3::operator=(Vector3 vec)
{
	this->x = vec.x;
	this->y = vec.y;
	this->z = vec.z;
}

//normalisation
void Vector3::Normalise()
{
	float mag = this->GetMagnitude();
	x /= mag;
	y /= mag;	
	z /= mag;	
}

Vector3 
Vector3::GetNormal()
{
	Vector3 normal(x, y, z);
	normal.Normalise();
	return normal;
}

//comparison
bool Vector3::operator!=(const Vector3& vec)
{
	if ( this->x == vec.x )
		if (this->y == vec.y )
			if (this->z == vec.z )
				return false;
	return true;
}

bool Vector3::operator==(const Vector3& vec)
{
	if ( this->x == vec.x )
		if (this->y == vec.y )
			if (this->y == vec.y )
				return true;
	return false;
}

bool Vector3::operator>(float vec)
{
	return this->GetMagnitude() > vec;
}

//ostream operator
std::ostream& operator<<(std::ostream& os, Vector3 obj)
{
	os << "X: " << obj.x << ", Y: " << obj.y << ", Z: " << obj.z; 
	return os;
}

void Vector3::SetAngle(float angle)//angle in Radians (between -pi and pi)
{
	float length = this->GetMagnitude();
	this->x = cos(angle) * length;
	this->y = sin(angle) * length;
}

//dot product
float Vector3::Dot(Vector3 vec_)
{
	return this->x * vec_.x + this->y * vec_.y + this->z * vec_.z;
}

Vector3 Vector3::Cross(Vector3 vec_)
{
	Vector3 ret;
	ret.x = y * vec_.z - z * vec_.y;
	ret.y = z * vec_.x - x * vec_.z;
	ret.z = x * vec_.y - y * vec_.x;
	return ret;
}

//VECTOR4//////////////////////////
////////////////////////////////////

Vector4::Vector4()
{
	this->x = 1.f;
	this->y = 1.f;
	this->z = 1.f;
	this->w = 1.f;
}

Vector4::Vector4(float x, float y, float z, float w)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Vector4::~Vector4(){}

const float Vector4::GetMagnitude()
{
	return sqrt(x * x + y * y + z * z + w * w);
}

//overloaded arithmetic operators
Vector4& Vector4::operator+=(const Vector4& vec)
{
	this->x += vec.x;
	this->y += vec.y;
	this->z += vec.z;
	this->w += vec.w;
	return *this;
}
Vector4& Vector4::operator-=(const Vector4& vec)
{
	this->x -= vec.x;
	this->y -= vec.y;
	this->z -= vec.z;
	this->w -= vec.w;
	return *this;
}
Vector4& Vector4::operator*=(const Vector4& vec)
{
	this->x *= vec.x;
	this->y *= vec.y;
	this->z *= vec.z;
	this->w *= vec.w;
	return *this;
}

Vector4& Vector4::operator*=(const float& vec)
{
	this->x *= vec;
	this->y *= vec;
	this->z *= vec;
	this->w *= vec;
	return *this;
}
Vector4& Vector4::operator/=(const Vector4& vec)
{
	this->x /= vec.x;
	this->y /= vec.y;
	this->z /= vec.z;
	this->w /= vec.w;
	return *this;
}

Vector4 Vector4::operator+(Vector4 vec)
{
	Vector4 temp;
	temp.x = this->x + vec.x;
	temp.y = this->y + vec.y;
	temp.z = this->z + vec.z;
	temp.z = this->w + vec.w;
	return temp;
}

Vector4 Vector4::operator-(Vector4 vec)
{
	Vector4 temp;
	temp.x = this->x - vec.x;
	temp.y = this->y - vec.y;
	temp.z = this->z - vec.z;
	temp.w = this->w - vec.w;
	return temp;
}

Vector4 Vector4::operator*(Vector4 vec)
{
	Vector4 temp;
	temp.x = this->x * vec.x;
	temp.y = this->y * vec.y;
	temp.z = this->z * vec.z;
	temp.w = this->z * vec.w;
	return temp;
}

Vector4 Vector4::operator/(Vector4 vec)
{
	Vector4 temp;
	temp.x = this->x / vec.x;
	temp.y = this->y / vec.y;
	temp.z = this->z / vec.z;
	temp.w = this->z / vec.w;
	return temp;
}

Vector4 Vector4::operator*(float vec)
{
	Vector4 temp;
	temp.x = this->x * vec;
	temp.y = this->y * vec;
	temp.z = this->z * vec;
	temp.w = this->w * vec;
	return temp;
}

//assignment
void Vector4::operator=(Vector4 vec)
{
	this->x = vec.x;
	this->y = vec.y;
	this->z = vec.z;
	this->w = vec.w;
}

//normalisation
void Vector4::Normalise()
{
	float mag = this->GetMagnitude();
	x /= mag;
	y /= mag;	
	z /= mag;	
	w /= mag;	
}

Vector4 
Vector4::GetNormal()
{
	Vector4 normal(x, y, z, w);
	normal.Normalise();
	return normal;
}

//comparison
bool Vector4::operator!=(const Vector4& vec)
{
	if ( this->x == vec.x )
		if (this->y == vec.y )
			if (this->z == vec.z )
				if (this->w == vec.w )
					return false;
	return true;
}

bool Vector4::operator==(const Vector4& vec)
{
	if ( this->x == vec.x )
		if (this->y == vec.y )
			if (this->y == vec.y )
				if (this->w == vec.w )
					return true;
	return false;
}

bool Vector4::operator>(float vec)
{
	return this->GetMagnitude() > vec;
}

//ostream operator
std::ostream& operator<<(std::ostream& os, Vector4 obj)
{
	os << "X: " << obj.x << ", Y: " << obj.y << ", Z: " << obj.z << ", W: " << obj.w; 
	return os;
}

//dot product
float Vector4::Dot(Vector4 vec_)
{
	return this->x * vec_.x + this->y * vec_.y + this->z * vec_.z + this->w * vec_.w;
}

Vector3 Vector4::Cross(Vector4 vec_)
{
	Vector3 ret;
	ret.x = y * vec_.z - z * vec_.y;
	ret.y = z * vec_.x - x * vec_.z;
	ret.z = x * vec_.y - y * vec_.x;
	return ret;
}