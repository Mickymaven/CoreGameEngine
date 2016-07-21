#if !defined(THESLURPENING_H)
#define THESLURPENING_H

#include "../../../../EngineMoba/src/Ability/SingleTargetAbility.h"
#include "../../../../EngineGameModel/src/Base/Sprite.h"
#include "../../../../EngineGameModuleDirectX9/src/UI/UIElement.h"

#include "AbilityIncludes.h"
class TheSlurpening : public SingleTargetAbility
{
private:
	Sprite m_straw;

	PhysicsObject * ownerPhysics;
	PhysicsObject * strawPhysics;
	PhysicsObject * targetPhysics;

	LMVector3 m_direction;


public:
	TheSlurpening(Actor * owner);
	~TheSlurpening();

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
	Sprite * GetStraw();

};

#endif