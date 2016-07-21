#include "Character.h"

Character::Character() : VitalEntityController()
{

}

Character::Character(Actor * actor, Pathfinder * pathfinder) : VitalEntityController(actor)
{
	m_actor = actor;

	//this has to be implemented in CoreCharacter derived in your Core Game Project

	m_walkState = WalkState(actor); //make all 'Init()s'
	m_pathController = PathController(pathfinder, &m_walkState, actor);
	m_battleStateController = BattleStateController(&m_pathController, &m_walkState, nullptr, actor);
	m_attackMoveController = AttackMoveController(&m_battleStateController, &m_walkState, actor);

	m_slotCastingIndex = playerActionCount;
	m_selectedAbility = nullptr;
}

Character::~Character()
{

}

void Character::Update(float deltaTime)
{
	m_attackMoveController.Update(deltaTime);


	if (m_actor->GetState() != actorDead)
	{
		m_actor->GetStats()->CalcStatsFromBase();

		for (unsigned int index = 0; index < m_inventory.size(); index++)
		{
			if (m_inventory.at(index) != NULL)
			{
				*m_actor->GetStatChangeObject() += *(StatChangeObject*)m_inventory.at(index);
			}
		}
	}

	UpdateBuffStructure(deltaTime, m_actor->GetBuffs());
	UpdateBuffStructure(deltaTime, m_actor->GetDebuffs());//Debuffs

	m_actor->Update(deltaTime);

	for (unsigned int i = 0; i < m_abilities.size(); i++)
	{
		if (m_abilities[i] != nullptr) m_abilities[i]->Update(deltaTime);
	}
}

void Character::UpdateBuffStructure(float deltaTime, vector<Buff*> * buffVector)
{
	for (unsigned int buffCount = 0; buffCount < buffVector->size(); buffCount++)
	{
		if (buffVector->at(buffCount) != NULL)
		{

			buffVector->at(buffCount)->Update(deltaTime);
			if (buffVector->at(buffCount)->GetTimer()->GetState() == timerFinished)
			{
				delete buffVector->at(buffCount);
				buffVector->at(buffCount) = NULL;
				return;
			}
			if (buffVector->at(buffCount)->GetTimer()->GetState() != timerFinished)
			{
				*m_actor->GetStatChangeObject() += *(StatChangeObject*)buffVector->at(buffCount)->GetStatChangeObject();
			}
		}
	}
}

void Character::ActionCastAbility(PlayerAction action, int slotIndex, float gameTime, vector<Actor * > * playerTeam, vector<Actor * > * opponentTeam, vector<Actor * > * neutralTeam)
{
	m_slotCastingIndex = action;

	//Ability * slot = m_abilities.at(slotIndex);
	m_selectedAbility = m_abilities.at(slotIndex);

	SetCastStateForAbility(m_selectedAbility, gameTime, action, playerTeam, opponentTeam, neutralTeam);


	//SOMEWHAT LEGACY ONLY
	// m_slotCastingIndex (playerAction enum codes) might be used as data to send to Server.
	switch (slotIndex)
	{
	case 1: m_slotCastingIndex = actionCastAbility1; break;
	case 2: m_slotCastingIndex = actionCastAbility2; break;
	case 3: m_slotCastingIndex = actionCastAbility3; break;
	case 4: m_slotCastingIndex = actionCastAbility4; break;
	case 5: m_slotCastingIndex = actionCastAbility5; break;
	case 6: m_slotCastingIndex = actionCastAbility6; break;
	case 7: m_slotCastingIndex = actionCastRecall; break;
	case 8: m_slotCastingIndex = actionCastSleep; break;

	default: break;
	}

}

