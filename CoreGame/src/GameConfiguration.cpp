#include "GameConfiguration.h"

GameConfiguration::GameConfiguration()
{

}

GameConfiguration::GameConfiguration(GameMapId mapId, string themeName, GameMode mode)
{
	m_mapId = mapId;
	//m_mapName = mapName;
	m_gameMode = mode;
	m_themeName = themeName;
}

GameConfiguration::~GameConfiguration()
{
	
}

void GameConfiguration::AddPlayer(string playerName, CharacterClassName characterClass, TeamName teamName, unsigned long id, AbilityName ability1, AbilityName ability2)
{
	m_names.push_back(playerName);
	m_characterName.push_back(characterClass);
	teamNames.push_back(teamName);
	playerID.push_back(teamName);

	customAbilities.resize(customAbilities.size()+1);
	customAbilities.at(customAbilities.size() - 1).resize(2);
	customAbilities.at(customAbilities.size() - 1).at(0) = ability1;
	customAbilities.at(customAbilities.size() - 1).at(1) = ability2;
}