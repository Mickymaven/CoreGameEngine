#include "StandardMatch5v5State.h"

StandardMatch5v5State::StandardMatch5v5State() : CoreGameState()
{
}

StandardMatch5v5State::~StandardMatch5v5State()
{

	//Mode Configuration Factory
	delete m_ModeMapConfig;
	m_ModeMapConfig = nullptr;

	//init NPCs

	for (unsigned int i = 0; i < m_npcs.size(); i++)
	{
		delete m_npcs.at(i);
		m_npcs.at(i) = nullptr;
	}

	

}

bool StandardMatch5v5State::InitSelectedPhase(int initPhase)
{
	if (initPhase == initLoading){ /////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////
		//bulk of game loading here

		m_playerID = m_gameConfiguration->GetPlayerIDs()->at(0);//TODO client test only line
		
		if (createModeCodeOK != m_modeConfigurationFactory->CreateModeConfiguration(
			(BaseMapConfigForMode**)&m_ModeMapConfig,
			m_gameConfiguration)) return false;




		QueryPerformanceCounter(&m_initStart);
		QueryPerformanceFrequency(&m_init_tFrequency);
		m_FrequencyQuadPart = (float)m_init_tFrequency.QuadPart;

		m_gameOverState = gameOverStateGameOn;
		m_winner = TeamNameCount;

	

		srand((unsigned int)time(NULL)); //to recieve srand in game configuration

	} /////////////////////////////////////////////////////////////////////////////////



	////////////////////////////////////////////////////////////////////////////////////////////
	if (initPhase == initAssetData){ ///////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////

		//Map Load
		if (constructGameMapCodeOK != m_gameMapFactory.ConstructGameMap(
			&m_map,
			m_gameConfiguration->GetMapId()
			)) return false;
		


		// Data //////////////////////////////////////////////////////////////////
		m_itemFactory.Init(&m_abilityFactory);
		m_relevantInvs = { invEmpty, inv5v5NormalBase, inv5v5NormalNeutral1};
		InitInventories(&m_relevantInvs);

	}//////////////////////////////////////////////////////////////////////////////////



	///////////////////////////////////////////////////////////////////////////////////////////
	if (initPhase == initDisplay){ ////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////
		// Data //////////////////////////////////////////////////////////////////




	}///////////////////////////////////////////////////////////////////////////////



	//////////////////////////////////////////////////////////////////////////////////////////
	if (initPhase == initInput){ ///////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////



	}////////////////////////////////////////////////////////////////////////////////



	////////////////////////////////////////////////////////////////////////////////////////////////
	if (initPhase == initScoreboard) { /////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////
		

		// Game State ////////////////////////////////////////////////////////////
		m_teamSize = 5;

		m_isFirstSpawn = false;
		m_teamScores.resize(2,0);


	}/////////////////////////////////////////////////////////////////////////////////



	////////////////////////////////////////////////////////////////////////////////////////////////
	if (initPhase == initShopping) { ///////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////////
		//item factory before any item stuff

		InitGameShopsForMode();

		// Game Shops //////////////////////////////////////////////////////////////////////////////
		
		//we have to use NPCs like game shops where ever we use m_gameShops / mobaState->GetGameShops()
		//there can be orphan shops with no NPC owners and then npc owner shops (checked 2nd in MobaController::InRangeShops stuff)

		//Shop For Shop Zone
		m_baseGameShop = &m_gameShops.at(standardMatch5v5GameShopBase);
		m_neutralGameShop = &m_gameShops.at(standardMatch5v5GameShopNeutral);

		m_baseGameShop->GetShopZones()->push_back(
			new ShopZone(LMVector3(330.0f, 0.0f, 330.0f), 30.0f,
			"Purple Shop", purpleTeamName));

		m_baseGameShop->GetShopZones()->push_back(
			new ShopZone(LMVector3(70.0f, 0.0f, 70.0f), 30.0f,
			"Yellow Shop", yellowTeamName));

		m_neutralGameShop->GetShopZones()->push_back(
			new ShopZone(LMVector3(150.0f, 0.0f, 150.0f), 20.0f,
			"Neutral Shop", teamNameNeutral));

	}/////////////////////////////////////////////////////////////////////////////////////////////////


	////////////////////////////////////////////////////////////////////////////////////////////
	if (initPhase == initKits){ /////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////
		// Starter Kit ////////////////////////////////////////////////////////
		//vector<vector <ItemName>> m_itemSets;
		m_itemSets.resize(itemSetsStandardMatch5v5Count);

		m_itemSets.at(itemSetsStandardMatch5v5Starter) = { itemBasicBoots, itemBasicSneakers,itemTreeBranch };
		m_itemSets.at(itemSetsStandardMatch5v5NPC) =
		{
			itemBasicBoots,
			itemBasicBoots,
			itemBasicSneakers,
			itemBasicSneakers,
			itemTreeBranch,
			itemTreeBranch
		};

		
	}///////////////////////////////////////////////////////////////////////////////////

	


	////////////////////////////////////////////////////////////////////////////////////////////
	if (initPhase == initSpawnPoints){ //////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////


		LMVector3 YellowSpawn;
		LMVector3 PurpleSpawn;
		m_yellowSpawns.resize(m_teamSize);
		m_purpleSpawns.resize(m_teamSize);

		float spawnSpacing;
		/*
		if (false)
		{
			YellowSpawn = LMVector3(10.0f, 0.0f, 10.0f);
			PurpleSpawn = LMVector3(394.0f, 0.0f, 394.0f);
			spawnSpacing = 2.0f;
			m_yellowSpawns[0] = LMVector3(YellowSpawn.x, 0.0f, YellowSpawn.z);
			m_yellowSpawns[1] = LMVector3(YellowSpawn.x - spawnSpacing, 0.0f, YellowSpawn.z);
			m_yellowSpawns[2] = LMVector3(YellowSpawn.x, 0.0f, YellowSpawn.z + spawnSpacing);
			m_yellowSpawns[3] = LMVector3(YellowSpawn.x + spawnSpacing, 0.0f, YellowSpawn.z);
			m_yellowSpawns[4] = LMVector3(YellowSpawn.x, 0.0f, YellowSpawn.z - spawnSpacing);

			m_purpleSpawns[0] = LMVector3(PurpleSpawn.x, 0.0f, PurpleSpawn.z);
			m_purpleSpawns[1] = LMVector3(PurpleSpawn.x - spawnSpacing, 0.0f, PurpleSpawn.z);
			m_purpleSpawns[2] = LMVector3(PurpleSpawn.x, 0.0f, PurpleSpawn.z + spawnSpacing);
			m_purpleSpawns[3] = LMVector3(PurpleSpawn.x + spawnSpacing, 0.0f, PurpleSpawn.z);
			m_purpleSpawns[4] = LMVector3(PurpleSpawn.x, 0.0f, PurpleSpawn.z - spawnSpacing);
		}
		else
		{
			YellowSpawn = LMVector3(190.0f, 0.0f, 190.0f);
			PurpleSpawn = LMVector3(210.0f, 0.0f, 210.0f);
			spawnSpacing = 2.0f;
			m_yellowSpawns[0] = LMVector3(YellowSpawn.x, 0.0f, YellowSpawn.z);
			m_yellowSpawns[1] = LMVector3(YellowSpawn.x - spawnSpacing, 0.0f, YellowSpawn.z);
			m_yellowSpawns[2] = LMVector3(YellowSpawn.x, 0.0f, YellowSpawn.z + spawnSpacing);
			m_yellowSpawns[3] = LMVector3(YellowSpawn.x + spawnSpacing, 0.0f, YellowSpawn.z);
			m_yellowSpawns[4] = LMVector3(YellowSpawn.x, 0.0f, YellowSpawn.z - spawnSpacing);

			m_purpleSpawns[0] = LMVector3(PurpleSpawn.x, 0.0f, PurpleSpawn.z);
			m_purpleSpawns[1] = LMVector3(PurpleSpawn.x - spawnSpacing, 0.0f, PurpleSpawn.z);
			m_purpleSpawns[2] = LMVector3(PurpleSpawn.x, 0.0f, PurpleSpawn.z + spawnSpacing);
			m_purpleSpawns[3] = LMVector3(PurpleSpawn.x + spawnSpacing, 0.0f, PurpleSpawn.z);
			m_purpleSpawns[4] = LMVector3(PurpleSpawn.x, 0.0f, PurpleSpawn.z - spawnSpacing);
		}
		*/


	}//////////////////////////////////////////////////////////////////////////////////


	 ////////////////////////////////////////////////////////////////////////////////////////////
	if (initPhase == initQuestModel) { /////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////


									   //TODO MAKE FACTORY maybe
		m_owlQuest.Init(&m_ModeMapConfig->m_owlStandard1config);
		m_quests.push_back(&m_owlQuest);


	}//////////////////////////////////////////////////////////////////////////////////


	 ////////////////////////////////////////////////////////////////////////////////////////////
	if (initPhase == initInteractionControl) { /////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////

		m_ic_vo_s1.InitQuestInformation(&m_owlQuest);
		m_ic_vo_list.push_back(&m_ic_vo_s1);

	}//////////////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////////////////////////////
	if (initPhase == initNPCs){ //////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////////////////////////////

		//we could recive a custom number of teams in other game modes?
		m_actorTeams.push_back(&m_yellowActors);
		m_actorTeams.push_back(&m_purpleActors);
		m_actorTeams.push_back(&m_neutralActors);

		m_mobaActorStateObject.SetActorTeams(&m_actorTeams);


		//Interaction AI inherits from this automagically getting game world stuff (vectors of actor targets by TeamName)
		//might be bad idea
		MobaControllerSharedData::SetMobaActorStateObject(&m_mobaActorStateObject);
		// ^

		m_npcs.resize(standardMatch5v5GameUniqueNPCCount,nullptr);
		
		// NPC shop keepers //////////////////////////////////////////////////////////////////////////
		
		
		vector<StandardMatch5v5GameUniqueNPC> uniqueNpcId =
		{
			standardMatch5v5GameUniqueNPCNeutralShop1,
			standardMatch5v5GameUniqueNPCBaseYellow,
			standardMatch5v5GameUniqueNPCBasePurple,
			standardMatch5v5GameUniqueNPCAngryCat,
			standardMatch5v5GameUniqueNPCVisionOwl
		};


		LMVector3 uniqueNpcPos[standardMatch5v5GameUniqueNPCCount];// = { LMVector3(0.0f,0.0f,0.0f) };
		int uniqueNpcConfig[standardMatch5v5GameUniqueNPCCount][2];
		string uniqueNpcName[standardMatch5v5GameUniqueNPCCount];

		uniqueNpcPos[standardMatch5v5GameUniqueNPCBaseYellow] = { 70.0f, 0.0f,  70.0f }; //Position
		uniqueNpcConfig[standardMatch5v5GameUniqueNPCBaseYellow][0] = characterAngryCat;
		uniqueNpcConfig[standardMatch5v5GameUniqueNPCBaseYellow][1] = teamNameNeutral;
		uniqueNpcName[standardMatch5v5GameUniqueNPCBaseYellow] = "Yellow Team Shop";

		uniqueNpcPos[standardMatch5v5GameUniqueNPCBasePurple] = { 330.0f, 0.0f, 330.0f }; //Position
		uniqueNpcConfig[standardMatch5v5GameUniqueNPCBasePurple][0] = characterAngryCat;
		uniqueNpcConfig[standardMatch5v5GameUniqueNPCBasePurple][1] = teamNameNeutral;
		uniqueNpcName[standardMatch5v5GameUniqueNPCBasePurple] = "Purple Team Shop";

		uniqueNpcPos[standardMatch5v5GameUniqueNPCNeutralShop1] =	{150.0f, 0.0f, 150.0f}; //Position
		uniqueNpcConfig[standardMatch5v5GameUniqueNPCNeutralShop1][0] = characterAngryCat;
		uniqueNpcConfig[standardMatch5v5GameUniqueNPCNeutralShop1][1] = teamNameNeutral;
		uniqueNpcName[standardMatch5v5GameUniqueNPCNeutralShop1] = "NPC Shopkeep";


		uniqueNpcPos[standardMatch5v5GameUniqueNPCAngryCat] =		{175.0f, 0.0f, 225.0f}; //Position
		uniqueNpcConfig[standardMatch5v5GameUniqueNPCAngryCat][0] = characterAngryCat;
		uniqueNpcConfig[standardMatch5v5GameUniqueNPCAngryCat][1] = teamNameNeutral;
		uniqueNpcName[standardMatch5v5GameUniqueNPCAngryCat] = "@x@";

		uniqueNpcPos[standardMatch5v5GameUniqueNPCVisionOwl] =		{170.0f, 0.0f, 170.0f}; //Position
		uniqueNpcConfig[standardMatch5v5GameUniqueNPCVisionOwl][0] = characterVisionOwl;
		uniqueNpcConfig[standardMatch5v5GameUniqueNPCVisionOwl][1] = teamNameNeutral;
		uniqueNpcName[standardMatch5v5GameUniqueNPCVisionOwl] = "Owl";

		//TODO fix up config of npc custom ability slots and make accessable to view so it can do npc view factory calls right
		vector<AbilityName> custom = { abilityElixirBurst, abilityEternalLight };


		for (unsigned int i = 0; i < uniqueNpcId.size(); i++)
		{
			if (! m_NPCControllerFactory.ConstructNPCController(
				(CoreNPCController**)&m_npcs.at(i),//NPCController ** npcOut,
				&uniqueNpcPos[uniqueNpcId.at(i)],//Position
				uniqueNpcId.at(i),//StandardMatch5v5GameUniqueNPC id,
				m_map->GetPathfinder(),//Pathfinder * pathfinder,
				&m_targetableNPCs,//vector <Actor*> * teamActors,
				&m_NPCtargets,//vector <Actor*> * opponentActors,
				&m_targetableNPCs,//vector <Actor*> * neutralActors,
				(CharacterClassName)uniqueNpcConfig[uniqueNpcId.at(i)][0],//CharacterClassName characterClass,
				&m_itemSets.at(itemSetsStandardMatch5v5Starter),//vector<ItemName> * itemSets,
				true,//bool targetable,
				(TeamName)uniqueNpcConfig[uniqueNpcId.at(i)][1],//TeamName team,
				&uniqueNpcName[uniqueNpcId.at(i)],//string * uniqueName,
				&custom//vector<AbilityName> * customAbilities
			)) return false;
			//todo see if we are - previous note: "deleting npc instances from m_npcs in destructor".

			m_actorTeams.at(teamNameNeutral)->push_back(m_npcs.at(i)->GetCharacter()->GetActor());
		}

		// Targetable NPCs
		m_targetableNPCs.resize(0);
		m_neutralTargetCharacterControllers.resize(0);
		m_neutralTargetCharacters.resize(0);
	
		// Invs and vectors ///////////////////////////////////////////////////////////
		for (unsigned int i = 0; i < uniqueNpcId.size(); i++)
		{
			switch (uniqueNpcId[i])
			{
			case standardMatch5v5GameUniqueNPCVisionOwl:
				//m_npcs.at(i)->GetCharacter()->GetTradeInventory()->GetPrivateTradeInventory()->at(9) = m_itemFactory.GetItem(NULL, itemBasicBoots);
				m_npcs.at(i)->GetCharacter()->GetTradeInventory()->PushActivateShopInventory(m_inventories.at(invEmpty), true);//invOwlQuestS1Reward
				if (!((VisionOwl*)m_npcs.at(i))->SetInteractionControllersList(&m_ic_vo_list)) return false;

				m_targetableNPCs.push_back(m_npcs.at(i)->GetCharacter()->GetActor());//used in CharacterInputSet for ability/item targets (ad PlayerWorldSelectionController)
				
				m_neutralTargetCharacterControllers.push_back(m_npcs.at(i)); //ends up in actorControlLists used to find damage objects in dmagae controller
				m_neutralTargetCharacters.push_back(m_npcs.at(i)->GetCharacter()); //ends up in actorControlLists used to find damage objects in dmagae controller
				break;

			case standardMatch5v5GameUniqueNPCAngryCat:
				m_targetableNPCs.push_back(m_npcs.at(i)->GetCharacter()->GetActor());
				m_neutralTargetCharacterControllers.push_back(m_npcs.at(i)); //ends up in actorControlLists used to find damage objects in dmagae controller
				m_neutralTargetCharacters.push_back(m_npcs.at(i)->GetCharacter()); //ends up in actorControlLists used to find damage objects in dmagae controller
				break;
			}
		}

		



	}/////////////////////////////////////////////////////////////////////////////////



	////////////////////////////////////////////////////////////////////////////////////////////
	if (initPhase == initPlayerCharacters){ ////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////
		
		//if (!m_playerCharacterControllerFactory.Init(&m_actorStatsFactory, &m_abilityFactory, &m_itemFactory)) return false;
		
		// m_actorStatsFactory //todo make a structure that connects CharacterClassNames to file paths or similar

		// Load Player's characters from config ////////////////////////////////////////////


		vector<string> * pvNames = m_gameConfiguration->GetNames();
		vector<TeamName> * pvTeams = m_gameConfiguration->GetTeamNames();
		vector<CharacterClassName> * pvCharacterClassNames = m_gameConfiguration->GetPlayerCharacterNames();
		vector<unsigned long> * pvPlayerIDs = m_gameConfiguration->GetPlayerIDs();
		vector < vector<AbilityName>> * customAbilities = m_gameConfiguration->GetCustomAbilities();
		int purpleCount = 0;
		int yellowCount = 0;
		PlayerCharacterController * charController;
		Actor * thisActor = nullptr;
		LMVector3 thisSpawn;
		
		vector<Actor *> * teamActors = nullptr;
		vector<Actor *> * opponentActors = nullptr;

		m_actorControllerTeams.resize(2);
		m_actorControllerTeams.at(yellowTeamName) = &m_yellowTeam;
		m_actorControllerTeams.at(purpleTeamName) = &m_purpleTeam;

		for (unsigned int i = 0; i < pvNames->size(); i++)
		{
			if (pvTeams->at(i) == purpleTeamName)
			{
				teamActors = &m_purpleActors;
				opponentActors = &m_yellowActors;
				thisSpawn = m_map->GetSpawnsForTeam(purpleTeamName)->at(purpleCount);
			}

			else if (pvTeams->at(i) == yellowTeamName)
			{
				teamActors = &m_yellowActors;
				opponentActors = &m_purpleActors;
				thisSpawn = m_map->GetSpawnsForTeam(yellowTeamName)->at(yellowCount);
			}

			//use core pc control factory
			if (! m_playerCharacterControllerFactory.ConstructPlayerCharacterController(
				&pvPlayerIDs->at(i),
				(CorePlayerCharacterController**)&charController,
				pvCharacterClassNames->at(i),
				m_map->GetPathfinder(),
				&m_itemSets.at(itemSetsStandardMatch5v5Starter),
				teamActors,
				opponentActors,
				&m_targetableNPCs,
				pvTeams->at(i),
				&pvNames->at(i),
				&customAbilities->at(i)))
			{
				//bad
				return false;
			}
			
			//Extra actor init
			thisActor = charController->GetCharacter()->GetActor();

			//allocate spawn point
			*thisActor->GetPhysicsObject()->GetPosition() = thisSpawn;

			//initialise gamestate vectors
			//team vec
			TeamName team = pvTeams->at(i);
			m_actorTeams.at(team)->push_back(thisActor);//same element vec as m_purpleActors
			m_actorControllerTeams.at(team)->push_back(charController);//same vec as m_purpleTeam / m_yellowTeam
			thisActor->SetTeam(team);
			//other vecs
			m_playerCharacters.push_back(charController->GetCharacter());
			m_pccs.push_back(charController);
			m_NPCtargets.push_back(thisActor);

			if (team == purpleTeamName) purpleCount++;
			else if (team == yellowTeamName) yellowCount++;

			if (pvPlayerIDs->at(i) == 1) //g_playerID
			{
				SetControlledCharacter(charController);
				m_ownedPlayerCharacter = charController;
			}
		}

		m_characterLists.push_back((vector<Character*>*)&m_neutralTargetCharacters);
		m_characterLists.push_back((vector<Character*>*)&m_playerCharacters);

	}//////////////////////////////////////////////////////////////////////////////////

	
	////////////////////////////////////////////////////////////////////////////////////////////
	if (initPhase == initGameEntities){ /////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////
		// Loot Chests ////



		ActorStats chestStats = ActorStats(
			"Test Loot Chest",//string name,
			"",//string caption,
			1000.0f,//float baseHealth,
			1.0f,//float baseHealthRegen,
			0.0f,//float baseCatVoodoo,
			0.0f,//float basePhysicalDamage,
			0.0f,//float baseAttackSpeed,
			0.0f,//float baseMoveSpeed,
			20.0f,//float baseArmor,
			10.0f,//float baseCatVoodooResist,
			0.0f//float baseRange
			);

		//chestStats->m_armor = 100;
		//chestStats->m_baseHealth = 10000.0f;
		//chestStats->m_maxHealth = 10000.0f;
		//chestStats->m_health = 10000.0f;

		m_yellowTeamChest = VitalEntity(
			new ActorStats(chestStats),
			LMVector3(60.0f, 0.0f, 60.0f),		//Position
			LMVector3(0.0f, 0.785f, 0.0f),		//Rotation
			LMVector3(1.0f, 1.0f, 1.0f),		//Scale
			LMVector3(0.0f, 0.0f, 0.0f),		//Velocity
			LMVector3(0.0f, 0.0f, 0.0f),		//Spin
			LMVector3(0.0f, 0.0f, 0.0f),		//Resize
			0.0f);  //accelerationas

		m_purpleTeamChest = VitalEntity(
			new ActorStats(chestStats),
			LMVector3(340.0f, 0.0f, 340.0f),		//Position
			LMVector3(0.0f, -0.785f, 0.0f),		//Rotation
			LMVector3(1.0f, 1.0f, 1.0f),		//Scale
			LMVector3(0.0f, 0.0f, 0.0f),		//Velocity
			LMVector3(0.0f, 0.0f, 0.0f),		//Spin
			LMVector3(0.0f, 0.0f, 0.0f),		//Resize
			0.0f);  //acceleration


		m_chest1 = VitalEntity(
			new ActorStats(chestStats),
			LMVector3(250.0f, 0.0f, 150.0f),	//Position
			LMVector3(0.0f, 1.571f, 0.0f),		//Rotation
			LMVector3(1.0f, 1.0f, 1.0f),		//Scale
			LMVector3(0.0f, 0.0f, 0.0f),		//Velocity
			LMVector3(0.0f, 0.0f, 0.0f),		//Spin
			LMVector3(0.0f, 0.0f, 0.0f),		//Resize
			0.0f); //Acceleration
			

		// vitals vector ////
		m_gameAssetConfig.push_back(assetMeshChest1);
		m_gameAssetConfig.push_back(assetMeshChest1);
		m_gameAssetConfig.push_back(assetMeshChest1);

		m_vitalEntities.push_back(&m_yellowTeamChest);
		m_vitalEntities.push_back(&m_purpleTeamChest);
		m_vitalEntities.push_back(&m_chest1);

		m_vitalEntities.at(0)->GetPhysicsObject()->SetRadius(5.0f);
		m_vitalEntities.at(1)->GetPhysicsObject()->SetRadius(5.0f);
		m_vitalEntities.at(2)->GetPhysicsObject()->SetRadius(5.0f);

	}//////////////////////////////////////////////////////////////////////////////////






	////////////////////////////////////////////////////////////////////////////////////////////
	if (initPhase == initEnvironment){ /////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////
		

		for (unsigned int i = 0; i < m_gameSpriteConfig.size(); i++)
		{
			//positioning stuff needs to be data driven since positions are static values
		}
		
		// Ground ////



		//possible mixed mvc
		//'view only' classes make sense for stuff with no need for a controller

		//

		/*
		m_ground = Sprite(
			LMVector3(0.0f, 0.0f, 0.0f),		//Position
			LMVector3(0.0f, 0.0f, 0.0f),		//Rotation
			LMVector3(1.0f, 1.0f, 1.0f),		//Scale
			LMVector3(0.0f, 0.0f, 0.0f),		//Velocity
			LMVector3(0.0f, 0.0f, 0.0f),		//Spin
			LMVector3(0.0f, 0.0f, 0.0f),		//Resize
			0.0f);  //acceleration

		//m_walls.push_back(&m_ground); (dont push on walls, needs to be renderedd and used in mobaView un a unique way.
		*/
		
		
		//m_gameSpriteConfig.push_back(assetBarebonesGroundStandard1); //storage data source of environment meshes (sprites)

		//todo ^ why did i make that

		// Boid Code ////

		LMVector3 bPos = LMVector3(200.0f, 6.0f, 200.0f);
		
		m_boidstorm.Cast(500.0f,500.0f, &bPos);

	}/////////////////////////////////////////////////////////////////////////////////


	////////////////////////////////////////////////////////////////////////////////////////////
	if (initPhase == initPathfinding){
		////////////////////////////////////////////////////////////////////////////////////////////

		//m_pathfinder = Pathfinder();//dupe default
		m_map->GetPathfinder()->InitGraph();

		////////////////////////////////////////////////////////////////////////////////////////////
	}	////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////////////////
	if (initPhase == initCount){ ///////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////
		OutputDebugString("(MODEL DONE)\n");

	}//////////////////////////////////////////////////////////////////////////////////



	return true;
}



