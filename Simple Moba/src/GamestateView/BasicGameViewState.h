#if !defined(BASICGAMEVIEWSTATE_H)
#define BASICGAMEVIEWSTATE_H

#include "../../../EngineGameModel/src/Gamestate/GameStateObject.h"

#include "../../../EngineGameModuleDirectX9/src/Lighting/GameLightingController.h"
#include "../../../EngineGameModuleDirectX9/src/UI/UIMenu.h"

#include "../GamestateViewIO/AspectProfileIO.h"
#include "../GamestateViewIO/ThemeProfileIO.h"
#include "../ViewControl/CameraDirector.h"
#include "AspectProfile.h"
#include "ThemeResourceProfile.h"
#include "ViewProfile.h"

class BasicGameViewState : public GameStateObject
{
protected:
	CameraDirector m_cameraDirector;
	GameLightingController m_gameLightingController;
	
	ViewProfile m_viewProfile;
	
	AspectProfile m_aspectProfile;
	AspectProfileIO m_aspectProfileIO;

	ThemeResourceProfile m_themeResourceProfile;
	ThemeProfileIO m_themeProfileIO;

public:
	BasicGameViewState();
	~BasicGameViewState();

	CameraDirector * GetCameraDirector();
	GameLightingController * GetGameLightingController();
	AspectProfile * GetAspectProfile();

	bool InitMenu(int elementID, UIMenu * uiMenu);
	
};

#endif