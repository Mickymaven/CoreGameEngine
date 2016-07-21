#if !defined(CUSTOMMATCHSTATE_H)
#define CUSTOMMATCHSTATE_H

#include "../../../EngineMoba/src/Gamestate/MobaState.h"

#include "CoreGameState.h"

class CustomMatchState : public CoreGameState
{
protected:
	TeamName m_winner;

public:
	CustomMatchState();
	~CustomMatchState();

	bool InitSelectedPhase(int initPhase);

};

#endif