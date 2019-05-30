#include "UICharacterPanelMini.h"

UICharacterPanelMini::UICharacterPanelMini()
{
}

UICharacterPanelMini::~UICharacterPanelMini()
{
}

bool UICharacterPanelMini::Init(ViewProfile * viewProfile,
	ThemeResources * themeResources,
	MobaState * gameState,
	vector<InputModel*> * inputModels,
	PlayerCharacterController * initCharControl)
{
	m_gameState = gameState;
	m_viewProfile = viewProfile;
	m_theme = themeResources;
	m_viewProfile = viewProfile;
	

	if (!InitAvatarElement(&m_avatar, characterGrey)) return false;
	if (!InitHPBar()) return false;

	return true;
}

void UICharacterPanelMini::Update(float deltaTime, PlayerCharacterController * playerCharacterController, PlayerCharacterView * playerCharacterView)
{

	UICharacterPanel::UpdateHP(deltaTime, playerCharacterController, playerCharacterView);
}

void UICharacterPanelMini::Render()
{
	m_hpbar.Render();
	m_avatar.Render();
}
