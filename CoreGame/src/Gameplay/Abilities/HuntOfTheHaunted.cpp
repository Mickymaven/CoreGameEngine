#include "HuntOfTheHaunted.h"

HuntOfTheHaunted::HuntOfTheHaunted(Actor * owner) : InstantAbility(owner)
{
	OnEnterInactive();
	
	m_range = 15.0f;
	m_name = "Hunt of the Haunted";
	m_defaultCooldown = 5.0f;
	m_castType = abilityCastTypeInstantCast;
	m_cooldownExpires = 0.0f;
	m_castTime = 0.0f;
	m_timeActive = 0.0f;
	m_maximumLife = 0.0f;
	m_damageType = damageTypeCatVoodoo;
	m_appType = heaOverTime;

	//m_allCreatures.resize(3);

	
	HauntedCreature * newCreature = NULL;
	for (int i = 0; i <= 2; i++)
	{
		newCreature = new HauntedCreature(
			LMVector3(0.0f, 1.0f, 0.0f),
			LMVector3(0.0f, 0.0f, 0.0f),
			LMVector3(0.2f, 0.2f, 0.2f),
			LMVector3(0.0f, 0.0f, 0.0f),
			LMVector3(0.0f, 0.0f, 0.0f),
			LMVector3(0.0f, 0.0f, 0.0f),
			0.0f,
			LMVector3(0.0f, 0.0f, 0.0f)
			);

		m_allCreatures.push_back(newCreature);
	}

}

HuntOfTheHaunted::~HuntOfTheHaunted()
{

}
void HuntOfTheHaunted::OnEnterActive(float currentGameTime)
{
	m_state = abilityActive;
	m_castTime = currentGameTime;

	m_timeActive = 0.0f;
	m_maximumLife = 20.0f;//5 seconds of scary fear and stuff


	LMVector3 * pos = m_owner->GetPhysicsObject()->GetPosition();

	for (unsigned int i = 0; i < m_allCreatures.size(); i++)
	{
		
		m_allCreatures.at(i)->GetPhysicsObject()->GetPosition()->x = pos->x;
		//m_allCreatures.at(i)->GetPhysicsObject()->GetPosition()->y = 0.0f;
		m_allCreatures.at(i)->GetPhysicsObject()->GetPosition()->z = pos->z;
	}

	Actor * newtarget = ClosestTargetInRange(
		m_owner->GetPhysicsObject()->GetPosition(),
		50.0f,
		neutralCategoryAll);


	if (newtarget != NULL)
	{
		m_allCreatures.at(0)->OnEnterSpawning(0, newtarget);
		m_allCreatures.at(1)->OnEnterSpawning(1, newtarget);
		m_allCreatures.at(2)->OnEnterSpawning(2, newtarget);
		//OutputDebugString("\n Target found for Hunt of the Haunted \n");
	}
	else
	{
		//Boooooooooo
		OutputDebugString("\n No Target found for Hunt of the Haunted \n");
	}
}

void HuntOfTheHaunted::Active(float deltaTime)
{
	for (unsigned int i = 0; i < m_allCreatures.size(); i++)
	{
		m_allCreatures.at(i)->Update(deltaTime);

		if (m_allCreatures.at(i)->GetState() == hauntedCreatureStateSeek)
		{
			//if (i==0) OutputDebugString("SEEKING");

			if (m_allCreatures.at(i)->IsOverTarget())
			{
				AddDamage(1.0f * m_owner->GetStats()->m_catVoodoo, m_damageType,
					m_owner, (Actor*)m_allCreatures.at(i)->GetTarget(),
					0.5f, 0.0f, m_appType);

				m_allCreatures.at(i)->OnEnterDone();
			}
		}
	}

	UpdateLifeTimer(deltaTime);
}

void HuntOfTheHaunted::OnExitActive()
{

}


void HuntOfTheHaunted::OnEnterInactive()
{
	m_state = abilityInactive;
}

void HuntOfTheHaunted::Inactive(float deltaTime)
{

}
void HuntOfTheHaunted::OnExitInactive()
{

}

vector <HauntedCreature *> * HuntOfTheHaunted::GetCreatures() { return &m_allCreatures; }