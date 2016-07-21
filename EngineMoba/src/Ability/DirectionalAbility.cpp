#include "DirectionalAbility.h"

DirectionalAbility::DirectionalAbility(){}
DirectionalAbility::DirectionalAbility(Actor * owner) : Ability(owner) {}
DirectionalAbility::~DirectionalAbility(){}


AbilityResult DirectionalAbility::CanActivate(float gameTime, LMVector3 * indicatorDirectionVector, LMVector3 * mousePositionVector, Actor * target, vector<Actor*>* playerTeam, vector<Actor*>* opponentTeam, vector<Actor*>* neutralTeam)
{
	if (!OffCooldown(gameTime)) return abilityResultOnCooldown;

	return abilityResultOK;
}

AbilityResult DirectionalAbility::Activate(
	float gameTime,
	LMVector3 * indicatorDirectionVector,
	LMVector3 * mousePositionVector,
	Actor * target,
	vector<Actor *> * playerTeam,
	vector<Actor *> * opponentTeam,
	vector<Actor *> * neutralTeam)
{
	AbilityResult result;
	if ( (result = CanActivate(
		gameTime,
		indicatorDirectionVector,
		mousePositionVector,
		target,
		playerTeam,
		opponentTeam,
		neutralTeam)) != abilityResultOK) return result;

	m_indicatorDirection = LMVector3(*(LMVector3*)indicatorDirectionVector);

	SetDamageValuesOnActivation();
	OnEnterActive(gameTime);

	ApplyCooldown(gameTime);
	return abilityResultOK;
}