void Character::SetCastStateForAbility(Ability * ability, float gameTime, PlayerAction action, vector<Actor * > * playerTeam, vector<Actor * > * opponentTeam, vector<Actor * > * neutralTeam)
{
	//Exit players current state:
	//		of: basic anim, cast anim, stat, walk
	//		
	//walk exit
	//set target position to current position
	//arrived at target is true
	//just change to cast state 
	//(cast animimation interupted)
	//change to cast state
	//basic attack exit 
	//	not
	//cast
	//
	//if we want to let the ability know we have
	//set the player to use the cast indicator on behalf of that ability
	//we would do this here by calling a new function we would have to make
	//in abiility that handles that information and uses it.
	//for example we could charge up energy over time, while we have the indicator open

	switch (ability->GetCastType())
	{
	case abilityCastTypeDirectionalCast:
		m_actor->OnEnterDirectionalCast();
		break;

	case abilityCastTypeInstantCast: //OutputDebugString("A");

		if (ability->Activate(
			gameTime,
			NULL,
			NULL,
			NULL,
			(vector<Actor*>*)playerTeam,
			(vector<Actor*>*)opponentTeam,
			(vector<Actor*>*)neutralTeam) == abilityResultOK)
		{

			RemoveIfConsumableItem(action);

			m_actor->OnEnterInstantCast();

			//for instant were as for other cast ///////
			//type we process behavioral methods "on click"
			//see ActionSelectWithMouse() implementation
			m_actor->OnExitInstantCast();

			m_actor->ExitCurrentState();
			m_actor->OnEnterCastingState();
			/*
			m_walkState.ExitCurrentState();
			if (m_walkState.GetState() == walkStateWalking)
			m_walkState.OnEnterPaused();*/

			m_selectedAbility = nullptr;
		}
		///////////////////////////////////////////



		break;
	case abilityCastTypePointCast:
		m_actor->OnEnterPointCast();
		break;

	case abilityCastTypeSingleTargetCast:
		m_actor->OnEnterSingleTargetCast();
		break;

	default:
		break;
	}
}

bool Character::RemoveIfConsumableItem(PlayerAction action)
{
	unsigned int i = -1;
	switch (action)
	{
	case actionInventory1: i = 0; break;
	case actionInventory2: i = 1;  break;
	case actionInventory3: i = 2;  break;
	case actionInventory4: i = 3;  break;
	case actionInventory5: i = 4;  break;
	case actionInventory6: i = 5;  break;
	case actionInventory7: i = 6;  break;
	case actionInventory8: i = 7;  break;
	case actionInventory9: i = 8;  break;
	case actionInventory0: i = 9;  break;
	default: return false;
	}

	if (i >= 0 && i < m_inventory.size())
	{
		if (m_inventory.at(i)->GetIsConsumable())
		{
			//delete m_inventory.at(i);
			m_inventory.at(i) = NULL;
		}
	}

	return false;
}

CastTestResult Character::SelectCastTest(float gameTime, LMVector3 * m_indicatorDirectionVector, LMVector3 * mousePositionVector, Actor * target, vector<Actor*>* playerTeam, vector<Actor*>* opponentTeam, vector<Actor*>* neutralTeam)
{
	if (m_actor->GetState() == actorSleeping) return castTestNoAbilitySelected;

	//Ability * selectedAbility = m_selectedAbility;
	if (m_selectedAbility == NULL) return castTestNoAbilitySelected;

	switch (m_actor->GetState())
	{
	case actorDirectionalCast: // INTENTIONAL FALL THROUGH ////////////////
	case actorPointCast:       // INTENTIONAL FALL THROUGH ////////////////
	case actorSingleTargetCast:
	{
		AbilityResult result = m_selectedAbility->CanActivate(
			gameTime,
			m_indicatorDirectionVector,
			mousePositionVector,
			target,
			playerTeam,
			opponentTeam,
			neutralTeam);

		switch (result)
		{
			//ok
		case abilityResultOK: return castTestOK;
			//errors
		case abilityResultRequiredTargetMissing: return castTestAbilityRequiredTargetMissing;
		case abilityResultStillActive: return castTestAbilityStillActive;
		case abilityResultMaximumCountReached: return castTestMaxCountReached;
		case abilityResultOutOfRange: return castTestNotInRange;
		case abilityResultOnCooldown: return castTestAbilityCooldown;

		case abilityResultIntargetable: return castTestIntargetable;
		}

	} break;


	case actorUnspawned:
	case actorDead:
	case actorRecall:
	case actorSleeping:
	case actorCasting:
	case actorBasicAttack:
	case actorStationary:
	case actorWalking:
	case actorWalkToBasicTarget:
	case actorStateCount:
	default: return castTestNoAbilitySelected;
	}

	return castTestError;
}

