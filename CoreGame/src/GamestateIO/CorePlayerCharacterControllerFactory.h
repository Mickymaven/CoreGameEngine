#if !defined(COREPLAYERCHARACTERCONTROLLERFACTORY_H)
#define COREPLAYERCHARACTERCONTROLLERFACTORY_H

#include "../../../EngineMoba/src/GamestateIO/PlayerCharacterControllerFactory.h"

#include "../Gameplay/Characters/CorePlayerCharacterController.h"
#include "CoreCharacterFactory.h"

class CorePlayerCharacterControllerFactory : public PlayerCharacterControllerFactory
{
protected:
	CoreCharacterFactory * m_coreCharacterFactory;
	CorePlayerCharacterController * m_corePlayerCharacterController;
	CoreCharacter * m_coreCharacter;
public:
	CorePlayerCharacterControllerFactory();
	~CorePlayerCharacterControllerFactory();

	bool Init(CoreCharacterFactory * coreCharacterFactory);

	bool ConstructPlayerCharacterController(
		unsigned long * playerID,
		CorePlayerCharacterController ** playerCharacterControllerOut,
		CharacterClassName characterClass,
		Pathfinder * pathfinder,
		vector<ItemName> * itemSet,
		vector<Actor*>* teamActors,
		vector<Actor*>* opponentActors,
		vector<Actor*>* neutralActors, 
		TeamName team,
		string * uniqueName,
		vector<AbilityName> * customAbilities );

};

#endif