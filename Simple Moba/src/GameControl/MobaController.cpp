#include "MobaController.h"

GameBuildPhase& operator++(GameBuildPhase& initialValue)
{
	initialValue = static_cast<GameBuildPhase>(initialValue + 1);
	return initialValue;
}

GameBuildPhase operator++(GameBuildPhase& initialValue, int)
{
	GameBuildPhase returnValue = initialValue;
	++initialValue;
	return returnValue;
}

MobaController::MobaController()
{
	mobaModel = NULL;
	mobaView = NULL;
}

MobaController::MobaController(MobaState * mobaModelIn, MobaViewState * mobaViewIn)
{
	// base class Implementation Pointers
	mobaModel = mobaModelIn;
	mobaView = mobaViewIn;

	// Initial load state variables:
	m_loadProgress = gameBuildPhaseModel;
	m_stateLoadProgress = 0;
	m_stateLoadProgressSize = 0;
}

MobaController::~MobaController()
{

}


InitMessage MobaController::LoadStates()
{
	if (m_loadProgress != gameBuildPhaseController)
	{

		if (!statesToInit[m_loadProgress]->InitSelectedPhase(m_stateLoadProgress))
		{
			return initMessageAbort;
		}

		int msg = statesToInit[m_loadProgress]->UpdateLoadProgress();

		if (msg == initMessageAbort) return initMessageAbort;
		else if (msg == initMessageContinue)
		{
			m_stateLoadProgress += 1;
			m_stateLoadProgressSize = *statesToInit[m_loadProgress]->GetLoadSize();

			return initMessageContinue;
		}
		else if (msg == initMessageComplete)
		{
			m_loadProgress++;
			m_stateLoadProgress = 0;
			return initMessageContinue;
		}
		return initMessageContinue;
	}
	else if (m_loadProgress == gameBuildPhaseController)
	{
		if (!InitControl(*gameConfiguration)) return initMessageAbort;
		else statesToInit[gameBuildPhaseModel]->InitDebugPrint("Initialisation Complete.");//todo move init debug print somewhere more useful
	}

	m_loadProgress++;

	return initMessageComplete;
}

string MobaController::GetLoadingMessage()
{
	return statesToInit[m_loadProgress]->GetInitPhaseString(m_stateLoadProgressSize);
}



void MobaController::UpdatePlayerControlled()
{
	ControlledInRangeShops();
}

void MobaController::ControlledInRangeShops()
{
	mobaModel->GetControlledPCC()->GetInRangeShops()->resize(0);

	vector<ShopZone *> * zones = NULL;

	for (unsigned int i = 0; i < mobaModel->GetShops()->size(); i++)
	{
		zones = mobaModel->GetShops()->at(i).GetShopZones();

		for (unsigned int z = 0; z < zones->size(); z++)
		{
			//fix so we check player team in IsUsable()
			//pass in player and zone team

			if (zones->at(z)->IsUsable(
				*mobaModel->GetControlledActor()->GetPhysicsObject()->GetPosition(),
				mobaModel->GetControlledActor()->GetTeam()
				))
			{
				mobaModel->GetControlledPCC()->GetInRangeShops()->push_back(i);
			}
		}
	}
}

void MobaController::RenderBegin()
{
	g_D3D_Device->Clear(
		0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(53, 54, 64), 1.0f, 0); //D3DCOLOR_XRGB(3, 0, 9)

	g_D3D_Device->BeginScene();

	mobaView->GetCameraDirector()->SetGameView();
	mobaView->GetCameraDirector()->SetGameProjection();
}

void MobaController::RenderEnd()
{
	g_D3D_Device->EndScene();
	g_D3D_Device->Present(NULL, NULL, NULL, NULL);
}

void MobaController::RenderUIBegin()
{
	g_deviceControl.SetRenderSettings(customRenderSettingsGameUI);
	
}

void MobaController::RenderUIEnd()
{
	mobaView->GetCameraDirector()->SwitchToCurrentGameCamera();
	g_deviceControl.SetRenderSettings(customRenderSettingsGame3d);
}

MobaState * MobaController::GetMobaState()
{
	return mobaModel;
}
