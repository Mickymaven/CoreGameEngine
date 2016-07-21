#include "Healing.h"

Healing::Healing()
{
	m_duration = 0.0f;
	m_timer = 0.0f;
	m_value = 0.0f;
	m_appType = heaTypeCount;
	m_owner = nullptr;
	m_target = nullptr;
	m_state = heActive;
	m_valueCounter = 0.0f;
	m_inactiveTime = 0.0f;
}

Healing::~Healing()
{
}

void Healing::Init(float duration, float timer, float damageValue, HealthEffectApplicationType damageApplicationType, VitalEntity * owner, void * abilitySource, VitalEntity * target)
{
	m_duration = duration;
	m_timer = timer;
	m_value = damageValue;
	m_valueCounter = m_value; //damage its to be subtracted each update in Damage Controller;
	m_appType = damageApplicationType;
	m_owner = owner;
	m_abilitySource = abilitySource;
	m_target = target;
}
