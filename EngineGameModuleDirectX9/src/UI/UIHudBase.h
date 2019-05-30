#if !defined (UIHUDBASE_H)
#define UIHUDBASE_H

#include "UIArea.h"

enum UIHudState
{
	uiHudOpen,
	uiHudClosed,
	uiHudStateCount
};

class UIHudBase : public UIArea
{
protected:
	UIHudState m_state;

public:
	UIHudBase();
	~UIHudBase();

	UIHudState GetState();
};

#endif