#include "AngryCat.h"

AngryCat::AngryCat(CoreCharacter * character,
	vector<Actor * > * teamActors,
	vector<Actor * > * opponentActors,
	vector<Actor * > * neutralActors) : CoreNPCController(character)
{
	Actor * actor = character->GetActor();

	m_spawn.x = actor->GetPhysicsObject()->GetPosition()->x;
	m_spawn.y = 0.0f;
	m_spawn.z = actor->GetPhysicsObject()->GetPosition()->z;

	character->GetBattleStateController()->SetBattleState(actorBattleStateDefendPosition);
	//m_attackMoveController; allocated i Actor Controller but not using
	
	m_aggroState.Init(character->GetBattleStateController(), character->GetWalkState(), actor);

	m_interactions.push_back(&m_aggroState);

	m_acState = AngryCatInteractionController(actor, &m_aggroState);

	m_interactionControllerInstance = &m_acState;
	
	actor->SetOnHitCallback(std::bind(&AngryCat::OnHit, this, _1));
}

AngryCat::~AngryCat()
{
	
}

void AngryCat::Update(float deltaTime)
{
	//commented walk state - were gonna try have character do that for its member
	//we this should happen first,
	//todo try integrate calls to low level stuff from AC state?

	switch (m_actor->GetState())
	{
	case actorUnspawned:
		m_actor->ExitCurrentState();
		m_actor->OnEnterStationary();
		break;
	case actorDead:

		break;
	case actorRecall:

		break;
	case actorCasting:

		break;
	case actorBasicAttack:

		break;
	case actorStationary:
		m_acState.Update(deltaTime);
		//m_walkState->Update(deltaTime);
		break;
	case actorWalkToBasicTarget:
		m_acState.Update(deltaTime);
		//m_walkState->Update(deltaTime);
		break;
	case actorWalking:
		m_acState.Update(deltaTime);
		//m_walkState->Update(deltaTime);
		break;
	case actorInstantCast:
		//m_walkState->Update(deltaTime);
		break;
	case actorDirectionalCast:
		//m_walkState->Update(deltaTime);
		break;
	case actorPointCast:
		//m_walkState->Update(deltaTime);
		break;
	case actorSingleTargetCast:
		//m_walkState->Update(deltaTime);
		break;
	case actorAttackMoveCast:
		//m_walkState->Update(deltaTime);
	case actorStateCount:
		break;
	default:
		break;
	}

	CoreNPCController::Update(deltaTime);
	//stats buff etc allowed to be updated from character intance now
}

void AngryCat::OnRespawn(float x, float y, float z)
{
	m_actor->Respawn(x, y, z);

	//m_acState.ExitCurrentState();
	//TODO enter a default state
	
	m_aggroState.ExitCurrentState();
	m_aggroState.OnEnterAngryStandby();

	m_character->GetBattleStateController()->ActionPassive();

}

void AngryCat::OnHit(VitalEntity * owner)
{
	m_acState.OnHit(owner);
}

NPCSelectAction AngryCat::GetSelectBehavior()
{
	return npcSelectAllowInfoClick;
}