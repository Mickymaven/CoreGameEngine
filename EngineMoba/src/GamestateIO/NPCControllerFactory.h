#if !defined (NPCCONTROLLERFACTORY_H)
#define NPCCONTROLLERFACTORY_H

#include "../Actors/NPCController.h"



#include "../../../CoreGame/src/Gameplay/Characters/AngryCat/AngryCat.h"// (forward dependency)
#include "../../../CoreGame/src/Gameplay/Characters/VisionOwl/VisionOwl.h"// (forward dependency)


#include "../../../CoreGame/src/Gameplay/Characters/CharacterData.h"// (forward dependency)

//enums
#include "../../../CoreGame/src/Gameplay/Characters/CharacterClassName.h"//(forward dependency)

#include "CharacterControllerFactory.h"



//you dont want to do this if you have derived NPCControllers
//must implement derived NPCControllerFactory with your implementation (use int id as your enum)

class NPCControllerFactory : public CharacterControllerFactory
{
protected:
	NPCController * m_NPC;

	CharacterData m_characterData;//todo remove

public:
	NPCControllerFactory();
	~NPCControllerFactory();

	bool Init(CharacterFactory * characterFactory);

	bool ConstructNPC(
		NPCController ** npcOut,
		LMVector3 * position,
		int id,
		Pathfinder * pathfinder,
		vector<Actor*>* teamActors,
		vector<Actor*>* opponentActors,
		vector<Actor*>* neutralActors,
		CharacterClassName characterClass,
		vector<ItemName> * itemSet,
		bool targetable,
		TeamName team,
		string * uniqueName,
		vector<AbilityName> * customAbilities);

	//bool InitAbilities?
};

#endif
