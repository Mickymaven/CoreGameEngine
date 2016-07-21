#include "BoidView.h"

BoidView::BoidView()
{

}

BoidView::BoidView(LPDIRECT3DDEVICE9 device, Boid * boid, LMMesh * mesh)
	:SpriteView(device, boid, mesh)
{
	m_boid = boid;
}

BoidView::~BoidView()
{
}

void BoidView::Render()
{
	SpriteView::Render();
}