#include "CoreNPCController.h"

CoreNPCController::CoreNPCController()
	: NPCController(), CoreCharacterController()
{
}

CoreNPCController::CoreNPCController(CoreCharacter * character)
	:NPCController(character), CoreCharacterController(character)
{
}

CoreNPCController::~CoreNPCController()
{
}

void CoreNPCController::Update(float deltaTime)
{
	m_character->Update(deltaTime);
}
