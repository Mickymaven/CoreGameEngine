#if !defined(BASICATTACKVIEW_H)
#define BASICATTACKVIEW_H

#include <d3dx9.h>

#include "../../../../CoreGame/src/Gameplay/Abilities/BasicAttack.h"

#include "../AbilityView.h"
#include "BasicProjectileView.h"

class BasicAttackView: public AbilityView
{
private:
	static LMMesh * m_sharedMesh;
	
	BasicAttack * m_basicAttack;
	vector<BasicProjectileView> m_basicAttackViews;

public:
	BasicAttackView();
	BasicAttackView(LPDIRECT3DDEVICE9 device, BasicAttack * basicAttack);
	~BasicAttackView();

	void Render();
};

#endif