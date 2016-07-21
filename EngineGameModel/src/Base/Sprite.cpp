#include "Sprite.h"

Sprite::Sprite()
{

}

Sprite::Sprite(	LMVector3 position,
				LMVector3 rotation,
				LMVector3 scale,
				LMVector3 velocity, 
				LMVector3 spin,
				LMVector3 resize,
				float acceleration )
{
	//m_isActive = false;
	m_physicsObject = PhysicsObject(position, rotation, scale, velocity, spin, resize, 1.0f);

}

Sprite::~Sprite() {}

PhysicsObject * Sprite::GetPhysicsObject() { return &m_physicsObject; }

//bool Sprite::GetIsActive() { return m_isActive; }

//void Sprite::SetIsActive(bool isActiveStatus) { m_isActive = isActiveStatus; }
