#include "VisionOwlStandard1InteractionController.h"

VisionOwlStandard1InteractionController::VisionOwlStandard1InteractionController()
{
}

VisionOwlStandard1InteractionController::~VisionOwlStandard1InteractionController()
{
}

bool VisionOwlStandard1InteractionController::Init(
		Character * character,
		AggressionState * aggressionState,
		VisionOwlDialogBehavior * visionOwlDialogBehavior,
		DialogStandbyBehavior * dialogStandbyBehavior)
{
	if (!VisionOwlInteractionController::Init(character,aggressionState,visionOwlDialogBehavior,dialogStandbyBehavior)) return false;

	m_despawnTarget.x = 0.0f;
	m_despawnTarget.y = 0.0f;
	m_despawnTarget.z = 0.0f;

	m_state = ibDialogStandby;
	m_stateInstance = aggressionState;

	m_pathController = character->GetPathController();

	character->GetTradeInventory()->AddCallbackOnConfirm(std::bind(&VisionOwlStandard1InteractionController::CallbackConfirmTrade, this));

	
	m_actor->SetIntargetable();

	return true;
}

bool VisionOwlStandard1InteractionController::InitQuestInformation(OwlQuestStandard1 * questS1)
{
	m_questS1 = questS1;
	return true;
}

void VisionOwlStandard1InteractionController::Update(float deltaTime)
{
	//m_stateInstance->Update(deltaTime);

	switch (m_state)
	{
	case ibAggressive: Aggressive(deltaTime); break;
	case ibPostRewardInactive: PostRewardInactive(deltaTime); break;
	};
}

void VisionOwlStandard1InteractionController::OnEnterDialogStandby()
{
	m_state = ibDialogStandby;
	m_stateInstance = m_dialogStandbyBehavior;
	m_actor->SetIntargetable();

	m_questS1->ActionPreQuest();
}

void VisionOwlStandard1InteractionController::DialogStandby(float deltaTime)
{

}

void VisionOwlStandard1InteractionController::OnExitDialogStandby()
{

}


void VisionOwlStandard1InteractionController::OnEnterInitialDialog()
{
	m_state = ibInitialDialog;
	//m_stateInstance = m_;
}

void VisionOwlStandard1InteractionController::InitialDialog(float deltaTime)
{

}

void VisionOwlStandard1InteractionController::OnExitInitialDialog()
{

}

void VisionOwlStandard1InteractionController::OnEnterAggressive()
{
	m_state = ibAggressive;
	m_stateInstance = m_aggressionState;

	m_actor->SetActive();

	m_aggressionState->OnHit(m_visionOwlDialogBehavior->GetClient()->GetCharacter()->GetActor());

}

void VisionOwlStandard1InteractionController::Aggressive(float deltaTime)
{
	m_aggressionState->Update(deltaTime);

	if (m_actor->GetStats()->GetHealth() / m_actor->GetStats()->GetMaxHealth() < 0.3f)
	{
		OutputDebugString("VisionOwlHealth < 30%\n");
		OnExitAggressive();
		OnEnterQuestCompleteStandby();
	}
}

void VisionOwlStandard1InteractionController::OnExitAggressive()
{
	m_actor->SetIntargetable();
}

void VisionOwlStandard1InteractionController::OnEnterQuest()
{
	m_state = ibQuest;
	//m_stateInstance = m_;

	m_questS1->ActionStartQuest();
}

void VisionOwlStandard1InteractionController::Quest(float deltaTime)
{

}

void VisionOwlStandard1InteractionController::OnExitQuest()
{
	m_questS1->ActionEndQuest();
}


void VisionOwlStandard1InteractionController::OnEnterReturnDialog()
{
	m_state = ibReturnDialog;
	//m_stateInstance = m_;
}

void VisionOwlStandard1InteractionController::ReturnDialog(float deltaTime)
{

}

void VisionOwlStandard1InteractionController::OnExitReturnDialog()
{

}


void VisionOwlStandard1InteractionController::OnEnterQuestCompleteStandby()
{
	m_state = ibQuestCompleteStandby;
	//m_stateInstance = m_;


	m_character->GetBattleStateController()->ActionPassive();
	m_visionOwlDialogBehavior->m_openDialogCallback();
}

void VisionOwlStandard1InteractionController::QuestCompleteStandby(float deltaTime)
{

}

void VisionOwlStandard1InteractionController::OnExitQuestCompleteStandby()
{

}


void VisionOwlStandard1InteractionController::OnEnterQuestRewardDialog()
{
	m_state = ibQuestRewardDialog;
	//m_stateInstance = m_;
	//if (m_visionOwlDialogBehavior->m_openDialogCallback)

	m_character->GetTradeInventory()->PushActivateShopInventory(m_questS1->GetInventory(owlQuestS1InvReward), true);

	m_visionOwlDialogBehavior->m_openDialogCallback();

}

void VisionOwlStandard1InteractionController::QuestRewardDialog(float deltaTime)
{

}

void VisionOwlStandard1InteractionController::OnExitQuestRewardDialog()
{
	
}


void VisionOwlStandard1InteractionController::OnEnterPostRewardInactive()
{
	m_state = ibPostRewardInactive;
	m_character->GetPathController()->WalkToPosition(true,
		&m_despawnTarget,
		m_actor->GetPhysicsObject()->GetPosition()
		);
}

void VisionOwlStandard1InteractionController::PostRewardInactive(float deltaTime)
{
	m_pathController->Update(deltaTime);
}

