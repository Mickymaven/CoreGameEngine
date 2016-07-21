#include "BudgetMenuBeverage.h"


BudgetMenuBeverage::BudgetMenuBeverage() {}


BudgetMenuBeverage::BudgetMenuBeverage(Actor * owner) : InstantAbility(owner)
{
	OnEnterInactive();

	m_range = 0.0f;
	m_name = "Budget Menu Beverage";
	m_defaultCooldown = 15.0f;
	m_castType = abilityCastTypeInstantCast;
	m_cooldownExpires = 0.0f;
	m_castTime = 0.0f;
	m_timeActive = 0.0f;
	m_maximumLife = 0.0f;
	m_damageType = damageTypeCatVoodoo;
	m_appType = heaOverTime;

}

BudgetMenuBeverage::~BudgetMenuBeverage()
{

}

void BudgetMenuBeverage::OnEnterActive(float currentGameTime)
{
	m_state = abilityActive;

	m_castTime = currentGameTime;

	m_timeActive = 0.0f;
	m_maximumLife = 0.0f;//5 seconds of scary fear and stuff


	// BUFF buffIncapacitedBySauce ///////////
	CreateBuff(m_owner, buffBuff, buffIncapacitedBySauce, 10.0f);

	m_tempBuff->SetHPCurve(true, 100.0f);//100 hp via regen buff

	m_tempBuff->stat()->m_catVoodoo = 100.0f;
	m_tempBuff->stat()->m_healthRegen = 7.5f;
	m_tempBuff->stat()->m_attackSpeed = -0.2f * m_owner->GetStats()->m_attackSpeed;
	m_tempBuff->stat()->m_moveSpeed = -0.2f * m_owner->GetStats()->m_moveSpeed;
	//////////////////////////////////////////

}

void BudgetMenuBeverage::Active(float deltaTime)
{

}

void BudgetMenuBeverage::OnExitActive()
{

}

void BudgetMenuBeverage::OnEnterInactive()
{
	m_state = abilityInactive;
}

void BudgetMenuBeverage::Inactive(float deltaTime)
{

}
void BudgetMenuBeverage::OnExitInactive()
{

}