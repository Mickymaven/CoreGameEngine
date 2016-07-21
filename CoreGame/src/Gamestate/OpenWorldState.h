#if !defined(OPENWORLDSTATE_H)
#define OPENWORLDSTATE_H

#include "../Gameplay/ModeConfig/BaseMapConfigForOpenWorld.h"
#include "../../../EngineMoba/src/Gamestate/MobaState.h"
#include "CoreGameState.h"

class OpenWorldState : public CoreGameState
{
	VitalEntity m_chest1;

	BaseMapConfigForOpenWorld * m_ModeMapConfig;

public:
	OpenWorldState();
	~OpenWorldState();

	bool InitSelectedPhase(int initPhase);

	

};

#endif