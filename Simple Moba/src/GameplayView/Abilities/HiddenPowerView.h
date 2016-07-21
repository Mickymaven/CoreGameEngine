#if !defined (HIDDENPOWERVIEW_H)
#define ETERNALLIGHTVIEW_H

#include "../../../../EngineGameModuleDirectX9/src/Base/SpriteView.h"
#include "../../../../CoreGame/src/Gameplay/Abilities/HiddenPower.h"
#include "../AbilityView.h"

class HiddenPowerView : public AbilityView
{
protected:
	HiddenPower * m_hiddenPowerAbility;
public:
	HiddenPowerView();
	HiddenPowerView(LPDIRECT3DDEVICE9 device, HiddenPower * hiddenPowerAbility);
	~HiddenPowerView();

	void Render();
};

#endif