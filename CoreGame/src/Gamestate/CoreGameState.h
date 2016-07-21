#if !defined(COREGAMESTATE_H)
#define COREGAMESTATE_H


#include "../../../EngineMoba/src/Gamestate/MobaState.h"
#include "../GameConfiguration.h"
#include "../Gameplay/ModeConfigIO/ModeConfigurationFactory.h"

#include "AssetMeshNameEnum.h" //all derived will need this

#include "../GamestateIO/CoreActorFactory.h"
#include "../GamestateIO/CoreActorStatsFactory.h"
#include "../GamestateIO/CoreCharacterFactory.h"
#include "../GamestateIO/CoreNPCControllerFactory.h"
#include "../GamestateIO/CorePlayerCharacterControllerFactory.h"

#include "../Gameplay/Quests/InvName.h"


class CoreGameState : public MobaState
{
protected:
	GameConfiguration * m_gameConfiguration;
	ModeConfigurationFactory * m_modeConfigurationFactory;

	CoreActorFactory m_actorFactory;
	CoreActorStatsFactory m_actorStatsFactory;
	CoreCharacterFactory m_characterFactory;
	CoreNPCControllerFactory m_NPCControllerFactory;
	CorePlayerCharacterControllerFactory m_playerCharacterControllerFactory;
	
	AbilityFactory m_abilityFactory;
	GameMapFactory m_gameMapFactory;


public:
	CoreGameState();
	~CoreGameState();

	bool Init(GameConfiguration * config);

	bool InitFactoryStuff();

	void InitInventories(vector<int>* invsToInit);

	bool virtual InitSelectedPhase(int initPhase) = 0;


	string GetInitPhaseString(int initPhase);

	GameConfiguration * GetGameConfiguration();

};


#endif