#include "InstantAbility.h"

InstantAbility::InstantAbility() {}
InstantAbility::InstantAbility(Actor * owner) : Ability(owner) {}
InstantAbility::~InstantAbility() {}



AbilityResult InstantAbility::CanActivate(float gameTime, LMVector3 * indicatorDirectionVector, LMVector3 * mousePositionVector, Actor * target, vector<Actor*>* playerTeam, vector<Actor*>* opponentTeam, vector<Actor*>* neutralTeam)
{
	if (!OffCooldown(gameTime)) return abilityResultOnCooldown;

	return abilityResultOK;
}

AbilityResult InstantAbility::Activate(
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

	SetDamageValuesOnActivation();
	SetTeams(playerTeam, opponentTeam, neutralTeam);
	OnEnterActive(gameTime);

	ApplyCooldown(gameTime);

	return abilityResultOK;
}