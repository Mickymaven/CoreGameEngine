#include "HauntedCreatureView.h"

HauntedCreatureView::HauntedCreatureView(LPDIRECT3DDEVICE9 device, HauntedCreature * creature, LMMesh * mesh)
	:SpriteView(device, creature, mesh), m_creature(creature)
{

}

HauntedCreatureView::~HauntedCreatureView()
{
}

void HauntedCreatureView::Render()
{
	SpriteView::Render();
}

HauntedCreature * HauntedCreatureView::GetCreature(){ return m_creature; }