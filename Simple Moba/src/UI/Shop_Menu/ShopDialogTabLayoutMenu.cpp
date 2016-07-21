#include "ShopDialogTabLayoutMenu.h"
ShopDialogTabLayoutMenu::ShopDialogTabLayoutMenu()
{
}

ShopDialogTabLayoutMenu::~ShopDialogTabLayoutMenu()
{
}

void ShopDialogTabLayoutMenu::Activate(NPCView * npcView)
{
	//if ui content area not null
	//ptr here?
	if (UIMenu::m_uiMenuState == menuClosed)
	{
		UIMenu::OnExitClosed();
		UIMenu::OnEnterOpened();
	}
	else
	{
		MessageBox(NULL, "shop was open when we activated a dialog", "simple moba debug", MB_OK);
	}

	UIDialogScreen::Activate(npcView);
}