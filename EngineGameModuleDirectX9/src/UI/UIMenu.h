#if !defined(UIMENU_H)
#define UIMENU_H


#include "../../../EngineGameModel/src/Maths/LMVector2.h"
#include "UIArea.h"
#include "UIElement.h"
#include "UIButton.h"
#include "../Input/InputModel.h"

#include "../../../Simple Moba/src/GamestateView/ViewProfile.h"
#include "../../../Simple Moba/src/GamestateView/ThemeResources.h"


enum UIMenuState
{
	menuClosed,
	menuOpened,
	menuStateCount
};

class UIMenu : public UIArea
{
protected:
	UIMenuState m_uiMenuState;
	UIElement m_background;
	UIButton m_close;
	InputModel * m_inputModel;

public:
	UIMenu();
	~UIMenu();

	bool Init(
		ViewProfile * viewProfile,
		ThemeResources * theme,
		LMVector2 * origin,
		LMVector2 * size );

	void OnEnterOpened();
	void Opened(float deltaTime);
	void OnExitOpened();

	void OnEnterClosed();
	void Closed(float deltaTime);
	void OnExitClosed();

	void ExitCurrentState();

	UIMenuState GetUIMenuState();

	bool ToggleState();

	bool IsOpen();
	void CloseMenu();

	virtual void Select(POINT * p);
	virtual void AltSelect(POINT * p);
};

#endif