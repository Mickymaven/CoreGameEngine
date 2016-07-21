#if !defined (BOIDVIEW_H)
#define BOIDVIEW_H


#include "../../../EngineGameModuleDirectX9/src/Base/SpriteView.h"
#include "../../../CoreGame/src/Environment/Boid.h"

class BoidView : public SpriteView
{
protected:
	Boid * m_boid;


public:
	BoidView();
	BoidView(LPDIRECT3DDEVICE9 device, Boid * boid, LMMesh * mesh);
	~BoidView();

	void Render();
};

#endif