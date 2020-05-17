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
	LMVector3 operator - (const LMVector3& rhs) const;    // subtract rhs
	LMVector3 operator + (const LMVector3 &v);
	LMVector3 operator * (const float f);

	float operator [](int i) const;
	float & operator [](int i);

	void set(float vx, float vy, float vz);

	float dot(const LMVector3& vec) const;          // dot product
	LMVector3 cross(const LMVector3& vec) const;        // cross product

	float LengthSq();
	
	float Magnitude();

	float DisplacementMag(const LMVector3 & v);

	void Normalize();

	bool IsInRegion(LMVector3 * start, LMVector3 * end);

	bool IsRangeFurther(const LMVector3 & v, float range);


};


inline float LMVector3::dot(const LMVector3& rhs) const {
	return (x*rhs.x + y * rhs.y + z * rhs.z);
}

inline LMVector3 LMVector3::cross(const LMVector3& rhs) const {
	return LMVector3(y*rhs.z - z * rhs.y, z*rhs.x - x * rhs.z, x*rhs.y - y * rhs.x);
}

#endif