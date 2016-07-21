#include "HealthEffect.h"

HealthEffect::HealthEffect()
{
}

HealthEffect::~HealthEffect()
{
}

float HealthEffect::UpdateReturningHealthPortion(float deltaTime)
{
	if (m_state == heActive)
	{
		//update timer
		m_timer += deltaTime;

		//calc what damage to return;
		switch (m_appType)
		{
			case heaSingle: ////////////////////////////////////////////////////
			{
				m_state = heInactive;
				return m_value;
				//state should end here
			} break;

			case heaOverTime:///////////////////////////////////////////////////
			{
				float damagePortion = 0.0f;

				//update at end where damage might be losee /////////////
				if (m_timer >= m_duration)
				{
					damagePortion = m_valueCounter;
					m_state = heInactive;
				}

				//update at the end where damage might be more ///////////
				else if (damagePortion >= m_valueCounter)
				{
					damagePortion = m_value;
					m_state = heInactive;
				}

				else //middle update /////////////////////
				{
					damagePortion = m_value * deltaTime  * (1.0f / m_duration);
				}
				/////////////////////////////////////////////

				if (m_duration > 0)
				{
					m_valueCounter -= damagePortion;
					return damagePortion;
				}
			} break;
		}


	}//end if (active)

	else if (m_state == heInactive) //a bit redundant
	{
		return 0.0f;
	}

	return 0.0f;//should not reach
}

void HealthEffect::MakeInactive(float gameTime)
{
	m_state = heInactive;
	m_inactiveTime = gameTime;
}

void HealthEffect::CountedTowardsScores()
{
	m_state = heCountedTowardsScores;
}

//Access
HealthEffectState HealthEffect::GetState() { return m_state; }
HealthEffectApplicationType HealthEffect::GetDamageApplicationType() { return m_appType; }

float HealthEffect::GetDuration() { return m_duration; }
float HealthEffect::GetTimer() { return m_timer; }
float HealthEffect::GetValue() { return m_value; }

VitalEntity * HealthEffect::GetOwner() { return m_owner; }
void * HealthEffect::GetAbilitySource() { return m_abilitySource; }
VitalEntity * HealthEffect::GetTarget() { return m_target; }

float HealthEffect::GetInactiveTime() { return m_inactiveTime; }

//Mutate

void HealthEffect::SetInactiveTime(float gameTime) { m_inactiveTime = gameTime; }