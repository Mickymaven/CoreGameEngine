#include "BasicAttack.h"



BasicAttack::BasicAttack() 
{

}

BasicAttack::BasicAttack(Actor * owner) : SingleTargetAbility(owner)
{
	m_attacksprites.resize(3);
	m_lastProjectileIndex = 2;
	m_state = abilityInactive;
	
	m_range = 5.0f; //initialised from our base stats, updated on stat changes from stats
	m_damageType = damageTypeDamage;//always physical damage
	m_castType = abilityCastTypeSingleTargetCast;// we ignore cast type in this instance as we dont test for it
	m_appType = heaSingle;//should probably be single
	m_defaultCooldown = 1.0f / m_owner->GetStats()->m_attackSpeed; //initialised from our base stats, updated on stat changes from stats
	m_cooldownExpires = 0.0f; //init as zero, gets set to whatever our timeGameElapsed is on Activate

	m_tempPos = NULL;
	tempOwnerPos = NULL;
	
	m_timer = LMTimer(m_defaultCooldown, false);
	//this stuff is a psuedo timer
	m_castTime = 0.0f;
	m_timeActive = 0.0f;
	m_maximumLife = 0.0f;

	m_velocity = 2.0f;//projectile moves at 10 metres/second

	m_attacksprites.at(0) = BasicProjectile(
		LMVector3(0.0f, 0.0f, 0.0f),
		LMVector3(0.0f, 0.0f, 0.0f),
		LMVector3(0.1f, 0.1f, 0.1f),
		LMVector3(0.0f, 0.0f, 0.0f),
		LMVector3(0.0f, 0.0f, 0.0f),
		LMVector3(0.0f, 0.0f, 0.0f),
		0.0f); //attack has a projectile to render;

	m_attacksprites.at(1) = BasicProjectile(
		LMVector3(0.0f, 0.0f, 0.0f),
		LMVector3(0.0f, 0.0f, 0.0f),
		LMVector3(0.1f, 0.1f, 0.1f),
		LMVector3(0.0f, 0.0f, 0.0f),
		LMVector3(0.0f, 0.0f, 0.0f),
		LMVector3(0.0f, 0.0f, 0.0f),
		0.0f); //attack has a projectile to render;

	m_attacksprites.at(2) = BasicProjectile(
		LMVector3(0.0f, 0.0f, 0.0f),
		LMVector3(0.0f, 0.0f, 0.0f),
		LMVector3(0.1f, 0.1f, 0.1f),
		LMVector3(0.0f, 0.0f, 0.0f),
		LMVector3(0.0f, 0.0f, 0.0f),
		LMVector3(0.0f, 0.0f, 0.0f),
		0.0f); //attack has a projectile to render;
}

BasicAttack::~BasicAttack()
{
}

void BasicAttack::Update(float deltaTime)
{
	//get and assign targets for battle states

	//check if dead targets make  attacks expended without doing damage.

	m_timer.Update(deltaTime);

	for (int i = 0; i <= 2; i++)
	{
		if (m_attacksprites.at(i).GetState() == basicProjectileStateSeeking)
		{
			m_attacksprites.at(i).Update(deltaTime);

			if (m_attacksprites.at(i).IsOverTarget())
			{
				m_attacksprites.at(i).OnEnterExpended();

				AddDamage(m_owner->GetStats()->m_physicalDamage,
					damageTypeDamage, m_owner, m_attacksprites.at(i).GetTarget(),
					0.25f, 0.1f, heaOverTime);

			}
		}
	}
}

AbilityResult BasicAttack::Activate(
		float gameTime,
		LMVector3 * indicatorDirectionVector,
		LMVector3 * mousePositionVector,
		VitalEntity * target,
		vector<Actor *> * playerTeam,
		vector<Actor *> * opponentTeam,
		vector<Actor *> * neutralTeam)
{
	//Overriding SingleTargetCast::Activate so we can do extra checks (dont do this often please).

	//if (!OffCooldown(gameTime)) return abilityResultOnCooldown;
	if (target == NULL) return abilityResultOutOfRange;
	//if (!SingleTargetInRange(target)) return abilityResultOutOfRange;

	//THE EXTRA CHECK ONLY FOR BASIC ATTACKs
	if (!IsNextBasicAvailable()) return abilityResultMaximumCountReached;
			//TODO if its possibel that use the abilility cooldown system for all this.

	m_singleVitalEntityTarget = target;

	SetDamageValuesOnActivation();
	OnEnterActive(gameTime);

	ApplyCooldown(gameTime);
	return abilityResultOK;
}

bool BasicAttack::IsNextBasicAvailable()
{
	if (m_timer.GetState() != timerStarted)
	{
		switch (m_lastProjectileIndex)
		{
		case 0:
			m_lastProjectileIndex = 1;
			break;
		case 1:
			m_lastProjectileIndex = 2;
			break;
		case 2:
			m_lastProjectileIndex = 0;
			break;
		default:
			MessageBox(NULL, "bad basic attack index. ", "Errrrr", MB_OK);
			break;
		}

		if (m_attacksprites.at(m_lastProjectileIndex).GetState() == basicProjectileStateExpended)
			return true;


	}

	return false;
}


void BasicAttack::OnEnterActive(float gameTime)
{
	m_state = abilityActive;

	m_timer.RestartWithDuration(1.0f / m_owner->GetStats()->m_attackSpeed, true);
	m_attacksprites.at(m_lastProjectileIndex).OnEnterSeeking(m_singleVitalEntityTarget);

	m_tempPos =
		m_attacksprites.at(m_lastProjectileIndex).GetPhysicsObject()->GetPosition();

	tempOwnerPos =
		m_owner->GetPhysicsObject()->GetPosition();


	m_tempPos->x = tempOwnerPos->x;
	m_tempPos->y = 1.0f;
	m_tempPos->z = tempOwnerPos->z;
}

void BasicAttack::Active(float deltaTime)
{

}

void BasicAttack::OnExitActive()
{

}

void BasicAttack::OnEnterInactive()
{
	m_state = abilityInactive;
}

void BasicAttack::Inactive(float deltaTime)
{
	
}

void BasicAttack::OnExitInactive()
{

}

vector<BasicProjectile> * BasicAttack::GetProjectiles() { return &m_attacksprites; }