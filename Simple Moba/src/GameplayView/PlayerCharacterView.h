#if !defined(PLAYERCHARACTERVIEW_H)
#define PLAYERCHARACTERVIEW_H

#include "ActorView.h"
#include "../../../EngineMoba/src/Actors/PlayerCharacterController.h"

#include "CharacterControllerView.h"

class PlayerCharacterView : public CharacterControllerView
{
protected:
	PlayerCharacterController * m_playerCharacterController;

public:
	PlayerCharacterView();
	PlayerCharacterView(
		PlayerCharacterController * playerCharacterController,
		CharacterView * characterView);
	~PlayerCharacterView();

	void Render();

	PlayerCharacterController * GetPlayerCharacterController();

	
};

#endif