#if !defined(GAMEMAPVIEW_H)
#define GAMEMAPVIEW_H

#include "../../../EngineMoba/src/Maps/GameMap.h"
#include "../../../EngineGameModuleDirectX9/src/Base/SpriteView.h"

class GameMapView
{
	SpriteView m_groundView;
	//vector<SpriteView *> m_wallViews;
	//vector<vector<LMVector3>> m_teamSpawnViews;

public:
	GameMapView();
	~GameMapView();

	void Render();

	SpriteView  * GetGroundView();

};

#endif