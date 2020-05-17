#if !defined(HEALLASER_H)
#define HEALLASER_H

#include "../../../../EngineGameModel/src/Base/Sprite.h"
#include "../../../../EngineGameModel/src/maths/LMVector3.h"

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
	Actor m_target;

public:
	HealLaser();
	~HealLaser();

	void SetTargetAndActivate(Actor target);

	void Update(float deltaTime);

	void OnEnterInactive();
	void OnExitInactive();

	void OnEnterActive();
	void OnExitActive();


	HealLaserState GetState();
private:
	void ExitCurrentState();


};

#endif