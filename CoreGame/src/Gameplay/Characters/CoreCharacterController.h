#if !defined (CORECHARACTERCONTROLLER_H)
#define CORECHARACTERCONTROLLER_H

#include "CoreCharacter.h"

class CoreCharacterController
{
protected:
	CoreCharacter * m_coreCharacter;

public:
	CoreCharacterController();
	CoreCharacterController(CoreCharacter * character);
	~CoreCharacterController();

	CoreCharacter * GetCoreCharacter();
};

#endif