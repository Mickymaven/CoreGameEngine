#if !defined UIMINIHUD_H
#define UIMINIHUD_H

#include "../../../EngineGameModuleDirectX9/src/UI/UIHudBase.h"

#include "../../../EngineGameModuleDirectX9/src/Input/InputModel.h"

#include "../../../CoreGame/src/Gamestate/CoreGameState.h"

#include "../../../EngineMoba/src/Actors/PlayerCharacterController.h"

#include "../GamestateView/ViewProfile.h"
#include "../GamestateView/ThemeResources.h"
#include "../GameplayView/PlayerCharacterView.h"


#include "UICharacterPanelMini.h"



/*


#include "../../../EngineGameModuleDirectX9/src/UI/UIHudBase.h"


#include "../../../EngineGameModuleDirectX9/src/UI/UIElement.h"
//#include "../../../EngineGameModuleDirectX9/src/UI/UIResizableElement.h"
#include "../../../EngineGameModuleDirectX9/src/Input/InputModel.h"
#include "../../../EngineMoba/src/Gamestate/MobaState.h"

#include "../../../EngineGameModel/src/Maths/LMVector2.h"
#include "../../../EngineGameModel/src/Maths/LMVector3.h"
#include "../../../EngineGameModel/src/Maths/LMVector4.h"
#include "../ViewControl/CameraDirector.h"
#include "../UI_Base/UIBuff.h"
#include "../UI_Base/UIBuffGroup.h"
#include "../UI_Base/UILayoutAbility.h"
#include "../UI_Base/UILayoutInventory.h"

#include "../GameplayView/BuffView.h"
#include "../GameplayView/ItemView.h"
#include "../GamestateView/ViewProfile.h"
#include "../GamestateView/ThemeResources.h"
#include "../GamestateView/MobaGameElementsEnum.h"
#include "Tooltips/TooltipController.h"


*/







class UIMiniHud : public UIHudBase
{
private:
	CoreGameState * m_gameState;
	ViewProfile * m_viewProfile;
	ThemeResources * m_theme;

	UICharacterPanelMini m_characterPanel;


public:
	UIMiniHud();
	~UIMiniHud();

	bool Init(
		CoreGameState * gameStateIn,
		ViewProfile * viewProfile,
		ThemeResources * theme,
		float * gameTime,
		vector<InputModel*> * inputModels,
		PlayerCharacterController * initCharControl);

	void Update(float deltaTime, PlayerCharacterController * playerCharacterController, PlayerCharacterView * playerCharacterView);
	void Render();

	


};

#endif