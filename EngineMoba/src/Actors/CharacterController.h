#if !defined(CHARACTERCONTROLLER_H)
#define CHARACTERCONTROLLER_H

#include "Character.h"

//Base class for NPCController and PlayerCharacterController

class CharacterController
{
protected:
	Character * m_character;
	Actor * m_actor;

	WalkState * m_walkState;

public:
	CharacterController();
	CharacterController(Character * character);
	~CharacterController();

	void Update(float deltaTime);

	//Actor * GetActor();
	Character * GetCharacter();
};

#endif