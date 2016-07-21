#include "Damage.h"

Damage::Damage()
{
	m_damageType = damageTypeCount;
}

Damage::~Damage() {}

void Damage::Init(
	float duration,
	float timer,
	float damageValue,
	DamageType damageType,
	HealthEffectApplicationType damageApplicationType,
	VitalEntity * owner,
	void * abilitySource,
	VitalEntity * target)
{
	m_duration = duration;
	m_timer = timer;
	m_value = damageValue;
	m_valueCounter = m_value; //damage its to be subtracted each update in Damage Controller;
	m_damageType = damageType;
	m_appType = damageApplicationType;
	m_owner = owner;
	m_abilitySource = abilitySource;
	m_target = target;
}

//Access
DamageType Damage::GetDamageType() { return m_damageType; }