#if !defined(LMMATRIX3_H)
#define LMMATRIX3_H

#include "LMMatrix.h"
#include "LMVector3.h"
#include "LMVector4.h"

#include <cmath>
#include <algorithm>

class LMMatrix3
{
public:

	// constructors
	LMMatrix3();  // init with identity
	LMMatrix3(const float src[9]);
	LMMatrix3(float m0, float m1, float m2,           // 1st column
		float m3, float m4, float m5,           // 2nd column
		float m6, float m7, float m8);          // 3rd column

	void        set(const float src[9]);
	void        set(float m0, float m1, float m2,   // 1st column
		float m3, float m4, float m5,   // 2nd column
		float m6, float m7, float m8);  // 3rd column
	void        setRow(int index, const float row[3]);
	void        setRow(int index, const LMVector3& v);
	void        setColumn(int index, const float col[3]);
	void        setColumn(int index, const LMVector3& v);

	const float* get() const;
	float       getDeterminant() const;
	LMVector3     getAngle() const;                       // return (pitch, yaw, roll)

	LMMatrix3&    identity();
	LMMatrix3&    transpose();                            // transpose itself and return reference
	LMMatrix3&    invert();

	// operators
	LMMatrix3     operator+(const LMMatrix3& rhs) const;    // add rhs
	LMMatrix3     operator-(const LMMatrix3& rhs) const;    // subtract rhs
	LMMatrix3&    operator+=(const LMMatrix3& rhs);         // add rhs and update this object
	LMMatrix3&    operator-=(const LMMatrix3& rhs);         // subtract rhs and update this object
	LMVector3     operator*(const LMVector3& rhs) const;    // multiplication: v' = M * v
	LMMatrix3     operator*(const LMMatrix3& rhs) const;    // multiplication: M3 = M1 * M2
	LMMatrix3&    operator*=(const LMMatrix3& rhs);         // multiplication: M1' = M1 * M2
	bool        operator==(const LMMatrix3& rhs) const;   // exact compare, no epsilon
	bool        operator!=(const LMMatrix3& rhs) const;   // exact compare, no epsilon
	float       operator[](int index) const;            // subscript operator v[0], v[1]
	float&      operator[](int index);                  // subscript operator v[0], v[1]

	// friends functions
	friend LMMatrix3 operator-(const LMMatrix3& m);                     // unary operator (-)
	friend LMMatrix3 operator*(float scalar, const LMMatrix3& m);       // pre-multiplication
	friend LMVector3 operator*(const LMVector3& vec, const LMMatrix3& m); // pre-multiplication
//	friend std::ostream& operator<<(std::ostream& os, const LMMatrix3& m);

protected:

private:
	float m[9];

};

///////////////////////////////////////////////////////////////////////////
// inline functions for Matrix3
///////////////////////////////////////////////////////////////////////////
inline LMMatrix3::LMMatrix3()
{
	// initially identity matrix
	identity();
}



inline LMMatrix3::LMMatrix3(const float src[9])
{
	set(src);
}



inline LMMatrix3::LMMatrix3(float m0, float m1, float m2,
	float m3, float m4, float m5,
	float m6, float m7, float m8)
{
	set(m0, m1, m2, m3, m4, m5, m6, m7, m8);
}



inline void LMMatrix3::set(const float src[9])
{
	m[0] = src[0];  m[1] = src[1];  m[2] = src[2];
	m[3] = src[3];  m[4] = src[4];  m[5] = src[5];
	m[6] = src[6];  m[7] = src[7];  m[8] = src[8];
}



inline void LMMatrix3::set(float m0, float m1, float m2,
	float m3, float m4, float m5,
	float m6, float m7, float m8)
{
	m[0] = m0;  m[1] = m1;  m[2] = m2;
	m[3] = m3;  m[4] = m4;  m[5] = m5;
	m[6] = m6;  m[7] = m7;  m[8] = m8;
}



inline void LMMatrix3::setRow(int index, const float row[3])
{
	m[index] = row[0];  m[index + 3] = row[1];  m[index + 6] = row[2];
}



inline void LMMatrix3::setRow(int index, const LMVector3& v)
{
	m[index] = v.x;  m[index + 3] = v.y;  m[index + 6] = v.z;
}



inline void LMMatrix3::setColumn(int index, const float col[3])
{
	m[index * 3] = col[0];  m[index * 3 + 1] = col[1];  m[index * 3 + 2] = col[2];
}



inline void LMMatrix3::setColumn(int index, const LMVector3& v)
{
	m[index * 3] = v.x;  m[index * 3 + 1] = v.y;  m[index * 3 + 2] = v.z;
}



inline const float* LMMatrix3::get() const
{
	return m;
}



inline LMMatrix3& LMMatrix3::identity()
{
	m[0] = m[4] = m[8] = 1.0f;
	m[1] = m[2] = m[3] = m[5] = m[6] = m[7] = 0.0f;
	return *this;
}



inline LMMatrix3 LMMatrix3::operator+(const LMMatrix3& rhs) const
{
	return LMMatrix3(m[0] + rhs[0], m[1] + rhs[1], m[2] + rhs[2],
		m[3] + rhs[3], m[4] + rhs[4], m[5] + rhs[5],
		m[6] + rhs[6], m[7] + rhs[7], m[8] + rhs[8]);
}



