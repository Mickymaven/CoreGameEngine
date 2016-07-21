#if !defined(BASICPROJECTILEVIEW_H)
#define BASICPROJECTILEVIEW_H

#include "../../../../EngineGameModuleDirectX9/src/Base/SpriteView.h"
#include "../../../../CoreGame/src/Gameplay/Abilities/BasicProjectile.h"

class BasicProjectileView: public SpriteView
{
private:
	BasicProjectile * m_basicProjectile;

public:
	BasicProjectileView();
	BasicProjectileView(LPDIRECT3DDEVICE9 device, BasicProjectile * basicProjectile, LMMesh * mesh);
	~BasicProjectileView();

	void Render();

	BasicProjectile * GetProjectile();
};

#endif