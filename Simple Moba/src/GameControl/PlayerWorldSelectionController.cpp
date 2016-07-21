#include "PlayerWorldSelectionController.h"

PlayerWorldSelectionController::PlayerWorldSelectionController()
{
}

PlayerWorldSelectionController::~PlayerWorldSelectionController()
{
}

bool PlayerWorldSelectionController::Init(StandardMatch5v5State * coreGameStateIn, MobaViewState * mobaViewStateIn)
{
	gameModel = coreGameStateIn;
	gameView = mobaViewStateIn;

	m_questItemController.Init(gameModel->GetItemFactory());


	m_opponent = nullptr;
	m_team = nullptr;
	m_neutral = nullptr;

	m_questItem = nullptr;
	m_questView = nullptr;
	m_questViewItemIndex = 0;

	m_neutralObject = nullptr;

	tempActorTarget = nullptr;
	tempVitalEntityTarget = nullptr;

	m_lastCastTestResult = castTestError;

	return true;
}

void PlayerWorldSelectionController::Update(float deltaTime)
{
	tempActorTarget = nullptr;
	tempVitalEntityTarget = nullptr;

	m_cameraRayMade = false;
	m_opponentChecked = false;
	m_teamChecked = false;
	m_neutralsChecked = false;
	m_questItemsChecked = false;
	m_neutralObjectsChecked = false;
	m_groundChecked = false;
}

void PlayerWorldSelectionController::SelectAction(SelectActions selectAction)
{



	// we will fallthrough cases later, here we need to use the right parameter
	switch (selectAction)
	{
	case selectActionQuerySelectTeam: //falls
	case selectActionControlledSelectTeam: tempActorTarget = m_team->GetCharacterView()->GetActorView()->GetActor(); break;
	case selectActionQuerySelectOpponent: //falls
	case selectActionControlledSelectOpponent: tempActorTarget = m_opponent->GetCharacterView()->GetActorView()->GetActor(); break;
	case selectActionQuerySelectNeutral: //falls
	case selectActionControlledSelectNeutral: tempActorTarget = m_neutral->GetCharacterView()->GetActorView()->GetActor(); break;
	//case selectActionControlledSelectNeutralObjects
	//case selectActionControlledSelectQuestItems
	//case selectActionControlledSelectGround:tempActorTarget = nullptr; break;

	case selectActionControlledAltSelectTeam: tempVitalEntityTarget = m_team->GetCharacterView()->GetActorView()->GetVitalEntity(); break;
	case selectActionControlledAltSelectOpponent: tempVitalEntityTarget = m_opponent->GetCharacterView()->GetActorView()->GetVitalEntity(); break;
	case selectActionControlledAltSelectNeutral: tempVitalEntityTarget = m_neutral->GetCharacterView()->GetActorView()->GetVitalEntity(); break;
	case selectActionControlledAltSelectNeutralObjects: tempVitalEntityTarget = m_neutralObject->GetVitalEntity(); break;
	//case selectActionControlledAltSelectNeutralObjects,
	//case selectActionControlledAltSelectQuestItems,
	//case selectActionControlledAltSelectGround,
	}

	switch (selectAction)
	{
	//case selectActionQuerySelectQuestItems:break;
	//case selectActionQuerySelectNeutralObjects:
	
	case selectActionQuerySelectTeam:
	case selectActionQuerySelectGround:
	case selectActionQuerySelectOpponent:
	case selectActionQuerySelectNeutral:

		m_lastCastTestResult = gameModel->GetControlledCharacter()->SelectCastTest(
			*gameModel->GetGameElapsedTime(),
			gameView->GetIndicatorController()->GetIndicatorDirectionVector(),
			gameView->GetIndicatorController()->GetMousePointVector(),
			tempActorTarget,
			gameModel->ActorsForSide(teamSideFriendly),
			gameModel->ActorsForSide(teamSideOpponent),
			gameModel->GetTargetableNPCs());

		break;

	//case selectActionControlledSelectNeutralObjects,
	case selectActionControlledSelectQuestItems:
	{
		if (m_questView != nullptr)
		{
			m_questItemController.SelectItem(m_questView->GetQuest(), gameModel->GetControlledCharacter(), m_questViewItemIndex);
		}
	} break;
	case selectActionControlledSelectTeam://Intentional fall
	case selectActionControlledSelectOpponent://Intentional fall
	case selectActionControlledSelectNeutral://Intentional fall
	//case selectActionControlledSelectNeutralObjects://intentional fall (well target var is actor cant single target)
	case selectActionControlledSelectGround://Intentional fall
		
		//casting single target when clicking ground bug
		//
		//ground is selected for point cast for example, but single target is recieving tempActorTarget
		//which is reusing selections on team members and targeting our team. (we could recheck again in ability but that is too much bloat).
		//we need to create flow where single target cast happens differently through here.
		//but hey setting tempActorTarget, tempVitalEntityTarget to nullptr in Update() did fix the problem
		//
		//diffent flow idea:
		//perhaps we should see if we are in a cast state before we even allow testing which could save us some crunch.
		//alltough we might not save much as the cursor state typically needs to test against most things anyway
		//but stops when it first finds a thing


		gameModel->GetControlledCharacter()->ActionSelectWithMouse(
			*gameModel->GetGameElapsedTime(),
			gameView->GetIndicatorController()->GetIndicatorDirectionVector(),
			gameView->GetIndicatorController()->GetMousePointVector(),
			tempActorTarget,
			gameModel->ActorsForSide(teamSideFriendly),
			gameModel->ActorsForSide(teamSideOpponent),
			gameModel->GetTargetableNPCs());
		break;
	
	//ALT SELECT CASES
	//case selectActionControlledAltSelectQuestItems:
	//case selectActionControlledAltSelectGround:

	case selectActionControlledAltSelectTeam:break;
	case selectActionControlledAltSelectOpponent://Intentional fall
	case selectActionControlledAltSelectNeutral://Intentional fall
	case selectActionControlledAltSelectNeutralObjects://Intentional fall
		gameModel->GetControlledCharacter()->ActionWalkOrBasicAttack(*gameModel->GetGameElapsedTime(), tempVitalEntityTarget);

	case selectActionControlledAltSelectGround:break;

	case selectActionNothing:case selectActionsCount:default:break;
	}
}

