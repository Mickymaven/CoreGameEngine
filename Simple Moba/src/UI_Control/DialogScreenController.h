#if !defined(DIALOGSCREENCONTROLLER_H)
#define DIALOGSCREENCONTROLLER_H

#include "../../../EngineMoba/src/Actor_Control/DialogViewScreenOptions.h"
#include "../GameplayView/NPCView.h"
#include "../UI/GameShopMenu.h"
#include "../UI_Base/UIBasicDialogScreen.h" 
#include "../UI_Base/UIBasicDialogScreen.h" 

class DialogScreenController
{
protected:
	//DialogScreenViewOptions m_state;

	UIBasicDialogScreen m_dialogScreen;
	GameShopMenu * m_gameShopMenu;

	UIDialogScreen * m_activeDialogScreen;

public:
	DialogScreenController();
	~DialogScreenController();

	bool Init(
		ViewProfile * viewProfile,
		ThemeResources * theme,
		GameShopMenu * gameShopMenu);
	
	//Update(float deltaTime);

	void Render();

	void OpenDialog(NPCView * npcView, PlayerCharacterController * client, vector<PlayerCharacterController *> * clientTeam);

	void ActionSelect(POINT * p);

	void DialogViewChangeCallback(NPCView * npcView, int dialogScreenIndex, DialogScreenViewOptions option);

	void SetActiveDialog(DialogScreenViewOptions option);
};

#endif