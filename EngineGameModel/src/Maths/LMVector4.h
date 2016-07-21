#if !defined(LMVECTOR4_H)
#define LMVECTOR4_H

class LMVector4
{
private:
	

public:

	float values[4];
	LMVector4();
	LMVector4(float x, float y, float z, float w);
	LMVector4(LMVector4 & v);
	~LMVector4();

	float&x();
	float&y();
	float&z();
	float&w();

	float&r();
	float&g();
	float&b();
	float&a();

	float&left();
	float&top();
	float&right();
	float&bottom();
};

#endif