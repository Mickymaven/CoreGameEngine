#include "HiddenPowerView.h"


HiddenPowerView::HiddenPowerView()
{

}

HiddenPowerView::HiddenPowerView(LPDIRECT3DDEVICE9 device, HiddenPower * hiddenPowerAbility)
	: AbilityView(hiddenPowerAbility), m_hiddenPowerAbility(hiddenPowerAbility)
{
	//if (m_mesh==nullptr) m_mesh = new LMMesh("[Resources/Characters/Shared/ here]", "[blah.x here]", device);
	//m_theSprite = SpriteView(device, motoBoostAbility->GetBlah(), m_mesh);
}

HiddenPowerView::~HiddenPowerView()
{

}

void HiddenPowerView::Render()
{
	if (!IsActive()) return;

	//render member views here
}