void PlayerWorldSelectionController::GenerateCameraRay()
{
	if (!m_cameraRayMade) GetRayFromLMCamera(
		gameView->GetCameraDirector()->GetPointerToCurrentCamera(),
		g_mouseClientPosition.x,
		g_mouseClientPosition.y,
		point1,
		point2);
}

void PlayerWorldSelectionController::CopyCameraRayToTempLocal()
{
	point1TempLocal = point1;
	point2TempLocal = point2;
}

bool PlayerWorldSelectionController::Pick(D3DXMATRIX * world, LMMesh * mesh, int index)
{
	TransformRayByMeshWorldMatrix(&point1TempLocal, &point2TempLocal, world);
	
	if (PickFromSprite(&ResultPoint, mesh, point1TempLocal, point2TempLocal))
	{
		m_tempOutIndex = index;
		return true;
	}

	return false;
}

bool PlayerWorldSelectionController::TestActorControllerViews(vector <CharacterControllerView * > * views)
{
	GenerateCameraRay();

	for (unsigned int i = 0; i < views->size(); i++)
	{
		if (views->at(i)->GetCharacterView()->GetActorView()->GetActor()->GetVitalEntityState() != vitalEntityStateInactive)
		{
			CopyCameraRayToTempLocal();

			if ( Pick(views->at(i)->GetCharacterView()->GetActorView()->GetWorldMatrix(), views->at(i)->GetCharacterView()->GetActorView()->GetLMMesh(), i))
				return true;
		}
	}

	return false;
}

bool PlayerWorldSelectionController::TestVitalEntityViews(vector<VitalEntityView*>* views)
{
	GenerateCameraRay();

	for (unsigned int i = 0; i < views->size(); i++)
	{
		if (views->at(i)->GetVitalEntity()->GetVitalEntityState() != vitalEntityStateInactive)
		{
			CopyCameraRayToTempLocal();

			if (Pick(views->at(i)->GetWorldMatrix(), views->at(i)->GetLMMesh(), i))
				return true;
		}
	}

	return false;
}

bool PlayerWorldSelectionController::TestItemEntityViews(vector<ItemEntityView>* views)
{
	GenerateCameraRay();

	for (unsigned int i = 0; i < views->size(); i++)
	{
		CopyCameraRayToTempLocal();

		if (Pick(views->at(i).GetVitalEntityView()->GetWorldMatrix(), views->at(i).GetVitalEntityView()->GetLMMesh(), i))
			return true;
	}

	return false;
}

bool PlayerWorldSelectionController::TestSpriteViewForPosition(SpriteView * spriteView)
{
	GenerateCameraRay();
	CopyCameraRayToTempLocal();

	if (Pick(spriteView->GetWorldMatrix(), spriteView->GetLMMesh(), 0))
	{
		return true;
	}

	return false;
}


