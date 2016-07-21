#if !defined(MOBACONTROLLER_H)
#define MOBACONTROLLER_H

#include "../../../EngineMoba/src/Gamestate/MobaState.h"
#include "../GamestateView/MobaViewState.h"

#include "../../../EngineGameModuleDirectX9/src/Input/GameInputController.h"

#include "../../../CoreGame/src/GameConfiguration.h"
#include "PlayerWorldSelectionController.h"




enum GameBuildPhase
{
	gameBuildPhaseModel,
	gameBuildPhaseView,
	gameBuildPhaseController,
	gameBuildPhaseCount
};


class MobaController
{
protected:
	MobaState * mobaModel;
	MobaViewState * mobaView;
	GameInputController m_gameInputController;
	PlayerWorldSelectionController m_playerWorldSelectionController;

	GameConfiguration * gameConfiguration;

	bool m_controlAnyPlayerCharacter; //Should we let them control the player character that the camera focuses?

	//temp 
	vector<ShopZone *> * zones;

public:

	//Load Variables
	GameStateObject * statesToInit[2];
	GameBuildPhase m_loadProgress;
	int m_stateLoadProgress;
	int m_stateLoadProgressSize;






	MobaController();
	MobaController(MobaState * mobaModelIn, MobaViewState * mobaViewIn);
	~MobaController();
	

	InitMessage LoadStates();
	string GetLoadingMessage();

	//= STUFF TO INHERIT IN GAME MODES ============

	bool virtual Init(GameConfiguration & gameConfiguration) = 0;
	bool virtual InitControl(GameConfiguration & gameConfiguration) = 0;


	void virtual Update(float deltaTime) =0;
	void virtual UpdateInput(float deltaTime) = 0;
	void virtual UpdateGameEvents(float deltaTime) = 0;
	void virtual UpdateRespawnBehavior(float deltaTime) = 0;

	void virtual Render() =0;
	void virtual RenderUI() =0;

	//=============================================

	void UpdatePlayerControlled();
	void ControlledInRangeShops();




	void RenderBegin();
	void RenderEnd();

	void RenderUIBegin();
	void RenderUIEnd();

	MobaState * GetMobaState();
};

#endif