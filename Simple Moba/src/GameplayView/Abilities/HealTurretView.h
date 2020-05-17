#if !defined (HEALTURRETVIEW_H)
#define HEALTURRETVIEW_H

#include "../../../../CoreGame/src/Gameplay/Abilities/HealTurret.h"

#include "../../../../EngineGameModuleDirectX9/src/Base/SpriteView.h"

#include "../AbilityView.h"


class HealTurretView : public AbilityView
{
private:
	HealTurret* m_turret;
	SpriteView m_turretView;

public:
	HealTurretView();
	HealTurretView(LPDIRECT3DDEVICE9 device, HealTurret* m_turret);
	~HealTurretView();

	void Render();

};

#endif