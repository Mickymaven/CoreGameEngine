#include "InputSet.h"

GameInputController * InputSet::sm_gameInputController = NULL;

void InputSet::SetInputController(GameInputController * gameInputController)
{
	sm_gameInputController = gameInputController;
}

InputSet::InputSet(){}


InputSet::~InputSet(){}

void InputSet::Update(float deltaTime){}
void InputSet::AttemptAction(int action, float deltaTime) {}
void InputSet::SpamAction(int action, float deltaTime) {}
void InputSet::SetModel(InputModel * model)
{
	m_model = model;
}

void InputSet::Finally(float deltaTime)
{
	//sm_gameInputController->ExpendAllTheThings(true, false);
}