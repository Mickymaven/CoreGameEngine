#include "PointAbility.h"

PointAbility::PointAbility() {}
PointAbility::PointAbility(Actor * owner) : Ability(owner) {}
PointAbility::~PointAbility() {}



bool PointAbility::PointCastInRange(LMVector3 * mousePosition)
{
	LMVector3 * pos = (LMVector3*)m_owner->GetPhysicsObject()->GetPosition();
	float x = mousePosition->x - pos->x;
	float z = mousePosition->z - pos->z;

	float length = sqrt(abs(x*x) + abs(z*z));

	if (length <= m_range) return true;

	OutputDebugString("Not in range (PointCastInRange)\n");

	return false;
}

AbilityResult PointAbility::CanActivate(
	float gameTime,
	LMVector3 * indicatorDirectionVector,
	LMVector3 * mousePositionVector,
	Actor * target,
	vector<Actor*>* playerTeam,
	vector<Actor*>* opponentTeam,
	vector<Actor*>* neutralTeam)
{
	if (!OffCooldown(gameTime)) return abilityResultOnCooldown;
	if (!PointCastInRange((LMVector3*)mousePositionVector)) return abilityResultOutOfRange;

	return abilityResultOK;
}

AbilityResult PointAbility::Activate(
	float gameTime,
	LMVector3 * indicatorDirectionVector,
	LMVector3 * mousePositionVector,
	Actor * target,
	vector<Actor *> * playerTeam,
	vector<Actor *> * opponentTeam,
	vector<Actor *> * neutralTeam)
{
	AbilityResult result;

	if ((result = CanActivate(
		gameTime,
		indicatorDirectionVector,
		mousePositionVector,
		target,
		playerTeam,
		opponentTeam,
		neutralTeam)) != abilityResultOK) return result;

	m_castPoint = (LMVector3*)mousePositionVector;


	SetDamageValuesOnActivation();
	OnEnterActive(gameTime);

	ApplyCooldown(gameTime);
	return abilityResultOK;
}


