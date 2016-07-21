#include "BasicGameViewState.h"

BasicGameViewState::BasicGameViewState()
{

}

BasicGameViewState::~BasicGameViewState()
{

}

CameraDirector * BasicGameViewState::GetCameraDirector()
{
	return &m_cameraDirector;
}

GameLightingController * BasicGameViewState::GetGameLightingController()
{
	return &m_gameLightingController;
}

AspectProfile * BasicGameViewState::GetAspectProfile()
{
	return &m_aspectProfile;
}

bool BasicGameViewState::InitMenu(int elementID, UIMenu * uiMenu)
{
	return true;
}