#include "OpenWorld.h"

OpenWorld::OpenWorld() : MobaController(&m_openWorldState, &m_openWorldView)
{
	//derived Implementation Pointers
	gameState = &m_openWorldState;
	gameView = &m_openWorldView;

	//Load Game View With Model
	m_openWorldView.SetGameModel(&m_openWorldState);

	//Initial LoadingState


	m_controlAnyPlayerCharacter = true;

}

OpenWorld::~OpenWorld()
{
}

bool OpenWorld::Init(GameConfiguration & gameConfigurationIn)
{
	gameConfiguration = &gameConfigurationIn;

	m_openWorldState.CoreGameState::Init(&gameConfigurationIn);
	m_openWorldView.Init(&gameConfigurationIn);

	statesToInit[gameBuildPhaseModel] = &m_openWorldState;
	statesToInit[gameBuildPhaseView] = &m_openWorldView;

	return true;
}

bool OpenWorld::InitControl(GameConfiguration & gameConfigurationIn)
{
	gameView->GetCameraDirector()->m_gameCameraThisUpdate = usingInterfaceCamera;
	gameView->GetCameraDirector()->SetUsingCamera(usingInterfaceCamera);

	return true;
}

void OpenWorld::Update(float deltaTime)
{
	gameState->UpdateGameTime();
}

void OpenWorld::UpdateInput(float deltaTime)
{
}

void OpenWorld::UpdateGameEvents(float deltaTime)
{
}

void OpenWorld::UpdateRespawnBehavior(float deltaTime)
{
}

void OpenWorld::Render()
{
	RenderBegin();



	RenderUI();
	RenderEnd();
}

void OpenWorld::RenderUI()
{
	RenderUIBegin();


	RenderUIEnd();
}

OpenWorldState * OpenWorld::GetOpenWorldState()
{
	return &m_openWorldState;
}
