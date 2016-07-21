#if !defined(INFOPANEL_H)
#define INFOPANEL_H

#include "../../../EngineGameModuleDirectX9/src/UI/UIElement.h"
#include "../../../EngineMoba/src/Actors/Character.h"
#include "../../../EngineMoba/src/Actors/PlayerCharacterController.h"
#include "../UI_Base/UILayoutInventory.h"
#include "../UI_Base/UILayoutStats.h"
#include "Tooltips/TooltipController.h"
#include "StatBase.h"

#include "../GameplayView/ItemView.h"

enum InfoPanelState
{
	infoPanelStateOpened,
	infoPanelStateClosed,
	infoPanelStateCount
};

class InfoPanel : public StatBase
{
private:
	InfoPanelState m_state;
	Character * m_character;

	UIElement m_background;

	UILayoutInventory m_inv;
	UILayoutStats m_stats;

	vector<LMVector3 *> m_itemPositions;

public:
	InfoPanel();
	~InfoPanel();

	bool Init(Character * character, vector<ItemView> * itemViews, TooltipController * tooltipController);

	void Render();

	void Select(POINT * p);
	void AltSelect(POINT * p);
	bool MouseOver(POINT * p);

	InfoPanelState GetState();
	void SetState(InfoPanelState state);
	void SetInfoPanelTarget(Character * actorController);

	vector<LMVector3 *> *  GetInventoryRenderPositions();

	Character * GetInfoPanelTarget();
};

#endif