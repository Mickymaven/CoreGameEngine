#include "CharacterInputSet.h"

CharacterInputSet::CharacterInputSet() : InputSet()
{

}

CharacterInputSet::CharacterInputSet(StandardMatch5v5State * state, MobaViewState * view, PlayerWorldSelectionController * playerWorldSelectionController) : InputSet()
{
	gameState = state;
	gameView = view;
	m_cameraDirector = view->GetCameraDirector();
	cam3p = m_cameraDirector->GetUsingCamera(usingThirdPersonCamera);

	m_playerWorldSelectionController = playerWorldSelectionController;

	m_mouseUpDuringAMInitialClick = true;
}

CharacterInputSet::~CharacterInputSet()
{

}

void CharacterInputSet::Update(float deltaTime)
{
	playerCharacter = gameState->GetControlledCharacter();


	//we have been putting model state changes actively into the part
	//of the code that changes the state
	//moving the SetState there would save us from calling this every update
	m_model->SetState(playerCharacter->GetActor()->GetState());

	if (m_mouseUpDuringAMInitialClick == false)
	{
		if (!sm_gameInputController->GetMousePress(m_model->m_keybinds[actionWalkOrBasicAttack], true, false))
		{
			m_mouseUpDuringAMInitialClick = true;
		}
	}
}

