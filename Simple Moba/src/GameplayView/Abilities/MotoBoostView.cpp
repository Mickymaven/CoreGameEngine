#include "MotoBoostView.h"

//LMMesh * MotoBoostView::m_mesh = nullptr;

MotoBoostView::MotoBoostView()
{

}

MotoBoostView::MotoBoostView(LPDIRECT3DDEVICE9 device, MotoBoost * motoBoostAbility)
	: AbilityView(motoBoostAbility), m_motoBoostAbility(motoBoostAbility)
{ 
	//if (m_mesh==nullptr) m_mesh = new LMMesh("[Resources/Characters/Shared/ here]", "[blah.x here]", device);
	//m_theSprite = SpriteView(device, motoBoostAbility->GetBlah(), m_mesh);
}

MotoBoostView::~MotoBoostView()
{

}

void MotoBoostView::Render()
{
	if (!IsActive()) return;
	
	//render member views here
}