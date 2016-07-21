#if !defined(GAMEMESSAGE_H)
#define GAMEMESSAGE_H

#include <string>
using std::string;

#include "../../../EngineGameModuleDirectX9/src/Application/Globals.h"//todo baaaaaaaaad
#include "../../../EngineGameModel/src/Utility/LMTimer.h"

class GameMessage
{
	
private:
	char m_messageBuffer[2000];
	LMTimer m_timer;

	LPD3DXFONT m_messageFont;
	RECT m_messagePos;

public:
	GameMessage();
	GameMessage(LPD3DXFONT messageFont);
	~GameMessage();

	void SetMessage(string message);
	void Update(float deltaTime);
	void Render();
	
};

#endif