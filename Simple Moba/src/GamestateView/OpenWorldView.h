#if !defined(OPENWORLDVIEW_H)
#define OPENWORLDVIEW_H

#include "../../../CoreGame/src/Gamestate/OpenWorldState.h"
#include "MobaViewState.h"

class OpenWorldView : public MobaViewState
{

protected:
	OpenWorldState * gameState;

public:
	OpenWorldView();
	~OpenWorldView();

	bool Init(GameConfiguration * gameConfiguration);

	bool InitSelectedPhase(int initPhase);
	void SetGameModel(OpenWorldState * gameStateIn); //gameStateIn,


};



#endif