inline LMMatrix3 LMMatrix3::operator-(const LMMatrix3& rhs) const
{
	return LMMatrix3(m[0] - rhs[0], m[1] - rhs[1], m[2] - rhs[2],
		m[3] - rhs[3], m[4] - rhs[4], m[5] - rhs[5],
		m[6] - rhs[6], m[7] - rhs[7], m[8] - rhs[8]);
}



inline LMMatrix3& LMMatrix3::operator+=(const LMMatrix3& rhs)
{
	m[0] += rhs[0];  m[1] += rhs[1];  m[2] += rhs[2];
	m[3] += rhs[3];  m[4] += rhs[4];  m[5] += rhs[5];
	m[6] += rhs[6];  m[7] += rhs[7];  m[8] += rhs[8];
	return *this;
}



inline LMMatrix3& LMMatrix3::operator-=(const LMMatrix3& rhs)
{
	m[0] -= rhs[0];  m[1] -= rhs[1];  m[2] -= rhs[2];
	m[3] -= rhs[3];  m[4] -= rhs[4];  m[5] -= rhs[5];
	m[6] -= rhs[6];  m[7] -= rhs[7];  m[8] -= rhs[8];
	return *this;
}



inline LMVector3 LMMatrix3::operator*(const LMVector3& rhs) const
{
	return LMVector3(m[0] * rhs.x + m[3] * rhs.y + m[6] * rhs.z,
		m[1] * rhs.x + m[4] * rhs.y + m[7] * rhs.z,
		m[2] * rhs.x + m[5] * rhs.y + m[8] * rhs.z);
}



inline LMMatrix3 LMMatrix3::operator*(const LMMatrix3& rhs) const
{
	return LMMatrix3(m[0] * rhs[0] + m[3] * rhs[1] + m[6] * rhs[2], m[1] * rhs[0] + m[4] * rhs[1] + m[7] * rhs[2], m[2] * rhs[0] + m[5] * rhs[1] + m[8] * rhs[2],
		m[0] * rhs[3] + m[3] * rhs[4] + m[6] * rhs[5], m[1] * rhs[3] + m[4] * rhs[4] + m[7] * rhs[5], m[2] * rhs[3] + m[5] * rhs[4] + m[8] * rhs[5],
		m[0] * rhs[6] + m[3] * rhs[7] + m[6] * rhs[8], m[1] * rhs[6] + m[4] * rhs[7] + m[7] * rhs[8], m[2] * rhs[6] + m[5] * rhs[7] + m[8] * rhs[8]);
}



inline LMMatrix3& LMMatrix3::operator*=(const LMMatrix3& rhs)
{
	*this = *this * rhs;
	return *this;
}



inline bool LMMatrix3::operator==(const LMMatrix3& rhs) const
{
	return (m[0] == rhs[0]) && (m[1] == rhs[1]) && (m[2] == rhs[2]) &&
		(m[3] == rhs[3]) && (m[4] == rhs[4]) && (m[5] == rhs[5]) &&
		(m[6] == rhs[6]) && (m[7] == rhs[7]) && (m[8] == rhs[8]);
}



inline bool LMMatrix3::operator!=(const LMMatrix3& rhs) const
{
	return (m[0] != rhs[0]) || (m[1] != rhs[1]) || (m[2] != rhs[2]) ||
		(m[3] != rhs[3]) || (m[4] != rhs[4]) || (m[5] != rhs[5]) ||
		(m[6] != rhs[6]) || (m[7] != rhs[7]) || (m[8] != rhs[8]);
}



inline float LMMatrix3::operator[](int index) const
{
	return m[index];
}



inline float& LMMatrix3::operator[](int index)
{
	return m[index];
}



inline LMMatrix3 operator-(const LMMatrix3& rhs)
{
	return LMMatrix3(-rhs[0], -rhs[1], -rhs[2], -rhs[3], -rhs[4], -rhs[5], -rhs[6], -rhs[7], -rhs[8]);
}



inline LMMatrix3 operator*(float s, const LMMatrix3& rhs)
{
	return LMMatrix3(s*rhs[0], s*rhs[1], s*rhs[2], s*rhs[3], s*rhs[4], s*rhs[5], s*rhs[6], s*rhs[7], s*rhs[8]);
}



inline LMVector3 operator*(const LMVector3& v, const LMMatrix3& m)
{
	return LMVector3(v.x*m[0] + v.y*m[1] + v.z*m[2], v.x*m[3] + v.y*m[4] + v.z*m[5], v.x*m[6] + v.y*m[7] + v.z*m[8]);
}


/*
inline std::ostream& operator<<(std::ostream& os, const LMMatrix3& m)
{
	os << std::fixed << std::setprecision(5);
	os << "[" << std::setw(10) << m[0] << " " << std::setw(10) << m[3] << " " << std::setw(10) << m[6] << "]\n"
		<< "[" << std::setw(10) << m[1] << " " << std::setw(10) << m[4] << " " << std::setw(10) << m[7] << "]\n"
		<< "[" << std::setw(10) << m[2] << " " << std::setw(10) << m[5] << " " << std::setw(10) << m[8] << "]\n";
	os << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);
	return os;
}*/
// END OF MATRIX3 INLINE //////////////////////////////////////////////////////


#endif;