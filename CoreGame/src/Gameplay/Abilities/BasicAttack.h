#if !defined(BASICATTACK_H)
#define BASICATTACK_H

#include <vector>
using std::vector;

#include "../../../../EngineMoba/src/Actors/VitalEntity.h"
#include "../../../../EngineMoba/src/Actors/Actor.h"
#include "../../../../EngineGameModel/src/Utility/LMTimer.h"
#include "../../../../EngineGameModel/src/Maths/LMVector3.h"
#include "../../../../EngineGameModel/src/Base/Sprite.h"
#include "AbilityIncludes.h"
#include "BasicProjectile.h"

#include "../../../../EngineMoba/src/Ability/SingleTargetAbility.h"

class BasicAttack : public SingleTargetAbility
{

private:
	vector<BasicProjectile> m_attacksprites;//size will be 3

	int m_lastProjectileIndex;
	float m_velocity;

	LMTimer m_timer;

	LMVector3 * m_tempPos;
	LMVector3 * tempOwnerPos;

public:
	BasicAttack();
	BasicAttack(Actor * owner);
	~BasicAttack();

	AbilityResult BasicAttack::Activate(
		float gameTime,
		LMVector3 * indicatorDirectionVector,
		LMVector3 * mousePositionVector,
		VitalEntity * target,
		vector<Actor *> * playerTeam,
		vector<Actor *> * opponentTeam,
		vector<Actor *> * neutralTeam);

	void Update(float deltaTime);
	//void TargetEliminated();
	bool IsNextBasicAvailable();

protected:
	void OnEnterActive(float currentGameTime);
	void Active(float deltaTime);
	void OnExitActive();

	void OnEnterInactive();
	void Inactive(float DeltaTime);
	void OnExitInactive();
public:
	
	vector<BasicProjectile> * GetProjectiles();
};

#endif
