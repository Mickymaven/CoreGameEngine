#include "Ability.h"

Ability::Ability(){}

Ability::Ability(Actor * owner)
{
	//OnEnterInactive();
	//m_state = abilityInactive;


	m_targetGroup = abilityTargetOpponents;


	m_owner = owner;
	m_name = "";

	m_opponentTeam = NULL;
	m_playerTeam = NULL;

	m_range = 0.0f;
	m_cooldownExpires = 0.0f;
	m_defaultCooldown = 0.0f;

	m_castTime = 0.0f;
	m_timeActive = 0.0f;
	m_maximumLife = 0.0f;

	m_tempTime = 0.0f;

	m_tempBuff = nullptr;

	m_ownerPhysicalDamageOnCast = 0.0f;
	m_ownerCatVoodooOnCast = 0.0f;

	m_physicalDamageApplied = 0.0f;
	m_catVoodooApplied = 0.0f;
}

Ability::~Ability()
{
	for (unsigned int i = 0; i < m_damageOnUpdate.size(); i++)
	{
		if (m_damageOnUpdate.at(i) != NULL)
		{
			delete m_damageOnUpdate.at(i);
			m_damageOnUpdate.at(i)=nullptr;
		}
	}
}

void Ability::Update(float deltaTime)
{
	switch (Ability::m_state)
	{
	case abilityInactive:Inactive(deltaTime); break;
	case abilityActive:Active(deltaTime); break;
	}
}

void Ability::UpdateLifeTimer(float deltaTime)
{
	m_timeActive += deltaTime;

	bool isTimeUp = m_timeActive >= m_maximumLife;
	
	//only if time was up do we give ability option to not make inactive
	//by implementing InactiveConditions 

	if (isTimeUp) isTimeUp = InactiveConditions(deltaTime, isTimeUp);

	if (isTimeUp)
	{
		ExitCurrentState();
		OnEnterInactive();
	}
}

bool Ability::InactiveConditions(float deltaTime, bool isTimeUp)
{
	// derive from this in your ability to add extra conditions to 
	// making you ability inactive when its lifespan timer expires.
	return true;
}

void Ability::TargetEliminated()
{
	ExitCurrentState();
	OnEnterInactive();
}

/*
void Ability::OnEnterActive(float currentGameTime) {}
void Ability::Active(float deltaTime) {}
void Ability::OnExitActive() {}

void Ability::OnEnterInactive() {}
void Ability::Inactive(float deltaTime) {}
void Ability::OnExitInactive() {}
*/

void Ability::ExitCurrentState()
{
	switch (m_state)
	{
	case abilityActive: OnExitActive();
	case abilityInactive: OnExitInactive();
	}
}

/*
//pure virtual

AbilityResult virtual Ability::CanActivate(
	float gameTime,
	LMVector3 * m_indicatorDirectionVector,
	LMVector3 * mousePositionVector,
	Actor * target,
	vector<Actor *> * playerTeam,
	vector<Actor *> * opponentTeam,
	vector<Actor *> * neutralTeam) = 0;

AbilityResult Ability::Activate(
	float gameTime,
	LMVector3 * m_indicatorDirectionVector,
	LMVector3 * mousePositionVector,
	Actor * target,
	vector<Actor *> * playerTeam,
	vector<Actor *> * opponentTeam,
	vector<Actor *> * neutralTeam)
{
	MessageBox(NULL, "NONONONONON do not want NNONONO", "Ability base class activate", MB_OK);
	return abilityResultOK;
}
*/

Actor * Ability::ClosestTargetInRange(LMVector3 * position, float radius, NeutralCategoryState checkneutral)
{
	Actor * target = NULL;
	LMVector3 * targetPosition = NULL;
	float a;
	float b;
	float hitDist;
	float hypoSquared;
	float closestDistSquared = 9999999.9f;

	vector<Actor*> * team = NULL;

	for (unsigned int vCount = 0; vCount <= 1; vCount++)
	{
		//hard coded way to iterated over two seperate vectors
		//opponents then npcs, break on testnpcs parameter is false

		if (vCount == 0) team = m_opponentTeam;
		else if (vCount == 1)
		{
			if (checkneutral == neutralCategoryAll) team = m_neutralTeam;
			else break;
		}

		if (team == NULL) continue;
		
		// test selected team vector

		for (unsigned int i = 0; i < team->size(); i++)
		{
			if (team->at(i)->GetVitalEntityState() == vitalEntityStateActive)
			{
				hitDist = radius + team->at(i)->GetPhysicsObject()->GetRadius();

				targetPosition = team->at(i)->GetPhysicsObject()->GetPosition();
				a = abs(position->x - targetPosition->x);
				b = abs(position->z - targetPosition->z);
				hypoSquared = (a*a + b*b);
				if (hypoSquared < hitDist*hitDist)
				{
					if (hypoSquared < closestDistSquared)
					{
						closestDistSquared = hypoSquared;
						target = team->at(i);//missed that one :/
					}
				}
			}
		}
	}

	return target;
}

