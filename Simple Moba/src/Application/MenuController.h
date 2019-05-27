#if !defined(MENUCONTROLLER_H)
#define MENUCONTROLLER_H

#include "../../../EngineGameModuleDirectX9/src/View/LMCamera.h"
#include "../../../CoreGame/src/GameConfiguration.h"
#include "MenuScene.h"
#include "MenuSceneIntro.h"
#include "MenuSceneNormalGameLobby.h"
#include "../../../EngineGameModuleDirectX9/src/Application/GlobalsDX9.h"
#include "MenuControllerTarget.h"
#include "MenuSceneSelection.h"

class MenuController
{
private:
	MenuSceneIntro * m_pIntroMenu;
	MenuScene * m_pHomeMenu;
	MenuScene * m_pPlayMenu;
	MenuSceneNormalGameLobby * m_pNormalGameLobbyMenu;

	MenuControllerTarget m_menuControllerTarget;
	MenuSceneSelection currentState;


	CameraFactory m_cameraFactory;
	LMCamera m_uicamera;

	GameConfiguration * m_pGameConfig;

	bool isDone;


public:
	MenuController();
	virtual ~MenuController();
	bool Init();
	void Reset();

	bool InitMenu(MenuSceneSelection menuSceneEnum);

	MenuControllerTarget Run();
	void Update(float deltaTime);
	void Render();

	MenuScene * GetMenu(MenuSceneSelection name);
	GameConfiguration * GetGameConfig() { return m_pGameConfig; }

	void SetMenu(MenuSceneSelection state);
};

#endif
