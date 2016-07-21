#include "GameMessage.h"
#include <string>

GameMessage::GameMessage()
{

}

GameMessage::GameMessage(LPD3DXFONT messageFont)
{

	m_messageFont = messageFont;


	m_messagePos = { 0, 150, g_clientSizeRect->right, g_clientSizeRect->bottom - 200 };

}

GameMessage::~GameMessage()
{

}

void GameMessage::SetMessage(string message)
{
	strcpy_s(m_messageBuffer, message.c_str());

	m_timer.RestartWithDuration(5.0f, true);

}

void GameMessage::Update(float deltaTime)
{
	m_timer.Update(deltaTime);
}

void GameMessage::Render()
{
	if (m_timer.GetRemainder() > 0)
	{
		m_messageFont->DrawText(NULL, m_messageBuffer, -1, &m_messagePos, DT_CENTER, D3DCOLOR_XRGB(192, 192, 192));
	}
}
