#if !defined(STANDARDMATCH5V5STATE_H)
#define STANDARDMATCH5V5STATE_H

#include "../../../EngineMoba/src/Gamestate/MobaState.h"

#include "../Environment/Boidstorm.h"
#include "../Gameplay/ModeConfig/BaseMapConfigForStandard.h"
#include "../Gameplay/Quests/OwlQuestStandard1.h"

//#include "../Gameplay/ModeConfig/BarebonesConfigForStandard.h"
//#include "../Gameplay/ModeConfig/TabulaRasaConfigForStandard.h"


//NPC AIs
#include "../Gameplay/Characters/VisionOwl/VisionOwlInteractionController.h"

#include "CoreGameState.h"
#include "GameMode.h"


enum StandardMatch5v5GameShops
{
	standardMatch5v5GameShopBase,
	standardMatch5v5GameShopNeutral,
	standardMatch5v5GameShopCount
};

enum StandardMatch5v5TeamSide
{
	teamSideFriendly,
	teamSideOpponent,
	teamSideNeutral,
	standardMatch5v5TeamSideCount
};

enum ItemSets
{
	itemSetsStandardMatch5v5Starter,
	itemSetsStandardMatch5v5NPC,
	itemSetsStandardMatch5v5Count

};

class StandardMatch5v5State : public CoreGameState
{
private:
protected:
	BaseMapConfigForStandard * m_ModeMapConfig;

	
	TeamName m_winner;

	//Environment
	Boidstorm m_boidstorm;
	//Sprite * m_cornerYellow;
	//Sprite * m_cornerPurple;

	//Events stuff
	vector<LMVector3> m_yellowSpawns;
	vector<LMVector3> m_purpleSpawns;

	//Objectives
	VitalEntity m_yellowTeamChest;
	VitalEntity m_purpleTeamChest;
	VitalEntity m_chest1;

	//Teams
	vector<NPCController *> m_neutralControllers;

	vector<PlayerCharacterController *> m_yellowTeam;
	vector<PlayerCharacterController *> m_purpleTeam;

	vector<Actor *> m_yellowActors;
	vector<Actor *> m_purpleActors;
	vector<Actor *> m_neutralActors;


	//Starter Kit

	vector<vector <ItemName>> m_itemSets;

	//Shops
	TradeInventory * m_baseGameShop;
	TradeInventory * m_neutralGameShop;

	//Quests for this mode
	OwlQuestStandard1 m_owlQuest;


	//npc ai
	VisionOwlStandard1InteractionController m_ic_vo_s1;
	vector<VisionOwlInteractionController*> m_ic_vo_list;


	
	//Interaction
	bool m_isFirstSpawn;

public:
	

	StandardMatch5v5State();
	~StandardMatch5v5State();

	bool InitSelectedPhase(int initPhase);


	void InitGameShopsForMode();

	vector<PlayerCharacterController *> * GetTeamControllersAsVector(TeamName team);
	
	TradeInventory * GetGameShopByName(StandardMatch5v5GameShops shop);
	
	Boidstorm * GetBoidstorm();
	vector<NPCController *> * GetNeutralControllers();
	vector<Actor *> * ActorsForSide(StandardMatch5v5TeamSide teamSide);
	vector<PlayerCharacterController *> * PlayerCharacterControllersForSide(StandardMatch5v5TeamSide teamSide);
	//vector<PlayerCharacterController *> * GetPlayerCharactersByTeam(TeamName team);
	vector<LMVector3> * GetTeamSpawns(TeamName team);
	//int * GetTeamScore(TeamName team);
	VitalEntity * GetYellowTeamChest();
	VitalEntity * GetPurpleTeamChest();

	TeamName GetWinner();
	void SetWinner(TeamName winner);

};

#endif