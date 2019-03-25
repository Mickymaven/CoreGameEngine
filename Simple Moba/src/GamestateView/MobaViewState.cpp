#include "MobaViewState.h"


string MobaViewState::m_avatarPath[characterNameCount] =
{
	"Resources/UI/Icons/Grey.png",
	"Resources/UI/Icons/Grey.png",
	"Resources/UI/Icons/Grey.png",
	"Resources/UI/Icons/Grey.png",
	"Resources/UI/Icons/Grey.png",
	"Resources/UI/Icons/Grey.png",
	"Resources/UI/Icons/Grey.png",
	"Resources/UI/Icons/Grey.png"
};

MobaViewState::MobaViewState()
{
	OutputDebugString("MobaViewState::MobaViewState\n");
	m_loadProgress = 0;
	m_loadSize = mobaViewInitPhaseCount;
	m_controlledPlayerView = nullptr;
}

MobaViewState::~MobaViewState()
{
	delete m_gameMapView;
	m_gameMapView = nullptr;

	for (unsigned int i = 0; i < m_playerCharacterViews.size(); i++)
	{
		delete m_playerCharacterViews.at(i);
		m_playerCharacterViews.at(i) = nullptr;
	}

	for (unsigned int i = 0; i < m_allShopViews.size(); i++)
	{
		if (m_allShopViews.at(i) != nullptr)
		{
			delete m_allShopViews.at(i);
			m_allShopViews.at(i) = nullptr;
		}
	}
}

bool MobaViewState::Init(GameConfiguration * gameConfiguration)
{
	m_gameConfiguration = gameConfiguration;

	return true;
}

