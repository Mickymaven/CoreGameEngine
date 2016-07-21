#include "CoreGameState.h"

CoreGameState::CoreGameState():MobaState()
{
}

CoreGameState::~CoreGameState()
{
}

bool CoreGameState::Init(GameConfiguration * config)
{
	m_gameConfiguration = config;

	InitFactoryStuff();
	return true;
}

bool CoreGameState::InitFactoryStuff()
{
	//m_abilityFactory init
	if (!m_itemFactory.Init(&m_abilityFactory)) return false;
	if (!m_actorFactory.Init(&m_actorStatsFactory)) return false;
	if (!m_characterFactory.Init(&m_actorFactory, &m_abilityFactory, &m_itemFactory)) return false;
	if (!m_NPCControllerFactory.Init(&m_characterFactory)) return false;
	if (!m_playerCharacterControllerFactory.Init(&m_characterFactory)) return false;

	return true;
}


void CoreGameState::InitInventories(vector<int>* invsToInit)
{
	vector<int> * targetInv;

	m_inventories.resize(invNameCount, nullptr);

	for (unsigned int i = 0; i < invsToInit->size(); i++)
	{
		m_inventories.at(i) = new ShopInventory();
		vector<int> inv;

		switch (i)
		{
		case invEmpty:
			inv = { itemNomBar };

			break;

		case inv5v5NormalBase:
			inv = { itemNomBar, itemBike, itemKetchup };
			break;

		case inv5v5NormalNeutral1:
			//*inv = {itemBasicBoots, itemBasicSneakers, };
			for (unsigned int i = 0; i < itemCount; i++)
			{
				inv.push_back(i);
			}//push int for each member of full inv
			break;
		//case invOwlQuestS1Reward:
		//	inv = { itemNomBar, itemBasicSneakers };
		//	break;
		default:break;
			//case:
			//	*inv = {};
			//	break;

		};

		targetInv = m_inventories.at(i)->GetInventory();

		for (unsigned int j = 0; j < inv.size(); j++)
		{
			targetInv->push_back(inv.at(j));
		}

		m_inventories.at(i)->SetInventoryID(i);//set unique inv id
	}

	//

	/*
	for (unsigned int i = 0; i < invsToInit->size(); i++)
	{
	inv = m_inventories.at(i)->GetInventory();

	for (unsigned int j = 0; j < inv->size(); j++)
	{
	m_itemFactory.GetItemByEnum((ItemName)inv->at(j));
	}
	}*/

}

string CoreGameState::GetInitPhaseString(int initPhase)
{
	switch ((InitPhase)initPhase)
	{
	case initLoading:		return "Model: Game Info"; break;
	case initAssetData:		return "Model: Data"; break;
	case initDisplay:		return "Model: Display"; break;
	case initInput:			return "Model: Input"; break;
	case initScoreboard:	return "Model: Scoreboard"; break;
	case initShopping:		return "Model: Shopping"; break;
	case initQuestModel:		return "Model: Quest"; break;
	case initInteractionControl:return "Model: NPC AI"; break;
	case initNPCs:			return "Model: NPC"; break;
	case initKits:			return "Model: Kits"; break;
	case initSpawnPoints:	return "Model: Spawn points"; break;
	case initPlayerCharacters:		return "Model: Player Characters"; break;
	case initEnvironment:	return "Model: Environment"; break;
	case initPathfinding:	return "Model: Pathfinding"; break;
	case initCount:			return "Model Initialised."; break;
	default: return ""; break;
	};

}

GameConfiguration * CoreGameState::GetGameConfiguration()
{
	return m_gameConfiguration;
}
