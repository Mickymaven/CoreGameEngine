#include "HealLaser.h"

HealLaser::HealLaser()
{
	m_state = healLaserInactive;
}

HealLaser::~HealLaser()
{
}

void HealLaser::Update(float deltaTime)
{
	switch(m_state)
	{
	case healLaserActive:
		Active(deltaTime);
		break;
	case healLaserInactive:
		Inactive(deltaTime);
		break;
	default:break;
	}


}

bool HealLaser::SetTargetActivate(Actor * target)
{
	m_target = target;

	return false;
}

HealLaserState HealLaser::GetState()
{
	return m_state;
}

void HealLaser::OnEnterActive()
{
}

void HealLaser::Active(float deltaTime)
{

}


void HealLaser::OnExitActive()
{
}

void HealLaser::OnEnterInactive()
{
}

void HealLaser::Inactive(float deltaTime)
{
}

void Inactive(float deltaTime)
{

}

void HealLaser::OnExitInactive()
{
}

void HealLaser::ExitCurrentState()
{
}

