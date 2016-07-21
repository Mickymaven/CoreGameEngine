#if !defined (MOBAMESSAGEEVENTMANAGER_H)
#define MOBAMESSAGEEVENTMANAGER_H


#include "../../../CoreGame/src/Gamestate/StandardMatch5v5State.h"

#include "../../../EngineMoba/src/GameControl/DamageController.h"
#include "../ViewControl/CameraDirector.h"
#include "../UI/GameMessage.h"

class MobaMessageEventManager
{
protected:
	GameMessage * m_gameMessage;
	StandardMatch5v5State * m_gameState;
	CameraDirector * m_cameraDirector;
	DamageController * m_damageController;

public:
	MobaMessageEventManager();
	~MobaMessageEventManager();

	bool Init(StandardMatch5v5State * gameState, GameMessage * gameMessage, CameraDirector * cameraDirector, DamageController * damageController);
	void Event(DamageEvent damageEvent); //will start off with a switch 

};


#endif