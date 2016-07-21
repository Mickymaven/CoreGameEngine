#include "StandardMatch5v5.h"


StandardMatch5v5::StandardMatch5v5() : MobaController(&m_StandardMatch5v5State, &m_gameView)
{
	//derived Implementation Pointers
	gameState = &m_StandardMatch5v5State;
	gameView = &m_gameView;

	//Load Game View With Model
	m_gameView.SetGameModel(&m_StandardMatch5v5State);

	m_controlAnyPlayerCharacter = true;
}

StandardMatch5v5::~StandardMatch5v5()
{

}

bool StandardMatch5v5::Init(GameConfiguration & gameConfigurationIn)
{
	gameConfiguration = &gameConfigurationIn;

	m_StandardMatch5v5State.CoreGameState::Init(&gameConfigurationIn);
	m_gameView.Init(&gameConfigurationIn);

	MobaController::mobaModel = &m_StandardMatch5v5State;
	MobaController::mobaView = &m_gameView;

	statesToInit[gameBuildPhaseModel] = &m_StandardMatch5v5State;
	statesToInit[gameBuildPhaseView] = &m_gameView;

	//statesToInit[gameBuildPhaseModel]->Init(gameConfigurationIn);
	//statesToInit[gameBuildPhaseView]->Init(gameConfigurationIn);

	return true;
}