bool MobaViewState::InitSelectedPhase(int initPhase)
{
	///////////////////////////////////////////////////////////////
	if (initPhase == mobaViewInitPhaseTheme)
	{///////////////////////////////////////////////////////////

		QueryPerformanceCounter(&m_initStart);
		QueryPerformanceFrequency(&m_init_tFrequency);

		if (!InitTheme(0)) return false;


		m_viewProfile.m_aspectProfile = &m_aspectProfile;
		m_viewProfile.m_themeResourceProfile = &m_themeResourceProfile;


		string path = "Resources/Themes/";
		path.append(m_gameConfiguration->GetThemeName());
		path.append("/ModeData/StandardMatch5v5.profile");

		if (!m_aspectProfileIO.ReadData(path, &m_aspectProfile)) return false;

		path = "Resources/Themes/";
		path.append(m_gameConfiguration->GetThemeName());
		path.append("/theme.paths");

		m_themeResourceProfile.SetCurrentAspect(m_aspectProfile.GetCurrentAspect());

		if (!m_themeProfileIO.ReadData(path, &m_themeResourceProfile)) return false;

		//Has to happen before npc view init (NPC views now form part of the game shop setup).
		m_gameShopOrigin.x = m_viewProfile.m_aspectProfile->GetXForElement(gameElementTradeMenuBackground);
		m_gameShopOrigin.y = m_viewProfile.m_aspectProfile->GetYForElement(gameElementTradeMenuBackground);
		m_gameShopSize.x = m_viewProfile.m_aspectProfile->GetWidthForElement(gameElementTradeMenuBackground);
		m_gameShopSize.y = m_viewProfile.m_aspectProfile->GetHeightForElement(gameElementTradeMenuBackground);

		ShopInventoryView::m_selectedPlayerController = gameState->GetControlledPCC();

		ShopInventoryView::m_tooltipController = &m_tooltipController;
		
		//These have to happen before npc/player character  init
		ShopInventoryView::m_itemFactory = gameState->GetItemFactory();
		ShopInventoryView::m_lightweightItemViews = m_itemViewFactory.GetLightweightItemViews();
		
		if (!m_itemViewFactory.Init(g_D3D_Device, &m_viewProfile, gameState->GetItemFactory(), &m_abilityViewFactory))return false;
		
		//character lmmesh init with device
		m_gameAssetFactory.Init(g_D3D_Device);

		m_gameMapViewFactory.Init(&m_gameAssetFactory);


	}
	///////////////////////////////////////////////////////////////


	///////////////////////////////////////////////////////////////
	if (initPhase == mobaViewInitPhaseInput)
	{///////////////////////////////////////////////////////////
		m_inputModelList.push_back(&m_keyDialogInputModel);
		m_inputModelList.push_back(&m_chatTextAreaInputModel);
		m_inputModelList.push_back(&m_mainMenuInputModel);
		m_inputModelList.push_back(&m_shopMenuInputModel);
		m_inputModelList.push_back(&m_editorInputModel);
		m_inputModelList.push_back(&m_devInputModel);
		m_inputModelList.push_back(&m_cameraInputModel);
		m_inputModelList.push_back(&m_interfaceInputModel);
		m_inputModelList.push_back(&m_characterInputModel);

		for (unsigned int i = 0; i < m_inputModelList.size(); i++)
			if (!m_inputModelList.at(i)->Init("")) return false;

		for (unsigned int i = 0; i < m_inputModelList.size(); i++)
		{
			if (!m_keybindData.ReadData(m_inputModelList.at(i)->m_path,
				&m_inputModelList.at(i)->m_keybinds)) return false;
		}

	}
	////////////////////////////////////// /////////////////////////
	
	///////////////////////////////////////////////////////////////
	if (initPhase == mobaViewInitPhaseActors)
	{///////////////////////////////////////////////////////////

		m_characterViewFactory.Init(&m_actorViewFactory, &m_abilityViewFactory);
		m_playerCharacterViewFactory.Init(&m_characterViewFactory);
		m_npcViewFactory.Init(&m_characterViewFactory);

		//Trade inv bounds needed for Character Init.
		//make these bounds part of view profile derivied variables
		LMVector4 bounds = LMVector4(m_gameShopOrigin.x, m_gameShopOrigin.y, m_gameShopOrigin.x + m_gameShopSize.x, m_gameShopOrigin.x + m_gameShopSize.y);

		vector< PlayerCharacterView *> playCharView;

		playCharView.resize(gameState->GetPlayerCharacters()->size(), NULL);

		for (unsigned int i = 0; i < gameState->GetPlayerCharacters()->size(); i++)
		{
			if (!m_playerCharacterViewFactory.ConstructPlayerCharacterView(
				g_D3D_Device,
				&playCharView.at(i),
				gameState->GetPCCs()->at(i),
				m_gameConfiguration->GetPlayerCharacterNames()->at(i),
				&m_gameConfiguration->GetCustomAbilities()->at(i),
				&m_viewProfile,
				&m_theme,
				&bounds)) return false;

			m_playerCharacterViews.push_back(playCharView.at(i));

		}

		//controlled init view
		for (unsigned int i = 0; i < gameState->GetPlayerCharacters()->size(); i++)
		{
			if (m_gameConfiguration->GetPlayerIDs()->at(i) == 1) //g_playerID
			{
				m_controlledPlayerView = m_playerCharacterViews.at(i);
			}
		}

		//sort player characters into team vectors
		m_playerTeams.resize(2);

		for (unsigned int i = 0; i < m_playerCharacterViews.size(); i++)
		{
			m_playerTeams.at(
				m_playerCharacterViews.at(i)->GetPlayerCharacterController()->GetCharacter()->GetActor()->GetTeam()

				).push_back(m_playerCharacterViews.at(i));
		}

		//2. NPC Init //////////////////////////////////////////
		NPCView * npcView = NULL;
		CharacterView * characterView = NULL;
		ActorView * actorView = NULL;

		//GAME MODE CONFIGURATION FOR NPCs (read from game mode configuration for npcs)

		//LMMesh * npcMesh = m_gameAssetFactory.GetActorMesh(characterGrey);
		
		//todo npc customs in game state (they should be more like player characters).

		vector<AbilityName> custom = {abilityElixirBurst, abilityEternalLight};


		m_npcViews.resize(gameState->GetNPCs()->size());

		for (unsigned int i = 0; i < gameState->GetNPCs()->size(); i++)
		{
			if (!m_npcViewFactory.ConstructNPCView(
				g_D3D_Device,
				&m_npcViews.at(i),
				gameState->GetNPCs()->at(i),
				characterGrey,
				&custom,
				&m_viewProfile,
				&m_theme,
				&bounds)) return false;

			m_playerCharacterViews.push_back(playCharView.at(i));

		}


		/*
		for (unsigned int i = 0; i < gameState->GetNPCs()->size(); i++)
		{
			actorView = new ActorView(g_D3D_Device, gameState->GetNPCs()->at(i)->GetCharacter()->GetActor(), npcMesh);
			characterView = new CharacterView(gameState->GetNPCs()->at(i)->GetCharacter(), actorView);
			npcView = new NPCView(g_D3D_Device, gameState->GetNPCs()->at(i), characterView,
				&m_viewProfile, &m_theme, &bounds);	

			m_npcViews.push_back(npcView);
		}
		*/


	} //End Actor View Init
	///////////////////////////////////////////////////////////////



	  ///////////////////////////////////////////////////////////////
	if (initPhase == mobaViewInitPhaseQuests)
	{///////////////////////////////////////////////////////////

		//ShopInv Views that coorespond to invCodes ().

		//Iterate over all quests
		//for each shop Inv get code
		//init shop inv view instance into m_allShopViews (parameter each shop in quest);
		//only if we havent already inited a view for this shop inventory.

		Quest * quest = nullptr;
		vector<ShopInventory *> * shopInvList = nullptr;
		InvName currentInvName;


		//todo this is copy pasta
		LMVector4 bounds = LMVector4(m_gameShopOrigin.x, m_gameShopOrigin.y, m_gameShopOrigin.x + m_gameShopSize.x, m_gameShopOrigin.x + m_gameShopSize.y);


		m_allShopViews.resize(invNameCount, nullptr);

		for (unsigned int questCount = 0; questCount < gameState->GetQuests()->size(); questCount++)
		{
			quest = gameState->GetQuests()->at(questCount);
			shopInvList = quest->GetInventories();

			for (unsigned int shopInvCount = 0; shopInvCount < shopInvList->size(); shopInvCount++)
			{
				currentInvName = (InvName)shopInvList->at(shopInvCount)->GetInventoryID();

				if (m_allShopViews.at(currentInvName) == nullptr)
				{
					m_allShopViews.at(currentInvName) = new ShopInventoryView();

					if (! m_allShopViews.at(currentInvName)->Init(&m_viewProfile, &m_theme, &bounds, shopInvList->at(shopInvCount))) return false;
				}
			}
		}


		ShopInventory * shopInv = nullptr;

		for (unsigned int invCount = 0; invCount < gameState->GetShops()->size(); invCount++)
		{
			shopInv = gameState->GetShops()->at(invCount).GetShopInvVector()->at(0);
			currentInvName = (InvName)shopInv->GetInventoryID();
			
			if (m_allShopViews.at(currentInvName) == nullptr)
			{
				m_allShopViews.at(currentInvName) = new ShopInventoryView();

				if (!m_allShopViews.at(currentInvName)->Init(&m_viewProfile, &m_theme, &bounds, shopInv)) return false;
			}
		}

		

		//temp init trade inventory view objects as part of character view
		//init of them happens here seperate from factory
		//while we test this inv id to access view object idea

		for (unsigned int i = 0; i < m_npcViews.size(); i++)
		{
			m_npcViews.at(i)->InitTradeView(&m_viewProfile, &m_theme, &bounds, &m_allShopViews);
		}

		for (unsigned int i = 0; i < m_playerCharacterViews.size(); i++)
		{
			m_playerCharacterViews.at(i)->InitTradeView(&m_viewProfile, &m_theme, &bounds, &m_allShopViews);
		}

		//todo views for Independent TradeInventory (the team zone stuff).

		// Quest Views


		m_owlQuestView.Init(gameState->GetQuests()->at(0), &m_viewProfile, &m_theme, &bounds);

		LMMesh * m = new LMMesh("Resources/Quests/VisionOwl/Models/", "drill-tool.x", g_D3D_Device);

		//todo temp init of new item view specific stufff in this way
		m_owlQuestView.AddItemView(g_D3D_Device, &((QuestItems*)gameState->GetQuests()->at(0))->GetItems()->at(0), m);
		m_owlQuestView.AddItemView(g_D3D_Device, &((QuestItems*)gameState->GetQuests()->at(0))->GetItems()->at(1), m);

		m_questViews.push_back(&m_owlQuestView);


	} //End mobaViewInitPhaseQuests
	  ///////////////////////////////////////////////////////////////



	///////////////////////////////////////////////////////////////
	if (initPhase == mobaViewInitPhaseAssets)
	{///////////////////////////////////////////////////////////

		m_boidstormView = BoidstormView(g_D3D_Device, gameState->GetBoidstorm());

		LMMesh * spriteMesh = NULL;
		SpriteView * spriteView = NULL;

		//walls sprite class
		
		InitDebugPrint("Environment: Pre Ground Init.");
		
		if (constructGameMapCodeError == m_gameMapViewFactory.ConstructGameMapView(
			&m_gameMapView,
			gameState->GetGameMap(),
			m_gameConfiguration->GetMapId()
			)) return false;

		//m_groundView = SpriteView(g_D3D_Device, gameState->GetGround(), m_gameAssetFactory.GetAssetMesh(assetBarebonesGroundStandard1));



		/* not old, use for wall process stuff later, probably in GameMapView

		for (unsigned int i = 0; i < gameState->GetWalls()->size(); i++)
		{
			//gotta make this less volatile (conversion tables confuse).
			spriteMesh = m_gameAssetFactory.GetAssetMesh((AssetMeshName)gameState->GetSpriteConfig()->at(i));
			spriteView = new SpriteView(g_D3D_Device, gameState->GetWalls()->at(i), spriteMesh);

			m_wallViews.push_back(spriteView);
		}

		InitDebugPrint("Environment: Post Ground Init.");//tests big texture load different sytstems

		*/


		VitalEntityView * vitalEntityView = NULL;

		//assets of vital entity class
		for (unsigned int i = 0; i < gameState->GetVitalEntities()->size(); i++)
		{
			spriteMesh = m_gameAssetFactory.GetAssetMesh((AssetMeshName)gameState->GetAssetConfig()->at(i));
			vitalEntityView = new VitalEntityView(g_D3D_Device, gameState->GetVitalEntities()->at(i), spriteMesh);

			m_vitalEntityViews.push_back(vitalEntityView);
		}
	}
	////////////////////////////////////// /////////////////////////


	///////////////////////////////////////////////////////////////
	if (initPhase == mobaViewInitPhaseInputGUI)
	{///////////////////////////////////////////////////////////
	
		//Game Message
		m_gameMessage = GameMessage(m_theme.m_messageText.m_font);


		//BUFF LIGHTWEIGHT INIT
		if (!m_buffViewFactory.Init(&m_viewProfile)) return false;



		//STATS PANEL
		if (!m_statPanel.Init(
			&m_viewProfile,
			&m_theme,
			gameState,
			gameState->GetTeamControllersAsVector(yellowTeamName),
			gameState->GetTeamControllersAsVector(purpleTeamName),
			&m_tooltipController,
			m_itemViewFactory.GetLightweightItemViews()
			)) return false;

		//main menu key dialog
		LMVector2 origin(100.0f, 100.0f);
		LMVector2 size(250.0f, 125.0f);

		if (!m_keyDialog.Init("KeyDialog", "Set our key",
			&m_viewProfile, &m_theme, &origin, &size)) return false;

		//main menu
		origin = LMVector2(100.0f, 100.0f);
		size = LMVector2(1065.0f, 785.0f);
		if (!m_mainMenu.Init(&m_mainMenuInputModel, &m_viewProfile, &m_theme, &origin, &size,
			&m_inputModelList, &m_keyDialog, &m_keybindData)) return false;

		//shop menu
		//vector<TradeInventory *> * gameShops,
		//	vector<ItemView *> * lightweightItemViews,
		//	ItemFactory * itemFactory,
		//GameAssetFactory * gameAssetFactory,



		if (!m_gameShopMenu.Init(&m_mainMenuInputModel, &m_viewProfile, &m_theme, &m_gameShopOrigin, &m_gameShopSize,
			gameState->GetShops(),
			&m_allShopViews,
			m_itemViewFactory.GetLightweightItemViews(),
			gameState->GetItemFactory(),
			&m_gameAssetFactory, &m_tooltipController, gameState->GetControlledPCC())) return false;
		
		// Player main GUI
		if (!m_mobaHud.Init(
			gameState,
			&m_viewProfile,
			&m_theme,
			&m_cameraDirector,
			m_gameConfiguration,
			true,
			gameState->GetGameElapsedTime(),
			&m_inputModelList,
			m_buffViewFactory.GetLightweightBuffViews(), 
			m_itemViewFactory.GetLightweightItemViews(),
			&m_tooltipController,
			gameState->GetControlledPCC())) return false;

		// Info Panel Controller
		//InitDebugPrint("UI: Info Panel");
		if (!m_infoPanelController.Init(&m_gameAssetFactory, gameState, m_gameConfiguration, m_itemViewFactory.GetLightweightItemViews(), &m_tooltipController)) return false;

		//dialog
		if (!m_dialogScreenController.Init(&m_viewProfile, &m_theme, &m_gameShopMenu)) return false;

		if (!InitDialog(languageEN) ) return false;

		//Cursor
		if (!m_cursor.Init(64.0f, 64.0f)) return false;

	}
	///////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////
	if (initPhase == mobaViewInitPhaseIndicators) 
	{///////////////////////////////////////////////////////////
		//Tooltip Init
		if (!m_tooltipController.Init()) return false;

		//Inidicator Init
		if (!m_indicatorController.Init(gameState, &m_cameraDirector, &m_cursor, &m_theme.m_shopZoneText, m_gameMapView->GetGroundView())) return false;
		//todo might not want to do ground hittests in this controller anymore

		// Health Bars ///////////////////////////////////////////////////
		//InitDebugPrint("UI: Loading New Health Bars");

		LPDIRECT3DTEXTURE9 friendlyFrameTexture;
		LPDIRECT3DTEXTURE9 friendlyHealthTexture;
		LPDIRECT3DTEXTURE9 opponentFrameTexture;
		LPDIRECT3DTEXTURE9 opponentHealthTexture;

		if (D3DXCreateTextureFromFile(g_D3D_Device, "Resources/misc/health-bar-frame-friendly.png", &friendlyFrameTexture))
			return false;
		if (D3DXCreateTextureFromFile(g_D3D_Device, "Resources/misc/health-bar-frame-opponent.png", &opponentFrameTexture))
			return false;
		if (D3DXCreateTextureFromFile(g_D3D_Device, "Resources/misc/health-bar-green.png", &friendlyHealthTexture))
			return false;
		if (D3DXCreateTextureFromFile(g_D3D_Device, "Resources/misc/health-bar-red.png", &opponentHealthTexture))
			return false;

		

		vector <HealthBar *> * currentVector;

		for (unsigned int vectorCount = 0; vectorCount < 3; vectorCount++)
		{
			switch (vectorCount)
			{
			case vitalEntityVectorNamePlayerCharacter:
				//m_newHealthBars = new vector < HealthBar * >;
				m_pcHealthBars.resize(gameState->GetPlayerCharacters()->size());
				currentVector = &m_pcHealthBars;
				break;

			case vitalEntityVectorNameNPC:
				//m_newNeutralHealthBars = new vector < HealthBar * >;
				m_npcHealthBars.resize(gameState->GetNPCs()->size());
				currentVector = &m_npcHealthBars;
				break;

			case vitalEntityVectorNameVitalEntity:
				//m_chestHealthBars = new vector < HealthBar * >;
				m_chestHealthBars.resize(gameState->GetVitalEntities()->size());
				currentVector = &m_chestHealthBars;
				break;
			}

			for (unsigned int i = 0; i < currentVector->size(); i++)
			{
				currentVector->at(i) = new HealthBar(
					friendlyFrameTexture,
					friendlyHealthTexture,
					opponentFrameTexture,
					opponentHealthTexture,
					&m_isHealthMirrorOn,
					m_theme.m_mediumText.m_font,
					&m_theme.m_mediumText.m_color
					);

				switch (vectorCount)
				{
				case vitalEntityVectorNamePlayerCharacter:
					if (!currentVector->at(i)->Init(
						((VitalEntity*)gameState->GetPlayerCharacters()->at(i)->GetActor()))) return false;

					if (!currentVector->at(i)->Init3DNamesForActors(
						gameState->GetPlayerCharacters()->at(i)->GetActor())) return false;

					break;
				case vitalEntityVectorNameNPC:
					if (!currentVector->at(i)->Init(
						((VitalEntity*)gameState->GetNPCs()->at(i)->GetCharacter()->GetActor()))) return false;
					break;
				case vitalEntityVectorNameVitalEntity:
					if (!currentVector->at(i)->Init(
						gameState->GetVitalEntities()->at(i))) return false;
					break;
				}
			}
		}

		// HP Bar mirror indicators
		m_isHealthMirrorOn = false;

	}
	///////////////////////////////////////////////////////////////


	///////////////////////////////////////////////////////////////
	if (initPhase == mobaViewInitPhaseLighting)
	{///////////////////////////////////////////////////////////
		
		if (!m_gameLightingController.Init()) return false;
	}
	///////////////////////////////////////////////////////////////


	///////////////////////////////////////////////////////////////
	if (initPhase == mobaViewInitPhaseCameras)
	{///////////////////////////////////////////////////////////

		if (!m_cameraDirector.Init(gameState,&m_playerCharacterViews)) return false;
	}
	///////////////////////////////////////////////////////////////
	

	////////////////////////////////////////////////////////////////////////////////////////////
	if (initPhase == mobaViewInitPhaseCount){ ///////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////
		OutputDebugString("(VIEW DONE)\n");

	}//////////////////////////////////////////////////////////////////////////////////


	return true;
}