void Ability::GetActorsInRange(vector<Actor*>* actorsInRange, vector<Actor*>* actorsIn, LMVector3 * position, float radius)
{
	LMVector3 * targetPosition;
	float hitDist, a, b, hypoSquared;

	for (unsigned int i = 0; i < actorsIn->size(); i++)
	{
		if (actorsIn->at(i)->GetVitalEntityState() != vitalEntityStateInactive)
		{
			hitDist = radius + actorsIn->at(i)->GetPhysicsObject()->GetRadius();

			targetPosition = actorsIn->at(i)->GetPhysicsObject()->GetPosition();
			a = abs(position->x - targetPosition->x);
			b = abs(position->z - targetPosition->z);
			hypoSquared = (a*a + b*b);
			if (hypoSquared < hitDist*hitDist)
			{
				actorsInRange->push_back(actorsIn->at(i));
			}
		}
	}
}

void Ability::CreateBuff(Actor * target, BuffType buffType, int buffName, float duration)
{
	m_tempBuff = target->CreateBuff(buffType, buffName, duration);
}


bool Ability::IsTargetableOpponentOrTeam(Actor * target)
{
	if (target->GetVitalEntityState() == vitalEntityStateIntargetable && target->GetTeam() != m_owner->GetTeam()) return false;

	return true;
}

bool Ability::OffCooldown(float gameTime)
{
	return (GetCooldownRemaining(gameTime) < 0.001f);
}

void Ability::ApplyCooldown(float gameTime)
{
	if (m_cooldownExpires <= gameTime)
	{
		m_cooldownExpires = gameTime + m_defaultCooldown;
	}
}

float Ability::GetCooldownRemaining(float currentGameTime)
{
	m_tempTime = m_cooldownExpires - currentGameTime;
	
	if (m_tempTime < 0.0f) return 0.0f;

	return m_tempTime;
}




void Ability::SetDamageValuesOnActivation()
{
	m_ownerPhysicalDamageOnCast = m_owner->GetStats()->GetPhysicalDamage();
	m_ownerCatVoodooOnCast = m_owner->GetStats()->GetCatVoodoo();
}

void Ability::AddDamage(float damageValue, DamageType damageType, VitalEntity * owner, VitalEntity * target, float duration, float timer, HealthEffectApplicationType appType)
{
	Damage * newDamage = new Damage();

	newDamage->Init(
		duration, //float duration,
		timer, //float timer,
		damageValue, //float damageValue,
		damageType, //DamageType damageType,
		appType, //DamageApplicationType damageApplicationType,
		owner,//VitalEntity * owner,
		this,//void * abilitySource,
		target//VitalEntity * target)
		);

	m_damageOnUpdate.push_back(newDamage);
}


void Ability::AddHealing(float healValue, VitalEntity * owner, VitalEntity * target, float duration, float timer, HealthEffectApplicationType appType)
{
	Healing * newHealing = new Healing();

	newHealing->Init(
		duration, //float duration,
		timer, //float timer,
		healValue, //float damageValue,
		appType, //DamageApplicationType damageApplicationType,
		owner,//VitalEntity * owner,
		this,//void * abilitySource,
		target//VitalEntity * target)
		);

	m_healingOnUpdate.push_back(newHealing);
}

//Accessors
AbilityState Ability::GetState() { return m_state; }
AbilityCastType Ability::GetCastType() { return m_castType; }
AbilityTargetGroup Ability::GetTargetGroup() { return m_targetGroup; }
HealthEffectApplicationType Ability::GetHealthEffectApplicationType() { return m_appType; };
float Ability::GetRange() { return m_range; }
string * Ability::GetName() { return &m_name; }
float Ability::GetCooldown() { return m_defaultCooldown; }
vector<Damage *> * Ability::GetDamageOnUpdate() { return &m_damageOnUpdate; }
vector<Healing *> * Ability::GetHealingOnUpdate() { return &m_healingOnUpdate; }

//Mutators
void Ability::SetDamageApplied(float damage, DamageType damageType)
{
	switch (damageType)
	{
	case damageTypeDamage: m_physicalDamageApplied = damage; break;
	case damageTypeCatVoodoo: m_catVoodooApplied = damage; break;
	default: break;
	};
}
void Ability::SetOwner(Actor * owner) { m_owner = owner; }

void Ability::SetTeams(vector<Actor *> * playerTeam, vector<Actor *> * opponentTeam, vector<Actor *> * neutralTeam)
{
	m_playerTeam = playerTeam;
	m_opponentTeam = opponentTeam;
	m_neutralTeam = neutralTeam;
}

