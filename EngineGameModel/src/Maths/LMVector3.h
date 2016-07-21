#if !defined(LMVECTOR3_H)
#define LMVECTOR3_H


class LMVector3
{
public:

	float x, y, z;

	LMVector3();
	LMVector3(float x, float y, float z);
	LMVector3(LMVector3 & v);
	~LMVector3();

	void operator += (const LMVector3& v);
	void operator -= (const LMVector3& v);
	void operator *= (const LMVector3& v);
	void operator /= (const LMVector3& v);

	bool operator == (const LMVector3 & v);
	bool operator != (const LMVector3 & v);

	void operator  = (const float& f);
	void operator += (const float& f);
	void operator -= (const float& f);
	void operator *= (const float& f);
	void operator /= (const float& f);
	
	void operator = (const LMVector3 &v);
	LMVector3 operator + (const LMVector3 &v);
	LMVector3 operator * (const float f);

	float & operator [](int i);

	float LengthSq();
	
	float Magnitude();

	float DisplacementMag(const LMVector3 & v);

	void Normalize();

	bool IsInRegion(LMVector3 * start, LMVector3 * end);

	bool IsRangeFurther(const LMVector3 & v, float range);


};

#endif