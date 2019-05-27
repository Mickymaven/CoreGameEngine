#if !defined(GAMECONTROLLER_H)
#define GAMECONTROLLER_H

#include <vector>
using std::vector;

#include <windows.h>

#include "../../../EngineGamePlatform/src/Application/Globals.h"

#include "../../../EngineGameModuleDirectX9/src/Application/GlobalsDX9.h"
#include "../../../EngineGameModuleDirectX9/src/UI/UIElement.h"

#include "../../../CoreGame/src/GameConfiguration.h"

#include "TimestepController.h"

#include "../Application/MsgParams.h"
#include "../GamestateView/AspectProfile.h"

//Modes
#include "StandardMatch5v5.h"
#include "OpenWorld.h"


class GameController : public TimestepController
{
private:
	//GAME LOOP HOUSEKEEPING



	UIElement * m_loadingBackground;
	
	MobaController * mobaControllerToRun;

	StandardMatch5v5 * standardMatch5v5;
	OpenWorld * openWorld;

	//init values

	char m_initBuffer[9000];
	LPD3DXFONT loadFont;
	RECT  fontPos;

public:
	GameController();
	virtual ~GameController();
	INT Run(GameConfiguration * config);
	bool ProcessMessages();
	void Shutdown();

	bool InitLoadingRender();
	void LoadingRender(GameConfiguration * config, int progress, int progressSize, string message);

	void InitDebugPrint();


};

#endif