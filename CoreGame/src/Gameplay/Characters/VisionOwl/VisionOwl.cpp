#include "VisionOwl.h"

VisionOwl::VisionOwl(CoreCharacter * character,
	vector<Actor * > * teamActors,
	vector<Actor * > * opponentActors,
	vector<Actor * > * neutralActors) : CoreNPCController(character)
{
	Actor * actor = character->GetActor();

	m_spawn.x = actor->GetPhysicsObject()->GetPosition()->x;
	m_spawn.y = 0.0f;
	m_spawn.z = actor->GetPhysicsObject()->GetPosition()->z;

	m_aggroState.Init(character->GetBattleStateController(), character->GetWalkState(), actor);

	m_interactions.push_back(&m_dialogStandbyBehavior);
	m_interactions.push_back(&m_aggroState);
	m_interactions.push_back(&m_visionOwlDialogBehavior);


	m_visionOwlDialogBehavior.Init(nullptr, nullptr, nullptr);//todo

	//m_s1.Init(m_actor, &m_pathController, &m_tradeInventory, &m_aggroState, &m_visionOwlDialogBehavior, &m_dialogStandbyBehavior);
	//m_voState = &m_s1;
	//m_interactionControllerInstance = m_voState; // todo when voState gets changed this base class copy wont change.

	m_dialogBehaviorInstance = &m_visionOwlDialogBehavior;

	character->GetTradeInventory()->ActionSetMode(tradeInventoryTradeMode);

	*character->GetFollowingZone() = ShopZone(*actor->GetPhysicsObject()->GetPosition(), 10.0f, m_actor->GetUniqueName(), m_actor->GetTeam());
	character->GetTradeInventory()->GetShopZones()->push_back(character->GetFollowingZone());
	
	//m_tradeInventory.AddCallbackOnConfirm(std::bind(&VisionOwlStandard1InteractionController::CallbackConfirmTrade, &m_s1));
	///m_tradeInventory.AddCallbackOnConfirm(std::bind(&VisionOwlInteractionController::CallbackConfirmTrade, &m_voState));

	actor->SetOnHitCallback(std::bind(&VisionOwl::OnHit, this, _1));
}

VisionOwl::~VisionOwl()
{

}



bool VisionOwl::SetInteractionControllersList(vector<VisionOwlInteractionController*>* ic_vo_list)
{
	//This function is so we can get the interaction controllers based on what game mode we are playing.
	//We still want derived classes for making the npc class similar in different modes, however quests do very different stuff per mode
	//we have the mode init us with the quests for this mode which come from Quest config stuff (map-mode objects etc)

	if (ic_vo_list->size() == 0) return false;//list needs to be >1 so npc can use first IC as its AI.

	m_ic_vo_list = ic_vo_list;

	for (unsigned int i = 0; i < ic_vo_list->size(); i++)
	{
		ic_vo_list->at(i)->Init(
			m_character,
			&m_aggroState,
			&m_visionOwlDialogBehavior,
			&m_dialogStandbyBehavior);
	}

	m_voState = m_ic_vo_list->at(0);

	m_interactionControllerInstance = m_voState; // todo when voState gets changed this base class copy wont change.
}


void VisionOwl::Update(float deltaTime)
{
	//we commented stuff as we hope character does this for us now. prob needs fix.

	m_voState->Update(deltaTime);

	CoreNPCController::Update(deltaTime);
}

void VisionOwl::Render()
{
	//m_actor->Render();
	//m_abilities.at(voBasicAttack)->Render();
}

void VisionOwl::OnRespawn(float x, float y, float z)
{
	//todo this onrespawn could easly be base class
	//provided we have code that selects what InteractionState we will be respawning with
	//then we can use base class InteractionState instance pointer to get ActionOnRespawn.
	//char->Function stuff should be something in character that reacts to all character respawn calls

	m_actor->Respawn(x, y, z);

	m_voState->ActionOnRespawn(x, y, z);
	
	//m_s1.ExitCurrentState();
	//m_s1.OnEnterDialogStandby();

	//m_acState.ExitCurrentState();
	//TODO enter a default state

	//m_aggroState.ExitCurrentState();
	//m_aggroState.OnExitAngryStandby();

	m_character->GetBattleStateController()->ActionPassive();

}

void VisionOwl::OnHit(VitalEntity * owner)
{
	m_voState->OnHit(owner);
}

NPCSelectAction VisionOwl::GetSelectBehavior()
{
	OutputDebugString("VisionOwl Get Select Behavior\n");

	switch (m_voState->GetState())
	{
		case ibDialogStandby		:
		case ibQuest				:
		case ibQuestCompleteStandby :
		case ibQuestRewardDialog    : return npcSelectOpenDialog; break;

		case ibInitialDialog        :
		case ibAggressive		    :
		case ibReturnDialog			:

		case ibPostRewardInactive	: return npcSelectAllowInfoClick; break;
	}

	OutputDebugString("BAD STATE IN VISION OWL GETSELECTBEHAVIOR\n");

	return npcSelectAllowInfoClick;
}