string MobaViewState::GetInitPhaseString(int initPhase)
{
	switch ((MobaViewInitPhase)initPhase)
	{
	case mobaViewInitPhaseTheme:		return "View: Theme"; break;
	case mobaViewInitPhaseInput:		return "View: Input"; break;
	case mobaViewInitPhaseInputGUI:		return "View: GUI"; break;
	case mobaViewInitPhaseIndicators:	return "View: Indicators"; break;
	case mobaViewInitPhaseLighting:		return "View: Lighting"; break;
	case mobaViewInitPhaseCameras:		return "View: Cameras"; break;
	case mobaViewInitPhaseCount:		return "View Initialised."; break;
	default: return ""; break;
	};
}


bool MobaViewState::InitTheme(int theme)
{	
	if (theme==0)
	{

		//font stuff to fix up
		AddFontResourceEx("Resources/UI/Fonts/NanumScript.ttc", FR_PRIVATE, 0);
		
		/*
		if (FAILED(
			D3DXCreateFont(g_D3D_Device, 22, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE, "Nanum Brush Script", &m_UXFont))) return false; // DEFAULT_QUALITY //FW_BOLD

		if (FAILED(
			D3DXCreateFont(g_D3D_Device, 18, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE, "Nanum Brush Script", &m_UXTinyFont))) return false;

		if (FAILED(
			D3DXCreateFont(g_D3D_Device, 32, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE, "Nanum Brush Script", &m_UXFontLevel))) return false;

		if (FAILED(D3DXCreateFont(g_D3D_Device, 48, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE, "Nanum Brush Script", &m_messageFont))) return false;

		if (FAILED(
			D3DXCreateFont(g_D3D_Device, 16, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
			DEFAULT_PITCH | FF_SWISS, "Nanum Brush Script", &m_smallSerif))) return false;
		*/

		if (FAILED(
			D3DXCreateFont(g_D3D_Device, 18, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE, "Nanum Brush Script", &m_theme.m_smallText.m_font))) return false;

		if (FAILED(
			D3DXCreateFont(g_D3D_Device, 22, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE, "Nanum Brush Script", &m_theme.m_mediumText.m_font))) return false; // DEFAULT_QUALITY //FW_BOLD

		if (FAILED(
			D3DXCreateFont(g_D3D_Device, 32, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE, "Nanum Brush Script", &m_theme.m_largeText.m_font))) return false;

		if (FAILED(D3DXCreateFont(g_D3D_Device, 48, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE, "Nanum Brush Script", &m_theme.m_messageText.m_font))) return false;

		if (FAILED(
			D3DXCreateFont(g_D3D_Device, 16, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
			DEFAULT_PITCH | FF_SWISS, "Nanum Brush Script", &m_theme.m_nameText.m_font))) return false;

		m_theme.m_smallText.m_color = D3DCOLOR_XRGB(255, 255, 255);
		m_theme.m_smallText.m_format = DT_CENTER;

		m_theme.m_mediumText.m_color = D3DCOLOR_XRGB(255, 255, 255);
		m_theme.m_mediumText.m_format = DT_CENTER;

		m_theme.m_largeText.m_color = D3DCOLOR_XRGB(255, 255, 255);
		m_theme.m_largeText.m_format = DT_CENTER;

		m_theme.m_messageText.m_color = D3DCOLOR_XRGB(255, 255, 255);
		m_theme.m_messageText.m_format = DT_CENTER;

		m_theme.m_nameText.m_color = D3DCOLOR_XRGB(255, 255, 255);
		m_theme.m_nameText.m_format = DT_CENTER;



		//medium plain white
		if (FAILED(
		D3DXCreateFont(g_D3D_Device, 18, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE, "", &m_theme.m_mediumPlainText.m_font))) return false; // DEFAULT_QUALITY //FW_BOLD


		m_theme.m_mediumPlainText.m_color = D3DCOLOR_XRGB(255, 255, 255);
		m_theme.m_mediumPlainText.m_format = DT_RIGHT;



		//Cooldown Text

		if (FAILED(
			D3DXCreateFont(g_D3D_Device, 42, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
				DEFAULT_PITCH | FF_SWISS, "Nanum Brush Script", &m_theme.m_abilityCooldownText.m_font))) return false;

		m_theme.m_abilityCooldownText.m_color = D3DCOLOR_XRGB(0,0,0);
		m_theme.m_abilityCooldownText.m_format = DT_CENTER;


		if (FAILED(
			D3DXCreateFont(g_D3D_Device, 42, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
				DEFAULT_PITCH | FF_SWISS, "Nanum Brush Script", &m_theme.m_abilityCooldownBelowText.m_font))) return false;

		m_theme.m_abilityCooldownBelowText.m_color = D3DCOLOR_XRGB(191, 0, 63);
		m_theme.m_abilityCooldownBelowText.m_format = DT_CENTER;

		


		//1.6* Settings Dialog Size
		if (FAILED(
			D3DXCreateFont(g_D3D_Device, 42, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE, "Nanum Brush Script", &m_theme.m_shopZoneText.m_font))) return false;

		m_theme.m_shopZoneText.m_color = D3DCOLOR_XRGB(170, 128, 192);// m_greyColorValue = 
		m_theme.m_shopZoneText.m_format = DT_CENTER;

		//1.6 * Shop Label Size
		if (FAILED(
			D3DXCreateFont(g_D3D_Device, 26, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE, "Nanum Brush Script", &m_theme.m_settingsLabel.m_font))) return false;

		m_theme.m_settingsLabel.m_color = D3DCOLOR_XRGB(255, 255, 255);// m_greyColorValue = 
		m_theme.m_settingsLabel.m_format = DT_LEFT;


		if (FAILED(
			D3DXCreateFont(g_D3D_Device, 26, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE, "Nanum Brush Script", &m_theme.m_dialogTitle.m_font))) return false;
		m_theme.m_dialogTitle.m_color = D3DCOLOR_XRGB(255, 255, 170);
		m_theme.m_dialogTitle.m_format = DT_LEFT;


		m_theme.m_dialogLabel.m_font = m_theme.m_settingsLabel.m_font;
		m_theme.m_dialogLabel.m_color = m_theme.m_settingsLabel.m_color;
		m_theme.m_dialogLabel.m_format = m_theme.m_settingsLabel.m_format;

		//1.6 * Item Menu Dialog Size
		if (FAILED(
			D3DXCreateFont(g_D3D_Device, 16, 0, FW_BOLD, 1, false, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE, "Cambria", &m_theme.m_shopItemLabel.m_font))) return false;
		m_theme.m_shopItemLabel.m_color = D3DCOLOR_XRGB(255, 255, 255);// m_greyColorValue = 
		m_theme.m_shopItemLabel.m_format = DT_LEFT;

	}

	return true;
}

