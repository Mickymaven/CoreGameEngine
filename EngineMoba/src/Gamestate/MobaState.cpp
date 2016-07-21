#include "MobaState.h"
#include "MobaState.h"

MobaState::MobaState()
{

	m_isDebugTextOn = false;
	m_loadProgress = 0;
	m_loadSize = initCount;

	QueryPerformanceFrequency(&m_init_tFrequency);
	m_map = nullptr;
}

MobaState::~MobaState()
{
	if (m_map!=nullptr) delete m_map;//factory made a map for us
	m_map = nullptr;


	//deletes for MobaState::InitInventories
	for (unsigned int i = 0; i < m_inventories.size(); i++)
	{
		delete m_inventories.at(i);
		m_inventories.at(i) = nullptr;
	}
}

void MobaState::InitInventories(vector<int>* invsToInit)
{
	//nope
}

void MobaState::InitGameShopsForMode()
{

}

//Access
vector<int> * MobaState::GetSpriteConfig() { return &m_gameSpriteConfig; }
vector<int> * MobaState::GetAssetConfig() { return &m_gameAssetConfig; }
ItemFactory * MobaState::GetItemFactory() { return &m_itemFactory; }
ChatModel * MobaState::GetChatModel() { return &m_chatModel; }
Character * MobaState::GetControlledCharacter() { return m_controlledCharacter; }
Actor * MobaState::GetControlledActor() { return m_controlledActor; }
PlayerCharacterController * MobaState::GetControlledPCC() { return m_controlledPlayerCharacter; }
bool MobaState::GetControlAnyPlayerCharacter() { return m_controlAnyPlayerCharacter; }
PlayerCharacterController * MobaState::GetOwnedPCC() { return m_ownedPlayerCharacter; }
vector<vector<Character *> *> * MobaState::GetCharacterLists() { return &m_characterLists; }
vector <Character *> * MobaState::GetPlayerCharacters() { return &m_playerCharacters; }
vector <PlayerCharacterController *> * MobaState::GetPCCs() { return &m_pccs; }
vector<NPCController *> * MobaState::GetNPCs() { return &m_npcs; }
vector<VitalEntity *> * MobaState::GetVitalEntities() { return &m_vitalEntities; }
vector<VitalEntity *> * MobaState::GetVitalEntityObjects() { return &m_vitalEntityObjects; }
vector <Character *> * MobaState::GetNeutralTargetCharacters() { return &m_neutralTargetCharacters; }
vector <NPCController *> * MobaState::GetNeutralTargetControllers() { return &m_neutralTargetCharacterControllers; }
vector<Actor *> * MobaState::GetNPCtargets() { return &m_NPCtargets; }
vector<DeathEvent *> * MobaState::GetDeathEvents() { return &m_deathEvents; }
vector<Quest*> * MobaState::GetQuests() { return &m_quests; }
GameMap * MobaState::GetGameMap() { return m_map; }
vector<TradeInventory> *  MobaState::GetShops() { return &m_gameShops; }

void MobaState::SetControlledCharacter(PlayerCharacterController * playerCharacterController)
{
	m_controlledPlayerCharacter = playerCharacterController;
	m_controlledCharacter = playerCharacterController->GetCharacter();
	m_controlledActor = playerCharacterController->GetCharacter()->GetActor();
}

vector<Actor * > * MobaState::GetTargetableNPCs() { return &m_targetableNPCs; }

int * MobaState::GetTeamScore(TeamName team)
{
	if (team >= 0 && team < m_teamScores.size()) return &m_teamScores.at(team);
	else MessageBox(NULL, "bad team name in MobaState::GetTeamScore", "Error", MB_OK);
	return NULL;
}

vector<PlayerCharacterController *> * MobaState::GetPlayerCharactersByTeam(TeamName team)
{
	if (team >= 0 && team < m_actorControllerTeams.size()) return m_actorControllerTeams.at(team);
	else MessageBox(NULL, "bad team (MobaState::GetPlayerCharactersByTeam)", "Error", MB_OK);

	return NULL;
}

vector<vector<PlayerCharacterController*>*>* MobaState::GetPlayerCharacterTeams() { return &m_actorControllerTeams; }
