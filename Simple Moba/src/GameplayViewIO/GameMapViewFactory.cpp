#include "GameMapViewFactory.h"

GameMapViewFactory::GameMapViewFactory()
{
	constructedMapView = nullptr;
	m_gameAssetFactory = nullptr;
}

GameMapViewFactory::~GameMapViewFactory()
{
}

bool GameMapViewFactory::Init(GameAssetFactory * gameAssetFactory)
{
	m_gameAssetFactory = gameAssetFactory;

	return true;
}

ConstructGameMapViewCode GameMapViewFactory::ConstructGameMapView(GameMapView ** gameMapViewOut, GameMap * gameMap, GameMapId mapId)
{
	//Ground MeshFirst
	AssetMeshName assetId;

	switch (mapId)
	{
	case gameMapTabulaRasa: assetId = assetTabulaRasaGroundStandard1; break;
	case gameMapBarebones: assetId = assetBarebonesGroundStandard1; break;

	}

	LMMesh * mesh = m_gameAssetFactory->GetAssetMesh(assetId);
	////////////////


	// All of it into GameMapView
	constructedMapView = new GameMapView();

	*constructedMapView->GetGroundView() = SpriteView(g_D3D_Device, gameMap->GetGround(), mesh);

	* gameMapViewOut = constructedMapView;
	return constructGameMapViewOK;
}
