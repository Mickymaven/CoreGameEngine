#if !defined(COSMICSPAGHETTIVIEW_H)
#define COSMICSPAGHETTIVIEW_H

#include "../AbilityView.h"
#include "../../../../CoreGame/src/Gameplay/Abilities/CosmicSpaghetti.h"
#include "../../../../EngineGameModuleDirectX9/src/Base/SpriteView.h"

class CosmicSpaghettiView : public AbilityView
{
private:
	static LMMesh * m_spaghettiMesh;

	CosmicSpaghetti * m_cosmicSpaghetti;
	SpriteView m_spagettiProjectileView;

public:
	CosmicSpaghettiView();
	CosmicSpaghettiView(LPDIRECT3DDEVICE9 device, CosmicSpaghetti * cosmicSpaghetti);
	~CosmicSpaghettiView();

	void Render();
};

#endif