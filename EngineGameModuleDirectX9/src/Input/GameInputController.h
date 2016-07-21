#if !defined(GAMEINPUTCONTROLLER_H)
#define GAMEINPUTCONTROLLER_H

#include <vector>
using std::vector;

#include "DirectInput8Controller.h"
#include "../UI/UIArea.h"
#include "../ControlHeader.h"

class GameInputController
{
private:
	DirectInput8Controller * m_input;
	int m_keyPresses[KEYS_SIZE];
	int m_keyDownLast[KEYS_SIZE];
	int m_mousePresses[3];
	int m_mouseDownLast[3];

	int m_isKeyExpended[KEYS_SIZE];
	int m_isMouseExpended[3];

	bool m_mouseOverExpendedState;
		
public:
	GameInputController();
	virtual ~GameInputController();

	void Update(float deltaTime);
	bool GetKeyPress(int key, bool isQueryAbsolute, bool ignoreExpendedState);
	bool GetMousePress(int key, bool isQueryAbsolute, bool ignoreExpendedState);

	bool GetKeyPressDownLast(int key);
	bool GetMousePressDownLast(int key);

	long GetZDelta();

	bool ExpendForBounds(int key, UIArea * area);
	void ExpendKey(int key);
	void ExpendMouseKey(int key);


	void ExpendAllTheThings(bool keys, bool mouse);

	bool GetIsMouseOverExpended();
	void SetMouseOverExpended();


	//TODO expend for key ?

};


#endif
