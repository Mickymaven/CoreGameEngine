#if !defined(VALIANTLEAP_H)
#define VALIANTLEAP_H

#include "../../../../EngineMoba/src/Ability/DirectionalAbility.h"
#include "../../../../EngineGameModel/src/Base/Sprite.h"
#include "AbilityIncludes.h"

enum ValiantLeapState
{
	valiantLeapJumpState,
	valiantLeapShotCastState,
	valiantLeapShotAnimState,
	valiantLeapLeapInactive
};

class ValiantLeap : public DirectionalAbility
{
private:
	Sprite m_leapShot;

	ValiantLeapState m_valiantLeapState;

	//Character Movement
	LMVector3 * m_actorPosition;

	LMVector3 m_displacementThisUpdate;


	float m_leapSpeed;
	LMVector3 m_leapDirection;
	LMVector3 m_leapTargetPosition;

	float m_leapTime;
	float m_leapMaxTime;

	float m_shotSpeed;
	LMVector3 m_shotDirection;
	LMVector3 m_shotTargetPosition;

	float m_shotTime;
	float m_shotMaxTime;

public:
	ValiantLeap(Actor * owner);
	~ValiantLeap();

	void OnEnterActive(float currentGameTime);
	void Active(float deltaTime);
	void OnExitActive();

	void OnEnterInactive();
	void Inactive(float DeltaTime);
	void OnExitInactive();

	//valiant leap

	void OnEnterJump();
	void Jump(float deltaTime);
	void OnExitJump();

	void OnEnterShotCast();
	void ShotCast(float deltaTime);
	void OnExitShotCast();

	void OnEnterShotAnim();
	void ShotAnim(float deltaTime);
	void OnExitShotAnim();

	void OnEnterLeapInactive();
	void LeapInactive(float deltaTime);
	void OnExitLeapInactive();

	void ExitCurrentValiantLeapState();

public:

	Sprite * GetLeapShot();

};

#endif