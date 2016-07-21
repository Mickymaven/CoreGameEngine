#if !defined(GAMECONTROLLER_H)
#define GAMECONTROLLER_H

#include <vector>
using std::vector;

#include <windows.h>

#include "../../../EngineGameModuleDirectX9/src/Application/Globals.h"
#include "../../../EngineGameModuleDirectX9/src/UI/UIElement.h"

#include "../../../CoreGame/src/GameConfiguration.h"
#include "../Application/MsgParams.h"
#include "../GamestateView/AspectProfile.h"

//Modes
#include "StandardMatch5v5.h"
#include "OpenWorld.h"


class GameController
{
private:
	//GAME LOOP HOUSEKEEPING

	LARGE_INTEGER tFrequency;
	LARGE_INTEGER tLastCount;
	LARGE_INTEGER tCurrentCount;
	float timeElapsed;

	bool isDone;

	UIElement * m_loadingBackground;
	
	MobaController * mobaControllerToRun;

	StandardMatch5v5 * standardMatch5v5;
	OpenWorld * openWorld;

	//init values
	LARGE_INTEGER m_initStart;
	LARGE_INTEGER m_initCurrent;
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