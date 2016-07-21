#if !defined(THESLURPENINGVIEW_H)
#define THESLURPENINGVIEW_H

#include "../../../../CoreGame/src/Gameplay/Abilities/TheSlurpening.h"
#include "../../../../EngineGameModuleDirectX9/src/Base/SpriteView.h"
#include "../AbilityView.h"

class TheSlurpeningView : public AbilityView
{
private:
	TheSlurpening * m_theSlurpening;
	SpriteView m_strawView;

public:
	TheSlurpeningView();
	TheSlurpeningView(LPDIRECT3DDEVICE9 device, TheSlurpening * m_theSlurpening);
	~TheSlurpeningView();

	void Render();

	TheSlurpening * GetTheSlurpening();
};

#endif