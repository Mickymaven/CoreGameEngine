#include "Actor.h"

Actor::Actor(
	ActorStats * stats,
	LMVector3 position,
	LMVector3 rotation,
	LMVector3 scale,
	LMVector3 velocity,
	LMVector3 spin,
	LMVector3 resize,
	float acceleration)
	:VitalEntity(stats, position, rotation, scale, velocity, spin, resize, acceleration)
{
	m_vitalEntityType = vitalEntityTypeActor;
	m_vitalEntityState = vitalEntityStateActive;

	m_state = actorUnspawned;

	m_afflictionState = afflictionNone;
	m_deathTimer = LMTimer(0.0f, false);
	m_castAnimationTimer = LMTimer(0.0f, false);

	m_stats.CalcStatsFromBase();
	m_stats.SetHealth(m_stats.GetMaxHealth());//once max health calculated
	
	m_kda.kills = 0;
	m_kda.deaths = 0;
	m_kda.assists = 0;
}

Actor::~Actor()
{

}

void Actor::Update(float deltaTime)
{
	//apply stat changes found in StatChangeObject
	StatChangeUpdate(deltaTime);

	m_stats.RegenHealth(deltaTime);//regen health
	
	switch (m_state)
	{
	case actorUnspawned:
		break;
	case actorDead:
		DeathState(deltaTime);
		break;
	case actorRecall:
		RecallAnimation(deltaTime);
		break;
	case actorSleeping:
		Sleeping(deltaTime);
		break;
	case actorCasting:
		CastAnimation(deltaTime);
		break;
	case actorBasicAttack:
		BasicAttackAnimation(deltaTime);
		break;
	case actorStationary:
		break;
	case actorWalking:
		Enroute(deltaTime);
		break;
	case actorWalkToBasicTarget:
		WalkToBasicTarget(deltaTime);
		break;
	case actorInstantCast:
		InstantCast(deltaTime);
		break;
	case actorDirectionalCast:
		DirectionalCast(deltaTime);
		break;
	case actorPointCast:
		PointCast(deltaTime);
		break;
	case actorSingleTargetCast:
		SingleTargetCast(deltaTime);
		break;
	case actorAttackMoveCast:
		AttackMoveCast(deltaTime);
	case actorDriveByCast:
		DriveByCast(deltaTime);
	case actorStateCount:
		break;
	default:
		break;
	}

	switch (m_afflictionState)
	{
	case afflictionNone:
		break;
	case afflictionStun:
		break;
	case afflictionRoot:
		break;
	case afflictionSilence:
		break;
	case afflictionCount:
		break;
	default:
		break;
	}

	m_physicsObject.Update(deltaTime);
}

void Actor::DeathTimerUpdate(float deltaTime)
{
	m_deathTimer.Update(deltaTime);
}

void Actor::StatChangeUpdate(float deltaTime)
{
	//m_stats.CalcStatsFromBase();

	m_stats.AddHealth(m_statChangeObject.m_health);

	m_stats.m_maxHealth += m_statChangeObject.m_maxHealth;
	m_stats.m_healthRegen += m_statChangeObject.m_healthRegen;
	m_stats.m_physicalDamage += m_statChangeObject.m_physicalDamage;
	m_stats.m_catVoodoo += m_statChangeObject.m_catVoodoo;
	m_stats.m_attackSpeed += m_statChangeObject.m_attackSpeed;
	m_stats.m_moveSpeed += m_statChangeObject.m_moveSpeed;
	if (m_stats.m_moveSpeed < 0) m_stats.m_moveSpeed = 0;
	m_stats.m_armor += m_statChangeObject.m_armor;
	m_stats.m_catVoodooResist += m_statChangeObject.m_catVoodooResist;
	m_stats.m_range += m_statChangeObject.m_range;
	m_statChangeObject.Update(deltaTime);
}

void Actor::OnEnterUnspawned()
{
	m_state = actorUnspawned;
}

void Actor::Unspawned(float deltaTime)
{

}

void Actor::OnExitUnspawned()
{

}

void Actor::OnEnterRecallAnimation()
{
	m_state = actorRecall;
}

void Actor::RecallAnimation(float deltaTime)
{
	//m_recallTimer->Update(deltaTime);
	
}

