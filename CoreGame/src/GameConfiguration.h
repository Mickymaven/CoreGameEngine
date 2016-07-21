#if !defined(GAMECONFIGURATION_H)
#define GAMECONFIGURATION_H

#include <vector>
using std::vector;
#include <string>
using std::string;

#include "../../CoreGame/src/Gamestate/GameMode.h"
#include "../../CoreGame/src/Gamestate/GameMapId.h"
#include "../../CoreGame/src/Gameplay/Abilities/AbilityName.h"
#include "../../CoreGame/src/Gameplay/TeamName.h"
#include "../../CoreGame/src/Gameplay/Characters/CharacterClassName.h"

class GameConfiguration
{

private:
	//string m_mapName;
	GameMapId m_mapId;
	string m_themeName;
	//GameMapId
	GameMode m_gameMode;

	vector<string> m_names;
	vector<CharacterClassName> m_characterName;
	vector<TeamName> teamNames;
	vector<unsigned long> playerID;
	vector<vector<AbilityName>> customAbilities;

public:
	GameConfiguration();
	GameConfiguration(GameMapId mapId, string themeName, GameMode mode);
	~GameConfiguration();

	void AddPlayer(string playerName, CharacterClassName characterClass, TeamName teamName, unsigned long id, AbilityName ability1, AbilityName ability2);

	//accessors
	//string GetMapName() { return m_mapName; }
	GameMapId GetMapId() { return m_mapId; };
	string GetThemeName() { return m_themeName; }
	GameMode GetGameMode() { return m_gameMode; }
	vector<string> * GetNames() { return &m_names; }
	vector<CharacterClassName> * GetPlayerCharacterNames() { return &m_characterName; }
	vector<TeamName> * GetTeamNames() { return &teamNames; }
	vector<unsigned long> * GetPlayerIDs() { return &playerID; }
	vector< vector<AbilityName>> * GetCustomAbilities() { return &customAbilities; };
};

#endif
