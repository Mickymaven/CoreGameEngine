#include <math.h>
#include <string>
#include <Windows.h>

#include "LMVector3.h"

LMVector3::LMVector3()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

LMVector3::LMVector3(float fx, float fy, float fz)
{
	x = fx;
	y = fy;
	z = fz;
}

LMVector3::LMVector3(LMVector3 & v)
{
	x = v.x;
	y = v.y;
	z = v.z;

}

LMVector3::~LMVector3()
{

}

void LMVector3::operator += (const LMVector3 & v)
{
	x += v.x;
	y += v.y;
	z += v.z;
}

void LMVector3::operator -= (const LMVector3& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
}

void LMVector3::operator *= (const LMVector3& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
}

void LMVector3::operator /= (const LMVector3& v)
{
	x /= v.x;
	y /= v.y;
	z /= v.z;
}

LMVector3 LMVector3::operator + (const LMVector3 &v)
{
	return LMVector3(x + v.x, y + v.y, z + v.z);
}

LMVector3 LMVector3::operator * (const float f)
{
	return LMVector3(x*f, y*f, z*f);
}

void LMVector3::operator = (const float& f)
{
	x = f;
	y = f;
	z = f;
}

void LMVector3::operator += (const float& f)
{
	x += f;
	y += f;
	z + f;
}

void LMVector3::operator -= (const float& f)
{
	x -= f;
	y -= f;
	z -= f;
}

void LMVector3::operator *= (const float& f)
{
	x *= f;
	y *= f;
	z *= f;
}

void LMVector3::operator /= (const float& f)
{
	if (f != 0.0f)
	{
		x /= f;
		y /= f;
		z /= f;
	}
	else x = y = z = 0.0f;
}

bool LMVector3::operator == (const LMVector3 & v)
{
	return v.x == x && v.y == y && v.z == z;
}

bool LMVector3::operator != (const LMVector3 & v)
{
	return v.x != x || v.y != y || v.z != z;
}

void LMVector3::operator = (const LMVector3 &v)
{
	x = v.x;
	y = v.y;
	z = v.z;
}

float & LMVector3::operator [] (int i)
{
	switch (i)
	{
	case 0: return x;
	case 1: return y;
	case 2: return z;
	}
}

float LMVector3::LengthSq()
{
	return x*x + y*y + z*z;
}

float LMVector3::Magnitude()
{
	return abs(sqrt(x*x + y*y + z*z));
}

float LMVector3::DisplacementMag(const LMVector3 & v)
{
	float resultX = x - v.x;
	float resultY = y - v.y;
	float resultZ = z - v.z;
	float result = sqrt(abs(resultX*resultX + resultY*resultY + resultZ*resultZ));

	return result;
}

void LMVector3::Normalize()
{
	float length = sqrt(x*x + y*y + z*z);

	if (length != 0.0f)
	{
		x /= length;
		y /= length;
		z /= length;
	}
	else
	{
		x = y = z = 0.0f;
	}
}

bool LMVector3::IsInRegion(LMVector3 * start, LMVector3 * end)
{

	if (end->x > start->x)
	{
		if (!(x > start->x)) return false;
		if (!(x < end->x)) return false;
	}
	else
	{
		if (!(x < start->x)) return false;
		if (!(x > end->x)) return false;
	}

	if (end->z > start->z)
	{
		if (!(z > start->z)) return false;
		if (!(z < end->z)) return false;
	}
	else
	{
		if (!(z < start->z)) return false;
		if (!(z > end->z)) return false;
	}

	return true;
}

bool LMVector3::IsRangeFurther(const LMVector3 & v, float range)
{
	float lx = abs(x - v.x);
	float ly = abs(y - v.y);
	float lz = abs(z - v.z);

	if (range*range > (lx*lx + ly*ly + lz*lz)) return true;

	return false;
}

