#if !defined(UIPANELBASE_H)
#define UIPANELBASE_H


#include "../../../EngineMoba/src/Gamestate/MobaState.h"

#include "../../../EngineGameModuleDirectX9/src/Input/InputModel.h"
#include "../../../EngineGameModuleDirectX9/src/Input/InputKeyDefines.h"
#include "../../../EngineGameModuleDirectX9/src/UI/UILabelCstr.h"
#include "../../../EngineGameModuleDirectX9/src/UI/UIArea.h"

#include "../GamestateView/ViewProfile.h"
#include "../GamestateView/ThemeResources.h"
#include "Tooltips/TooltipController.h"



#include "CooldownLabel.h"

class UIPanelBase : public UIArea
{
protected:
MobaState * m_gameState;
	TooltipController * m_tooltipController;
	ViewProfile * m_viewProfile;
	ThemeResources * m_theme;
	PlayerCharacterController * m_playerCharacter;

	vector<UILabelCstr> m_bindLabels;
	vector<CooldownLabel> m_cooldownLabels;

public:
	

	UIPanelBase();
	~UIPanelBase();


	virtual void Select(POINT * p);
	virtual void AltSelect(POINT * p);
	virtual bool MouseOver(POINT * p);
};

#endif