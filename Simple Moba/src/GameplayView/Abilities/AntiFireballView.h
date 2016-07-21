#if !defined(ANTIFIREBALLVIEW_H)
#define ANTIFIREBALLVIEW_H
//SpamFireGhettiBall

#include "../../../../CoreGame/src/Gameplay/Abilities/AntiFireball.h"
#include "../AbilityView.h"
#include "../../../../EngineGameModuleDirectX9/src/Base/SpriteView.h"

class AntiFireballView : public AbilityView
{
protected:
	AntiFireball * m_antiFireball;
	static LMMesh * m_mesh;
	SpriteView m_theSprite;

public:
	AntiFireballView();
	AntiFireballView(LPDIRECT3DDEVICE9 device, AntiFireball * antiFireball);
	~AntiFireballView();

	void Render();
};

#endif