bool MobaViewState::InitDialog(Language language)
{

	string path;

	for (unsigned int npcCount = 0; npcCount < gameState->GetNeutralTargetControllers()->size(); npcCount++)
	{
		if (gameState->GetNeutralTargetControllers()->at(npcCount)->GetDialogBehavior() != nullptr)
		{
			path = "Resources/Characters/";
			path.append(gameState->GetNeutralTargetControllers()->at(npcCount)->GetDialogBehavior()->GetDir());
			path.append("/dialog_");

			switch (language)
			{
			case languageEN: path.append("en.data"); break;
			}

			m_dialogBehaviorViewIO.ReadData(path, gameState->GetNeutralTargetControllers()->at(npcCount)->GetDialogBehavior());

		}
	}

	return true;
}


void MobaViewState::SubscribeMembersToDamageControllerEvents()
{

}

vector<PlayerCharacterView*> * MobaViewState::GetOpponentTeamViews()
{
	TeamName t = gameState->GetControlledActor()->GetTeam();

	switch (t)
	{
	case yellowTeamName: return MobaViewState::GetTeamForSide(purpleTeamName);
	case purpleTeamName: return MobaViewState::GetTeamForSide(yellowTeamName);
	}
}

vector<PlayerCharacterView*> * MobaViewState::GetPlayerTeamViews()
{
	switch (gameState->GetControlledPCC()->GetCharacter()->GetActor()->GetTeam())
	{
	case yellowTeamName: return MobaViewState::GetTeamForSide(yellowTeamName);
	case purpleTeamName: return MobaViewState::GetTeamForSide(purpleTeamName);
	}
}

