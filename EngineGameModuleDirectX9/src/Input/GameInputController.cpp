#include "GameInputController.h"
#include <vector>
using namespace std;

GameInputController::GameInputController()
{
	m_input = &g_inputControl;
	ZeroMemory(m_keyPresses, KEYS_SIZE * sizeof(int));
	ZeroMemory(m_keyDownLast, KEYS_SIZE * sizeof(int));

	ZeroMemory(m_mousePresses, 3 * sizeof(int));
	ZeroMemory(m_mouseDownLast, 3 * sizeof(int));

	ZeroMemory(m_isKeyExpended, KEYS_SIZE * sizeof(int));
	ZeroMemory(m_isMouseExpended, 3 * sizeof(int));
	//read in keybinds


	//index represents list of inputs
	//values are actions for that key

	m_mouseOverExpendedState = false;
}

GameInputController::~GameInputController()
{

}

void GameInputController::Update(float deltaTime)
{

	memcpy(m_keyDownLast, m_keyPresses, KEYS_SIZE * sizeof(int));
	memcpy(m_mouseDownLast, m_mousePresses, 3 * sizeof(int));

	ZeroMemory(m_keyPresses, KEYS_SIZE * sizeof(int));
	ZeroMemory(m_mousePresses, 3 * sizeof(int));

	ZeroMemory(m_isKeyExpended, KEYS_SIZE * sizeof(int));
	ZeroMemory(m_isMouseExpended, 3 * sizeof(int));

	m_mouseOverExpendedState = false;
}

bool GameInputController::GetMousePress(int key, bool isQueryAbsolute, bool ignoreExpendedState)
{
	//char keybuffer[9001];
	//sprintf_s(keybuffer, "GIC mouse key as hex: %0x \n", key);
	//OutputDebugString(keybuffer);

	if (m_input->MouseButtonDown(key))
	{
		if (ignoreExpendedState == false)
		{
			if (m_isMouseExpended[key] == 1)
			{
				return false;
				OutputDebugString("Expended..");
			}
		}

		if (m_mouseDownLast[key] == 1)
		{
			m_mousePresses[key] = 1;

			if (isQueryAbsolute == true)
			{
				return true;
			}
			else//lie
			{
				return false;
			}
		}
		else
		{
			m_mousePresses[key] = 1;
			return true;
		}
	}
	else
	{
		m_mousePresses[key] = 0;
		return false;
	}

	return false;
}

bool GameInputController::GetKeyPress(int key, bool isQueryAbsolute, bool ignoreExpendedState)
{

	//char keybuffer[9001];
	//sprintf_s(keybuffer, "GIC key as hex: %0x \n", key);
	//OutputDebugString(keybuffer);

	if (m_input->KeyDown(key))
	{
		if (ignoreExpendedState == false)
		{
			if (m_isKeyExpended[key] == 1)
			{
				return false;
			}
		}


		if (m_keyDownLast[key] == 1)
		{
			m_keyPresses[key] = 1;

			if (isQueryAbsolute == true)
			{
				return true;
			}
			else//lie
			{
				return false;
			}
		}
		else
		{
			m_keyPresses[key] = 1;
			return true;
		}
	}
	else
	{
		m_keyPresses[key] = 0;
		return false;
	}
	return false;
}



bool GameInputController::GetKeyPressDownLast(int key)
{
	return m_keyDownLast[key];
}

bool GameInputController::GetMousePressDownLast(int key)
{
	return m_mouseDownLast[key];
}


long GameInputController::GetZDelta()
{
	return m_input->GetZDelta();

}

bool GameInputController::ExpendForBounds(int key, UIArea * area)
{
	if (area->IsPointInBounds(&g_mouseClientPosition))
	{
		//OutputDebugString("click in bounds \n");
		m_isMouseExpended[key] = 1;
		return true;
	}

	return false;
}

void GameInputController::ExpendKey(int key)
{
	m_isKeyExpended[key] = 1;
}

void GameInputController::ExpendMouseKey(int key)
{
	m_isMouseExpended[key] = 1;
}

void GameInputController::ExpendAllTheThings(bool keys, bool mouse)
{
	//In the UIKeyDialog we want to expend everything when we are detecting the next key
	if (keys) std::fill(m_isKeyExpended, m_isKeyExpended + KEYS_SIZE, 1);
	if (mouse) std::fill(m_isMouseExpended, m_isMouseExpended + 3, 1);
}

bool GameInputController::GetIsMouseOverExpended()
{
	return m_mouseOverExpendedState;
}

void GameInputController::SetMouseOverExpended()
{
	m_mouseOverExpendedState = true;
}