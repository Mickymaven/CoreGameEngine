#if !defined(MOBASTATE_H)
#define MOBASTATE_H

//#include "../../../CoreGame/src/GameConfiguration.h"

//#include "../GamestateIO/NPCControllerFactory.h"
//#include "../GamestateIO/PlayerCharacterControllerFactory.h"
//#include "../GamestateIO/AbilityFactory.h"
//#include "../GamestateIO/ActorStatsFactory.h"
#include "../GamestateIO/ItemFactory.h"
#include "../GamestateIO/GameMapFactory.h"


#include "../../../EngineGameModel/src/Base/Sprite.h"
#include "../../../EngineGameModel/src/Gamestate/BasicGameState.h"
#include "../../../EngineMoba/src/Actors/Actor.h"
#include "../../../EngineMoba/src/Actors/PlayerCharacterController.h"
#include "../../../EngineMoba/src/Actors/NPCController.h"
#include "../Maps/GameMap.h"
#include "../../../EngineMoba/src/Quests/Quest.h"
#include "../../../EngineMoba/src/GameControl/DeathEvent.h"
#include "../../../EngineMoba/src/Actors/TradeInventory.h"
#include "../../../EngineMoba/src/Player/ChatModel.h"

#include "MobaActorStateObject.h"
#include "../Actors/PlayerActionEnum.h"
#include "../../../CoreGame/src/Gameplay/TeamName.h"
#include "../Pathfinding/Pathfinder.h"

enum InitPhase
{
	initLoading,
	initAssetData,
	initDisplay,
	initInput,
	initScoreboard,
	initShopping,
	initKits,
	initSpawnPoints,
	initQuestModel,
	initInteractionControl,
	initNPCs,
	initPlayerCharacters,
	initGameEntities,
	
	initEnvironment,
	initPathfinding,
	initCount
};

class MobaState : public BasicGameState
{
private:
protected:
	int m_loadProgress;

	ItemFactory m_itemFactory;
	
	//PlayerCharacterControllerFactory m_playerCharacterControllerFactory;
	//NPCControllerFactory m_NPCControllerFactory;
	//ActorStatsFactory m_actorStatsFactory;
	//AbilityFactory m_abilityFactory;
	GameMapFactory m_gameMapFactory;

	GameMap * m_map;

	ChatModel m_chatModel;

	//Pathfinder m_pathfinder;//forward dependency

	vector<int> m_gameSpriteConfig;
	vector<int> m_gameAssetConfig;

	MobaActorStateObject m_mobaActorStateObject;

	
	vector<int> m_teamScores;
	int m_teamSize;

	//vector <vector <PlayerCharacterController *> *> m_teams;
	vector <vector <Actor *> *> m_actorTeams;
	vector <vector <PlayerCharacterController *> *> m_actorControllerTeams;

	PlayerCharacterController * m_ownedPlayerCharacter;

	bool m_controlAnyPlayerCharacter;
	PlayerCharacterController * m_controlledPlayerCharacter;
	Character * m_controlledCharacter;
	Actor * m_controlledActor;

	vector<vector<Character *> *> m_characterLists;

	vector <Character *> m_playerCharacters;
	vector <PlayerCharacterController *> m_pccs;

	vector <Actor *> m_NPCtargets; //actor (of player's character) for npcs to target
	
	vector<NPCController *> m_npcs;//all npc controllers
	vector<VitalEntity *> m_vitalEntities;//every object of with VitalEntity as base class
	vector<VitalEntity *> m_vitalEntityObjects;//objects initialised as the base class

	vector<Character *> m_neutralTargetCharacters; //npcs that do damage
	vector <NPCController *> m_neutralTargetCharacterControllers;//^ but npcc
	vector<Actor * > m_targetableNPCs; //npcs that are targetable in abilities

	//vector<Sprite *> m_walls;//an idea not used at this point. list aof sprites to hit test in client view, to move to moba view is used like this (but would still have models)..

	vector<Quest *> m_quests; //quest models only?




	//Sprite m_ground;//ground has a special meaning in moba (used for nav testing in client)
	// but we will also add ground to sprite vector where it will be rendered from (in MobaView)


	vector<DeathEvent *> m_deathEvents;
	vector<TradeInventory> m_gameShops;

	vector<ShopInventory*>  m_inventories; //these are to initialise TradeInvs (serve as game shops independently or as part of NPC TradeInv Members).
	vector<int> m_relevantInvs;


	//game map customisation? stuff


public:
	MobaState();
	~MobaState();

	virtual void InitInventories(vector<int> * invsToInit);
	virtual void InitGameShopsForMode();
	//Accessors

	vector<int> * GetSpriteConfig();
	vector<int> * GetAssetConfig();

	ItemFactory * GetItemFactory();

	ChatModel *GetChatModel();

	Character * GetControlledCharacter();
	Actor * GetControlledActor();
	PlayerCharacterController * GetControlledPCC();
	bool GetControlAnyPlayerCharacter();
	PlayerCharacterController * GetOwnedPCC();

	vector<vector<Character *> *> * GetCharacterLists();

	vector <Character *> * GetPlayerCharacters();
	vector <PlayerCharacterController *> * GetPCCs();

	vector<NPCController *> * GetNPCs();
	vector<VitalEntity *> * GetVitalEntities();
	vector<VitalEntity *> * GetVitalEntityObjects();
	
	vector <Character *> * GetNeutralTargetCharacters();
	vector <NPCController *> * GetNeutralTargetControllers();

	vector<Actor * > * GetTargetableNPCs();

	vector<Actor *> * GetNPCtargets();

	vector<DeathEvent *> * GetDeathEvents();

	vector<Quest *> * GetQuests();

	GameMap * GetGameMap();

	vector<TradeInventory> * GetShops();

	//Mutators
	void SetControlledCharacter(PlayerCharacterController * playerCharacterController);

	int * GetTeamScore(TeamName team);
	vector<PlayerCharacterController *> * GetPlayerCharactersByTeam(TeamName team);

	vector<vector<PlayerCharacterController *> *> * GetPlayerCharacterTeams();

};

#endif