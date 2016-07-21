#if !defined(HAUNTEDCREATUREVIEW_H)
#define HAUNTEDCRREATUREVIEW_H

#include "../../../../EngineGameModuleDirectX9/src/Base/SpriteView.h"
#include "../../../../CoreGame/src/Gameplay/Abilities/HauntedCreature.h"

class HauntedCreatureView : public SpriteView
{
private:
	HauntedCreature * m_creature;

public:
	HauntedCreatureView(LPDIRECT3DDEVICE9 device, HauntedCreature * creature, LMMesh * mesh);
	~HauntedCreatureView();

	void Render();

	HauntedCreature * GetCreature();

};

#endif