#if!defined (GAMESTATE_H)
#define GAMESTATE_H

enum GameOverState
{
	gameOverStateGameOn,
	gameOverStateGameOver,
	gameOverStateCount
};

#include "GameStateObject.h"

class GameState : public GameStateObject
{
private:


protected:
	GameOverState m_gameOverState;

public:
	GameState();
	~GameState();

	//Accessors
	GameOverState GetGameOverState();

	//Mutators
	void SetGameOverState(GameOverState state);

};

#endif