bool StandardMatch5v5::InitControl(GameConfiguration & gameConfigurationIn)
{
	gameView->GetCameraDirector()->m_gameCameraThisUpdate = usingInterfaceCamera;

	//game events
	m_isFirstSpawn = false;//hasnt occured yet
	sTime1 = false;
	sTime2 = false;
	sTime3 = false;
	sTime4 = false;
	sTime5 = false;

	//view stuff
	m_cursorController.Init(gameView, gameState, &m_playerWorldSelectionController);
	
	//kind of view stuff
	m_nodeEditor = NodeEditor(gameView->GetGameMapView()->GetGroundView(), (BasicGameState*)gameState, (BasicGameViewState*)gameView);

	// PLAYERCONTROLLER INPUT CONTROL ///////////////////////////////////////////
	m_StandardMatch5v5State.InitDebugPrint("Input: Loading Player Controller. ");


	//a couple of classes that need Input controller
	gameView->GetKeyDialog()->SetInputController(&m_gameInputController);
	CursorController::m_gameInputController = &m_gameInputController;
	gameView->GetHud()->GetChat()->GetInputBox()->SetInputController(&m_gameInputController);

	if (!m_playerWorldSelectionController.Init(gameState, gameView)) return false;



	InputSet::SetInputController(&m_gameInputController);

	m_keyDialogInputSet = KeyDialogInputSet(gameState, gameView);
	m_chatTextAreaInputSet = ChatTextAreaInputSet(gameState, gameView);
	m_mainMenuInputSet = MainMenuInputSet(gameState, gameView);
	m_shopMenuInputSet = ShopMenuInputSet(gameState, gameView);
	m_editorInputSet = EditorInputSet(gameState, gameView, &m_nodeEditor);
	m_devInputSet = DevInputSet(gameState, gameView);
	m_cameraInputSet = CameraInputSet(gameState, gameView);
	m_interfaceInputSet = InterfaceInputSet(gameState, gameView, &m_playerWorldSelectionController);
	m_characterInputSet = CharacterInputSet(gameState, gameView, &m_playerWorldSelectionController);


	m_keyDialogInputSet.SetModel(gameView->GetKeyDialogInputModel());
	m_chatTextAreaInputSet.SetModel(gameView->GetChatTextAreaInputModel());
	m_mainMenuInputSet.SetModel(gameView->GetMainMenuInputModel());
	 m_shopMenuInputSet.SetModel(gameView->GetShopMenuInputModel());
	   m_editorInputSet.SetModel(gameView->GetEditorInputModel());
	      m_devInputSet.SetModel(gameView->GetDevInputModel());
	   m_cameraInputSet.SetModel(gameView->GetCameraInputModel());
	m_interfaceInputSet.SetModel(gameView->GetInterfaceInputModel());
	m_characterInputSet.SetModel(gameView->GetCharacterInputModel());

	m_playerInputController = PlayerInputController(&m_gameInputController, &m_StandardMatch5v5State);


	m_playerInputController.AddInputSet(&m_keyDialogInputSet);
	m_playerInputController.AddInputSet(&m_chatTextAreaInputSet);
	m_playerInputController.AddInputSet(&m_mainMenuInputSet);
	m_playerInputController.AddInputSet(&m_shopMenuInputSet);
	m_playerInputController.AddInputSet(&m_editorInputSet);
	m_playerInputController.AddInputSet(&m_devInputSet);
	m_playerInputController.AddInputSet(&m_cameraInputSet);
	m_playerInputController.AddInputSet(&m_interfaceInputSet);
	m_playerInputController.AddInputSet(&m_characterInputSet);

	m_playerInputController.AddInputModel(gameView->GetKeyDialogInputModel());
	m_playerInputController.AddInputModel(gameView->GetChatTextAreaInputModel());
	m_playerInputController.AddInputModel(gameView->GetMainMenuInputModel());
	m_playerInputController.AddInputModel(gameView->GetShopMenuInputModel());
	m_playerInputController.AddInputModel(gameView->GetEditorInputModel());
	m_playerInputController.AddInputModel(gameView->GetDevInputModel());
	m_playerInputController.AddInputModel(gameView->GetCameraInputModel());
	m_playerInputController.AddInputModel(gameView->GetInterfaceInputModel());
	m_playerInputController.AddInputModel(gameView->GetCharacterInputModel());

	//Game Controller refactored stuff
	m_StandardMatch5v5State.InitDebugPrint("Logic: Loading Player Controller. ");

	m_vitalEventController.Init(MobaController::mobaModel);

	m_pathOptimiser.Init(gameState->GetGameMap()->GetPathfinder(), mobaView->GetGameMapView()->GetGroundView());

	m_mobaMessageEventManager.Init(gameState, gameView->GetGameMessage(), gameView->GetCameraDirector(), m_vitalEventController.GetDamageController());

	//if (D3DXCreateTextureFromFile(g_D3D_Device, "BricickSmallBrown.jpg", &m_bricks))
	//	return false;

	/*
	m_boxMesh = LMMesh("Resources/Models/","brick.x", g_D3D_Device);

	m_brickBox = Sprite(
		&m_boxMesh,
		D3DXVECTOR3(160.0f, 0.5f, 240.0f),	//Position
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//Rotation
		D3DXVECTOR3(1.0f, 1.0f, 1.0f),		//Scale
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//Velocity
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//Spin
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),		//Resize
		0.0f);
	*/
	/*
	m_world = D3DXMATRIX(
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0,
		0, 0, 0, 0);
	*/

	//if (FAILED(D3DXCreateEffectFromFile(g_D3D_Device, "Resources/shaders/fogshader.fx", 0, 0, D3DXSHADER_USE_LEGACY_D3DX9_31_DLL, 0, &m_effect, &m_errorLog))) return false;

	//D3DXSHADER_USE_LEGACY_D3DX9_31_DLL
	//D3DXSHADER_ENABLE_BACKWARDS_COMPATIBILITY

	//m_effect->FindNextValidTechnique(NULL, &m_technique);

	//g_D3D_Device->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_COLORVALUE(0.6f, 0.6f, 0.6f, 1.0f));


	return true;

}

