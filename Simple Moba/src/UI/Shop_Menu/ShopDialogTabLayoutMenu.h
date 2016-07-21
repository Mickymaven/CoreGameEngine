#if !defined(SHOPDIALOGTABLAYOUTMENU_H)
#define SHOPDIALOGTABLAYOUTMENU_H

#include "../TabLayoutMenu.h" 
#include "../../UI_Base/UIDialogScreen.h"
#include "../../GameplayView/NPCView.h"

class ShopDialogTabLayoutMenu: public TabLayoutMenu, public UIDialogScreen
{

protected:
public:
	ShopDialogTabLayoutMenu();
	~ShopDialogTabLayoutMenu();

	void Activate(NPCView * npcView);

};

#endif