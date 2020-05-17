#include "LMMatrix2.h"

///////////////////////////////////////////////////////////////////////////////
// transpose 2x2 matrix
///////////////////////////////////////////////////////////////////////////////
LMMatrix2& LMMatrix2::transpose()
{
	std::swap(m[1], m[2]);
	return *this;
}



///////////////////////////////////////////////////////////////////////////////
// return the determinant of 2x2 matrix
///////////////////////////////////////////////////////////////////////////////
float LMMatrix2::getDeterminant() const
{
	return m[0] * m[3] - m[1] * m[2];
}



///////////////////////////////////////////////////////////////////////////////
// inverse of 2x2 matrix
// If cannot find inverse, set identity matrix
///////////////////////////////////////////////////////////////////////////////
LMMatrix2& LMMatrix2::invert()
{
	float determinant = getDeterminant();
	if (fabs(determinant) <= EPSILON)
	{
		return identity();
	}

	float tmp = m[0];   // copy the first element
	float invDeterminant = 1.0f / determinant;
	m[0] = invDeterminant * m[3];
	m[1] = -invDeterminant * m[1];
	m[2] = -invDeterminant * m[2];
	m[3] = invDeterminant * tmp;

	return *this;
}



///////////////////////////////////////////////////////////////////////////////
// retrieve rotation angle in degree from rotation matrix, R
// R = | c -s |
//     | s  c |
// angle = atan(s / c)
///////////////////////////////////////////////////////////////////////////////
float LMMatrix2::getAngle() const
{
	// angle between -pi ~ +pi (-180 ~ +180)
	return RAD2DEG * atan2f(m[1], m[0]);
}

//=============================================================================


