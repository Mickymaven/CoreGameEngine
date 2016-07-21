#include "CursorController.h"


GameInputController * CursorController::m_gameInputController = nullptr;


CursorController::CursorController()
{
	ResultPoint = nullptr;
	m_pcView = nullptr;
	m_npcView = nullptr;
	m_tempVE = nullptr;
}

CursorController::~CursorController()
{

}

void CursorController::Init(MobaViewState * gameViewIn, StandardMatch5v5State * gameStateIn, PlayerWorldSelectionController * playerWorldSelectionController)
{
	gameView = gameViewIn;
	cameraDirector = gameViewIn->GetCameraDirector();
	m_cursor = gameViewIn->GetGameCursor();
	gameState = gameStateIn;
	m_playerWorldSelectionController = playerWorldSelectionController;
}

void CursorController::Update(float deltaTime)
{
	m_cursor->SetState(WhichCursorShouldIShow());
	m_cursor->Update(deltaTime);
}

GameCursorTypes CursorController::WhichCursorShouldIShow()
{
	if (m_gameInputController->GetMousePress(MIDDLE_BUTTON, true, false))
	{
		if (cameraDirector->GetUsingCamera() == usingLockCamera) return gameCursorTypeCameraPan;
		if (cameraDirector->GetUsingCamera() == usingFlyCamera) return gameCursorTypeCameraPan;
		//else return gameCursorTypeCursor;
	}

	//just an alternative idea to process the cursorstate
	//GameCursorTypes m_cursorType[actorStateCount][castTestResultCount][abilityTargetGroupCount];
	//m_cursorType[actorSingleTargetCast][castTestOK][abilityTargetTeam] = gameCursorTypeHeal;

	AbilityTargetGroup targetGroup;
	switch (gameState->GetControlledCharacter()->GetActor()->GetState())
	{
		case actorSingleTargetCast:
		case actorDirectionalCast:
		case actorInstantCast:
		case actorPointCast:
			targetGroup = gameState->GetControlledCharacter()->ReturnCastingAbility()->GetTargetGroup();
			break;
			//all other cases
		//default: return gameCursorTypeCursor;
		default: targetGroup = abilityTargetOpponents;
	}
	
	//cursors if opponent is target
	if ((m_castTestResultOpponent = TestOpponentReturningCastTest()) != castTestTargetMissing)
	{
		switch (m_castTestResultOpponent)
		{
		case castTestOK: 
			if (targetGroup == abilityTargetOpponents)
			{
				switch (gameState->GetControlledActor()->GetState())
				{
				case actorSingleTargetCast: return gameCursorTypeCastAttack;
				case actorDirectionalCast: return gameCursorDirectionalAttack;
				case actorInstantCast: return gameCursorTypeCursor;
				case actorPointCast: return gameCursorTypePoint;
				case actorAttackMoveCast://fall (todo new cursor for attack or driveby)
				case actorDriveByCast: return gameCursorTypeAttackMove;
					//all other cases
					//default: return gameCursorTypeCursor;
				}
				return gameCursorTypeCast;
			}
			else
			{
				//todo use ground code
			}
		
		case castTestAbilityStillActive:
		case castTestMaxCountReached:
		case castTestAbilityCooldown:
		{
			//different cooldown for single target mouse over or directional mouse over

			return gameCursorTypeCooldownAttack;
			if (targetGroup == abilityTargetOpponents)
			{
				switch (gameState->GetControlledCharacter()->GetActor()->GetState())
				{
				case actorSingleTargetCast: return gameCursorTypeCooldownCastAttack;
				case actorInstantCast://fall
				case actorPointCast://fall
				case actorDirectionalCast: return gameCursorTypeCooldownAttack;
				}
			}
			else
			{
				//todo use ground code
			}

		}break;
			

		case castTestNoAbilitySelected: return gameCursorTypeInfoAttack;
		case castTestNotInRange: return gameCursorTypeRange;
		case castTestIntargetable: return gameCursorTypeInfo;

		}

		return gameCursorTypeInfoAttack;

	}
	//cursors if opponent is npc
	else if((m_castTestResultNeutral = TestNPCsReturningCastTest()) != castTestTargetMissing)
	{
		switch (m_castTestResultNeutral)
		{
		case castTestOK: return gameCursorTypeCastAttack;
		default: return gameCursorTypeInfoAttack;
		}
	}

	//cursors if target is team
	else if((m_castTestResultTeam = TestTeamReturningCastTest()) != castTestTargetMissing)
	{
		switch (m_castTestResultTeam)
		{
		case castTestOK:

			if (targetGroup == abilityTargetTeam)
			{
				switch (gameState->GetControlledCharacter()->GetActor()->GetState())
				{
				case actorSingleTargetCast: return gameCursorTypeHealCast;
				case actorDirectionalCast: return gameCursorTypeHealCast;
				case actorInstantCast: return gameCursorTypeHealCast;
				case actorPointCast: return gameCursorTypeHealCast;
				case actorAttackMoveCast://fall (todo new cursor for attack or driveby)
				case actorDriveByCast: return gameCursorTypeAttackMove;
					//all other cases
					//default: return gameCursorTypeCursor;
				}
				return gameCursorTypeCast;
			}
			else  if (targetGroup == abilityTargetOpponents)
			{
				//todo use ground code
			}

		case castTestAbilityStillActive:
		case castTestMaxCountReached:
		case castTestAbilityCooldown:
		{
			//different cooldown for single target mouse over or directional mouse over
			if (targetGroup == abilityTargetTeam)
			{
				switch (gameState->GetControlledCharacter()->GetActor()->GetState())
				{
				case actorSingleTargetCast: return gameCursorTypeCooldownCast;
				case actorInstantCast://fall
				case actorPointCast://fall
				case actorDirectionalCast: return gameCursorTypeCooldownCast;
				}
			}
			else
			{
				//todo use ground code.
			}

		}break;


		case castTestNoAbilitySelected: return gameCursorTypeInfo;
		case castTestNotInRange: return gameCursorTypeRange;
		case castTestIntargetable: return gameCursorTypeInfo;

		}

		return gameCursorTypeInfo;


	}

	else if ((m_castTestResultGround = TestGroundReturningCastTest()) != castTestTargetMissing)
	{
		switch (m_castTestResultGround)
		{
			case castTestError:
			{
					OutputDebugString("case Test Error\n\n\n");
			} break;

			case castTestOK:
			{
				if (targetGroup == abilityTargetTeam)
				{
					switch (gameState->GetControlledCharacter()->GetActor()->GetState())
					{
					case actorSingleTargetCast: return gameCursorTypeHeal;
					case actorDirectionalCast: return gameCursorTypeHealCast;
					case actorInstantCast: return gameCursorTypeHealCast;
					case actorPointCast: return gameCursorTypeHealCast;
					case actorAttackMoveCast://fall (todo new cursor for attack or driveby)
					case actorDriveByCast: return gameCursorTypeAttackMove;
						//all other cases
						//default: return gameCursorTypeCursor;
					}
					return gameCursorTypeCast;
				}
				else if (targetGroup == abilityTargetOpponents)
				{
					switch (gameState->GetControlledCharacter()->GetActor()->GetState())
					{
					//case actorSingleTargetCast: return gameCursorTypeCast;
					case actorDirectionalCast: return gameCursorDirectional;
					case actorInstantCast: return gameCursorTypeCursor;
					case actorPointCast: return gameCursorTypePoint;
					case actorAttackMoveCast://fall (todo new cursor for attack or driveby)
					case actorDriveByCast: return gameCursorTypeAttackMove;
					//all other cases
					//default: return gameCursorTypeCursor;
					}
					return gameCursorTypeCast;
				}
			} break;

			case castTestAbilityRequiredTargetMissing:
				if (targetGroup == abilityTargetTeam) return gameCursorTypeHeal;
				else if (targetGroup == abilityTargetTeam) return gameCursorTypeCast;
				break;

			case castTestAbilityStillActive:
			case castTestMaxCountReached:
			case castTestAbilityCooldown: return gameCursorTypeCooldownCast;

			case castTestNotInRange: return gameCursorTypeRange;

			case castTestNoAbilitySelected:
			default: return gameCursorTypeCursor;
		}
	}

	return gameCursorTypeCursor;
}

