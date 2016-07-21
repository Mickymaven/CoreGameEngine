#if !defined(GAMEMAPFACTORY_H)
#define GAMEMAPFACTORY_H

#include "../Maps/GameMap.h"
#include "../../../CoreGame/src/Gamestate/GameMapId.h"


#include "../../../CoreGame/src/Gameplay/Maps/MapBarebones.h"
#include "../../../CoreGame/src/Gameplay/Maps/MapTabulaRasa.h"


enum ConstructGameMapCode
{
	constructGameMapCodeOK,
	constructGameMapCodeError,
	constructGameMapCodeCount

};

class GameMapFactory
{
private:
	GameMap * constructedGameMap;

public:
	GameMapFactory();
	~GameMapFactory();

	ConstructGameMapCode ConstructGameMap(GameMap ** gameMapOut, GameMapId gameMapId);



};

#endif