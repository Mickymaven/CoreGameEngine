#if !defined (PLAYERCHARACTERCONTROLLERFACTORY_H)
#define PLAYERCHARACTERCONTROLLERFACTORY_H

#include "../Actors/PlayerCharacterController.h"


//#include "../../../CoreGame/src/Gameplay/Characters/CharacterData.h"// (forward dependency)

//enums
//#include "../../../CoreGame/src/Gameplay/Characters/CharacterClassName.h"//(forward dependency)

#include "CharacterControllerFactory.h"


class PlayerCharacterControllerFactory: public CharacterControllerFactory
{
protected:

	PlayerCharacterController * m_playerCharacter;
	


public:
	PlayerCharacterControllerFactory();
	~PlayerCharacterControllerFactory();

	bool Init(CharacterFactory * characterFactory);

	bool ConstructPlayerCharacter(
		unsigned long * playerID,
		PlayerCharacterController ** playerCharacterControllerOut,
		CharacterClassName characterClass,
		Pathfinder * pathfinder,
		vector<ItemName> * itemSet,
		vector<Actor*>* teamActors,
		vector<Actor*>* opponentActors,
		vector<Actor*>* neutralActors,
		TeamName team,
		string * uniqueName,
		vector<AbilityName> * customAbilities);

};

#endif