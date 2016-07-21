#include "ElixirBurst.h"

ElixirBurst::ElixirBurst(Actor * owner) : DirectionalAbility(owner)
{
	OnEnterInactive();

	m_targetGroup = abilityTargetTeam;

	m_range = 6.0f;
	m_name = "Elixir Burst";
	m_defaultCooldown = 5.0f;
	m_castType = abilityCastTypeDirectionalCast;
	m_cooldownExpires = 0.0f;
	m_castTime = 0.0f;
	m_timeActive = 0.0f;
	m_maximumLife = 0.0f;
	m_damageType = damageTypeCatVoodoo;
	m_appType = heaSingle;

	m_ballSpeed = 8.0f;

	m_ball = Sprite(
		LMVector3(0.0f, 2.0f, 0.0f),
		LMVector3(0.0f, 0.0f, 0.0f),
		LMVector3(0.2f, 0.2f, 0.2f),
		LMVector3(0.0f, 0.0f, 0.0f),
		LMVector3(0.0f, 0.0f, 0.0f),
		LMVector3(0.0f, 0.0f, 0.0f),
		0.0f);
}


ElixirBurst::~ElixirBurst()
{
}

void ElixirBurst::OnEnterActive(float currentGameTime)
{
	m_state = abilityActive;
	m_castTime = currentGameTime;

	m_timeActive = 0.0f;
	m_maximumLife = 5.0f;

	SetDamageValuesOnActivation();

	//m_maximumLife = m_range / m_ballSpeed;

	m_pos = m_ball.GetPhysicsObject()->GetPosition();


	m_startPos = LMVector3(m_owner->GetPhysicsObject()->GetPosition()->x, 2.0f, m_owner->GetPhysicsObject()->GetPosition()->z);
	*m_pos = m_startPos;

	m_endPos = m_indicatorDirection;
	m_endPos.Normalize();
	m_endPos *= m_range;
	m_endPos += m_startPos;

	m_newScale = LMVector3(0.2f,0.2f,0.2f);
	m_ball.GetPhysicsObject()->SetScale(m_newScale);

	m_ishealingAdded = false;

}

void ElixirBurst::Active(float deltaTime)
{

	m_pos = m_ball.GetPhysicsObject()->GetPosition();

	if (m_pos->DisplacementMag(m_startPos) > m_range)
	{
		if (!m_ishealingAdded)
		{
			m_ishealingAdded = true;

			m_ball.GetPhysicsObject()->GetPosition()->x = m_endPos.x;
			m_ball.GetPhysicsObject()->GetPosition()->y = 2.0f;
			m_ball.GetPhysicsObject()->GetPosition()->z = m_endPos.z;

			m_actorsInRange.resize(0);

			GetActorsInRange(&m_actorsInRange, m_playerTeam, m_pos, m_range);

			for (unsigned int i = 0; i < m_actorsInRange.size(); i++)
			{
				//30% of missing HP to be added as heal object.
				float healValue = 0.3f * (m_actorsInRange.at(i)->GetStats()->m_maxHealth - m_actorsInRange.at(i)->GetStats()->m_health);

				AddHealing(healValue, m_owner, m_actorsInRange.at(i), 5.0f, 0.0f, heaOverTime);
			}
		}
		

		//OnExitActive();
		//OnEnterInactive();
		//return;
	}
	else
	{
		if (!m_ishealingAdded)
		{
			m_ball.GetPhysicsObject()->GetVelocity()->x = m_indicatorDirection.x * m_ballSpeed;
			m_ball.GetPhysicsObject()->GetVelocity()->y = m_indicatorDirection.y * m_ballSpeed;
			m_ball.GetPhysicsObject()->GetVelocity()->z = m_indicatorDirection.z * m_ballSpeed;

			m_ball.GetPhysicsObject()->Update(deltaTime);
		}
	}
	
	if (m_ishealingAdded)
	{
		m_newScale = *m_ball.GetPhysicsObject()->GetScale();
		m_newScale *= (1.0f + 0.8f*deltaTime);

		m_ball.GetPhysicsObject()->SetScale(m_newScale);
		m_ball.GetPhysicsObject()->SetRotation(LMVector3(rand()*2.0f, rand()*2.0f, rand()*2.0f));
	}


	UpdateLifeTimer(deltaTime);
}

void ElixirBurst::OnExitActive()
{
}

void ElixirBurst::OnEnterInactive()
{
	m_state = abilityInactive;
}

void ElixirBurst::Inactive(float DeltaTime)
{
}

void ElixirBurst::OnExitInactive()
{
}

Sprite * ElixirBurst::GetBall() { return &m_ball; }