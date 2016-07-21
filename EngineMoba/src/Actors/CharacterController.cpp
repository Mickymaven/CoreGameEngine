#include "CharacterController.h"

CharacterController::CharacterController()
{
}

CharacterController::CharacterController(Character * character) : 
	m_character(character),
	m_actor(character->GetActor())
{
	m_walkState = character->GetWalkState();
	//todo we seem to have allot of walk state stuff accessed directly from derived npc controllers
	// is kind of bad idea as characters should manage all that stuff and we only interface whith char functions
	//that we need more of

}

CharacterController::~CharacterController()
{
}

void CharacterController::Update(float deltaTime)
{
	m_character->Update(deltaTime);
}

//Actor * CharacterController::GetActor() { return m_actor; }

Character * CharacterController::GetCharacter() { return m_character; }


