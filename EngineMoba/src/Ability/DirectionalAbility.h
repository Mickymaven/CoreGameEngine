#if !defined(DIRECTIONALABILITY_H)
#define DIRECTIONALABILITY_H

#include "Ability.h"

class DirectionalAbility : public Ability
{
private:
protected:
	LMVector3 m_indicatorDirection;

public:
	DirectionalAbility();
	DirectionalAbility(Actor * owner);
	~DirectionalAbility();


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