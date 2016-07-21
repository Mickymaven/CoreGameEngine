#if !defined(VALIANTLEAPVIEW_H)
#define VALIANTLEAPVIEW_H

#include "../../../../CoreGame/src/Gameplay/Abilities/ValiantLeap.h"
#include "../AbilityView.h"
//#include "../../../../EngineGameModuleDirectX9/src/Base/SpriteView.h"

class ValiantLeapView : public AbilityView
{
private:
	ValiantLeap * m_valiantLeap;

public:

	ValiantLeapView();
	ValiantLeapView(LPDIRECT3DDEVICE9 device, ValiantLeap * valiantLeap);
	~ValiantLeapView();

	void Render();

};

#endif