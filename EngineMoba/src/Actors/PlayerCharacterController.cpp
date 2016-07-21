#include "PlayerCharacterController.h"
#include "Character.h"

PlayerCharacterController::PlayerCharacterController():CharacterController(){}

PlayerCharacterController::PlayerCharacterController(Character *  character)
	: CharacterController(character)
{

}

PlayerCharacterController::~PlayerCharacterController()
{
}

void PlayerCharacterController::Update(float deltaTime)
{
	CharacterController::Update(deltaTime);
}

//stat accessors
vector <unsigned int> * PlayerCharacterController::GetInRangeShops() { return &m_inRangeShops; }