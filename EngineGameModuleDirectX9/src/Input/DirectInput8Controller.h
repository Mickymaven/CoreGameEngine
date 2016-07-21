#if !defined(DIRECTINPUT8CONTROLLER_H)

#define DIRECTINPUT8CONTROLLER_H

#define LEFT_BUTTON     0
#define RIGHT_BUTTON    1

#define KEYS_SIZE 256

#define DIRECTINPUT_VERSION 0x0800

#include <windows.h>
#include <dinput.h>

class DirectInput8Controller
{
public:
	DirectInput8Controller();
	virtual ~DirectInput8Controller();
	bool Init(HWND hwnd, HINSTANCE hInstance, bool mouseExclusive);

	bool UpdateDeviceStates();

	bool KeyUp(int key);//key presses
	bool KeyDown(int key);
	bool MouseButtonUp(int button);//mouse presses
	bool MouseButtonDown(int button);
	long GetXDelta();//mouse coords
	long GetYDelta();
	long GetZDelta();

	void Shutdown();

private:

	HWND m_hwnd;
	LPDIRECTINPUT8 m_inputDevice;

	LPDIRECTINPUTDEVICE8 m_keyboard;
	char m_keys[KEYS_SIZE];
	char m_previousKeys[KEYS_SIZE];

	LPDIRECTINPUTDEVICE8 m_mouse;
	DIMOUSESTATE m_mouseState;
	DIMOUSESTATE m_previousMouseState;
};

#endif
