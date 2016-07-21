#if !defined(NPCCONTROLLER_H)
#define NPCCONTROLLER_H


#include "../Item/Item.h"
#include "../Ability/Ability.h"
#include "../Actor_Control/Interaction.h"
#include "../Actor_Control/InteractionController.h"

#include "../../../CoreGame/src/Gameplay/Abilities/BasicAttack.h" //makes engine rely on core game

#include "CharacterController.h"

enum NPCSelectAction

{
	npcSelectOpenDialog,
	npcSelectAllowInfoClick,
	npcSelectDoesNothing,
	npcSelectActionCount
};

class NPCController : public CharacterController
{
private:
protected:
	
	//vector <Item *> m_dropInventory;

	InteractionController * m_interactionControllerInstance;
	DialogBehavior * m_dialogBehaviorInstance;

	LMVector3 m_spawn;

	vector<Interaction*> m_interactions; //iterate over interactions so we can get zones to render in IndicatorController


public:
	NPCController();
	NPCController(Character * character);

	~NPCController();


	void virtual Update(float deltaTime);
	void virtual OnRespawn(float x, float  y, float z);

	LMVector3 *	GetSpawn(int i);

	vector<Interaction*> * GetInteractions();

	//void SetDropInvFromSet(vector<Item*> * set);

	virtual NPCSelectAction GetSelectBehavior();

	InteractionController * GetInteractionController();
	DialogBehavior * GetDialogBehavior();

	//make in derived like this (with derived IC : void SetInteractionControllerSet(vector<InteractionController*> * ic_list);

};

#endif