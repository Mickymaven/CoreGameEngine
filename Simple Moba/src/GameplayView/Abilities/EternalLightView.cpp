#include "EternalLightView.h"


EternalLightView::EternalLightView()
{

}

EternalLightView::EternalLightView(LPDIRECT3DDEVICE9 device, EternalLight * eternalLightAbility)
	: AbilityView(eternalLightAbility), m_eternalLightAbility(eternalLightAbility)
{
	//if (m_mesh==nullptr) m_mesh = new LMMesh("[Resources/Characters/Shared/ here]", "[blah.x here]", device);
	//m_theSprite = SpriteView(device, motoBoostAbility->GetBlah(), m_mesh);
}

EternalLightView::~EternalLightView()
{

}

void EternalLightView::Render()
{
	if (!IsActive()) return;

	//render member views here
}