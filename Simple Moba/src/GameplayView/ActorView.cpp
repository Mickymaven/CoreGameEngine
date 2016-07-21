#include "ActorView.h"

ActorView::ActorView(LPDIRECT3DDEVICE9 device, Actor * actor, LMMesh * mesh)
	:VitalEntityView(device, actor, mesh)
{
	m_actor = actor;
}

ActorView::~ActorView()
{

}

void ActorView::Render()
{
	//VitalEntityView::Render();
	if (m_actor->Actor::GetState() != actorDead)
		SpriteView::Render();
}

Actor * ActorView::GetActor() { return m_actor; }