void VisionOwlStandard1InteractionController::OnExitPostRewardInactive()
{

}

void VisionOwlStandard1InteractionController::ExitCurrentState()
{
	switch (m_state)
	{
	case ibDialogStandby: OnExitDialogStandby(); break;
	case ibInitialDialog: OnExitInitialDialog(); break;
	case ibAggressive: OnExitAggressive(); break;
	case ibQuest: OnExitQuest(); break;
	case ibReturnDialog: OnExitReturnDialog(); break;
	case ibQuestCompleteStandby: OnExitQuestCompleteStandby(); break;
	case ibQuestRewardDialog: OnExitQuestRewardDialog(); break;
	case ibPostRewardInactive: OnExitPostRewardInactive(); break;
	}
}

void VisionOwlStandard1InteractionController::OnHit(VitalEntity * owner)
{
	//m_aggressionState->OnHit(owner);

	//m_aggressionState->OnHit(owner);

	//How will we be triggering on combat
	//Maybe this npc will be untargetable until we are in combat
	//and then we will be using another on click system on them to
	//enter dialog before any combat happens
}

DialogScreenData * VisionOwlStandard1InteractionController::ActionRequestDialogScreen()//is used confirmed
{
	if (m_state == ibQuest)
	{
		vector<int> indicesToKill;
		vector<int> countOfEachItem;
	
		int itemsNeeded = 2;
		int itemsFound = CountTools(&indicesToKill, &countOfEachItem);
		
		if (itemsFound >= itemsNeeded)//maybe conditional is 'min one of each owl item type'
		{
			RemoveTools(&indicesToKill);
			
			OutputDebugString("Check quest complete = true \n");

			ExitCurrentState();
			OnEnterReturnDialog();

			return &m_visionOwlDialogBehavior->GetDialogScreens()->at(visionOwlDialogScreenQuestReturnWin);
		}
		else return &m_visionOwlDialogBehavior->GetDialogScreens()->at(visionOwlDialogScreenQuestReturnIncomplete);


	}
	else return m_visionOwlDialogBehavior->GetEntryOptions(GetState());

	OutputDebugString("VisionOwlStandard1InteractionController::ActionRequestDialogScreen()\n we should of given a method of getting the dialog screen. something wrong with conditionals?\n");

	return m_visionOwlDialogBehavior->GetEntryOptions(GetState());

}


void VisionOwlStandard1InteractionController::ExitInitialDialog()
{
	1;
}

void VisionOwlStandard1InteractionController::ActionEvent(int index)
{
	switch (index)
	{
	case visionOwlDialogEventCancelQuest: ActionTakeToolsOnCancel(); ExitCurrentState(); OnEnterDialogStandby(); break;
	case visionOwlDialogEventStartQuest:	ExitCurrentState(); OnEnterQuest(); break;
	case visionOwlDialogEventQuestEndTransition: ExitCurrentState(); OnEnterQuestRewardDialog(); break;
	case visionOwlDialogEventStartCombat:	ExitCurrentState(); OnEnterAggressive(); break;
	case visionOwlDialogEventDespawn: ExitCurrentState(); OnEnterPostRewardInactive(); break;

		//case visionOwlDialogEventOpenTrade:		ExitCurrentState(); OnEnterQuestRewardDialog();  OutputDebugString("VisionOwl OnEnterRewardDialog"); break;
	case visionOwlDialogEventCount:			default: break; return;
	}
}

void VisionOwlStandard1InteractionController::ActionOnRespawn(float x, float y, float z)
{
	ExitCurrentState();
	OnEnterInitialDialog();
}

void VisionOwlStandard1InteractionController::ActionTakeToolsOnCancel()
{
	vector<int> indicesToKill;

	CountTools(&indicesToKill, nullptr);
	RemoveTools(&indicesToKill);
}

int VisionOwlStandard1InteractionController::CountTools(vector<int> * itemIndicesOut, vector<int> * countOfEachItem)
{
	//PlayerCharacterController * client = m_visionOwlDialogBehavior->GetClient();
	vector<Item*> * clientInv = m_visionOwlDialogBehavior->GetClient()->GetCharacter()->GetInventory();
	
	int totalItems = 0;

	int drillsFound = 0;
	int hammersFound = 0;

	for (unsigned int i = 0; i < clientInv->size(); i++)
	{
		if (clientInv->at(i) != NULL)
		{
			switch (clientInv->at(i)->GetItemClass())
			{
			case itemOwlDrill: ++drillsFound; itemIndicesOut->push_back(i);  break;
			}
		}
	}

	if (countOfEachItem != nullptr)
	{
		//add item counts as vector
		countOfEachItem->resize(1);

		countOfEachItem->at(0) = drillsFound;
		totalItems+= drillsFound;
	}

	return totalItems;
}

void VisionOwlStandard1InteractionController::RemoveTools(vector<int> * itemIndices)
{
	vector<Item*> * clientInv = m_visionOwlDialogBehavior->GetClient()->GetCharacter()->GetInventory();

	for (unsigned int i = 0; i < itemIndices->size(); i++)
	{
		clientInv->at(itemIndices->at(i)) = nullptr;
	}
}

void VisionOwlStandard1InteractionController::CallbackConfirmTrade()
{
	if (m_state == ibQuestRewardDialog)
	{
		OnExitQuestRewardDialog();
		OnEnterPostRewardInactive();
	}
}

