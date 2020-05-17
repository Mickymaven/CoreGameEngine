#if !defined (HEALTURRETVIEW_H)
#define HEALTURRETVIEW_H

#include "../../../../CoreGame/src/Gameplay/Abilities/HealTurret.h"

#include "../../../../EngineGameModuleDirectX9/src/Base/SpriteView.h"

#include "../AbilityView.h"


class HealTurretView : public AbilityView
{
private:
	HealTurret * m_turret;
	SpriteView m_meringueView;

public:
	HealTurretView();
	HealTurretView(LPDIRECT3DDEVICE9 device, SpookySpaceMeringue* m_spookySpaceMeringue);
	~HealTurretView();

	void Render();

};

#endif