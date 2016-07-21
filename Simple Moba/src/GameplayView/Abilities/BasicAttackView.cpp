#include "BasicAttackView.h"

LMMesh * BasicAttackView::m_sharedMesh = NULL;


BasicAttackView::BasicAttackView(){}

BasicAttackView::BasicAttackView(LPDIRECT3DDEVICE9 device, BasicAttack * basicAttack)
	:AbilityView(basicAttack), m_basicAttack(basicAttack)
{
	if (m_sharedMesh == NULL) m_sharedMesh = new LMMesh("Resources/Characters/Shared/","bird.x", g_D3D_Device); //Lightweight sprite, static = shared all characters

	vector<BasicProjectile> * basicProjectiles = basicAttack->GetProjectiles();
	
	for (unsigned int i = 0; i < basicProjectiles->size(); i++)
	{
		m_basicAttackViews.push_back(BasicProjectileView(device, &basicProjectiles->at(i), m_sharedMesh));
	}
}

BasicAttackView::~BasicAttackView()
{
}

void BasicAttackView::Render()
{
	//if (!IsActive()) return;

	for (unsigned int i = 0; i < m_basicAttackViews.size(); i++)
	{
		m_basicAttackViews.at(i).Render();
	}
}