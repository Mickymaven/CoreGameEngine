#if !defined(MOTOBOOSTVIEW_H)
#define MOTOBOOSTVIEW_H

#include "../../../../EngineGameModuleDirectX9/src/Base/SpriteView.h"
#include "../../../../CoreGame/src/Gameplay/Abilities/MotoBoost.h"
#include "../AbilityView.h"

class MotoBoostView : public AbilityView
{
protected:
	MotoBoost * m_motoBoostAbility;
public:
	MotoBoostView();
	MotoBoostView(LPDIRECT3DDEVICE9 device, MotoBoost * motoBoostAbility);
	~MotoBoostView();

	void Render();
};

#endif