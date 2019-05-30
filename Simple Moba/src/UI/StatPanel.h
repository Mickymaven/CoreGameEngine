#if !defined(STATPANEL_H)
#define STATPANEL_H

#include <functional>
using namespace std::placeholders;

#include "../../../EngineGamePlatform/src/Application/Globals.h"//todo ?


#include "../../../EngineMoba/src/Actors/PlayerCharacterController.h"

#include "../../../EngineGameModuleDirectX9/src/UI/UIArea.h"
#include "../../../EngineGameModuleDirectX9/src/UI/UIElement.h"
#include "../../../EngineGameModuleDirectX9/src/UI/UIButton.h"

#include "Tooltips/TooltipController.h"
#include "../UI_Base/UILayoutItem.h"
#include "../GameplayView/ItemView.h"

#include "UIPanelBase.h"

enum StatPanelState
{
	statPanelOpenedStats,
	statPanelOpenedItems,
	statPanelClosed,
	statPanelStateCount
};

class StatPanel : public UIPanelBase//, public StatBase
{
private:

	StatPanelState m_state;

	vector <UILayoutItem *> m_layoutItems;

	vector<vector <UILayoutItem>> m_playerInvLayouts;
	vector<vector<vector <UILayoutItem>>> m_teams;

	UIElement m_background;
	UIElement m_verticalStats;

	UIElement * statIcons1;
	UIElement * statIcons2;

	UIButton * m_close;

	vector<vector<PlayerCharacterController *> *> m_teamControllers;

	vector<PlayerCharacterController *> * m_yellowTeam;
	vector<PlayerCharacterController *> * m_purpleTeam;


	LPD3DXFONT m_textFont;
	RECT m_fontPosition;
	char m_textBuffer[200];

	RECT m_kdaPosition1;

	vector<ItemView> * m_lightweightItemViews;


	LMVector2 m_originLeft;
	LMVector2 m_originRight;

	LMVector2 m_originLeft2;
	LMVector2 m_originRight2;




public:
	StatPanel();
	~StatPanel();
	
	bool Init(
		ViewProfile * viewProfile,
		ThemeResources * themeResources,

		MobaState * gameState,
		vector<PlayerCharacterController*> * yellowTeam,
		vector<PlayerCharacterController*> * purpleTeam,
		TooltipController * tooltipController,
		vector<ItemView> * lightweightItemViews);

	void CalculateInvPositions();
	void SetInvItems();

	void Update(float deltaTime);
	void Render();

	void RenderTeamCollumns(vector<PlayerCharacterController* > * team, unsigned int teamIndex);
	void RenderKDA(PlayerKDA kda);
	void RenderItems(PlayerCharacterController * playerCharacterController);
	void RenderStats(PlayerCharacterController * playerCharacterController);
	
	bool ToggleAction(StatPanelState message);


	void Select(POINT * p);
	void AltSelect(POINT * p);
	bool MouseOver(POINT * p);

	StatPanelState GetState();


};




#endif