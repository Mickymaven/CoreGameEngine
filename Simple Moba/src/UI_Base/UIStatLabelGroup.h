#if !defined(UISTATLABELGROUP_H)
#define UISTATLABELGROUP_H

#include <vector>
using std::vector;


#include "../../../EngineMoba/src/Actors/PlayerCharacterController.h"
#include "../../../EngineMoba/src/Gamestate/MobaState.h"

#include "../../../EngineGameModuleDirectX9/src/UI/UIArea.h"
#include "../../../EngineGameModuleDirectX9/src/UI/UILabelCstr.h"

#include "../GamestateView/ViewProfile.h"
#include "../GamestateView/ThemeResources.h"
#include "../GameplayView/PlayerCharacterView.h"
#include "../UI/Tooltips/TooltipController.h"

enum StatLabel
{
	statLabelRange,
	statLabelAS,
	statLabelAD,
	statLabelCV,
	statLabelMS,
	statLabelARM,
	statLabelCVR,
	statLabelHPR,
	statLabelHP,
	statLabelMHP,
	statLabelCount
};


class UIStatLabelGroup : public UIArea
{
protected:
	MobaState * m_gameState;
	TooltipController * m_tooltipController;
	ViewProfile * m_viewProfile;
	ThemeResources * m_theme;

	vector<UILabelCstr> m_statLabels;

public:
	UIStatLabelGroup();
	~UIStatLabelGroup();

	bool Init(ViewProfile * viewProfile, ThemeResources * themeResources,
		MobaState * gameState, TooltipController * tooltipController,
		PlayerCharacterController * initCharControl);

	void Update(float deltaTime, ActorStats * a);
	void Render();
};

#endif