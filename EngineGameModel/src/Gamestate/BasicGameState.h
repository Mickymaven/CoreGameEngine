#if!defined(BASICGAMESTATE_H)
#define BASICGAMESTATE_H

#include "GameState.h"


class BasicGameState : public GameState
{
private:
protected:

	float m_gameElapsedTime;
	LARGE_INTEGER m_gameStartTime;
	LARGE_INTEGER m_gameCurrentTime;
	float m_FrequencyQuadPart;

public:
	bool m_isDebugTextOn;
	
	BasicGameState();
	~BasicGameState();

	void UpdateGameTime();

	float * GetGameElapsedTime();
	LARGE_INTEGER * GetGameStartTime();
	LARGE_INTEGER * GetGameCurrentTime();

	void SetGameElapsedTime(float elapsed);
	void SetGameStartTime(LARGE_INTEGER start);
	void SetGameCurrentTime(LARGE_INTEGER current);

};

#endif