void StandardMatch5v5State::InitGameShopsForMode()
{
	m_gameShops.push_back(TradeInventory(m_inventories.at(inv5v5NormalBase), "Team Shop"));
	m_gameShops.push_back(TradeInventory(m_inventories.at(inv5v5NormalNeutral1), "NPC Shop"));
}

vector<PlayerCharacterController *> * StandardMatch5v5State::GetTeamControllersAsVector(TeamName team)
{
	switch (team)
	{
	case yellowTeamName:
		return &m_yellowTeam;
		break;
	case purpleTeamName:
		return &m_purpleTeam;
		break;
	}
	return NULL;
}

TradeInventory * StandardMatch5v5State::GetGameShopByName(StandardMatch5v5GameShops shop) { return &m_gameShops.at(shop); }

Boidstorm * StandardMatch5v5State::GetBoidstorm()
{
	return &m_boidstorm;
}

vector<NPCController *> * StandardMatch5v5State::GetNeutralControllers()
{
	return &m_neutralControllers;
}

vector<Actor *> * StandardMatch5v5State::ActorsForSide(StandardMatch5v5TeamSide teamSide)
{
	TeamName team = m_controlledPlayerCharacter->GetCharacter()->GetActor()->GetTeam();

	if (team == yellowTeamName)
	{
		if (teamSide == teamSideFriendly) return &m_yellowActors;
		else if (teamSide == teamSideOpponent) return &m_purpleActors;
		else MessageBox(NULL, "bad team (StandardMatch5v5State::GetPlayerCharactersBySide)", "Error", MB_OK);

		return NULL;
	}

	else if (team == purpleTeamName)
	{
		if (teamSide == teamSideFriendly) return &m_purpleActors;
		else if (teamSide == teamSideOpponent) return &m_yellowActors;
		else MessageBox(NULL, "bad team (StandardMatch5v5State::GetPlayerCharactersBySide)", "Error", MB_OK);
		return NULL;
	}

	return NULL;
}

