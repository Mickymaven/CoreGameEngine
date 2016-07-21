#include "CorePlayerCharacterController.h"

CorePlayerCharacterController::CorePlayerCharacterController()
	: PlayerCharacterController(), CoreCharacterController()
{
}

CorePlayerCharacterController::CorePlayerCharacterController( CoreCharacter *  character ) 
	: PlayerCharacterController(character), CoreCharacterController(character)
{

}

CorePlayerCharacterController::~CorePlayerCharacterController()
{
}