#include "GameMainMenu.h"


string GameMainMenu::labels[4] = {
	"Keybinds",
	"Gameplay",
	"Sound",
	"Display" };

GameMainMenu::GameMainMenu() :TabLayoutMenu()
{

}

GameMainMenu::~GameMainMenu()
{

}

bool GameMainMenu::Init(
	InputModel * mainMenuInputModel,
	ViewProfile * viewProfile,
	ThemeResources * theme,
	LMVector2 * origin,
	LMVector2 * size,
	vector<InputModel*> * inputModels,
	UIKeyDialog * keyDialog,
	KeybindData * keybindData)
{
	//used to do initializer list (is now error in compiler v140)
	UIMenu::m_bounds.left = origin->x;
	UIMenu::m_bounds.top = origin->y;
	UIMenu::m_bounds.right = origin->x + size->x;
	UIMenu::m_bounds.bottom = origin->y + size->y;

	m_keybindData = keybindData;

	m_keyDialog = keyDialog;
	//ActivateKeyDialog
	m_inputModel = mainMenuInputModel;

	m_inputModels = inputModels;

	m_pageOrigin = LMVector4(origin->x + (0.2f*size->x), origin->y + (0.1f*size->y), origin->x + size->x, origin->x + size->y);
	
	if (!UIMenu::Init(viewProfile, theme, origin, size)) return false;

	m_background = UIElement(size->x, size->y, "Resources/UI/Menu/Main/GameMainMenu.png");
	if (!m_background.Init()) return false;
	m_background.SetPosition(origin->x, 0.0f, origin->y);

	m_exit = UIButton(122.0f, 52.0f, "Resources/UI/Menu/Main/ButtonExitGame.png");
	if (!m_exit.Init()) return false;
	m_exit.SetCallbackSTDFunction(std::bind(&GameMainMenu::ExitGame, this));
	m_exit.SetPosition(origin->x + 20.0f, 0.0f, origin->y + 710.0f);

	m_resetAllKeybinds = UIButton(122.0f, 52.0f, "Resources/UI/Menu/Main/ButtonResetAllKeybinds.png");
	if (!m_resetAllKeybinds.Init()) return false;
	m_resetAllKeybinds.SetCallbackSTDFunction(std::bind(&GameMainMenu::ResetAllKeybinds, this));
	m_resetAllKeybinds.SetPosition(origin->x + 162.0f, 0.0f, origin->y + 710.0f);
	
	//init content
	if (!m_keybindContent.Init(viewProfile, theme, &m_pageOrigin, inputModels)) return false;
	m_keybindContent.SetKeyDialogCallback(std::bind(&GameMainMenu::ActivateKeyDialog, this, _1));

	if (!m_optionsContent.Init(viewProfile, theme, &m_pageOrigin)) return false;
	if (!m_soundContent.Init(viewProfile, theme, &m_pageOrigin)) return false;
	if (!m_displayContent.Init(viewProfile, theme, &m_pageOrigin)) return false;

	//store content
	m_content.push_back(&m_keybindContent);
	m_content.push_back(&m_optionsContent);
	m_content.push_back(&m_soundContent);
	m_content.push_back(&m_displayContent);

	m_page = &m_keybindContent;

	string path = "Resources/UI/Menu/Main/tab-background.png";

	//FontGroup * fontGroup, string * labelText;
	



	
	/*
	if (!m_tabgroup.NewTab(50.0f, 50.0f, path, &m_keybindContent, std::bind(&TabLayoutMenu::SetPage, this, _1))) return false;
	if (!m_tabgroup.NewTab(50.0f, 50.0f, path, &m_optionsContent, std::bind(&TabLayoutMenu::SetPage, this, _1))) return false;
	if (!m_tabgroup.NewTab(50.0f, 50.0f, path, &m_soundContent, std::bind(&TabLayoutMenu::SetPage, this, _1))) return false;
	if (!m_tabgroup.NewTab(50.0f, 50.0f, path, &m_displayContent, std::bind(&TabLayoutMenu::SetPage, this, _1))) return false;
	*/
	
	for (unsigned int i = 0; i < m_content.size(); i++)
	{
		if (!m_tabgroup.NewTab(
			150.0f, 40.0f,
			path,
			&theme->m_settingsLabel,
			&labels[i],
			m_content.at(i),
			std::bind(&TabLayoutMenu::SetPage, this, _1) )) return false;
	}


	//must be after filling tabgroup up
	LMVector2 tgSize(160.0f, size->y);
	LMVector2 tgOrigin(origin->x + 20.0f, origin->y + 20.0f);

	if (!m_tabgroup.Init(&tgOrigin, &tgSize)) return false;

	return true;
}

void GameMainMenu::Update(float deltaTime)
{
	/*
	switch (m_state)
	{

	}*/
}

void GameMainMenu::Render()
{
	switch (m_uiMenuState)
	{
	case menuOpened:
		m_background.Render();
		m_close.Render();
		m_exit.Render();
		m_resetAllKeybinds.Render();

		m_tabgroup.Render();
		
		if (m_page != NULL) m_page->Render();

		break;
	case menuClosed:
	default:
		break;
	}
}

void GameMainMenu::Select(POINT * p)
{
	
	if (!m_uiMenuState == menuOpened) return;
	if (!IsPointInBounds(p)) return;

	m_tabgroup.Select(p);

	m_close.Select(p);
	m_exit.Select(p);
	m_resetAllKeybinds.Select(p);

	if (m_page != NULL) m_page->Select(p);

}

void GameMainMenu::AltSelect(POINT * p)
{

}

void GameMainMenu::Apply()
{
	for (unsigned int i = 0; i < m_inputModels->size(); i++)
	{
		m_keybindData->WriteData(m_inputModels->at(i)->m_path, &m_inputModels->at(i)->m_keybinds);
	}
}

void GameMainMenu::ResetAllKeybinds()
{
	for (unsigned int i = 0; i < m_inputModels->size(); i++)
	{ m_inputModels->at(i)->Init(""); }//init contains set to default values

	MessageBeep((UINT)0);
	MessageBox(NULL, "All keybinds have been reset to the default values.", "Simple MOBA", MB_OK);

	Apply();
}

void GameMainMenu::ActivateKeyDialog(KeyLabel * label)
{
	m_keyDialog->Activate(label);
}

void GameMainMenu::ExitGame()
{
	PostMessage(g_hwnd, GAMEEXIT_MENU, 1, 0);

}