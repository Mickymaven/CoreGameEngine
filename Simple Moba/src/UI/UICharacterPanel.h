#if !defined(UICHARACTERPANEL_H)
#define UICHARACTERPANEL_H

#include <vector>
using std::vector;

#include "../../../EngineMoba/src/Actors/PlayerCharacterController.h"

#include "../../../EngineGameModuleDirectX9/src/UI/UIElement.h"
#include "../../../EngineGameModuleDirectX9/src/UI/UIResizableElement.h"
#include "../../../EngineGameModuleDirectX9/src/UI/UILabelCstr.h"

#include "../GameplayView/PlayerCharacterView.h"
#include "../UI_Base/UILayoutAbility.h"
#include "Tooltips/TooltipController.h"
#include "../UI_Base/UIStatLabelGroup.h"

#include "../Input/Model/CharacterInputModel.h"

#include "UIPanelBase.h"


class UICharacterPanel : public UIPanelBase
{
protected:

	vector<UILayoutAbility> m_characterAbilities;

	UIElement m_abilityIcon;


	UIResizableElement m_hpbar;
	UIElement m_avatar;

	UIStatLabelGroup m_stats;

	static const int elementIDs[];

	//UI Fonts


	//hp bar pos
	float m_xorigin, m_y;
	float hppc, hpwidth;

	// ability position stuff
	RECT m_afLeft;
	RECT m_fontPos;

public:
	UICharacterPanel();
	~UICharacterPanel();

	bool Init(ViewProfile * viewProfile,
		ThemeResources * themeResources,
		MobaState * gameState,
		TooltipController * tooltipController,
		vector<InputModel*> * inputModels,
		PlayerCharacterController * initCharControl);

	bool InitAvatarElement(UIElement * uiElement, CharacterClassName characterClass);
	bool InitHPBar();
	
	void Update(float deltaTime, PlayerCharacterController * playerCharacterController, PlayerCharacterView * playerCharacterView);
	void UpdateHP(float deltaTime, PlayerCharacterController * playerCharacterController, PlayerCharacterView * playerCharacterView);

	void Render();

	void SetAbilityPositions(ViewProfile * viewProfile);

	void SetAbilities(PlayerCharacterView * playerCharacterView);
	

	int SelectFromAbilities(POINT * p);

	void Select(POINT * p);
	void AltSelect(POINT * p);
	bool MouseOver(POINT * p);
};

#endif