vector<PlayerCharacterView*> *  MobaViewState::GetTeamForSide(TeamName name)
{
	return &m_playerTeams.at(name);
}



IndicatorController * MobaViewState::GetIndicatorController() { return &m_indicatorController; }
InfoPanelController * MobaViewState::GetInfoPanelController() { return  &m_infoPanelController; }
TooltipController * MobaViewState::GetTooltipController() { return &m_tooltipController; }
DialogScreenController * MobaViewState::GetDialogScreenController() { return &m_dialogScreenController; }

vector <PlayerCharacterView*> * MobaViewState::GetPlayerCharacterViews() { return &m_playerCharacterViews; }
vector <NPCView*> * MobaViewState::GetNPCViews() { return &m_npcViews; }
//vector <SpriteView*> * MobaViewState::GetWallViews() { return &m_wallViews; }
vector <VitalEntityView*> * MobaViewState::GetVitalEntityViews() { return &m_vitalEntityViews; }
GameMapView * MobaViewState::GetGameMapView() { return m_gameMapView; }
//SpriteView * MobaViewState::GetGroundView() { return &m_groundView; }

vector<QuestView*>* MobaViewState::GetQuestViews()
{
	return &m_questViews;
}

BoidstormView * MobaViewState::GetBoidstormView() { return &m_boidstormView;  }