void StandardMatch5v5::Update(float deltaTime)
{
	//ToDO GameViewUpdate and GameModelUpdate()???


	////////////////////////////////////////////////////////////////////////////////////
	// 1  UPDATE HOUSEKEEPING  /////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////
	gameState->UpdateGameTime();
	UpdateInput(deltaTime);//update input states/info


	////////////////////////////////////////////////////////////////////////////////////
	// 2  MAIN INPUT BEHAVIOR  /////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////
	//
	// this is where we will stack our ordered input handling 
	// 
	//

	//2.1 Player input updates/////////////////////////////////////////////////////////////

	m_playerWorldSelectionController.Update(deltaTime);

	m_playerInputController.Update(deltaTime);

	////////////////////////////////////////////////////////////////////////////////////
	// 3  MAIN SIMULATION BEHAVIOR /////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////

	//3.1 State Changes: CharacterController updates (player characters)
	for (unsigned int i = 0; i < gameState->GetPlayerCharacters()->size(); i++)
		gameState->GetPlayerCharacters()->at(i)->Update(deltaTime);

	//void 
	for (unsigned int i = 0; i < gameState->GetNeutralTargetControllers()->size(); i++)
	{
		gameState->GetNeutralTargetControllers()->at(i)->Update(deltaTime);
	}
	
	// 3.2 State Changes: Process any game wide events
	UpdateGameEvents(deltaTime);
	UpdateRespawnBehavior(deltaTime);



	////////////////////////////////////////////////////////////////////////////////////
	// 4  APPLY RESULTS AND RULE TO SIMULATION /////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////
	
	

	//4.1 Any stat change object structures and deaths caused
	if (gameState->GetGameOverState() == gameOverStateGameOn)
		m_vitalEventController.Update(deltaTime);


	////////////////////////////////////////////////////////////////////////////////////
	// 5  UPDATES THAT DONT AFFECT GAME STATE  /////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////


	// 5.1 EFFECTS STATES  //////////////////////////////////////////////////////////////

	// 5.1a map element animation stuff
	gameState->GetBoidstorm()->Update(deltaTime);	//ai birds


	// 5.2 CAMERA POSITION  //////////////////////////////////////////////////////////////

	//5.2a Unlocked camera focus (with SPACE)

	gameView->GetCameraDirector()->UpdateCameraStatesAfterPlayerMovement(gameState->GetControlledActor());


	//5.2b set camera view before render
	gameView->GetCameraDirector()->Update(
		deltaTime,
		gameState->GetControlledActor());
	


	// 5.3 INDICATOR STATE  //////////////////////////////////////////////////////////////




	if (gameState->GetGameOverState() == gameOverStateGameOn)
	{
		// 2.1a Game Shop System ////////////////////////////////////////////////////////////

		if (gameView->GetGameShopMenu()->GetUIMenuState() == menuOpened)
		{

			//todo what are we updating and why (missing updates, potentially no reason to call update on a shop)
			//m_tempController was a way to make sure we can change chars in 'dev mode' and have menu reflect our char
			//a solultion: a callback on the char change function can notify or directly change a game shop static member.
			//maybe an item could be 'limited time only' based on a game event. < another reason to maintain updates properly here

			gameState->GetGameShopByName(standardMatch5v5GameShopBase)->Update(deltaTime);
			gameState->GetGameShopByName(standardMatch5v5GameShopNeutral)->Update(deltaTime);
		}

		MobaController::UpdatePlayerControlled();

		gameView->GetGameShopMenu()->Update(
			deltaTime,
			gameState->GetControlledPCC());

		//2.2 Tooltip Controller Input and Behavior/////////////////////////////////////////////
		gameView->GetTooltipController()->Update(deltaTime);


		//2.4 Game Hud updates ////////////////////////////////////////////////////////////////

		gameView->GetHud()->Update(deltaTime, gameState->GetControlledPCC(), gameView->GetControlledPlayerView());


	} //End of if (coreGameStateGameOn)





	//5.3a cast/range indicators
		//update indicators in based on player state
	
	if ( gameState->GetControlAnyPlayerCharacter() )
		gameView->GetIndicatorController()->UpdateIndicators(
		deltaTime,
		*gameState->GetGameElapsedTime(),
		gameState->GetControlledActor());

	else gameView->GetIndicatorController()->UpdateIndicators(
		deltaTime, *gameState->GetGameElapsedTime(),
		gameState->GetControlledActor());


	// 5.4 GAME MESSAGES //////////////////////////////////////////////////////////////
	gameView->GetGameMessage()->Update(deltaTime);


	// 5.5 GAME CURSOR  //////////////////////////////////////////////////////////////
	m_cursorController.Update(deltaTime);

	//5.6 Info Panel Controller //////////////////////////////////////////////////////
	//m_infoPanelController.Update(deltaTime); // it is currently empty, no need to call
	gameView->GetStatPanel()->Update(deltaTime);

	//5.8 HEALTH BARS ///////////////////////////////////////////////////////////////
	//
	// needs to be done after camera update which does vie changes that effect
	// position of health bars positioning on screen
	
	bool friendly = true;

	vector <HealthBar *> * currentVector;

	for (unsigned int vectorCount = 0; vectorCount < 4; vectorCount++)
	{
		currentVector = gameView->GetHealthBarsByType((VitalEntityVectorName)vectorCount);

		for (unsigned int i = 0; i < currentVector->size(); i++)
		{
			switch (vectorCount)
			{
			case vitalEntityVectorNamePlayerCharacter:
				if (gameState->GetControlledActor()->GetTeam()
					== gameState->GetPlayerCharacters()->at(i)->GetActor()->GetTeam())
				{ friendly = true; }
				else
				{ friendly = false; }

				currentVector->at(i)->Update(
					deltaTime,
					gameView->GetCameraDirector()->GetPointerToCurrentCamera(),
					(gameState->GetPlayerCharacters()->at(i)->GetActor()->GetStats()->m_health /
					gameState->GetPlayerCharacters()->at(i)->GetActor()->GetStats()->m_maxHealth),
					friendly,
					i);
				break;

			case vitalEntityVectorNameNPC:
				currentVector->at(i)->Update(
					deltaTime,
					gameView->GetCameraDirector()->GetPointerToCurrentCamera(),
					(gameState->GetNPCs()->at(i)->GetCharacter()->GetActor()->GetStats()->m_health /
					gameState->GetNPCs()->at(i)->GetCharacter()->GetActor()->GetStats()->m_maxHealth),
					false,//not friendly
					i);
				break;

			case vitalEntityVectorNameVitalEntity:

				currentVector->at(i)->Update(
					deltaTime,
					gameView->GetCameraDirector()->GetPointerToCurrentCamera(),
					(gameState->GetVitalEntities()->at(i)->GetStats()->m_health /
					gameState->GetVitalEntities()->at(i)->GetStats()->m_maxHealth),
					false,//not friendly
					i);
				break;

			case vitalEntityVectorNameObjects:
				/**/
				currentVector->at(i)->Update(
					deltaTime,
					gameView->GetCameraDirector()->GetPointerToCurrentCamera(),
					(gameState->GetVitalEntityObjects()->at(i)->GetStats()->m_health /
					gameState->GetVitalEntityObjects()->at(i)->GetStats()->m_maxHealth),
					false,//not friendly
					i);
				break;

			case vitalEntityVectorNameCount:
			default:
				break;
			}
		}
	}




} // END OF UPDATE() //