CastTestResult CursorController::TestOpponentReturningCastTest()
{
	if (m_playerWorldSelectionController->OpponentTarget(&m_pcView, selectActionQuerySelectOpponent))
	{
		return m_playerWorldSelectionController->GetCastTestResult();
	}

	return castTestTargetMissing;
}

CastTestResult CursorController::TestNPCsReturningCastTest()
{
	if (m_playerWorldSelectionController->NPCTarget(&m_npcView, selectActionQuerySelectNeutral))
	{
		return m_playerWorldSelectionController->GetCastTestResult();
	}
	return castTestTargetMissing;
}

CastTestResult CursorController::TestTeamReturningCastTest()
{
	if (m_playerWorldSelectionController->TeamTarget(&m_pcView, selectActionQuerySelectTeam))
	{
		return m_playerWorldSelectionController->GetCastTestResult();
	}
	return castTestTargetMissing;
}

CastTestResult CursorController::TestGroundReturningCastTest()
{
	if (m_playerWorldSelectionController->GroundPointWithScreen(nullptr, selectActionQuerySelectGround))
	{
		return m_playerWorldSelectionController->GetCastTestResult();
	}
	return castTestTargetMissing;
}

CastTestResult CursorController::TestEntitiesReturningCastTest()
{
	return castTestNoAbilitySelected;
}

bool CursorController::TestOpponentReturningBool()
{
	if (m_playerWorldSelectionController->OpponentTarget(&m_pcView, selectActionQuerySelectOpponent))
	{

		return true;
	}

	return false;

}

bool CursorController::TestTeamReturningBool()
{
	if (m_playerWorldSelectionController->TeamTarget(&m_pcView, selectActionControlledSelectTeam))
	{
		return true;
	}
	return false;
}

bool CursorController::TestEntitiesReturningBool()
{
	return m_playerWorldSelectionController->NeutralObjectTarget(&m_tempVE, selectActionNothing);
}