#if !defined (INTERACTIONCONTROLLER_H)
#define INTERACTIONCONTROLLER_H

#include <vector>
using namespace std;

#include "../Actors/Actor.h"
#include "Interaction.h"
#include "DialogBehavior.h"
#include "../Actors/TradeInventory.h" //should init inv from here

enum InteractionBehavior
{
	ibDialogStandby,
	ibInitialDialog,
	ibAggressive,
	ibQuest,
	ibReturnDialog,
	ibQuestCompleteStandby,
	ibQuestRewardDialog,
	ibPostRewardInactive,
	ibCount
};

class InteractionController
{
private:
protected:
	InteractionBehavior m_state;
	Interaction * m_stateInstance;
	Actor * m_actor;
	Character * m_character;

public:
	/*
	InteractionController();
	InteractionController(NPC * npc);
	~InteractionController();
	*/


	void virtual Update(float deltaTime) = 0; //we want this class to be an abstract base class


	virtual void OnHit(VitalEntity * owner)=0;


	virtual DialogScreenData * ActionRequestDialogScreen()=0;
	//virtual int ActionRequestDialogEntryPoint()=0;


	//InteractionBehavior GetInteractionController();

	InteractionBehavior GetState();

	virtual DialogBehavior * GetDialogBehavior()=0;

	virtual void ActionEvent(int index)=0;

	void SetState(InteractionBehavior state);


};

#endif