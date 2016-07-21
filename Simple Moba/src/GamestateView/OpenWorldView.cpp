#include "OpenWorldView.h"

OpenWorldView::OpenWorldView()
{
}

OpenWorldView::~OpenWorldView()
{
}

bool OpenWorldView::Init(GameConfiguration * gameConfiguration)
{
	return MobaViewState::Init(gameConfiguration);
}

bool OpenWorldView::InitSelectedPhase(int initPhase)
{



	///////////////////////////////////////////////////////////////
	if (initPhase == mobaViewInitPhaseCameras)
	{///////////////////////////////////////////////////////////

		if (!m_cameraDirector.Init(gameState, &m_playerCharacterViews)) return false;
	}
	return true;
}

void OpenWorldView::SetGameModel(OpenWorldState * gameStateIn)
{
	OpenWorldView::gameState = gameStateIn;
}
