#include "LMMatrix3.h"




///////////////////////////////////////////////////////////////////////////////
// transpose 3x3 matrix
///////////////////////////////////////////////////////////////////////////////
LMMatrix3& LMMatrix3::transpose()
{
	std::swap(m[1], m[3]);
	std::swap(m[2], m[6]);
	std::swap(m[5], m[7]);

	return *this;
}



///////////////////////////////////////////////////////////////////////////////
// return determinant of 3x3 matrix
///////////////////////////////////////////////////////////////////////////////
float LMMatrix3::getDeterminant() const
{
	return m[0] * (m[4] * m[8] - m[5] * m[7]) -
		m[1] * (m[3] * m[8] - m[5] * m[6]) +
		m[2] * (m[3] * m[7] - m[4] * m[6]);
}



///////////////////////////////////////////////////////////////////////////////
// inverse 3x3 matrix
// If cannot find inverse (det=0), set identity matrix
// M^-1 = adj(M) / det(M)
//        | m4m8-m5m7  m5m6-m3m8  m3m7-m4m6 |
//      = | m7m2-m8m1  m0m8-m2m6  m6m1-m7m0 | / det(M)
//        | m1m5-m2m4  m2m3-m0m5  m0m4-m1m3 |
///////////////////////////////////////////////////////////////////////////////
LMMatrix3& LMMatrix3::invert()
{
	float determinant, invDeterminant;
	float tmp[9];

	tmp[0] = m[4] * m[8] - m[5] * m[7];
	tmp[1] = m[7] * m[2] - m[8] * m[1];
	tmp[2] = m[1] * m[5] - m[2] * m[4];
	tmp[3] = m[5] * m[6] - m[3] * m[8];
	tmp[4] = m[0] * m[8] - m[2] * m[6];
	tmp[5] = m[2] * m[3] - m[0] * m[5];
	tmp[6] = m[3] * m[7] - m[4] * m[6];
	tmp[7] = m[6] * m[1] - m[7] * m[0];
	tmp[8] = m[0] * m[4] - m[1] * m[3];

	// check determinant if it is 0
	determinant = m[0] * tmp[0] + m[1] * tmp[3] + m[2] * tmp[6];
	if (fabs(determinant) <= EPSILON)
	{
		return identity(); // cannot inverse, make it idenety matrix
	}

	// divide by the determinant
	invDeterminant = 1.0f / determinant;
	m[0] = invDeterminant * tmp[0];
	m[1] = invDeterminant * tmp[1];
	m[2] = invDeterminant * tmp[2];
	m[3] = invDeterminant * tmp[3];
	m[4] = invDeterminant * tmp[4];
	m[5] = invDeterminant * tmp[5];
	m[6] = invDeterminant * tmp[6];
	m[7] = invDeterminant * tmp[7];
	m[8] = invDeterminant * tmp[8];

	return *this;
}



///////////////////////////////////////////////////////////////////////////////
// retrieve angles in degree from rotation matrix, M = Rx*Ry*Rz
// Rx: rotation about X-axis, pitch
// Ry: rotation about Y-axis, yaw(heading)
// Rz: rotation about Z-axis, roll
//    Rx           Ry          Rz
// |1  0   0| | Cy  0 Sy| |Cz -Sz 0|   | CyCz        -CySz         Sy  |
// |0 Cx -Sx|*|  0  1  0|*|Sz  Cz 0| = | SxSyCz+CxSz -SxSySz+CxCz -SxCy|
// |0 Sx  Cx| |-Sy  0 Cy| | 0   0 1|   |-CxSyCz+SxSz  CxSySz+SxCz  CxCy|
//
// Pitch: atan(-m[7] / m[8]) = atan(SxCy/CxCy)
// Yaw  : asin(m[6]) = asin(Sy)
// Roll : atan(-m[3] / m[0]) = atan(SzCy/CzCy)
///////////////////////////////////////////////////////////////////////////////
LMVector3 LMMatrix3::getAngle() const
{
	float pitch, yaw, roll;         // 3 angles

	// find yaw (around y-axis) first
	// NOTE: asin() returns -90~+90, so correct the angle range -180~+180
	// using z value of forward vector
	yaw = RAD2DEG * asinf(m[6]);
	if (m[8] < 0)
	{
		if (yaw >= 0) yaw = 180.0f - yaw;
		else         yaw = -180.0f - yaw;
	}

	// find roll (around z-axis) and pitch (around x-axis)
	// if forward vector is (1,0,0) or (-1,0,0), then m[0]=m[4]=m[9]=m[10]=0
	if (m[0] > -EPSILON && m[0] < EPSILON)
	{
		roll = 0;  //@@ assume roll=0
		pitch = RAD2DEG * atan2f(m[1], m[4]);
	}
	else
	{
		roll = RAD2DEG * atan2f(-m[3], m[0]);
		pitch = RAD2DEG * atan2f(-m[7], m[8]);
	}

	return LMVector3(pitch, yaw, roll);
}

//=============================================================================
