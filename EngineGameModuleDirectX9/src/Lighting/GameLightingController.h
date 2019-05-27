#if !defined(GAMELIGHTINGCONTROLLER_H)
#define GAMELIGHTINGCONTROLLER_H

#include <d3dx9.h>

#include "../Application/GlobalsDX9.h"

enum GameLightingState
{
	gameLightsOff,
	gameLightsOn,
	gameLightsCount
};

enum GameLightNames
{
	gameLight0,
	gameLight1,
	gameLight2,
	gameLight3,
	gameLight4,
	gameLight5,
	gameLight6,
	gameLightBigWhite,
	gameLightNameCount
};


class GameLightingController
{
private:
	GameLightingState m_state;
	unsigned int lightCount;

	D3DLIGHT9 m_light; // the most basic ambient light

	//directional lights that give volume
	//a bit like a stage


	D3DLIGHT9 m_purple;
	D3DLIGHT9 m_white;
	D3DLIGHT9 m_white2;
	D3DLIGHT9 m_BigWhite;



	D3DLIGHT9 m_magenta;
	D3DLIGHT9 m_cyan;
	D3DLIGHT9 m_yellow;
	D3DLIGHT9 moonlight;
	D3DLIGHT9 purpleBaseLight;
	D3DLIGHT9 yellowBaseLight;


public:
	GameLightingController();
	~GameLightingController();
	bool Init();

	void GameLightsOff();
	void GameLightsOn();
};

#endif