#if !defined(BOIDSTORMVIEW_H)
#define BOIDSTORMVIEW_H

#include <vector>
using std::vector;

#include "../../../EngineGameModuleDirectX9/src/Graphics/LMMesh.h"
#include "../../../CoreGame/src/Environment/Boidstorm.h"
#include "BoidView.h"

class BoidstormView
{
protected:
	Boidstorm * m_boidstorm;
	vector<SpriteView> m_boidViews;

	static LMMesh * m_boidMesh;

	D3DMATERIAL9 m_birdMaterial; // LightWeight;

public:
	BoidstormView();
	BoidstormView(LPDIRECT3DDEVICE9 device, Boidstorm * boidstorm);
	~BoidstormView();

	void Render();

};

#endif