#if !defined(BASICPROJECTILE_H)
#define BASICPROJECTILE_H

#include "../../../../EngineGameModel/src/Base/Sprite.h"
#include "../../../../EngineMoba/src/Actors/VitalEntity.h"

enum BasicProjectileState
{
	basicProjectileStateSeeking,
	basicProjectileStateExpended,
	basicProjectileStateCount
};

class BasicProjectile : public Sprite
{

private:
	BasicProjectileState m_state;
	VitalEntity * m_target;
	LMVector3 * m_targetPosition;
	LMVector3 m_tempDisplacement;

public:
	static const float m_moveSpeed;

	BasicProjectile();
	BasicProjectile(
		LMVector3 position,
		LMVector3 rotation,
		LMVector3 scale,
		LMVector3 velocity,
		LMVector3 spin,
		LMVector3 resize,
		float acceleration);
	~BasicProjectile();

	void Update(float deltaTime);

	bool IsOverTarget();
	
	void OnEnterSeeking(VitalEntity * target);
	void SeekingBehavior(float deltaTime);
	void OnExitSeeking();

	void OnEnterExpended();
	void ExpendedBehavior(float deltaTime);
	void OnExitExpended();

	//Accessors
	BasicProjectileState  GetState();
	VitalEntity * GetTarget();
	
	//Mutators
	void SetTarget(VitalEntity * target);
};

#endif