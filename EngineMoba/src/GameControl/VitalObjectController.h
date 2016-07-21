#if !defined(VITALOBJECTCONTROLLER_H)
#define VITALOBJECTCONTROLLER_H

//Base class for controllers that handle "objects that change vital entity states" that are handled by VitalEventController

#include "../../../EngineMoba/src/Gamestate/MobaState.h"

class VitalObjectController
{
protected:
	MobaState * gameState;
public:
	VitalObjectController();
	~VitalObjectController();

};

#endif