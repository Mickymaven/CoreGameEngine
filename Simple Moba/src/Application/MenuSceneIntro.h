#if !defined(MENUSCENEINTRO_H)
#define MENUSCENEINTRO_H

#include <string>
using namespace std;

#include "../../../EngineGameModuleDirectX9/src/UI/LMButton.h"
#include "../../../CoreGame/src/GameConfiguration.h"

#include "MenuScene.h"

#include "../../../EngineGamePlatform/src/Application/Globals.h"

#include "../../../EngineGameModuleDirectX9/src/Application/GlobalsDX9.h"

class MenuSceneIntro: public MenuScene
{
	
private:

	RECT m_fontposTitle;
	RECT m_fontPositionX;
	RECT m_fontPositionY;

	LMButton m_buttonLaunch;

	LMButton m_buttonQuickPlay;
	LMButton m_moveScreenTwo;

public:
	MenuSceneIntro(MenuSceneSelection selfSceneEnum, string name, LMCamera * cam);
	virtual ~MenuSceneIntro();

	bool Init();

	void Update(float fDeltaTime) override;
	void Render() override;
	void OnEnterScene() override;


};

#endif
