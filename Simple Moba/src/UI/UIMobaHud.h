#if !defined(UIMOBAHUD_H)
#define UIMOBAHUD_H

#include <functional>
using namespace std::placeholders;

#include <vector>
using std::vector;

#include "../../../EngineGameModuleDirectX9/src/UI/UIHudBase.h"


#include "../../../EngineGameModuleDirectX9/src/UI/UIElement.h"
//#include "../../../EngineGameModuleDirectX9/src/UI/UIResizableElement.h"
#include "../../../EngineGameModuleDirectX9/src/Input/InputModel.h"
#include "../../../EngineMoba/src/Gamestate/MobaState.h"
#include "../../../EngineMoba/src/Actors/PlayerCharacterController.h"
#include "../../../EngineGameModel/src/Maths/LMVector2.h"
#include "../../../EngineGameModel/src/Maths/LMVector3.h"
#include "../../../EngineGameModel/src/Maths/LMVector4.h"

#include "../../../CoreGame/src/Gamestate/CoreGameState.h"

#include "../ViewControl/CameraDirector.h"
#include "../UI_Base/UIBuff.h"
#include "../UI_Base/UIBuffGroup.h"
#include "../UI_Base/UILayoutAbility.h"
#include "../UI_Base/UILayoutInventory.h"

#include "../GameplayView/PlayerCharacterView.h"
#include "../GameplayView/BuffView.h"
#include "../GameplayView/ItemView.h"
#include "../GamestateView/ViewProfile.h"
#include "../GamestateView/ThemeResources.h"
#include "../GamestateView/MobaGameElementsEnum.h"
#include "Tooltips/TooltipController.h"

#include "UIChat.h"
#include "UIMobaMap.h"
#include "UICharacterPanelFull.h"
#include "UIGameInfoPanel.h"
#include "UIInvPanel.h"


class UIMobaHud: public UIHudBase
{
private:
	CoreGameState * gameState;
	
	static TooltipController * m_tooltipController;

	CameraDirector * m_cameraDirector;
	
	UICharacterPanelFull m_characterPanel;
	UIGameInfoPanel m_gameInfoPanel;
	UIInvPanel m_invPanel;
	UIMobaMap m_map;

	UIChat m_chat;

	UIElement m_playergui;
	UIElement m_avatar;

	int m_playerBuffSize;

	UIBuffGroup m_buffs;
	UIBuffGroup m_debuffs;


	//UILayoutInventory m_playerInventory;

	//vector <UILayoutItem> m_playerInventory;


	
	//vector <UILayoutAbility> m_playerAbilities;

	UIResizableElement m_hpbar;
	float m_xorigin, m_y;
	float hppc, hpwidth;


	int m_maxInvSize;

	LMVector3 m_inventoryPositons[10];
	bool m_isLeftInv;

	bool m_isDragging;
	int m_dragIndex;
	LMTimer m_dragTimer;

	PlayerCharacterController * m_playerCharacter;

	float x_start, z_start, x_dist, z_dist;

	LMVector2 m_origin;
	int m_xIndexCount;

	float * m_elapsedGameTime;



	//render stuff
	char m_charbuffer[10000];
	float tempCDvalue;
	D3DCOLOR m_tempColorValue;
	D3DCOLOR m_greyColorValue;
	D3DCOLOR m_darkGreyColorValue;
	D3DCOLOR m_tomatoColorValue;
	RECT m_afLeft;
	RECT m_fontPos;
	char m_buffer9001[9001];
	float cTime;

	ViewProfile * m_viewProfile;
	ThemeResources * m_theme;



public:
	UIMobaHud();
	~UIMobaHud();
	bool Init(
		CoreGameState * gameStateIn,
		ViewProfile * viewProfile,
		ThemeResources * theme,
		CameraDirector * cameraDirector,
		GameConfiguration * gameConfiguration,
		bool invLeft,
		float * gameTime,
		vector<InputModel*> * inputModels,
		vector<BuffView> * buffViews,
		vector<ItemView> * itemViews,
		TooltipController * tooltipController,
		PlayerCharacterController * initCharControl);

	void CalculateInvPositions(ViewProfile * viewProfile);

	void SetInvItems(PlayerCharacterController * playerCharacterController);

	void SetBuffs(PlayerCharacterController * playerCharacterController);

	void Update(float deltaTime, PlayerCharacterController * playerCharacterController, PlayerCharacterView * playerCharacterView);
	void Render();
	void RenderTextStuff();

	void ImplementBehavior(int index, int enumIndex);
	
	void ActionSelect();
	void ActionUnselect();

	void Select(POINT * p);
	void AltSelect(POINT * p);
	bool MouseOver(POINT * p);
	
	bool IsDragging();
	bool InitAvatarElement(UIElement * uiElement, CharacterClassName characterClass);

	void SetStateRequest(UIHudState state);


	
	UIChat * GetChat();
	UIMobaMap * GetMap();
	UIGameInfoPanel * GetGameInfoPanel();
	UICharacterPanel * GetCharacterPanel();
	UIInvPanel * GetInvPanel();



};

#endif