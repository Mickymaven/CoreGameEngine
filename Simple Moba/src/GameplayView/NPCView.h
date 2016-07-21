#if !defined(NPCVIEW_H)
#define NPCVIEW_H

#include "ActorView.h"
#include "../../../EngineMoba/src/Actors/NPCController.h"
#include "Abilities/BasicAttackView.h"


#include "CharacterControllerView.h"

//About to use this class to for View specialisation for Actor and NPC Controller Member Elements

class NPCView : public CharacterControllerView
{
protected:
	NPCController * m_npcController;
	//BasicAttackView m_basicView;
public:

	NPCView();
	NPCView(NPCController * npcController, CharacterView * characterView);
	~NPCView();

	void Render();

	NPCController * GetNPCController();


};

#endif