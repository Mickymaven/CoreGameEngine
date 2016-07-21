#if !defined (ANTIFIREBALL_H)
#define ANTIFIREBALL_H

#include "../../../../EngineMoba/src/Ability/SingleTargetAbility.h"
#include "../../../../EngineGameModel/src/Base/Sprite.h"
#include "AbilityIncludes.h"

class AntiFireball : public SingleTargetAbility
{
private:
	Sprite m_fireball;
	float m_moveSpeed;
	float m_fireBallRadius;

protected:
	LMVector3 m_direction; 
	LMVector3  m_tempDisplacement;

public:
	AntiFireball(Actor * owner);
	~AntiFireball();

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

	Sprite * GetFireball();
};

#endif