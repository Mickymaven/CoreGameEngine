#include "AntiFireballView.h"

LMMesh * AntiFireballView::m_mesh = nullptr;

AntiFireballView::AntiFireballView()
{

}

AntiFireballView::AntiFireballView(LPDIRECT3DDEVICE9 device, AntiFireball * antiFireball)
	: AbilityView(antiFireball), m_antiFireball(antiFireball)
{ 
	if (m_mesh==nullptr) m_mesh = new LMMesh("Resources/Characters/Shared/", "bird.x", device);

	m_theSprite = SpriteView(device, antiFireball->GetFireball(), m_mesh);
}

AntiFireballView::~AntiFireballView()
{

}

void AntiFireballView::Render()
{
	if (!IsActive()) return;

	m_theSprite.Render();
}