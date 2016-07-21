#include "NomBarHeal.h"

NomBarHeal::NomBarHeal(Actor * owner) : InstantAbility(owner)
{
	OnEnterInactive();

	m_range = 0.0f;
	m_name = "Nom Bar Heal";
	m_defaultCooldown = 15.0f;
	m_castType = abilityCastTypeInstantCast;
	m_cooldownExpires = 0.0f;
	m_castTime = 0.0f;
	m_timeActive = 0.0f;
	m_maximumLife = 0.0f;
	m_damageType = damageTypeCatVoodoo;
	m_appType = heaOverTime;

}

NomBarHeal::~NomBarHeal()
{

}

//state implementation
void NomBarHeal::OnEnterActive(float currentGameTime)
{
	m_state = abilityActive;

	m_castTime = currentGameTime;

	m_timeActive = 0.0f;
	m_maximumLife = 0.0f;//5 seconds of scary fear and stuff
	
	// OMNOM NOM BUFF ///
	CreateBuff(m_owner, buffBuff, buffOmNomNom, 10.0f);
	m_tempBuff->SetHPCurve(true, 100.0f);//100 hp via regen buff

	//buff->stat()->m_healthRegen = 7.5f;

}

void NomBarHeal::Active(float deltaTime)
{
	UpdateLifeTimer(deltaTime);
}

void NomBarHeal::OnExitActive()
{

}


void NomBarHeal::OnEnterInactive()
{
	m_state = abilityInactive;
}

void NomBarHeal::Inactive(float deltaTime)
{

}
void NomBarHeal::OnExitInactive()
{

}
