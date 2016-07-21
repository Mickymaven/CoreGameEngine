#include "CoreCharacterController.h"

CoreCharacterController::CoreCharacterController()
{
}

CoreCharacterController::CoreCharacterController(CoreCharacter * character)
	: m_coreCharacter(character)
{

}

CoreCharacterController::~CoreCharacterController()
{
}

CoreCharacter * CoreCharacterController::GetCoreCharacter()
{
	return m_coreCharacter;
}
