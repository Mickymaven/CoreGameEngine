#if !defined(INSTANTABILITY_H)
#define INSTANTABILITY_H

#include "Ability.h"

class InstantAbility : public Ability
{
private:

public:
	InstantAbility();
	InstantAbility(Actor * owner);
	~InstantAbility();



public:
	AbilityResult CanActivate(
		float gameTime,
		LMVector3 * indicatorDirectionVector,
		LMVector3 * mousePositionVector,
		Actor * target,
		vector<Actor *> * playerTeam,
		vector<Actor *> * opponentTeam,
		vector<Actor *> * neutralTeam) override;

	AbilityResult Activate(
		float gameTime,
		LMVector3 * indicatorDirectionVector,
		LMVector3 * mousePositionVector,
		Actor * target,
		vector<Actor *> * playerTeam,
		vector<Actor *> * opponentTeam,
		vector<Actor *> * neutralTeam);
};

#endif