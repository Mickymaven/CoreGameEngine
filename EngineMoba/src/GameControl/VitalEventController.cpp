#include "VitalEventController.h"

VitalEventController::VitalEventController()
{
}

VitalEventController::~VitalEventController()
{
}

bool VitalEventController::Init(MobaState * gameState)
{
	m_gameState = gameState;

	m_buffController.Init(gameState);
	m_healingController.Init(gameState);
	m_damageController.Init(gameState);

	return true;
}

void VitalEventController::Update(float deltaTime)
{
	m_buffController.Update(deltaTime);
	m_healingController.Update(deltaTime);
	m_damageController.Update(deltaTime);
}

DamageController * VitalEventController::GetDamageController() { return &m_damageController; }