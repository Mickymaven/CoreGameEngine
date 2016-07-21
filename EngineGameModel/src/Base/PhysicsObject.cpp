#include "PhysicsObject.h"

PhysicsObject::PhysicsObject()
{

}
	
PhysicsObject::PhysicsObject(LMVector3 position, LMVector3 rotation, LMVector3 scale, LMVector3 velocity, LMVector3 spin, LMVector3 resize, float initialRadius)
{
	//OutputDebugString("Physics object initialised");
	m_position = position;
	m_rotation = rotation;
	m_scale = scale;

	m_velocity = velocity;
	m_spin = spin;
	m_resize = resize;
	
	/*
	m_pPosition = position;
	m_pRotation = rotation;
	m_pScale = scale;
	m_pVelocity = velocity;
	m_acceleration = acceleration;
	m_pSpin = spin;
	m_pResize = resize;
	*/

	m_radius = initialRadius;
	/*
	m_noMove = LMVector3( 0.0f, 0.0f, 0.0f );
	m_right = LMVector3 ( 1.0f, 0.0f, 0.0f );
	m_up = LMVector3 ( 0.0f, 1.0f, 0.0f );
	m_forward = LMVector3 ( 0.0f, 0.0f, 1.0f );
	*/
}

PhysicsObject::~PhysicsObject()
{
}

LMVector3 * PhysicsObject::GetPosition()
{
	return &m_position;
}

LMVector3 * PhysicsObject::GetRotation()
{
	return &m_rotation;
}


LMVector3 * PhysicsObject::GetScale()
{
	return &m_scale;
}

LMVector3 * PhysicsObject::GetVelocity()
{
	return &m_velocity;
}

LMVector3 * PhysicsObject::GetSpin()
{
	return &m_spin;
}

LMVector3 * PhysicsObject::GetResize()
{
	return &m_resize;
}

float PhysicsObject::GetRadius()
{
	return m_radius;
}

void PhysicsObject::SetPosition(LMVector3& position)
{
	m_position = position;
}

void PhysicsObject::SetRotation(LMVector3& rotation)
{
	m_rotation = rotation;
}

void PhysicsObject::SetScale(LMVector3& scale)
{
	m_scale = scale;
}

void PhysicsObject::SetVelocity(LMVector3& velocity)
{
	m_velocity = velocity;
}

void PhysicsObject::SetSpin(LMVector3& spin)
{
	m_spin = spin;
}

void PhysicsObject::SetResize(LMVector3& resize)
{
	m_resize = resize;
}

void PhysicsObject::SetRadius(float radius)
{
	m_radius = radius;
}

/*
void PhysicsObject::Strafe(float units)
{
	m_position += m_right * units;
}*/

void PhysicsObject::Update(const float timeStep)
{	
	m_position += m_velocity * timeStep;
	m_rotation += m_spin * timeStep;
	m_scale += m_resize * timeStep;
}
