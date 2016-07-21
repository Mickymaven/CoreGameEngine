#if !defined(COSMICSPAGHETTI_H)
#define COSMICSPAGHETTI_H

#include "../../../../EngineMoba/src/Ability/DirectionalAbility.h"
#include "../../../../EngineGameModel/src/Base/Sprite.h"
#include "AbilityIncludes.h"



class CosmicSpaghetti : public DirectionalAbility
{

private:
	Sprite m_spaghettiball;
	float m_ballSpeed;

	LMVector3 * m_enemypos;
	LMVector3 * m_pos;
	VitalEntity * m_newTarget;
protected:

public:
	CosmicSpaghetti(Actor * owner);
	~CosmicSpaghetti();

	//void Update(float deltaTime);
	//void TargetEliminated();

protected:
	void OnEnterActive(float currentGameTime);
	void Active(float deltaTime);
	void OnExitActive();

	void OnEnterInactive();
	void Inactive(float DeltaTime);
	void OnExitInactive();
public:

	Sprite * GetSpaghettiBall();
};

#endif