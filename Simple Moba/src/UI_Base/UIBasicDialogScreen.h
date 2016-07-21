#if !defined(UIBASICDIALOGSCREEN_H)
#define UIBASICDIALOGSCREEN_H

#include "UIDialogScreen.h"

class UIBasicDialogScreen : public UIDialogScreen, public UIArea
{

protected:
	UIElement m_background;

public:
	UIBasicDialogScreen();
	~UIBasicDialogScreen();

	bool Init(ViewProfile * viewProfile,
		ThemeResources * theme);

	void Update(float deltaTime);
	void Render();

	virtual void Select(POINT * p);
	virtual void AltSelect(POINT * p);

};

#endif