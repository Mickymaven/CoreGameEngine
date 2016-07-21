#include "DirectInput8Controller.h"

DirectInput8Controller::DirectInput8Controller()
{
	m_hwnd = NULL;
	m_inputDevice = NULL;
	m_keyboard = NULL;
	m_mouse = NULL;
	memset(&m_mouseState, 0, sizeof(m_mouseState));
	memset(&m_previousMouseState, 0, sizeof(m_previousMouseState));
	memset(&m_keys, 0, sizeof(m_keys));
	memset(&m_previousKeys, 0, sizeof(m_previousKeys));
}

DirectInput8Controller::~DirectInput8Controller()
{
	//OutputDebugString("DESTRUCTOR ON ~DirectInput8Controller() !!!!!!!!!!!");
	Shutdown();
}

bool DirectInput8Controller::Init(HWND hwnd, HINSTANCE hInstance, bool mouseExclusive)
{
	m_hwnd = hwnd;

	mouseExclusive = false;
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8,
		(void **)&m_inputDevice, NULL))) return false;
	if (FAILED(m_inputDevice->CreateDevice(GUID_SysKeyboard, &m_keyboard, NULL))) return false;
	if (FAILED(m_keyboard->SetDataFormat(&c_dfDIKeyboard))) return false;
	if (FAILED(m_keyboard->SetCooperativeLevel(hwnd,
		DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))) return false;
	if (FAILED(m_keyboard->Acquire())) return false;

	ZeroMemory(m_keys, KEYS_SIZE * sizeof(char));

	if (FAILED(m_inputDevice->CreateDevice(GUID_SysMouse, &m_mouse, NULL))) return false;
	if (FAILED(m_mouse->SetDataFormat(&c_dfDIMouse))) return false;

	DWORD flags;
	if (mouseExclusive) flags = DISCL_FOREGROUND | DISCL_EXCLUSIVE | DISCL_NOWINKEY;
	else flags = DISCL_FOREGROUND | DISCL_NONEXCLUSIVE;
	if (FAILED(m_mouse->SetCooperativeLevel(hwnd, flags))) return false;
	if (FAILED(m_mouse->Acquire())) return false;

	//OutputDebugString("DI8 Controller::Init success\n");

	return true;
}

bool DirectInput8Controller::UpdateDeviceStates()
{
	if (m_mouse == NULL)
	{
		OutputDebugString("RE INIT OF M_MOUSE");
		if (FAILED(m_inputDevice->CreateDevice(GUID_SysMouse, &m_mouse, NULL))) return false;
		if (FAILED(m_mouse->SetDataFormat(&c_dfDIMouse))) return false;

		DWORD flags;
		if (false) flags = DISCL_FOREGROUND | DISCL_EXCLUSIVE | DISCL_NOWINKEY;
		else flags = DISCL_FOREGROUND | DISCL_NONEXCLUSIVE;
		if (FAILED(m_mouse->SetCooperativeLevel(m_hwnd, flags))) return false;
		if (FAILED(m_mouse->Acquire())) return false;
	}

	if (!m_mouse || !m_keyboard) return false;

	memcpy(&m_previousMouseState, &m_mouseState, sizeof(m_mouseState));

	if (FAILED(m_mouse->GetDeviceState(sizeof(DIMOUSESTATE), &m_mouseState)))
	{
		if (FAILED(m_mouse->Acquire())) return false;
		if (FAILED(m_mouse->GetDeviceState(sizeof(DIMOUSESTATE), &m_mouseState))) return false;
	}

	memcpy(m_previousKeys, m_keys, sizeof(m_keys));

	if (FAILED(m_keyboard->GetDeviceState(sizeof(m_keys), (LPVOID)m_keys)))
	{
		if (FAILED(m_keyboard->Acquire())) return false;
		if (FAILED(m_keyboard->GetDeviceState(sizeof(m_keys), (LPVOID)m_keys))) return false;
	}

	//OutputDebugString("DI8 Controller::UpdateDeviceStates success\n");

	return true;
}

bool DirectInput8Controller::KeyUp(int key)
{
	return (!(m_keys[key] & 0x80) && m_keys[key] != m_previousKeys[key]);
}

bool DirectInput8Controller::KeyDown(int key)
{
	return m_keys[key] & 0x80;
}

bool DirectInput8Controller::MouseButtonUp(int button)
{
	return (!(m_mouseState.rgbButtons[button] & 0x80)
		&& m_mouseState.rgbButtons[button] != m_previousMouseState.rgbButtons[button]);
}

bool DirectInput8Controller::MouseButtonDown(int button)
{
	return m_mouseState.rgbButtons[button] & 0x80;
}

long DirectInput8Controller::GetXDelta()
{
	return m_mouseState.lX;
}

long DirectInput8Controller::GetYDelta()
{
	return m_mouseState.lY;
}

long DirectInput8Controller::GetZDelta()
{
	return m_mouseState.lZ;
}

void DirectInput8Controller::Shutdown()
{
	if (m_keyboard)
	{
		m_keyboard->Unacquire();
		m_keyboard->Release();
		m_keyboard = NULL;
	}
	if (m_mouse)
	{
		m_mouse->Unacquire();
		m_mouse->Release();
		m_mouse = NULL;
	}
	if (m_inputDevice)
	{
		m_inputDevice->Release();
		m_inputDevice = NULL;
	}
}