vector<PlayerCharacterController *> * StandardMatch5v5State::PlayerCharacterControllersForSide(StandardMatch5v5TeamSide teamSide)
{
	TeamName team = m_controlledPlayerCharacter->GetCharacter()->GetActor()->GetTeam();

	if (team == yellowTeamName)
	{
		if (teamSide == teamSideFriendly) return &m_yellowTeam;
		else if (teamSide == teamSideOpponent) return &m_purpleTeam;
		else MessageBox(NULL, "bad team (StandardMatch5v5State::GetPlayerCharactersBySide)", "Error", MB_OK);

		return NULL;
	}

	else if (team == purpleTeamName)
	{
		if (teamSide == teamSideFriendly) return &m_purpleTeam;
		else if (teamSide == teamSideOpponent) return &m_yellowTeam;
		else MessageBox(NULL, "bad team (StandardMatch5v5State::GetPlayerCharactersBySide)", "Error", MB_OK);

		return NULL;
	}

	return NULL;
}



vector<LMVector3> * StandardMatch5v5State::GetTeamSpawns(TeamName team)
{
	if (team == yellowTeamName) return m_map->GetSpawnsForTeam(team);
	else if (team == purpleTeamName) return m_map->GetSpawnsForTeam(team);
	else MessageBox(NULL, "bad team (StandardMatch5v5State::GetTeamSpawns)", "Error", MB_OK);

	return NULL;
}


/*
int * StandardMatch5v5State::GetTeamScore(TeamName team)
{
	if (team == yellowTeamName) return &m_yellowTeamScore;
	else if (team == purpleTeamName) return &m_purpleTeamScore;
	else MessageBox(NULL, "bad team name in StandardMatch5v5State::GetTeamScore", "Error", MB_OK);

	return NULL;
}*/

VitalEntity * StandardMatch5v5State::GetYellowTeamChest()
{
	return 	&m_yellowTeamChest;
}

VitalEntity * StandardMatch5v5State::GetPurpleTeamChest()
{
	return 	&m_purpleTeamChest;
}

TeamName StandardMatch5v5State::GetWinner()
{
	return m_winner;
}

void  StandardMatch5v5State::SetWinner(TeamName winner)
{
	m_winner = winner;
}