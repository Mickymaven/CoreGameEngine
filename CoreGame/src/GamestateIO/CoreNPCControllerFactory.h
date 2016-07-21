#if !defined(CORENPCCONTROLLERFACTORY_H)
#define CORENPCCONTROLLERFACTORY_H

#include "../../../EngineMoba/src/GamestateIO/NPCControllerFactory.h"

#include "../Gameplay/Characters/CoreNPCController.h"
#include "CoreCharacterFactory.h"

enum StandardMatch5v5GameUniqueNPC
{
	standardMatch5v5GameUniqueNPCBaseYellow,
	standardMatch5v5GameUniqueNPCBasePurple,
	standardMatch5v5GameUniqueNPCNeutralShop1,
	standardMatch5v5GameUniqueNPCAngryCat,
	standardMatch5v5GameUniqueNPCVisionOwl,
	standardMatch5v5GameUniqueNPCCount
};

class CoreNPCControllerFactory : public NPCControllerFactory
{
protected:
	CoreCharacterFactory * m_coreCharacterFactory;
	CoreCharacter * m_constructedCoreCharacter;
	CoreNPCController * m_NPC;

public:
	CoreNPCControllerFactory();
	~CoreNPCControllerFactory();

	bool Init(CoreCharacterFactory * coreCharacterFactory);

	bool ConstructNPCController(
		CoreNPCController ** npcOut,
		LMVector3 * position,
		StandardMatch5v5GameUniqueNPC id,
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
};

#endif