void Actor::OnExitRecallAnimation()
{
	OnEnterStationary();
}



void Actor::OnEnterSleeping()
{
	m_state = actorSleeping;
	m_sleepTimer.RestartWithDuration(5.0f,true);

	m_physicsObject.GetRotation()->x = -1.57f;
	m_physicsObject.GetRotation()->z = 0.0f;
}

void Actor::Sleeping(float numberOfSheep)
{
	m_sleepTimer.Update(numberOfSheep);

	if (m_sleepTimer.GetState() == timerFinished)
	{
		OnExitSleeping();
		OnEnterStationary();
	}
}

void Actor::OnExitSleeping()
{
	m_physicsObject.GetRotation()->x = 0.0f;
	m_physicsObject.GetRotation()->z = 0.0f;
}


void Actor::OnEnterStationary()
{
	//m_vitalEntityState = vitalEntityStateActive;
	m_state = actorStationary;
}

void Actor::Stationary(float deltaTime)
{
	//UpdateBattleState(deltaTime);
}

void Actor::OnExitStationary()
{

}

void Actor::OnEnterEnroute()
{
	m_state = actorWalking;
}

void Actor::Enroute(float deltaTime)
{
	
}

void Actor::OnExitEnroute()
{
	OnEnterStationary();
}

void Actor::OnEnterWalkToBasicTarget()
{
	m_state = actorWalkToBasicTarget;
}

void Actor::WalkToBasicTarget(float deltaTime)
{

}

void Actor::OnExitWalkToBasicTarget()
{

}

void Actor::OnEnterInstantCast()
{
	m_state = actorInstantCast;
}

void Actor::InstantCast(float deltaTime)
{

}

void Actor::OnExitInstantCast()
{

}

void Actor::OnEnterDirectionalCast()
{
	m_state = actorDirectionalCast;
}

void Actor::DirectionalCast(float deltaTime)
{

}

void Actor::OnExitDirectionalCast()
{

}

void Actor::OnEnterPointCast()
{
	m_state = actorPointCast;
}

void Actor::PointCast(float deltaTime)
{
	
}

void Actor::OnExitPointCast()
{

}

void Actor::OnEnterSingleTargetCast()
{
	m_state = actorSingleTargetCast;
}

void Actor::SingleTargetCast(float deltaTime)
{
	
}

void Actor::OnExitSingleTargetCast()
{

}

void Actor::OnEnterAttackMoveCast()
{
	m_state = actorAttackMoveCast;
}

void Actor::AttackMoveCast(float deltaTime)
{

}

void Actor::OnExitAttackMoveCast()
{

}

void Actor::OnEnterDriveByCast()
{
	m_state = actorDriveByCast;
}

void Actor::DriveByCast(float deltaTime)
{

}

void Actor::OnExitDriveByCast()
{

}

void Actor::OnEnterCastingState()
{
	//State represents a stopped actor playing the casting animation

	m_state = actorCasting;
	m_castAnimationTimer.RestartWithDuration(0.2f, true);
}

void Actor::CastAnimation(float deltaTime)
{
	//tick timer over
	m_castAnimationTimer.Update(deltaTime);

	//control the animation frames
	//todo animation frames

	//see if we are finished
	if (m_castAnimationTimer.GetState() == timerFinished)
	{
		OnExitCastingState();
	}
}

void Actor::OnExitCastingState()
{
	OnEnterEnroute();
}

void Actor::OnEnterBasicAttackAnimationState()
{	
	//OutputDebugString("ENTER BASIC ANIM\n");
	m_state = actorBasicAttack;

	m_castAnimationTimer.RestartWithDuration(
		1.0f/m_stats.m_attackSpeed * 0.20f, true);//TODO seperate timerss
}

void Actor::BasicAttackAnimation(float deltaTime)
{
	m_castAnimationTimer.Update(deltaTime);

	//control the animation frames
	//todo animation frames

	//see if we are finished
	if (m_castAnimationTimer.GetState() == timerFinished)
	{
		OnExitBasicAttackAnimationState();
	}
}

void Actor::OnExitBasicAttackAnimationState()
{
	OnEnterEnroute();
}

void Actor::OnEnterDeathState()
{
	m_state = actorDead;
	m_vitalEntityState = vitalEntityStateInactive;
}

