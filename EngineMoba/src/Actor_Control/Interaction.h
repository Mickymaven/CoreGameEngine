#if !defined (INTERACTION_H)
#define INTERACTION_H

#include "../../../EngineMoba/src/Actors/Actor.h"


#include "InteractionZone.h"
#include "../Gamestate/MobaControllerSharedData.h"


class Interaction : public MobaControllerSharedData
{

private:
protected:
	Actor * m_owner;
	LMVector3 * m_ownerPosition;
	vector <InteractionZone*> m_interactionZones;

public:
	Interaction();
	~Interaction();

	void virtual Update(float deltaTime);
	
	vector <InteractionZone*> * GetInteractionZones();
};

#endif