#if !defined(LMMATRIX2_H)
#define LMMATRIX2_H

#include "LMMatrix.h"
#include "LMVector2.h"

#include <cmath>
#include <algorithm>


class LMMatrix2
{
public:
	// constructors
	LMMatrix2();  // init with identity
	LMMatrix2(const float src[4]);
	LMMatrix2(float m0, float m1, float m2, float m3);

	void        set(const float src[4]);
	void        set(float m0, float m1, float m2, float m3);
	void        setRow(int index, const float row[2]);
	void        setRow(int index, const LMVector2& v);
	void        setColumn(int index, const float col[2]);
	void        setColumn(int index, const LMVector2& v);

	const float* get() const;
	float       getDeterminant() const;
	float       getAngle() const;                       // retrieve angle (degree) from matrix

	LMMatrix2&    identity();
	LMMatrix2&    transpose();                            // transpose itself and return reference
	LMMatrix2&    invert();

	// operators
	LMMatrix2     operator+(const LMMatrix2& rhs) const;    // add rhs
	LMMatrix2     operator-(const LMMatrix2& rhs) const;    // subtract rhs
	LMMatrix2&    operator+=(const LMMatrix2& rhs);         // add rhs and update this object
	LMMatrix2&    operator-=(const LMMatrix2& rhs);         // subtract rhs and update this object
	LMVector2     operator*(const LMVector2& rhs) const;    // multiplication: v' = M * v
	LMMatrix2     operator*(const LMMatrix2& rhs) const;    // multiplication: M3 = M1 * M2
	LMMatrix2&    operator*=(const LMMatrix2& rhs);         // multiplication: M1' = M1 * M2
	bool        operator==(const LMMatrix2& rhs) const;   // exact compare, no epsilon
	bool        operator!=(const LMMatrix2& rhs) const;   // exact compare, no epsilon
	float       operator[](int index) const;            // subscript operator v[0], v[1]
	float&      operator[](int index);                  // subscript operator v[0], v[1]

	// friends functions
	friend LMMatrix2 operator-(const LMMatrix2& m);                     // unary operator (-)
	friend LMMatrix2 operator*(float scalar, const LMMatrix2& m);       // pre-multiplication
	friend LMVector2 operator*(const LMVector2& vec, const LMMatrix2& m); // pre-multiplication
	//friend std::ostream& operator<<(std::ostream& os, const LMMatrix2& m);

	// static functions

protected:

private:
	float m[4];

}; 


///////////////////////////////////////////////////////////////////////////
// inline functions for LMMatrix2
///////////////////////////////////////////////////////////////////////////
inline LMMatrix2::LMMatrix2()
{
	// initially identity matrix
	identity();
}



inline LMMatrix2::LMMatrix2(const float src[4])
{
	set(src);
}



inline LMMatrix2::LMMatrix2(float m0, float m1, float m2, float m3)
{
	set(m0, m1, m2, m3);
}



inline void LMMatrix2::set(const float src[4])
{
	m[0] = src[0];  m[1] = src[1];  m[2] = src[2];  m[3] = src[3];
}



inline void LMMatrix2::set(float m0, float m1, float m2, float m3)
{
	m[0] = m0;  m[1] = m1;  m[2] = m2;  m[3] = m3;
}



inline void LMMatrix2::setRow(int index, const float row[2])
{
	m[index] = row[0];  m[index + 2] = row[1];
}



inline void LMMatrix2::setRow(int index, const LMVector2& v)
{
	m[index] = v.x;  m[index + 2] = v.y;
}



inline void LMMatrix2::setColumn(int index, const float col[2])
{
	m[index * 2] = col[0];  m[index * 2 + 1] = col[1];
}



inline void LMMatrix2::setColumn(int index, const LMVector2& v)
{
	m[index * 2] = v.x;  m[index * 2 + 1] = v.y;
}



inline const float* LMMatrix2::get() const
{
	return m;
}

inline LMMatrix2& LMMatrix2::identity()
{
	m[0] = m[3] = 1.0f;
	m[1] = m[2] = 0.0f;
	return *this;
}



inline LMMatrix2 LMMatrix2::operator+(const LMMatrix2& rhs) const
{
	return LMMatrix2(m[0] + rhs[0], m[1] + rhs[1], m[2] + rhs[2], m[3] + rhs[3]);
}



inline LMMatrix2 LMMatrix2::operator-(const LMMatrix2& rhs) const
{
	return LMMatrix2(m[0] - rhs[0], m[1] - rhs[1], m[2] - rhs[2], m[3] - rhs[3]);
}



inline LMMatrix2& LMMatrix2::operator+=(const LMMatrix2& rhs)
{
	m[0] += rhs[0];  m[1] += rhs[1];  m[2] += rhs[2];  m[3] += rhs[3];
	return *this;
}



inline LMMatrix2& LMMatrix2::operator-=(const LMMatrix2& rhs)
{
	m[0] -= rhs[0];  m[1] -= rhs[1];  m[2] -= rhs[2];  m[3] -= rhs[3];
	return *this;
}



inline LMVector2 LMMatrix2::operator*(const LMVector2& rhs) const
{
	return LMVector2(m[0] * rhs.x + m[2] * rhs.y, m[1] * rhs.x + m[3] * rhs.y);
}



inline LMMatrix2 LMMatrix2::operator*(const LMMatrix2& rhs) const
{
	return LMMatrix2(m[0] * rhs[0] + m[2] * rhs[1], m[1] * rhs[0] + m[3] * rhs[1],
		m[0] * rhs[2] + m[2] * rhs[3], m[1] * rhs[2] + m[3] * rhs[3]);
}



inline LMMatrix2& LMMatrix2::operator*=(const LMMatrix2& rhs)
{
	*this = *this * rhs;
	return *this;
}



inline bool LMMatrix2::operator==(const LMMatrix2& rhs) const
{
	return (m[0] == rhs[0]) && (m[1] == rhs[1]) && (m[2] == rhs[2]) && (m[3] == rhs[3]);
}



inline bool LMMatrix2::operator!=(const LMMatrix2& rhs) const
{
	return (m[0] != rhs[0]) || (m[1] != rhs[1]) || (m[2] != rhs[2]) || (m[3] != rhs[3]);
}



inline float LMMatrix2::operator[](int index) const
{
	return m[index];
}



inline float& LMMatrix2::operator[](int index)
{
	return m[index];
}



inline LMMatrix2 operator-(const LMMatrix2& rhs)
{
	return LMMatrix2(-rhs[0], -rhs[1], -rhs[2], -rhs[3]);
}



inline LMMatrix2 operator*(float s, const LMMatrix2& rhs)
{
	return LMMatrix2(s*rhs[0], s*rhs[1], s*rhs[2], s*rhs[3]);
}



inline LMVector2 operator*(const LMVector2& v, const LMMatrix2& rhs)
{
	return LMVector2(v.x*rhs[0] + v.y*rhs[1], v.x*rhs[2] + v.y*rhs[3]);
}

/*

inline std::ostream& operator<<(std::ostream& os, const LMMatrix2& m)
{
	os << std::fixed << std::setprecision(5);
	os << "[" << std::setw(10) << m[0] << " " << std::setw(10) << m[2] << "]\n"
		<< "[" << std::setw(10) << m[1] << " " << std::setw(10) << m[3] << "]\n";
	os << std::resetiosflags(std::ios_base::fixed | std::ios_base::floatfield);
	return os;
}*/
// END OF LMMatrix2 INLINE //////////////////////////////////////////////////////


#endif