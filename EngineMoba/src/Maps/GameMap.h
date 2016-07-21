#if !defined(GAMEMAP_H)
#define GAMEMAP_H


#include "../Pathfinding/Pathfinder.h"
#include "../../../EngineGameModel/src/Base/Sprite.h"
#include "../../../EngineGameModel/src/Maths/LMVector3.h"

class GameMap
{
private:
protected:
	//Groups of spawn points
	///npc class spawns (maybe an extra layer between maps and modes)

	int m_teamLimit;

	Pathfinder m_pathfinder;

	//vector<Sprite *> m_walls;
	Sprite m_ground;
	
	vector<vector<LMVector3>> m_teamSpawns;
	
	//EnvironmentControllers or configs
	//Boidstorm;

	//Materials for grounds or similar
	//Lighting Sets Etc


public:
	GameMap();
	~GameMap();

	//bool Init();

	void SpawnGen(int teamIndex, float x, float z, float spacing, int count);
	
	Pathfinder * GetPathfinder();
	Sprite * GetGround();
	
	vector<LMVector3> * GetSpawnsForTeam(int team);

};

#endif