#if !defined(GAMEMAINMENU_H)
#define GAMEMAINMENU_H

#include "../Application/MsgParams.h"

#include "../../../EngineGameModuleDirectX9/src/UI/UIElement.h"
#include "../../../EngineGameModuleDirectX9/src/UI/UIButton.h"
#include "../../../EngineGameModuleDirectX9/src/UI/UICheckBox.h"
#include "../../../EngineGameModuleDirectX9/src/UI/UICheckBox.h"

#include "../Input/Model/MainMenuInputModel.h"
#include "../InputIO/KeybindData.h"
#include "../UI_Base/UIKeyDialog.h"
#include "../GamestateView/ViewProfile.h"
#include "../GamestateView/ThemeResources.h"
#include "Main_Menu/KeybindContent.h"
#include "Main_Menu/OptionsContent.h"
#include "Main_Menu/SoundContent.h"
#include "Main_Menu/DisplayContent.h"
#include "TabLayoutMenu.h"

class GameMainMenu : public TabLayoutMenu
{
private:
	static string labels[4];

	KeybindData * m_keybindData;

	KeybindContent m_keybindContent;
	OptionsContent m_optionsContent;
	SoundContent m_soundContent;
	DisplayContent m_displayContent;

	UIButton m_resetAllKeybinds;
	UIButton m_exit;

	vector<InputModel*> * m_inputModels;
	UIKeyDialog * m_keyDialog;
	KeyLabel * m_tempLabel;

public:
	GameMainMenu();
	~GameMainMenu();
	
	bool Init(
		InputModel * mainMenuInputModel,
		ViewProfile * viewProfile,
		ThemeResources * theme,
		LMVector2 *origin,
		LMVector2 *size,
		vector<InputModel*> * inputModels,
		UIKeyDialog * keyDialog,
		KeybindData * keybindData);
	
	void Update(float deltaTime);
	void Render();

	void Select(POINT * p);
	void AltSelect(POINT * p);

	void Apply();
	void ResetAllKeybinds();

	void ActivateKeyDialog(KeyLabel * label);

	void ExitGame();
};

#endif