#if !defined (SPOOKYSPACEMERINGUEVIEW_H)
#define SPOOKYSPACEMERINGUEVIEW_H

#include "../../../../CoreGame/src/Gameplay/Abilities/SpookySpaceMeringue.h"

#include "../../../../EngineGameModuleDirectX9/src/Base/SpriteView.h"

#include "../AbilityView.h"


class SpookySpaceMeringueView : public AbilityView
{
private:
	SpookySpaceMeringue * m_spookySpaceMeringue;
	SpriteView m_meringueView;

public:
	SpookySpaceMeringueView();
	SpookySpaceMeringueView(LPDIRECT3DDEVICE9 device, SpookySpaceMeringue * m_spookySpaceMeringue);
	~SpookySpaceMeringueView();

	void Render();

};

#endif