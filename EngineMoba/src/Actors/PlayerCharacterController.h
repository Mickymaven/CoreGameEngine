#if !defined (PLAYERCHARACTER_H)
#define PLAYERCHARACTER_H

#include <string>
using std::string;

#include "../../../EngineGameModel/src/Maths/LMVector3.h"

#include "../../../EngineMoba/src/Ability/Ability.h"
#include "../../../EngineMoba/src/Pathfinding/Pathfinder.h"
#include "../../../EngineMoba/src/Actors/ActorStats.h"
#include "../../../EngineMoba/src/Actors/Actor.h"
#include "../../../EngineMoba/src/Actor_Control/BattleStateController.h"
#include "../../../EngineMoba/src/Actors/ShopZone.h"



#include "CharacterController.h"

#include "PlayerActionEnum.h"
#include "StatChangeObject.h"




class PlayerCharacterController:  public CharacterController
{
private:
	vector <unsigned int> m_inRangeShops;

public:
	PlayerCharacterController();
	PlayerCharacterController(Character * character);

	virtual ~PlayerCharacterController();

	void Update(float deltaTime);
	
	vector <unsigned int> * GetInRangeShops();

	ShopZone * GetFollowingZone();
};

#endif
