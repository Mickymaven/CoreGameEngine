#if !defined (UIINVPANEL_H)
#define UIINVPANEL_H

#include <vector>
using std::vector;

#include "../../../EngineGameModel/src/Utility/LMTimer.h"

#include "../../../EngineMoba/src/Actors/PlayerCharacterController.h"

#include "../GameplayView/PlayerCharacterView.h"

#include "../Input/Model/CharacterInputModel.h"

#include "../UI_Base/UILayoutInventory.h"
#include "UIPanelBase.h"


class UIInvPanel : public UIPanelBase
{
protected:
	static const int elementIDs[];

	UILayoutInventory m_playerInventory;

	//Item Drag
	bool m_isDragging;
	int m_dragIndex;
	LMTimer m_dragTimer;

public:
	UIInvPanel();
	~UIInvPanel();

	bool Init(ViewProfile * viewProfile,
		ThemeResources * themeResources,
		MobaState * gameState,
		TooltipController * tooltipController,
		vector<InputModel*> * inputModels,
		vector<ItemView> * itemViews,
		PlayerCharacterController * initCharControl);

	void  InitInvPositions(ViewProfile * viewProfile);
	void Update(float deltaTime, PlayerCharacterController * playerCharacterController, PlayerCharacterView * playerCharacterView);
	void Render();

	void Select(POINT * p);
	void SelectMouseUp(POINT * p);

	void AltSelect(POINT * p);
	bool MouseOver(POINT * p);

	UILayoutInventory * GetLayoutInventory();

	bool GetIsDraggingItem();
};

#endif