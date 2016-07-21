#include "LMVector4.h"

LMVector4::LMVector4() { 

	values[0] = 0.0f;
	values[1] = 0.0f;
	values[2] = 0.0f;
	values[3] = 0.0f;
}

LMVector4::LMVector4(float fx, float fy, float fz, float fw)
{
	values[0] = fx;
	values[1] = fy;
	values[2] = fz;
	values[3] = fw;
}

LMVector4::LMVector4(LMVector4 & v)
{
	/*
	values[0] = v.x;
	values[1] = v.y;
	values[2] = v.z;
	values[3] = v.w;
*/
}

LMVector4::~LMVector4() {  }

float& LMVector4::x() { return values[0]; }
float& LMVector4::y() { return values[1]; }
float& LMVector4::z() { return values[2]; }
float& LMVector4::w() { return values[3]; }

float& LMVector4::r() { return values[0]; }
float& LMVector4::g() { return values[1]; }
float& LMVector4::b() { return values[2]; }
float& LMVector4::a() { return values[3]; }

float& LMVector4::left() { return values[0]; }
float& LMVector4::top() { return values[1]; }
float& LMVector4::right() { return values[2]; }
float& LMVector4::bottom() { return values[3]; }