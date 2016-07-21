#if !defined(POINTBILITY_H)
#define POINTABILITY_H

#include "Ability.h"

class PointAbility : public Ability
{
private:
protected:
	LMVector3 * m_castPoint;

public:
	PointAbility();
	PointAbility(Actor * owner);
	~PointAbility();

	bool PointCastInRange(LMVector3 * mousePosition);


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