#if !defined(ETERNALLIGHTVIEW_H)
#define ETERNALLIGHTVIEW_H

#include "../../../../EngineGameModuleDirectX9/src/Base/SpriteView.h"
#include "../../../../CoreGame/src/Gameplay/Abilities/EternalLight.h"
#include "../AbilityView.h"

class EternalLightView : public AbilityView
{
protected:
	EternalLight * m_eternalLightAbility;
public:
	EternalLightView();
	EternalLightView(LPDIRECT3DDEVICE9 device, EternalLight * eternalLightAbility);
	~EternalLightView();

	void Render();
};

#endif