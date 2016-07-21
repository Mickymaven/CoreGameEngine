#if !defined(COREPLAYERCHARACTERCONTROLLER_H)
#define COREPLAYERCHARACTERCONTROLLER_H

#include "../../../../EngineMoba/src/Actors/PlayerCharacterController.h"

#include "CoreCharacterController.h"
#include "CoreCharacter.h"

class CorePlayerCharacterController: public PlayerCharacterController, public CoreCharacterController
{
public:
	CorePlayerCharacterController();
	CorePlayerCharacterController( CoreCharacter *  character );
	~CorePlayerCharacterController();

};

#endif