void StandardMatch5v5::UpdateInput(float deltaTime)
{
	UpdateMouseClientPosition();//gloabls.cpp
	SetCursor(NULL);//hide windows cursor

	//direct x 8 function
	g_inputControl.UpdateDeviceStates();
	m_gameInputController.Update(deltaTime);
}

void StandardMatch5v5::UpdateGameEvents(float deltaTime)
{
	//1. spawn players at start of game
	if (!m_isFirstSpawn)
	{
		if (!sTime1)
		{
			if (*gameState->GetGameElapsedTime() > 0.5f)
			{
				sTime1 = true;
				gameState->GetPlayerCharactersByTeam(yellowTeamName)->at(0)->GetCharacter()->GetActor()->OnEnterStationary();
				gameState->GetPlayerCharactersByTeam(purpleTeamName)->at(0)->GetCharacter()->GetActor()->OnEnterStationary();
			}
		}

		if (!sTime2)
		{
			if (*gameState->GetGameElapsedTime() > 1.0f)
			{
				sTime2 = true;
				gameState->GetPlayerCharactersByTeam(yellowTeamName)->at(1)->GetCharacter()->GetActor()->OnEnterStationary();
				gameState->GetPlayerCharactersByTeam(purpleTeamName)->at(1)->GetCharacter()->GetActor()->OnEnterStationary();
			}
		}

		if (!sTime3)
		{
			if (*gameState->GetGameElapsedTime() > 1.5f)
			{
				sTime3 = true;
				gameState->GetPlayerCharactersByTeam(yellowTeamName)->at(2)->GetCharacter()->GetActor()->OnEnterStationary();
				gameState->GetPlayerCharactersByTeam(purpleTeamName)->at(2)->GetCharacter()->GetActor()->OnEnterStationary();
			}
		}

		if (!sTime4)
		{
			if (*gameState->GetGameElapsedTime() > 2.0f)
			{
				sTime4 = true;
				gameState->GetPlayerCharactersByTeam(yellowTeamName)->at(3)->GetCharacter()->GetActor()->OnEnterStationary();
				gameState->GetPlayerCharactersByTeam(purpleTeamName)->at(3)->GetCharacter()->GetActor()->OnEnterStationary();
			}
		}

		if (*gameState->GetGameElapsedTime() > 2.5f)
		{
			m_isFirstSpawn = true;
			gameState->GetPlayerCharactersByTeam(yellowTeamName)->at(4)->GetCharacter()->GetActor()->OnEnterStationary();
			gameState->GetPlayerCharactersByTeam(purpleTeamName)->at(4)->GetCharacter()->GetActor()->OnEnterStationary();

			gameView->GetCameraDirector()->ActionToggleFreeCamera(gameState->GetOwnedPCC()->GetCharacter()->GetActor());
			gameView->GetCameraDirector()->SetIsCameraLocked(false);

		}
	}
}