void CharacterInputSet::AttemptAction(int action, float deltaTime)
{
	
	ResultPoint = NULL;
	target = NULL;
	basicAttackTarget = NULL;


	switch (action)
	{
	
	//third person view
	case characterActionKeyMoveLeft: 
		gameState->GetControlledCharacter()->KeyMove(
			*gameState->GetGameElapsedTime(),
			'l',
			(LMVector3*)cam3p->GetPosition(),
			(LMVector3*)cam3p->GetLookAt(),
			gameView->GetIndicatorController()->GetWalkIndicator()->GetPhysicsObject()->GetPosition()
			);
		break;
	case characterActionKeyMoveRight:
		gameState->GetControlledCharacter()->KeyMove(
			*gameState->GetGameElapsedTime(),
			'r',
			(LMVector3*)cam3p->GetPosition(),
			(LMVector3*)cam3p->GetLookAt(),
			gameView->GetIndicatorController()->GetWalkIndicator()->GetPhysicsObject()->GetPosition()
			);
		break;
	case characterActionKeyMoveUp:
		gameState->GetControlledCharacter()->KeyMove(
			*gameState->GetGameElapsedTime(),
			'u',
			(LMVector3*)cam3p->GetPosition(),
			(LMVector3*)cam3p->GetLookAt(),
			gameView->GetIndicatorController()->GetWalkIndicator()->GetPhysicsObject()->GetPosition()
			);
		break;
	case characterActionKeyMoveDown: 
		gameState->GetControlledCharacter()->KeyMove(
			*gameState->GetGameElapsedTime(),
			'd',
			(LMVector3*)cam3p->GetPosition(),
			(LMVector3*)cam3p->GetLookAt(),
			gameView->GetIndicatorController()->GetWalkIndicator()->GetPhysicsObject()->GetPosition()
			);
		break;


	//regular actions
	case characterActionSelectWithMouse: //usually left click
	{
		targetPlayerCharacterController = NULL;
		pcView=nullptr; //PlayerCharacterView * 
		npcView=nullptr; //NPCView * 
		//pointHere; //LMVector3
		
		//selectWithMouse =false;
		ItemEntityView * ieView = nullptr;

		//intentional assignment in conditional
		if (m_playerWorldSelectionController->OpponentTarget(&pcView, selectActionControlledSelectOpponent))
		{ }
		else if (m_playerWorldSelectionController->NPCTarget(&npcView, selectActionControlledSelectNeutral))
		{ }
		else if (m_playerWorldSelectionController->TeamTarget(&pcView, selectActionControlledSelectTeam))
		{ }
		else if (m_playerWorldSelectionController->QuestItemTarget(&ieView, selectActionControlledSelectQuestItems))
		{ }
		else if (m_playerWorldSelectionController->GroundPointWithScreen(&pointHere, selectActionControlledSelectGround))
		{
			playerCharacter->GetAttackMoveController()->ForceStandby();
			gameView->GetHud()->GetGameInfoPanel()->GetInfoPanel()->SetState(infoPanelStateClosed);
		}
		else { }

		if (pcView != nullptr)
		{
			target = pcView->GetCharacterView()->GetActorView()->GetActor();
			targetPlayerCharacterController = pcView->GetPlayerCharacterController();

			gameView->GetHud()->GetGameInfoPanel()->GetInfoPanel()->SetInfoPanelTarget(targetPlayerCharacterController->GetCharacter());
			gameView->GetHud()->GetGameInfoPanel()->GetInfoPanel()->SetState(infoPanelStateOpened);
		}
		else if (npcView != nullptr)
		{	
			switch (npcView->GetNPCController()->GetSelectBehavior())
			{
			case npcSelectOpenDialog:
				//NPCController, strings, DialogBehavior
				if (!sm_gameInputController->GetMousePressDownLast(LEFT_BUTTON))
					gameView->GetDialogScreenController()->OpenDialog(npcView,
						gameState->GetControlledPCC(),
						gameState->GetPlayerCharactersByTeam(gameState->GetControlledActor()->GetTeam())
						);

				


				break;
			}

			gameView->GetHud()->GetGameInfoPanel()->GetInfoPanel()->SetInfoPanelTarget(npcView->GetNPCController()->GetCharacter());
			gameView->GetHud()->GetGameInfoPanel()->GetInfoPanel()->SetState(infoPanelStateOpened);

		}
	}
	break;
	case characterActionWalkOrBasicAttack:  //usually right click
	{
		targetPlayerCharacterController = NULL;
		pcView = nullptr; //PlayerCharacterView * 
		npcView = nullptr; //NPCView *
		veView=nullptr;
		//LMVector3 walkTarget;

		if (m_playerWorldSelectionController->OpponentTarget(&pcView, selectActionControlledAltSelectOpponent)) {}
		else if (m_playerWorldSelectionController->NPCTarget(&npcView, selectActionControlledAltSelectNeutral)) {}
		//else if (m_playerWorldSelectionController->TeamTarget(&pcView, selectActionControlledAltSelectTeam)) {}
		else if (m_playerWorldSelectionController->NeutralObjectTarget(&veView, selectActionControlledAltSelectNeutralObjects)) {}
		
		else if (m_playerWorldSelectionController->GroundPointWithScreen(&walkTarget, selectActionControlledAltSelectGround))
		{
			if (walkTarget.Magnitude() > 0.001f && walkTarget.y < 0.2f )//mag because we zero if no result in 
			{
				gameView->GetIndicatorController()->SetWalkIndicatorTimer(0.0f);
				//gameState->GetWalkIndicator()->GetPhysicsObject()->SetPosition(D3DXVECTOR3(walkTarget.x, walkTarget.y + 0.1f, walkTarget.z));


				gameView->GetIndicatorController()->GetWalkIndicator()->GetPhysicsObject()->GetPosition()->x = walkTarget.x;
				gameView->GetIndicatorController()->GetWalkIndicator()->GetPhysicsObject()->GetPosition()->y = walkTarget.y + 0.1f;
				gameView->GetIndicatorController()->GetWalkIndicator()->GetPhysicsObject()->GetPosition()->z = walkTarget.z;

				LMVector3 * pos = playerCharacter->GetActor()->GetPhysicsObject()->GetPosition();

				float displacementSquared = abs(pos->x - walkTarget.x) + abs(pos->z - walkTarget.z);

				if (displacementSquared > 0.3f)
				{
					walkTarget.y = 0.0f;

					if (playerCharacter->GetActor()->GetState() == actorAttackMoveCast)
					{
						playerCharacter->GetAttackMoveController()->AttackMoveToTarget(walkTarget.x, walkTarget.y, walkTarget.z);
						//m_amCastTimer.RestartWithDuration(0.3f, true);
						m_mouseUpDuringAMInitialClick = false;
						//whichCastStateIsOurMouseDownFor = actorAttackMoveCast;
					}
					else if (playerCharacter->GetActor()->GetState() == actorDriveByCast)
					{
						playerCharacter->GetAttackMoveController()->DriveByToTarget(walkTarget.x, walkTarget.y, walkTarget.z);
						//m_dbCastTimer.RestartWithDuration(0.3f, true);
						m_mouseUpDuringAMInitialClick = false;
						//whichCastStateIsOurMouseDownFor = actorDriveByCast;
					}
					else
					{
						if (m_mouseUpDuringAMInitialClick == false)
						{
							if (playerCharacter->GetAttackMoveController()->GetState() != attackMoveStateStandby)
							{
								playerCharacter->GetAttackMoveController()->NewTarget(walkTarget.x, walkTarget.y, walkTarget.z);
							}
						}
						else if (m_mouseUpDuringAMInitialClick == true)
						{
							//regular moves force end Attack Move and call ActionWalk
							/*
							if (m_dbCastTimer.GetState() == timerFinished
							&& m_amCastTimer.GetState() == timerFinished)
							{
							}*/

							//playerCharacterController->GetAttackMoveController()->ForceStandby();

							tempVec3.x = walkTarget.x;
							tempVec3.y = walkTarget.y;
							tempVec3.z = walkTarget.z;

							//whichCastStateIsOurMouseDownFor = actorWalking;
							playerCharacter->ActionWalkOrBasicAttack(*gameState->GetGameElapsedTime(), &tempVec3); //usually right click
						}
					}
				}
			}
		}
	}
	break;
	case characterActionStop: 
		playerCharacter->ActionStop();
	break;
	case characterActionAttackMove: 
		playerCharacter->ActionAttackMove();
	break;
	case characterActionDriveByMove: 
		playerCharacter->ActionDriveBy();
	break;
	case characterActionCastRecall: 
		((CoreCharacter*)gameState->GetControlledPCC()->GetCharacter())->ActionCastRecall(*gameState->GetGameElapsedTime());
	break;
	case characterActionCastSleep: 
		((CoreCharacter*)gameState->GetControlledPCC()->GetCharacter())->ActionCastSleep(*gameState->GetGameElapsedTime());
	break;
	case characterActionCastAbility1: 
		playerCharacter->ActionCastAbility(actionCastAbility1, 1, *gameState->GetGameElapsedTime(), gameState->ActorsForSide(teamSideFriendly), gameState->ActorsForSide(teamSideOpponent), gameState->GetTargetableNPCs());
	break;
	case characterActionCastAbility2:
		playerCharacter->ActionCastAbility(actionCastAbility2, 2, *gameState->GetGameElapsedTime(), gameState->ActorsForSide(teamSideFriendly), gameState->ActorsForSide(teamSideOpponent), gameState->GetTargetableNPCs());
	break;
	case characterActionCastAbility3:
		playerCharacter->ActionCastAbility(actionCastAbility3, 3, *gameState->GetGameElapsedTime(), gameState->ActorsForSide(teamSideFriendly), gameState->ActorsForSide(teamSideOpponent), gameState->GetTargetableNPCs());
	break;
	case characterActionCastAbility4:
		playerCharacter->ActionCastAbility(actionCastAbility4, 4, *gameState->GetGameElapsedTime(), gameState->ActorsForSide(teamSideFriendly), gameState->ActorsForSide(teamSideOpponent), gameState->GetTargetableNPCs());
	break;
	case characterActionCastAbility5:
		playerCharacter->ActionCastAbility(actionCastAbility5, 5, *gameState->GetGameElapsedTime(), gameState->ActorsForSide(teamSideFriendly), gameState->ActorsForSide(teamSideOpponent), gameState->GetTargetableNPCs());
	break;
	case characterActionCastAbility6:
		playerCharacter->ActionCastAbility(actionCastAbility6, 6, *gameState->GetGameElapsedTime(), gameState->ActorsForSide(teamSideFriendly), gameState->ActorsForSide(teamSideOpponent), gameState->GetTargetableNPCs());
	break;

	case characterActionInventory1:
		playerCharacter->ActionInventory(actionInventory1, 0, *gameState->GetGameElapsedTime(), gameState->ActorsForSide(teamSideFriendly), gameState->ActorsForSide(teamSideOpponent), gameState->GetTargetableNPCs());
	break;
	case characterActionInventory2:
		playerCharacter->ActionInventory(actionInventory2, 1, *gameState->GetGameElapsedTime(), gameState->ActorsForSide(teamSideFriendly), gameState->ActorsForSide(teamSideOpponent), gameState->GetTargetableNPCs());
	break;
	case characterActionInventory3:
		playerCharacter->ActionInventory(actionInventory3, 2, *gameState->GetGameElapsedTime(), gameState->ActorsForSide(teamSideFriendly), gameState->ActorsForSide(teamSideOpponent), gameState->GetTargetableNPCs());
	break;
	case characterActionInventory4:
		playerCharacter->ActionInventory(actionInventory4, 3, *gameState->GetGameElapsedTime(), gameState->ActorsForSide(teamSideFriendly), gameState->ActorsForSide(teamSideOpponent), gameState->GetTargetableNPCs());
	break;
	case characterActionInventory5:
		playerCharacter->ActionInventory(actionInventory5, 4, *gameState->GetGameElapsedTime(), gameState->ActorsForSide(teamSideFriendly), gameState->ActorsForSide(teamSideOpponent), gameState->GetTargetableNPCs());
	break;
	case characterActionInventory6:
		playerCharacter->ActionInventory(actionInventory6, 5, *gameState->GetGameElapsedTime(), gameState->ActorsForSide(teamSideFriendly), gameState->ActorsForSide(teamSideOpponent), gameState->GetTargetableNPCs());
	break;
	case characterActionInventory7:
		playerCharacter->ActionInventory(actionInventory7, 6, *gameState->GetGameElapsedTime(), gameState->ActorsForSide(teamSideFriendly), gameState->ActorsForSide(teamSideOpponent), gameState->GetTargetableNPCs());
	break;
	case characterActionInventory8:
		playerCharacter->ActionInventory(actionInventory8, 7, *gameState->GetGameElapsedTime(), gameState->ActorsForSide(teamSideFriendly), gameState->ActorsForSide(teamSideOpponent), gameState->GetTargetableNPCs());
	break;
	case characterActionInventory9:
		playerCharacter->ActionInventory(actionInventory9, 8, *gameState->GetGameElapsedTime(), gameState->ActorsForSide(teamSideFriendly), gameState->ActorsForSide(teamSideOpponent), gameState->GetTargetableNPCs());
	break;
	case characterActionInventory0:
		playerCharacter->ActionInventory(actionInventory0, 9, *gameState->GetGameElapsedTime(), gameState->ActorsForSide(teamSideFriendly), gameState->ActorsForSide(teamSideOpponent), gameState->GetTargetableNPCs());
	break;

	}
}


void CharacterInputSet::SpamAction(int action, float deltaTime)
{

}