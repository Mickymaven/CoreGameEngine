#include "Boid.h"


float Boid::sm_xmax = 0.0f;
float Boid::sm_zmax = 0.0f;

Boid::Boid()
{

}

Boid::Boid( float xmax, float zmax,
					LMVector3 position,
					LMVector3 rotation,
					LMVector3 scale,
					LMVector3 velocity,
					LMVector3 spin,
					LMVector3 resize,
					float acceleration, 
					LMVector3 * origin)
					:Sprite(position, rotation, scale, velocity, spin, resize, acceleration)
{


	if (sm_xmax == 0.0f) sm_xmax = xmax;
	if (sm_zmax == 0.0f) sm_zmax = zmax;
	m_origin = LMVector3(*origin);


	m_seperation = LMVector3(0.0f, 0.0f, 0.0f);
	m_cohesion = LMVector3(0.0f, 0.0f, 0.0f);
	m_alignment = LMVector3(0.0f, 0.0f, 0.0f);
	m_random = LMVector3(0.0f, 0.0f, 0.0f);
	m_inBounds = LMVector3(0.0f, 0.0f, 0.0f);
	m_attractOrigin = LMVector3(0.0f, 0.0f, 0.0f);
	m_compositeVector = LMVector3(0.0f, 0.0f, 0.0f);

	m_minVelocity = 15.0f;
	m_maxVelocity = 30.0f;

	m_pPos = GetPhysicsObject()->GetPosition();

	m_fAngleRads = 0.0f;

	m_cohesionfactor = 0.007f;
	m_alignmentFactor = 0.9f;

	m_originfactor = 4.0f;
	m_inBoundsFactor = 10.0f;


	m_rotateSpeed = 2.0f;
	m_isRotateOn = false;
}

Boid::~Boid()
{

}

void Boid::Update(const float fDeltaTime)
{
	m_compositeVector *= 0.0f;

	//Seperation
	m_compositeVector = m_seperation;

	//Cohesion
	m_compositeVector += (m_cohesion * m_cohesionfactor);

	//Alignment
	m_compositeVector += (m_alignment * m_alignmentFactor);

	//Free Will
	FreeWill(fDeltaTime);
	AttractionToOrigin(fDeltaTime);
	StayInBounds(fDeltaTime);

	m_compositeVector.y = 0.0f;

	m_seperation *= 0.0f;
	m_cohesion *= 0.0f;
	m_alignment *= 0.0f;
	//dont 0 random that is retained momentum over updates


	float min = 2.0f;

	float resultX = m_compositeVector.x;
	float resultY = m_compositeVector.y;
	float resultZ = m_compositeVector.z;

	float length = sqrt(abs(resultX*resultX + resultY*resultY + resultZ*resultZ));

	//speed limits

	if (length > 0)
	{
		if (length * fDeltaTime > m_maxVelocity * fDeltaTime) //max speed 8
		{
			m_compositeVector.x /= length;
			m_compositeVector.y /= length;
			m_compositeVector.z /= length;

			m_compositeVector *= m_maxVelocity;
		}
		else if (length * fDeltaTime < m_minVelocity * fDeltaTime) //min speed 3
		{
			m_compositeVector.x /= length;
			m_compositeVector.y /= length;
			m_compositeVector.z /= length;

			m_compositeVector *= m_minVelocity;
		}
	}

	if (length > min) //rotate only for min speed;
	{

	}



	float newAngle = atan2(m_compositeVector.x, m_compositeVector.z);

	//gradual rotate
	if (m_isRotateOn)
	{
		if (newAngle > m_fAngleRads) m_fAngleRads += fDeltaTime * m_rotateSpeed * (newAngle - m_fAngleRads);
		else if (newAngle < m_fAngleRads) m_fAngleRads -= fDeltaTime * m_rotateSpeed * (m_fAngleRads - newAngle);
	}
	//no rotate
	else m_fAngleRads = newAngle;

	/*
	if (0)
	{
		char bufferx[100];

		sprintf(bufferx, "in rads %f\n", fAngleRads);
		OutputDebugString(bufferx);
	}
	*/
	//m_compositeVector *= ;


	//Sprite::GetPhysicsObject()->GetRotation()->x = 0.0f;
	Sprite::GetPhysicsObject()->GetRotation()->y = m_fAngleRads;
	//Sprite::GetPhysicsObject()->GetRotation()->z = 0.0f;

	Sprite::GetPhysicsObject()->GetVelocity()->x = m_compositeVector.x;
	Sprite::GetPhysicsObject()->GetVelocity()->y = m_compositeVector.y;
	Sprite::GetPhysicsObject()->GetVelocity()->z = m_compositeVector.z;
	
	Sprite::GetPhysicsObject()->Update(fDeltaTime);

	//todo where to use fDelta time, im physics object or before.
	
}

