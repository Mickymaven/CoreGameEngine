#if !defined(LMVECTOR4_H)
#define LMVECTOR4_H

class LMVector4
{
private:
	

public:
	float x, y, z, w;

	float * values=&x;
	LMVector4();
	LMVector4(float x, float y, float z, float w);
	LMVector4(LMVector4 & v);
	~LMVector4();

	void operator += (const LMVector4& v);
	void operator -= (const LMVector4& v);
	void operator *= (const LMVector4& v);
	void operator /= (const LMVector4& v);

	bool operator == (const LMVector4 & v);
	bool operator != (const LMVector4 & v);

	void operator  = (const float& f);
	void operator += (const float& f);
	void operator -= (const float& f);
	void operator *= (const float& f);
	void operator /= (const float& f);

	void operator = (const LMVector4 &v);
	LMVector4 operator + (const LMVector4 &v);
	LMVector4 operator * (const float f);

	float operator [](int i) const;
	float & operator [](int i);

	/*float &x() const;
	float &y() const;
	float &z() const;
	float &w() const;*/

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