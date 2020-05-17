#include "lightclass.h"

LightClass::LightClass()
{
}


LightClass::LightClass(const LightClass& other)
{
}


LightClass::~LightClass()
{
}


void LightClass::SetDiffuseColor(float red, float green, float blue, float alpha)
{
	m_diffuseColor[0] = red;
	m_diffuseColor[1] = green;
	m_diffuseColor[2] = blue;
	m_diffuseColor[3] = alpha;
	return;
}


void LightClass::SetDirection(float x, float y, float z)
{
	m_direction[0] = x;
	m_direction[1] = y;
	m_direction[2] = z;
	return;
}

void LightClass::SetAmbientLight(float red, float green, float blue, float alpha)
{
	m_ambientLight[0] = red;
	m_ambientLight[1] = green;
	m_ambientLight[2] = blue;
	m_ambientLight[3] = alpha;
	return;
}


void LightClass::GetDiffuseColor(float* color)	
{
	color[0] = m_diffuseColor[0];
	color[1] = m_diffuseColor[1];
	color[2] = m_diffuseColor[2];
	color[3] = m_diffuseColor[3];
	return;
}


void LightClass::GetDirection(float* direction)
{
	direction[0] = m_direction[0];
	direction[1] = m_direction[1];
	direction[2] = m_direction[2];
	return;
}

void LightClass::GetAmbientLight(float* ambient)
{
	ambient[0] = m_ambientLight[0];
	ambient[1] = m_ambientLight[1];
	ambient[2] = m_ambientLight[2];
	ambient[3] = m_ambientLight[3];
	return;
}
