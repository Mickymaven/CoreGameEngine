#if !defined (ELIXIRBURST_H)
#define ELIXIRBURST_H


#include "../../../../EngineMoba/src/Ability/DirectionalAbility.h"
#include "../../../../EngineGameModel/src/Base/Sprite.h"
#include "AbilityIncludes.h"

class ElixirBurst : public DirectionalAbility
{
private:
	Sprite m_ball;
	float m_ballSpeed;

	LMVector3 * m_enemypos;
	LMVector3 * m_pos;
	VitalEntity * m_newTarget;

	LMVector3 m_startPos;
	LMVector3 m_endPos;

	LMVector3 m_newScale;

	vector<Actor*> m_actorsInRange;

	bool m_ishealingAdded;

public:

public:
	ElixirBurst(Actor * owner);
	~ElixirBurst();

	void OnEnterActive(float currentGameTime);
	void Active(float deltaTime);
	void OnExitActive();

	void OnEnterInactive();
	void Inactive(float DeltaTime);
	void OnExitInactive();

	Sprite * GetBall();
};

#endif