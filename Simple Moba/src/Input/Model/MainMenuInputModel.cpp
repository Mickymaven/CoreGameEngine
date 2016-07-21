#include "MainMenuInputModel.h"
MainMenuInputModel::MainMenuInputModel()
{}

bool MainMenuInputModel::Init(string path)
{

	m_path = "Resources/Settings/MainMenuInput.keys";


	m_keybinds.resize(mainMenuActionCount);

	m_keybinds[mainMenuActionLeftClick] = MO_LEFT_BUTTON;
	m_keybinds[mainMenuActionRightClick] = MO_RIGHT_BUTTON;
	m_keybinds[mainMenuActionToggleOpen] = DIK_ESCAPE;
	m_keybinds[mainMenuActionToggleOpenStatPanelItems] = DIK_TAB;
	m_keybinds[mainMenuActionToggleOpenStatPanelStats] = DIK_GRAVE;
	m_keybinds[mainMenuActionApply] = DIK_S;
	m_keybinds[mainMenuActionConfirm] = NO_KEY;

	m_spamFlags.resize(mainMenuActionCount, 0);

	vector<int> full
	{
		mainMenuActionLeftClick,
		mainMenuActionRightClick,
		mainMenuActionToggleOpen,
		mainMenuActionToggleOpenStatPanelItems,
		mainMenuActionToggleOpenStatPanelStats,
		mainMenuActionApply,
		mainMenuActionConfirm
	};

	vector<int> closed
	{
		mainMenuActionLeftClick,
		mainMenuActionRightClick,
		mainMenuActionToggleOpen,
		mainMenuActionToggleOpenStatPanelItems,
		mainMenuActionToggleOpenStatPanelStats
	};

	m_actionsforState.resize(2);

	m_actionsforState.at(0) = closed;
	m_actionsforState.at(1) = full;

	return true;
}

MainMenuInputModel::~MainMenuInputModel()
{

}