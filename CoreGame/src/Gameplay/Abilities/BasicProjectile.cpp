#include "BasicProjectile.h"

const float BasicProjectile::m_moveSpeed = 16.5f;

BasicProjectile::BasicProjectile()
{
	
}

BasicProjectile::BasicProjectile(
	LMVector3 position,
	LMVector3 rotation,
	LMVector3 scale,
	LMVector3 velocity,
	LMVector3 spin,
	LMVector3 resize,
	float acceleration)
	:Sprite(position, rotation, scale, velocity, spin, resize, acceleration)
{
	m_state = basicProjectileStateExpended;
	m_tempDisplacement = LMVector3(0.0f, 0.0f, 0.0f);
}

BasicProjectile::~BasicProjectile()
{
	
}

void BasicProjectile::Update(float deltaTime)
{
	m_physicsObject.Update(deltaTime);

	switch (m_state)
	{
	case basicProjectileStateSeeking:
		SeekingBehavior(deltaTime);
		break;
	case basicProjectileStateExpended:
		ExpendedBehavior(deltaTime);
		break;
	case basicProjectileStateCount:
		break;
	default:
		break;
	}
}


bool BasicProjectile::IsOverTarget()
{
	LMVector3 * pos = m_physicsObject.GetPosition();
	LMVector3 * targpos = m_target->GetPhysicsObject()->GetPosition();

	//maybe use pos->DisplacementMag(*targpos) here

	float x = abs(pos->x - targpos->x);
	float z = abs(pos->z - targpos->z);
	float displacementsq = x*x + z*z;

	float testsq = m_target->GetPhysicsObject()->GetRadius() + m_physicsObject.GetRadius();
	testsq = testsq*testsq;
	
	if (displacementsq <= testsq / 3.0f )
		return true;

	return false;
}

void BasicProjectile::OnEnterSeeking(VitalEntity * target)
{
	m_state = basicProjectileStateSeeking;
	SetTarget(target);
}

void BasicProjectile::SeekingBehavior(float deltaTime)
{
	//m_targetPosition = m_target->GetPhysicsObject()->GetPosition();

	//LMGeometryUnitVector((D3DXVECTOR3*)&m_tempDisplacement, (D3DXVECTOR3*)m_physicsObject.GetPosition(), (D3DXVECTOR3*)m_targetPosition);
	//replacement implementation for use of new class LMVector3
	
	m_tempDisplacement = *m_targetPosition;
	m_tempDisplacement -= *m_physicsObject.GetPosition();
	m_tempDisplacement.Normalize();

	m_physicsObject.GetPosition()->x += m_tempDisplacement.x * m_moveSpeed * deltaTime;
	//m_physicsObject->GetPosition()->y += m_tempDisplacement.y  * m_moveSpeed * deltaTime;
	m_physicsObject.GetPosition()->z += m_tempDisplacement.z * m_moveSpeed * deltaTime;
}

void BasicProjectile::OnExitSeeking()
{

}

void BasicProjectile::OnEnterExpended()
{
	m_state = basicProjectileStateExpended;
}

void BasicProjectile::ExpendedBehavior(float deltaTime)
{

}

void BasicProjectile::OnExitExpended()
{

}

BasicProjectileState BasicProjectile::GetState()
{
	return m_state;
}

VitalEntity * BasicProjectile::GetTarget()
{
	return m_target;
}

void BasicProjectile::SetTarget(VitalEntity * target)
{
	m_target = target;
	m_targetPosition = target->GetPhysicsObject()->GetPosition();
}
