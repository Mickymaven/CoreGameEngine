#include "BasicProjectileView.h"

BasicProjectileView::BasicProjectileView(){}

BasicProjectileView::BasicProjectileView(LPDIRECT3DDEVICE9 device, BasicProjectile * basicProjectile, LMMesh * mesh)
	:SpriteView(device, basicProjectile, mesh), m_basicProjectile(basicProjectile)
{
}

BasicProjectileView::~BasicProjectileView()
{
}

void BasicProjectileView::Render()
{
	if (m_basicProjectile->GetState() == basicProjectileStateSeeking)
		SpriteView::Render();
}

BasicProjectile * BasicProjectileView::GetProjectile() { return m_basicProjectile; }