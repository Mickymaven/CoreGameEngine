#if !defined(MENUSCENENORMALGAMELOBBY_H)
#define MENUSCENENORMALGAMELOBBY_H

#include <string>
using std::string;

#include <dinput.h>

#include "../../../EngineGameModuleDirectX9/src/UI/LMButton.h"
#include "../../../CoreGame/src/GameConfiguration.h"

#include "MenuScene.h"

#include "../../../EngineGameModel/src/Utility/LMTimer.h"


#include "../../../EngineGameModuleDirectX9/src/ControlHeader.h"

#include "../../../EngineGamePlatform/src/Application/Globals.h"

class MenuSceneNormalGameLobby: public MenuScene
{
	
private:

	char buffertext[1000];

	LPD3DXFONT m_uxTitleFont;
	RECT m_fontposTitle;

	LPD3DXFONT m_fontCountdown;
	RECT m_positionCountdown;


	//LMButton m_buttonIntroMenu;
	//LMButton m_buttonSelectGrey;
	//LMButton m_buttonSelectLoost;
	//LMButton m_buttonSelectTypy;
	//LMButton m_buttonSelectShork;

	LMButton m_buttonLockCharacter;

	//lobby base class stuff

	LMTimer m_timer;

	GameConfiguration m_gameConfigResult;
	GameConfiguration * m_pointerToGameConfig;


public:
	MenuSceneNormalGameLobby(MenuSceneSelection selfSceneEnum, string name, LMCamera * cam);
	~MenuSceneNormalGameLobby();

	bool Init();

	void Update(float deltaTime) override;
	void Render() override;

	void OnEnterScene() override;

	GameConfiguration * GetGameConfig();
};



#endif