void StandardMatch5v5::UpdateRespawnBehavior(float deltaTime)
{
	bool needsRespawn;
	//ActorState state;
	Actor * c = NULL;
	Recall * targetsRecall = NULL;

	vector<Character *> * characterList = NULL;
	//for

	for (unsigned int h = 0; h < gameState->GetCharacterLists()->size(); h++)
	{
		characterList = gameState->GetCharacterLists()->at(h);

		for (unsigned int i = 0; i < characterList->size(); i++)
		{
			needsRespawn = false;

			c = characterList->at(i)->GetActor();

			switch (c->GetState())
			{
			case actorDead:
				if (c->GetTimer()->GetState() == timerFinished)
				{
					needsRespawn = true;
					c->OnExitDeathState();
				}
				break;
			case actorRecall:

				targetsRecall = (Recall*)gameState->GetPlayerCharacters()->at(i)->GetAbilities()->at(actionCastRecall);

				if (targetsRecall->GetRecallTimer()->GetState() == timerFinished)
				{
					targetsRecall->Success();
					needsRespawn = true;
				}
				break;
			default:
				break;
			}

			if (needsRespawn)
			{
				LMVector3 * spawnpoint = nullptr;

				if (true)//new respawn behaviour
				{
					int spawnNo = (int)floor(rand() % 5);
					if (spawnNo > 4) spawnNo = 4;

					float randx = floor((rand() % 10) - 5.0f);
					float randz = floor((rand() % 10) - 5.0f);

					switch (c->GetTeam())
					{
					case yellowTeamName://intentional fall through case
					case purpleTeamName:
  						spawnpoint = &gameState->GetTeamSpawns(c->GetTeam())->at(spawnNo);
						break;
					case teamNameNeutral:
						spawnpoint = ((NPCController*)characterList->at(i))->GetSpawn(0);
						/*
						if (h == 0)
						{
							LMVector3 * sp = ((NPCController*)actorList->at(i))->GetSpawn(0);
							c->Respawn(sp->x, sp->y, sp->z);
						}
						break;
						*/
					}

					characterList->at(i)->OnRespawn(spawnpoint->x + randx, spawnpoint->y, spawnpoint->z + randz);
				}

				/*
				else//old respawn behavior
				{
					switch (c->GetTeam())
					{
					case yellowTeamName:
						c->Respawn(
							gameState->GetTeamSpawns(yellowTeamName)->at(0).x,
							gameState->GetTeamSpawns(yellowTeamName)->at(0).y,
							gameState->GetTeamSpawns(yellowTeamName)->at(0).z);
						break;
					case purpleTeamName:
						c->Respawn(
							gameState->GetTeamSpawns(purpleTeamName)->at(0).x,
							gameState->GetTeamSpawns(purpleTeamName)->at(0).y,
							gameState->GetTeamSpawns(purpleTeamName)->at(0).z);
						break;
					}
				}
				*/

			}
		}
	}
}

