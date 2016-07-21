#include "SingleTargetAbility.h"

SingleTargetAbility::SingleTargetAbility() {}
SingleTargetAbility::SingleTargetAbility(Actor * owner) : Ability(owner)
{
	m_singleTarget = NULL;
}

SingleTargetAbility::~SingleTargetAbility() {}

bool SingleTargetAbility::SingleTargetInRange(VitalEntity * target)
{
	LMVector3 * pos = (LMVector3 *)m_owner->GetPhysicsObject()->GetPosition();
	LMVector3 * targPos = (LMVector3 *)target->GetPhysicsObject()->GetPosition();
	float x = targPos->x - pos->x;
	float z = targPos->z - pos->z;
	
	//true if length sq <= range sq
	if (( abs(x*x) + abs(z*z)) <= m_range*m_range) return true;

	return false;
}

bool SingleTargetAbility::TargetOnTargetTeam(Actor * target)
{
	if (m_targetGroup == abilityTargetTeam)
	{
		if (target->GetTeam() == m_owner->GetTeam()) return true;
		else return false;
	}
	else if (m_targetGroup == abilityTargetOpponents)
	{
		if (target->GetTeam() != m_owner->GetTeam()) return true;
		return false;
	}

	return false;
}

AbilityResult SingleTargetAbility::CanActivate(float gameTime, LMVector3 * indicatorDirectionVector, LMVector3 * mousePositionVector, Actor * target, vector<Actor*>* playerTeam, vector<Actor*>* opponentTeam, vector<Actor*>* neutralTeam)
{
	if (!OffCooldown(gameTime)) return abilityResultOnCooldown;
	if (target == nullptr) return abilityResultRequiredTargetMissing;
	if (!TargetOnTargetTeam(target)) return abilityResultIntargetable;
	if (!IsTargetableOpponentOrTeam(target)) return abilityResultIntargetable;
	if (!SingleTargetInRange(target)) return abilityResultOutOfRange;

	return abilityResultOK;
}

AbilityResult SingleTargetAbility::Activate(
	float gameTime,
	LMVector3 * indicatorDirectionVector,
	LMVector3 * mousePositionVector,
	Actor * target,
	vector<Actor *> * playerTeam,
	vector<Actor *> * opponentTeam,
	vector<Actor *> * neutralTeam)
{
	//if you make changes to this make sure any overrides are updated.
	AbilityResult result;

	if ((result = CanActivate(
		gameTime,
		indicatorDirectionVector,
		mousePositionVector,
		target,
		playerTeam,
		opponentTeam,
		neutralTeam)) != abilityResultOK) return result;
	

	m_singleTarget = target;

	SetDamageValuesOnActivation();
	OnEnterActive(gameTime);

	ApplyCooldown(gameTime);
	return abilityResultOK;
}

AbilityResult SingleTargetAbility::Activate(
	float gameTime,
	LMVector3 * indicatorDirectionVector,
	LMVector3 * mousePositionVector,
	VitalEntity * target,
	vector<Actor *> * playerTeam,
	vector<Actor *> * opponentTeam,
	vector<Actor *> * neutralTeam)
{
	/*
	//if you make changes to this make sure any overrides are updated.

	if (!OffCooldown(gameTime)) return abilityResultOnCooldown;
	if (target == NULL) return abilityResultOutOfRange;
	if (!SingleTargetInRange(target)) return abilityResultOutOfRange;

	m_singleTarget = target;

	SetDamageValuesOnActivation();
	OnEnterActive(gameTime);

	ApplyCooldown(gameTime);
	return abilityResultOK;
	*/

	//this implementation is commented out beacuse we are only implementing this type of
	//init in basic attack

	return abilityResultOK;

}