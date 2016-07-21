#include "LMButton.h"


LPD3DXFONT LMButton::m_uxFont2 = NULL;
D3DXCOLOR LMButton::m_color = D3DCOLOR_ARGB(255, 255, 255, 255);

LMButton::LMButton()
{
	m_position = { 0, 0 };
	m_dimensions = { 0, 0 };
	m_hitarea = { 0,0,0,0 };
	m_line = NULL;
	//m_labelText = NULL;
}

LMButton::~LMButton()
{
	OutputDebugString("BUTTON DESTROYED\n");
}

bool LMButton::Init(POINT * position, POINT * size, string text)
{
	if (m_uxFont2 == NULL)
		if (FAILED(
			D3DXCreateFont(g_D3D_Device, 20, 0, FW_BOLD, 1, false,
				DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
				DEFAULT_PITCH | FF_SWISS, "", &m_uxFont2)
			)) return false;


	m_labelText = new char[text.length() + 1];
	strcpy_s(m_labelText, text.length() + 1, text.c_str());


	m_position.x = position->x;//position
	m_position.y = position->y;//position
	m_dimensions.x = size->x;
	m_dimensions.y = size->y;

	m_hitarea.left = position->x;
	m_hitarea.top = position->y;
	m_hitarea.right = position->x + size->x;
	m_hitarea.bottom = position->y + size->y;

	m_leftVerts[0] = D3DXVECTOR2(m_hitarea.left, m_hitarea.bottom);
	m_leftVerts[1] = D3DXVECTOR2(m_hitarea.left, m_hitarea.top);
	m_topVerts[0] = D3DXVECTOR2(m_hitarea.left, m_hitarea.top);
	m_topVerts[1] = D3DXVECTOR2(m_hitarea.right, m_hitarea.top);
	m_rightVerts[0] = D3DXVECTOR2(m_hitarea.right, m_hitarea.top);
	m_rightVerts[1] = D3DXVECTOR2(m_hitarea.right, m_hitarea.bottom);
	m_bottomVerts[0] = D3DXVECTOR2(m_hitarea.right, m_hitarea.bottom);
	m_bottomVerts[1] = D3DXVECTOR2(m_hitarea.left, m_hitarea.bottom);

	m_lines[0] = m_leftVerts;
	m_lines[1] = m_topVerts;
	m_lines[2] = m_rightVerts;
	m_lines[3] = m_bottomVerts;

	return true;
}

void LMButton::Render()
{

	m_uxFont2->DrawText(NULL, m_labelText, -1, &m_hitarea, DT_CENTER, m_color);

	for (int i = 0; i < 4; i++)
	{
		D3DXCreateLine(g_D3D_Device, &m_line);
		m_line->Begin();
		m_line->Draw(m_lines[i], 2, m_color);
		m_line->End();
		m_line->Release();
	}
}

bool LMButton::IsHit(float x, float y)
{
	if (x > m_hitarea.left)
	{
		if (x < m_hitarea.right)
		{
			if (y > m_hitarea.top)
			{
				if (y < m_hitarea.bottom)
				{
					//OutputDebugString("LMButton has been hit. \n");
					return true;//Turl

				}
			}
		}
	}
	return false;
}