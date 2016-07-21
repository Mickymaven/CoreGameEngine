
#include "DeathEvent.h"
DeathEvent::DeathEvent(VitalEntity * victim, DamageOriginType finalBlowType, VitalEntity * finalBlowOrigin)
{
	m_victim = victim;
	m_finalBlowType = finalBlowType;
	m_finalBlowOrigin = finalBlowOrigin;
}

DeathEvent::~DeathEvent()
{

}

void DeathEvent::AddAssist(VitalEntity * assistant)
{
	if (assistant != NULL) m_assists.push_back(assistant);
}

void DeathEvent::AddDamage(Damage * damage)
{
	if (damage !=NULL) m_damageContributions.push_back(damage);
}

VitalEntity * DeathEvent::GetVictim()
{
	return m_victim;
}

vector<VitalEntity * > * DeathEvent::GetAssists()
{
	return &m_assists;
}

vector<Damage * > * DeathEvent::GetDamageContributions()
{
	return &m_damageContributions;
}

VitalEntity * DeathEvent::GetFinalBlowOrigin()
{
	return m_finalBlowOrigin;
}

DamageOriginType * DeathEvent::GetFinalBlowType()
{
	return &m_finalBlowType;
}