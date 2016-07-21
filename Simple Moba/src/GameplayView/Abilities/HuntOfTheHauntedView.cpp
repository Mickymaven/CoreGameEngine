#include "HuntOfTheHauntedView.h"

LMMesh * HuntOfTheHauntedView::m_hauntedCreatureMesh = nullptr;
HuntOfTheHauntedView::HuntOfTheHauntedView(){}
HuntOfTheHauntedView::HuntOfTheHauntedView(LPDIRECT3DDEVICE9 device, HuntOfTheHaunted * huntOfTheHaunted)
	:AbilityView(huntOfTheHaunted), m_huntOfTheHaunted(huntOfTheHaunted)
{
	//temp lightweight inline creature mesh
	if (m_hauntedCreatureMesh == nullptr) m_hauntedCreatureMesh = new LMMesh("Resources/Characters/Shared/","CosmicSpaghetti.x", device);

	//make the views
	vector <HauntedCreature *> * creatureModels = huntOfTheHaunted->GetCreatures();

	for (unsigned int i = 0; i < creatureModels->size(); i++)
	{
		m_hauntedCreatureViews.push_back(HauntedCreatureView(device, creatureModels->at(i), m_hauntedCreatureMesh));
	}
}

HuntOfTheHauntedView::~HuntOfTheHauntedView()
{
}

void HuntOfTheHauntedView::Render()
{
	if (!IsActive()) return;

	for (unsigned int i = 0; i < m_hauntedCreatureViews.size(); i++)
	{
		m_hauntedCreatureViews.at(i).Render();
	}
}