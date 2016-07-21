#if !defined(STANDARDMATCH5V5_H)
#define STANDARDMATCH5V5_H

#include "../../../EngineMoba/src/GameControl/VitalEventController.h"
#include "../../../EngineMoba/src/Actors/PlayerCharacterController.h"

#include "../../../CoreGame/src/Gamestate/StandardMatch5v5State.h"

#include "../../../EngineGameModuleDirectX9/src/Input/InputSet.h"

#include "../GamestateView/MobaViewState.h"
#include "../UI_Control/CursorController.h"
#include "../UI_Control/IndicatorController.h"
#include "../Tools/NodeEditor.h"
#include "../Tools/PathOptimiser.h"
#include "../InputControl/PlayerInputController.h"
#include "../Input/Control/CharacterInputSet.h"
#include "../Input/Control/InterfaceInputSet.h"
#include "../Input/Control/CameraInputSet.h"
#include "../Input/Control/DevInputSet.h"
#include "../Input/Control/EditorInputSet.h"
#include "../Input/Control/ShopMenuInputSet.h"
#include "../Input/Control/MainMenuInputSet.h"
#include "../Input/Control/ChatTextAreaInputSet.h"
#include "../Input/Control/KeyDialogInputSet.h"

#include "../UI_Control/MobaMessageEventManager.h"

#include "MobaController.h"

class StandardMatch5v5 : public MobaController
{
private:
	//Init vars



	StandardMatch5v5State m_StandardMatch5v5State;
	StandardMatch5v5State * gameState;
	
	MobaViewState m_gameView;
	MobaViewState * gameView;

	CharacterInputSet m_characterInputSet;
	InterfaceInputSet m_interfaceInputSet;
	CameraInputSet m_cameraInputSet;
	DevInputSet  m_devInputSet;
	EditorInputSet  m_editorInputSet;
	ShopMenuInputSet m_shopMenuInputSet;
	MainMenuInputSet m_mainMenuInputSet;
	ChatTextAreaInputSet m_chatTextAreaInputSet;
	KeyDialogInputSet m_keyDialogInputSet;

	PlayerInputController m_playerInputController;
	
	IndicatorController m_indicatorController;
	CursorController m_cursorController;

	VitalEventController m_vitalEventController;
	NodeEditor m_nodeEditor;

	PathOptimiser m_pathOptimiser;//to init with pathfinder. (all dx win code here)


	MobaMessageEventManager m_mobaMessageEventManager;//this is a match specific thing.

	//refactor game events to own class

	bool m_isFirstSpawn;
	bool sTime1, sTime2, sTime3, sTime4, sTime5;

	/*
	LMMesh m_boxMesh;
	Sprite m_brickBox;
	*/

	LPD3DXBUFFER m_errorLog;
	LPD3DXEFFECT m_effect;
	D3DXHANDLE m_technique;
	D3DXMATRIX m_world;

public:
	
	StandardMatch5v5();
	~StandardMatch5v5();

	bool Init(GameConfiguration & gameConfigurationIn);
	bool InitControl(GameConfiguration & gameConfigurationIn);
	
	void Update(float deltaTime);
	void UpdateInput(float deltaTime);
	void UpdateGameEvents(float deltaTime);
	void UpdateRespawnBehavior(float deltaTime);

	void Render();
	void RenderUI();

	//Accessors
	StandardMatch5v5State * GetStandardMatch5v5State();
};

#endif