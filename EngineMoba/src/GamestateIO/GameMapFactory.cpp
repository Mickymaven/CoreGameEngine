#include "GameMapFactory.h"

GameMapFactory::GameMapFactory()
{
	constructedGameMap = nullptr;

}

GameMapFactory::~GameMapFactory()
{
}

ConstructGameMapCode GameMapFactory::ConstructGameMap(GameMap ** gameMapOut, GameMapId gameMapId)
{
	//instancese should be deleted by game mode. 

	switch (gameMapId)
	{
	case gameMapTabulaRasa:constructedGameMap = new MapTabulaRasa(); break;//init hidden as derived class in this factory
	case gameMapBarebones:constructedGameMap = new MapBarebones(); break;//init hidden as derived class in this factory
	default:return constructGameMapCodeError;
	}

	*gameMapOut = constructedGameMap;

	return constructGameMapCodeOK;
}