GameCursor * MobaViewState::GetGameCursor() { return &m_cursor; }
UIMobaHud * MobaViewState::GetHud() { return &m_mobaHud; }
GameShopMenu * MobaViewState::GetGameShopMenu() { return &m_gameShopMenu; }
GameMainMenu *  MobaViewState::GetMainMenu() { return &m_mainMenu; }
UIKeyDialog * MobaViewState::GetKeyDialog() { return &m_keyDialog; }
StatPanel *  MobaViewState::GetStatPanel() { return &m_statPanel; }
GameMessage * MobaViewState::GetGameMessage() { return &m_gameMessage; }

vector <HealthBar *> * MobaViewState::GetHealthBarsByType(VitalEntityVectorName name)
{
	switch (name)
	{
	case vitalEntityVectorNamePlayerCharacter:
		return &m_pcHealthBars;
		break;
	case vitalEntityVectorNameNPC:
		return &m_npcHealthBars;
		break;
	case vitalEntityVectorNameVitalEntity:
		return &m_chestHealthBars;
		break;
	case vitalEntityVectorNameObjects:
		return &m_objectHealthBars;
		break;
	default://intentional fall through
	case vitalEntityVectorNameCount:
		MessageBox(NULL, "bad name in (MobaViewState::GetHealthBarsByType) ", "Error", MB_OK);
		break;
	}

	return NULL;
}

