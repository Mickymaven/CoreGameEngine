#if !defined(GAMEMAPVIEWFACTORY_H)
#define GAMEMAPVIEWFACTORY_H

#include "../GameplayView/GameMapView.h"
#include "../../../CoreGame/src/Gamestate/GameMapId.h"
#include "../GamestateViewIO/GameAssetFactory.h"

enum ConstructGameMapViewCode
{
	constructGameMapViewOK,
	constructGameMapViewError,
	constructGameMapViewCount
};

class GameMapViewFactory
{
	GameMapView * constructedMapView;

	GameAssetFactory * m_gameAssetFactory;

public:
	GameMapViewFactory();
	~GameMapViewFactory();

	bool Init(GameAssetFactory * gameAssetFactory);

	ConstructGameMapViewCode ConstructGameMapView(GameMapView ** gameMapViewOut, GameMap * gameMap, GameMapId mapId);

};


#endif