void Character::ActionSelectWithMouse(float gameTime, LMVector3 * m_indicatorDirectionVector, LMVector3 * mousePositionVector, Actor * target, vector<Actor * > * playerTeam, vector<Actor * > * opponentTeam, vector<Actor*> * neutralTeam)//usually left click
{
	//Ability * m_selectedAbility = GetAbilitySlot(m_slotCastingIndex);

	if (castTestOK == SelectCastTest(gameTime,
		m_indicatorDirectionVector,
		mousePositionVector,
		target,
		playerTeam,
		opponentTeam,
		neutralTeam))
	{
		if (m_selectedAbility->Activate(
			gameTime,
			m_indicatorDirectionVector,
			mousePositionVector,
			target,
			playerTeam,
			opponentTeam,
			neutralTeam) == abilityResultOK)
		{
			RemoveIfConsumableItem(m_slotCastingIndex);
			m_actor->ExitCurrentState();
			m_actor->OnEnterCastingState();
		}
	}
}

void Character::ActionWalkOrBasicAttack(float gameTime, VitalEntity * target)//usually right click
{
	if (m_actor->GetState() == actorSleeping) return;

	if (target->GetVitalEntityState() == vitalEntityStateActive) //prevent chase of intargable or inactive
	{
		m_battleStateController.ExitCurrentState();
		m_battleStateController.OnEnterBattleStateChase(target);
	}
}

void Character::ActionWalkOrBasicAttack(float gameTime, LMVector3 * point)//usually right click
{
	if (m_actor->GetState() == actorSleeping) return;

	m_attackMoveController.ActionRegularWalk();

	if (m_actor->GetState() != actorCasting
		&& m_actor->GetState() != actorBasicAttack)
	{
		m_pathController.WalkToPosition(
			false,//ignoreRateLowering
			point,//target (todo possibly const this?)
			m_actor->GetPhysicsObject()->GetPosition()//origin
		);

		m_actor->ExitCurrentState();
		m_actor->OnEnterEnroute();
	}
}


void Character::ActionInventory(PlayerAction action, int vectorIndex, float gameTime, vector<Actor * > * playerTeam, vector<Actor * > * opponentTeam, vector<Actor * > * neutralTeam)
{
	if (m_actor->GetState() == actorSleeping) return;

	if (m_inventory.at(vectorIndex) == NULL) return;

	if (m_inventory.at(vectorIndex)->GetAbility() != NULL)
	{
		//temp while we play around
		m_inventory.at(vectorIndex)->GetAbility()->SetOwner(m_actor);
		//

		SetCastStateForAbility(m_inventory.at(vectorIndex)->GetAbility(), gameTime, action, playerTeam, opponentTeam, neutralTeam);

		m_slotCastingIndex = action;
	}
}

void Character::KeyMove(float gameTime, char dir,
	LMVector3 * cPos, LMVector3 * cLookAtPos, LMVector3 * walkIndicatorPos)
{

	LMVector3 lookDisp(0.0f, 0.0f, 0.0f);
	LMVector3 disp(0.0f, 0.0f, 0.0f);

	lookDisp.x = cPos->x - cLookAtPos->x;
	lookDisp.z = cPos->z - cLookAtPos->z;

	lookDisp.Normalize();

	lookDisp *= 0.7f;

	walkIndicatorPos->x = disp.x;
	walkIndicatorPos->y = 0.1f;
	walkIndicatorPos->z = disp.z;

	//3rd pewrson cam controls


	switch (dir)
	{
	case 'l':
		disp.z = m_actor->GetPhysicsObject()->GetPosition()->z - lookDisp.x;
		disp.x = m_actor->GetPhysicsObject()->GetPosition()->x + lookDisp.z;
		break;

	case 'r':
		disp.z = m_actor->GetPhysicsObject()->GetPosition()->z + lookDisp.x;
		disp.x = m_actor->GetPhysicsObject()->GetPosition()->x - lookDisp.z;
		break;

	case 'u':
		disp.z = m_actor->GetPhysicsObject()->GetPosition()->z - lookDisp.z;
		disp.x = m_actor->GetPhysicsObject()->GetPosition()->x - lookDisp.x;
		break;

	case 'd':
		disp.z = m_actor->GetPhysicsObject()->GetPosition()->z + lookDisp.z;
		disp.x = m_actor->GetPhysicsObject()->GetPosition()->x + lookDisp.x;
		break;
	}

	ActionWalkOrBasicAttack(gameTime, &disp);
}