void Boid::FreeWill(float deltaTime)
{
	if (true)
	{

		if (rand() % 1000 < 30)
		{
			float range = 0.4f;
			if (rand() % 1000 < 500) range = 0.3f;

			float granularity = 100;
			int modvalue = range * granularity;

			for (unsigned int i = 0; i < 3; i++)
			{
				if (i == 1) { m_random[1] = 0.0f; continue; }

				m_random[i] = (rand() % modvalue / granularity) - (0.5f * range);

				//sm_xmax 400
				//m_origin = 200
			}
		}
	}

	else {
		if (rand() % 1000 < 7)
		{
			float range = 2;
			if (rand() % 1000 < 20) range = 75;

			float granularity = 100;
			int modvalue = range * granularity;

			for (unsigned int i = 0; i < 3; i++)
			{
				if (i == 1) { m_random[1] = 0.0f; continue; }

				m_random[i] = (rand() % modvalue / granularity) - (0.5f * range);
			
				//sm_xmax 400
				//m_origin = 200
			}
		}
	}
	
	m_compositeVector += m_random;
}

void Boid::AttractionToOrigin(float deltaTime)
{

	m_tempDisplacement.x = m_pPos->x - m_origin.x;
	m_tempDisplacement.y = m_pPos->y - m_origin.y;
	m_tempDisplacement.z = m_pPos->z - m_origin.z;

	float length = m_tempDisplacement.Magnitude();

	m_tempDisplacement.Normalize();

	//length usually upto map edge from center
	//radius 200 units (map edge from center, corners further)
	m_tempDisplacement *= length / (0.5f * sm_zmax);//length / radius

	m_compositeVector += (m_attractOrigin * m_originfactor);
}

void Boid::StayInBounds(float deltaTime)
{
	if (m_pPos->x > (m_origin.x + (0.5f * sm_xmax))) { m_inBounds.x = -m_inBoundsFactor; }
	if (m_pPos->x < (m_origin.x - (0.5f * sm_xmax))) { m_inBounds.x = m_inBoundsFactor; }

	if (m_pPos->z >(m_origin.z + (0.5f * sm_zmax))) { m_inBounds.z = -m_inBoundsFactor; }
	if (m_pPos->z < (m_origin.z - (0.5f * sm_zmax))) { m_inBounds.z = m_inBoundsFactor; }

	m_compositeVector += m_inBounds;
}


void Boid::SetOrigin(LMVector3 * origin) { m_origin = *origin; }

void Boid::SetSeperationVector(const LMVector3 & seperation) { m_seperation = seperation; }
void Boid::SetAlignmentVector(const LMVector3 & alignment) { m_alignment = alignment; }
void Boid::SetCohesionVector(const LMVector3 & cohesion) { m_cohesion = cohesion; }

LMVector3 * Boid::GetCompositeVector() { return &m_compositeVector; }
LMVector3 * Boid::GetSeperationVector() { return &m_seperation; }
LMVector3 * Boid::GetCohesionVector() { return &m_cohesion; }
LMVector3 * Boid::GetAlignmentVector() { return &m_alignment; }