void StandardMatch5v5::Render()
{
	//TODO Move Render() to MobaView class or similar

	RenderBegin();

	//m_effect->SetMatrix("View", gameView->GetCameraDirector()->GetPointerToCurrentCamera()->GetViewMatrix());
	//m_effect->SetMatrix("Projection", gameView->GetCameraDirector()->GetPointerToCurrentCamera()->GetProjectionMatrix());
	//m_effect->SetMatrix("World", &m_world);

	//m_effect->Begin(NULL,NULL);
	//m_effect->BeginPass(0);


	/////////////////////////////////////////////////////////////////////
	// Render Device Settings ///////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////


	switch (gameState->GetControlledActor()->GetState())
	{
	case actorSleeping:
		gameView->GetGameLightingController()->GameLightsOff();
		g_D3D_Device->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_COLORVALUE(0.0f, 0.0f, 0.0f, 1.0f));
		break;
	default:
		gameView->GetGameLightingController()->GameLightsOn();
		g_D3D_Device->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_COLORVALUE(0.8f, 0.8f, 0.8f, 1.0f));
	}

	/////////////////////////////////////////////////////////////////////
	// Render Environment ///////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////

	gameView->GetBoidstormView()->Render();

	//AFFECTED BY LIGHTING
	//NOT EFFECTED BY ALPHA BLENDS
	//g_D3D_Device->SetRenderState(D3DRS_LIGHTING, FALSE);
	//m_brickBox.Render();
	//g_D3D_Device->SetRenderState(D3DRS_LIGHTING, TRUE);

	for (unsigned int index = 0; index < gameState->GetVitalEntities()->size(); index++)
	{
		gameView->GetVitalEntityViews()->at(index)->Render();
	}

	// Walls //////////////////////////////////////////////////////////

	//m_effect->SetMatrix("World", gameView->GetGroundView()->GetWorldMatrix());

	//m_effect->Begin(NULL, NULL);
	//m_effect->BeginPass(0);
	gameView->GetGameMapView()->Render(); //Ground rendered here. also incs. all enviro, walls
	

	//m_effect->EndPass();
	//m_effect->End();
	

	/* todo use wall views idea?
	for (unsigned int index = 0; index < gameState->GetWalls()->size(); index++)
	{ 
		gameView->GetWallViews()->at(index)->Render();
	}*/

	
	g_D3D_Device->SetRenderState(D3DRS_LIGHTING, FALSE);
	m_nodeEditor.Render();
	g_D3D_Device->SetRenderState(D3DRS_LIGHTING, TRUE);

	// Ground ///////////////////////////////////////////////////////////

	//g_D3D_Device->SetRenderState(D3DRS_LIGHTING, FALSE);

	//g_D3D_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//g_D3D_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//gameState->GetGround()->Render();
	//ground rendering moved to "walls"

	//g_D3D_Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
	//g_D3D_Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);

	//g_D3D_Device->SetRenderState(D3DRS_LIGHTING, TRUE);


	/////////////////////////////////////////////////////////////////////
	// Indicator UI /////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////
	
	if (gameState->GetGameOverState() == gameOverStateGameOn)
	{
		g_deviceControl.SetRenderSettings(customRenderSettingsGameUI);

		//render range indicators for tooltips that are hovered over

		if (gameView->GetTooltipController()->GetTimer()->GetState() != timerFinished)
		{
			if (gameView->GetTooltipController()->GetAbilityOwner() != NULL)
			{
				gameView->GetIndicatorController()->UpdateRangeIndicatorWithAbility(
					gameView->GetTooltipController()->GetAbilityOwner()
					);
				gameView->GetIndicatorController()->RenderRangeIndicator(
					gameView->GetTooltipController()->GetAbilityOwner()->GetCastType()
					);
			}
			else gameView->GetIndicatorController()->RenderRangeIndicator();
		}
		else gameView->GetIndicatorController()->RenderRangeIndicator();


		//Debug On: NPC auto agro range


		if (gameState->m_isDebugTextOn) gameView->GetIndicatorController()->RenderDebugRanges();


		// Render Shop Zone Feedback ///////////////////////////////////////
		gameView->GetIndicatorController()->RenderShopZones();

	}//end indicator ui



	//3d render phase (change render settings accordingly)
	g_deviceControl.SetRenderSettings(customRenderSettingsGame3d);


	/////////////////////////////////////////////////////////////////////
	// Render Actors ////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////

	// Render PlayerCharacterViews //////////////////////////////////////

	for (unsigned int i = 0; i < gameView->GetPlayerCharacterViews()->size(); i++)
	{
		
		//m_effect->SetMatrix("World", gameView->GetPlayerCharacterViews()->at(i)->GetActorView()->GetWorldMatrix());

		//m_effect->Begin(NULL, NULL);
		//m_effect->BeginPass(0);
		gameView->GetPlayerCharacterViews()->at(i)->Render();

		//m_effect->EndPass();
		//m_effect->End();


		
	}

	// Render NPCViews //////////////////////////////////////////////////

	for (unsigned int index = 0; index < gameView->GetNPCViews()->size(); index++)
	{


		//m_effect->SetMatrix("World", gameView->GetNPCViews()->at(index)->GetActorView()->GetWorldMatrix());

		//m_effect->Begin(NULL, NULL);
		//m_effect->BeginPass(0);

		gameView->GetNPCViews()->at(index)->Render();

		//m_effect->EndPass();
		//m_effect->End();


		
	}

	// Render QuestViews / Members /////////////////////////////////////

	for (unsigned int index = 0; index < gameView->GetQuestViews()->size(); index++)
	{
		gameView->GetQuestViews()->at(index)->Render();

	}
	
	/////////////////////////////////////////////////////////////////////
	// Render UI ////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////
	
	if (gameState->m_isDebugTextOn) m_pathOptimiser.Render();
	
	RenderUI();//GUI
	
	/////////////////////////////////////////////////////////////////

	RenderEnd();
	
}

