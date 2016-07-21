#if !defined(ACTORVIEW_H)
#define ACTORVIEW_H

#include "VitalEntityView.h"
#include "../../../EngineMoba/src/Actors/Actor.h"

class ActorView : public VitalEntityView
{
protected:
	Actor * m_actor;
public:
	ActorView(LPDIRECT3DDEVICE9 device, Actor * actor, LMMesh * mesh);
	~ActorView();

	void Render();
	Actor * GetActor();
};

#endif