void Actor::DeathState(float deltaTime)
{
	DeathTimerUpdate(deltaTime);
}

void Actor::OnExitDeathState()
{
	m_vitalEntityState = vitalEntityStateActive;

	m_stats.CalcStatsFromBase();
	m_stats.m_health = m_stats.m_maxHealth;
	OnEnterStationary();
}

void Actor::OnEnterForState(ActorState state)
{
	switch (state)
	{
	case actorUnspawned:
		OnEnterUnspawned();
		break;
	case actorDead:
		OnEnterDeathState();
		break;
	case actorRecall:
		OnEnterRecallAnimation();
		break;
	case actorSleeping:
		OnEnterSleeping();
		break;
	case actorCasting:
		OnEnterCastingState();
		break;
	case actorBasicAttack:
		OnEnterBasicAttackAnimationState();
		break;
	case actorStationary:
		OnEnterStationary();
		break;
	case actorWalking:
		OnEnterEnroute();
		break;
	case actorWalkToBasicTarget:
		OnEnterWalkToBasicTarget();
		break;
	case actorInstantCast:
		OnEnterInstantCast();
		break;
	case actorDirectionalCast:
		OnEnterDirectionalCast();
		break;
	case actorPointCast:
		OnEnterPointCast();
		break;
	case actorSingleTargetCast:
		OnEnterSingleTargetCast();
		break;
	case actorDriveByCast:
		OnEnterDriveByCast();
		break;
	case actorStateCount:
		break;
	default:
		break;
	}
}

void Actor::OnExitForState(ActorState state)
{
	switch (state)
	{
	case actorUnspawned:
		OnExitUnspawned();
		break;
	case actorDead:
		OnExitDeathState();
		break;
	case actorRecall:
		OnExitRecallAnimation();
		break;
	case actorSleeping:
		OnExitSleeping();
		break;
	case actorCasting:
		OnExitCastingState();
		break;
	case actorBasicAttack:
		//OnExitBasicAttack()
		break;
	case actorStationary:
		OnExitStationary();
		break;
	case actorWalking:
		OnExitEnroute();
		break;
	case actorWalkToBasicTarget:
		OnExitWalkToBasicTarget();
		break;
	case actorInstantCast:
		OnExitInstantCast();
		break;
	case actorDirectionalCast:
		OnExitDirectionalCast();
		break;
	case actorPointCast:
		OnExitPointCast();
		break;
	case actorSingleTargetCast:
		OnExitSingleTargetCast();
		break;
	case actorAttackMoveCast:
		OnExitAttackMoveCast();
		break;
	case actorDriveByCast:
		OnExitDriveByCast();
		break;
	case actorStateCount:
		break;
	default:
		break;
	}
}

void  Actor::ExitCurrentState()
{
	OnExitForState(m_state);
}


void Actor::Respawn(float x, float y, float z)
{
	m_vitalEntityState = vitalEntityStateActive;

	m_physicsObject.GetPosition()->x = x;
	m_physicsObject.GetPosition()->y = y;
	m_physicsObject.GetPosition()->z = z;

	ExitCurrentState();
	OnEnterStationary();
}

void Actor::Death(float duration)
{
	//RaccAttack Death doesn't care what state you are in. RaccAttack

	m_deathTimer.RestartWithDuration(duration, true);

	if (m_state != actorDead)
	{
		ExitCurrentState();
		OnEnterDeathState();
	}
	else
	{
		OutputDebugString("Trying to kill dead character (Actor.cpp)");
		MessageBox(NULL, "Trying to kill dead character (Actor.cpp)", "Err", MB_OK);
	}
}




//accessors
PlayerKDA Actor::GetKDA() { return m_kda; }
ActorState Actor::GetState() { return m_state; }
LMTimer * Actor::GetTimer() { return &m_deathTimer; }

LMTimer * Actor::GetRecallTimer() { return &m_recallTimer; }

TeamName Actor::GetTeam() { return m_team; }


//stat mutators
void Actor::SetKDA(PlayerKDA kda) { m_kda = kda; }
void Actor::SetTeam(TeamName team) { m_team = team; }


void Actor::SetBasicAttackTarget(Actor * target)
{
	m_basicAttackTarget = target;
}