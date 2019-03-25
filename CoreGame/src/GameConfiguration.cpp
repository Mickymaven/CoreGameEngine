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
	m_playerIDs.push_back(id);

	customAbilities.resize(customAbilities.size()+1);
	customAbilities.at(customAbilities.size() - 1).resize(2);
	customAbilities.at(customAbilities.size() - 1).at(0) = ability1;
	customAbilities.at(customAbilities.size() - 1).at(1) = ability2;
}

bool GameConfiguration::GetNameByPlayerID(string ** playerNameOut, unsigned long * id)
{
	for (unsigned int i = 0; i < m_playerIDs.size(); i++)
	{
		if (m_playerIDs.at(i) == *id)
		{
			*playerNameOut = &m_names.at(i);
			return true;
		}
	}

	return false;
}
