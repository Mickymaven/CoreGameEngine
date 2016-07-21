#include "GameState.h"

GameState::GameState()
{
	m_gameOverState = gameOverStateGameOn;
}

GameState::~GameState()
{

}

//Accessors
GameOverState GameState::GetGameOverState()
{
	return m_gameOverState;
}

//Mutators
void GameState::SetGameOverState(GameOverState state)
{
	m_gameOverState = state;
}