#include "GameMap.h"

GameMap::GameMap()
{
}

GameMap::~GameMap()
{
}

void GameMap::SpawnGen(int teamIndex, float x, float z, float spacing, int count)
{

	vector<LMVector3> * spawnList = &m_teamSpawns.at(teamIndex);

	spawnList->resize(count);

	for (int index = 0; index < count; index++)
	{
		//even
		if (index % 2 == 0) 
		{ 
			spawnList->at(index).x = x + (spacing*(index-1));
			spawnList->at(index).y = 0.0f;
			spawnList->at(index).z = z;
		}
		//odd 
		else
		{
			spawnList->at(index).x = x;
			spawnList->at(index).y = 0.0f;
			spawnList->at(index).z = z + (spacing*index);
		}
	}


}

Pathfinder * GameMap::GetPathfinder()
{
	return &m_pathfinder;
}

Sprite * GameMap::GetGround()
{
	return &m_ground;
}

vector<LMVector3>* GameMap::GetSpawnsForTeam(int team)
{
	if (team >= m_teamSpawns.size()) return nullptr;
	//else
	return &m_teamSpawns.at(team);
}
