#if !defined (ELIXIRBURSTVIEW_H)
#define ELIXIRBURSTVIEW_H

#include "../../../../EngineGameModuleDirectX9/src/Base/SpriteView.h"
#include "../../../../CoreGame/src/Gameplay/Abilities/ElixirBurst.h"
#include "../AbilityView.h"


class ElixirBurstView : public AbilityView
{
private:
	static LMMesh * m_ballMesh;
	
	ElixirBurst * m_elixirBurstAbility;
	SpriteView m_ballView;

public:
	ElixirBurstView();
	ElixirBurstView(LPDIRECT3DDEVICE9 device, ElixirBurst * elixirBurstAbility);
	~ElixirBurstView();

	void Render();

};


#endif