bool PlayerWorldSelectionController::OpponentTarget(PlayerCharacterView ** targetView, SelectActions action)
{
	if (!m_opponentChecked)
	{
		m_opponentChecked = true;

		if (TestActorControllerViews((vector <CharacterControllerView * > *)gameView->GetOpponentTeamViews()))
		{
			m_opponent = gameView->GetOpponentTeamViews()->at(m_tempOutIndex);
		}
		else m_opponent = nullptr;
	}

	*targetView = m_opponent;	//whether or not we checked list time we want to set output params and perform actions that were requested

	if (m_opponent == nullptr) return false; //else { SelectAction(action); return true; }
	SelectAction(action); return true;
}

bool PlayerWorldSelectionController::TeamTarget(PlayerCharacterView ** targetView, SelectActions action)
{
	if (!m_teamChecked)
	{
		m_teamChecked = true;

		if (TestActorControllerViews((vector <CharacterControllerView * > *)gameView->GetPlayerTeamViews()))
		{
			m_team = gameView->GetPlayerTeamViews()->at(m_tempOutIndex);
		}
		else m_team = nullptr;
	}

	*targetView = m_team;	//whether or not we checked list time we want to set output params and perform actions that were requested

	if (m_team == nullptr) return false; //else { SelectAction(action); return true; }
	SelectAction(action); return true;
}

bool PlayerWorldSelectionController::NPCTarget(NPCView ** targetView, SelectActions action)
{
	if (!m_neutralsChecked)
	{
		m_neutralsChecked = true;

		if (TestActorControllerViews((vector <CharacterControllerView * > *)gameView->GetNPCViews()))
		{
			m_neutral = gameView->GetNPCViews()->at(m_tempOutIndex);
		}
		else m_neutral = nullptr;
	}

	*targetView = m_neutral;	//whether or not we checked list time we want to set output params and perform actions that were requested

	if (m_neutral == nullptr) return false; //else { SelectAction(action); return true; }
	SelectAction(action); return true;
}

bool PlayerWorldSelectionController::NeutralObjectTarget(VitalEntityView ** targetView, SelectActions action)
{
	if (!m_neutralObjectsChecked)
	{
		m_neutralObjectsChecked = true;

		if (TestVitalEntityViews(gameView->GetVitalEntityViews()))
		{
			m_neutralObject = gameView->GetVitalEntityViews()->at(m_tempOutIndex);
		}
		else m_neutralObject = nullptr;
	}

	*targetView = m_neutralObject;	//whether or not we checked list time we want to set output params and perform actions that were requested

	if (m_neutralObject == nullptr) return false; //else { SelectAction(action); return true; }
	SelectAction(action); return true;
}

bool PlayerWorldSelectionController::QuestItemTarget(ItemEntityView ** targetView, SelectActions action)
{
	if (!m_questItemsChecked)
	{
		m_questItemsChecked = true;


		vector<QuestView*> * questViews = gameView->GetQuestViews();


		for (unsigned int questCount = 0; questCount < questViews->size(); questCount++)
		{
			if (TestItemEntityViews(questViews->at(questCount)->GetItemViews()))
			{
				m_questItem = &questViews->at(questCount)->GetItemViews()->at(m_tempOutIndex);
				m_questViewItemIndex = m_tempOutIndex;
				m_questView = questViews->at(questCount);
				
				break;
			}
			else m_questItem = nullptr;
		}
	}

	*targetView = m_questItem;	//whether or not we checked list time we want to set output params and perform actions that were requested

	if (m_questItem == nullptr) return false; //else { SelectAction(action); return true; }
	SelectAction(action); return true;
}

bool PlayerWorldSelectionController::GroundPointWithScreen(LMVector3 * targetPosition, SelectActions action)
{
	if (!m_groundChecked)
	{
		m_groundChecked = true;
		m_validgroundPoint = false;

		if (TestSpriteViewForPosition(gameView->GetGameMapView()->GetGroundView()))
		{
			m_groundPos.x = ResultPoint.x;
			m_groundPos.y = ResultPoint.y;
			m_groundPos.z = ResultPoint.z;
			if (targetPosition != nullptr) *targetPosition = m_groundPos;//can pass in nullptr to this function 
			m_validgroundPoint = true;
		}
		else { m_validgroundPoint = false; return false; }
	}

	if (m_validgroundPoint)
	{
		SelectAction(action); return true;
	}
	return false;//!m_validgroundPoint as default return
}

CastTestResult PlayerWorldSelectionController::GetCastTestResult()
{
	return m_lastCastTestResult;
}
