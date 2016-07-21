#if !defined(OPENWORLD_H)
#define OPENWORLD_H

#include "../../../CoreGame/src/Gamestate/OpenWorldState.h"
#include "../GamestateView/OpenWorldView.h"

#include "MobaController.h"

class OpenWorld : public MobaController
{
private:
	OpenWorldState m_openWorldState;
	OpenWorldState * gameState;

	OpenWorldView m_openWorldView;
	OpenWorldView * gameView;

public:

	OpenWorld();
	~OpenWorld();

	bool Init(GameConfiguration & gameConfigurationIn);
	bool InitControl(GameConfiguration & gameConfigurationIn);

	void Update(float deltaTime);
	void UpdateInput(float deltaTime);
	void UpdateGameEvents(float deltaTime);
	void UpdateRespawnBehavior(float deltaTime);

	void Render();
	void RenderUI();

	//Accessors
	OpenWorldState * GetOpenWorldState();


};


#endif