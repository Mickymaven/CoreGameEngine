#include "BoidstormView.h"

LMMesh * BoidstormView::m_boidMesh = nullptr;

BoidstormView::BoidstormView()
{
	OutputDebugString("BoidstormView \n");
}

BoidstormView::BoidstormView(LPDIRECT3DDEVICE9 device, Boidstorm * boidstorm)
{

	m_birdMaterial.Diffuse.r = m_birdMaterial.Ambient.r = 0.8f;
	m_birdMaterial.Diffuse.g = m_birdMaterial.Ambient.g = 0.8f;
	m_birdMaterial.Diffuse.b = m_birdMaterial.Ambient.b = 0.8f;
	m_birdMaterial.Specular.r = 0.6f;
	m_birdMaterial.Specular.g = 0.6f;
	m_birdMaterial.Specular.b = 0.6f;
	m_birdMaterial.Power = 5.0f;

	if (m_boidMesh == nullptr) m_boidMesh = new LMMesh("Resources/Characters/Shared/", "CosmicSpaghetti.x", device, &m_birdMaterial, false);
	//if (m_boidMesh == nullptr) m_boidMesh = new LMMesh("Resources/Characters/Shared/", "CosmicSpaghetti.x", device);
	///= LMMesh("Resources/Characters/Shared/", "bird.x", device, &m_birdMaterial, false);

	m_boidstorm = boidstorm;

	vector<Boid *> * boids = boidstorm->GetBoids();

	m_boidViews.resize(boids->size());

	//init boids

	
	
	for (unsigned int i = 0; i < boids->size(); i++)
	{
		m_boidViews.at(i) = SpriteView(device, boids->at(i), m_boidMesh);
			
			//BoidView(device, boids->at(i), &m_birdMesh);
	}
}

BoidstormView::~BoidstormView()
{
	OutputDebugString("~BoidstormView() \n");
}

void BoidstormView::Render()
{
	for (unsigned int i = 0; i < m_boidViews.size(); i++)
	{
		m_boidViews.at(i).Render();
	}
}