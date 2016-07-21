#include "PlayerInputController.h"

PlayerInputController::PlayerInputController()
{
	m_gameInputController = NULL;
}

PlayerInputController::PlayerInputController(GameInputController * gameInputController, StandardMatch5v5State * gameStateIn)
{
	gameState = gameStateIn;
	m_gameInputController = gameInputController;

	vec = NULL;
}

PlayerInputController::~PlayerInputController()
{

}

void PlayerInputController::Update(float deltaTime)
{
	for (unsigned int i = 0; i < m_inputSets.size(); i++)
	{
		m_inputSets.at(i)->Update(deltaTime);

		vec = m_inputModels.at(i)->GetVectorForCurrentState();

		for (unsigned int index = 0; index < vec->size(); index++)
		{
			if (IsPressForAction(m_inputModels.at(i), false, vec->at(index)))
			{
				m_inputSets.at(i)->AttemptAction(vec->at(index), deltaTime);
			}

			if (IsPressForAction(m_inputModels.at(i), true, vec->at(index)))
			{
				m_inputSets.at(i)->SpamAction(vec->at(index), deltaTime);
			}
		}

		m_inputSets.at(i)->Finally(deltaTime);

		
	}
}

bool PlayerInputController::IsPressForAction(InputModel * inputModel, bool isSpamPass, int action)
{
	bool isPress = false;
	
	
	bool isSpam;
	
	if (isSpamPass) isSpam = true;
	else if (!isSpamPass) isSpam = inputModel->m_spamFlags[action];


	if (inputModel->m_keybinds[action] == NO_KEY) isPress = false;

	else if (inputModel->m_keybinds[action] == MO_LEFT_BUTTON)
	{
		if (m_gameInputController->GetMousePress(LEFT_BUTTON, isSpam, false)) isPress = true;
	}
	else if (inputModel->m_keybinds[action] == MO_RIGHT_BUTTON)
	{
		if (m_gameInputController->GetMousePress(RIGHT_BUTTON, isSpam, false)) isPress = true;
	}
	else if (inputModel->m_keybinds[action] == MO_MIDDLE_BUTTON)
	{
		if (m_gameInputController->GetMousePress(MIDDLE_BUTTON, isSpam, false)) isPress = true;
	}
	else if (inputModel->m_keybinds[action] == MO_ZDELTA)
	{
		if (m_gameInputController->GetZDelta() != 0) isPress = true;
	}

	else if (m_gameInputController->GetKeyPress(inputModel->m_keybinds[action], isSpam, false)) isPress = true;

	return isPress;
}

void PlayerInputController::AddInputSet(InputSet * inputSet)
{
	//be sure to add input sets in order
	if (inputSet != NULL) m_inputSets.push_back(inputSet);
}

void  PlayerInputController::AddInputModel(InputModel * inputModel)
{
	if (inputModel != NULL) m_inputModels.push_back(inputModel);
}
