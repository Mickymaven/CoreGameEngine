#include "OpenWorldState.h"

OpenWorldState::OpenWorldState()
{
}

OpenWorldState::~OpenWorldState()
{
	//Mode Configuration Factory
	delete m_ModeMapConfig;
	m_ModeMapConfig = nullptr;

}

bool OpenWorldState::InitSelectedPhase(int initPhase)
{
	if (initPhase == initLoading) { /////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////
		
		if (createModeCodeOK != m_modeConfigurationFactory->CreateModeConfiguration(
			(BaseMapConfigForMode**)&m_ModeMapConfig,
			m_gameConfiguration)) return false;

		QueryPerformanceCounter(&m_initStart);
		QueryPerformanceFrequency(&m_init_tFrequency);
		m_FrequencyQuadPart = (float)m_init_tFrequency.QuadPart;

		m_gameOverState = gameOverStateGameOn;
		//m_winner = TeamNameCount;


		//srand((unsigned int)time(NULL)); //to recieve srand in game configuration
	}

	// missing


	////////////////////////////////////////////////////////////////////////////////////////////
	if (initPhase == initGameEntities) { /////////////////////////////////////////////////////////////////////
	 ////////////////////////////////////////////////////////////////////////////////////////

		//set up classes for objects like this.
		
		//copied from Standard5v5State
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

		m_chest1 = VitalEntity(
			new ActorStats(chestStats),
			LMVector3(250.0f, 0.0f, 150.0f),	//Position
			LMVector3(0.0f, 1.571f, 0.0f),		//Rotation
			LMVector3(1.0f, 1.0f, 1.0f),		//Scale
			LMVector3(0.0f, 0.0f, 0.0f),		//Velocity
			LMVector3(0.0f, 0.0f, 0.0f),		//Spin
			LMVector3(0.0f, 0.0f, 0.0f),		//Resize
			0.0f); //Acceleration


		m_chest1.GetPhysicsObject()->SetRadius(5.0f);


		// vitals vector ////
		m_gameAssetConfig.push_back(assetMeshChest1);

		m_vitalEntities.push_back(&m_chest1);

	}//////////////////////////////////////////////////////////////////////////////////

	//missing

	if (initPhase == initPathfinding) {
		////////////////////////////////////////////////////////////////////////////////////////////

		//m_pathfinder = Pathfinder();//dupe default
		//m_map->GetPathfinder()->InitGraph();

		////////////////////////////////////////////////////////////////////////////////////////////
	}	////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////////////////////////////////////////////////////////////////////

	return true;
}