bool * MobaViewState::GetIsHealthMirrorOn() { return &m_isHealthMirrorOn; }

CameraInputModel	* MobaViewState::GetCameraInputModel()	 { return &m_cameraInputModel; }
CharacterInputModel * MobaViewState::GetCharacterInputModel(){ return &m_characterInputModel; }
DevInputModel		* MobaViewState::GetDevInputModel()		 { return &m_devInputModel; }
EditorInputModel	* MobaViewState::GetEditorInputModel()	 { return &m_editorInputModel; }
InterfaceInputModel * MobaViewState::GetInterfaceInputModel(){ return &m_interfaceInputModel; }
KeyDialogInputModel	* MobaViewState::GetKeyDialogInputModel() { return &m_keyDialogInputModel; }
MainMenuInputModel	* MobaViewState::GetMainMenuInputModel() { return &m_mainMenuInputModel; }
ShopMenuInputModel	* MobaViewState::GetShopMenuInputModel() { return &m_shopMenuInputModel; }
ChatTextAreaInputModel * MobaViewState::GetChatTextAreaInputModel() { return &m_chatTextAreaInputModel; }

PlayerCharacterView * MobaViewState::GetControlledPlayerView() { return m_controlledPlayerView; }
void MobaViewState::SetControlledPlayerView(PlayerCharacterView * controlledPlayerView) { m_controlledPlayerView = controlledPlayerView; }



void MobaViewState::ActionSetControlledPlayerView(int i)
{
	// this should be base on some debug varibale being true
	if (true)
	{
		if (i <= m_playerCharacterViews.size())
		{
			gameState->SetControlledCharacter(gameState->GetPCCs()->at(i));
			m_mobaHud;
			SetControlledPlayerView(m_playerCharacterViews.at(i));
		}
	}

	else m_cameraDirector.ActionCentreCamera(gameState->GetPlayerCharacters()->at(i)->GetActor());
}

void MobaViewState::SetGameModel(StandardMatch5v5State * gameStateIn) { gameState = gameStateIn; }

