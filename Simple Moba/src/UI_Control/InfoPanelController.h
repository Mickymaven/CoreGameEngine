#if !defined(INFOPANELCONTROLLER_H)
#define INFOPANELCONTROLLER_H

#include "../../../EngineGamePlatform/src/Application/Globals.h"//todo bad?


#include "../../../EngineMoba/src/Actors/PlayerCharacterController.h"
#include "../../../CoreGame/src/Gamestate/StandardMatch5v5State.h"
#include "../../../CoreGame/src/GameConfiguration.h"
#include "../../../EngineGameModuleDirectX9/src/UI/UIArea.h"
#include "../UI/InfoPanel.h"
#include "../GameplayView/ItemView.h"
#include "../GamestateViewIO/GameAssetFactory.h"

class InfoPanelController : public UIArea
{
private:
	StandardMatch5v5State * gameState;
	GameConfiguration * gameConfiguration;

	InfoPanel m_infoPanel;

	int m_boxCount;
	LMVector3 * m_boxPositions;

	vector<PlayerCharacterController * > * m_leftTeam;
	vector<PlayerCharacterController * > * m_rightTeam;

	vector<UIElement*> m_teamsPanelIcons;

	GameAssetFactory * gameAssetFactory;

public:
	InfoPanelController();
	~InfoPanelController();

	bool Init(GameAssetFactory * gameAssetFactory, StandardMatch5v5State * gameStateIn, GameConfiguration * gameConfigurationIn, vector<ItemView> * itemViews, TooltipController * tooltipController);
	void Update(float deltaTime);
	void Render();
	void RenderInfoPanel();

	void Select(POINT * p);
	void AltSelect(POINT * p);
	bool MouseOver(POINT * p);

	void HandleLeftClick();
	void ImplementBehavior(int index, int enumIndex);

	InfoPanel * GetInfoPanel();
	LMVector3 * GetPositionArray();
	vector <UIElement*> * GetTeamsPanelIcons();
};

#endif