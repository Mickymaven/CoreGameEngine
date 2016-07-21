#if !defined(SINGLETARGETABILITY_H)
#define SINGLETARGETABILITY_H

#include "Ability.h"

class SingleTargetAbility : public Ability
{
private:
protected:
	VitalEntityType m_SingleTargetType;

	Actor * m_singleTarget;
	VitalEntity * m_singleVitalEntityTarget;

public:
	SingleTargetAbility();
	SingleTargetAbility(Actor * owner);
	~SingleTargetAbility();

	bool SingleTargetInRange(VitalEntity * target);
	bool TargetOnTargetTeam(Actor * target);

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
		vector<Actor *> * neutralTeam) override;

	AbilityResult virtual Activate(
		float gameTime,
		LMVector3 * indicatorDirectionVector,
		LMVector3 * mousePositionVector,
		VitalEntity * target,
		vector<Actor *> * playerTeam,
		vector<Actor *> * opponentTeam,
		vector<Actor *> * neutralTeam);
};

#endif