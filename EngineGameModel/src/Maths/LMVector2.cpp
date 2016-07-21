#include "LMVector2.h"



LMVector2::LMVector2()
{
	x = 0.0f;
	y = 0.0f;
}

LMVector2::LMVector2(float fx, float fy)
{
	x = fx;
	y = fy;
}

LMVector2::LMVector2(LMVector2 & v)
{
	x = v.x;
	y = v.y;
}


LMVector2::~LMVector2()
{
	x = 0.0f;
	y = 0.0f;
}

void LMVector2::operator += (const LMVector2 & v)
{
	x += v.x;
	y += v.y;
}

void LMVector2::operator -= (const LMVector2& v)
{
	x -= v.x;
	y -= v.y;
}

void LMVector2::operator *= (const LMVector2& v)
{
	x *= v.x;
	y *= v.y;
}

void LMVector2::operator /= (const LMVector2& v)
{
	x /= v.x;
	y /= v.y;
	
}

bool LMVector2::operator == (const LMVector2 & v)
{
	return v.x == x && v.y == y;
}

bool LMVector2::operator != (const LMVector2 & v)
{
	return v.x != x || v.y != y;
}