void Character::ActionStop()
{
	if (m_actor->GetState() == actorSleeping) return;

	if (m_actor->GetState() != actorCasting
		&& m_actor->GetState() != actorBasicAttack)
	{
		m_actor->OnEnterStationary();
	}

	m_walkState.ExitCurrentState();
	m_walkState.OnEnterStopped();



	m_attackMoveController.ExitCurrentState();
	m_attackMoveController.OnEnterStandby();
}

void Character::ActionAttackMove()
{
	if (GetActor()->GetState() == actorSleeping) return;
	m_actor->ExitCurrentState();
	m_actor->OnEnterAttackMoveCast();
}

void Character::ActionDriveBy()
{
	if (GetActor()->GetState() == actorSleeping) return;
	m_actor->ExitCurrentState();
	m_actor->OnEnterDriveByCast();
}

void Character::DebugTeleport(float x, float y, float z)
{
	m_walkState.ExitCurrentState();
	m_walkState.OnEnterStopped();

	if (m_battleStateController.GetBattleState() == actorBattleStateChase)
	{
		m_battleStateController.ExitCurrentState();
		m_battleStateController.OnEnterBattleStateDefendPosition();
	}

	m_attackMoveController.ExitCurrentState();
	m_attackMoveController.OnEnterStandby();

	m_walkState.GetTargetPosition()->x = x;
	m_walkState.GetTargetPosition()->y = y;
	m_walkState.GetTargetPosition()->z = z;

	m_actor->GetPhysicsObject()->GetPosition()->x = x;
	m_actor->GetPhysicsObject()->GetPosition()->y = y;
	m_actor->GetPhysicsObject()->GetPosition()->z = z;
}


void Character::OnRespawn(float x, float y, float z)
{
	//actorList->at(i)->OnRespawn();

	m_actor->Respawn(x, y, z);

	GetBattleStateController()->ActionPassive();
}

Ability * Character::GetAbilityAtIndex(unsigned int i)
{
	if (i < m_abilities.size()) return m_abilities.at(i);

	return NULL;
}

int * Character::GetInventoryValue()
{
	m_inventoryValue = 0;

	for (unsigned int index = 0; index < m_inventory.size(); index++)
	{
		if (m_inventory.at(index) != NULL)
			m_inventoryValue += m_inventory.at(index)->GetValue();
	}

	return &m_inventoryValue;
}

Actor * Character::GetActor() { return m_actor; }
vector<Ability *> * Character::GetAbilities() { return &m_abilities; }
vector<Item *> * Character::GetInventory() { return &m_inventory; }
TradeInventory * Character::GetTradeInventory() { return &m_tradeInventory; }
AttackMoveController * Character::GetAttackMoveController() { return &m_attackMoveController; }
BattleStateController * Character::GetBattleStateController() { return &m_battleStateController; }
PathController * Character::GetPathController() { return &m_pathController; }
WalkState * Character::GetWalkState() { return &m_walkState; }

void Character::SetInvFromSet(vector<Item*> * set)
{
	for (unsigned int index = 0; index < set->size(); index++)
	{
		m_inventory.push_back(set->at(index));
	}

	for (unsigned int index = 0; index < 10 - set->size(); index++)
	{
		m_inventory.push_back(NULL);
	}
}

void Character::InitAbility(int slotToInit, Ability * ability) { m_abilities.at(slotToInit) = ability; }
Ability * Character::ReturnCastingAbility() { return m_selectedAbility; }
ShopZone * Character::GetFollowingZone() { return &m_zoneThatFollows; }
PlayerAction Character::GetCastingAbility() { return m_slotCastingIndex; }//is private, see header notes