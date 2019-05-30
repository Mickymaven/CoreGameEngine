#include "UIMiniHud.h"

UIMiniHud::UIMiniHud()
{
}

UIMiniHud::~UIMiniHud()
{
}

bool UIMiniHud::Init(
	CoreGameState * gameStateIn,
	ViewProfile * viewProfile,
	ThemeResources * theme,
	float * gameTime,
	vector<InputModel*>* inputModels,
	PlayerCharacterController * initCharControl)
{

	m_gameState = gameStateIn;
	m_viewProfile = viewProfile;
	m_theme = theme;
	
	m_state = uiHudOpen;
	
	if (!m_characterPanel.Init(viewProfile,theme,gameStateIn,inputModels,initCharControl)) return false;


	return true;
}

void UIMiniHud::Update(float deltaTime, PlayerCharacterController * playerCharacterController, PlayerCharacterView * playerCharacterView)
{
	m_characterPanel.Update(deltaTime, playerCharacterController, playerCharacterView);
}

void UIMiniHud::Render()
{
	m_characterPanel.Render();
}