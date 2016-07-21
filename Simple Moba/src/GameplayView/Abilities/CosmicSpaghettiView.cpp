#include "CosmicSpaghettiView.h"

LMMesh * CosmicSpaghettiView::m_spaghettiMesh = nullptr;
CosmicSpaghettiView::CosmicSpaghettiView(){}
CosmicSpaghettiView::CosmicSpaghettiView(LPDIRECT3DDEVICE9 device, CosmicSpaghetti * cosmicSpaghetti)
	:AbilityView(cosmicSpaghetti), m_cosmicSpaghetti(cosmicSpaghetti)
{
	if (m_spaghettiMesh==nullptr) m_spaghettiMesh = new LMMesh("Resources/Characters/Shared/","CosmicSpaghetti.x", device);

	m_spagettiProjectileView = SpriteView(device, cosmicSpaghetti->GetSpaghettiBall(), m_spaghettiMesh);
}

CosmicSpaghettiView::~CosmicSpaghettiView()
{
	if (m_spaghettiMesh != nullptr)
	{
		delete m_spaghettiMesh;
		m_spaghettiMesh = nullptr;
	}
}

void CosmicSpaghettiView::Render()
{
	if (!IsActive()) return;

	m_spagettiProjectileView.Render();
}