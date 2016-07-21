#include "ValiantLeap.h"

ValiantLeap::ValiantLeap(Actor * owner) : DirectionalAbility(owner)
{
	OnEnterInactive();

	m_range = 5.0f;
	m_name = "Valiant Leep";
	m_defaultCooldown = 3.0f;
	m_castType = abilityCastTypeDirectionalCast;
	m_cooldownExpires = 0.0f;
	m_castTime = 0.0f;
	m_timeActive = 0.0f;
	m_maximumLife = 0.0f;
	m_damageType = damageTypeCatVoodoo;
	m_appType = heaOverTime;

	//derived class inits
	m_valiantLeapState = valiantLeapLeapInactive;

	m_actorPosition = owner->GetPhysicsObject()->GetPosition();

	m_leapSpeed = 15.0f;
	//LMVector3 m_leapDirection;
	//LMVector3 m_targetPosition;

	m_shotSpeed = 30.0f;
	//LMVector3 m_shotDirection;
	//LMVector3 m_shotTargetPosition;
}

ValiantLeap::~ValiantLeap()
{
}

void ValiantLeap::OnEnterActive(float currentGameTime)
{
	m_state = abilityActive;

	m_castTime = currentGameTime;

	ExitCurrentValiantLeapState();
	OnEnterJump();
}

void ValiantLeap::Active(float deltaTime)
{
	switch (m_valiantLeapState)
	{
	case valiantLeapJumpState: Jump(deltaTime); break;
	case valiantLeapShotCastState: ShotCast(deltaTime); break;
	case valiantLeapShotAnimState: ShotAnim(deltaTime); break;
	case valiantLeapLeapInactive: LeapInactive(deltaTime); break;
	}

	if (m_valiantLeapState == valiantLeapLeapInactive)
	{
		Ability::ExitCurrentState();
		OnEnterInactive();
	}
}

void ValiantLeap::OnExitActive()
{
}

void ValiantLeap::OnEnterInactive()
{
	m_state = abilityInactive;
}

void ValiantLeap::Inactive(float DeltaTime)
{
}

void ValiantLeap::OnExitInactive()
{
}

//valiantLeapJumpState;
//valiantLeapShotCastState;
//valiantLeapShotAnimState;
//valiantLeapLeapInactive;

void ValiantLeap::OnEnterJump()
{
	m_valiantLeapState = valiantLeapJumpState;

	LMVector3 startPos = *m_actorPosition;

	m_leapTargetPosition = startPos + (m_indicatorDirection*m_range);

	m_leapMaxTime = m_range / m_leapSpeed;
	m_leapTime = 0;

	m_timeActive = 0.0f;
	m_maximumLife = 15.0f;
}

void ValiantLeap::Jump(float deltaTime)
{
	m_leapTime += deltaTime;

	//once time of jump met, set player position to the jump target position exactly.
	if (m_leapTime > m_leapMaxTime)
	{
		*m_actorPosition = m_leapTargetPosition;
		
		//todo
		//OnExitJump();
		//OnEnterShotCast();
		
		//remove
		OnExitActive();
		OnEnterInactive();

		return;
	}
	
	//move player in jump direction
	m_displacementThisUpdate = m_indicatorDirection * (m_leapSpeed * deltaTime);

	*m_actorPosition += m_displacementThisUpdate;

	//todo we are going to let jump code flow into inactive then we obeserve that to make ability inactive
	//we wont then make inactive with hardcode time like updtaelifetimer() does.
	UpdateLifeTimer(deltaTime);
}

void ValiantLeap::OnExitJump()
{
}

void ValiantLeap::OnEnterShotCast()
{
	m_valiantLeapState = valiantLeapShotCastState;
}

void ValiantLeap::ShotCast(float deltaTime)
{
}

void ValiantLeap::OnExitShotCast()
{
}

void ValiantLeap::OnEnterShotAnim()
{
	m_valiantLeapState = valiantLeapShotAnimState;
}

void ValiantLeap::ShotAnim(float deltaTime)
{
}

void ValiantLeap::OnExitShotAnim()
{

}

void ValiantLeap::OnEnterLeapInactive()
{
	m_valiantLeapState = valiantLeapLeapInactive;
}

void ValiantLeap::LeapInactive(float deltaTime)
{
}

void ValiantLeap::OnExitLeapInactive()
{
}

void ValiantLeap::ExitCurrentValiantLeapState()
{

	switch (m_valiantLeapState)
	{
	case valiantLeapJumpState: OnExitJump(); break;
	case valiantLeapShotCastState: OnExitShotCast(); break;
	case valiantLeapShotAnimState: OnExitShotAnim(); break;
	case valiantLeapLeapInactive: OnExitLeapInactive(); break;
	}
}

Sprite * ValiantLeap::GetLeapShot()
{
	return nullptr;
}
