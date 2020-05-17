#if !defined (HEALLASER_H)
#define HEALLASER_H

#include "../../../../EngineGameModel/src/Base/Sprite.h"
#include "../../../../EngineGameModel/src/Maths/LMVector3.h"
#include "../../../../EngineMoba/src/Actors/Actor.h"

enum HealLaserState
{
	healLaserInactive,
	healLaserActive,
	healLaserStateCount
};

class HealLaser
{
private:
	HealLaserState m_state;
	LMVector3 m_difference;
	Sprite m_laser;
	Actor * m_target;
public:
	HealLaser();
	~HealLaser();

	void Update(float deltaTime);

	bool SetTargetActivate(Actor * target);

	HealLaserState GetState();

private:
	void OnEnterActive();
	void Active(float deltaTime);
	void OnExitActive();


	void OnEnterInactive();
	void Inactive(float deltaTime);
	void OnExitInactive();

	void ExitCurrentState();




};

#endif