#include "CoreCharacter.h"

CoreCharacter::CoreCharacter() {}

CoreCharacter::CoreCharacter(
	Actor * actor,
	Pathfinder * pathfinder,
	vector<Actor * > * teamActors,
	vector<Actor * > * opponentActors,
	vector<Actor * > * neutralActors) 
	: Character(actor, pathfinder)
{
	m_inventoryValue = 0;

	//some kind of init needs to apply more state (such as these vars) to the character at start of game
	//m_state = actorUnspawned;
	//m_afflictionState = afflictionNone;

	m_SlotBasicAttack = new BasicAttack(actor);
	m_SlotBasicAttack->SetTeams(teamActors, opponentActors, neutralActors);

	m_recall = new Recall(actor);
	m_recall->SetTeams(teamActors, opponentActors, neutralActors);

	m_sleep = new ZZzzz(actor);
	m_sleep->SetTeams(teamActors, opponentActors, neutralActors);


	//other slots are done by PlayerCharacterFactory
	m_abilities.resize(abilitySlotCount);
	m_abilities.at(abilitySlotBasicAttack) = m_SlotBasicAttack;
	m_abilities.at(abilitySlot1) = nullptr;
	m_abilities.at(abilitySlot2) = nullptr;
	m_abilities.at(abilitySlot3) = nullptr;
	m_abilities.at(abilitySlot4) = nullptr;
	m_abilities.at(abilitySlot5) = nullptr;
	m_abilities.at(abilitySlot6) = nullptr;
	m_abilities.at(abilitySlotRecall) = m_recall;
	m_abilities.at(abilitySlotSleep) = m_sleep;


	m_walkState = WalkState(actor); //make all 'Init()s'
	m_pathController = PathController(pathfinder, &m_walkState, actor);
	m_battleStateController = BattleStateController(&m_pathController, &m_walkState, (BasicAttack*)m_SlotBasicAttack, actor);
	m_attackMoveController = AttackMoveController(&m_battleStateController, &m_walkState, actor);

	GetTradeInventory()->SetPrivateTradeInventory(GetInventory());

}

CoreCharacter::~CoreCharacter()
{
	delete m_slot1; m_slot1 = NULL;
	delete m_slot2; m_slot2 = NULL;
	delete m_slot3; m_slot3 = NULL;
	delete m_slot4; m_slot4 = NULL;
	delete m_custom1; m_custom1 = NULL;
	delete m_custom2; m_custom2 = NULL;
	delete m_SlotBasicAttack; m_SlotBasicAttack = NULL;
	delete m_recall; m_recall = NULL;
	delete m_sleep; m_sleep = NULL;

}

void CoreCharacter::AddAbility(Ability * ability, AbilitySlotType slot)
{
	switch (slot)
	{
		//case abilitySlotBasicAttack: m_SlotBasicAttack = ability; break;
	case abilitySlot1: m_slot1 = ability; break;
	case abilitySlot2: m_slot2 = ability; break;
	case abilitySlot3: m_slot3 = ability; break;
	case abilitySlot4: m_slot4 = ability; break;
	case abilitySlot5: m_custom1 = ability; break;
	case abilitySlot6: m_custom2 = ability; break;
		//case abilitySlotSleep: m_recall = ability; break;
		//case abilitySlotRecall: m_sleep = ability; break;
	}

	//DEBUG_IF(slot < 1 || slot > 6) OutputDebugString("bad slot in PlayerCharacterController::AddAbility");

	m_abilities.at(slot) = ability;
}

void CoreCharacter::ActionCastRecall(float gameTime)
{
	if (GetActor()->GetState() == actorSleeping) return;

	m_walkState.ExitCurrentState();
	m_walkState.OnEnterStopped();

	m_recall->Activate(gameTime);

	m_actor->ExitCurrentState();
	m_actor->OnEnterRecallAnimation();
}

void CoreCharacter::ActionCastSleep(float gameTime)
{
	if (GetActor()->GetState() == actorSleeping) return;

	m_walkState.ExitCurrentState();
	m_walkState.OnEnterStopped();

	m_sleep->Activate(gameTime);

	m_attackMoveController.ActionOnSleep();

	m_actor->ExitCurrentState();
	m_actor->OnEnterSleeping();
}