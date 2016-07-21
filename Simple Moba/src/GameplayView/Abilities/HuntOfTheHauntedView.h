#if !defined(HUNTOFTHEHAUNTEDVIEW_H)
#define HUNTOFTHEHAUNTEDVIEW_H

#include "../../../../CoreGame/src/Gameplay/Abilities/HuntOfTheHaunted.h"
#include "../AbilityView.h"
#include "HauntedCreatureView.h"

class HuntOfTheHauntedView : public AbilityView
{
	static LMMesh * m_hauntedCreatureMesh;

	HuntOfTheHaunted * m_huntOfTheHaunted;
	vector<HauntedCreatureView> m_hauntedCreatureViews;

public:
	HuntOfTheHauntedView();
	HuntOfTheHauntedView(LPDIRECT3DDEVICE9 device, HuntOfTheHaunted * huntOfTheHaunted);
	~HuntOfTheHauntedView();
	
	void Render();
};

#endif