void StandardMatch5v5::RenderUI()
{
	MobaController::RenderUIBegin();

	mobaView->GetIndicatorController()->RenderIndicators();

	//TODO Render() and RenderUI to be moved to MobaViewState();

	gameView->GetCameraDirector()->m_gameCameraThisUpdate = gameView->GetCameraDirector()->GetUsingCamera();


	// THAT 3D TEXT STUFF how we used to have it
	if (false)
	{
		g_deviceControl.SetRenderSettings(customRenderSettingsGame3d);

		for (unsigned int healthCount = 0; healthCount < gameState->GetPlayerCharacters()->size(); healthCount++)
		{
			if (gameState->GetPlayerCharacters()->at(healthCount)->GetActor()->GetState() != actorDead)
			{
				gameView->GetHealthBarsByType(vitalEntityVectorNamePlayerCharacter)->at(healthCount)->RenderName(true);
			}
		}

		g_deviceControl.SetRenderSettings(customRenderSettingsGameUI);
	}


	

	//interface camera setting this up in Camera Director
	gameView->GetCameraDirector()->SetUsingCamera(usingInterfaceCamera);

	
	//3d FONT RENDER ATTEMPTS
	for (unsigned int healthCount = 0; healthCount < gameState->GetPlayerCharacters()->size(); healthCount++)
	{
		if (gameState->GetPlayerCharacters()->at(healthCount)->GetActor()->GetState() != actorDead)
		{
			gameView->GetHealthBarsByType(vitalEntityVectorNamePlayerCharacter)->at(healthCount)->RenderName3d();
		}
	}
	



	
	// HP BAR /////////////////////////////////////////////////////////
	DWORD n;
	g_D3D_Device->GetSamplerState(0, D3DSAMP_MIPFILTER, &n);
	g_D3D_Device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_NONE);

	vector <HealthBar *> * currentVector;

	for (int vectorCount = 0; vectorCount < 3; vectorCount++)
	{
		currentVector = gameView->GetHealthBarsByType((VitalEntityVectorName)vectorCount);

		for (unsigned int i = 0; i < currentVector->size(); i++)
		{
			switch (vectorCount)
			{
			case vitalEntityVectorNamePlayerCharacter:
				if (gameState->GetPlayerCharacters()->at(i)->GetActor()->GetState() != actorDead)
				{
					currentVector->at(i)->Render();
					gameView->GetHealthBarsByType(vitalEntityVectorNamePlayerCharacter)->at(i)->RenderName(false);
				}
				break;

			case vitalEntityVectorNameNPC:
				if (gameState->GetNPCs()->at(i)->GetCharacter()->GetActor()->GetStats()->m_health > 0.0f)
				{
					currentVector->at(i)->Render();
					gameView->GetHealthBarsByType(vitalEntityVectorNameNPC)->at(i)->RenderName(false);
				}
				break;

			case vitalEntityVectorNameVitalEntity:
				if (gameState->GetVitalEntities()->at(i)->GetStats()->m_health > 0.0f)
					currentVector->at(i)->Render();
				break;

			case vitalEntityVectorNameObjects:
				currentVector->at(i)->Render();
				break;
			}
		}
	}
	

	g_D3D_Device->SetSamplerState(0, D3DSAMP_MIPFILTER, n);

	//Game Messages //////////////////////
	gameView->GetGameMessage()->Render();

	if (gameState->GetGameOverState() == gameOverStateGameOn)
	{
		//PLAYER GUI ///////////////////////

		//INFO PANEL (bg need needs to be below hud top bar)
		//gameView->GetInfoPanelController()->RenderInfoPanel();

		//Stat Panel (TAB for scores)
		gameView->GetStatPanel()->Render();

		//HUD
		gameView->GetHud()->Render();

		// Game/Teams GUI
		//gameView->GetInfoPanelController()->Render();


		gameView->GetDialogScreenController()->Render();


		gameView->GetHud()->RenderTextStuff();
		// UI TEXT //////////////////////////////////////////////////

		//CHAT STUFF

		//SHOP
		gameView->GetGameShopMenu()->Render();

		//Tooltips
		gameView->GetTooltipController()->Render();
	
	}

	//PAUSE LAYER (3rd highest)

	//ESCAPEMENU (2nd highest)
	gameView->GetMainMenu()->Render();

	//ESCAPE MENU DIALOGS (screen on top of all others)

	gameView->GetKeyDialog()->Render();

	
	// Render Cursor //////////////////////////////////////////////////
	//
	//requres us to change back to camera used for interface things
	//

	gameView->GetGameCursor()->Render();


	// END OF RENDER UI housekeeping ///////////////////////////////////
	//
	// set ourself up to render game on next render cycle




	//gameView->GetCameraDirector()->SwitchToLastState();


	//

	MobaController::RenderUIEnd();
}



//Accessors
StandardMatch5v5State * StandardMatch5v5::GetStandardMatch5v5State()
{
	return & m_StandardMatch5v5State;
}