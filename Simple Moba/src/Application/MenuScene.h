#if !defined(MENUSCENE_H)
#define MENUSCENE_H

#include <string>
using namespace std;

#include <d3dx9.h>

#include "../../../EngineGameModuleDirectX9/src/View/LMCamera.h"
#include "../../../EngineGameModuleDirectX9/src/UI/UIElement.h"

#include "../../../CoreGame/src/GameConfiguration.h"

#include "../ViewControl/CameraFactory.h"

#include "MenuControllerTarget.h"
#include "MenuSceneSelection.h"



class MenuScene
{
private:
	string m_menuName;

protected:
	static UIElement * m_sharedBackground;
	static D3DXMATRIXA16 m_world;
	static D3DXMATRIX m_scale;
	static D3DXMATRIX m_rotation;
	static D3DXMATRIX m_translation;
	static LMCamera * m_uicamera;

	MenuControllerTarget m_nextTarget;
	MenuSceneSelection m_nextScene;
	GameConfiguration m_gameConfig;
	
public:

	MenuScene(MenuSceneSelection selfSceneEnum, string name, LMCamera * cam);
	virtual ~MenuScene();

	void virtual Update(float fDeltaTime);
	void virtual Render();

	void virtual OnEnterScene();

	MenuControllerTarget CheckTargetController() { return m_nextTarget; }
	MenuSceneSelection CheckTargetScene() { return m_nextScene; }

	GameConfiguration * GetTestGameConfig(int i);
};

#endif