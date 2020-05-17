#include "LMVector4.h"

LMVector4::LMVector4() { 

	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
	w = 0.0f;
}

LMVector4::LMVector4(float fx, float fy, float fz, float fw)
{
	x = fx;
	y = fy;
	z = fz;
	w = fw;
}

LMVector4::LMVector4(LMVector4 & v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
}

LMVector4::~LMVector4() {  }

void LMVector4::operator+=(const LMVector4 & v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	w += v.w;
}

void LMVector4::operator -= (const LMVector4& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	w -= v.w;
}

void LMVector4::operator *= (const LMVector4& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
	w *= v.w;
}

void LMVector4::operator /= (const LMVector4& v)
{
	x /= v.x;
	y /= v.y;
	z /= v.z;
	w /= v.w;
}

LMVector4 LMVector4::operator + (const LMVector4 &v)
{
	return LMVector4(x + v.x, y + v.y, z + v.z, w + v.w);
}

LMVector4 LMVector4::operator * (const float f)
{
	return LMVector4(x*f, y*f, z*f, w* f);
}

void LMVector4::operator = (const float& f)
{
	x = f;
	y = f;
	z = f;
	w = f;
}

void LMVector4::operator += (const float& f)
{
	x += f;
	y += f;
	z += f;
	w += f;
}

void LMVector4::operator -= (const float& f)
{
	x -= f;
	y -= f;
	z -= f;
	w -= f;
}

void LMVector4::operator *= (const float& f)
{
	x *= f;
	y *= f;
	z *= f;
	w *= f;
}

void LMVector4::operator /= (const float& f)
{
	if (f != 0.0f)
	{
		x /= f;
		y /= f;
		z /= f;
		w /= f;
	}
	else x = y = z = w = 0.0f;
}

bool LMVector4::operator == (const LMVector4 & v)
{
	return v.x == x && v.y == y && v.z == z && v.w == w;
}

bool LMVector4::operator != (const LMVector4 & v)
{
	return v.x != x || v.y != y || v.z != z || v.w != w;
}

void LMVector4::operator = (const LMVector4 &v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;
}

float LMVector4::operator[](int i) const
{
	/*
	switch (i)
	{
	case 0: return x;
	case 1: return y;
	case 2: return z;
	}
	*/

	return (&x)[i];
}

float & LMVector4::operator [] (int i)
{
	return (&x)[i];
}

/*
float & LMVector4::x() const { return values[0]; }
float & LMVector4::y() const { return values[1]; }
float & LMVector4::z() const { return values[2]; }
float & LMVector4::w() const { return values[3]; }
*/

float& LMVector4::r() { return values[0]; }
float& LMVector4::g() { return values[1]; }
float& LMVector4::b() { return values[2]; }
float& LMVector4::a() { return values[3]; }

float& LMVector4::left() { return values[0]; }
float& LMVector4::top() { return values[1]; }
float& LMVector4::right() { return values[2]; }
float& LMVector4::bottom() { return values[3]; }