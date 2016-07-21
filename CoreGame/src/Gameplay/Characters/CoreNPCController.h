#if !defined(CORENPCCONTROLLER_H)
#define CORENPCCONTROLLER_H

#include "../../../../EngineMoba/src/Actors/NPCController.h"

#include "CoreCharacterController.h"
#include "CoreCharacter.h"

class CoreNPCController : public NPCController, public CoreCharacterController
{
public:
	CoreNPCController();
	CoreNPCController(CoreCharacter *  character);
	~CoreNPCController();

	void Update(float deltaTime);

};

#endif