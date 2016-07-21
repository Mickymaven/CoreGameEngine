#if !defined(MAINMENUINPUTMODEL_H)
#define MAINMENUINPUTMODEL_H

#include "../../../../EngineGameModuleDirectX9/src/Input/InputModel.h"

enum MainMenuAction
{
	mainMenuActionLeftClick,
	mainMenuActionRightClick,
	mainMenuActionToggleOpen,
	mainMenuActionToggleOpenStatPanelItems,
	mainMenuActionToggleOpenStatPanelStats,
	mainMenuActionConfirm,
	mainMenuActionApply,
	mainMenuActionCount
};

class MainMenuInputModel : public InputModel
{
public:
	MainMenuInputModel();
	bool Init(string path);
	~MainMenuInputModel();
};

#endif;