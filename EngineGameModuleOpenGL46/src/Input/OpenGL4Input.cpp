////////////////////////////////////////////////////////////////////////////////
// Filename: OpenGL4Input.cpp
////////////////////////////////////////////////////////////////////////////////

#include "OpenGL4Input.h"


OpenGL4Input::OpenGL4Input()
{
}


OpenGL4Input::OpenGL4Input(const OpenGL4Input& other)
{
}


OpenGL4Input::~OpenGL4Input()
{
}


void OpenGL4Input::Initialize()
{
	int i;


	// Initialize all the keys to being released and not pressed.
	for (i = 0; i < 256; i++)
	{
		m_keys[i] = false;
	}

	return;
}


void OpenGL4Input::KeyDown(unsigned int input)
{
	// If a key is pressed then save that state in the key array.
	m_keys[input] = true;
	return;
}


void OpenGL4Input::KeyUp(unsigned int input)
{
	// If a key is released then clear that state in the key array.
	m_keys[input] = false;
	return;
}


bool OpenGL4Input::IsKeyDown(unsigned int key)
{
	// Return what state the key is in (pressed/not pressed).
	return m_keys[key];
}